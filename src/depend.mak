# vim:set ts=8 sts=8 sw=8 tw=0:
#
# �\���t�@�C���ƈˑ��֌W
#
# Last Change:	18-Oct-2003.
# Written By:	MURAOKA Taro <koron@tka.att.ne.jp>

##############################################################################
# �\���t�@�C��
#
SRC = 	$(srcdir)filename.c \
	$(srcdir)migemo.c \
	$(srcdir)mnode.c \
	$(srcdir)romaji.c \
	$(srcdir)rxgen.c \
	$(srcdir)wordbuf.c \
	$(srcdir)wordlist.c

OBJ = 	$(objdir)filename.$(O) \
	$(objdir)migemo.$(O) \
	$(objdir)mnode.$(O) \
	$(objdir)romaji.$(O) \
	$(objdir)rxgen.$(O) \
	$(objdir)wordbuf.$(O) \
	$(objdir)wordlist.$(O)

##############################################################################
# �ˑ��֌W�̐ݒ�
#
$(objdir)filename.$(O): $(srcdir)filename.c \
	$(srcdir)filename.h

$(objdir)main.$(O): $(srcdir)main.c \
	$(srcdir)migemo.h

$(objdir)migemo.$(O): $(srcdir)migemo.c \
	$(srcdir)filename.h \
	$(srcdir)wordbuf.h \
	$(srcdir)wordlist.h \
	$(srcdir)mnode.h \
	$(srcdir)rxgen.h \
	$(srcdir)romaji.h \
	$(srcdir)migemo.h

$(objdir)mnode.$(O): $(srcdir)mnode.c \
	$(srcdir)dbg.h \
	$(srcdir)wordbuf.h \
	$(srcdir)wordlist.h \
	$(srcdir)mnode.h

$(objdir)romaji.$(O): $(srcdir)romaji.c \
	$(srcdir)romaji.h

$(objdir)rxgen.$(O): $(srcdir)rxgen.c \
	$(srcdir)wordbuf.h \
	$(srcdir)rxgen.h

$(objdir)wordbuf.$(O): $(srcdir)wordbuf.c \
	$(srcdir)wordbuf.h

$(objdir)wordlist.$(O): $(srcdir)wordlist.c \
	$(srcdir)wordlist.h

