#pragma once
#include "Scene.h"

class CreditScene : public Scene
{
public:
	CreditScene(SceneManager* manager);
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	SceneManager* sceneManager;

};
