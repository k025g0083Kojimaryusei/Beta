#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include "Score.h"
#include "ComboManager.h"
#include <Novice.h>
#include "GameConfig.h"
#include "Easing.h"
#include "Player.h"
#include <array>

class UI {
public:

	UI();
	void Init();
	void Update(const Vector2& playerWorldPos, int hp);
	void Draw(const Transform2D & playerPos,float cameraRotate,int hp);

private:

	Transform2D scoreBoardTransform_;
	Vector2 scoreTextPos = { 415.0f,690.0f };
	float scoreBoardW = 150.0f;
	float scoreBoardH = 46.0f;
	int scoreBoardTextureHandle_ = Novice::LoadTexture("./Textures/UI/ScoreBoard/scoreboard.png");

	Vector2 numberSize = { 24.0f,40.0f };
	Vector2 numberPos = { 640.0f,690.0f };
	int numbersTextureHandle[10] = {
		Novice::LoadTexture("./Textures/UI/Number/No0.png"),
		Novice::LoadTexture("./Textures/UI/Number/No1.png"),
		Novice::LoadTexture("./Textures/UI/Number/No2.png"),
		Novice::LoadTexture("./Textures/UI/Number/No3.png"),
		Novice::LoadTexture("./Textures/UI/Number/No4.png"),
		Novice::LoadTexture("./Textures/UI/Number/No5.png"),
		Novice::LoadTexture("./Textures/UI/Number/No6.png"),
		Novice::LoadTexture("./Textures/UI/Number/No7.png"),
		Novice::LoadTexture("./Textures/UI/Number/No8.png"),
		Novice::LoadTexture("./Textures/UI/Number/No9.png")
	};
	
	Transform2D comboTransform_;
	Vector2 comboSize = { 32.0f,26.0f };
	Vector2 comboPos;
	Vector2 offset = {44.0f,44.0f };
	int ComboTextureHandle_[31] = {
		Novice::LoadTexture("./Textures/UI/Combo/Combo0.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo1.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo2.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo3.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo4.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo5.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo6.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo7.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo8.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo9.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo10.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo11.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo12.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo13.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo14.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo15.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo16.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo17.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo18.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo19.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo20.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo21.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo22.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo23.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo24.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo25.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo26.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo27.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo28.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo29.png"),
		Novice::LoadTexture("./Textures/UI/Combo/Combo30.png")
	};

	void ScoreBoardDraw();
	void ComboDraw(const Transform2D & playerPos,float cameraRotate);
	// --- HP Bar (Life Bar) ---
	int lifeBarTexture_ = Novice::LoadTexture("./Textures/UI/lifebar.png");
	int lifeIconTexture_ = Novice::LoadTexture("./Textures/UI/life.png");

	// Bar and icon layout settings
	static constexpr int kMaxHP = 5;
	static constexpr int hpBarWidth_ = 440;
	static constexpr int hpBarHeight_ = 12;
	static constexpr int hpBarPosX_ = 640;  // Center of screen
	static constexpr int hpBarPosY_ = 704;  // Near bottom
	static constexpr int lifeIconWidth_ = 52;
	static constexpr int lifeIconHeight_ = 48;
	static constexpr int lifeIconSpacing_ = 12;
	static constexpr int lifeIconFirstX_ = hpBarPosX_ - (lifeIconWidth_ + lifeIconSpacing_) * (kMaxHP / 2);
	static constexpr int lifeIconY_ = hpBarPosY_ - 46; // Slightly above the bar

	// For HP icon pop/scale effect (for each life)
	float lifePopScale_[kMaxHP]{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	Easing lifePopEasing_[kMaxHP];

	// For HP icon shake effect (for each life)
	float lifeShakeTime_[kMaxHP]{};
	float lifeShakePower_[kMaxHP]{};
	bool  lifeShakeActive_[kMaxHP]{};

	// Track previous HP for edge detection
	int lastLifeCount_ = kMaxHP;

	void DrawHPBar(int hp); // Declare draw method

	// == Add these members in UI class ==
	float comboScale_ = 1.0f;                  // Current popup scale
	
	Easing comboScaleEasing_; 

	float comboShakeTime_ = 0.0f;              // Shake animation time
	float comboShakePower_ = 0.0f;             // Shake strength
	bool  comboEffectActive_ = false;          // Is effect active?

	int lastComboDrawn_ = 0;

	// --- Add these: ---
	Vector2 comboPopupBase_;      // The player position for this popup (set when combo increases)
	Vector2 comboPopupRand_;      // The random position offset around the player for popup

	float comboPopupRotation_ = 0.0f;  // The current (animated) rotation in degrees for combo popup
	float comboPopupRotationPower_ = 0.0f; // How strong the rotation is at peak

	// For max 7 digits, tracks scale of each digit popup
	std::array<float, 7> scoreDigitScales_{};
	std::array<Easing, 7> scoreDigitEasing_{};
	int lastDisplayedScore_ = 0; // For change detection
};