#include "GameMain.h"
#include "GameSceneMain.h"
#include "Game1Scene.h"
#include "Effect.h"
#include "Bullet.h"
#include "MyUtil.h"


#define SCREEN_WIDTH     (640)    // 画面の横幅
#define SCREEN_HEIGHT    (480)    // 画面の縦幅
#define CHIP_SIZE        (32)     // 一つのチップのサイズ
#define MAP_WIDTH        (30)     // マップの横幅
#define MAP_SCREEN_WIDTH (20)     // 画面上見えるマップの横幅
#define MAP_HEIGHT       (20)     // マップの縦幅

#define G                (0.3F)   // キャラに掛かる重力加速度
#define JUMP_POWER       (9.0F)   // キャラのジャンプ力
#define SPEED            (5.0F)   // キャラの移動スピード
#define CHAR_SIZE        (30)     // プレイヤーのサイズ

//現在使用中のマップデータ
char NowMapData[MAP_HEIGHT][MAP_WIDTH];

// マップデータ CHECK:Charは容量削減の為
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

// マップデータ
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

//敵の仕様Tips
//敵は左右から迫ってくる。

//キャラクターの行動パターン
struct CHARACTER {
	int Hp;
	float WorldX;
	float WorldY;
	int AIPattern;
	float DownSpeed;
	char JumpFlag;
	int DeadFlag;		//0:生きている　1:使用していない
	int EnemyAICount;
};

//プレイヤー宣言
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

//生死フラグ
#define ISALIVE 0
#define ISDEAD 1

//==変数定義==============================================================
float PlX, PlY;            // プレイヤーの座標(中心座標)
float PlDownSp;            // プレイヤーの落下速度
char PlJumpFlag;           // プレイヤーがジャンプ中か、のフラグ

float FeX, FeY;				//妖精の位置
int FeShotCoolTime;			//弾の発射感覚

extern int Input, EdgeInput;      // 入力状態(Input(押しっぱなし)、EdgeInput(1回のみ） 

int MapGapX;
int MapTipXGap;	//マップチップの横移動量(TipSizeを超えたら0に)
int MapTipXScroll;	//マップチップの初期位置からの横移動量

//妖精をプカプカ浮かせるためのカウント変数
int SinTime;

//背景変数
int BackImage;
int BackImage_SizeX, BackImage_SizeY;
float BackImage_PosX, BackImage_PosY;

//スクロール中の動作をエネミーに伝える変数
float scrollMoveX;

//現在のステージ数
int StageNum;

//鍵を持っているかフラグ
int GetKeyFlag;

//中間ポイントフラグ
int GetCheckPointFlag;

enum GAMEMODE {
	GAMEMODE_START = 0,
	GAMEMODE_GAMECLEAR,
	GAMEMODE_GAMEOVER
};
int GameMode;


//==変数定義==============================================================

//色々やるよ初期化処理
void StatusInit();

// マップチップの値を取得する関数
int GetChipParam(float X, float Y);

// キャラクタをマップとの当たり判定を考慮しながら移動する関数
int CharMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, char *JumpFlag);

// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
//                                                3:上辺に当たった  4:下辺に当たった
// 注意：MoveX と MoveY 、どっちか片方が０じゃないとまともに動作しません
int MapHitCheck(float X, float Y, float *MoveX, float *MoveY);

// シーン開始前の初期化を行う
BOOL initGame1Scene(void) {
	//各変数の初期化
	StatusInit();

	//画像データの読み込み
	BackImage = LoadGraph("res/back.jpg", true);
	//背景画像の解像度を取得
	GetGraphSize(BackImage, &BackImage_SizeX, &BackImage_SizeY);
	//背景画像を左下を基準に移動
	BackImage_PosX = 0;
	BackImage_PosY = (float)-BackImage_SizeY + 480;

	//ステージ数
	StageNum = 1;
	GetKeyFlag = 0;
	GameMode = GAMEMODE_START;

	GetCheckPointFlag = 0;

	//マップデータの移動
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j< MAP_WIDTH; j++) {
			NowMapData[i][j] = MapData[i][j];
		}
	}


	return TRUE;
}
//	フレーム処理
void moveGame1Scene() {

	scrollMoveX = 0;

	// プレイヤーの移動処理
	if (GameMode == GAMEMODE_START) {
		{
			float MoveX, ScrollX, MoveY;

			// 移動量の初期化
			MoveX = 0.0F;
			ScrollX = 0.0F;
			MoveY = 0.0F;

			// 左右の移動を見る　左
			if ((Input & PAD_INPUT_LEFT) != 0) {
				//キャラクターが画面端に到達していたらマップを動かす
				if (PlX < CHIP_SIZE * 5 && MapGapX > 0) {

					float DummyX = 0.0F;
					float DMoveX = -SPEED;
					// 左下のチェックと左上のチェックを行い、ブロックが無い場合スクロールを行う
					if (MapHitCheck(PlX - (CHAR_SIZE / 2) + MapGapX, PlY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
						MapHitCheck(PlX - (CHAR_SIZE / 2) + MapGapX, PlY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
						MapGapX -= SPEED;
						scrollMoveX = -SPEED;
						MapTipXScroll = MapGapX / CHIP_SIZE;
						MapTipXGap = MapGapX % CHIP_SIZE;

						BackImage_PosX += SPEED;
					}

				}
				else {	//画面端にいない場合はキャラクターを移動させる
					MoveX -= SPEED;
				}

				//バグ避け
				if (MapTipXScroll < 0) {
					MapGapX = 0;
					MapTipXScroll = 0;
					BackImage_PosX = 0;

					//スクロールした際に、画面外に超えないようにする
					for (int i = 0; i < ENEMY_MAX; i++) {
						if (enemy[i].DeadFlag == ISDEAD) {
							if (enemy[i].WorldX < 0)enemy[i].WorldX = 0;
						}
					}
				}

			}

			// 左右の移動を見る　右
			if ((Input & PAD_INPUT_RIGHT) != 0) {
				if (PlX > CHIP_SIZE * 10 && MapTipXScroll < MAP_WIDTH - MAP_SCREEN_WIDTH) {

					float DummyX = 0.0F;
					float DMoveX = +SPEED;
					// 右下のチェックと右上のチェックを行い、ブロックが無い場合スクロールを行う
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

			// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
			if (PlJumpFlag == FALSE && (EdgeInput & PAD_INPUT_A) != 0)
			{
				PlDownSp = -JUMP_POWER;
				PlJumpFlag = TRUE;
			}

			// 落下処理
			PlDownSp += G;

			// 落下速度を移動量に加える
			MoveY = PlDownSp;

			//攻撃処理
			if ((EdgeInput & PAD_INPUT_B) != 0) {
				//if ((Input & PAD_INPUT_B) != 0) {
				Effect_Add(PlX + CHAR_SIZE, PlY);
			}

			// 移動量に基づいてキャラクタの座標を移動
			CharMove(&PlX, &PlY, &PlDownSp, MoveX, MoveY, CHAR_SIZE, &PlJumpFlag);
		}

		//妖精の位置を更新
		FeX = (int)(PlX - CHAR_SIZE * 0.2F) - 20;
		FeY = (int)(PlY - CHAR_SIZE * 0.2F) - 20 + sin(PI * 2 / 240 * SinTime) * 10;

		//ボタン3で弾を発射する
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

		//とりあえずボタンを押したらエネミー生成
		if ((EdgeInput & PAD_INPUT_C) != 0) {
			//使っていない（死んでいる）エネミーを検索
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (enemy[i].DeadFlag == ISDEAD) {
					//りぼーん！
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
				// エネミーの移動処理
				{
					float MoveX, ScrollX, MoveY;

					// 移動量の初期化
					MoveX = 0.0F - scrollMoveX;
					ScrollX = 0.0F;
					MoveY = 0.0F;

					//エネミーはワールド座標ElX,ElYで指定

					float DummyX = 0.0F;
					float DMoveX = 0;
					switch (enemy[i].AIPattern) {
					case ENEMY_MOVE_LEFT:
						DMoveX = -SPEED;
						// 左右の移動を見る　左
						// 左下のチェックと左上のチェックを行い、ブロックが無い場合スクロールを行う
						if (MapHitCheck(enemy[i].WorldX - (CHAR_SIZE / 2) + MapGapX,
							enemy[i].WorldY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
							MapHitCheck(enemy[i].WorldX - (CHAR_SIZE / 2) + MapGapX,
								enemy[i].WorldY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
							//壁に当たらなかったので進む
							MoveX -= SPEED;
						}
						else {
							//壁にあたったので右に進む事とする
							enemy[i].AIPattern = ENEMY_MOVE_RIGHT;
						}
						break;

						// 左右の移動を見る　右
					case ENEMY_MOVE_RIGHT:
						DMoveX = +SPEED;
						// 右下のチェックと右上のチェックを行い、ブロックが無い場合スクロールを行う
						if (MapHitCheck(enemy[i].WorldX + (CHAR_SIZE / 2) + MapGapX,
							enemy[i].WorldY + (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0 &&
							MapHitCheck(enemy[i].WorldX + (CHAR_SIZE / 2) + MapGapX,
								enemy[i].WorldY - (CHAR_SIZE / 2), &DMoveX, &DummyX) == 0) {
							//壁に当たらなかったので進む
							MoveX += SPEED;
						}
						else {
							//壁にあたったので右に進む事とする
							enemy[i].AIPattern = ENEMY_MOVE_LEFT;
						}
						break;
					}

					// 落下処理
					enemy[i].DownSpeed += G;

					// 落下速度を移動量に加える
					MoveY = enemy[i].DownSpeed;

					// 移動量に基づいてキャラクタの座標を移動
					CharMove(&enemy[i].WorldX, &enemy[i].WorldY,
						&enemy[i].DownSpeed, MoveX, MoveY, CHAR_SIZE, &enemy[i].JumpFlag);
				}
			}
		}
	}
	else {
		//ゲームクリア中にボタンを押したら次のステージへ
		if ((Input & PAD_INPUT_1) != 0) {
			//ステータスを初期化します。
			StatusInit();

			//画像データの読み込み(2ステージ目の画像に切替えるならここで。
			BackImage = LoadGraph("res/back.jpg", true);
			//背景画像の解像度を取得
			GetGraphSize(BackImage, &BackImage_SizeX, &BackImage_SizeY);
			//背景画像を左下を基準に移動
			BackImage_PosX = 0;
			BackImage_PosY = (float)-BackImage_SizeY + 480;

			//ステージ数の更新
			StageNum = 2;
			GetKeyFlag = 0;
			GameMode = GAMEMODE_START;

			//マップを切り替えます
			for (int i = 0; i < MAP_HEIGHT; i++) {
				for (int j = 0; j < MAP_WIDTH; j++) {
					NowMapData[i][j] = MapData2[i][j];
				}
			}

		}

	}//GameMode

}
//	レンダリング処理
void renderGame1Scene(void){

	//背景画像の表示
	DrawGraph(BackImage_PosX, BackImage_PosY, BackImage, true);

	// マップの描画
	{
		int i, j;

		for (i = 0; i < MAP_HEIGHT; i++)
		{
			for (j = 0; j < MAP_WIDTH; j++)
			{
				// １は当たり判定チップを表しているので１のところだけ描画
				if (NowMapData[i][j + MapTipXScroll] == 1)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(255, 255, 255), TRUE);
				}

				//クリアゴール
				if (NowMapData[i][j + MapTipXScroll] == 2)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(255, 0, 0), TRUE);
				}

				//鍵アイテム
				if (NowMapData[i][j + MapTipXScroll] == 3)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 0, 255), TRUE);
				}

				//チェックフラグアイテム
				if (NowMapData[i][j + MapTipXScroll] == 4)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 255, 255), TRUE);
				}

				//扉
				if (NowMapData[i][j + MapTipXScroll] == 10)
				{
					DrawBox(j * CHIP_SIZE - MapTipXGap, i * CHIP_SIZE,
						j * CHIP_SIZE + CHIP_SIZE - MapTipXGap, i * CHIP_SIZE + CHIP_SIZE,
						GetColor(0, 255, 0), TRUE);
				}
			}
		}
	}

	//デバック表示
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%f,%f", PlX, PlY);

	// キャラクタの描画
	DrawBox((int)(PlX - CHAR_SIZE * 0.5F), (int)(PlY - CHAR_SIZE * 0.5F),
		(int)(PlX + CHAR_SIZE * 0.5F) + 1, (int)(PlY + CHAR_SIZE * 0.5F),
		GetColor(255, 0, 0), TRUE);

	// エネミーの描画
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].DeadFlag == ISALIVE) {
			DrawBox((int)(enemy[i].WorldX - CHAR_SIZE * 0.5F), (int)(enemy[i].WorldY - CHAR_SIZE * 0.5F),
				(int)(enemy[i].WorldX + CHAR_SIZE * 0.5F) + 1, (int)(enemy[i].WorldY + CHAR_SIZE * 0.5F),
				GetColor(0, 0, 255), TRUE);
		}
	}

	//鍵を持っている時は鍵を表示する
	if (GetKeyFlag == 1) {
		// 縦にゆらゆらと動くようにする。
		if (SinTime++ > 360) SinTime = 0;
		DrawBox((int)FeX, (float)FeY, (int)FeX + 10, (float)FeY + 10, GetColor(255, 255, 0), TRUE);
	}

	//エフェクトの表示
	Effect_Render();
	Bullet_Render();


	//ゲームクリア表示
	if (GameMode == GAMEMODE_GAMECLEAR) {
		DrawString(50, 200 ,"GameClear!!!!",GetColor(255, 255, 255));
		DrawString(50, 250, "Button 1 to Next Stage", GetColor(255, 255, 255));
	}

	//デバック用表示
	//DrawFormatString(30, 50, GetColor(255, 255, 255),"%03.1f,%03.1f,%d",ElX,ElY,EnemyAIMode);

}

//	シーン終了時の後処理
void releaseGame1Scene(void){

	Effect_Relese();
	Bullet_Relese();

	DeleteGraph(BackImage);

}

// 当り判定コールバック 　　　ここでは要素を削除しないこと！！
void  Game1SceneCollideCallback( int nSrc, int nTarget, int nCollideID ){


}

//初期化処理
void StatusInit() {
	PlX = PlY = 0;            // プレイヤーの座標(中心座標)
	PlDownSp = 0;            // プレイヤーの落下速度
	PlJumpFlag = 0;           // プレイヤーがジャンプ中か、のフラグ

	FeX = FeY = 0;				//妖精の位置
	FeShotCoolTime = 0;			//弾の発射感覚
	MapGapX = 0;
	MapTipXGap = 0;
	MapTipXScroll = 0;

	FeShotCoolTime = 0;

	//プレイヤーステータスの初期化
	player[0].Hp = 10;
	player[0].WorldX = 0;
	player[0].WorldY = 0;
	player[0].DownSpeed = 0;
	player[0].JumpFlag = 0;
	player[0].DeadFlag = 0;

	//敵ステータスの初期化
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

	//ステージ数
	StageNum = 1;
	GetKeyFlag = 0;
	GameMode = GAMEMODE_START;

}

// キャラクタをマップとの当たり判定を考慮しながら移動する
int CharMove(float *X, float *Y, float *DownSP,
	float MoveX, float MoveY, float Size, char *JumpFlag)
{
	float Dummy = 0.0F;
	float hsize;

	// キャラクタの左上、右上、左下、右下部分が当たり判定のある
	// マップに衝突しているか調べ、衝突していたら補正する

	// 半分のサイズを算出
	hsize = Size * 0.5F;

	// 先ず上下移動成分だけでチェック
	{
		// 左下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (MapHitCheck(*X - hsize + MapGapX, *Y + hsize, &Dummy, &MoveY) == 3) *DownSP = 0.0F;

		// 右下のチェック、もしブロックの上辺に着いていたら落下を止める
		if (MapHitCheck(*X + hsize + MapGapX, *Y + hsize, &Dummy, &MoveY) == 3) *DownSP = 0.0F;

		// 左上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (MapHitCheck(*X - hsize + MapGapX, *Y - hsize, &Dummy, &MoveY) == 4) *DownSP *= -1.0F;

		// 右上のチェック、もしブロックの下辺に当たっていたら落下させる
		if (MapHitCheck(*X + hsize + MapGapX, *Y - hsize, &Dummy, &MoveY) == 4) *DownSP *= -1.0F;

		// 上下移動成分を加算
		//CHECK:小数点以下を切り捨てる
		int _y = *Y + MoveY;
		*Y = _y;
		//*Y += MoveY;
	}

	// 後に左右移動成分だけでチェック
	{
		// 左下のチェック
		MapHitCheck(*X - hsize + MapGapX, *Y + hsize, &MoveX, &Dummy);

		// 右下のチェック
		MapHitCheck(*X + hsize + MapGapX, *Y + hsize, &MoveX, &Dummy);

		// 左上のチェック
		MapHitCheck(*X - hsize + MapGapX, *Y - hsize, &MoveX, &Dummy);

		// 右上のチェック
		MapHitCheck(*X + hsize + MapGapX, *Y - hsize, &MoveX, &Dummy);

		// 左右移動成分を加算
		*X += MoveX;
	}

	// 接地判定
	{
		// キャラクタの左下と右下の下に地面があるか調べる
		if (GetChipParam(*X - Size * 0.5F + MapGapX, *Y + Size * 0.5F + 1.0F) == 0 &&
			GetChipParam(*X + Size * 0.5F + MapGapX, *Y + Size * 0.5F + 1.0F) == 0)
		{
			// 足場が無かったらジャンプ中にする
			*JumpFlag = TRUE;
		}
		else
		{
			// 足場が在ったら接地中にする
			*JumpFlag = FALSE;
		}
	}

	// 終了
	return 0;
}


// マップとの当たり判定( 戻り値 0:当たらなかった  1:左辺に当たった  2:右辺に当たった
//                                                3:上辺に当たった  4:下辺に当たった
// 注意：MoveX と MoveY 、どっちか片方が０じゃないとまともに動作しません
int MapHitCheck(float X, float Y,
	float *MoveX, float *MoveY)
{
	float afX, afY;

	// 移動量を足す
	afX = X + *MoveX;
	afY = Y + *MoveY;

	//先に特殊ブロックの処理を行う
		//2番に触れたらゲームクリア扱い。
	if (GetChipParam(afX, afY) == 2) {
		GameMode = GAMEMODE_GAMECLEAR;
	}

	//3番は鍵
	if (GetChipParam(afX, afY) == 3) {
		// 整数値へ変換
		int _x = (int)afX / CHIP_SIZE;
		int _y = (int)afY / CHIP_SIZE;
		NowMapData[_y][_x] = 0;		//鍵をとったので、マップから消す
		GetKeyFlag = 1;	//鍵を持っているフラグ
		return 0;	//当たったので処理を返す
	}

	//4番チェックフラッグ
	if (GetChipParam(afX, afY) == 4) {
		// 整数値へ変換
		int _x = (int)afX / CHIP_SIZE;
		int _y = (int)afY / CHIP_SIZE;
		NowMapData[_y][_x] = 0;		//鍵をとったので、マップから消す
		GetKeyFlag = 1;	//鍵を持っているフラグ
		return 0;	//当たったので処理を返す
	}

	//扉
	if (GetChipParam(afX, afY) == 10) {
		//鍵を持っているかチェック。
		if (GetKeyFlag == 1) {
			//扉のブロックを削除
			NowMapData[12][28] = 0;
			NowMapData[13][28] = 0;
		}
	}

	//特殊ブロックと当たっていなければ、通常の当たり判定を行う
	// TODO:通常ブロックと、通れないブロックの全チェックを行う
	if (GetChipParam(afX, afY) == 1 || GetChipParam(afX, afY) == 10)
	{
		float blx, bty, brx, bby;

		// 当たっていたら壁から離す処理を行う

		// ブロックの上下左右の座標を算出
		blx = (float)((int)afX / CHIP_SIZE) * CHIP_SIZE;        // 左辺の X 座標
		brx = (float)((int)afX / CHIP_SIZE + 1) * CHIP_SIZE;    // 右辺の X 座標

		bty = (float)((int)afY / CHIP_SIZE) * CHIP_SIZE;        // 上辺の Y 座標
		bby = (float)((int)afY / CHIP_SIZE + 1) * CHIP_SIZE;    // 下辺の Y 座標

																// 上辺に当たっていた場合
		if (*MoveY > 0.0F)
		{
			// 移動量を補正する
			*MoveY = bty - Y - 1.0F;

			// 上辺に当たったと返す
			return 3;
		}

		// 下辺に当たっていた場合
		if (*MoveY < 0.0F)
		{
			// 移動量を補正する
			*MoveY = bby - Y + 1.0F;

			// 下辺に当たったと返す
			return 4;
		}

		// 左辺に当たっていた場合
		if (*MoveX > 0.0F)
		{
			// 移動量を補正する
			*MoveX = blx - X - 1.0F;

			// 左辺に当たったと返す
			return 1;
		}

		// 右辺に当たっていた場合
		if (*MoveX < 0.0F)
		{
			// 移動量を補正する
			*MoveX = brx - X + 1.0F;

			// 右辺に当たったと返す
			return 2;
		}

		// ここに来たら適当な値を返す
		return 4;
	}

	// どこにも当たらなかったと返す
	return 0;
}

// マップチップの値を取得する関数
int GetChipParam(float X, float Y)
{
	int x, y;

	// 整数値へ変換
	x = (int)X / CHIP_SIZE;
	y = (int)Y / CHIP_SIZE;

	// マップからはみ出ていたら 0 を返す
	if (x >= MAP_WIDTH || y >= MAP_HEIGHT || x < 0 || y < 0) return 0;

	// 指定の座標に該当するマップの情報を返す
	return NowMapData[y][x];
}