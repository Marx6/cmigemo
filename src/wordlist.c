/* vim:set ts=8 sts=4 sw=4 tw=0 */
/*
 * wordlist.h -
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 07-Aug-2001.
 */

#include <stdlib.h>
#include <string.h>
#include "wordlist.h"

int n_wordlist_new	= 0;
int n_wordlist_delete	= 0;
int n_wordlist_total	= 0;

    wordlist*
wordlist_new(unsigned char* ptr)
{
    wordlist *p;

    ++n_wordlist_new;
    if ((p = (wordlist*)calloc(1, sizeof(wordlist))) && ptr)
    {
	/* �ق�strdup()�Ɠ����Ȏ����B�P��̕ۑ��ɕK�v�ȑ���������m�肽����
	 * �ŁB*/
	int len = strlen(ptr) + 1;

	n_wordlist_total += len;
	if (p->ptr = malloc(len))
	    strcpy(p->ptr, ptr);
    }
    return p;
}

    void
wordlist_delete(wordlist* p)
{
    if (p)
    {
	++n_wordlist_delete;
	free(p->ptr);
	if (p->next)
	    wordlist_delete(p->next);
	free(p);
    }
}

