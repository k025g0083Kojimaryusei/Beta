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
#include "PlayBackground.h"
#include "Score.h"
#include "ComboManager.h"
#include <vector>
#include "SoundManager.h"
//
#include "EnemyEffect.h"

class GamePlay {
public:

	enum GameState {
		Play,
		Ranking,
	};

	GameState state = Play;
	GamePlay();											//コンストラクタ
	void Init();										//初期化
	void Update(char* keys, char* preKeys);				//更新	
	void Draw();										//描画
	int GetPlayerHP() const { return player_.GetHP(); }
private:
	Stage stage_;										//ステージ
	Player player_;										//プレイヤー
	Enemy enemy_;										//敵
	UI ui_;												//UI
	PlayBackground bg_;								//背景
	Collider collider_;									//当たり判定
	Easing cameraRotateEasing_;							//カメラ回転イージング
	float currentCameraRotation_ = 0.0f;				//現在のカメラ回転角度
	void CameraControl();								//カメラ操作
	Camera2D::cameraInfo mainCameraInfo;
	Camera2D::cameraInfo uiCameraInfo;
	bool PlayerIsHitEnemy();							//プレイヤーが敵に当たったか
	void DebugText();									//デバッグテキスト表示
	void NextStageCheck();								//次のステージへ進むかの判定
	bool isNextStageAdded = false;
	void WaveCountCheck();								//ウェーブ数の判定
	bool isWaveCountEnded = true;						//ウェーブ数が終了したか
	bool prePlayerOnGround = false;
	void SlowMotion();									//スローモーション開始
	Easing timeScaleEasing_;							//時間倍率イージング
	float  normalTimeScale = 1.0f;						//通常時間倍率
	float slowMotionTimeScale = normalTimeScale / 180;	//スローモーション時間倍率

	int slowMotionTime = 30;							//スローモーション時間

	int combo = 0;										//コンボ数

	// In GamePlay.h (private section)
	float cameraShakeTime_ = 0.0f;
	float cameraShakeDuration_ = 0.0f;
	float cameraShakePower_ = 0.0f;
	Vector2 cameraShakeOffset_ = { 0.0f, 0.0f };
	Vector2 cameraBasePos_ = { 640.0f, 360.0f };

	bool isPlayerWasHit_ = false;
	bool wasPlayerHitInLastFrame_ = false;

	/// <summary>
	/// //////////
	/// </summary>
	std::vector<EnemyEffect> enemyEffects_;
};