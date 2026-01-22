#pragma once
#include "Object2D.h"

struct Matrix3x3 {
	float m[3][3];
};

class Camera2D {
public:

	Camera2D();

	struct cameraInfo {
		Vector2 centerpos = {};
		float rotation;
		Vector2 scale;
		float left;
		float right;
		float top;
		float bottom;
		float width;
		float height;

	};

	//カメラの初期化　描画範囲距離､初期位置､回転､拡大率の設定
	void InitCameraTransform(cameraInfo& cameraInfo, float w, float h);

	//カメラの数値を更新
	void MoveCameraTransform();

	//ワールド座標をスクリーン座標に変換
	Quad WorldToScreen(const Transform2D& object);

	//ワールド座標をスクリーン座標に変換
	Vector2 WorldToScreen(const Vector2& worldPos);
	void MoveCamera(const Vector2& offset);

	// カメラの位置を設定
	void SetCameraPosition(const Vector2& pos);

	// カメラを回転
	void RotateCamera(float angle);

	// カメラの回転を設定
	void SetCameraRotation(float angle);

	// カメラをズーム（拡大率を変更）
	void ZoomCamera(float zoomFactor);

	// カメラのズームを設定
	void SetCameraZoom(const Vector2& zoom);

	// カメラ情報を取得
	const cameraInfo& GetCameraInfo() const;

private:
	cameraInfo info_;
	Matrix3x3 vpVpMatrix_;
	Matrix3x3 MultiplyMatrix(const Matrix3x3& m1, const Matrix3x3& m2);
	Matrix3x3 WorldMatrix(const Vector2& pos, float rotation, const Vector2& scale);
	Matrix3x3 InverseMatrix(const Matrix3x3& m);
	Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom);
	Matrix3x3 ViewPortMatrix(float x, float y, float width, float height);
	Vector2 Transform(const Vector2& v, const Matrix3x3& m);
	Matrix3x3 MakeWVP(const Matrix3x3& world, const Matrix3x3& view, const Matrix3x3& ortho, const Matrix3x3& viewport);
};