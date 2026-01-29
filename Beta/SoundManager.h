#pragma once
#include <Novice.h>
#include <string>
#include <unordered_map>

// シンプルなサウンドマ��ージャークラス
class SoundManager {
public:
    // シングルトンで簡単にクラスを使えるように
    static SoundManager& Get();

    // サウンドをキー名でロードする　例: Load("BGM", "./sounds/bgm.mp3")
    void Load(const std::string& name, const char* filename);

    // サウンドを再生する　例: Play("BGM", 128, true)
    // volume : 0〜255, loop : true=ループ, false=一回だけ
    void Play(const std::string& name, float volume = 255.0f, bool loop = false);

    // In SoundManager.h, public:
    bool IsPlaying(const std::string& name) const;

    // サウンドを停止する
    void Stop(const std::string& name);

    // すべてのサウンドを停止する
    void StopAll();

private:
    std::unordered_map<std::string, int> soundData_;     // ロードしたサウンドのhandle
    std::unordered_map<std::string, int> playingHandle_; // 再生中のサウンド

    // コンストラクタとデストラクタ
    SoundManager() = default;
    ~SoundManager() = default;

    // コピー禁止
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
};