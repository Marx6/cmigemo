C/Migemo���C�u����������
                                                             since 15-Aug-2001
                                                                   Version 1.1
                                                  Author: MURAOKA Taro (KoRoN)
                                                     Last Change: 14-May-2002.

����
  C/Migemo��Migemo(Ruby/Migemo)��C����Ŏ����������̂ł��BC/Migemo���C�u������
  ���p����\�t�g�E�F�A�́u���[�}���̂܂ܓ��{���(�C���N�������^����)��������v
  �@�\�������Ƃ��\�ɂȂ�܂��BC����Ŏ����������Ƃɂ��A�{��Ruby/Migemo��
  ��ׁAC����ŏ����ꂽ�����̃\�t�g�E�F�A����̗��p���e�ՂɂȂ邱�ƁA�y��(����
  ��)���s���x�̌��オ���҂ł��܂��B

  �܂�C/Migemo�𗘗p���邽�߂ɂ͕ʓr�����t�@�C��(dict/migemo-dict)���쐬������
  �͓��肷��K�v������܂��B�����ł܂������̃[�����玫�����쐬���邱�Ƃ��ł���
  �����ARuby/Migemo��migemo-dict�𗬗p������ASKK�̎�������R���o�[�g���邱��
  ���\�ł��B�ڂ����͉��L�́u�����ɂ��āv�̃Z�N�V�������Q�Ƃ��Ă��������B

  Ruby/Migemo�͍��� �N���񂪍l�Ă����u���[�}�����͂���{�ꌟ���̂��߂̐��K�\��
  �ɕϊ�����v�c�[���ł��BEmacs��Ń��[�}���̂܂ܓ��{����C���N�������^������
  ���邽�߂ɁARuby��Emacs LISP�Ŏ�������Ă��܂����B

  - �{��Ruby/Migemo�T�C�g (Migemo�Ɋւ���ڍ׏��)
      http://migemo.namazu.org/
  - C/Migemo����E�z�z�T�C�g (C/Migemo�̏��)
      http://www.kaoriya.net/

�t�@�C���\��
  C/Migemo�̃p�b�P�[�W�͌��݂̂Ƃ��뎟�̂悤�ȃt�@�C���E�f�B���N�g������\����
  ��Ă��܂��B
    Makefile            :cygwin make + VC6�ɂ��e�X�g�p���C�N�t�@�C��
    Make_*.mak          :�e�v���b�g�z�[���p�̃��C�N�t�@�C��
    migemo.dsw          :VC6�̃��[�N�X�y�[�X
    *.dsp               :VC6�p�v���W�F�N�g(migemo.dsw����Q�Ƃ����)
    migemo.h            :���C�u�����𗘗p����̂��߂̃C���N���[�h�t�@�C��
    main.c              :���C�u�����𗘗p����T���v���v���O����
    *.c                 :���C�u�����̃\�[�X
    *.h                 :���C�u�����̃\�[�X�p�C���N���[�h�t�@�C��
    dict/               :�����u����
    tool/               :�e��c�[��
    testdata/           :�J���e�X�g�ɗ��p�����f�[�^�̒u����

�R���p�C�����@
  ���݂�Windows���VC++6��p����DLL���R���p�C�����邽�߂̃t�@�C�������p�ӂ���
  �Ă��܂���BDLL���쐬����ɂ�migemo.dsw��Visual Studio�ŊJ���Adll_migemo�v��
  �W�F�N�g���r���h����Ί����ł��B

  �R���p�C�����̂�cygwin��Linux��ŉ\�Ȃ��Ƃ͊m�F���Ă���܂��B�\�[�X�̂���
  �f�B���N�g����:
    $ gcc *.c -o migemo
  �Ƃ��Ă݂Ă��������B�T���v���A�v���P�[�V����migemo���R���p�C������܂��B
  Windows�ȊO�̃v���b�g�z�[��(UNIX��Linux)�Ŏg�p����ꍇ�ɂ́A�����t�@�C���̃G
  ���R�[�h���R���o�[�g����K�v��������\��������܂��B�����ɂ��Ă̏ڍׂ�
  �u�����ɂ��āv�̃Z�N�V�������Q�Ƃ��Ă��������Bautotools�ɂ�郉�C�u������
  ���ăR���p�C�����邽�߂�:
    $ ./configure && make && make install
  �͏������Ă��܂���B�ǂȂ�������Ă��������܂���?�B

���p����
  ����C/Migemo���C�u�����͈ȉ��̏����ɓ��ӂł�����̂ݗ��p��������܂��B

  1. �\�[�X�R�[�h�̒��쌠�͕������܂���B
  2. ���̃��C�u�������g�p�������߂ɐ��������Q�ɂ��Ă͈�ؕ⏞���܂���B
  3. �ڍׂ͌��܂��Ă��܂��񂪁AC/Migemo�̃\�[�X�R�[�h�͕��L����R�X�g�ŗ��p��
     ����悤��LGPL��BSD�A�������͂����ɏ����郉�C�Z���X��K�p���܂��B

  ���Ɏ����̃��C�Z���X�����ɃO���[�Ȃ̂Ŋm��ł��Ă��Ȃ��̂ł��B

����E�A����
  C/Migemo�Ɋւ��鎿��E�v�]���͑���(���L�A�h���X�Q��)�܂ŘA�����Ă��������B�\
  �t�g�E�F�A����C/Migemo���g�p�������ꍇ�̖₢���킹���󂯕t���܂��B

�ӎ�
  Migemo�𔭈Ă���Ruby/Migemo���쐬����AC/Migemo�ɂ��Ă̑��k��ML�Őe�؂ɓ�
  ���Ă������������� �N����ɁB


�����ɂ���
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
  �܂��B�܂��ɋ�����4�t�@�C����Windows�Ŏg���ꍇ�ɂ�cp932�ɁAUNIX��Linux��
  �g���ꍇ�ɂ�euc-jp�ɕϊ�����K�v������̂ł��B�ϊ��ɂ�nkf��qkc���g���Ɨǂ���
  ���傤�B

  - Migemo DLL�z�z�y�[�W (cp932��migemo-dict������\)
      http://www.kaoriya.net/~koron/
  - Ruby/Migemo (euc-jp��migemo-dict������\)
      http://migemo.namazu.org/
  - SKK Openlab (�ŐV��SKK-JISYO.L������\)
      http://openlab.ring.gr.jp/skk/index-j.html

�^���t�@�����X
  C/Migemo�ŗ��p�����^�ɂ��ďq�ׂ�B

- migemo*;
    Migemo�I�u�W�F�N�g�Bmigemo_open()�ō쐬����Amigemo_close()�Ŕj�������B

- int (*MIGEMO_PROC_CHAR2INT)(unsigned char*, unsigned int*);
    ������(unsigned char*)���R�[�h(unsigned int)�ɕϊ�����v���V�[�W���^�B
    Shift-JIS��EUC-JP�ȊO�̃G���R�[�h�̕�����������Ƃ��A�������͓��ꕶ���̏�
    �����s�������Ƃ��ɒ�`����B�߂�l�͕�����̂������������o�C�g���ŁA0���
    ���΃f�t�H���g�̃v���V�[�W�������s�����B���̎d�g�݂ŕK�v�ȕ��������ɏ�
    �����{�����Ƃ��o����B

- int (*MIGEMO_PROC_INT2CHAR)(unsigned int, unsigned char*);
    �R�[�h(unsigned int)�𕶎���(unsigned char*)�ɕϊ�����v���V�[�W���^�B
    Shift-JIS��EUC-JP�ȊO�̃G���R�[�h������������Ƃ��A�������͓��ꕶ���̏���
    ���s�������Ƃ��ɒ�`����B�߂�l�͏o�͂��ꂽ������̃o�C�g���ŁA0��Ԃ���
    �f�t�H���g�̃v���V�[�W�������s�����B���̎d�g�݂ŕK�v�ȕ��������ɏ������{
    �����Ƃ��o����B

�֐����t�@�����X
  C/Migemo���C�u�����Œ񋟂����API���ȉ��ŉ������B���ۂ̎g�p��̓A�[�J�C�u
  �Ɋ܂܂��main.c���Q�Ƃ̂��ƁB

- migemo* migemo_open(char* dict);
    Migemo�I�u�W�F�N�g���쐬����B�쐬�ɐ�������ƃI�u�W�F�N�g���߂�l�Ƃ��ĕ�
    ��A���s�����NULL���Ԃ�Bdict�Ŏw�肵���t�@�C����migemo-dict�����Ƃ��ăI
    �u�W�F�N�g�쐬���ɓǂݍ��܂��B�����Ɠ����f�B���N�g����:
      1. roma2hira.dat  (���[�}�����������ϊ��\)
      2. hira2kata.dat  (���������J�^�J�i�ϊ��\)
      3. han2zen.dat    (���p���S�p�ϊ��\)
    �Ƃ������O�̃t�@�C�������݂���΁A���݂������̂������ǂݍ��܂��Bdict��
    NULL���w�肵���ꍇ�ɂ́A�������܂߂Ă����Ȃ�t�@�C�����ǂݍ��܂�Ȃ��B�t�@
    �C���̓I�u�W�F�N�g�쐬��ɂ�migemo_load()�֐����g�p���邱�ƂŒǉ��ǂݍ���
    ���ł���B

- void migemo_close(migemo* object);
    Migemo�I�u�W�F�N�g��j�����A�g�p���Ă������\�[�X���������B

- unsigned char* migemo_query(migemo* object, unsigned char* query);
    query�ŗ^����ꂽ������(���[�}��)����{�ꌟ���̂��߂̐��K�\���֕ϊ�����B
    �߂�l�͕ϊ����ꂽ���ʂ̕�����(���K�\��)�ŁA�g�p���migemo_release()�֐���
    �n�����Ƃŉ�����Ȃ���΂Ȃ�Ȃ��B

- void migemo_release(migemo* object, unsigned char* string);
    �g���I�����migemo_query()�֐��œ���ꂽ���K�\�����������B

- int migemo_load(migemo* obj, int dict_id, char* dict_file);
    Migemo�I�u�W�F�N�g�Ɏ����A�܂��̓f�[�^�t�@�C����ǉ��ǂݍ��݂���B
    dict_file�͓ǂݍ��ރt�@�C�������w�肷��Bdict_id�͓ǂݍ��ގ����E�f�[�^�̎�
    �ނ��w�肷����̂ňȉ��̂����ǂꂩ����w�肷��:

      MIGEMO_DICTID_MIGEMO      mikgemo-dict����
      MIGEMO_DICTID_ROMA2HIRA   ���[�}�����������ϊ��\
      MIGEMO_DICTID_HIRA2KATA   ���������J�^�J�i�ϊ��\
      MIGEMO_DICTID_HAN2ZEN     ���p���S�p�ϊ��\

    �߂�l�͎��ۂɓǂݍ��񂾎�ނ������A��L�̑��ɓǂݍ��݂Ɏ��s�������Ƃ�����
    ���̉����Ԃ邱�Ƃ�����B
      MIGEMO_DICTID_INVALID     

- int migemo_is_enable(migemo* obj);
    Migemo�I�u�W�F�N�g��migemo_dict���ǂݍ��߂Ă��邩���`�F�b�N����B�L����
    migemo_dict��ǂݍ��߂ē����ɕϊ��e�[�u�����\�z�ł��Ă����0�ȊO(TRUE)���A
    �\�z�ł��Ă��Ȃ��Ƃ��ɂ�0(FALSE)��Ԃ��B

- int migemo_set_operator(migemo* object, int index, unsigned char* op);
    Migemo�I�u�W�F�N�g���������鐳�K�\���Ɏg�p���郁�^����(���Z�q)���w�肷��B
    index�łǂ̃��^���������w�肵�Aop�Œu��������Bindex�ɂ͈ȉ��̒l���w��\
    �ł���:

      MIGEMO_OPINDEX_OR
        �_���a�B�f�t�H���g�� "|" �Bvim�ŗ��p����ۂ� "\|" �B
      MIGEMO_OPINDEX_NEST_IN
        �O���[�s���O�ɗp����J�����ʁB�f�t�H���g�� "(" �Bvim�ł̓��W�X�^\1�`\9
        �ɋL�������Ȃ��悤�ɂ��邽�߂� "\%(" ��p����BPerl�ł����l�̂��Ƃ��
        �_�ނȂ�� "(?:" ���g�p�\�B
      MIGEMO_OPINDEX_NEST_OUT
        �O���[�s���O�̏I����\�������ʁB�f�t�H���g�ł� ")" �Bvim�ł� "\)" �B
      MIGEMO_OPINDEX_SELECT_IN
        �I���̊J�n��\���J���p���ʁB�f�t�H���g�ł� "[" �B
      MIGEMO_OPINDEX_SELECT_OUT
        �I���̏I����\�����p���ʁB�f�t�H���g�ł� "]" �B
      MIGEMO_OPINDEX_NEWLINE
        �e�����̊Ԃɑ}�������u0�ȏ�̋󔒂������͉��s�Ƀ}�b�`����v�p�^�[
        ���B�f�t�H���g�ł� "" �ł���ݒ肳��Ȃ��Bvim�ł� "\_s*" ���w�肷��B

    �f�t�H���g�̃��^�����͓��ɒf�肪�Ȃ�����Perl�̂���Ɠ����Ӗ��ł���B�ݒ��
    ��������Ɩ߂�l��0�ƂȂ�A���s�����0�ȊO�ɂȂ�B

- const unsigned char* migemo_get_operator(migemo* object, int index);
    Migemo�I�u�W�F�N�g���������鐳�K�\���Ɏg�p���Ă��郁�^����(���Z�q)���擾��
    ��Bindex�ɂ��Ă�migemo_set_operator()�֐����Q�ƁB�߂�l�ɂ�index�̎w��
    ����������΃��^�������i�[����������ւ̃|�C���^���A�s���ł����NULL����
    ��B

- void migemo_setproc_char2int(migemo* object, MIGEMO_PROC_CHAR2INT proc);
    Migemo�I�u�W�F�N�g�ɃR�[�h�ϊ��p�̃v���V�[�W����ݒ肷��B�v���V�[�W���ɂ�
    ���Ă̏ڍׂ́u�^���t�@�����X�v�Z�N�V������MIGEMO_PROC_CHAR2INT���Q�ƁB

- void migemo_setproc_int2char(migemo* object, MIGEMO_PROC_INT2CHAR proc);
    Migemo�I�u�W�F�N�g�ɃR�[�h�ϊ��p�̃v���V�[�W����ݒ肷��B�v���V�[�W���ɂ�
    ���Ă̏ڍׂ́u�^���t�@�����X�v�Z�N�V������MIGEMO_PROC_INT2CHAR���Q�ƁB

�X�V�ӏ�
  �� 14-May-2002 (1.1a-beta)
    �h�L�������g�C��
    cache���œK�����č����� (mnode_load())
    wordbuf_add()���œK�����č����� (wordbuf.c)
    migemo�����ǂݍ��ݎ��s�����o�ł��Ȃ��Ȃ��Ă����o�O�C��
    mnode���܂Ƃ߂Ċm�ۂ��邱�Ƃō����� (mnode.c��)
    �����𒷂��~���Ƀ\�[�g (tools/lensort.pl)
    �N����1������2�������� (mnode.c)
  �� 21-Aug-2001
    main.c��gets()��fgets()�ɕύX

-------------------------------------------------------------------------------
                  �����鎖�ւ̋����ӎu�������Ɏ����ƈقȂ鐶���������ԐS�ƂȂ�
                                    MURAOKA Taro/�������Y<koron@tka.att.ne.jp>

 vi:set ts=8 sts=2 sw=2 tw=78 et ft=memo:
