#include "UI.h"
#include <imgui.h>
#include "Easing.h"
#include <cmath>

UI::UI() {
	Init();
}

void UI::Init() {
	scoreBoardTransform_.Init(scoreTextPos, scoreBoardW, scoreBoardH);
	comboTransform_.Init({ 0.0f,0.0f }, comboSize.x, comboSize.y);
	lastLifeCount_ = kMaxHP;
	for (int i = 0; i < kMaxHP; ++i) {
		lifePopScale_[i] = 1.0f;
		lifePopEasing_[i].Init(1.0f, 1.0f, 1, EasingType::EASING_EASE_OUT_BACK);
		lifeShakeActive_[i] = false;
		lifeShakeTime_[i] = 0.0f;
	}
}

void UI::Update(const Vector2& playerWorldPos, int hp) {
	int currentCombo = ComboManager::GetInstance()->GetComboCount();

	int displayScore = Score::GetInstance()->GetDisplayScore();

	if (hp < lastLifeCount_) {
		// For each lost life, trigger its effect (in case HP drops by more than 1)
		for (int i = hp; i < lastLifeCount_; ++i) {
			lifePopEasing_[i].Init(1.5f, 0.0f, 20, EasingType::EASING_EASE_OUT_BACK);
			lifePopEasing_[i].Start();
			lifeShakeTime_[i] = 0.0f;
			lifeShakePower_[i] = 20.0f; // your shake strength
			lifeShakeActive_[i] = true;
		}
	}
	lastLifeCount_ = hp;

	// Per-icon (lost) pop/scale update
	for (int i = 0; i < kMaxHP; ++i) {
		if (lifePopEasing_[i].isMove)
			lifePopEasing_[i].Update();
		else if (lifePopScale_[i] != 0.0f)
			lifePopScale_[i] = 0.0f;
		// Update shake
		if (lifeShakeActive_[i]) {
			lifeShakeTime_[i] += 1.0f;
			if (lifeShakeTime_[i] > 15.0f) { // shake lasts 15 frames
				lifeShakeActive_[i] = false;
				lifeShakeTime_[i] = 0.0f;
			}
		}
	}

	// --- Detect changed digits and trigger pop per changed digit ---
	int prev = lastDisplayedScore_;
	int curr = displayScore;

	for (int i = 0; i < 7; ++i) {
		int prevDigit = prev % 10;
		int currDigit = curr % 10;
		if (prevDigit != currDigit) {
			// Digit changed: kick popup effect for this digit!
			scoreDigitEasing_[i].Init(1.2f, 1.0f, 20, EasingType::EASING_EASE_OUT_BACK);
			scoreDigitEasing_[i].Start();
		}
		prev /= 10;
		curr /= 10;
	}

	lastDisplayedScore_ = displayScore;

	// Tick easings
	for (int i = 0; i < 7; ++i)
		scoreDigitEasing_[i].Update();

	if (currentCombo > lastComboDrawn_) {
		// Combo increased! Start pop+shake effect
		comboScaleEasing_.Init(5.0f, 1.0f, 25, EasingType::EASING_EASE_OUT_BACK); // Tweak strength as desired
		comboScaleEasing_.Start();

		comboShakeTime_ = 0.0f;
		comboShakePower_ = 16.0f; // set shake amplitude (pixels)
		comboEffectActive_ = true;

		comboPopupBase_ = playerWorldPos;

		float angle = float(rand() % 360) * 3.1415926f / 180.0f;     // random angle 0~2pi
		float distance = 52.0f + float(rand() % 36);                  // 52~87 px
		comboPopupRand_ = { std::cosf(angle) * distance, std::sinf(angle) * distance };

		// Set max rotation. Try 27–45 for a big swing, 10–20 for soft.
		comboPopupRotationPower_ = (rand() % 2 == 0 ? 1.0f : -1.0f) * (18.0f + rand() % 13); // Randomly -18~+30 deg
		comboPopupRotation_ = comboPopupRotationPower_; // Start at peak
	}
	lastComboDrawn_ = currentCombo;
	Score::GetInstance()->Update();
}

void UI::Draw(const Transform2D& playerPos,float cameraRotate, int hp) {
	ScoreBoardDraw();
	ComboDraw(playerPos,cameraRotate);
	DrawHPBar(hp);

	//ImGui::DragFloat2("position", &scoreTextPos.x, 0.1f);
	scoreBoardTransform_.Init(scoreTextPos, scoreBoardW, scoreBoardH);

	Quad screenSB = CameraManager::GetInstance()->GetUICamera().WorldToScreen(scoreBoardTransform_);
	Novice::DrawQuad(
		static_cast<int>(screenSB.v[0].x+43 + 75), static_cast<int>(screenSB.v[0].y),
		static_cast<int>(screenSB.v[1].x+43 + 75), static_cast<int>(screenSB.v[1].y),
		static_cast<int>(screenSB.v[2].x+43 + 75), static_cast<int>(screenSB.v[2].y),
		static_cast<int>(screenSB.v[3].x+43 + 75), static_cast<int>(screenSB.v[3].y),
		0, 0,
		static_cast<int>(scoreBoardTransform_.width),
		static_cast<int>(scoreBoardTransform_.height),
		scoreBoardTextureHandle_, WHITE
	);
}

void UI::ScoreBoardDraw() {
	//ImGui::DragFloat2("Numberpos", &numberPos.x, 0.1f);
  
	const int kMaxDigits = 7;

	//int currentScore = Score::GetInstance()->GetDisplayScore();

	// ★ここ！ 数字の「幅」に「どれくらい隙間を空けるか」を足す
	const float kSpacing = 4.0f; // 4ピクセル分空ける（お好みで調整）
	const float kOffsetPerDigit = numberSize.x + kSpacing;


	// basePos も間隔を含めた全体の幅で再計算
	Vector2 basePos = { numberPos.x + (kOffsetPerDigit * (kMaxDigits - 1) / 2.0f), numberPos.y };
	int score = Score::GetInstance()->GetDisplayScore();

	for (int i = 0; i < kMaxDigits; i++) {
		int digit = score % 10;
		score /= 10;

		Vector2 digitPos = { basePos.x - (i * kOffsetPerDigit), basePos.y };
		Transform2D digitTransform;
		digitTransform.Init(digitPos, numberSize.x, numberSize.y);

		// --- get popup scale for this digit ---
		float digitScale = scoreDigitEasing_[i].isMove ? scoreDigitEasing_[i].easingRate : 1.0f;
		digitTransform.scale = { digitScale, digitScale };

		Quad screen = CameraManager::GetInstance()->GetUICamera().WorldToScreen(digitTransform);

		Novice::DrawQuad(
			static_cast<int>(screen.v[0].x + 75), static_cast<int>(screen.v[0].y),
			static_cast<int>(screen.v[1].x + 75), static_cast<int>(screen.v[1].y),
			static_cast<int>(screen.v[2].x + 75), static_cast<int>(screen.v[2].y),
			static_cast<int>(screen.v[3].x + 75), static_cast<int>(screen.v[3].y),
			0, 0, static_cast<int>(numberSize.x), static_cast<int>(numberSize.y),
			numbersTextureHandle[digit], 0xFFFFFFFF
		);
	}
}


void UI::ComboDraw(const Transform2D& /*playerPos*/, float cameraRotate) {
	ComboManager* combo = ComboManager::GetInstance();
		comboTransform_.rotation = cameraRotate;

	// 2コンボ以上の時だけ、タイマーが残っている間に表示
	if (combo->GetComboCount() >= 1 && combo->GetTimer() > 0) {

		// Calculate combo popup position
		Vector2 baseComboPos;
		if (comboEffectActive_) {
			// Animate the combo popup from player outward (and back in)
			float t = 1.0f - std::fmin(comboScaleEasing_.easingRate, 1.0f);
			// t: 1 at start, 0 at end of effect
			baseComboPos.x = comboPopupBase_.x + comboPopupRand_.x * (0.5f + 0.5f * t);
			baseComboPos.y = comboPopupBase_.y + comboPopupRand_.y * (0.5f + 0.5f * t);
			float rotationDecay = std::fmax(1.0f - comboShakeTime_ / 12.0f, 0.0f); // match to shake
			comboPopupRotation_ = comboPopupRotationPower_ * rotationDecay;
		}
		else {
			baseComboPos.x = comboPopupBase_.x + comboPopupRand_.x * 0.5f;
			baseComboPos.y = comboPopupBase_.y + comboPopupRand_.y * 0.5f;
			comboPopupRotation_ = 0.0f;
		}

		/*switch (GameConfig::GetInstance()->GetStageState()) {


		case GameConfig::TOP:
			comboPos = { playerPos.worldPos.x, playerPos.worldPos.y + offset.y };
			break;

		case GameConfig::BOTTOM:
			comboPos = { playerPos.worldPos.x, playerPos.worldPos.y - offset.y };
			break;

		case GameConfig::LEFT:
			comboPos = { playerPos.worldPos.x - offset.x, playerPos.worldPos.y};
			break;
	
		case GameConfig::RIGHT:
			comboPos = { playerPos.worldPos.x  + offset.x, playerPos.worldPos.y};

			break;
		
		}*/

		//comboTransform_.worldPos = comboPos;
		// ... inside ComboDraw()
		if (combo->GetComboCount() >= 1 && combo->GetTimer() > 0) {
			// === Animate scale and shake ===
			float drawScale = 1.0f;
			float shakeX = 0.0f, shakeY = 0.0f;
			if (comboEffectActive_) {
				comboScaleEasing_.Update();
				drawScale = comboScaleEasing_.easingRate;

				comboShakeTime_ += 1.0f;
				float shakeDecay = std::fmax(1.0f - comboShakeTime_ / 12.0f, 0.0f); // shake lasts 12 frames
				shakeX = std::sinf(comboShakeTime_ * 0.38f) * comboShakePower_ * shakeDecay;
				shakeY = std::cosf(comboShakeTime_ * 0.56f) * comboShakePower_ * shakeDecay;

				if (shakeDecay <= 0.0f && !comboScaleEasing_.isMove) {
					comboEffectActive_ = false; // Done animating
				}
			}

			// === Calc position for popup+shake ===
			//Vector2 baseComboPos = comboPos; // This comes from your logic as before
			Vector2 drawPos = { baseComboPos.x + shakeX, baseComboPos.y + shakeY };

			// Center the scaling (your transform); adjust as needed
			Transform2D comboTransform = comboTransform_;
			comboTransform.worldPos = drawPos;
			comboTransform.scale = { drawScale, drawScale };
			
			float rotation = comboPopupRotation_ - cameraRotate; // your normal effect
			auto state = GameConfig::GetInstance()->GetStageState();
			if (state == GameConfig::LEFT || state == GameConfig::RIGHT) {
				rotation += 180.0f;
			}
			else
			{
				rotation = comboPopupRotation_ - cameraRotate;
			}
			comboTransform.rotation = rotation;

			Quad screenPos = CameraManager::GetInstance()->GetMainCamera().WorldToScreen(comboTransform);

			Novice::DrawQuad(
				static_cast<int>(screenPos.v[0].x), static_cast<int>(screenPos.v[0].y),
				static_cast<int>(screenPos.v[1].x), static_cast<int>(screenPos.v[1].y),
				static_cast<int>(screenPos.v[2].x), static_cast<int>(screenPos.v[2].y),
				static_cast<int>(screenPos.v[3].x), static_cast<int>(screenPos.v[3].y),
				0, 0,
				static_cast<int>(comboSize.x),
				static_cast<int>(comboSize.y),
				ComboTextureHandle_[combo->GetComboCount()], WHITE
			);
		}
	}
}

void UI::DrawHPBar(int hp) {
	Novice::DrawSprite(hpBarPosX_ - hpBarWidth_ / 2, hpBarPosY_ + 5, lifeBarTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	int iconsStartX = hpBarPosX_ - ((lifeIconWidth_ + lifeIconSpacing_) * kMaxHP - lifeIconSpacing_) / 2;

	for (int i = 0; i < kMaxHP; ++i) {
		float scale = 1.0f;
		float shakeOffset = 0.0f;
		// Animate lost life ONLY when disappearing
		if (i >= hp && lifePopEasing_[i].isMove) {
			scale = lifePopEasing_[i].easingRate;
			if (lifeShakeActive_[i]) {
				float decay = 1.0f - (lifeShakeTime_[i] / 15.0f);
				shakeOffset = std::sinf(lifeShakeTime_[i] * 0.6f + i) * lifeShakePower_[i] * decay;
			}
		}
		// Only draw up to life you have
		if (i < hp) {
			Novice::DrawSprite(
				iconsStartX + i * (lifeIconWidth_ + lifeIconSpacing_),
				lifeIconY_ + 3,
				lifeIconTexture_,
				scale, scale, 0.0f,
				WHITE);
		}
		// Optional/advanced: show fading/disappearing icon as it pops away when lost
		else if (lifePopEasing_[i].isMove) {
			Novice::DrawSprite(
				(int)(iconsStartX + i * (lifeIconWidth_ + lifeIconSpacing_) + shakeOffset),
				(int)(lifeIconY_ + 3),
				lifeIconTexture_,
				scale, scale, 0.0f,
				0xCCFFFFFF // faded white (optionally sprite transparent)
			);
		}
	}
}