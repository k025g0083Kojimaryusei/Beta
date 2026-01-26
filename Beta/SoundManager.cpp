#include "SoundManager.h"

// シングルトン用
SoundManager& SoundManager::Get() {
    static SoundManager instance;
    return instance;
}

// サウンドのロード
void SoundManager::Load(const std::string& name, const char* filename) {
    int handle = Novice::LoadAudio(filename); // ファイルからサウンド読み込み
    soundData_[name] = handle; // マップに保存
}

// サウンドの再生
void SoundManager::Play(const std::string& name, int volume, bool loop) {
    // すでにロードされていたら
    if (soundData_.count(name)) {
        int handle = soundData_[name];
        int playHandle = Novice::PlayAudio(handle, loop, static_cast<float>(volume));
        playingHandle_[name] = playHandle;
    }
}

// サウンドの停止
void SoundManager::Stop(const std::string& name) {
    if (playingHandle_.count(name)) {
        Novice::StopAudio(playingHandle_[name]);
        playingHandle_.erase(name);
    }
}

// 全部止める
void SoundManager::StopAll() {
    for (auto& pair : playingHandle_) {
        Novice::StopAudio(pair.second);
    }
    playingHandle_.clear();
}