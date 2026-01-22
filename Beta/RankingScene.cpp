#include "RankingScene.h"
#include <Novice.h>

RankingScene::RankingScene(SceneManager* manager)
	: sceneManager(manager)
{
}

void RankingScene::Update(char* keys, char* preKeys)
{
	if (!preKeys[DIK_B] && keys[DIK_B])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
}

void RankingScene::Draw()
{
	Novice::ScreenPrintf(100, 100, "Ranking Scene");
}