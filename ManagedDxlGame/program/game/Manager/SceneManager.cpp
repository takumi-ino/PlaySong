#include "SceneManager.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Result/SceneResult.h"


SceneManager::SceneManager(Scenes* scene) :_nowScene(scene) {
	_transGraph_hdl = LoadGraph("graphics/black.bmp");
}


SceneManager* SceneManager::GetInstance(Scenes* scene) {

	static SceneManager* instance = nullptr;

	if (!instance) {

		instance = new SceneManager(scene);
	}

	return instance;
}


void SceneManager::SceneChange(Scenes* NEXT, float TIME) {

	_nextScene = NEXT;
	_transTime = TIME;

	sequence_.change(&SceneManager::SeqFadeOut);
}


void SceneManager::Update(float deltaTime) {

	if (_nowScene) 
		_nowScene->Update(deltaTime);    // 現在のシーン更新

	if (_nowScene)
		_nowScene->Render();

	sequence_.update(deltaTime);
}


bool SceneManager::SeqFadeOut(const float deltaTime) {  // フェードアウト

	float brightAlpha = (sequence_.getProgressTime() / _transTime * 255.0f);
	
	if (brightAlpha >= 255.f) {

		sequence_.change(&SceneManager::SeqFadeIn);
		_nowScene->Destroy();

		delete _nowScene;
		_nowScene = _nextScene;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightAlpha));
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, _transGraph_hdl, true);
	SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 255);

	return true;
}


bool SceneManager::SeqFadeIn(const float deltaTime) {       // フェードイン

	float brightAlpha = 255.f - (sequence_.getProgressTime() / _transTime * 255.0f);

	if (brightAlpha <= 0.f)
		sequence_.change(&SceneManager::SeqRun);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(brightAlpha));
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, _transGraph_hdl, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	return true;
}


bool SceneManager::SeqRun(const float deltaTime) {
	return true;
}


void SceneManager::Destroy() {

	delete GetInstance();
}