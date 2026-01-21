#include "Enemy.h"
#include <random>

Enemy::Enemy() {

}

Enemy::Enemy(const Transform2D& spawnStage) {
	Init(spawnStage);
}

void Enemy::Init(const Transform2D& spawnStage) {
	SpawnEnemy(spawnStage);
}

void Enemy::Update(const Transform2D& spawnStage,float cameraRotate) {
	Move();
	ClampToStage(spawnStage);
	RotateTexture(cameraRotate);
}

void Enemy::Draw() {
	for (const EnemyData& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
		
		
		Quad screen = Camera2D::GetInstance()->WorldToScreen(enemy.transform);
		Novice::DrawQuad(
			static_cast<int>(screen.v[0].x), static_cast<int>(screen.v[0].y),
			static_cast<int>(screen.v[1].x), static_cast<int>(screen.v[1].y),
			static_cast<int>(screen.v[2].x), static_cast<int>(screen.v[2].y),
			static_cast<int>(screen.v[3].x), static_cast<int>(screen.v[3].y),
			0, 0,
			static_cast<int>(enemy.transform.width),
			static_cast<int>(enemy.transform.height),
			count1Texture, WHITE
		);
	}
}

//敵スポーン処理
void Enemy::SpawnEnemy(const Transform2D& spawnStage) {
	for (int i = 0; i < maxEnemiesSpawnCount; i++) {
		EnemyData newEnemy;

		float enemyHW = newEnemy.transform.width / 2.0f;
		float enemyHH = newEnemy.transform.height / 2.0f;
		float spawnHW = spawnStage.width / 2.0f;
		float spawnHH = spawnStage.height / 2.0f;
		float rangeX = spawnHW - enemyHW;
		float rangeY = spawnHH - enemyHH;
		float spawnX = GetRandomFloat(-rangeX, rangeX);
		float spawnY = GetRandomFloat(-rangeY, rangeY);

		Vector2 finalSpawnPos = { spawnStage.worldPos.x + spawnX, spawnStage.worldPos.y + spawnY };
		newEnemy.transform.Init(finalSpawnPos, newEnemy.size.x, newEnemy.size.y);
		newEnemy.moveType = static_cast<int>(GetRandomFloat(0.0f, 2.0f)); //0か1をランダムに設定

		newEnemy.moveType = GetRandomInt(0, 2); // 0か1

		// 最初に向かう方向をランダムに決めて固定する（例：-1.0か1.0）
		if (newEnemy.moveType == 0) {
			newEnemy.velocity.x = (GetRandomFloat(0.0f, 1.0f) > 0.5f) ? 1.0f : -1.0f;
			newEnemy.velocity.y = 0.0f;
		} else {
			newEnemy.velocity.x = 0.0f;
			newEnemy.velocity.y = (GetRandomFloat(0.0f, 1.0f) > 0.5f) ? 1.0f : -1.0f;
		}

		newEnemy.isActive = true;
		enemies.push_back(newEnemy);

	}
}

void Enemy::Move() {
	for (EnemyData& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
		enemy.transform.worldPos.x += enemy.velocity.x * enemy.speed.x;
		enemy.transform.worldPos.y += enemy.velocity.y * enemy.speed.y;
	}
}

void Enemy::ClampToStage(const Transform2D& spawnStage) {
	for (EnemyData& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}

		// 半分のサイズを算出（SpawnEnemyと同様の考え方）
		float enemyHW = enemy.transform.width / 2.0f;
		float enemyHH = enemy.transform.height / 2.0f;
		float spawnHW = spawnStage.width / 2.0f;
		float spawnHH = spawnStage.height / 2.0f;

		// ステージの上下左右の限界座標を計算
		float minX = spawnStage.worldPos.x - (spawnHW - enemyHW);
		float maxX = spawnStage.worldPos.x + (spawnHW - enemyHW);
		float minY = spawnStage.worldPos.y - (spawnHH - enemyHH);
		float maxY = spawnStage.worldPos.y + (spawnHH - enemyHH);

		// X軸のクランプと反転
		if (enemy.transform.worldPos.x < minX) {
			enemy.transform.worldPos.x = minX;
			enemy.velocity.x *= -1.0f; // 左端に当たったら右へ反転
		} else if (enemy.transform.worldPos.x > maxX) {
			enemy.transform.worldPos.x = maxX;
			enemy.velocity.x *= -1.0f; // 右端に当たったら左へ反転
		}

		// Y軸のクランプと反転
		if (enemy.transform.worldPos.y < minY) {
			enemy.transform.worldPos.y = minY;
			enemy.velocity.y *= -1.0f; // 下端に当たったら上へ反転
		} else if (enemy.transform.worldPos.y > maxY) {
			enemy.transform.worldPos.y = maxY;
			enemy.velocity.y *= -1.0f; // 上端に当たったら下へ反転
		}
	}
}

void Enemy::RotateTexture(float cameraRotate) {
	for (EnemyData& enemy : enemies) {
		if (!enemy.isActive) {
			continue;
		}
		enemy.transform.rotation = cameraRotate;
	}
}

float Enemy::GetRandomFloat(float min, float max) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}

int Enemy::GetRandomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max - 1);
	return dist(mt);
}