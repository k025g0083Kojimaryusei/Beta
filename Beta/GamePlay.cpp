#define _USE_MATH_DEFINES
#include <cmath>
#include "GamePlay.h"
#include "Collider.h"

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
	Camera2D::GetInstance()->SetCameraZoom({ 1.0f,1.0f });

	currentWave_ = 1; // first wave
	StartWave(currentWave_);  // NEW

}

void GamePlay::Update(char* keys, char* preKeys) {
	// Fixed dt: 1/60 sec each frame
	dt_ = 1.0f / 60.0f;

	CameraControl(keys, preKeys);
	cameraRotateEasing_.Update();
	Camera2D::GetInstance()->MoveCameraTransform();
	player_.Update(keys, preKeys, stage_.GetTransform(), dt_);
	enemy_.Update(stage_.GetEnemySpawnRangeTransform(),currentCameraRotation_, dt_);
	// NEW: check collisions between player and enemies
	CheckPlayerEnemyCollision();
	if (IsWaveCleared()) {
		if (currentWave_ < 5) {
			currentWave_++;
			StartWave(currentWave_);
		}
		else {
			// All 5 waves cleared – you can add "game clear" logic here
			// e.g., stop spawning or show message
		}
	}
	
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

void GamePlay::CheckPlayerEnemyCollision() {
	const Transform2D& playerTf = player_.GetTransform();
	const auto& enemyList = enemy_.GetEnemies();

	for (int i = 0; i < static_cast<int>(enemyList.size()); ++i) {
		const auto& e = enemyList[i];
		if (!e.isActive) {
			continue;
		}

		if (collider_.AABB(playerTf, e.transform)) {
			// Collision detected
			player_.OnHitEnemy();
			enemy_.DeactivateEnemy(i);

			// If you want only one collision processed per frame:
			break;
		}
	}
}

void GamePlay::StartWave(int waveIndex) {
	if (waveIndex < 1 || waveIndex > 5) {
		return; // out of range
	}

	int enemyCount = waveEnemyCounts_[waveIndex - 1];
	const Transform2D& spawnStageTf = stage_.GetEnemySpawnRangeTransform();

	enemy_.SpawnWave(spawnStageTf, enemyCount);
}

bool GamePlay::IsWaveCleared() const {
	const auto& enemyList = enemy_.GetEnemies();
	for (const auto& e : enemyList) {
		if (e.isActive) {
			return false;
		}
	}
	return true;
}

