# vim:set ts=8 sts=8 sw=8 tw=0:
#
# �f�t�H���g�R���t�B�M�����[�V�����t�@�C��
#
# Last Change:	15-May-2002.
# Base Idea:	AIDA Shinra
# Written By:	MURAOKA Taro <koron@tka.att.ne.jp>

##############################################################################
# �C���X�g�[���f�B���N�g���̐ݒ�
#
prefix		= /usr/local
bindir		= $(prefix)/bin
libdir		= $(prefix)/lib
incdir		= $(prefix)/include
# �x��: $(dictdir)��$(docdir)�̓A���C���X�g�[�����s���Ƀf�B���N�g�����Ə���
# ����܂��B
dictdir		= $(prefix)/share/migemo
docdir		= $(prefix)/doc/migemo

##############################################################################
# �R�}���h�ݒ�
#
RM		= rm -f
CP		= cp
MKDIR		= mkdir -p
RMDIR		= rm -rf
CTAGS		= ctags
HTTP		= curl -O
PERL		= perl
BUNZIP2		= bzip2 -d
FILTER_CP932	= qkc -q -u -s
FILTER_EUCJP	= qkc -q -u -e
INSTALL		= /usr/bin/install -c
INSTALL_PROGRAM	= $(INSTALL) -m 755
INSTALL_DATA	= $(INSTALL) -m 644
