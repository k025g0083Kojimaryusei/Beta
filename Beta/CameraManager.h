#pragma once
#include "Camera2D.h"
class CameraManager {
public:
	static CameraManager* GetInstance() {
		static CameraManager instance;
		return &instance;
	}

	Camera2D& GetMainCamera() {
		return mainCamera_;
	}

	Camera2D& GetUICamera() {
		return uiCamera_;
	}

	void UpdateAll() {
		mainCamera_.MoveCameraTransform();
		uiCamera_.MoveCameraTransform();
	}
private:
	CameraManager() = default;
	~CameraManager() = default;
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	Camera2D mainCamera_;
	Camera2D uiCamera_;

};