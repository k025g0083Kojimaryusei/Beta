#pragma once
#include "Scene.h"
#include "GamePlay.h"

class PlayScene : public Scene
{
public:
	PlayScene(SceneManager* manager);

	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;
	GamePlay gamePlay_;
};