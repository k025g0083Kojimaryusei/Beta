#pragma once
#include <Novice.h>
#include "Object2D.h"
#include "CameraManager.h"
#include "Camera2D.h"

class EnemyEffect {
public:
    enum EffectType { BLUE_EXPLODE, RED_EXPLODE };

    EnemyEffect();

    // Start playing an effect
    void Play(const Vector2& pos, EffectType type);

    // Update animation frame
    void Update();

    // Draw current animation frame
    void Draw();

    // Is effect still playing?
    bool IsPlaying() const { return isPlaying_; }

private:
    bool isPlaying_ = false;
    int currentFrame_ = 0;
    int frameDuration_ = 5; // How many frames per image
    Vector2 pos_;
    EffectType type_;
    int blueTextures_[5]{};
    int redTextures_[5]{};
    void LoadTextures();
};