# vim:set ts=8 sts=8 sw=8 tw=0:
#
# Cygwin�pMakefile
#
# Last Change:	19-Oct-2003.
# Base Idea:	AIDA Shinra
# Maintainer:	MURAOKA Taro <koron@tka.att.ne.jp>

##############################################################################
# ���ɉ����Ă��̕ϐ���ύX����
#
libmigemo_LIB = $(outdir)libmigemo.dll.a
libmigemo_DSO = $(outdir)cygmigemo1.dll
EXEEXT = .exe
CFLAGS_MIGEMO =
LDFLAGS_MIGEMO =

include config.mk
include compile/unix.mak
include src/depend.mak
include compile/clean_unix.mak
include compile/clean.mak

##############################################################################
# ���ɉ����ă��C�u�����\�z�@��ύX����
#
$(libmigemo_LIB): $(libmigemo_DSO)
$(libmigemo_DSO): $(libmigemo_OBJ) $(srcdir)migemo.def
	dllwrap --dllname $(libmigemo_DSO) --implib $(libmigemo_LIB) --def $(srcdir)migemo.def $(libmigemo_OBJ)

install-lib: $(libmigemo_DSO) $(libmigemo_LIB)
	$(INSTALL_DATA)		$(libmigemo_LIB) $(libdir)
	$(INSTALL_PROGRAM)	$(libmigemo_DSO) $(bindir)

uninstall-lib:
	$(RM) $(bindir)/$(libmigemo_DSO)
	$(RM) $(libdir)/$(libmigemo_LIB)

dictionary:
	cd dict && $(MAKE) cyg
