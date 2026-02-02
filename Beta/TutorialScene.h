#pragma once
#include "Scene.h"
#include "Easing.h"
#include "TitleBackground.h"
#include "Score.h"
#include "TutorialBackground.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "GamePlay.h"


class TutorialScene : public Scene
{
public:
	TutorialScene(SceneManager* manager);
	void Update(char* keys, char* preKeys) override;
	void Draw() override;
	

private:
	SceneManager* sceneManager;
	TitleBackground bg_;
	TutorialBackground tutorialBg_;
	int bgTexture_;
	int enterTexture_;
	int posX_ = 640;
	int posY_ = 360;
	int width_ = 1280;
	int height_ = 720;
	int enterX_ = 600;
	int enterY_ = 620;
	int enterW_ = 78;
	int enterH_ = 86;
	int frameCount_ = 0;
	float hoverOffset_ = 0.0f;

	// In TutorialScene.h (private section)

	float bgBreathPhase_ = 0.0f;
	float bgBreathSpeed_ = 0.012f;
	Easing breathEasing_;
	bool isBreathForward_ = true;


	GamePlay miniGamePlay;

	char keys_[256]{};

	// Key UI handles: [W, A, S, D][state 0:up, 1:down]
	int wasdTexHandles[4][2]{};
};