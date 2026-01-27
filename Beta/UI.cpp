#include "UI.h"
#include <imgui.h>

UI::UI() {
	
	Init();
}

void UI::Init() {
	scoreBoardTransform_.Init(scoreTextPos, scoreBoardW, scoreBoardH);
}

void UI::Update() {
}

void UI::Draw() {
    ScoreBoardDraw();
	ImGui::DragFloat2("position", &scoreTextPos.x, 0.1f);
	scoreBoardTransform_.Init(scoreTextPos, scoreBoardW, scoreBoardH);

	Quad screenSB = CameraManager::GetInstance()->GetUICamera().WorldToScreen(scoreBoardTransform_);
	Novice::DrawQuad(
		static_cast<int>(screenSB.v[0].x), static_cast<int>(screenSB.v[0].y),
		static_cast<int>(screenSB.v[1].x), static_cast<int>(screenSB.v[1].y),
		static_cast<int>(screenSB.v[2].x), static_cast<int>(screenSB.v[2].y),
		static_cast<int>(screenSB.v[3].x), static_cast<int>(screenSB.v[3].y),
		0, 0,
		static_cast<int>(scoreBoardTransform_.width),
		static_cast<int>(scoreBoardTransform_.height),
		scoreBoardTextureHandle_, WHITE
	);
}

void UI::ScoreBoardDraw() {
    ImGui::DragFloat2("Numberpos", &numberPos.x, 0.1f);
    int currentScore = Score::GetInstance()->GetDisplayScore();

    const int kMaxDigits = 7;
    

    // ★ここ！ 数字の「幅」に「どれくらい隙間を空けるか」を足す
    const float kSpacing = 4.0f; // 4ピクセル分空ける（お好みで調整）
    const float kOffsetPerDigit = numberSize.x + kSpacing;


    // basePos も間隔を含めた全体の幅で再計算
    Vector2 basePos = { numberPos.x + (kOffsetPerDigit * (kMaxDigits - 1) / 2.0f),numberPos.y };
    for (int i = 0; i < kMaxDigits; i++) {
        int digit = currentScore % 10;
        currentScore /= 10;

        // ★計算で kDigitWidth の代わりに kOffsetPerDigit を使う
        Vector2 digitPos = { basePos.x - (i * kOffsetPerDigit), basePos.y };
        Transform2D digitTransform;
        digitTransform.Init(digitPos, numberSize.x, numberSize.y);

        // ④ 描画（Novice::DrawQuad を使う場合）
        // local座標をworldPos（digitPos）を基準に変換して描画

		Quad screen = CameraManager::GetInstance()->GetUICamera().WorldToScreen(digitTransform);

        Novice::DrawQuad(
			static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
			static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
			static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
			static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
            0, 0, static_cast<int>(numberSize.x), static_cast<int>(numberSize.y),
            numbersTextureHandle[digit], // 抽出した数字のハンドル
            0xFFFFFFFF
        );
    }
}