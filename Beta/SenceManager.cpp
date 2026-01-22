#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "CreditScene.h"
#include "RankingScene.h"

SceneManager::SceneManager()
	: currentScene(nullptr), currentType(SceneType::Title)
{
	ChangeScene(SceneType::Title);
}

SceneManager::~SceneManager()
{
	if (currentScene)
	{
		delete currentScene;
	}
}

void SceneManager::ChangeScene(SceneType newType)
{
	delete currentScene;
	currentScene = nullptr;
	currentType = newType;
	
	switch (newType)
	{
	case SceneType::Title:
		currentScene = new TitleScene(this);
		break;
	case SceneType::Play:
		currentScene = new PlayScene(this);
		break;
	case SceneType::Credit:
		currentScene = new CreditScene(this);
		break;
	case SceneType::Ranking:
		currentScene = new RankingScene(this);
		break;
	}
}

void SceneManager::UpdateCurrentScene(char* keys, char* preKeys)
{
	if (currentScene)
	{
		currentScene->Update(keys, preKeys);
	}
}

void SceneManager::DrawCurrentScene()
{
	if (currentScene)
	{
		currentScene->Draw();
	}
}