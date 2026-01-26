#pragma once
#include "Scene.h"
#include "TitleBackground.h"
#include "TitleLogo2.h"

class TitleScene2 : public Scene {
public:
    TitleScene2(SceneManager* manager);

    void Update(char* keys, char* preKeys) override;
    void Draw() override;

private:
    SceneManager* sceneManager;
    TitleBackground bg_;
    TitleLogo2 logo_;
    int selectedIndex = 0;

    int enterTexture_;
	int bgTexture_;

    int enterX_ = 1190;           // <-- Adjust these to position under "Program:"
    int enterY_ = 620;
    int enterW_ = 78;            // <-- Adjust size to fit the scene (original PNG is 64x58, see below for scaling)
    int enterH_ = 86;

    int frameCount_ = 0;         // <- For hover animation
    float hoverOffset_ = 0.0f;
};