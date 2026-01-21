#define _USE_MATH_DEFINES
#include <cmath>
#include "GamePlay.h"

GamePlay::GamePlay() {
	Init();
}

void GamePlay::Init() {
	Camera2D::cameraInfo cameraInfo;
	Camera2D::GetInstance()->InitCameraTransform(cameraInfo, 1280.0f, 720.0f);
	GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetPrevStageState(GameConfig::TOP);
	currentCameraRotation_ = 0.0f;
	player_.Init();
	enemy_.Init(stage_.GetEnemySpawnRangeTransform());
	Camera2D::GetInstance()->SetCameraZoom({ 2.0f,2.0f });
}

void GamePlay::Update(char* keys, char* preKeys) {
	CameraControl(keys, preKeys);
	cameraRotateEasing_.Update();
	Camera2D::GetInstance()->MoveCameraTransform();
	player_.Update(keys, preKeys, stage_.GetTransform());
	enemy_.Update(stage_.GetEnemySpawnRangeTransform(),currentCameraRotation_);

}

void GamePlay::Draw() {
	stage_.Draw();
	player_.Draw();
	enemy_.Draw();
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

	Camera2D::GetInstance()->SetCameraRotation(cameraRotateEasing_.easingRate);
	currentCameraRotation_ = cameraRotateEasing_.easingRate;
}

