#include <Novice.h>
#include "Scene.h" 

const char kWindowTitle[] = "コジマ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	//Novice::SetWindowMode(WindowMode::kFullscreen);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	SceneManager sceneManager;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		///
		/// ↑更新処理ここまで
		///

		sceneManager.UpdateCurrentScene(keys, preKeys);

		///
		/// ↓描画処理ここから
		///

		sceneManager.DrawCurrentScene();

		//unsigned int color = WHITE; // semi-transparent red
		//Novice::DrawBox(320, 180, 640, 360, 0.0f, color, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0 &&
			sceneManager.GetCurrentSceneType() == SceneType::Title) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
