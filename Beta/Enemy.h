#pragma once
#include <Novice.h>
#include "Object2D.h"
#include "Camera2D.h"
#include "GameConfig.h"
#include"Collider.h"
#include "Easing.h"
#include <vector>


//敵データ構造体
struct EnemyData {
	Transform2D transform;				//データ
	Vector2 size = { 68.0f,68.0f };		//サイズ
	Collider collider;					//当たり判定
	Vector2 velocity = {};				//速度
	int moveType;						//移動軸 x = 0, y = 1
	int count;							//カウント
	Vector2 speed = { 400.0f,400.0f };		//移動速度
	bool isActive;						//生存フラグ
};

class Enemy{
public:
	Enemy();
	Enemy(const Transform2D & spawnStage);
	void Init(const Transform2D & spawnStage);
	void Update(const Transform2D& spawnStage,float cameraRotate, float dt);
	void Draw();
	// NEW: read-only access to enemies
	const std::vector<EnemyData>& GetEnemies() const { return enemies; }

	// NEW (optional): handle enemy when hit
	void DeactivateEnemy(int index);

	// Enemy.h (public)
	void SpawnWave(const Transform2D& spawnStage, int count);   // NEW
	void ClearEnemies();                                        // NEW

private:

	//敵データ配列
	std::vector<EnemyData> enemies;
	const int maxEnemiesSpawnCount = 10;	//最大敵数
	
	Easing rotateEasing;				//テクスチャ回転イージング
	float targetRotation = 0.0f;		//目標回転角度

	

	//敵テクスチャ
	int count1Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy1.png");
	int count2Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy2.png");
	int count3Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy3.png");
	int count4Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy4.png");
	int count5Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy5.png");
	int count6Texture = Novice::LoadTexture("./Textures/Characters/Enemy/enemy6.png");

	//敵スポーン処理
	void SpawnEnemy(const Transform2D & spawnStage);
	
	//敵移動処理
	void Move(float dt);
	
	//ステージ内にクランプする処理
	void ClampToStage(const Transform2D & spawnStage);

	//テクスチャ回転処理
	void RotateTexture(float cameraRotate);

	float GetRandomFloat(float min, float max);
	int GetRandomInt(int min, int max);

};

