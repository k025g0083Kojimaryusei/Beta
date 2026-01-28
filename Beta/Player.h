#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include "GameConfig.h"
#include"Collider.h"
#include <Novice.h>
#include "Easing.h"


class Player {
public:
	Player();
	void Init();
	void Update(char* keys, char* preKeys, const Transform2D& stage);
	void Draw();
	const Transform2D& GetTransform() const { return transform; }
	void SetIsHitEnemy(bool hit) { isHitEnemy = hit; }

	bool IsOnGround() const { return onGround; }

private:
	//プレイヤーの向き
	enum Direction {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	Collider collider;											//当たり判定
	Vector2 size = { 60.0f,60.0f };								//サイズ
	Transform2D transform;										//データ
	Vector2 velocity = {};										//速度
	Direction direction;										//向いている方向
	Direction preDirection;										//前の向いている方向
	float gravityStrength = 0.5f;								//重力の強さ
	Vector2 gravity = { 0.0f,gravityStrength };					//重力
	int directionChangeLeft = 2;								//方向変更残り回数
	const int maxDirectionChange = 1;							//方向変更最大回数
	bool canChangeGravity;										//方向を変えることができるか
	bool isHitLeft = false;										//左に当たったか
	bool isHitRight = false;									//右に当たったか
	bool isHitTop = false;										//上に当たったか
	bool isHitBottom = false;									//下に当たったか
	bool isHitStage = false;									//ステージに当たったか
	bool onGround = false;										//地面にいるか
	Easing rotateEasing;										//テクスチャ回転イージング
	float targetRotation = 0.0f;								//目標回転角度
	bool isHitEnemy = false;									//敵に当たったか

	//プレイヤーテクスチャ
	int playerTextureHandle[3] = {
		Novice::LoadTexture("./Textures/Characters/Player/player3.png"),
		Novice::LoadTexture("./Textures/Characters/Player/player2.png"),
		Novice::LoadTexture("./Textures/Characters/Player/player1.png"),
	};

	void Move(char* keys, char* preKeys, const Transform2D& stage);

	// 地面にいるときの移動処理
	void OnGroundMove();

	//空中にいるときの移動処理
	void InAirMove(char* keys, char* preKeys);

	//ステージ内にクランプする処理
	void ClampToStage(const Transform2D& stage);

	//テクスチャ回転処理
	void RotateTexture();

	//回数回復処理
	void RecoverCount();
};