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
libmigemo_LIB = libmigemo.1.dylib
libmigemo_DSO = libmigemo.dylib
EXEEXT =

include compile/unix.mak

##############################################################################
# ���ɉ����ă��C�u�����\�z�@��ύX����
#
$(libmigemo_LIB): $(libmigemo_DSO)
$(libmigemo_DSO): $(libmigemo_OBJ)
	$(CC) -dynamiclib -install_name $@ -o $(libmigemo_LIB) $(libmigemo_OBJ)
	ln -s $(libmigemo_LIB) $@

install-lib: $(libmigemo_DSO)
	$(INSTALL_DATA) $(libmigemo_LIB) $(libdir)
	ln -s $(libdir)/$(libmigemo_LIB) $(libdir)/$(libmigemo_DSO)

uninstall-lib:
	$(RM) $(libdir)/$(libmigemo_DSO)
	$(RM) $(libdir)/$(libmigemo_LIB)
