#define _USE_MATH_DEFINES
#include "Camera2D.h"
#include <cmath>

Camera2D::Camera2D() {

}

//カメラの初期化　描画範囲距離､初期位置､回転､拡大率の設定
void Camera2D::InitCameraTransform(cameraInfo& info,float w,float h) {
	
	if (info.centerpos.x == 0 && info.centerpos.y == 0) {
		info.centerpos = { w / 2.0f, h / 2.0f };
	}	
	info.rotation = 0.0f;
	info.scale = { 1.0f, 1.0f };
	info.left = -w / 2.0f;
	info.right = w/ 2.0f;
	info.top = h / 2.0f;
	info.bottom = -h / 2.0f;
	info.width = w;
	info.height = h;
	this->info_ = info;
}

//カメラの数値を更新
void Camera2D::MoveCameraTransform() {

	Vector2 invScale = { 1.0f / info_.scale.x,1.0f / info_.scale.y };

	Matrix3x3 cameraMatrix = WorldMatrix(info_.centerpos, info_.rotation,invScale);
	Matrix3x3 viewMatrix = InverseMatrix(cameraMatrix);
	Matrix3x3 orthoMatrix = OrthoMatrix(info_.left, info_.right, info_.top, info_.bottom);
	Matrix3x3 viewportMatrix = ViewPortMatrix(0.0f, 0.0f, info_.width, info_.height);
	Matrix3x3 viewProjection = MultiplyMatrix(viewMatrix, orthoMatrix);
	this->vpVpMatrix_ = MultiplyMatrix(viewProjection, viewportMatrix);
}

Quad Camera2D::WorldToScreen(const Transform2D & object) {
	Matrix3x3 worldMatrix = WorldMatrix(object.worldPos, object.rotation, object.scale);
	Matrix3x3 wvpMatrix = MultiplyMatrix(worldMatrix, this->vpVpMatrix_);
	Quad screenQuad;
	for (int i = 0; i < 4; i++) {
		screenQuad.v[i] = Transform(object.local.v[i], wvpMatrix);
	}
	return screenQuad;
}

Vector2 Camera2D::WorldToScreen(const Vector2& worldPos) {
	return Transform(worldPos, this->vpVpMatrix_);
}

void Camera2D::MoveCamera(const Vector2& offset) {
	info_.centerpos.x += offset.x;
	info_.centerpos.y += offset.y;
}

// カメラの位置を直接設定
void Camera2D::SetCameraPosition(const Vector2& pos) {
	info_.centerpos = pos;
}

// カメラを相対的に回転
void Camera2D::RotateCamera(float angle) {
	info_.rotation += angle;
}

// カメラの回転を直接設定
void Camera2D::SetCameraRotation(float angle) {
	info_.rotation = angle;
}

// カメラをズーム（現在の拡大率に乗算）
void Camera2D::ZoomCamera(float zoomFactor) {
	info_.scale.x *= zoomFactor;
	info_.scale.y *= zoomFactor;

	// 最小値を設定してゼロ除算を防ぐ
	const float minScale = 0.001f;
	if (info_.scale.x < minScale) info_.scale.x = minScale;
	if (info_.scale.y < minScale) info_.scale.y = minScale;
}

// カメラのズームを直接設定
void Camera2D::SetCameraZoom(const Vector2& zoom) {
	info_.scale = zoom;

	// 最小値を設定してゼロ除算を防ぐ
	const float minScale = 0.001f;
	if (info_.scale.x < minScale) info_.scale.x = minScale;
	if (info_.scale.y < minScale) info_.scale.y = minScale;
}

// カメラ情報を取得
const Camera2D::cameraInfo& Camera2D::GetCameraInfo() const {
	return info_;
}


Matrix3x3 Camera2D:: MultiplyMatrix(const Matrix3x3& m1, const Matrix3x3& m2) {
	Matrix3x3 result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 3; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix3x3 Camera2D::WorldMatrix(const Vector2& pos, float rotation, const Vector2& scale) {
	Matrix3x3 worldMatrix;

	float radian = -rotation * (static_cast<float>(M_PI) / 180.0f);

	float cos = std::cosf(radian);
	float sin = std::sinf(radian);

	worldMatrix = {
		scale.x * cos,scale.x * sin,0.0f,
		-scale.y * sin,scale.y * cos,0.0f,
		pos.x,pos.y,1.0f
	};
	return worldMatrix;
}

Matrix3x3 Camera2D::InverseMatrix(const Matrix3x3& m) {
	Matrix3x3 inverse;

	float det = m.m[0][0] * m.m[1][1]
		- m.m[0][1] * m.m[1][0];

	float invDet = 1.0f / det;

	inverse.m[0][0] = m.m[1][1] * invDet;
	inverse.m[0][1] = -m.m[0][1] * invDet;
	inverse.m[1][0] = -m.m[1][0] * invDet;
	inverse.m[1][1] = m.m[0][0] * invDet;


	inverse.m[2][0] = -(m.m[2][0] * inverse.m[0][0] + m.m[2][1] * inverse.m[1][0]);
	inverse.m[2][1] = -(m.m[2][0] * inverse.m[0][1] + m.m[2][1] * inverse.m[1][1]);

	inverse.m[0][2] = 0.0f;
	inverse.m[1][2] = 0.0f;
	inverse.m[2][2] = 1.0f;

	return inverse;
}

Matrix3x3 Camera2D::OrthoMatrix(float left, float right, float top, float bottom) {
	Matrix3x3 ortho;

	ortho.m[0][0] = 2.0f / (right - left);
	ortho.m[0][1] = 0.0f;
	ortho.m[0][2] = 0.0f;

	ortho.m[1][0] = 0.0f;
	ortho.m[1][1] = 2.0f / (top - bottom);
	ortho.m[1][2] = 0.0f;

	ortho.m[2][0] = -(right + left) / (right - left);
	ortho.m[2][1] = -(top + bottom) / (top - bottom);
	ortho.m[2][2] = 1.0f;
	return ortho;
}

Matrix3x3 Camera2D::ViewPortMatrix(float x, float y, float width, float height) {
	Matrix3x3 viewport;
	viewport.m[0][0] = width / 2.0f;
	viewport.m[0][1] = 0.0f;
	viewport.m[0][2] = 0.0f;
	viewport.m[1][0] = 0.0f;
	viewport.m[1][1] = -(height / 2.0f);;
	viewport.m[1][2] = 0.0f;
	viewport.m[2][0] = x + width / 2.0f;
	viewport.m[2][1] = y + height / 2.0f;
	viewport.m[2][2] = 1.0f;
	return viewport;
}
Vector2 Camera2D::Transform(const Vector2& v, const Matrix3x3& m) {
	Vector2 result;
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + m.m[2][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + m.m[2][1];
	return result;
}

Matrix3x3 Camera2D::MakeWVP(const Matrix3x3& world, const Matrix3x3& view, const Matrix3x3& ortho, const Matrix3x3& viewport) {
	Matrix3x3 wvp;
	wvp = MultiplyMatrix(world, view);
	wvp = MultiplyMatrix(wvp, ortho);
	wvp = MultiplyMatrix(wvp, viewport);
	return wvp;
}