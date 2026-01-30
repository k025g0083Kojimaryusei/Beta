#pragma once
#include <Novice.h>
#include "Object2D.h"
#include "CameraManager.h"
#include "GameConfig.h"
#include"Collider.h"
#include "Easing.h"
#include <vector>
#include "EnemyEffect.h"

class Enemy {
public:
	//敵データ構造体
	struct EnemyData {
		Transform2D transform;				//データ
		Vector2 size = { 40.0f,40.0f };		//サイズ
		Collider collider;					//当たり判定
		Vector2 velocity = {};				//速度
		int moveType;						//移動軸 x = 0, y = 1
		int count;							//カウント
		Vector2 speed = { 5.0f,5.0f };		//移動速度
		bool isActive;						//生存フラグ

	};

	Enemy();
	Enemy(const Transform2D& spawnStage);

	//初期化
	void Init(const Transform2D& spawnStage);

	//更新
	void Update(const Transform2D& spawnStage, float cameraRotate, bool playerIsOnGround);

	//描画
	void Draw();

	//敵データ配列取得 
	std::vector<EnemyData>& GetEnemies() { return enemies; }

	//敵データ配列設定
	void SetEnemyData(const std::vector<EnemyData>& newEnemies);

	//全滅判定取得
	bool IsAllDead() const { return allDead; }

	//STAGEの最大敵数取得
	int GetMaxEnemyCount() const {
		int stage = GameConfig::GetInstance()->GetCurrentStage();
		if (stage > 4) {
			stage = 4;
		}
		return stageEnemyCount[stage];
	}

	int GetNumZeroedThisTick() const { return numEnemiesZeroedThisTick_; }
	void ResetNumZeroedThisTick() { numEnemiesZeroedThisTick_ = 0; }

	const std::vector<Vector2>& GetNaturalRedDeaths() const { return naturalRedDeaths_; }
	void ClearNaturalRedDeaths() { naturalRedDeaths_.clear(); }

	// In Enemy.h (in Enemy class, public section)
	bool IsRed(const EnemyData& e) const { return e.count == 0; }

private:
	//敵データ配列
	std::vector<EnemyData> enemies;

	Easing rotateEasing;				//テクスチャ回転イージング
	float targetRotation = 0.0f;		//目標回転角度

	int numEnemiesZeroedThisTick_ = 0;

	//敵テクスチャ
	int countTexture40[6] = {
		Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy1.png"),
	Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy2.png"),
	Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy3.png"),
	Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy4.png"),
	Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy5.png"),
	Novice::LoadTexture("./Textures/Characters/Enemy/40Enemy/40enemy6.png")
	};

	int countTexture50[6] = {
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy1.png"),
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy2.png"),
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy3.png"),
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy4.png"),
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy5.png"),
			Novice::LoadTexture("./Textures/Characters/Enemy/50Enemy/50enemy6.png")
	};

	int textTexture[6] = {
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy1.png"),
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy2.png"),
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy3.png"),
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy4.png"),
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy5.png"),
					Novice::LoadTexture("./Textures/Characters/Enemy/enemy6.png"),
	};
	//敵スポーン処理
	void SpawnEnemy(const Transform2D& spawnStage);

	//敵移動処理
	void Move();

	//ステージ内にクランプする処理
	void ClampToStage(const Transform2D& spawnStage);

	//テクスチャ回転処理
	void RotateTexture(float cameraRotate);

	//全滅フラグ
	bool allDead = false;

	//全滅判定処理
	void CheckAllDead();

	//リスポーン処理
	void Respawn(const Transform2D& spawnStage, bool playerIsOnGround);

	//ランダム関数
	float GetRandomFloat(float min, float max);
	int GetRandomInt(int min, int max);

	//ステージごとの敵出現数
	int stageEnemyCount[5] = { 7,12,17,20,30 };

	bool canCountdown = false;
	int prevWaveCount = GameConfig::GetInstance()->GetCurrentWave();

	std::vector<Vector2> naturalRedDeaths_;
};

