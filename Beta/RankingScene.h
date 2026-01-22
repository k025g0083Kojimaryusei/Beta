#pragma once
#include "Scene.h"

class RankingScene : public Scene
{
public:
	RankingScene(SceneManager* manager);
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;
};

