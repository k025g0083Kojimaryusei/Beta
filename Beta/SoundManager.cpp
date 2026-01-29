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
void SoundManager::Play(const std::string& name, float volume, bool loop) {
    if (soundData_.count(name)) {
        int handle = soundData_[name];
        int loopFlag = loop ? 1 : 0;
        // Pass volume as float directly!
        int playHandle = Novice::PlayAudio(handle, loopFlag, volume);
        playingHandle_[name] = playHandle;
    }
}

// In SoundManager.cpp:
bool SoundManager::IsPlaying(const std::string& name) const {
    // If key exists and still returns PlayAudio as "playing":
    auto it = playingHandle_.find(name);
    if (it != playingHandle_.end()) {
        return Novice::IsPlayingAudio(it->second); // true if handle is active
    }
    return false;
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