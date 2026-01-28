#define _USE_MATH_DEFINES
#include <cmath>
#include "GamePlay.h"
#include <imgui.h>

GamePlay::GamePlay() {
	Init();
}



void GamePlay::Init() {
	//メインカメラの初期化
	CameraManager::GetInstance()->GetMainCamera().InitCameraTransform(mainCameraInfo, 1280.0f, 720.0f);
	
	uiCameraInfo.centerpos = { 640.0f,360.0f };
	//UIカメラの初期化
	CameraManager::GetInstance()->GetUICamera().InitCameraTransform(uiCameraInfo, 1280.0f, 720.0f);
	
	//ステージステータスの初期化
	GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetPrevStageState(GameConfig::TOP);
	GameConfig::GetInstance()->SetCurrentStage(0);
	GameConfig::GetInstance()->SetCurrentWave(0);
	//カメラ回転角度の初期化
	currentCameraRotation_ = 0.0f;
	
	//プレイヤーの初期化
	player_.Init();

	//敵の初期化
	enemy_.Init(stage_.GetEnemySpawnRangeTransform());

	//UIの初期化
	ui_.Init();

	//コンボの初期化
	ComboManager::GetInstance()->ResetCombo();

	//スコアの初期化
	Score::GetInstance()->ResetScore();

	//ステージ回転の初期化
	cameraRotateEasing_.Init(0.0f, 0.0f, 60, EasingType::EASING_EASE_IN_OUT_QUAD);
	cameraRotateEasing_.easingRate = 0.0f;
}


void GamePlay::Update(char* keys, char* preKeys) {

	if (keys[DIK_R] && !preKeys[DIK_R]) {
		Score::GetInstance()->ResetScore();
	}

	bg_.Update();

	//カメラ操作
	CameraControl();

	//カメラ更新
	CameraManager::GetInstance()->UpdateAll();
	// カメライージング更新
	cameraRotateEasing_.Update();

	//プレイヤー更新
	player_.Update(keys, preKeys, stage_.GetTransform());

	WaveCountCheck();
	//敵更新
	enemy_.Update(stage_.GetEnemySpawnRangeTransform(),currentCameraRotation_,player_.IsOnGround());


	timeScaleEasing_.Update();

	//プレイヤーが敵に当たったか
	if(PlayerIsHitEnemy()){
		timeScaleEasing_.Init(slowMotionTimeScale,normalTimeScale, slowMotionTime, EasingType::EASING_EASE_OUT_CUBIC);
		timeScaleEasing_.Start();
	}

	if (timeScaleEasing_.isMove) {
		GameConfig::GetInstance()->SetTimeScale(timeScaleEasing_.easingRate);
	}else {
		GameConfig::GetInstance()->SetTimeScale(normalTimeScale);
	}

	GameConfig::GetInstance()->ClearWaveChangedFlag();

	//次のステージへ進むかの判定
	NextStageCheck();

	//UI更新
	ui_.Update();
	
}

//描画処理
void GamePlay::Draw() {
	bg_.Draw();
	stage_.Draw();
	player_.Draw();
	enemy_.Draw();
	ui_.Draw(player_.GetTransform(),currentCameraRotation_);
	DebugText();
}

void GamePlay::DebugText() {
	ImGui::Begin("GamePlay::DebugText ");
	
	ImGui::Text("stage = %d", GameConfig::GetInstance()->GetCurrentStage());
	ImGui::Text("Wave = % d", GameConfig::GetInstance()->GetCurrentWave());
	ImGui::Text("Score = %d", Score::GetInstance()->GetDisplayScore());
	ImGui::Text("Combo = % d",ComboManager::GetInstance()->GetComboCount());
	ImGui::Text("StageState = %d", GameConfig::GetInstance()->GetStageState());
	ImGui::End();
	

}


//カメラ操作
void GamePlay::CameraControl() {

	GameConfig* config = GameConfig::GetInstance();
	
	//ステージの状態が変化したらカメラ回転イージング開始
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

//プレイヤーが敵に当たったか
bool GamePlay::PlayerIsHitEnemy() {
	const Transform2D& playerTransform = player_.GetTransform();
	std::vector<Enemy::EnemyData>& enemies = enemy_.GetEnemies();

	for (auto& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
		if (collider_.AABB(playerTransform, enemy.transform)) {

			int maxEnemies = enemy_.GetMaxEnemyCount();
		
			ComboManager::GetInstance()->AddCombo();
			Score::GetInstance()->AddScore(maxEnemies);
			enemy.isActive = false; // 生存フラグをfalse
			player_.SetIsHitEnemy(true); // プレイヤーに当たりフラグを設定
			return true; // 衝突が検出された場合、trueを返す
		}
	}
	return false;
}

//次のステージへ進むかの判定
void GamePlay::NextStageCheck() {
	if (enemy_.IsAllDead()) {
		if (!isNextStageAdded) {
			GameConfig::GetInstance()->NextStage();
			GameConfig::GetInstance()->SetCurrentWave(-1); 

			isNextStageAdded = true;
		}
	} else {
		// 敵が復活したらフラグをリセット
		isNextStageAdded = false;
	}
}

void GamePlay::WaveCountCheck() {
	bool currentOnGround = player_.IsOnGround();
	GameConfig* config = GameConfig::GetInstance();

	if (!prePlayerOnGround && currentOnGround) {
		
		int nextWave = config->GetCurrentWave() + 1;
		config->SetCurrentWave(nextWave);
		ComboManager::GetInstance()->ResetCombo();
		combo = 0;
	}

	prePlayerOnGround = currentOnGround;


}

void GamePlay::SlowMotion() {
	timeScaleEasing_.Init(slowMotionTimeScale, normalTimeScale, slowMotionTime, EasingType::EASING_EASE_OUT_CUBIC);
	timeScaleEasing_.Start();
}

