#pragma once
#include "Scene.h"
#include "TitleBackground.h"
#include "TitleLogo.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneManager* manager);

	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;
	int selectedIndex = 0;

	TitleBackground bg_;
	TitleLogo logo_;
};
