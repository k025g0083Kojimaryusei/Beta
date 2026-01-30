#include "EnemyEffect.h"

// You can call LoadTextures from your GamePlay constructor or enemy initialization, or lazily in Play().
EnemyEffect::EnemyEffect() {
    LoadTextures();
}

void EnemyEffect::LoadTextures() {
    // Load blue effect frames (replace with your actual paths)
    blueTextures_[0] = Novice::LoadTexture("./Textures/UI/particleBlue1.png");
    blueTextures_[1] = Novice::LoadTexture("./Textures/UI/particleBlue2.png");
    blueTextures_[2] = Novice::LoadTexture("./Textures/UI/particleBlue3.png");
    blueTextures_[3] = Novice::LoadTexture("./Textures/UI/particleBlue4.png");
    blueTextures_[4] = Novice::LoadTexture("./Textures/UI/particleBlue5.png");

    // Load red effect frames
    redTextures_[0] = Novice::LoadTexture("./Textures/UI/particleRed1.png");
    redTextures_[1] = Novice::LoadTexture("./Textures/UI/particleRed2.png");
    redTextures_[2] = Novice::LoadTexture("./Textures/UI/particleRed3.png");
    redTextures_[3] = Novice::LoadTexture("./Textures/UI/particleRed4.png");
    redTextures_[4] = Novice::LoadTexture("./Textures/UI/particleRed5.png");
}

void EnemyEffect::Play(const Vector2& pos, EffectType type) {
    pos_ = pos;
    type_ = type;
    currentFrame_ = 0;
    isPlaying_ = true;
}

void EnemyEffect::Update() {
    if (!isPlaying_) return;

    currentFrame_++;
    if (currentFrame_ > 5 * frameDuration_) {
        isPlaying_ = false;
    }
}

void EnemyEffect::Draw() {
    if (!isPlaying_) return;
    int curImageIdx = currentFrame_ / frameDuration_;
    if (curImageIdx > 4) curImageIdx = 4; // Clamp

    int tex = (type_ == BLUE_EXPLODE) ? blueTextures_[curImageIdx] : redTextures_[curImageIdx];
    // Draw centered at pos_
    // In EnemyEffect::Draw()
    Vector2 screenPos = CameraManager::GetInstance()->GetMainCamera().WorldToScreen(pos_);
    Novice::DrawSprite(
        static_cast<int>(screenPos.x) - 40, // Center the 80x80 effect
        static_cast<int>(screenPos.y) - 40,
        tex,
        1.0f, 1.0f,
        0.0f,
        WHITE
    );  
}