#include "GameMain.h"
#include "GameSceneMain.h"
#include "Bullet.h"



//エフェクトの画像
#define Bullet_NUM 100
struct BULLET_STATUS {
	int isDead;		//生死フラグ
	int img_x;		//X位置
	int img_y;		//Y位置
	int img_angle;	//角度（軌跡のゆらぎ
	int img_no;
	int BulletNo;
	int LifeTime;
	int BulletTimeWait;
	int LightBulletFlag;		//光るエフェクトかどうか
	int LightBulletTime;		//光度
};
BULLET_STATUS BulletStatus[Bullet_NUM];
#define Bullet_IMG_NUM 9
int Bullet_img_rld[Bullet_IMG_NUM];
int Bullet_img_rlu[Bullet_IMG_NUM];
int Bullet_img_lrd[Bullet_IMG_NUM];
int Bullet_img_lru[Bullet_IMG_NUM];
int Bullet_img_down[Bullet_IMG_NUM];
int Bullet_img_up[Bullet_IMG_NUM];

#define Bullet_Size 120


void Bullet_Init() {

	LoadDivGraph("res/btlBullet01.png", 9, 9, 1, 120, 120, Bullet_img_rld);
	LoadDivGraph("res/btlBullet02.png", 9, 9, 1, 120, 120, Bullet_img_rlu);
	LoadDivGraph("res/btlBullet03.png", 9, 9, 1, 120, 120, Bullet_img_lrd);
	LoadDivGraph("res/btlBullet04.png", 9, 9, 1, 120, 120, Bullet_img_lru);
	LoadDivGraph("res/btlBullet05.png", 9, 9, 1, 120, 180, Bullet_img_down);
	LoadDivGraph("res/btlBullet06.png", 9, 9, 1, 120, 180, Bullet_img_up);

	//構造体配列の初期化
	for (int i = 0; i < Bullet_NUM; i++) {
		BulletStatus[i].isDead = 0;		//使っていない
		BulletStatus[i].img_x = 0;
		BulletStatus[i].img_y = 0;
		BulletStatus[i].img_angle = 0;
		BulletStatus[i].img_no = 0;		//画像種類
		BulletStatus[i].BulletNo = 0;
		BulletStatus[i].LifeTime = 0;	//表示時間
		BulletStatus[i].BulletTimeWait = 0;	//表示時間
		BulletStatus[i].LightBulletFlag = 0;	//光エフェクトフラグ
		BulletStatus[i].LightBulletTime = 0;	//光エフェクトフラグ
	}

}

void Bullet_Add(int _x, int _y) {
	//構造体配列の初期化
	for (int i = 0; i < Bullet_NUM; i++) {
		if (BulletStatus[i].isDead == 0) {
			BulletStatus[i].isDead = 1;		//使用中
			BulletStatus[i].img_x = _x;
			BulletStatus[i].img_y = _y;
			BulletStatus[i].img_angle = (rand() % 60) + 90;
			BulletStatus[i].img_no = 0;		//画像種類
											//BulletStatus[i].BulletNo = rand() % 6;	//エフェクトの種類
			BulletStatus[i].BulletNo = 0;	//エフェクトの種類
			BulletStatus[i].LifeTime = 0;	//生存時間
			BulletStatus[i].BulletTimeWait = Bullet_IMG_NUM - 1;	//表示時間
			BulletStatus[i].LightBulletFlag = 0;	//光エフェクトフラグ
			BulletStatus[i].LightBulletTime = 255;	//光度
			break;
		}
	}

}

void Bullet_Update() {


	//構造体配列の初期化
	for (int i = 0; i < Bullet_NUM; i++) {
		if (BulletStatus[i].isDead == 1) {
			// アニメーションカウントの計算
			// カウントが終了した場合は殺す
			if (BulletStatus[i].LifeTime++ >= BulletStatus[i].BulletTimeWait) BulletStatus[i].LifeTime = 0;

			BulletStatus[i].img_x += 10;

			if (BulletStatus[i].img_x > 640)  BulletStatus[i].isDead = 0;
		//	BulletStatus[i].LightBulletTime -= 25;//明るさを少なくする

		}
	}


}

void Bullet_Render() {
	//　画像の表示
	for (int i = 0; i < Bullet_NUM; i++) {
		if (BulletStatus[i].isDead == 1) {

			//エフェクトが光エフェクトならブレンドモードを適応する
			if (BulletStatus[i].LightBulletFlag == 1)
				SetDrawBlendMode(DX_BLENDMODE_ADD, BulletStatus[i].LightBulletTime);


			switch (BulletStatus[i].BulletNo) {
			case 0:
				//DrawRotaGraphF(BulletStatus[i].img_x, BulletStatus[i].img_y, 1, BulletStatus[i].img_angle, Bullet_img_rld[BulletStatus[i].LifeTime], true);
				//DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_rld[BulletStatus[i].LifeTime], true);
				DrawBox(BulletStatus[i].img_x, BulletStatus[i].img_y,
					BulletStatus[i].img_x + 10, BulletStatus[i].img_y + 10,
					GetColor(255, 255, 0), TRUE);

				break;
				//TODO:以下要らない？
			case 1:
				DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_rlu[BulletStatus[i].LifeTime], true);
				break;
			case 2:
				DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_lrd[BulletStatus[i].LifeTime], true);
				break;
			case 3:
				DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_lru[BulletStatus[i].LifeTime], true);
				break;
			case 4:
				DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_down[BulletStatus[i].LifeTime], true);
				break;
			case 5:
				DrawGraph(BulletStatus[i].img_x, BulletStatus[i].img_y, Bullet_img_up[BulletStatus[i].LifeTime], true);
				break;
			}

			//ブレンドモードを消す
			if (BulletStatus[i].LightBulletFlag == 1)
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
	}

}

void Bullet_Relese() {


	for (int i = 0; i < Bullet_IMG_NUM; i++) {
		DeleteGraph(Bullet_img_rld[i]);
		DeleteGraph(Bullet_img_rlu[i]);
		DeleteGraph(Bullet_img_lrd[i]);
		DeleteGraph(Bullet_img_lru[i]);

		DeleteGraph(Bullet_img_down[i]);
		DeleteGraph(Bullet_img_up[i]);
	}
}

