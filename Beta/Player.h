#pragma once

#include "Object2D.h"
#include "Camera2D.h"
#include "GameConfig.h"
#include"Collider.h"
#include <Novice.h>
#include "Easing.h"


class Player {
public:
	Player();
	void Init();
	void Update(char* keys, char* preKeys,const Transform2D & stage, float dt);
	void Draw();

	// NEW: access to transform
	Transform2D& GetTransform() { return transform; }
	const Transform2D& GetTransform() const { return transform; }

	// NEW: handle damage / respawn
	void OnHitEnemy();

	bool IsInvincible() const { return invincibleTime_ > 0; }
private:
	//プレイヤーの向き
	enum Direction {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	Collider collider;											//当たり判定
	Vector2 size = { 68.0f,68.0f };								//サイズ
	Transform2D transform;										//データ
	Vector2 velocity = {};										//速度
	Direction direction;										//向いている方向
	Direction preDirection;										//前の向いている方向
	float gravityStrength = 2000.0f;								//重力の強さ
	Vector2 gravity = {0.0f,gravityStrength};					//重力
	int directionChangeLeft = 2;								//方向変更残り回数
	const int maxDirectionChange = 9;							//方向変更最大回数
	int hp;														//体力
	float walkSpeed = 5.0f;										//歩く速さ
	bool canChangeGravity;										//方向を変えることができるか
	bool isHitLeft = false;										//左に当たったか
	bool isHitRight = false;									//右に当たったか
	bool isHitTop = false;										//上に当たったか
	bool isHitBottom = false;									//下に当たったか
	bool isHitStage = false;									//ステージに当たったか
	bool onGround = false;										//地面にいるか
	Easing rotateEasing;										//テクスチャ回転イージング
	float targetRotation = 0.0f;								//目標回転角度
	
	int invincibleTime_ = 0;     // frames of invincibility after hit
	int invincibleDuration_ = 60;
	int playerTextureHandle = Novice::LoadTexture("./Textures/Characters/Player/player.png");	//テクスチャハンドル
	void Move(char* keys, char* preKeys,const Transform2D & stage, float dt);

	// 地面にいるときの移動処理
	void OnGroundMove();

	//空中にいるときの移動処理
	void InAirMove(char* keys, char* preKeys);

	//ステージ内にクランプする処理
	void ClampToStage(const Transform2D& stage);

	//テクスチャ回転処理
	void RotateTexture();

	//デバッグ出力
	void DebugOutput();
};