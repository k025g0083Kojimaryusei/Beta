#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include "Score.h"

#include <Novice.h>


class UI {
public:

	UI();
	void Init();
	void Update();
	void Draw();

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

	int ComboTextureHandle_[10] = {
		Novice::LoadTexture("./Textures/UI/Combo/No0.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No1.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No2.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No3.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No4.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No5.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No6.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No7.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No8.png"),
		Novice::LoadTexture("./Textures/UI/Combo/No9.png")
	};
	void ScoreBoardDraw();
};