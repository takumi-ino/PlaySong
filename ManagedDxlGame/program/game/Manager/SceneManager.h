#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"


class Scenes;

class SceneManager {
public:

	static SceneManager* GetInstance(Scenes* scene = nullptr);
	static void Destroy();

	// �^�C�g����ʁA�ȑI����ʁA�v���C��ʁA���U���g���
	void SceneChange(Scenes* next, float time = 0.5f);
	void Update(float deltaTime);

private:

	SceneManager(Scenes* scene);
	~SceneManager();

	tnl::Sequence<SceneManager> sequence_ = tnl::Sequence<SceneManager>(this, &SceneManager::SeqFadeIn);

	bool SeqFadeOut(const float deltaTime);
	bool SeqFadeIn(const float deltaTime);
	bool SeqRun(const float deltaTime);

private:

	Scenes* _nowScene = nullptr;
	Scenes* _nextScene = nullptr;
	float _transitionTime = 0.5f;   // �J�ڂɊ|���鎞��
	int _BG_gfx = 0;
};