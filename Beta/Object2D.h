#pragma once

struct Vector2 {
	float x;
	float y;
};

// 4頂点をまとめる構造体
struct Quad {
	Vector2 v[4];
	// v[0]:左上(LT), v[1]:右上(RT), v[2]:左下(LB), v[3]:右下(RB)
};

struct Transform2D {

	Quad local; // 四角形の4頂点座標
	Vector2 worldPos; // 回転・拡大の中心点
	float rotation = 0.0f; // 回転角
	Vector2 scale = { 1.0f,1.0f }; // 拡大率
	float width;  // 幅
	float height; // 高さ

	void Init(Vector2 pos, float w, float h, float rot = 0.0f, Vector2 scal = {1.0f,1.0f}) {
		worldPos = pos;
		width = w;
		height = h;
		scale = scal;
		rotation = rot;
		local.v[0] = { -w / 2.0f,  h / 2.0f }; // LT
		local.v[1] = { w / 2.0f,  h / 2.0f }; // RT
		local.v[2] = { -w / 2.0f, -h / 2.0f }; // LB
		local.v[3] = { w / 2.0f, -h / 2.0f }; // RB

	}

};

