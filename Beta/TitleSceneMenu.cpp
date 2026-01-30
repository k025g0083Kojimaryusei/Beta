#include "TitleScene.h"

TitleScene::TitleScene() {
	
	// PLAYボタン（Aグループ）
	btnTex_[0][0] = Novice::LoadTexture("../title/Aselect1.png");
	btnTex_[0][1] = Novice::LoadTexture("../title/Aselect2.png");
	btnTex_[0][2] = Novice::LoadTexture("../title/Aselect3.png");

	// RANKINGボタン（Bグループ）
	btnTex_[1][0] = Novice::LoadTexture("../title/Bselect1.png");
	btnTex_[1][1] = Novice::LoadTexture("../title/Bselect2.png");
	btnTex_[1][2] = Novice::LoadTexture("../title/Bselect3.png");

	// CREDITボタン（Cグループ）
	btnTex_[2][0] = Novice::LoadTexture("../title/Cselect1.png");
	btnTex_[2][1] = Novice::LoadTexture("../title/Cselect2.png");
	btnTex_[2][2] = Novice::LoadTexture("../title/Cselect3.png");

	// 選択バーとカーソル
	BchoiceTex_[0] = Novice::LoadTexture("../title/bar1.png");
	BchoiceTex_[1] = Novice::LoadTexture("../title/bar2.png");
	BchoiceTex_[2] = Novice::LoadTexture("../title/bar3.png");
	choiceTex_ = Novice::LoadTexture("../title/choice.png");

	// 座標の初期化
	AchoiceX_[0] = 756;
	AchoiceY_[0] = 126;
	AchoiceX_[1] = 756;
	AchoiceY_[1] = 306;
	AchoiceX_[2] = 756;
	AchoiceY_[2] = 490;

	BChoiceX_[0] = 676;
	BChoiceY_[0] = 156;
	BChoiceX_[1] = 676;
	BChoiceY_[1] = 338;
	BChoiceX_[2] = 676;
	BChoiceY_[2] = 524;

	// 変数の初期化
	selectedIndex_ = 0;
	cursorCurrentY_ = (float)AchoiceY_[0];
	noiseTimer_ = 0;
	nextScene_ = SCENE_TITLE;
}

TitleScene::~TitleScene() {}

void TitleScene::Update(char* keys, char* preKeys) {
	//  選択移動
	if (keys[DIK_UP] && !preKeys[DIK_UP]) {
		selectedIndex_ = (selectedIndex_ - 1 + 3) % 3;
	}
	if (keys[DIK_DOWN] && !preKeys[DIK_DOWN]) {
		selectedIndex_ = (selectedIndex_ + 1) % 3;
	}

	// カーソルのイージング
	cursorCurrentY_ += ((float)AchoiceY_[selectedIndex_] - cursorCurrentY_) * kEasingSpeed;

	// ノイズタイマー
	noiseTimer_++;
	if (noiseTimer_ >= 60) {
		noiseTimer_ = 0;
	}

	// 決定
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (selectedIndex_ == 0)
			nextScene_ = SCENE_PLAY;
		if (selectedIndex_ == 1)
			nextScene_ = SCENE_RAMKING;
		if (selectedIndex_ == 2)
			nextScene_ = SCENE_CREDIT;
	}
}

void TitleScene::Draw() {
	// 背景
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

	// 選択バーの描画
	Novice::DrawSprite(BChoiceX_[selectedIndex_], BChoiceY_[selectedIndex_], BchoiceTex_[selectedIndex_], 1.0f, 1.0f, 0.0f, WHITE);

	// カーソルの描画
	Novice::DrawSprite(AchoiceX_[0] - 80, (int)cursorCurrentY_ + 30, choiceTex_, 1.0f, 1.0f, 0.0f, WHITE);

	// 文字の描画
	for (int i = 0; i < 3; i++) {
		int frame = 0;
		if (i == selectedIndex_ && noiseTimer_ < 15) {
			frame = (noiseTimer_ / 5) % 3;
		}
		Novice::DrawSprite(AchoiceX_[i], AchoiceY_[i], btnTex_[i][frame], 1.0f, 1.0f, 0.0f, WHITE);
	}
}