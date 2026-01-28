#pragma once
class ComboManager {
public:
    static ComboManager* GetInstance() {
        static ComboManager instance;
        return &instance;
    }

    // 敵を倒した時に呼ぶ
    void AddCombo() {
        comboCount_++;
        displayTimer_ = 30; 
    }

    // コンボが途切れる処理（着地した時や時間切れなど）
    void ResetCombo() {
        comboCount_ = 0;
        displayTimer_ = 0;
    }

    void Update() {
        if (displayTimer_ > 0) {
            displayTimer_--;
        }
    }

    // 描画用の情報を取得
    int GetComboCount() const { return comboCount_; }
    int GetTimer() const { return displayTimer_; }

private:
    ComboManager() = default;
    int comboCount_ = 0;
    int displayTimer_ = 0;
    bool isDisplay = false;
};