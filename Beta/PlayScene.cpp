#include "PlayScene.h"

PlayScene::PlayScene(SceneManager* manager)
	: sceneManager(manager), gamePlay_()
{
	SoundManager::Get().Load("PlayBgm", "./Sounds/gamePlay.mp3");
	SoundManager::Get().Play("PlayBgm", 1.0f, true);
}

void PlayScene::Update(char* keys, char* preKeys)
{
	gamePlay_.Update(keys, preKeys);
	

	if (gamePlay_.GetPlayerHP() <= 0)
	{
		SoundManager::Get().Stop("PlayBgm");
		sceneManager->ChangeScene(SceneType::Score);
	}
}

void PlayScene::Draw()
{
	gamePlay_.Draw();
	
}	
