#include "TitleLogo2.h"
#include <Novice.h>
#include <cmath>
#include <tuple>
#include "SoundManager.h"

TitleLogo2::TitleLogo2() {
    texWhite_ = Novice::LoadTexture("./Textures/UI/Title/Logo/titl1.png");
    texCyan_  = Novice::LoadTexture("./Textures/UI/Title/Logo/titl2.png");
    texRed_   = Novice::LoadTexture("./Textures/UI/Title/Logo/titl3.png");

    // EasingType is the same as your existing TitleScene (InOutSine)
    scaleEasing_.Init(0.0f, 1.0f, introDuration_, EasingType::EASING_EASE_IN_OUT_SINE);
    scaleEasing_.Start();

    SoundManager::Get().Load("Intro", "./Sounds/intro.mp3");
    
}

void TitleLogo2::Update() {
   
    frameCount_++;

    // Scale and rotation in intro
    if (!isIntroFinished_) {
        scaleEasing_.Update();

        // Smoothly spin from rotation_ = -360 up to 0.
        float t = scaleEasing_.easingRate; // Ease [0~1]
        rotation_ = rotationAmount_ * (1.0f - t);

        // Done?
        if (t >= 1.0f - 0.001f && !scaleEasing_.isMove) {
            isIntroFinished_ = true;
            rotation_ = 0.0f;
        }
    } else {
        // Instead of hover, just let the time run for shaking effect.
        shakeTimer_ += 3.0f;
		
    }
}

void TitleLogo2::Draw() {
    // Logo center and size
    float logoScale = scaleEasing_.easingRate;
    if (logoScale <= 0.0f) return;

    int cx = centerX_; // logo center x
    int cy = centerY_; // logo center y
    float angle = rotation_ * 3.14159265f / 180.0f; // radians
    float baseScale = 1.0f;
    int w = logoW_;
    int h = logoH_;

    //--- Glitch shake, still just uses regular DrawSprite for BG layers ---
    if (isIntroFinished_) {
        float shakeX = std::sinf(shakeTimer_ * 0.29f) * shakeAmount_;
        float shakeY = std::cosf(shakeTimer_ * 0.16f) * shakeAmount_;

        // Cyan
        Novice::DrawSprite(
            int(cx - w * 0.5f * baseScale + shakeX + 6),
            int(cy - h * 0.5f * baseScale + shakeY),
            texCyan_,
            baseScale, baseScale,
            0.0f, 0xA0FFFFFF
        );
        // Red
        Novice::DrawSprite(
            int(cx - w * 0.5f * baseScale - shakeX - 6),
            int(cy - h * 0.5f * baseScale - shakeY),
            texRed_,
            baseScale, baseScale,
            0.0f, 0xA0FFFFFF
        );
    }

    // --- Main logo: use Quad for center rotation ---
    float sw = w * 0.5f * logoScale; // half width after scale
    float sh = h * 0.5f * logoScale; // half height after scale
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    // Top-left
    int x1 = int(cx + (-sw) * cosA - (-sh) * sinA);
    int y1 = int(cy + (-sw) * sinA + (-sh) * cosA);
    // Top-right
    int x2 = int(cx + (sw)*cosA - (-sh) * sinA);
    int y2 = int(cy + (sw)*sinA + (-sh) * cosA);
    // Bottom-left
    int x3 = int(cx + (-sw) * cosA - (sh)*sinA);
    int y3 = int(cy + (-sw) * sinA + (sh)*cosA);
    // Bottom-right
    int x4 = int(cx + (sw)*cosA - (sh)*sinA);
    int y4 = int(cy + (sw)*sinA + (sh)*cosA);

    Novice::DrawQuad(
        x1, y1, x2, y2, x3, y3, x4, y4,
        0, 0, w, h,
        texWhite_,
        0xFFFFFFFF
    );
}