#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game1Scene.h"
#include "Effect.h"
#include "Bullet.h"
#include "MyUtil.h"


#define SCREEN_WIDTH     (640)    // ��ʂ̉���
#define SCREEN_HEIGHT    (480)    // ��ʂ̏c��
#define CHIP_SIZE        (32)     // ��̃`�b�v�̃T�C�Y
#define MAP_WIDTH        (30)     // �}�b�v�̉���
#define MAP_SCREEN_WIDTH (20)     // ��ʏ㌩����}�b�v�̉���
#define MAP_HEIGHT       (20)     // �}�b�v�̏c��

#define G                (0.3F)   // �L�����Ɋ|����d�͉����x
#define JUMP_POWER       (9.0F)   // �L�����̃W�����v��
#define SPEED            (5.0F)   // �L�����̈ړ��X�s�[�h
#define CHAR_SIZE        (30)     // �v���C���[�̃T�C�Y

//���ݎg�p���̃}�b�v�f�[�^
char NowMapData[MAP_HEIGHT][MAP_WIDTH];

// �}�b�v�f�[�^ CHECK:Char�͗e�ʍ팸�̈�
char MapData[MAP_HEIGHT][MAP_WIDTH] =
{
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,3,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,1,0,1,

	1,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,1,

	1,0,0,0,0, 1,1,1,1,1, 0,0,0,0,1, 1,0,0,0,0, 0,0,0,0,1, 1,0,0,0,1,
	1,0,0,0,0, 1,1,1,1,1, 0,0,0,1,1, 1,0,0,0,0, 0,0,0,1,1, 1,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 1,0,0,0,0, 0,0,0,1,1, 1,0,0,10,2,
	1,0,0,0,0, 0,0,0,0,0, 4,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,2,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
};

char MapData2[MAP_HEIGHT][MAP_WIDTH] =
{
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,2,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,10,2,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
};

// �}�b�v�f�[�^
char EnemyData[MAP_HEIGHT][MAP_WIDTH] =
{
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	0,0,0,1,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0,
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
};

//�G�̎d�lTips
//�G�͍��E���甗���Ă���B

//�L�����N�^�[�̍s���p�^�[��
struct CHARACTER {
	int Hp;
	float WorldX;
	float WorldY;
	int AIPattern;
	float DownSpeed;
	char JumpFlag;
	int DeadFlag;		//0:�����Ă���@1:�g�p���Ă��Ȃ�
	int EnemyAICount;
};

//�v���C���[�錾
#define ENEMY_MAX 5
CHARACTER player[1];
CHARACTER enemy[ENEMY_MAX];

enum EnemyPattern{
	ENEMY_MOVE_LEFT = 0,
	ENEMY_MOVE_RIGHT,
	ENEMY_MOVE_UP,
	ENEMY_MOVE_DOWN,
	ENEMY_ATTACK
};

//�����t���O
#define ISALIVE 0
#define ISDEAD 1

//==�ϐ���`==============================================================
float PlX, PlY;            // �v���C���[�̍��W(���S���W)
float PlDownSp;            // �v���C���[�̗������x
char PlJumpFlag;           // �v���C���[���W�����v�����A�̃t���O

float FeX, FeY;				//�d���̈ʒu
int FeShotCoolTime;			//�e�̔��ˊ��o

extern int Input, EdgeInput;      // ���͏��(Input(�������ςȂ�)�AEdgeInput(1��̂݁j 

int MapGapX;
int MapTipXGap;	//�}�b�v�`�b�v�̉��ړ���(TipSize�𒴂�����0��)
int MapTipXScroll;	//�}�b�v�`�b�v�̏����ʒu����̉��ړ���

//�d�����v�J�v�J�������邽�߂̃J�E���g�ϐ�
int SinTime;

//�w�i�ϐ�
int BackImage;
int BackImage_SizeX, BackImage_SizeY;
float BackImage_PosX, BackImage_PosY;

//�X�N���[�����̓�����G�l�~�[�ɓ`����ϐ�
float scrollMoveX;

//���݂̃X�e�[�W��
int StageNum;

//���������Ă��邩�t���O
int GetKeyFlag;

//���ԃ|�C���g�t���O
int GetCheckPointFlag;

enum GAMEMODE {
	GAMEMODE_START = 0,
	GAMEMODE_GAMECLEAR,
	GAMEMODE_GAMEOVER
};
int GameMode;


//==�ϐ���`==============================================================

//�F�X���揉��������
void StatusInit();

// �}�b�v�`�b�v�̒l���擾����֐�
int GetChipParam(float X, float Y);

// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����֐�
int CharMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, char *JumpFlag);

// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
//                                                3:��ӂɓ�������  4:���ӂɓ�������
// ���ӁFMoveX �� MoveY �A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���
int MapHitCheck(float X, float Y, float *MoveX, float *MoveY);

// �V�[���J�n�O�̏��������s��
BOOL initGame1Scene(void) {
	//�e�ϐ��̏�����
	StatusInit();

	//�摜�f�[�^�̓ǂݍ���
	BackImage = LoadGraph("res/back.jpg", true);
	//�w�i�摜�̉𑜓x���擾
	GetGraphSize(BackImage, &BackImage_SizeX, &BackImage_SizeY);
	//�w�i�摜����������Ɉړ�
	BackImage_PosX = 0;
	BackImage_PosY = (float)-BackImage_SizeY + 480;

	//�X�e�[�W��
	StageNum = 1;
	GetKeyFlag = 0;
	GameMode = GAMEMODE_START;

	GetCheckPointFlag = 0;

	//�}�b�v�f�[�^�̈ړ�
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j< MAP_WIDTH; j++) {
			NowMapData[i][j] = MapData[i][j];
		}
	}


	return TRUE;
}
//	�t���[������
void moveGame1Scene() {

	scrollMoveX = 0;

	// �v���C���[�̈ړ�����
	if (GameMode == GAMEMODE_START) {
		{
			float MoveX, ScrollX, MoveY;

			// �ړ��ʂ̏�����
			MoveX = 0.0F;
			ScrollX = 0.0F;
			MoveY = 0.0F;

			// ���E�̈ړ�������@��
			if ((Input & PAD_INPUT_LEFT) != 0) {
				//�L�����N�^�[����ʒ[�ɓ��B���Ă�����}�b�v�𓮂���
				if (PlX < CHIP_SIZE * 5 && MapGapX > 0) {

					float DummyX = 0.0F;
					float DMoveX = -SPEED;
					// �����̃`�F�b�N�ƍ���̃`�F�b�N���s���A�u���b�N�������ꍇ�X�N���[�����s��
					if (MapHitCheck(PlX - (CHAR_SIZE / 2) + MapGapX, PlY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
						MapHitCheck(PlX - (CHAR_SIZE / 2) + MapGapX, PlY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
						MapGapX -= SPEED;
						scrollMoveX = -SPEED;
						MapTipXScroll = MapGapX / CHIP_SIZE;
						MapTipXGap = MapGapX % CHIP_SIZE;

						BackImage_PosX += SPEED;
					}

				}
				else {	//��ʒ[�ɂ��Ȃ��ꍇ�̓L�����N�^�[���ړ�������
					MoveX -= SPEED;
				}

				//�o�O����
				if (MapTipXScroll < 0) {
					MapGapX = 0;
					MapTipXScroll = 0;
					BackImage_PosX = 0;

					//�X�N���[�������ۂɁA��ʊO�ɒ����Ȃ��悤�ɂ���
					for (int i = 0; i < ENEMY_MAX; i++) {
						if (enemy[i].DeadFlag == ISDEAD) {
							if (enemy[i].WorldX < 0)enemy[i].WorldX = 0;
						}
					}
				}

			}

			// ���E�̈ړ�������@�E
			if ((Input & PAD_INPUT_RIGHT) != 0) {
				if (PlX > CHIP_SIZE * 10 && MapTipXScroll < MAP_WIDTH - MAP_SCREEN_WIDTH) {

					float DummyX = 0.0F;
					float DMoveX = +SPEED;
					// �E���̃`�F�b�N�ƉE��̃`�F�b�N���s���A�u���b�N�������ꍇ�X�N���[�����s��
					if (MapHitCheck(PlX + (CHAR_SIZE / 2) + MapGapX, PlY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
						MapHitCheck(PlX + (CHAR_SIZE / 2) + MapGapX, PlY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
						MapGapX += SPEED;
						scrollMoveX = +SPEED;
						MapTipXScroll = MapGapX / CHIP_SIZE;
						MapTipXGap = MapGapX % CHIP_SIZE;

						BackImage_PosX -= SPEED;
					}
				}
				else {
					MoveX += SPEED;
				}
			}

			// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
			if (PlJumpFlag == FALSE && (EdgeInput & PAD_INPUT_A) != 0)
			{
				PlDownSp = -JUMP_POWER;
				PlJumpFlag = TRUE;
			}

			// ��������
			PlDownSp += G;

			// �������x���ړ��ʂɉ�����
			MoveY = PlDownSp;

			//�U������
			if ((EdgeInput & PAD_INPUT_B) != 0) {
				//if ((Input & PAD_INPUT_B) != 0) {
				Effect_Add(PlX + CHAR_SIZE, PlY);
			}

			// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
			CharMove(&PlX, &PlY, &PlDownSp, MoveX, MoveY, CHAR_SIZE, &PlJumpFlag);
		}

		//�d���̈ʒu���X�V
		FeX = (int)(PlX - CHAR_SIZE * 0.2F) - 20;
		FeY = (int)(PlY - CHAR_SIZE * 0.2F) - 20 + sin(PI * 2 / 240 * SinTime) * 10;

		//�{�^��3�Œe�𔭎˂���
		if ((Input & PAD_INPUT_C) != 0) {
			if (FeShotCoolTime < 0) {
				Bullet_Add((int)FeX, (int)FeY);
				FeShotCoolTime = 10;
			}

			FeShotCoolTime--;
		}
		if ((Input & PAD_INPUT_C) == 0) {
			FeShotCoolTime = 0;
		}

		Effect_Update();
		Bullet_Update();

		//�Ƃ肠�����{�^������������G�l�~�[����
		if ((EdgeInput & PAD_INPUT_C) != 0) {
			//�g���Ă��Ȃ��i����ł���j�G�l�~�[������
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (enemy[i].DeadFlag == ISDEAD) {
					//��ځ[��I
					enemy[i].Hp = 10;
					enemy[i].WorldX = 0;
					enemy[i].WorldY = 0;
					enemy[i].DownSpeed = 0;
					enemy[i].JumpFlag = 0;
					enemy[i].DeadFlag = ISALIVE;
					enemy[i].AIPattern = ENEMY_MOVE_RIGHT;

					break;
				}
			}
		}

		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].DeadFlag == ISALIVE) {
				// �G�l�~�[�̈ړ�����
				{
					float MoveX, ScrollX, MoveY;

					// �ړ��ʂ̏�����
					MoveX = 0.0F - scrollMoveX;
					ScrollX = 0.0F;
					MoveY = 0.0F;

					//�G�l�~�[�̓��[���h���WElX,ElY�Ŏw��

					float DummyX = 0.0F;
					float DMoveX = 0;
					switch (enemy[i].AIPattern) {
					case ENEMY_MOVE_LEFT:
						DMoveX = -SPEED;
						// ���E�̈ړ�������@��
						// �����̃`�F�b�N�ƍ���̃`�F�b�N���s���A�u���b�N�������ꍇ�X�N���[�����s��
						if (MapHitCheck(enemy[i].WorldX - (CHAR_SIZE / 2) + MapGapX,
							enemy[i].WorldY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
							MapHitCheck(enemy[i].WorldX - (CHAR_SIZE / 2) + MapGapX,
								enemy[i].WorldY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
							//�ǂɓ�����Ȃ������̂Ői��
							MoveX -= SPEED;
						}
						else {
							//�ǂɂ��������̂ŉE�ɐi�ގ��Ƃ���
							enemy[i].AIPattern = ENEMY_MOVE_RIGHT;
						}
						break;

						// ���E�̈ړ�������@�E
					case ENEMY_MOVE_RIGHT:
						DMoveX = +SPEED;
						// �E���̃`�F�b�N�ƉE��̃`�F�b�N���s���A�u���b�N�������ꍇ�X�N���[�����s��
						if (MapHitCheck(enemy[i].WorldX + (CHAR_SIZE / 2) + MapGapX,
							enemy[i].WorldY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
							MapHitCheck(enemy[i].WorldX + (CHAR_SIZE / 2) + MapGapX,
								enemy[i].WorldY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
							//�ǂɓ�����Ȃ������̂Ői��
							MoveX += SPEED;
						}
						else {
							//�ǂɂ��������̂ŉE�ɐi�ގ��Ƃ���
							enemy[i].AIPattern = ENEMY_MOVE_LEFT;
						}
						break;
					}

					// ��������
					enemy[i].DownSpeed += G;

					// �������x���ړ��ʂɉ�����
					MoveY = enemy[i].DownSpeed;

					// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
					CharMove(&enemy[i].WorldX, &enemy[i].WorldY,
						&enemy[i].DownSpeed, MoveX, MoveY, CHAR_SIZE, &enemy[i].JumpFlag);
				}
			}
		}
	}
	else {
		//�Q�[���N���A���Ƀ{�^�����������玟�̃X�e�[�W��
		if ((Input & PAD_INPUT_1) != 0) {
			//�X�e�[�^�X�����������܂��B
			StatusInit();

			//�摜�f�[�^�̓ǂݍ���(2�X�e�[�W�ڂ̉摜�ɐؑւ���Ȃ炱���ŁB
			BackImage = LoadGraph("res/back.jpg", true);
			//�w�i�摜�̉𑜓x���擾
			GetGraphSize(BackImage, &BackImage_SizeX, &BackImage_SizeY);
			//�w�i�摜����������Ɉړ�
			BackImage_PosX = 0;
			BackImage_PosY = (float)-BackImage_SizeY + 480;

			//�X�e�[�W���̍X�V
			StageNum = 2;
			GetKeyFlag = 0;
			GameMode = GAMEMODE_START;

			//�}�b�v��؂�ւ��܂�
			for (int i = 0; i < MAP_HEIGHT; i++) {
				for (int j = 0; j < MAP_WIDTH; j++) {
					NowMapData[i][j] = MapData2[i][j];
				}
			}

		}

	}//GameMode

}
//	�����_�����O����
void renderGame1Scene(void){

	//�w�i�摜�̕\��
	DrawGraph(BackImage_PosX, BackImage_PosY, BackImage, true);

	// �}�b�v�̕`��
	{
		int i, j;

		for (i = 0; i < MAP_HEIGHT; i++)
		{
			for (j = 0; j < MAP_WIDTH; j++)
			{
				// �P�͓����蔻��`�b�v��\���Ă���̂łP�̂Ƃ��낾���`��
				if (NowMapData[i][j + MapTipXScroll] == 1)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(255, 255, 255), TRUE);
				}

				//�N���A�S�[��
				if (NowMapData[i][j + MapTipXScroll] == 2)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(255, 0, 0), TRUE);
				}

				//���A�C�e��
				if (NowMapData[i][j + MapTipXScroll] == 3)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 0, 255), TRUE);
				}

				//�`�F�b�N�t���O�A�C�e��
				if (NowMapData[i][j + MapTipXScroll] == 4)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 255, 255), TRUE);
				}

				//��
				if (NowMapData[i][j + MapTipXScroll] == 10)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 255, 0), TRUE);
				}
			}
		}
	}

	//�f�o�b�N�\��
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f,%f", PlX, PlY);

	// �L�����N�^�̕`��
	DrawBox((int)(PlX - CHAR_SIZE * 0.5F), (int)(PlY - CHAR_SIZE * 0.5F),
		(int)(PlX + CHAR_SIZE * 0.5F) + 1, (int)(PlY + CHAR_SIZE * 0.5F),
		GetColor(255, 0, 0), TRUE);

	// �G�l�~�[�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].DeadFlag == ISALIVE) {
			DrawBox((int)(enemy[i].WorldX - CHAR_SIZE * 0.5F), (int)(enemy[i].WorldY - CHAR_SIZE * 0.5F),
				(int)(enemy[i].WorldX + CHAR_SIZE * 0.5F) + 1, (int)(enemy[i].WorldY + CHAR_SIZE * 0.5F),
				GetColor(0, 0, 255), TRUE);
		}
	}

	//���������Ă��鎞�͌���\������
	if (GetKeyFlag == 1) {
		// �c�ɂ����Ɠ����悤�ɂ���B
		if (SinTime++ > 360) SinTime = 0;
		DrawBox((int)FeX, (float)FeY, (int)FeX + 10, (float)FeY + 10, GetColor(255, 255, 0), TRUE);
	}

	//�G�t�F�N�g�̕\��
	Effect_Render();
	Bullet_Render();


	//�Q�[���N���A�\��
	if (GameMode == GAMEMODE_GAMECLEAR) {
		DrawString(50, 200 ,"GameClear!!!!",GetColor(255, 255, 255));
		DrawString(50, 250, "Button 1 to Next Stage", GetColor(255, 255, 255));
	}

	//�f�o�b�N�p�\��
	//DrawFormatString(30, 50, GetColor(255, 255, 255),"%03.1f,%03.1f,%d",ElX,ElY,EnemyAIMode);

}

//	�V�[���I�����̌㏈��
void releaseGame1Scene(void){

	Effect_Relese();
	Bullet_Relese();

	DeleteGraph(BackImage);

}

// ���蔻��R�[���o�b�N �@�@�@�����ł͗v�f���폜���Ȃ����ƁI�I
void  Game1SceneCollideCallback( int nSrc, int nTarget, int nCollideID ){


}

//����������
void StatusInit() {
	PlX = PlY = 0;            // �v���C���[�̍��W(���S���W)
	PlDownSp = 0;            // �v���C���[�̗������x
	PlJumpFlag = 0;           // �v���C���[���W�����v�����A�̃t���O

	FeX = FeY = 0;				//�d���̈ʒu
	FeShotCoolTime = 0;			//�e�̔��ˊ��o
	MapGapX = 0;
	MapTipXGap = 0;
	MapTipXScroll = 0;

	FeShotCoolTime = 0;

	//�v���C���[�X�e�[�^�X�̏�����
	player[0].Hp = 10;
	player[0].WorldX = 0;
	player[0].WorldY = 0;
	player[0].DownSpeed = 0;
	player[0].JumpFlag = 0;
	player[0].DeadFlag = 0;

	//�G�X�e�[�^�X�̏�����
	for (int i = 0; i < ENEMY_MAX; i++) {
		enemy[i].Hp = 10;
		enemy[i].WorldX = 0;
		enemy[i].WorldY = 0;
		enemy[i].DownSpeed = 0;
		enemy[i].JumpFlag = 0;
		enemy[i].DeadFlag = ISDEAD;
		enemy[i].AIPattern = ENEMY_MOVE_RIGHT;
	}

	Effect_Init();
	Bullet_Init();

	//�X�e�[�W��
	StageNum = 1;
	GetKeyFlag = 0;
	GameMode = GAMEMODE_START;

}

// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
int CharMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, char *JumpFlag)
{
	float Dummy = 0.0F;
	float hsize;

	// �L�����N�^�̍���A�E��A�����A�E�������������蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

	// �����̃T�C�Y���Z�o
	hsize = Size * 0.5F;

	// �悸�㉺�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (MapHitCheck(*X - hsize + MapGapX, *Y + hsize, &Dummy, &MoveY) == 3) *DownSP = 0.0F;

		// �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
		if (MapHitCheck(*X + hsize + MapGapX, *Y + hsize, &Dummy, &MoveY) == 3) *DownSP = 0.0F;

		// ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (MapHitCheck(*X - hsize + MapGapX, *Y - hsize, &Dummy, &MoveY) == 4) *DownSP *= -1.0F;

		// �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
		if (MapHitCheck(*X + hsize + MapGapX, *Y - hsize, &Dummy, &MoveY) == 4) *DownSP *= -1.0F;

		// �㉺�ړ����������Z
		//CHECK:�����_�ȉ���؂�̂Ă�
		int _y = *Y + MoveY;
		*Y = _y;
		//*Y += MoveY;
	}

	// ��ɍ��E�ړ����������Ń`�F�b�N
	{
		// �����̃`�F�b�N
		MapHitCheck(*X - hsize + MapGapX, *Y + hsize, &MoveX, &Dummy);

		// �E���̃`�F�b�N
		MapHitCheck(*X + hsize + MapGapX, *Y + hsize, &MoveX, &Dummy);

		// ����̃`�F�b�N
		MapHitCheck(*X - hsize + MapGapX, *Y - hsize, &MoveX, &Dummy);

		// �E��̃`�F�b�N
		MapHitCheck(*X + hsize + MapGapX, *Y - hsize, &MoveX, &Dummy);

		// ���E�ړ����������Z
		*X += MoveX;
	}

	// �ڒn����
	{
		// �L�����N�^�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
		if (GetChipParam(*X - Size * 0.5F + MapGapX, *Y + Size * 0.5F + 1.0F) == 0 &&
			GetChipParam(*X + Size * 0.5F + MapGapX, *Y + Size * 0.5F + 1.0F) == 0)
		{
			// ���ꂪ����������W�����v���ɂ���
			*JumpFlag = TRUE;
		}
		else
		{
			// ���ꂪ�݂�����ڒn���ɂ���
			*JumpFlag = FALSE;
		}
	}

	// �I��
	return 0;
}


// �}�b�v�Ƃ̓����蔻��( �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ�������
//                                                3:��ӂɓ�������  4:���ӂɓ�������
// ���ӁFMoveX �� MoveY �A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���
int MapHitCheck(float X, float Y,
	float *MoveX, float *MoveY)
{
	float afX, afY;

	// �ړ��ʂ𑫂�
	afX = X + *MoveX;
	afY = Y + *MoveY;

	//��ɓ���u���b�N�̏������s��
		//2�ԂɐG�ꂽ��Q�[���N���A�����B
	if (GetChipParam(afX, afY) == 2) {
		GameMode = GAMEMODE_GAMECLEAR;
	}

	//3�Ԃ͌�
	if (GetChipParam(afX, afY) == 3) {
		// �����l�֕ϊ�
		int _x = (int)afX / CHIP_SIZE;
		int _y = (int)afY / CHIP_SIZE;
		NowMapData[_y][_x] = 0;		//�����Ƃ����̂ŁA�}�b�v�������
		GetKeyFlag = 1;	//���������Ă���t���O
		return 0;	//���������̂ŏ�����Ԃ�
	}

	//4�ԃ`�F�b�N�t���b�O
	if (GetChipParam(afX, afY) == 4) {
		// �����l�֕ϊ�
		int _x = (int)afX / CHIP_SIZE;
		int _y = (int)afY / CHIP_SIZE;
		NowMapData[_y][_x] = 0;		//�����Ƃ����̂ŁA�}�b�v�������
		GetKeyFlag = 1;	//���������Ă���t���O
		return 0;	//���������̂ŏ�����Ԃ�
	}

	//��
	if (GetChipParam(afX, afY) == 10) {
		//���������Ă��邩�`�F�b�N�B
		if (GetKeyFlag == 1) {
			//���̃u���b�N���폜
			NowMapData[12][28] = 0;
			NowMapData[13][28] = 0;
		}
	}

	//����u���b�N�Ɠ������Ă��Ȃ���΁A�ʏ�̓����蔻����s��
	// TODO:�ʏ�u���b�N�ƁA�ʂ�Ȃ��u���b�N�̑S�`�F�b�N���s��
	if (GetChipParam(afX, afY) == 1 || GetChipParam(afX, afY) == 10)
	{
		float blx, bty, brx, bby;

		// �������Ă�����ǂ��痣���������s��

		// �u���b�N�̏㉺���E�̍��W���Z�o
		blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // ���ӂ� X ���W
		brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // �E�ӂ� X ���W

		bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // ��ӂ� Y ���W
		bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // ���ӂ� Y ���W

																// ��ӂɓ������Ă����ꍇ
		if (*MoveY > 0.0F)
		{
			// �ړ��ʂ�␳����
			*MoveY = bty - Y - 1.0F;

			// ��ӂɓ��������ƕԂ�
			return 3;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*MoveY < 0.0F)
		{
			// �ړ��ʂ�␳����
			*MoveY = bby - Y + 1.0F;

			// ���ӂɓ��������ƕԂ�
			return 4;
		}

		// ���ӂɓ������Ă����ꍇ
		if (*MoveX > 0.0F)
		{
			// �ړ��ʂ�␳����
			*MoveX = blx - X - 1.0F;

			// ���ӂɓ��������ƕԂ�
			return 1;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (*MoveX < 0.0F)
		{
			// �ړ��ʂ�␳����
			*MoveX = brx - X + 1.0F;

			// �E�ӂɓ��������ƕԂ�
			return 2;
		}

		// �����ɗ�����K���Ȓl��Ԃ�
		return 4;
	}

	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return 0;
}

// �}�b�v�`�b�v�̒l���擾����֐�
int GetChipParam(float X, float Y)
{
	int x, y;

	// �����l�֕ϊ�
	x = (int)X / CHIP_SIZE;
	y = (int)Y / CHIP_SIZE;

	// �}�b�v����͂ݏo�Ă����� 0 ��Ԃ�
	if (x >= MAP_WIDTH || y >= MAP_HEIGHT || x < 0 || y < 0) return 0;

	// �w��̍��W�ɊY������}�b�v�̏���Ԃ�
	return NowMapData[y][x];
}