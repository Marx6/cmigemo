/* vim:set ts=8 sts=4 sw=4 tw=0 */
/*
 * migemo.c -
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 11-Aug-2001.
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

/* migemo�I�u�W�F�N�g */
struct _migemo
{
    mnode* node;
    romaji* roma2hira;
    romaji* hira2kata;
    rxgen* rx;
};

/*
 * migemo interfaces
 */

/*
 * ������migemo�I�u�W�F�N�g�Ɏ����t�@�C����ǉ��Ǎ�����B
 */
    int
migemo_load(migemo* obj, char* dict, char* roma_dict, char* kata_dict)
{
    int result = 0;
    FILE *fp;

    if (!obj)
	return result;

    /* migemo�����ǂݍ��� */
    if (dict && (fp = fopen(dict, "rt")))
    {
	obj->node = mnode_load(obj->node, fp);
	fclose(fp);
	result |= 1;
    }

    /* ���[�}�������ǂݍ��� */
    if (roma_dict)
    {
	romaji_load(obj->roma2hira, roma_dict);
	result |= 2;
    }

    /* �J�^�J�i�����ǂݍ��� */
    if (kata_dict)
    {
	romaji_load(obj->hira2kata, kata_dict);
	result |= 4;
    }

    return result;
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
    obj->node = mnode_open(NULL);
    obj->rx = rxgen_open();
    obj->roma2hira = romaji_open();
    obj->hira2kata = romaji_open();
    if (!obj->rx || !obj->roma2hira || !obj->hira2kata)
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
	char dir[_MAX_PATH], roma_dict[_MAX_PATH], kata_dict[_MAX_PATH];

	filename_directory(dir, dict);
	strcpy(roma_dict, strlen(dir) ? dir : ".");
	strcpy(kata_dict, strlen(dir) ? dir : ".");
	strcat(roma_dict, "/romaji.dat");
	strcat(kata_dict, "/hira2kata.dat");

	migemo_load(obj, dict, roma_dict, kata_dict);
    }
    return obj;
}

    void
migemo_close(migemo* obj)
{
    if (obj)
    {
	if (obj->hira2kata)
	    romaji_close(obj->hira2kata);
	if (obj->roma2hira)
	    romaji_close(obj->roma2hira);
	if (obj->rx)
	    rxgen_close(obj->rx);
	if (obj->node)
	    mnode_close(obj->node);
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
    wordlist *list = p->list;

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

    if (pnode = mnode_query(object->node, query))
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
	/* �������A�J�^�J�i�A�y�т���ɂ�鎫�������ǉ� */
	if (add_roma(object, query))
	    add_dubious_roma(object, object->rx, query);

	/* query���M�͂��������ɉ����� */
	rxgen_add(object->rx, query);
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
    return (obj && obj->node) ? 1 : 0;
}

#if 1
/*
 * ��Ƀf�o�b�O�p�̉B���֐�
 */

    void
migemo_print(migemo* object)
{
    if (object)
	mnode_print(object->node, NULL);
}
#endif
