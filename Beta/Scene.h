#pragma once
#include "Easing.h"

enum class SceneType
{
	Title,
	Play,
	Credit,
	Ranking
};

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Update(char* keys, char* preKeys) = 0;
	virtual void Draw() = 0;
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void ChangeScene(SceneType newType);
	void UpdateCurrentScene(char* keys, char* preKeys);
	void DrawCurrentScene();

	SceneType GetCurrentSceneType() const { return currentType_; }

private:
	Scene* currentScene_ = nullptr;
	SceneType currentType_ = SceneType::Title;

	bool inTransition_ = false;
	bool switchingDone_ = false;
	SceneType nextType_ = SceneType::Title;

	int phase_ = 0;
	int transitionTotalFrame_ = 10;

	int pauseTimer_ = 0;
	int pauseDuration_ = 45;

	int radialGlowTex_ = 0; 

	Easing vertEasing_;
	Easing horizonEasing_;

	void StartTransition( SceneType to);
	void UpdateTransition();
	void DrawTransitionOverlay();

	int bgTexture_ = 0;
	
};


