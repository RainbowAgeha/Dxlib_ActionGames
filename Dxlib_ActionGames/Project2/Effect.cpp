#include "GameMain.h"
#include "GameSceneMain.h"
#include "Effect.h"



//エフェクトの画像
#define EFFECT_NUM 100
struct EFFECT_STATUS {
	int isDead;		//生死フラグ
	int img_x;		//X位置
	int img_y;		//Y位置
	int img_angle;	//角度（軌跡のゆらぎ
	int img_no;
	int EffectNo;
	int LifeTime;
	int EffectTimeWait;
	int LightEffectFlag;		//光るエフェクトかどうか
	int LightEffectTime;		//光度
};
EFFECT_STATUS EffectStatus[EFFECT_NUM];
#define EFFECT_IMG_NUM 9
int Effect_img_rld[EFFECT_IMG_NUM];
int Effect_img_rlu[EFFECT_IMG_NUM];
int Effect_img_lrd[EFFECT_IMG_NUM];
int Effect_img_lru[EFFECT_IMG_NUM];
int Effect_img_down[EFFECT_IMG_NUM];
int Effect_img_up[EFFECT_IMG_NUM];

#define Effect_Size 120


//エフェクトデータの初期化
void Effect_Init() {

	LoadDivGraph("res/btleffect01.png", 9, 9, 1, 120, 120, Effect_img_rld);
	LoadDivGraph("res/btleffect02.png", 9, 9, 1, 120, 120, Effect_img_rlu);
	LoadDivGraph("res/btleffect03.png", 9, 9, 1, 120, 120, Effect_img_lrd);
	LoadDivGraph("res/btleffect04.png", 9, 9, 1, 120, 120, Effect_img_lru);
	LoadDivGraph("res/btleffect05.png", 9, 9, 1, 120, 180, Effect_img_down);
	LoadDivGraph("res/btleffect06.png", 9, 9, 1, 120, 180, Effect_img_up);

	//構造体配列の初期化
	for (int i = 0; i < EFFECT_NUM; i++) {
		EffectStatus[i].isDead = 0;		//使っていない
		EffectStatus[i].img_x = 0;
		EffectStatus[i].img_y = 0;
		EffectStatus[i].img_angle = 0;
		EffectStatus[i].img_no = 0;		//画像種類
		EffectStatus[i].EffectNo = 0;
		EffectStatus[i].LifeTime = 0;	//表示時間
		EffectStatus[i].EffectTimeWait = 0;	//表示時間
		EffectStatus[i].LightEffectFlag = 0;	//光エフェクトフラグ
		EffectStatus[i].LightEffectTime = 0;	//光エフェクトフラグ
	}

}

void Effect_Add(int _x,int _y) {
	//構造体配列の初期化
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (EffectStatus[i].isDead == 0) {
			EffectStatus[i].isDead = 1;		//使用中
			EffectStatus[i].img_x = _x;
			EffectStatus[i].img_y = _y;
			EffectStatus[i].img_angle = (rand () % 60) + 90;
			EffectStatus[i].img_no = 0;		//画像種類
			//EffectStatus[i].EffectNo = rand() % 6;	//エフェクトの種類
			EffectStatus[i].EffectNo = 0;	//エフェクトの種類
			EffectStatus[i].LifeTime = 0;	//生存時間
			EffectStatus[i].EffectTimeWait = EFFECT_IMG_NUM-1;	//表示時間
			EffectStatus[i].LightEffectFlag = 1;	//光エフェクトフラグ
			EffectStatus[i].LightEffectTime = 255;	//光度
			break;
		}
	}

}

void Effect_Update() {


	//構造体配列の初期化
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (EffectStatus[i].isDead == 1) {
			// アニメーションカウントの計算
			// カウントが終了した場合は殺す
			if (EffectStatus[i].LifeTime++ >= EffectStatus[i].EffectTimeWait) EffectStatus[i].isDead = 0;
			EffectStatus[i].LightEffectTime -= 25;//明るさを少なくする
		}
	}


}

void Effect_Render() {
	//　画像の表示
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (EffectStatus[i].isDead == 1) {

			//エフェクトが光エフェクトならブレンドモードを適応する
			if (EffectStatus[i].LightEffectFlag == 1)
				SetDrawBlendMode(DX_BLENDMODE_ADD, EffectStatus[i].LightEffectTime);


			switch (EffectStatus[i].EffectNo) {
			case 0:
				DrawRotaGraphF(EffectStatus[i].img_x, EffectStatus[i].img_y , 1 , EffectStatus[i].img_angle, Effect_img_rld[EffectStatus[i].LifeTime], true);
				//DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_rld[EffectStatus[i].LifeTime], true);
				break;
			//TODO:以下要らない？
			case 1:
				DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_rlu[EffectStatus[i].LifeTime], true);
				break;
			case 2:
				DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_lrd[EffectStatus[i].LifeTime], true);
				break;
			case 3:
				DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_lru[EffectStatus[i].LifeTime], true);
				break;
			case 4:
				DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_down[EffectStatus[i].LifeTime], true);
				break;
			case 5:
				DrawGraph(EffectStatus[i].img_x, EffectStatus[i].img_y, Effect_img_up[EffectStatus[i].LifeTime], true);
				break;
			}

			//ブレンドモードを消す
			if (EffectStatus[i].LightEffectFlag  == 1)
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}
	}

}

void Effect_Relese() {


	for (int i = 0; i < EFFECT_IMG_NUM; i++){
		DeleteGraph(Effect_img_rld[i]);
		DeleteGraph(Effect_img_rlu[i]);
		DeleteGraph(Effect_img_lrd[i]);
		DeleteGraph(Effect_img_lru[i]);

		DeleteGraph(Effect_img_down[i]);
		DeleteGraph(Effect_img_up[i]);
	}
}

