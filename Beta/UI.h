#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include "Score.h"
#include "ComboManager.h"
#include <Novice.h>
#include "GameConfig.h"
class UI {
public:

	UI();
	void Init();
	void Update();
	void Draw(const Transform2D & playerPos,float cameraRotate);

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
};