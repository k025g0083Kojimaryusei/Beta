#include "Scene.h"
#include "TitleScene2.h"
#include "PlayScene.h"
#include "CreditScene.h"
#include "RankingScene.h"

SceneManager::SceneManager()
{
	currentType_ = SceneType::Title;
	currentScene_ = new TitleScene2(this);
    radialGlowTex_ = Novice::LoadTexture("./Textures/UI/glow.png"); 
}

SceneManager::~SceneManager()
{
	if (currentScene_)
	{
		delete currentScene_;
	}
}

void SceneManager::ChangeScene(SceneType newType)
{
	if (inTransition_) return;

	if (newType == currentType_) return;

	StartTransition(newType);
}

//Work in progress
void SceneManager::StartTransition(SceneType to)
{
    inTransition_ = true;
    switchingDone_ = false;
    nextType_ = to;
    phase_ = 0;

    // Phase 0: vertical close (1 -> 0) over 30 frames
    vertEasing_.Init(1.0f, 0.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_BOUNCE);
    vertEasing_.Start();

    // Phase 1: horizontal close (1 -> 0) over 30 frames - will start later
    horizonEasing_.Init(1.0f, 0.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_BOUNCE);
    // do NOT call horizonEasing_.Start() here

    pauseTimer_ = pauseDuration_;
}

void SceneManager::UpdateTransition()
{
    switch (phase_)
    {
    case 0: // vertical close
        vertEasing_.Update();
        horizonEasing_.easingRate = 1.0f;
        if (!vertEasing_.isMove) {
            phase_ = 1;
            horizonEasing_.Start();
        }
        break;
    case 1: // horizontal close
        horizonEasing_.Update();
        vertEasing_.easingRate = 0.0f;
        if (!horizonEasing_.isMove && !switchingDone_) {
            switchingDone_ = true;

            delete currentScene_;
            currentScene_ = nullptr;
            currentType_ = nextType_;

            switch (nextType_) {
            case SceneType::Title:   currentScene_ = new TitleScene2(this);   break;
            case SceneType::Play:    currentScene_ = new PlayScene(this);    break;
            case SceneType::Credit:  currentScene_ = new CreditScene(this);  break;
            case SceneType::Ranking: currentScene_ = new RankingScene(this); break;
            }

            // Begin black screen pause
            phase_ = 2;
            // pauseTimer_ already set; can reset if needed
        }
        break;
    case 2: // *** black pause ***
        if (--pauseTimer_ <= 0) {
            // Prepare open
            phase_ = 3;
            horizonEasing_.Init(0.0f, 1.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_BOUNCE);
            horizonEasing_.Start();
            vertEasing_.easingRate = 0.0f;
        }
        break;
    case 3: // horizontal open (dot -> line)
        horizonEasing_.Update();
        vertEasing_.easingRate = 0.0f;
        if (!horizonEasing_.isMove) {
            phase_ = 4;
            vertEasing_.Init(0.0f, 1.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_BOUNCE);
            vertEasing_.Start();
        }
        break;
    case 4: // vertical open (line -> full)
        vertEasing_.Update();
        horizonEasing_.easingRate = 1.0f;
        if (!vertEasing_.isMove) {
            inTransition_ = false;
        }
        break;
    }
}

void SceneManager::DrawCurrentScene()
{
    //Novice::ScreenPrintf(0, 0, "inTransition=%d", inTransition_ ? 1 : 0);

    const int screenW = 1280;
    const int screenH = 720;

    if (!inTransition_) {
        // Normal: just draw the scene
        if (currentScene_) {
            currentScene_->Draw();
        }
    }
    else {
        // During transition: white background instead of scene content
        Novice::DrawBox(0, 0, screenW, screenH, 0.0f, WHITE, kFillModeSolid);
    }

    // TV overlay effect on top (uses white as base)
    if (inTransition_) {
        DrawTransitionOverlay();
    }
}

//
//void SceneManager::DrawCurrentScene()
//{
//    Novice::ScreenPrintf(0, 0, "inTransition=%d", inTransition_ ? 1 : 0);
//
//    const int screenW = 1280;
//    const int screenH = 720;
//
//    if (!inTransition_) {
//        // Not in transition: Draw normal scene
//        if (currentScene_) {
//            currentScene_->Draw();
//        }
//    }
//    else {
//        // In transition, show:
//        // - Old scene: closing phases (0 and 1)
//        // - Nothing but black: phase 2
//        // - New scene: opening phases (3 and 4)
//       // bool drawScene = false;
//
//        // Decide which scene to draw
//        if (phase_ == 0 || phase_ == 1) {
//            // Draw the *old scene* (content before switch)
//            if (currentScene_) {
//                currentScene_->Draw();
//            }
//        }
//        else if (phase_ == 3 || phase_ == 4) {
//            // Draw the *new scene* (content after switch)
//            if (currentScene_) {
//                currentScene_->Draw();
//            }
//        }
//        // In phase 2 (black pause), draw black
//        else if (phase_ == 2) {
//            Novice::DrawBox(0, 0, screenW, screenH, 0.0f, BLACK, kFillModeSolid);
//        }
//    }
//
//    // TV overlay always on top
//    if (inTransition_) {
//        DrawTransitionOverlay();
//    }
//}

void SceneManager::UpdateCurrentScene(char* keys, char* preKeys)
{
    if (!inTransition_) {
        // Normal update
        if (currentScene_) {
            currentScene_->Update(keys, preKeys);
        }
    }
    else {
        // During transition we freeze the scenes
        // (no Update on current or next scene)
    }

    if (inTransition_) {
        UpdateTransition();
    }
}

void SceneManager::DrawTransitionOverlay()
{
    // Debug
    //Novice::ScreenPrintf(0, 20, "Transition ON phase=%d", phase_);
    //Novice::ScreenPrintf(0, 40, "w=%.2f h=%.2f",
    //    horizonEasing_.easingRate, vertEasing_.easingRate);

    const int screenW = 1280;
    const int screenH = 720;
    const int centerX = screenW / 2;
    const int centerY = screenH / 2;

    // Tweak for your mask/bar color during transition
    unsigned int color = BLACK; // or use DARKGRAY for demo

    float wScale = horizonEasing_.easingRate;
    float hScale = vertEasing_.easingRate;
    if (wScale < 0.0f) wScale = 0.0f;
    if (wScale > 1.0f) wScale = 1.0f;
    if (hScale < 0.0f) hScale = 0.0f;
    if (hScale > 1.0f) hScale = 1.0f;

    if (phase_ == 0 || phase_ == 4) {
        // --- vertical squash/expand ---
        int visibleH = static_cast<int>(screenH * hScale);
        int top = centerY - visibleH / 2;
        int bottom = centerY + visibleH / 2;

        if (visibleH <= 0) {
            Novice::DrawBox(0, 0, screenW, screenH, 0.0f, color, kFillModeSolid);
            return;
        }
        if (top > 0) {
            Novice::DrawBox(0, 0, screenW, top, 0.0f, color, kFillModeSolid);
        }
        if (screenH - bottom > 0) {
            Novice::DrawBox(0, bottom, screenW, screenH - bottom, 0.0f, color, kFillModeSolid);
        }
    }
    else if (phase_ == 1 || phase_ == 3) {
        // --- horizontal pinch/expand ---
        int lineThickness = 2;
        int top = centerY - lineThickness / 2;
        int bottom = centerY + lineThickness / 2;

        int visibleW = static_cast<int>(screenW * wScale);
        int left = centerX - visibleW / 2;
        int right = centerX + visibleW / 2;

        if (visibleW <= 0) {
            Novice::DrawBox(0, 0, screenW, screenH, 0.0f, color, kFillModeSolid);
            return;
        }

        // LEFT / RIGHT bars
        if (left > 0) {
            Novice::DrawBox(0, top, left, lineThickness, 0.0f, color, kFillModeSolid);
        }
        if (screenW - right > 0) {
            Novice::DrawBox(right, top, screenW - right, lineThickness, 0.0f, color, kFillModeSolid);
        }
        // Black above and below the beam
        Novice::DrawBox(0, 0, screenW, top, 0.0f, color, kFillModeSolid);
        Novice::DrawBox(0, bottom, screenW, screenH - bottom, 0.0f, color, kFillModeSolid);

        // ---- radial glow PNG using DrawQuad ----
        float t = 1.0f - wScale;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        float alphaT = t * (1.0f - t) * 4.0f;

        if (alphaT >= 0.3f && radialGlowTex_ != 0) {
            // Calculate dynamic radius/scaling
            float minRadius = 10.0f;
            float maxRadius = 60.0f;
            float radius = minRadius + (maxRadius - minRadius) * t;

            // PNG size and quad side length
            float textureSize = 350.0f;
            float scale = radius / (textureSize / 2.0f);

            int quadW = static_cast<int>(textureSize * scale);
            int quadH = static_cast<int>(textureSize * scale);

            int centerXC = screenW / 2;
            int centerYC = screenH / 2;

            // Quad vertices
            int x1 = centerXC - quadW / 2;
            int y1 = centerYC - quadH / 2;
            int x2 = centerXC + quadW / 2;
            int y2 = centerYC - quadH / 2;
            int x3 = centerXC - quadW / 2;
            int y3 = centerYC + quadH / 2;
            int x4 = centerXC + quadW / 2;
            int y4 = centerYC + quadH / 2;

            // Source image: use entire 350x350 region
            int srcX = 0;
            int srcY = 0;
            int srcW = 350;
            int srcH = 350;

            Novice::DrawQuad(
                x1, y1,
                x2, y2,
                x3, y3,
                x4, y4,
                srcX, srcY,
                srcW, srcH,
                radialGlowTex_,
                WHITE  // Or other color, for full brightness
            );
        }
    }
    else if (phase_ == 2) {
        // --- PAUSE: Full black ---
        Novice::DrawBox(0, 0, screenW, screenH, 0.0f, color, kFillModeSolid);
        // Optionally you could draw a small dot or nothing
    }
}