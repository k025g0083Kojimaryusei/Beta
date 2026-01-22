#define _USE_MATH_DEFINES
#include <cmath>
#include "GamePlay.h"

GamePlay::GamePlay() {
	Init();
}

void GamePlay::Init() {
	mainCameraInfo.centerpos = { 640.0f,360.0f };
	//メインカメラの初期化
	CameraManager::GetInstance()->GetMainCamera().InitCameraTransform(mainCameraInfo, 1280.0f, 720.0f);
	
	uiCameraInfo.centerpos = { 640.0f,360.0f };
	//UIカメラの初期化
	CameraManager::GetInstance()->GetUICamera().InitCameraTransform(uiCameraInfo, 1280.0f, 720.0f);
	
	//ステージステータスの初期化
	GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetPrevStageState(GameConfig::TOP);

	//カメラ回転角度の初期化
	currentCameraRotation_ = 0.0f;
	
	//プレイヤーの初期化
	player_.Init();

	//敵の初期化
	enemy_.Init(stage_.GetEnemySpawnRangeTransform());

	//UIの初期化
	ui_.Init();

	//背景の初期化
	background_.Init();
}

void GamePlay::Update(char* keys, char* preKeys) {
	//カメラ操作
	CameraControl(keys, preKeys);

	// カメライージング更新
	cameraRotateEasing_.Update();

	//プレイヤー更新
	player_.Update(keys, preKeys, stage_.GetTransform());

	//敵更新
	enemy_.Update(stage_.GetEnemySpawnRangeTransform(),currentCameraRotation_);
	if (keys[DIK_UPARROW]) {
		mainCameraInfo.centerpos.y += 5.0f;
	}
	if (keys[DIK_DOWNARROW]) {
		mainCameraInfo.centerpos.y -= 5.0f;
	}
	if (keys[DIK_LEFTARROW]) {
		mainCameraInfo.centerpos.x -= 5.0f;
	}
	if (keys[DIK_RIGHTARROW]) {
		mainCameraInfo.centerpos.x += 5.0f;
	}
	// カメラ更新
	CameraManager::GetInstance()->UpdateAll();
	CameraManager::GetInstance()->GetMainCamera().InitCameraTransform(mainCameraInfo, 1280.0f, 720.0f);

}

void GamePlay::Draw() {
	background_.Draw();
	stage_.Draw();
	player_.Draw();
	enemy_.Draw();
	ui_.Draw();
}











void GamePlay::CameraControl(char* keys, char* preKeys) {

	GameConfig* config = GameConfig::GetInstance();
	if (keys[DIK_0] || preKeys[DIK_9]) {

	}
	if (config->GetStageState() != config->GetPrevStageState() && !cameraRotateEasing_.isMove) {
		config->SetIsRotate(true);

		float start = fmodf(currentCameraRotation_, 360.0f);;
		float end = 0.0f;

		switch (config->GetStageState()) {
		case GameConfig::TOP:
			end = 0.0f;
			break;

		case GameConfig::BOTTOM:
			end = 180.0f;
			break;

		case GameConfig::LEFT:
			end = 270.0f;
			break;

		case GameConfig::RIGHT:
			end = 90.0f;
		}



		float diff = end - start;

		// 最短経路の計算
		if (diff > 180.0f) {
			diff -= 360.0f;
		} else if (diff < -180.0f) {
			diff += 360.0f;
		}


		cameraRotateEasing_.Reset();
		cameraRotateEasing_.Init(start, start + diff, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
		cameraRotateEasing_.Start();

		config->SetPrevStageState(config->GetStageState());
	}

	if (!cameraRotateEasing_.isMove) {
		config->SetIsRotate(false);
	}

	CameraManager::GetInstance()->GetMainCamera().SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

