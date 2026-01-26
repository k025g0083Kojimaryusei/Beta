// TitleScene2.h
#pragma once
#include "Scene.h"
#include "TitleBackground.h"
#include "TitleLogo2.h"
#include <Novice.h>
#include <cmath>

// Animation states for the title
enum class TitleState {
    Intro,
    Shake,
    SlideLeft,
    MenuActive
};

class TitleScene2 : public Scene {
public:
    TitleScene2(SceneManager* manager);

    void Update(char* keys, char* preKeys) override;
    void Draw() override;

private:
    SceneManager* sceneManager;
    TitleBackground bg_;
    TitleLogo2 logo_;

    // State handling
    TitleState state_ = TitleState::Intro;

    // Logo position animation
    float logoStartX_;
    float logoTargetX_;
    float logoCurrentX_;
    float logoSlideT_ = 0.0f;
    float logoSlideSpeed_ = 0.04f;

    // Enter key
    int enterTexture_;
    int enterX_ = 1190, enterY_ = 620, enterW_ = 78, enterH_ = 86;
    int frameCount_ = 0;
    float hoverOffset_ = 0.0f;

    // --- Select menu ---
    int selectedIndex_ = 0;
    float cursorCurrentY_;
    const float kCursorEasingSpeed = 0.14f;
    int noiseTimer_ = 0;

    // Menu graphics
    int btnTex_[3][3];  // [menu][glitch frame]
    int barTex_[3];     // bar highlight
    int cursorTex_;     // selector arrow

    // Menu layout positions (ADJUST to match your red lines & visual preference!)
    int menuBaseX_ = 800;     // Start of menu (right red line)
    int menuBaseY_ = 180;
    int menuSpacingY_ = 160;  // Space between menu items

    int barGapY_ = 132;     // Bar appears directly below each word (tweak as needed)
    int cursorGapX_ = -112; // Cursor arrow to left of each word (tweak for nice left distance)

    // For scene change result if needed
    int nextSceneIndex_ = -1;

    int  bgTexture_;
};