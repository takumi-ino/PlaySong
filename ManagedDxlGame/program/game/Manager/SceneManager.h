#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"


class Scenes;

class SceneManager {
private:

	explicit SceneManager(Scenes* start_scene);

	tnl::Sequence<SceneManager> sequence_ = tnl::Sequence<SceneManager>(this, &SceneManager::SeqFadeIn);

	bool SeqFadeOut(const float deltaTime);
	bool SeqFadeIn(const float deltaTime);
	bool SeqRun(const float deltaTime);

public:

	static SceneManager* GetInstance(Scenes* scene = nullptr);

	void Destroy();

	// タイトル画面、曲選択画面、プレイ画面、リザルト画面
	void SceneChange(Scenes* next, float time = 0.5f);

	void Update(float deltaTime);

private:

	Scenes* _nowScene = nullptr;
	Scenes* _nextScene = nullptr;

private:

	float _transTime = 0.5f;
	int   _transGraph_hdl = 0;
};