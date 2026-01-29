#define _USE_MATH_DEFINES
#include <cmath>
#include "Player.h"

#ifdef USE_IMGUI
#include <imgui.h>
#endif 

Player::Player() {
	Init();
}
void Player::Init() {
	// 1. 基本ステータスのリセット
	transform.Init({ 640.0f,626.0f }, size.x, size.y);	// 初期座標
	velocity = { 0.0f, 0.0f };							// 速度をゼロにする

	// 2. フラグ類のリセット
	isHitStage = false;
	onGround = true;
	canChangeGravity = true;

	// 当たり判定フラグもすべて偽にリセット
	isHitLeft = false;
	isHitRight = false;
	isHitTop = false;
	isHitBottom = false;

	// 3. 重力回数のリセット
	directionChangeLeft = maxDirectionChange;

	// GameConfig の初期値が TOP なら、それに対応する重力方向をセットする
	gravity = { 0.0f, -gravityStrength };

	//テクスチャ回転イージング初期化
	rotateEasing.Init(0.0f,0.0f,20,EasingType::EASING_EASE_IN_OUT_CUBIC);

	direction = TOP;
	preDirection = TOP;
	targetRotation = 0.0f;
}

//更新処理
void Player::Update(char* keys, char* preKeys, const Transform2D& stage) {
	Move(keys, preKeys, stage);
	RotateTexture();
	/*ImGui::Begin("Player Info");
	ImGui::SliderFloat("Speed",&gravityStrength,0.5f,5.0f);
	ImGui::End();*/
}

//描画処理
void Player::Draw() {

	Quad screen = CameraManager::GetInstance()->GetMainCamera().WorldToScreen(transform);
	Novice::DrawQuad(
		static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
		static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
		static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
		static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
		0, 0,
		static_cast<int>(transform.width),
		static_cast<int>(transform.height),
		playerTextureHandle[directionChangeLeft], WHITE
	);

	//Novice::ScreenPrintf(0,20,"PlayerDirectionLeft = %d",directionChangeLeft);
}

//移動処理
void Player::Move(char* keys, char* preKeys, const Transform2D& stage) {

	if (GameConfig::GetInstance()->GetIsRotate()) {
		return;
	}

	float ts = GameConfig::GetInstance()->GetTimeScale();

	//回数回復処理
	RecoverCount();

	//地面にいる場合の処理
	if (onGround) {
		OnGroundMove();
	}

	//空中での処理
	if (!onGround && canChangeGravity) {
		InAirMove(keys, preKeys);
	}

	//重力を加算
	velocity.x += gravity.x * ts;
	velocity.y += gravity.y * ts;

	transform.worldPos.x += velocity.x * ts;
	transform.worldPos.y += velocity.y * ts;


	onGround = false;

	ClampToStage(stage);
	
}

void Player::OnGroundMove() {
	if (!onGround) {
		return;
	}
	onGround = false;
	canChangeGravity = true;
	velocity = { 0.0f,0.0f };
	gravity = { 0.0f,0.0f };
	directionChangeLeft = 2;
}


void Player::InAirMove(char* keys, char* preKeys) {
	switch (GameConfig::GetInstance()->GetStageState()) {
		//--------------------------------------------------------------------------
	case GameConfig::TOP:
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			if (direction != TOP) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = TOP;
				}
			}
		}
		if (keys[DIK_S] && !preKeys[DIK_S]) {
			if (direction != BOTTOM) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = BOTTOM;
				}
			}
		}
		if (keys[DIK_A] && !preKeys[DIK_A]) {
			if (direction != LEFT) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = LEFT;
				}
			}
		}
		if (keys[DIK_D] && !preKeys[DIK_D]) {
			if (direction != RIGHT) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = RIGHT;
				}
			}
		}
		break;

		//----------------------------------------------------------------------
	case GameConfig::BOTTOM:
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			if (direction != BOTTOM) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = BOTTOM;
				}
			}
		}
		if (keys[DIK_S] && !preKeys[DIK_S]) {
			if (direction != TOP) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = TOP;
				}
			}
		}
		if (keys[DIK_A] && !preKeys[DIK_A]) {
			if (direction != RIGHT) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = RIGHT;
				}
			}
		}
		if (keys[DIK_D] && !preKeys[DIK_D]) {
			if (direction != LEFT) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = LEFT;
				}
			}
		}
		break;
		//----------------------------------------------------------------------
	case GameConfig::LEFT:
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			if (direction != LEFT) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = LEFT;
				}
			}
		}
		if (keys[DIK_S] && !preKeys[DIK_S]) {
			if (direction != RIGHT) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = RIGHT;
				}
			}
		}
		if (keys[DIK_A] && !preKeys[DIK_A]) {
			if (direction != BOTTOM) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = BOTTOM;
				}
			}
		}
		if (keys[DIK_D] && !preKeys[DIK_D]) {
			if (direction != TOP) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = TOP;
				}
			}
		}
		break;
		//------------------------------------------------------------------
	case GameConfig::RIGHT:
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			if (direction != RIGHT) {
				velocity = { 0.0f,0.0f };
				gravity = { gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = RIGHT;
				}
			}
		}
		if (keys[DIK_S] && !preKeys[DIK_S]) {
			if (direction != LEFT) {
				velocity = { 0.0f,0.0f };
				gravity = { -gravityStrength,0.0f };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = LEFT;
				}
			}
		}
		if (keys[DIK_A] && !preKeys[DIK_A]) {
			if (direction != TOP) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = TOP;
				}
			}
		}
		if (keys[DIK_D] && !preKeys[DIK_D]) {
			if (direction != BOTTOM) {
				velocity = { 0.0f,0.0f };
				gravity = { 0.0f,-gravityStrength };
				if (directionChangeLeft > 0) {
					directionChangeLeft--;
					direction = BOTTOM;
				}
			}
		}
		break;
	}
	
	if (directionChangeLeft <= 0) {
		canChangeGravity = false;
	}

}
void Player::ClampToStage(const Transform2D& stage) {
	//当たり判定
	isHitLeft = collider.IsHitLeft(transform, stage);
	isHitRight = collider.IsHitRight(transform, stage);
	isHitTop = collider.IsHitTop(transform, stage);
	isHitBottom = collider.IsHitBottom(transform, stage);

	if (gravity.x < 0 && isHitLeft) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::LEFT);
	}
	if (gravity.x > 0 && isHitRight) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::RIGHT);
	}
	if (gravity.y < 0 && isHitBottom) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::BOTTOM);
	}
	if (gravity.y > 0 && isHitTop) {
		onGround = true;
		GameConfig::GetInstance()->SetStageState(GameConfig::TOP);
	}
}

//テクスチャ回転処理
void Player::RotateTexture() {
	
	if (direction != preDirection) {
		float target = 0.0f;
		switch (direction) {
		case TOP:    target = 0.0f;   break;
		case BOTTOM: target = 180.0f; break;
		case LEFT:   target = 270.0f; break;
		case RIGHT:  target = 90.0f;  break;
		}

		// --- 最短経路の計算 ---
		// 現在の角度を 0~360 の範囲に収める (念のため)
		float current = fmodf(transform.rotation, 360.0f);
		if (current < 0) current += 360.0f;

		// 差分を求める
		float diff = target - current;

		// 差分が 180度 を超える場合は、逆回転の方が近い
		if (diff > 180.0f) {
			diff -= 360.0f;
		}
		else if (diff < -180.0f) {
			diff += 360.0f;
		}

		// 現在の角度から、最短の差分を足したものを新しい目標にする
		float finalTarget = current + diff;
		// ----------------------

		// イージング初期化
		rotateEasing.Init(current, finalTarget, 20 , EasingType::EASING_EASE_IN_OUT_CUBIC);
		rotateEasing.Start();

		preDirection = direction;
	}

	// 更新と反映
	rotateEasing.Update();
	transform.rotation = rotateEasing.easingRate;
	transform.Init(transform.worldPos, transform.width, transform.height, transform.rotation);
}

//回復カウント処理
void Player::RecoverCount() {
	if (isHitEnemy) {
		isHitEnemy = false;
		directionChangeLeft++;
		if (directionChangeLeft > maxDirectionChange) {
			directionChangeLeft = maxDirectionChange;
		}

	}

	if (directionChangeLeft > 0) {
		canChangeGravity = true;
	}

}