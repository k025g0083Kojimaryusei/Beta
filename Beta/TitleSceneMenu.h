#pragma once
#include <Novice.h>

// シーンの定義
enum GameScene {
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RAMKING,
	SCENE_CREDIT,
};

class TitleScene {
public:
	TitleScene();  // コンストラクタ
	~TitleScene(); // デストラクタ

	void Update(char* keys, char* preKeys);
	void Draw();

	// 次のシーンを確認する
	GameScene GetNextScene() const { return nextScene_; }

private:
	// 画像ハンドル
	int btnTex_[3][3];
	int BchoiceTex_[3];
	int choiceTex_;

	// 座標
	int AchoiceX_[3];
	int AchoiceY_[3];
	int BChoiceX_[3];
	int BChoiceY_[3];

	// 制御変数
	int selectedIndex_;
	float cursorCurrentY_;
	const float kEasingSpeed = 0.1f;
	int noiseTimer_;

	GameScene nextScene_; // 遷移先
};