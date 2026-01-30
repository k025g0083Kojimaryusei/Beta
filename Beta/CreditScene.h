#pragma once
#include "Scene.h"
#include "Easing.h"
#include "TitleBackground.h"

class CreditScene : public Scene
{
public:
	CreditScene(SceneManager* manager);
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;
	TitleBackground bg_;

	int bgTexture_;
	int enterTexture_;           // <-- Add handle for enter image

	int posX_ = 640;
	int posY_ = 360;
	int width_ = 1280;
	int height_ = 720;

	int enterX_ = 600;           // <-- Adjust these to position under "Program:"
	int enterY_ = 620;
	int enterW_ = 78;            // <-- Adjust size to fit the scene (original PNG is 64x58, see below for scaling)
	int enterH_ = 86;

	int frameCount_ = 0;         // <- For hover animation
	float hoverOffset_ = 0.0f;

	// In CreditScene.h (private section)
	float bgBreathPhase_ = 0.0f;
	float bgBreathSpeed_ = 0.012f;  // Breathing speed (adjustable)

	Easing breathEasing_;
	bool isBreathForward_ = true; // to loop breathing

	//float bgColorPhase_ = 0.0f;
	//float bgColorSpeed_ = 0.018f;   // Tint speed (adjustable)
};