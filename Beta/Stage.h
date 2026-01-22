#pragma once
#include "Object2D.h"
#include "Easing.h"
#include "CameraManager.h"
#include <Novice.h>

class Stage {
public:
	Stage();
   	void Draw();
	Transform2D& GetTransform() { return stageTransform_; }
	Transform2D& GetEnemySpawnRangeTransform() { return enemySpawnRangeTransform_; }
private:

	float stageWidth_ = 600.0f;				//ステージ幅
	float stageHeight_ = 600.0f;			//ステージ高さ
	Transform2D stageTransform_;			//ステージデータ

	float enemySpawnRangeWidth_ = 450.0f;	//敵スポーン範囲幅
	float enemySpawnRangeHeight_ = 450.0f;  //敵スポーン範囲高さ
	Transform2D enemySpawnRangeTransform_;  //敵スポーン範囲データ

	float backgroundWidth_ = 1300.0f;		//背景幅
	float backgroundHeight_ = 740.0f;		//背景高さ
	Transform2D backgroundTransform_;		//背景データ
	int stageTextureHandle_ = Novice::LoadTexture("./Textures/Stage/stage.png");
};