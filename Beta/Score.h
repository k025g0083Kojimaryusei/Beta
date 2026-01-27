#pragma once

class Score {
public:
    static Score* GetInstance() {
        static Score instance;
        return &instance;
    }

    void AddScore(int maxEnemies, int combo) {
        targetScore_ += (100 * combo * combo) / maxEnemies;
    }

    // 毎フレーム呼び出して、表示スコアを目標スコアに近づける
    void Update() {
        if (displayScore_ < targetScore_) {
            // 1フレームで増える量を決める（例：目標までの差の10%ずつ増やす、または固定値）
            int diff = targetScore_ - displayScore_;
            int add = diff / 10 + 1; // 最低でも1ずつは増やす
            displayScore_ += add;
        }

        // もし超えてしまったら補正
        if (displayScore_ > targetScore_) {
            displayScore_ = targetScore_;
        }
    }

    int GetDisplayScore() const { return displayScore_; }
    void ResetScore() { targetScore_ = 0; displayScore_ = 0; }

private:
    Score() = default;
    int targetScore_ = 0;   // 本当のスコア（計算用）
    int displayScore_ = 0;  // UIに出すスコア（演出用）

    Score(const Score&) = delete;
    Score& operator=(const Score&) = delete;
};