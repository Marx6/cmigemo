/* vim:set ts=8 sts=4 sw=4 tw=0: */
/*
 * wordbuf.h -
 *
 * Written By:  Muraoka Taro <koron@tka.att.ne.jp>
 * Last Change: 15-May-2002.
 */
#ifndef WORDBUF_H
#define WORDBUF_H

typedef struct _wordbuf_t wordbuf_t, *wordbuf_p;
struct _wordbuf_t
{
    int len;
    unsigned char* buf;
    int last; /* �i�[���Ă��镶����̒��� */
};

extern int n_wordbuf_open;
extern int n_wordbuf_close;

#define wordbuf_len(w) wordbuf_last(w)
#define WORDBUF_GET(w) ((w)->buf)
#define WORDBUF_LEN(w) ((w)->last)

#ifdef __cplusplus
extern "C" {
#endif

wordbuf_p wordbuf_open();
void wordbuf_close(wordbuf_p p);
void wordbuf_reset(wordbuf_p p);
int wordbuf_last(wordbuf_p p);
int wordbuf_add(wordbuf_p p, unsigned char ch);
int wordbuf_cat(wordbuf_p p, unsigned char* sz);
unsigned char* wordbuf_get(wordbuf_p p);

#ifdef __cplusplus
}
#endif

#endif /* WORDBUF_H */
