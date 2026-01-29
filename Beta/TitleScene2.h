// TitleScene2.h

#pragma once
#include "Scene.h"
#include "TitleBackground.h"
#include "TitleLogo2.h"
#include <Novice.h>
#include "SoundManager.h"

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
    void Begin();

private:
    SceneManager* sceneManager;
    TitleBackground bg_;
    TitleLogo2 logo_;

    int bgTexture_;

    // State handling
    TitleState state_ = TitleState::Intro;

    // Logo position animation
    float logoStartX_;
    float logoTargetX_ = 360.0f;
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
    //const float kCursorEasingSpeed = 0.14f;
    int noiseTimer_ = 0;

    // Menu graphics
    int btnTex_[3][3];  // [menu][glitch frame]
    int barTex_[3];     // bar animation frames
    int cursorTex_;     // selector

    // Menu layout positions
    int menuBaseX_ = 800;     // X of menu text
    int menuBaseY_ = 180;     // Y of first menu
    int menuSpacingY_ = 160;  // Spacing

    // Sizes from assets:
    const int menuWidth_ = 516;
    const int menuHeight_ = 126;
    const int barWidth_ = 592;
    const int barHeight_ = 114;
    const int barYGap_ = 6;   // Gap between menu and bar below
    const int cursorWidth_ = 68;
    const int cursorHeight_ = 68;
    const int cursorXGap_ = 20; // Gap from left of menu

    // "Bar slot" positions for each menu, just like your friend
    int barX_[3] = { 676-56, 676-56, 676-56 };   // ← use your BChoiceX_[i] values
    int barY_[3] = { 156, 338, 524 };   // ← use your BChoiceY_[i] values

    // Cursor positions if you want them the same way (optional)
    // If you want cursor based on old code:
    int cursorX_ = 756 - 80;    // = AchoiceX_[0] - 80
    int cursorYOffset_ = 30;
   
    const float kCursorEasingSpeed = 0.1f; // Try these, or tweak as needed  // Add to cursor Y in draw

    // Menu text positions (same as before)
    int menuTextX_[3] = { 700, 700, 700 };  // = AchoiceX_[i] from friend
    int menuTextY_[3] = { 126, 306, 490 };  // = AchoiceY_[i] from friend

    Easing logoSlideEasing_;
   
};