/* vim:set ts=8 sts=4 sw=4 tw=0 */
/*
 * mnode.c - mnode interfaces.
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 11-Aug-2001.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "wordlist.h"
#include "wordbuf.h"
#include "mnode.h"

#if defined(_MSC_VER) || defined(__GNUC__)
# define INLINE __inline
#else
# define INLINE 
#endif

int n_mnode_new = 0;
int n_mnode_delete = 0;

    INLINE static mnode*
mnode_new()
{
#if 0
    ++n_mnode_new;
    return (mnode*)calloc(1, sizeof(mnode));
#else
    /* Windows�̑���Ƃ��̂ق��������̂ł��B */
    mnode *obj = (mnode*)malloc(sizeof(mnode));
    obj->next = obj->child = NULL;
    obj->list = NULL;
    ++n_mnode_new;
    return obj;
#endif
}

    static void
mnode_delete(mnode* p)
{
    while (p)
    {
	mnode* child = p->child;

	if (p->list)
	    wordlist_delete(p->list);
	if (p->next)
	    mnode_delete(p->next);
	free(p);
	p = child;
	++n_mnode_delete;
    }
}

    void
mnode_print(mnode* vp, unsigned char* p)
{
    static unsigned char buf [256];

    if (!vp)
	return;
    if (!p)
	p = &buf[0];
    p[0] = MNODE_GET_CH(vp);
    p[1] = '\0';
    if (vp->list)
	printf("%s (list=%p)\n", buf, vp->list);
    if (vp->child)
	mnode_print(vp->child, p + 1);
    if (vp->next)
	mnode_print(vp->next, p);
}

#define MNODE_BUFENABLE 0
#define MNODE_BUFSIZE 16384

    void
mnode_close(mnode* p)
{
    mnode_delete(p);
}

/*
 * �����̃m�[�h�Ƀt�@�C������f�[�^���܂Ƃ߂Ēǉ�����B
 */
    mnode*
mnode_load(mnode* root, FILE* fp)
{
    mnode **pp = &root;
    int mode = 0, cnt = 0;
    int depth = 0, maxdepth = -1;
    int ch;
    wordbuf *buf;
    wordlist **ppword;

#if MNODE_BUFENABLE
    unsigned char cache[MNODE_BUFSIZE];
    int remain = 0, point = 0;
#endif

    if (!fp || !(buf = wordbuf_open()))
	return root; /* ERROR! */

    /*
     * EOF�̏������B���B�s���Ȍ`���̃t�@�C�����������ꍇ���l�����Ă��Ȃ��B�e
     * ���[�h����EOF�̓���p�ӂ��Ȃ��Ɛ������Ȃ����c�ʓ|�Ȃ̂ł��Ȃ��B�f�[
     * �^�t�@�C���͐�΂ɊԈ���Ă��Ȃ��Ƃ����O���u���B
     */
    do
    {
#if MNODE_BUFENABLE
	if (point >= remain)
	{
	    remain = fread(cache, 1, MNODE_BUFSIZE, fp);
	    point = 0;
	}
	ch = (remain <= 0 && feof(fp)) ? EOF : cache[point++];
#else
	ch = fgetc(fp);
#endif

	/* ���:mode�̃I�[�g�}�g�� */
	switch (mode)
	{
	    case 0: /* ���x���P�ꌟ�����[�h */
		/* �󔒂̓��x���P��ɂȂ肦�܂��� */
		if (isspace(ch) || ch == EOF)
		    continue;

		/* �R�����g���C���`�F�b�N */
		if (ch == ';')
		{
		    mode = 2; /* �s���܂ŐH���ׂ����[�h �ֈڍs */
		    continue;
		}

		mode = 1; /* ���x���P��̓Ǎ����[�h �ֈڍs*/
		depth = 0;
		pp = &root;
		goto SEARCH_OR_NEW;

	    case 1: /* ���x���P��̓Ǎ����[�h */
		/* ���x���̏I�������o */
		if (ch == '\t')
		{
		    wordbuf_reset(buf);
		    mode = 3; /* �P��O�󔒓ǔ�΂����[�h �ֈڍs */
		    continue;
		}

		pp = &(*pp)->child;
SEARCH_OR_NEW:
		/* ����ch�����Z��m�[�h�������B������΍��B */
		/*
		 * �ŏ��͕ʊ֐��ƂȂ��Ă��ă\�[�X�̕ʉӏ�������Q�Ƃ���Ă�
		 * �����A�Ăяo���񐔂����ɑ������ߓW�J�����BProfile�r���h
		 * ��1000msec���x�̍�������B
		 */
		while (1)
		{
		    if (!(*pp))
		    {
			*pp = mnode_new();
			MNODE_SET_CH(*pp, ch);
			break;
		    }
		    else if (MNODE_GET_CH(*pp) == ch)
			break;
		    pp = &(*pp)->next;
		}

		if (++depth > maxdepth)
		    maxdepth = depth;
		break;

	    case 2: /* �s���܂ŐH���ׂ����[�h */
		if (ch == '\n')
		{
		    wordbuf_reset(buf);
		    mode = 0; /* ���x���P�ꌟ�����[�h �֖߂� */
		}
		break;

	    case 3: /* �P��O�󔒓ǂݔ�΂����[�h */
		if (ch == '\n')
		{
		    wordbuf_reset(buf);
		    mode = 0; /* ���x���P�ꌟ�����[�h �֖߂� */
		}
		else if (ch != '\t')
		{
		    /* �P��o�b�t�@���Z�b�g */
		    wordbuf_reset(buf);
		    wordbuf_add(buf, (unsigned char)ch);
		    /* �P�ꃊ�X�g�̍Ō������(���ꃉ�x����������) */
		    ppword = &(*pp)->list;
		    while (*ppword)
			ppword = &(*ppword)->next;
		    mode = 4; /* �P��̓ǂݍ��݃��[�h �ֈڍs */
		}
		break;

	    case 4: /* �P��̓ǂݍ��݃��[�h */
		if (ch == '\t' || ch == '\n')
		{
		    /* �P����L�� */
		    *ppword = wordlist_new(wordbuf_get(buf));
		    wordbuf_reset(buf);

		    if (ch == '\t')
		    {
			ppword = &(*ppword)->next;
			mode = 3; /* �P��O�󔒓ǂݔ�΂����[�h �֖߂� */
		    }
		    else
		    {
			ppword = NULL;
			mode = 0; /* ���x���P�ꌟ�����[�h �֖߂� */
		    }
		}
		else
		    wordbuf_add(buf, (unsigned char)ch);
		break;
	}
    }
    while (ch != EOF);
    /*fprintf(stderr, "mode=%d\n", mode);*/

    wordbuf_close(buf);
    return root;
}

    mnode*
mnode_open(FILE* fp)
{
    return mnode_load(NULL, fp);
}

#if 0
    static int
mnode_size(mnode* p)
{
    return p ? mnode_size(p->child) + mnode_size(p->next) + 1 : 0;
}
#endif

    static mnode*
mnode_query_stub(mnode* node, unsigned char* query)
{
    while (1)
    {
	if (*query == MNODE_GET_CH(node))
	    return (*++query == '\0') ? node :
		(node->child ? mnode_query_stub(node->child, query) : NULL);
	if (!(node = node->next))
	    break;
    }
    return NULL;
}

    mnode*
mnode_query(mnode* node, unsigned char* query)
{
    return (query && *query != '\0' && node)
	? mnode_query_stub(node, query) : 0;
}

    static void
mnode_traverse_stub(mnode* node, MNODE_TRAVERSE_PROC proc, void* data)
{
    while (1)
    {
	if (node->child)
	    mnode_traverse_stub(node->child, proc, data);
	proc(node, data);
	if (!(node = node->next))
	    break;
    }
}

    void
mnode_traverse(mnode* node, MNODE_TRAVERSE_PROC proc, void* data)
{
    if (node && proc)
    {
	proc(node, data);
	if (node->child)
	    mnode_traverse_stub(node->child, proc, data);
    }
}
