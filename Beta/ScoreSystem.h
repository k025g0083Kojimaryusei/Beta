#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "json.hpp"
#include <Novice.h>
#include <dinput.h>
#include "Object2D.h"
#include "Camera2D.h"
#include "Easing.h"

using json = nlohmann::json;

// 名前とスコアをセットにする構造体
struct RankingData {
	std::string name;
	int score;
};

struct KeyMap {
	int dikCode;
	char character;
};

class ScoreSystem {
public:
	// シングルトンインスタンスの取得
	static ScoreSystem* GetInstance() {
		static ScoreSystem instance;
		return &instance;
	}

	// コピーと代入を禁止
	ScoreSystem(const ScoreSystem&) = delete;
	ScoreSystem& operator=(const ScoreSystem&) = delete;


	void Initialize();

	// 名前入力処理
	void InputName(char* keys, char* preKeys);

	// スコア追加処理
	void Add(int newScore);

	// スコア表示用の関数
	void DrawScore(int score);

	//ランキング表示用の関数
	void DrawRanking();

	//ランキングスクロール処理
	void ScrollRanking(char* keys);
	// 配列リセット処理
	void Reset();

	// 最後に追加したスコアにフォーカスを合わせる
	void FocusOnLastAdded();

	// 1位のスコアにフォーカスを合わせる
	void FocusOnFirstPlace();

	void DrawScoreSprite(Vector2 pos, const std::string& s, float spacing);

private:
	ScoreSystem();

	// 最後に追加したスコアのインデックス
	int lastAddedIndex = 0; 


	Easing scrollEasing;    // カメラ移動用イージング
	float startCamY = 0.0f; // 移動開始時のカメラY
	float targetCamY = 0.0f; // 移動目標のカメラY
	bool isAutoScrolling = false; // 自動スクロール中フラグ


	// プレイヤー名
	std::string playerName;
	//スコア配列
	std::vector<RankingData> scores_;
	
	//  カメラ
	Camera2D camera;
	Camera2D::cameraInfo cameraInfo;
	//ファイル名
	const std::string fileName;

	std::vector<RankingData> Load();

	//セーブ
	void Save();

	// 名前入力用バッファ
	char nameInput[9];

	// スコア配列の取得
	const std::vector<RankingData>& GetScores() const;

	//スコアのスプライトを描画
	void DrawScoreSprite(Vector2 pos, int score,float spacing);

	//名前のスプライトを描画
	void DrawNameSprite(Vector2 pos,  std::string& name, float spacing);


	Vector2 inputScorePos = {470.0f,407.0f};
	float inputScoreSpacing = 50.0f;
	Vector2 inputNamePos = {419.0f,241.0f};
	float inputNameSpacing = 57.0f;


	Vector2 rankingBasePos = { 250.0f, 150.0f }; // ランキング全体の開始位置
	float rowHeight = 90.0f;                    // 各行の間隔
	float columnSpacing = 200.0f;               // 順位、名前、スコアの列の間隔

	Vector2 rankBasePos = { 122.0f, 150.0f };
	Vector2 nameBasePos = { 254.0f, 150.0f };
	Vector2 scoreBasePos = { 761.0f, 150.0f };

	// --- 間隔の個別設定 ---
	float rankSpacing = 40.0f;
	float nameSpacing = 60.0f;
	float scoreSpacing = 50.0f;



	// 名前の最大入力文字数
	int nameLengthLimit = 8;
	//背景のテクスチャ
	int BGtexture = Novice::LoadTexture("./Textures/UI/BackGround/ranking4.png");

	//大文字英語のテクスチャ
	int upperAlphabetTexture[26] = {
	Novice::LoadTexture("./texture/name/11.png"),
	Novice::LoadTexture("./texture/name/12.png"),
	Novice::LoadTexture("./texture/name/13.png"),
	Novice::LoadTexture("./texture/name/14.png"),
	Novice::LoadTexture("./texture/name/15.png"),
	Novice::LoadTexture("./texture/name/16.png"),
	Novice::LoadTexture("./texture/name/17.png"),
	Novice::LoadTexture("./texture/name/18.png"),
	Novice::LoadTexture("./texture/name/19.png"),
	Novice::LoadTexture("./texture/name/20.png"),
	Novice::LoadTexture("./texture/name/21.png"),
	Novice::LoadTexture("./texture/name/22.png"),
	Novice::LoadTexture("./texture/name/23.png"),
	Novice::LoadTexture("./texture/name/24.png"),
	Novice::LoadTexture("./texture/name/25.png"),
	Novice::LoadTexture("./texture/name/26.png"),
	Novice::LoadTexture("./texture/name/27.png"),
	Novice::LoadTexture("./texture/name/28.png"),
	Novice::LoadTexture("./texture/name/29.png"),
	Novice::LoadTexture("./texture/name/30.png"),
	Novice::LoadTexture("./texture/name/31.png"),
	Novice::LoadTexture("./texture/name/32.png"),
	Novice::LoadTexture("./texture/name/33.png"),
	Novice::LoadTexture("./texture/name/34.png"),
	Novice::LoadTexture("./texture/name/35.png"),
	Novice::LoadTexture("./texture/name/36.png")

	};

	// 小文字英語のテクスチャ	
	int lowAlphabetTexture[26] = {
		Novice::LoadTexture("./texture/name/37.png"),
		Novice::LoadTexture("./texture/name/38.png"),
		Novice::LoadTexture("./texture/name/39.png"),
		Novice::LoadTexture("./texture/name/40.png"),
		Novice::LoadTexture("./texture/name/41.png"),
		Novice::LoadTexture("./texture/name/42.png"),
		Novice::LoadTexture("./texture/name/43.png"),
		Novice::LoadTexture("./texture/name/44.png"),
		Novice::LoadTexture("./texture/name/45.png"),
		Novice::LoadTexture("./texture/name/46.png"),
		Novice::LoadTexture("./texture/name/47.png"),
		Novice::LoadTexture("./texture/name/48.png"),
		Novice::LoadTexture("./texture/name/49.png"),
		Novice::LoadTexture("./texture/name/50.png"),
		Novice::LoadTexture("./texture/name/51.png"),
		Novice::LoadTexture("./texture/name/52.png"),
		Novice::LoadTexture("./texture/name/53.png"),
		Novice::LoadTexture("./texture/name/54.png"),
		Novice::LoadTexture("./texture/name/55.png"),
		Novice::LoadTexture("./texture/name/56.png"),
		Novice::LoadTexture("./texture/name/57.png"),
		Novice::LoadTexture("./texture/name/58.png"),
		Novice::LoadTexture("./texture/name/59.png"),
		Novice::LoadTexture("./texture/name/60.png"),
		Novice::LoadTexture("./texture/name/61.png"),
		Novice::LoadTexture("./texture/name/62.png")
	};



	// 数字のテクスチャ
	int numberTexture[10] = {
	Novice::LoadTexture("./texture/name/1.png"),	
	Novice::LoadTexture("./texture/name/2.png"),
	Novice::LoadTexture("./texture/name/3.png"),
	Novice::LoadTexture("./texture/name/4.png"),
	Novice::LoadTexture("./texture/name/5.png"),
	Novice::LoadTexture("./texture/name/6.png"),
	Novice::LoadTexture("./texture/name/7.png"),
	Novice::LoadTexture("./texture/name/8.png"),
	Novice::LoadTexture("./texture/name/9.png"),
	Novice::LoadTexture("./texture/name/10.png")
	};

	// キーコードと文字の対応表
	std::array<KeyMap, 26> upperKeyMaps{
	   { { DIK_A, 'A' }, { DIK_B, 'B' }, { DIK_C, 'C' }, { DIK_D, 'D' },
		 { DIK_E, 'E' }, { DIK_F, 'F' }, { DIK_G, 'G' }, { DIK_H, 'H' },
		 { DIK_I, 'I' }, { DIK_J, 'J' }, { DIK_K, 'K' }, { DIK_L, 'L' },
		 { DIK_M, 'M' }, { DIK_N, 'N' }, { DIK_O, 'O' }, { DIK_P, 'P' },
		 { DIK_Q, 'Q' }, { DIK_R, 'R' }, { DIK_S, 'S' }, { DIK_T, 'T' },
		 { DIK_U, 'U' }, { DIK_V, 'V' }, { DIK_W, 'W' }, { DIK_X, 'X' },
		 { DIK_Y, 'Y' }, { DIK_Z, 'Z' } }
	};

	std::array<KeyMap, 26> lowKeyMaps{
		{ { DIK_A, 'a' }, { DIK_B, 'b' }, { DIK_C, 'c' }, { DIK_D, 'd' },
		  { DIK_E, 'e' }, { DIK_F, 'f' }, { DIK_G, 'g' }, { DIK_H, 'h' },
		  { DIK_I, 'i' }, { DIK_J, 'j' }, { DIK_K, 'k' }, { DIK_L, 'l' },
		  { DIK_M, 'm' }, { DIK_N, 'n' }, { DIK_O, 'o' }, { DIK_P, 'p' },
		  { DIK_Q, 'q' }, { DIK_R, 'r' }, { DIK_S, 's' }, { DIK_T, 't' },
		  { DIK_U, 'u' }, { DIK_V, 'v' }, { DIK_W, 'w' }, { DIK_X, 'x' },
		  { DIK_Y, 'y' }, { DIK_Z, 'z' } }
	};

	std::array<KeyMap, 10> numKeyMaps{
		{ { DIK_0, '0' }, { DIK_1, '1' }, { DIK_2, '2' }, { DIK_3, '3' },
		  { DIK_4, '4' }, { DIK_5, '5' }, { DIK_6, '6' }, { DIK_7, '7' },
		  { DIK_8, '8' }, { DIK_9, '9' } }
	};
};