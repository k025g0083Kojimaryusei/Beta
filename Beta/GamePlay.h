#pragma once
#include "GameConfig.h"
#include "Camera2D.h"
#include "CameraManager.h"
#include "Stage.h"
#include "Player.h"
#include "Easing.h"
#include "Collider.h"
#include "Enemy.h"
#include "UI.h"
#include "Background.h"



class GamePlay {
public:

	GamePlay();										//コンストラクタ
	void Init();									//初期化
	void Update(char* keys, char* preKeys);			//更新	
	void Draw();									//描画

private:

	Stage stage_;									//ステージ
	Player player_;									//プレイヤー
	Enemy enemy_;									//敵
	UI ui_;											//UI
	Background background_;							//背景
	Collider collider_;								//当たり判定
	Easing cameraRotateEasing_;						//カメラ回転イージング
	float currentCameraRotation_ = 0.0f;			//現在のカメラ回転角度
	void CameraControl(char* keys, char* preKeys);	//カメラ操作
	Camera2D::cameraInfo mainCameraInfo;
	Camera2D::cameraInfo uiCameraInfo;

};