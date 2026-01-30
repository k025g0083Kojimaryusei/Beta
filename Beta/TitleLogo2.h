#pragma once
#include <Novice.h>
#include "Easing.h"

class TitleLogo2 {
public:
    TitleLogo2();
    ~TitleLogo2() = default;

    void Update();
    void Draw();

    bool IsIntroFinished() const { return isIntroFinished_; }
    void SetRotateSpeed(float degPerFrame) { rotateSpeed_ = degPerFrame; }
    void SetIntroDuration(int frame) { introDuration_ = frame; }

    float GetCenterX() const { return static_cast<float>(centerX_); }
    float GetCenterY() const { return static_cast<float>(centerY_); }
    float GetLogoWidth() const { return static_cast<float>(logoW_); }
    float GetBaseScale() const { return 0.88f; }
    void SetPosition(float x, float y) { centerX_ = static_cast<int>(x); centerY_ = static_cast<int>(y); }
    void UpdateShakeOnly() { /* just update shakeTimer_ as in shaking phase */ }
    void DrawAt(float x, float y) {
        int oldX = centerX_, oldY = centerY_;
        centerX_ = (int)x; centerY_ = (int)y;
        Draw();
        centerX_ = oldX; centerY_ = oldY; // Restore
    }

private:
    // PNG handles
    int texWhite_;
    int texCyan_;
    int texRed_;
    // Logo logical size (px)
    int logoW_ = 508;
    int logoH_ = 504;

    // Center
    int centerX_ = 620;
    int centerY_ = 340; // Adjust as needed

    /// Animation
    int frameCount_ = 0;
    int introDuration_ = 120; // adjustable intro scale+rotation frames
    float rotateSpeed_ = 10.0f; // degrees per frame
    float rotation_ = 0.0f;

    bool isIntroFinished_ = false;

    // Easing for scale/rotation
    Easing scaleEasing_; // scale 0.0 -> 1.0

    // -- Glitch variables --
    float shakeTimer_ = 0.0f;
    float shakeAmount_ = 1.0f; // adjustable: how much "glitch"

    float rotationAmount_ = -720.0f;
};