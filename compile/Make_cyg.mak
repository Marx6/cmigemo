# vim:set ts=8 sts=8 sw=8 tw=0:
#
# Cygwin�pMakefile
#
# Last Change:	14-May-2002.
# Base Idea:	AIDA Shinra
# Written By:	MURAOKA Taro <koron@tka.att.ne.jp>

##############################################################################
# ���ɉ����Ă���3�ϐ���ύX����
#
libmigemo_LIB = libmigemo.dll.a
libmigemo_DSO = cygmigemo1.dll
EXEEXT = .exe

include compile/unix.mak

##############################################################################
# ���ɉ����ă��C�u�����\�z�@��ύX����
#
$(libmigemo_LIB): $(libmigemo_DSO)
$(libmigemo_DSO): $(libmigemo_OBJ) migemo.def
	dllwrap --dllname $(libmigemo_DSO) --implib $(libmigemo_LIB) --def migemo.def $(libmigemo_OBJ)
