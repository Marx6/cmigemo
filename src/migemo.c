/* vim:set ts=8 sts=4 sw=4 tw=0 */
/*
 * migemo.c -
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 24-Jan-2002.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordbuf.h"
#include "wordlist.h"
#include "mnode.h"
#include "rxgen.h"
#include "romaji.h"
#include "filename.h"
#include "migemo.h"

#define DICT_MIGEMO "migemo-dict"
#define DICT_ROMA2HIRA "roma2hira.dat"
#define DICT_HIRA2KATA "hira2kata.dat"
#define DICT_HAN2ZEN "han2zen.dat"

/* migemo�I�u�W�F�N�g */
struct _migemo
{
    mtree_p mtree;
    romaji* roma2hira;
    romaji* hira2kata;
    romaji* han2zen;
    rxgen* rx;
};

/*
 * migemo interfaces
 */

/*
 * ������migemo�I�u�W�F�N�g�Ɏ����t�@�C����ǉ��Ǎ�����B
 */
    int 
migemo_load(migemo* obj, int dict_id, char* dict_file)
{
    FILE *fp;

    if (!obj && dict_file)
	return MIGEMO_DICTID_INVALID;

    switch (dict_id)
    {
	case MIGEMO_DICTID_MIGEMO:
	    /* migemo�����ǂݍ��� */
	    if (fp = fopen(dict_file, "rt"))
	    {
		mtree_p mtree = mnode_load(obj->mtree, fp);

		fclose(fp);
		if (mtree)
		    obj->mtree = mtree;
		else
		    return MIGEMO_DICTID_INVALID; /* Exhausted memory */
	    }
	    else
		return MIGEMO_DICTID_INVALID; /* Can't find file */
	    break;

	case MIGEMO_DICTID_ROMA2HIRA:
	    /* ���[�}�������ǂݍ��� */
	    romaji_load(obj->roma2hira, dict_file);
	    break;

	case MIGEMO_DICTID_HIRA2KATA:
	    /* �J�^�J�i�����ǂݍ��� */
	    romaji_load(obj->hira2kata, dict_file);
	    break;

	case MIGEMO_DICTID_HAN2ZEN:
	    /* ���p���S�p�����ǂݍ��� */
	    romaji_load(obj->han2zen, dict_file);
	    break;

	default:
	    return MIGEMO_DICTID_INVALID;
    }

    return dict_id;
}

/*
 * (dict == NULL)�Ƃ��Ď�����ǂݍ��܂��Ȃ����Ƃ��\
 */
    migemo*
migemo_open(char* dict)
{
    migemo *obj;

    /* migemo�I�u�W�F�N�g�Ɗe�����o���\�z */
    if (!(obj = (migemo*)malloc(sizeof(migemo))))
	return obj;
    obj->mtree = mnode_open(NULL);
    obj->rx = rxgen_open();
    obj->roma2hira =	romaji_open();
    obj->hira2kata =	romaji_open();
    obj->han2zen =	romaji_open();
    if (!obj->rx || !obj->roma2hira || !obj->hira2kata || !obj->han2zen)
    {
	migemo_close(obj);
	return obj = NULL;
    }

    /* �f�t�H���gmigemo�������w�肳��Ă����烍�[�}���ƃJ�^�J�i�������T�� */
    if (dict)
    {
#ifndef _MAX_PATH
# define _MAX_PATH 1024 /* ���������Ȑ��l */
#endif
	char dir[_MAX_PATH];
	char roma_dict[_MAX_PATH], kata_dict[_MAX_PATH], h2z_dict[_MAX_PATH];
	char *tmp;

	filename_directory(dir, dict);
	tmp = strlen(dir) ? dir : ".";
	strcpy(roma_dict, tmp);
	strcpy(kata_dict, tmp);
	strcpy(h2z_dict, tmp);
	strcat(roma_dict, "/" DICT_ROMA2HIRA);
	strcat(kata_dict, "/" DICT_HIRA2KATA);
	strcat(h2z_dict, "/" DICT_HAN2ZEN);

	migemo_load(obj, MIGEMO_DICTID_MIGEMO, dict);
	migemo_load(obj, MIGEMO_DICTID_ROMA2HIRA, roma_dict);
	migemo_load(obj, MIGEMO_DICTID_HIRA2KATA, kata_dict);
	migemo_load(obj, MIGEMO_DICTID_HAN2ZEN, h2z_dict);
    }
    return obj;
}

    void
migemo_close(migemo* obj)
{
    if (obj)
    {
	if (obj->han2zen)
	    romaji_close(obj->han2zen);
	if (obj->hira2kata)
	    romaji_close(obj->hira2kata);
	if (obj->roma2hira)
	    romaji_close(obj->roma2hira);
	if (obj->rx)
	    rxgen_close(obj->rx);
	if (obj->mtree)
	    mnode_close(obj->mtree);
	free(obj);
    }
}

/*
 * query version 2
 */

    static void
migemo_query_proc(mnode* p, void* data)
{
    rxgen *rx = (rxgen*)data;
    wordlist_p list = p->list;

    for (; list; list = list->next)
	rxgen_add(rx, list->ptr);
}

/*
 * �o�b�t�@��p�ӂ���mnode�ɍċA�ŏ������܂���
 */
    static void
add_mnode_query(migemo* object, unsigned char* query)
{
    mnode *pnode;

    if (pnode = mnode_query(object->mtree, query))
	mnode_traverse(pnode, migemo_query_proc, object->rx);
}

    static int
add_roma(migemo* object, unsigned char* query)
{
    unsigned char *stop, *hira, *kata;

    hira = romaji_convert(object->roma2hira, query, &stop);
    if (!stop)
    {
	rxgen_add(object->rx, hira);
	/* �������ɂ�鎫������ */
	add_mnode_query(object, hira);
	/* �Љ���������𐶐������ɉ����� */
	kata = romaji_convert(object->hira2kata, hira, NULL);
	rxgen_add(object->rx, kata);
	/* �J�^�J�i�ɂ�鎫������ */
	add_mnode_query(object, kata);
	romaji_release(object->hira2kata, kata); /* �J�^�J�i��� */
    }
    romaji_release(object->roma2hira, hira); /* ��������� */

    return stop ? 1 : 0;
}

/*
 * ���[�}���ϊ����s���S���������ɁA[aiueo]�����"xn"��"xtu"�����ĕϊ�����
 * �݂�B
 */
    static void
add_dubious_roma(migemo* object, rxgen* rx, unsigned char* query)
{
    int len;
    char *buf;
    unsigned char candidate[] = "aiueo", *ptr;

    if (!(len = strlen(query)))
	return;
    if (!(buf = malloc(len + 1 + 3))) /* NUL�Ɗg�������p(�Œ�:xtu) */
	return;
    strcpy(buf, query);
    buf[len + 1] = '\0';

    if (!strchr(candidate, buf[len - 1]))
    {
	/* [aiueo]�����Ԃɕ₤ */
	for (ptr = candidate; *ptr; ++ptr)
	{
	    buf[len] = *ptr;
	    add_roma(object, buf);
	}
	/* ���m��P��̒�����2�������A���m�蕶���̒��O���d��Ȃ�΁c */
	if (len < 2 || strchr(candidate, buf[len - 2]))
	{
	    if (buf[len - 1] == 'n')
	    {
		/* �u��v�����Ă݂� */
		strcpy(&buf[len - 1], "xn");
		add_roma(object, buf);
	    }
	    else
	    {
		/* �u���v�����Ă݂� */
		strcpy(&buf[len - 1], "xtu");
		add_roma(object, buf);
	    }
	}
    }

    free(buf);
}

    unsigned char*
migemo_query(migemo* object, unsigned char* query)
{
    unsigned char* answer = NULL;

    if (object && object->rx && query)
    {
	unsigned char* zen;
	/* query���M�͂��������ɉ����� */
	rxgen_add(object->rx, query);

	/* query��S�p�ɂ��Č��ɉ����� */
	if (zen = romaji_convert(object->han2zen, query, NULL))
	{
	    rxgen_add(object->rx, zen);
	    romaji_release(object->han2zen, zen);
	}

	/* �������A�J�^�J�i�A�y�т���ɂ�鎫�������ǉ� */
	if (add_roma(object, query))
	    add_dubious_roma(object, object->rx, query);

	/* query���̂��̂ɂ�鎫������ */
	add_mnode_query(object, query);

	/* �����p�^�[��(���K�\��)���� */
	answer = rxgen_generate(object->rx);
	rxgen_reset(object->rx);
    }

    return answer;
}

    void
migemo_release(migemo* p, unsigned char* string)
{
    rxgen_release(NULL, string);
}

    int
migemo_set_operator(migemo* object, int index, unsigned char* op)
{
    return object ? rxgen_set_operator(object->rx, index, op) : 1;
}

    const unsigned char*
migemo_get_operator(migemo* object, int index)
{
    return object ? rxgen_get_operator(object->rx, index) : NULL;
}

    void
migemo_setproc_char2int(migemo* object, MIGEMO_PROC_CHAR2INT proc)
{
    if (object)
	rxgen_setproc_char2int(object->rx, (RXGEN_PROC_CHAR2INT)proc);
}

    void
migemo_setproc_int2char(migemo* object, MIGEMO_PROC_INT2CHAR proc)
{
    if (object)
	rxgen_setproc_int2char(object->rx, (RXGEN_PROC_INT2CHAR)proc);
}

    int
migemo_is_enable(migemo* obj)
{
    return (obj && obj->mtree) ? 1 : 0;
}

#if 1
/*
 * ��Ƀf�o�b�O�p�̉B���֐�
 */

    void
migemo_print(migemo* object)
{
    if (object)
	mnode_print(object->mtree, NULL);
}
#endif
