#include "Stage.h"
#include <Novice.h>

Stage::Stage() {
	stageTransform_.Init({ 640.0f,360.0f }, stageWidth_, stageHeight_);
	enemySpawnRangeTransform_.Init({ 640.0f,360.0f }, enemySpawnRangeWidth_, enemySpawnRangeHeight_);
}

void Stage::Draw() {

	Quad screen = CameraManager::GetInstance()->GetMainCamera().WorldToScreen(stageTransform_);
	Novice::DrawQuad(
		static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
		static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
		static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
		static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
		0, 0,
		static_cast<int>(stageTransform_.width),
		static_cast<int>(stageTransform_.height),
		stageTextureHandle_,WHITE
	);


}