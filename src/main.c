/* vim:set ts=8 sts=4 sw=4 tw=0: */
/*
 * main.c - migemo���C�u�����e�X�g�h���C�o
 *
 * Written By:  Muraoka Taro  <koron@tka.att.en.jp>
 * Last Change: 16-May-2002.
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "migemo.h"

#define MIGEMODICT_NAME "migemo-dict"

/*
 * main
 */

    int
query_loop(migemo* p, int quiet)
{
    while (!feof(stdin))
    {
	unsigned char buf[256], *ans;

	if (!quiet)
	    printf("QUERY: ");
	/* gets()���g���Ă�����fgets()�ɕύX */
	if (!fgets(buf, sizeof(buf), stdin))
	{
	    if (!quiet)
		printf("\n");
	    break;
	}
	/* ���s��NUL�����ɒu�������� */
	if ((ans = strchr(buf, '\n')) != NULL)
	    *ans = '\0';

	ans = migemo_query(p, buf);
	if (ans)
	    printf(quiet ? "%s\n" : "PATTERN: %s\n", ans);
	migemo_release(p, ans);
    }
    return 0;
}

    int
main(int argc, char** argv)
{
    int mode_vim = 0;
    int mode_quiet = 0;
    char* dict = NULL;
    migemo *pmigemo;
    FILE *fplog = stdout;
    char *word = NULL;

    while (*++argv)
    {
	if (0)
	    ;
	else if (!strcmp("--vim", *argv) || !strcmp("-v", *argv))
	    mode_vim = 1;
	else if (argv[1] && (!strcmp("--dict", *argv) || !strcmp("-d", *argv)))
	    dict = *++argv;
	else if (argv[1] && (!strcmp("--word", *argv) || !strcmp("-w", *argv)))
	    word = *++argv;
	else if (!strcmp("--quiet", *argv) || !strcmp("-q", *argv))
	    mode_quiet = 1;
    }

#ifdef _PROFILE
    fplog = fopen("exe.log", "wt");
#endif

    /* �������J�����g�f�B���N�g����1��̃f�B���N�g������{�� */
    if (!dict)
    {
	pmigemo = migemo_open("./dict/" MIGEMODICT_NAME);
	if (!word && !mode_quiet)
	{
	    fprintf(fplog, "migemo_open(%s)=%p\n",
		    "./dict/" MIGEMODICT_NAME, pmigemo);
	}
	if (!pmigemo || !migemo_is_enable(pmigemo))
	{
	    migemo_close(pmigemo); /* NULL��close���Ă����͂Ȃ� */
	    pmigemo = migemo_open("../dict/" MIGEMODICT_NAME);
	    if (!word && !mode_quiet)
	    {
		fprintf(fplog, "migemo_open(%s)=%p\n",
			"../dict/" MIGEMODICT_NAME, pmigemo);
	    }
	}
    }
    else
	pmigemo = migemo_open(dict);

    if (!pmigemo)
	return 1;
    else
    {
	if (mode_vim)
	{
	    migemo_set_operator(pmigemo, MIGEMO_OPINDEX_OR, "\\|");
	    migemo_set_operator(pmigemo, MIGEMO_OPINDEX_NEST_IN, "\\%(");
	    migemo_set_operator(pmigemo, MIGEMO_OPINDEX_NEST_OUT, "\\)");
	    migemo_set_operator(pmigemo, MIGEMO_OPINDEX_NEWLINE, "\\_s*");
	}
#ifndef _PROFILE
	if (word)
	{
	    unsigned char *ans;

	    ans = migemo_query(pmigemo, word);
	    if (ans)
		fprintf(fplog, mode_vim ? "%s" : "%s\n", ans);
	    migemo_release(pmigemo, ans);
	}
	else
	{
	    if (!mode_quiet)
		printf("clock()=%f\n", (float)clock() / CLOCKS_PER_SEC);
	    query_loop(pmigemo, mode_quiet);
	}
#else
	/* �v���t�@�C���p */
	{
	    unsigned char *ans;

	    ans = migemo_query(pmigemo, "a");
	    if (ans)
		fprintf(fplog, "  [%s]\n", ans);
	    migemo_release(pmigemo, ans);

	    ans = migemo_query(pmigemo, "k");
	    if (ans)
		fprintf(fplog, "  [%s]\n", ans);
	    migemo_release(pmigemo, ans);
	}
#endif
	migemo_close(pmigemo);
    }

    if (fplog != stdout)
	fclose(fplog);
    return 0;
}
