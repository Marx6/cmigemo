# vim:set ts=8 sts=8 sw=8 tw=0:
#
# Clean up �A�[�L�e�N�`����ˑ�
#
# Last Change:	16-May-2002.
# Written By:	MURAOKA Taro <koron@tka.att.ne.jp>

clean: clean-arch
	-$(RM) *.o
	-$(RM) *.obj
	-$(RMDIR) Release
	-$(RMDIR) Debug

distclean: clean distclean-arch
	-$(RM) *.a
	-$(RM) *.dll
	-$(RM) *.dylib
	-$(RM) *.exe
	-$(RM) cmigemo
	-$(RM) libmigemo.*.dylib
	-$(RM) libmigemo.so*
	-$(RM) migemo.opt
	-$(RM) migemo.ncb
	-$(RM) tags
