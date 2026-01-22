#include "TitleScene.h"
#include <Novice.h>

TitleScene::TitleScene(SceneManager* manager)
	: sceneManager(manager), selectedIndex(0), bg_(), logo_()
{
}

void TitleScene::Update(char* keys, char* preKeys)
{

	bg_.Update();
	logo_.Update();

	if (!preKeys[DIK_DOWN] && keys[DIK_DOWN]) {
		selectedIndex++;
		if (selectedIndex > 2) {
			selectedIndex = 0;
		}
	}

	if (!preKeys[DIK_UP] && keys[DIK_UP])
	{
		selectedIndex--;
		if (selectedIndex < 0) {
			selectedIndex = 2;
		}
	}

	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		switch (selectedIndex) {
		case 0: // Play
			sceneManager->ChangeScene(SceneType::Play);
			break;
		case 1: // Credit
			sceneManager->ChangeScene(SceneType::Credit);
			break;
		case 2: // Rank
			sceneManager->ChangeScene(SceneType::Ranking);
			break;
		}
	}
}

void TitleScene::Draw()
{
	bg_.Draw();
	logo_.Draw();

	const int baseX = 100;
	int y = 200;

	// Play
	if (selectedIndex == 0) {
		Novice::ScreenPrintf(baseX, y, "> Play");
	}
	else {
		Novice::ScreenPrintf(baseX, y, "  Play");
	}
	y += 30;

	// Credit
	if (selectedIndex == 1) {
		Novice::ScreenPrintf(baseX, y, "> Credit");
	}
	else {
		Novice::ScreenPrintf(baseX, y, "  Credit");
	}
	y += 30;

	// Rank
	if (selectedIndex == 2) {
		Novice::ScreenPrintf(baseX, y, "> Rank");
	}
	else {
		Novice::ScreenPrintf(baseX, y, "  Rank");
	}
}