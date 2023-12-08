#include "SceneManager.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Result/SceneResult.h"

 
void SceneManager::Destroy() {
	delete GetInstance();
}


SceneManager::~SceneManager() {

	if (_nowScene != nullptr) {
		delete _nowScene;
		_nowScene = nullptr;
	}
}


SceneManager* SceneManager::GetInstance(Scenes* scene) {
	static SceneManager* instance = nullptr;

	if (!instance) 	instance = new SceneManager(scene);
	return instance;
}


SceneManager::SceneManager(Scenes* scene) :_nowScene(scene) {
	_BG_gfx = LoadGraph("graphics/black.bmp");     // �t�F�[�h�C���A�t�F�[�h�A�E�g�p�摜
}


void SceneManager::SceneChange(Scenes* NEXT, float TIME) {
	_nextScene = NEXT;
	_transitionTime = TIME;


	sequence_.change(&SceneManager::SeqFadeOut);
}


void SceneManager::Update(float deltaTime) {

	if (_nowScene) _nowScene->Update(deltaTime);    // ���݂̃V�[���X�V
	if (_nowScene) _nowScene->Render();             // ���݂̃V�[���`��

	sequence_.update(deltaTime);
}


bool SceneManager::SeqFadeOut(const float deltaTime) {  // �t�F�[�h�A�E�g

	int alpha = (sequence_.getProgressTime() / _transitionTime * 255.0f);
	
	if (alpha >= 255) {

		sequence_.change(&SceneManager::SeqFadeIn);
		_nowScene->Destroy();

		delete _nowScene;
		_nowScene = nullptr;
		_nowScene = _nextScene;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, _BG_gfx, true);
	SetDrawBlendMode(DX_GRAPH_BLEND_NORMAL, 255);
	return true;
}


bool SceneManager::SeqFadeIn(const float deltaTime) {       // �t�F�[�h�C��
	int alpha = 255 - (sequence_.getProgressTime() / _transitionTime * 255.0f);

	if (alpha <= 0)		sequence_.change(&SceneManager::SeqRun);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, _BG_gfx, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	return true;
}


bool SceneManager::SeqRun(const float deltaTime) {
	return true;
}