/* vim:set ts=8 sts=4 sw=4 tw=0: */
/*
 * migemo.c -
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 19-Oct-2003.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
#define VOWELS_STRING "aiueo"

#ifdef __BORLANDC__
# define EXPORTS __declspec(dllexport)
#else
# define EXPORTS
#endif

typedef int (*MIGEMO_PROC_ADDWORD)(void* data, unsigned char* word);

/* migemo�I�u�W�F�N�g */
struct _migemo
{
    int enable;
    mtree_p mtree;
    romaji* roma2hira;
    romaji* hira2kata;
    romaji* han2zen;
    rxgen* rx;
    MIGEMO_PROC_ADDWORD addword;
};

/*
 * migemo interfaces
 */

    static mtree_p
load_mtree_dictionary(mtree_p mtree, char* dict_file)
{
    FILE *fp;

    if ((fp = fopen(dict_file, "rt")) == NULL)
	return NULL;			/* Can't find file */
    mtree = mnode_load(mtree, fp);
    fclose(fp);
    return mtree;
}

/*
 * ������migemo�I�u�W�F�N�g�Ɏ����t�@�C����ǉ��Ǎ�����B
 */
    EXPORTS
    int 
migemo_load(migemo* obj, int dict_id, char* dict_file)
{
    if (!obj && dict_file)
	return MIGEMO_DICTID_INVALID;

    if (dict_id == MIGEMO_DICTID_MIGEMO)
    {
	/* migemo�����ǂݍ��� */
	mtree_p mtree;

	if ((mtree = load_mtree_dictionary(obj->mtree, dict_file)) == NULL)
	    return MIGEMO_DICTID_INVALID;
	obj->mtree = mtree;
	obj->enable = 1;
	return dict_id;			/* Loaded successfully */
    }
    else
    {
	romaji *dict;

	switch (dict_id)
	{
	    case MIGEMO_DICTID_ROMA2HIRA:
		/* ���[�}�������ǂݍ��� */
		dict = obj->roma2hira;
		break;
	    case MIGEMO_DICTID_HIRA2KATA:
		/* �J�^�J�i�����ǂݍ��� */
		dict = obj->hira2kata;
		break;
	    case MIGEMO_DICTID_HAN2ZEN:
		/* ���p���S�p�����ǂݍ��� */
		dict = obj->han2zen;
		break;
	    default:
		dict = NULL;
		break;
	}
	if (dict && romaji_load(dict, dict_file) == 0)
	    return dict_id;
	else
	    return MIGEMO_DICTID_INVALID;
    }
}

/*
 * (dict == NULL)�Ƃ��Ď�����ǂݍ��܂��Ȃ����Ƃ��\
 */
    EXPORTS
    migemo*
migemo_open(char* dict)
{
    migemo *obj;

    /* migemo�I�u�W�F�N�g�Ɗe�����o���\�z */
    if (!(obj = (migemo*)malloc(sizeof(migemo))))
	return obj;
    obj->enable = 0;
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
	mtree_p mtree;

	filename_directory(dir, dict);
	tmp = strlen(dir) ? dir : ".";
	strcpy(roma_dict, tmp);
	strcpy(kata_dict, tmp);
	strcpy(h2z_dict, tmp);
	strcat(roma_dict, "/" DICT_ROMA2HIRA);
	strcat(kata_dict, "/" DICT_HIRA2KATA);
	strcat(h2z_dict, "/" DICT_HAN2ZEN);

	mtree = load_mtree_dictionary(obj->mtree, dict);
	if (mtree)
	{
	    obj->mtree = mtree;
	    obj->enable = 1;
	    romaji_load(obj->roma2hira, roma_dict);
	    romaji_load(obj->hira2kata, kata_dict);
	    romaji_load(obj->han2zen, h2z_dict);
	}
    }
    return obj;
}

    EXPORTS
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

/*
 * mnode�̎��P�ꃊ�X�g�𐳋K�\�������G���W���ɓ��͂���B
 */
    static void
migemo_query_proc(mnode* p, void* data)
{
    migemo *object = (migemo*)data;
    wordlist_p list = p->list;

    for (; list; list = list->next)
	object->addword(object, list->ptr);
}

/*
 * �o�b�t�@��p�ӂ���mnode�ɍċA�ŏ������܂���
 */
    static void
add_mnode_query(migemo* object, unsigned char* query)
{
    mnode *pnode;

    if ((pnode = mnode_query(object->mtree, query)) != NULL)
	mnode_traverse(pnode, migemo_query_proc, object);
}

    static int
add_roma(migemo* object, unsigned char* query)
{
    unsigned char *stop, *hira, *kata;

    hira = romaji_convert(object->roma2hira, query, &stop);
    if (!stop)
    {
	object->addword(object, hira);
	/* �������ɂ�鎫������ */
	add_mnode_query(object, hira);
	/* �Љ���������𐶐������ɉ����� */
	kata = romaji_convert(object->hira2kata, hira, NULL);
	object->addword(object, kata);
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
    static unsigned char candidate[] = VOWELS_STRING;
    int len;
    char *buf;

    if (!(len = strlen(query)))
	return;
    if (!(buf = malloc(len + 1 + 3))) /* NUL�Ɗg�������p(�Œ�:xtu) */
	return;
    memcpy(buf, query, len + 1);
    buf[len + 1] = '\0';

    if (!strchr(candidate, buf[len - 1]))
    {
	unsigned char *ptr;

	/* [aiueo]�����Ԃɕ₤ */
	for (ptr = candidate; *ptr; ++ptr)
	{
	    buf[len] = *ptr;
	    add_roma(object, buf);
	}
	/* ���m��P��̒�����2�������A���m�蕶���̒��O���ꉹ�Ȃ�΁c */
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

/*
 * query�𕶐߂ɕ�������B���߂̐؂�ڂ͒ʏ�A���t�@�x�b�g�̑啶���B���߂���
 * �������̑啶���Ŏn�܂������߂͔�啶������؂�Ƃ���B
 */
    static wordlist_p
parse_query(unsigned char* query)
{
    unsigned char *buf = query;
    wordlist_p querylist = NULL, *pp = &querylist;

    while (*buf != '\0')
    {
	unsigned char *start = buf++;

	if (isupper(start[0]) && isupper(buf[0]))
	{
	    ++buf;
	    while (buf[0] != '\0' && isupper(buf[0]))
		++buf;
	}
	else
	    while (buf[0] != '\0' && !isupper(buf[0]))
		++buf;
	*pp = wordlist_open_len(start, buf - start);
	pp = &(*pp)->next;
    }
    return querylist;
}

/*
 * 1�̒P���migemo�ϊ��B�����̃`�F�b�N�͍s�Ȃ�Ȃ��B
 */
    static int
query_a_word(migemo* object, unsigned char* query)
{
    unsigned char* zen;

    /* query���M�͂��������ɉ����� */
    object->addword(object, query);

    /* query��S�p�ɂ��Č��ɉ����� */
    zen = romaji_convert(object->han2zen, query, NULL);
    if (zen != NULL)
    {
	object->addword(object, zen);
	romaji_release(object->han2zen, zen);
    }

    /* �������A�J�^�J�i�A�y�т���ɂ�鎫�������ǉ� */
    if (add_roma(object, query))
	add_dubious_roma(object, object->rx, query);

    return 1;
}

    static int
addword_rxgen(migemo* object, unsigned char* word)
{
    return rxgen_add(object->rx, word);
}

    EXPORTS
    unsigned char*
migemo_query(migemo* object, unsigned char* query)
{
    unsigned char *retval = NULL;
    wordlist_p querylist = NULL;
    wordbuf_p outbuf = NULL;

    if (object && object->rx && query)
    {
	wordlist_p p;

	querylist = parse_query(query);
	if (querylist == NULL)
	    goto MIGEMO_QUERY_END; /* ��query�̂��߃G���[ */
	outbuf = wordbuf_open();
	if (outbuf == NULL)
	    goto MIGEMO_QUERY_END; /* �o�͗p�̃������̈�s���̂��߃G���[ */

	/* �P��Q��rxgen�I�u�W�F�N�g�ɓ��͂����K�\���𓾂� */
	object->addword = (MIGEMO_PROC_ADDWORD)addword_rxgen;
	rxgen_reset(object->rx);
	for (p = querylist; p; p = p->next)
	{
	    unsigned char* answer;

	    query_a_word(object, p->ptr);
	    /* �����p�^�[��(���K�\��)���� */
	    answer = rxgen_generate(object->rx);
	    rxgen_reset(object->rx);
	    wordbuf_cat(outbuf, answer);
	    rxgen_release(object->rx, answer);
	}
    }

MIGEMO_QUERY_END:
    if (outbuf)
    {
	retval = outbuf->buf;
	outbuf->buf = NULL;
	wordbuf_close(outbuf);
    }
    if (querylist)
	wordlist_close(querylist);

    return retval;
}

    EXPORTS
    void
migemo_release(migemo* p, unsigned char* string)
{
    free(string);
}

    EXPORTS
    int
migemo_set_operator(migemo* object, int index, unsigned char* op)
{
    if (object)
    {
	int retval = rxgen_set_operator(object->rx, index, op);
	return retval ? 0 : 1;
    }
    else
	return 0;
}

    EXPORTS
    const unsigned char*
migemo_get_operator(migemo* object, int index)
{
    return object ? rxgen_get_operator(object->rx, index) : NULL;
}

    EXPORTS
    void
migemo_setproc_char2int(migemo* object, MIGEMO_PROC_CHAR2INT proc)
{
    if (object)
	rxgen_setproc_char2int(object->rx, (RXGEN_PROC_CHAR2INT)proc);
}

    EXPORTS
    void
migemo_setproc_int2char(migemo* object, MIGEMO_PROC_INT2CHAR proc)
{
    if (object)
	rxgen_setproc_int2char(object->rx, (RXGEN_PROC_INT2CHAR)proc);
}

/*
 * migemo�������ǂݍ��܂�Ă��邩�𒲂ׂ�
 */
    EXPORTS
    int
migemo_is_enable(migemo* obj)
{
    return obj ? obj->enable : 0;
}

#if 1
/*
 * ��Ƀf�o�b�O�p�̉B���֐�
 */
    EXPORTS
    void
migemo_print(migemo* object)
{
    if (object)
	mnode_print(object->mtree, NULL);
}
#endif
