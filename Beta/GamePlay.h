#pragma once
#include "GameConfig.h"
#include "Camera2D.h"
#include "Stage.h"
#include "Player.h"
#include "Easing.h"
#include "Collider.h"
#include "Enemy.h"

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
	Collider collider_;								//当たり判定
	Easing cameraRotateEasing_;						//カメラ回転イージング
	float currentCameraRotation_ = 0.0f;			//現在のカメラ回転角度
	void CameraControl(char* keys, char* preKeys);	//カメラ操作
	void CheckPlayerEnemyCollision();  // NEW
	void StartWave(int waveIndex);       // NEW
	bool IsWaveCleared() const;          // NEW
	int currentWave_ = 1;                // 1..5
	// number of enemies per wave
	int waveEnemyCounts_[5] = { 5, 10, 15, 20, 25 };  // NEW
	// --- NEW: time control ---
	float dt_ = 1.0f / 60.0f;             // current delta time
	//const float normalDt_ = 1.0f / 60.0f; // normal speed
	//const float slowDt_ = 1.0f / 240.0f; // slow motion like prototype

	//bool isInSlowMotion_ = false;
	//int   slowMotionFrames_ = 0;            // use frames, not float seconds

};