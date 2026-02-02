#include "ScoreSystem.h"
#include <imgui.h>
//public-------------------------------------------------------------

ScoreSystem::ScoreSystem() : fileName("ranking.json") {
	// 起動時に一回読み込んでおく
	scores_ = Load();
	camera.InitCameraTransform(cameraInfo, 1280.0f, 720.0f);

}

void ScoreSystem::Initialize() {
	camera.InitCameraTransform(cameraInfo, 1280.0f, 720.0f);
	playerName.clear();
}

void ScoreSystem::InputName(char* keys, char* preKeys) {
	if (keys[DIK_BACK] && !preKeys[DIK_BACK]) {
		if (!playerName.empty()) {
			playerName.pop_back();
		}
	}

	// 2. アルファベットの入力 (1つのループにまとめる)
	for (int i = 0; i < 26; i++) {
		int code = upperKeyMaps[i].dikCode; // DIK_A など

		if (keys[code] && !preKeys[code]) { // キーが押された瞬間
			if (playerName.length() < nameLengthLimit) {
				// Shiftが押されているかチェック
				if (keys[DIK_LSHIFT] || keys[DIK_RSHIFT]) {
					playerName += upperKeyMaps[i].character; // 大文字
				}
				else {
					playerName += lowKeyMaps[i].character;   // 小文字
				}
			}
		}
	}

	// 3. 数字の入力
	for (const auto& km : numKeyMaps) {
		if (keys[km.dikCode] && !preKeys[km.dikCode]) {
			if (playerName.length() < nameLengthLimit) {
				playerName += km.character;
			}
		}
	}
}

void ScoreSystem::Add(int newScore) {
	scores_ = Load();
	std::string limitedName = playerName.substr(0, 8);

	// 1. 新しいデータを追加
	RankingData newData = { limitedName, newScore };
	scores_.push_back(newData);

	// 2. スコアで降順ソート
	std::sort(scores_.begin(), scores_.end(), [](const RankingData& a, const RankingData& b) {
		return a.score > b.score;
		});

	// 3. 追加したスコアがどこに行ったか探す（同じスコアがある場合は最初に見つけた方）
	auto it = std::find_if(scores_.begin(), scores_.end(), [&](const RankingData& d) {
		return d.name == limitedName && d.score == newScore;
		});

	if (it != scores_.end()) {
		lastAddedIndex = static_cast<int>(std::distance(scores_.begin(), it));
	}

	Save();
}
void ScoreSystem::DrawScore(int score) {
	camera.MoveCameraTransform();

	// 背景描画
	//Novice::DrawSprite(0, 0, BGtexture, 1.0f, 1.0f, 0.0f, WHITE);

	//ImGui::Begin("Score Layout");
	//ImGui::DragFloat2("ScorePos", &inputScorePos.x, 1.0f);
	//ImGui::DragFloat2("NamePos", &inputNamePos.x, 1.0f);
	//ImGui::DragFloat("Score Spacing", &inputScoreSpacing, 1.0f);
	//ImGui::DragFloat("Name Spacing", &inputNameSpacing, 1.0f);
	//ImGui::End();

	// スコア描画

	// Pad with zeros to 7 digits:
	char buf[8];
	sprintf_s(buf, "%07d", score);
	std::string scoreStr = buf;

	// Now, call the overload (see below):
	DrawScoreSprite(inputScorePos, scoreStr, inputScoreSpacing);

	//DrawScoreSprite(inputScorePos, score, inputScoreSpacing);
	DrawNameSprite(inputNamePos, playerName, inputNameSpacing);
}

void ScoreSystem::DrawRanking() {

	const std::vector<RankingData>& currentScores = GetScores();
	// --- ImGuiでの個別調整用UI ---
	//ImGui::Begin("Ranking Detailed Layout");
	//ImGui::DragFloat2("Rank Base Pos", &rankBasePos.x, 1.0f);
	//ImGui::DragFloat("Rank Spacing", &rankSpacing, 1.0f);
	//
	//ImGui::DragFloat2("Name Base Pos", &nameBasePos.x, 1.0f);
	//ImGui::DragFloat("Name Spacing", &nameSpacing, 1.0f);
	//
	//ImGui::DragFloat2("Score Base Pos", &scoreBasePos.x, 1.0f);
	//ImGui::DragFloat("Score Spacing", &scoreSpacing, 1.0f);
	//
	//ImGui::DragFloat("Row Height", &rowHeight, 1.0f);
	//ImGui::End();

	// --- 描画処理 ---
	for (int i = 0; i < static_cast<int>(currentScores.size()); i++) {
		float yOffset = i * -rowHeight;

		// 1. 順位 (Rank)
		Vector2 rPos = { rankBasePos.x, rankBasePos.y + yOffset };
		DrawScoreSprite(rPos, i + 1, rankSpacing);

		// 2. 名前 (Name)
		Vector2 nPos = { nameBasePos.x, rankBasePos.y + yOffset };
		std::string name = currentScores[i].name;
		DrawNameSprite(nPos, name, nameSpacing);

		// 3. スコア (Score)
		Vector2 sPos = { scoreBasePos.x, rankBasePos.y + yOffset };
		// Pad the score to 7 digits
		char buf[8];
		sprintf_s(buf, "%07d", currentScores[i].score);
		std::string paddedScore = buf;
		DrawScoreSprite(sPos, paddedScore, scoreSpacing);
	}
	//Novice::DrawSprite(0, 0, BGtexture, 1.0f, 1.0f, 0.0f, WHITE);
}//private-------------------------------------------------------------

std::vector<RankingData> ScoreSystem::Load() {
	std::vector<RankingData> loadScores;
	std::ifstream file(fileName);

	if (file.is_open()) {
		try {
			json j;
			file >> j;

			// ここが重要！JSONの配列から名前とスコアをセットで取り出す
			if (j.contains("scores") && j["scores"].is_array()) {
				for (auto& item : j["scores"]) {
					RankingData data;
					data.name = item.value("name", "Unknown");
					data.score = item.value("score", 0);
					loadScores.push_back(data);
				}
			}
		}
		catch (...) {
			// ファイルが壊れていた時の安全策
		}
		file.close();
	}

	return loadScores;
}

void ScoreSystem::Save() {
	json j_array = json::array();

	for (const auto& item : scores_) {
		// 名前とスコアをペアにして配列に入れる
		j_array.push_back({ {"name", item.name}, {"score", item.score} });
	}

	json j_final;
	j_final["scores"] = j_array;

	std::ofstream file(fileName);
	if (file.is_open()) {
		file << j_final.dump(4);
		file.close();
	}
}

const std::vector<RankingData>& ScoreSystem::GetScores() const {
	return scores_;
}

void ScoreSystem::Reset() {
	scores_.clear();
	Save();
}



void ScoreSystem::DrawScoreSprite(Vector2 pos, int score, float spacing) {
	std::string s = std::to_string(score);

	for (int i = 0; i < s.length(); i++) {
		int num = s[i] - '0';

		Vector2 pos_ = { pos.x + spacing * i,pos.y };

		Vector2 screenPos = camera.WorldToScreen(pos_);

	if (screenPos.y >= 230.0f && screenPos.y <= 510.0f) {

			Novice::DrawSprite(
				static_cast<int>(screenPos.x),
				static_cast<int>(screenPos.y),
				numberTexture[num], 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
}

void ScoreSystem::DrawNameSprite(Vector2 pos, std::string& name, float spacing) {
	for (int i = 0; i < static_cast<int>(name.length()); i++) {
		char ch = name[i];
		int index = -1;
		int* textureArray = nullptr;

		// 文字種を判定してインデックスと配列を決定
		if (ch >= 'A' && ch <= 'Z') {
			index = ch - 'A';
			textureArray = upperAlphabetTexture;
		}
		else if (ch >= 'a' && ch <= 'z') {
			index = ch - 'a';
			textureArray = lowAlphabetTexture;
		}
		else if (ch >= '0' && ch <= '9') {
			index = ch - '0';
			textureArray = numberTexture;
		}

		// 有効な文字の場合のみ描画
		if (index != -1 && textureArray != nullptr) {

			Vector2 pos_ = { pos.x + spacing * i, pos.y };
			Vector2 screenPos = camera.WorldToScreen(pos_);
			if (screenPos.y >= 230.0f && screenPos.y <= 510.0f) {
				Novice::DrawSprite(
					static_cast<int>(screenPos.x),
					static_cast<int>(screenPos.y),
					textureArray[index],
					1.0f,
					1.0f,
					0.0f,
					WHITE
				);
			}
		}
	}
}

void ScoreSystem::ScrollRanking(char* keys) {
	if (isAutoScrolling) {
		// 自動スクロール処理（変更なし）
		scrollEasing.Update();
		float newY = scrollEasing.easingRate;
		camera.SetCameraPosition({ camera.GetCameraInfo().centerpos.x, newY });

		if (!scrollEasing.isMove) {
			isAutoScrolling = false;
		}
	}
	else {
		// --- 手動スクロール（範囲制限付き）---
		float moveSpeed = 5.0f;
		float currentY = camera.GetCameraInfo().centerpos.y;
		float nextY = currentY;

		if (keys[DIK_W]) nextY += moveSpeed;  // 上方向（1位側へ）
		if (keys[DIK_S]) nextY -= moveSpeed;  // 下方向（最下位側へ）

		// ランキングが空でなければ範囲制限を適用
		if (!scores_.empty() && (keys[DIK_W] || keys[DIK_S])) {
			int lastIndex = static_cast<int>(scores_.size()) - 1;

			// 1位のY座標（画面上端の限界 - 1位が中央に来る位置）
			float firstPlaceY = rankBasePos.y;

			// 最下位のY座標（画面下端の限界 - 最下位が中央に来る位置）
			float lastPlaceY = rankBasePos.y - (lastIndex * rowHeight);

			// Clamp: 1位と最下位の間に制限
			// nextY > firstPlaceY → 1位より上には行かない（1位が中央より上に来ない）
			// nextY < lastPlaceY → 最下位より下には行かない（最下位が中央より下に来ない）
			if (nextY > firstPlaceY) {
				nextY = firstPlaceY;
			}
			if (nextY < lastPlaceY) {
				nextY = lastPlaceY;
			}

			camera.SetCameraPosition({ camera.GetCameraInfo().centerpos.x, nextY });
		}
		else if (!scores_.empty()) {
			// キー入力がない場合も、現在位置が範囲外なら補正（安全のため）
			camera.MoveCameraTransform();
			return; // このreturnはMoveCameraTransformをスキップしないように注意
		}
	}

	camera.MoveCameraTransform();
}

void ScoreSystem::FocusOnLastAdded() {
	// 現在のカメラY座標を取得
	float startY = camera.GetCameraInfo().centerpos.y;

	// 目標Y座標を計算
	float targetY = rankBasePos.y + (lastAddedIndex * -rowHeight);

	// ★デバッグ：値を確認（コンソールに出力）
	

	// ★重要：以前の自動スクロールを確実に終了させる
	isAutoScrolling = false;
	scrollEasing.Reset();

	// 目標位置が現在位置と同じ場合は自動スクロール不要
	// イージング初期化（60フレームかけて移動）
	scrollEasing.Init(startY, targetY, 60, EasingType::EASING_EASE_OUT_QUART);
	scrollEasing.Start();
	isAutoScrolling = true;
}

void ScoreSystem::FocusOnFirstPlace() {
	if (scores_.empty()) return;

	// 1位のY座標（rankBasePos.y が1位の基準位置）
	float targetY = rankBasePos.y;

	// カメラを即座に1位の位置に設定（アニメーションなし）
	camera.SetCameraPosition({ camera.GetCameraInfo().centerpos.x, targetY });
	camera.MoveCameraTransform();

	// 自動スクロール中なら解除
	isAutoScrolling = false;
}

void ScoreSystem::DrawScoreSprite(Vector2 pos, const std::string& s, float spacing) {
	for (int i = 0; i < s.length(); i++) {
		int num = s[i] - '0';
		Vector2 pos_ = { pos.x + spacing * i, pos.y };
		Vector2 screenPos = camera.WorldToScreen(pos_);

		if (screenPos.y >= 230.0f && screenPos.y <= 510.0f) {
			Novice::DrawSprite(
				static_cast<int>(screenPos.x),
				static_cast<int>(screenPos.y),
				numberTexture[num], 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
}

