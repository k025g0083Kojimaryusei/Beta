#pragma once
#include "Object2D.h"
#include "CameraManager.h"
#include <Novice.h>

class Background {
public:
	Background();
	void Init();
	void Draw();
private:
	Transform2D backgroundTransform_;
	float backgroundW = 1300.0f;
	float backgroundH = 740.0f;
	int backgroundTextureHandle_ = Novice::LoadTexture("./Textures/UI/BackGround/back5.png");
};