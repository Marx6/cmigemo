C/Migemo���C�u����������
                                                             since 15-Aug-2001
                                                                   Version 1.0
                                                          Muraoka Taro (KoRoN)
                                                     Last Change: 16-Aug-2001.

���� {{{1
  C/Migemo��Migemo(��������Ruby/Migemo)��C����Ŏ����������̂ł��BC/Migemo���C
  �u�����𗘗p����\�t�g�E�F�A�́u���[�}���̂܂ܓ��{���(�C���N�������^����)��
  ������v�@�\�������Ƃ��\�ɂȂ�܂��BC����Ŏ����������Ƃɂ��A�{��
  Ruby/Migemo�ɔ�ׁAC����ŏ����ꂽ�����̃\�t�g�E�F�A����̗��p���e�ՂɂȂ邱
  �ƁA�y�ю��s���x�̌��オ���҂ł��܂��B

  �܂�C/Migemo�𗘗p���邽�߂ɂ͕ʓr�����t�@�C��(dict/migemo-dict)���쐬�E����
  ����K�v������܂��B�����ł܂������̃[�����玫�����쐬���邱�Ƃ��ł��܂����A
  Ruby/Migemo��migemo-dict�𗬗p������ASKK�̎�������R���o�[�g���邱�Ƃ��\
  �ł��B�ڂ����͉��L�́u�����ɂ��āv�̃Z�N�V�������Q�Ƃ��Ă��������B

  Migemo�Ƃ͍��� �N���񂪍l�Ă����u���[�}�����͂���{�ꌟ���̂��߂̐��K�\����
  �ϊ�����v�c�[���ł��B���Ƃ��Ƃ�Emacs��Ń��[�}���̂܂ܓ��{����C���N������
  �^���������邽�߂ɁARuby��Emacs LISP�Ŏ�������Ă��܂����B

  - �{��Ruby/Migemo�T�C�g (Migemo�Ɋւ���ڍ׏��)
      http://migemo.namazu.org/
  - C/Migemo��҂̃T�C�g (C/Migemo�̏��)
      http://ixeris.bios.ics.saitama-u.ac.jp/~koron/

�t�@�C���\�� {{{1
  C/Migemo�̃p�b�P�[�W�͌��݂̂Ƃ��뎟�̂悤�ȃt�@�C���E�f�B���N�g������\����
  ��Ă��܂��B
    Makefile            :cygwin make + VC6�ɂ��e�X�g�p���C�N�t�@�C��
    migemo.dsw          :VC6�̃��[�N�X�y�[�X
    *.dsp               :VC6�p�v���W�F�N�g(migemo.dsw����Q�Ƃ����)
    migemo.h            :���C�u�����𗘗p����̂��߂̃C���N���[�h�t�@�C��
    main.c              :���C�u�����𗘗p����T���v���v���O����
    *.c                 :���C�u�����̃\�[�X
    *.h                 :���C�u�����̃\�[�X�p�C���N���[�h�t�@�C��
    dict                :�����u����
    tool                :�e��c�[��
    testdata            :�J���e�X�g�ɗ��p�����f�[�^�̒u����

�R���p�C�����@ {{{1
  ���݂�Windows���VC++6��p����DLL���R���p�C�����邽�߂̃t�@�C�������p�ӂ���
  �Ă��܂���BDLL���쐬����ɂ�migemo.dsw��Visual Studio�ŊJ���Adll_migemo�v��
  �W�F�N�g���r���h����Ί����ł��B

  �R���p�C�����̂�cygwin��Linux��ŉ\�Ȃ��Ƃ͊m�F���Ă���܂��B�\�[�X�̂���
  �f�B���N�g����:
    $ gcc *.c -o migemo
  �Ƃ��Ă݂Ă��������B�T���v���A�v���P�[�V����migemo���R���p�C������܂��B
  Windows�ȊO�̃v���b�g�z�[��(UNIX��Linux)�Ŏg�p����ꍇ�ɂ́A�����t�@�C���̃G
  ���R�[�h���R���o�[�g����K�v��������\��������܂��B�ڂ����́u�����ɂ�
  �āv�̃Z�N�V�������Q�Ƃ��Ă��������B�Ȃ�autotools�ɂ�郉�C�u�����Ƃ��ăR��
  �p�C�����邽�߂�:
    $ ./configure && make && make install
  �͏������Ă��܂���B�ǂȂ�������Ă��������܂���?�B

���p���� {{{1
  ����C/Migemo���C�u�����͈ȉ��̏����ɓ��ӂł�����̂ݗ��p��������܂��B

  1. �\�[�X�R�[�h�̒��쌠�͕������܂���B
  2. ���̃��C�u�������g�p�������߂ɐ��������Q�ɂ��Ă͈�ؕ⏞���܂���B
  3. �܂��ڍׂ������܂��Ă��܂��񂪁AC/Migemo�̃\�[�X�R�[�h�͕��L����R�X�g��
     ���p�ł���悤��LGPL��BSD�A�������͂���ɏ����郉�C�Z���X�̓K�p���s�Ȃ���
     ���B

  ���Ɏ����̃��C�Z���X�����ɃO���[�Ȃ̂Ŋm��ł��Ă��Ȃ��̂ł��B

����E�A���� {{{1
  C/Migemo�Ɋւ��鎿��E�v�]���͑���(���L�A�h���X�Q��)�܂ŘA�����Ă��������B�\
  �t�g�E�F�A����C/Migemo���g�p�������ꍇ�̖₢���킹���󂯕t���܂��B

�ӎ� {{{1
  Migemo�𔭈Ă���Ruby/Migemo���쐬����AC/Migemo�ɂ��Ă̑��k��ML�Őe�؂ɓ�
  ���Ă������������� �N����ɁB


�����ɂ��� {{{1
  C/Migemo�ł̓��[�}������{��֕ϊ�����̂Ɏ����t�@�C��dict/migemo-dict��K�v
  �Ƃ��܂��B�t�@�C��dict/migemo-dict�͂��̃A�[�J�C�u�Ɋ܂܂�Ă��܂��񂪁A
    1. vim�����ɃR���p�C���ς݂�Migemo DLL���玝���Ă��邩
    2. Ruby/Migemo�̂��̂𗬗p���邩
    3. SKK�̎����t�@�C������R���o�[�g����
  ���Ƃ��ł��܂��B

  SKK����R���o�[�g���邽�߂̃c�[����Perl�ŏ����ꂽtool/conv.pl�Ƃ��Ď��^����
  �Ă��܂��BSKK-JISYO.L�����LURL����擾���Ď��̂悤�ɃR���o�[�g���܂��B
    $ perl tool/conv.pl < SKK-JISYO.L > dict/migemo-dict
  tool/strip.pl�͎����t�@�C������d���P����폜���邽�߂̃c�[���ł��B

  C/Migemo�ł�
    1. dict/migemo-dict�ȊO�ɂ��A
    2. ���[�}���𕽉����ɕϊ����邽�߂̃t�@�C��(dict/roma2hira.dat)��A
    3. ��������Љ����ɕϊ����邽�߂̃t�@�C��(dict/hira2kata.dat)��A
    4. ���p������S�p�����ɕϊ����邽�߂̃t�@�C��(dict/han2zen.dat)
  ���g�p���Ă��܂��B�����̑S�Ẵt�@�C���͒P�Ƀf�[�^�e�[�u���Ƃ��ċ@�\���Ă�
  �邾���łȂ��A�V�X�e���̃G���R�[�h(�����R�[�h)�̈Ⴂ���z������������S���Ă�
  �܂��B�܂��ɋ�����4�t�@�C����Windows�Ŏg���ꍇ�ɂ�sjis�ɁAUNIX��Linux��
  �g���ꍇ�ɂ�euc-jp�ɕϊ�����K�v������̂ł��B�ϊ��ɂ�nkf��qkc���g���Ɨǂ���
  ���傤�B

  - Migemo DLL�z�z�y�[�W (sjis��migemo-dict������\)
      http://ixeris.bios.ics.saitama-u.ac.jp/~koron/
  - Ruby/Migemo (euc-jp��migemo-dict������\)
      http://migemo.namazu.org/
  - SKK Openlab (�ŐV�̃I���W�i����SKK-JISYO.L������\)
      http://openlab.ring.gr.jp/skk/index-j.html

�֐����t�@�����X {{{1
  C/Migemo���C�u�����Œ񋟂����API���ȉ��ŉ������B���ۂ̎g�p��̓A�[�J�C�u
  �Ɋ܂܂��main.c���Q�Ƃ̂��ƁB

  migemo* migemo_open(char* dict); {{{2
    Migemo�I�u�W�F�N�g���쐬����B�쐬�ɐ�������ƃI�u�W�F�N�g���߂�l�Ƃ��ĕ�
    ��A���s�����NULL���Ԃ�Bdict�Ŏw�肵���t�@�C����migemo-dict�����Ƃ��ăI
    �u�W�F�N�g�쐬���ɓǂݍ��܂��B�����Ɠ����f�B���N�g����:
      1. roma2hira.dat
      2. hira2kata.dat
      3. han2zen.dat
    �Ƃ������O�̃t�@�C�������݂���΁A���݂������̂������ǂݍ��܂��Bdict��
    NULL���w�肵���ꍇ�ɂ́A�������܂߂Ă����Ȃ�t�@�C�����ǂݍ��܂�Ȃ��B�t�@
    �C���̓I�u�W�F�N�g�쐬��ɂ�migemo_load()�֐����g�p���邱�ƂŒǉ��ǂݍ���
    ���ł���B

  void migemo_close(migemo* object); {{{2
    Migemo�I�u�W�F�N�g��j�����A�g�p���Ă������\�[�X���������B

  unsigned char* migemo_query(migemo* object, unsigned char* query); {{{2
    query�ŗ^����ꂽ������(���[�}��)����{�ꌟ���̂��߂̐��K�\���֕ϊ�����B
    �߂�l�͕ϊ����ꂽ���ʂ̕�����(���K�\��)�ŁA�g�p���migemo_release()�֐���
    �n�����Ƃŉ�����Ȃ���΂Ȃ�Ȃ��B

  void migemo_release(migemo* object, unsigned char* string); {{{2
    �g���I�����migemo_query()�֐��œ���ꂽ���K�\�����������B

  int migemo_load(migemo* obj, int dict_id, char* dict_file); {{{2
    Migemo�I�u�W�F�N�g�Ɏ����A�܂��̓f�[�^�t�@�C����ǉ��ǂݍ��݂���B
    dict_file�͓ǂݍ��ރt�@�C�������w�肷��Bdict_id�͓ǂݍ��ގ����E�f�[�^�̎�
    �ނ��w�肷����̂ňȉ��̂����ǂꂩ����w�肷��B
      MIGEMO_DICTID_MIGEMO      mikgemo-dict����
      MIGEMO_DICTID_ROMA2HIRA   ���[�}�����������ϊ��\
      MIGEMO_DICTID_HIRA2KATA   ���������J�^�J�i�ϊ��\
      MIGEMO_DICTID_HAN2ZEN     ���p���S�p�ϊ��\
    �߂�l�͎��ۂɓǂݍ��񂾎�ނ������A��L�̑��ɓǂݍ��݂Ɏ��s�������Ƃ�����
    ���̉����Ԃ邱�Ƃ�����B
      MIGEMO_DICTID_INVALID     

  int migemo_is_enable(migemo* obj); {{{2

  int migemo_set_operator(migemo* object, int index, unsigned char* op); {{{2
      MIGEMO_OPINDEX_OR
      MIGEMO_OPINDEX_NEST_IN
      MIGEMO_OPINDEX_NEST_OUT
      MIGEMO_OPINDEX_SELECT_IN
      MIGEMO_OPINDEX_SELECT_OUT
      MIGEMO_OPINDEX_NEWLINE

  const unsigned char* migemo_get_operator(migemo* object, int index); {{{2
  void migemo_setproc_char2int(migemo* object, MIGEMO_PROC_CHAR2INT proc); {{{2
  void migemo_setproc_int2char(migemo* object, MIGEMO_PROC_INT2CHAR proc); {{{2

{{{1
-------------------------------------------------------------------------------
                  �����鎖�ւ̋����ӎu�������Ɏ����ƈقȂ鐶���������ԐS�ƂȂ�
                                    Muraoka Taro/�������Y<koron@tka.att.ne.jp>
 vi:set ts=8 sts=2 sw=2 tw=78 et fdm=marker:
