# vim:set ts=8 sts=8 sw=8 tw=0:
#
# Clean up �A�[�L�e�N�`���ˑ� (DOS/Windows)
#
# Last Change:	17-May-2002.
# Written By:	MURAOKA Taro <koron@tka.att.ne.jp>

RM = del /F /Q
RMDIR = rd /S /Q
# ���s��\�̂��Ƃɂ͔��p�X�y�[�X���K�v��"\ "
DICT_DIR = dict\ 

# BC5�ł͋�̃`�����N�̓G���[�ɂȂ�̂�"\t@"���K�v
clean-arch:
	@

distclean-arch:
	@
