#pragma once
#include "../SceneManager.h"


// 各シーン制御
class Scenes {
public:

	// テキスト、オブジェクト描画
	virtual void  Render() {}
	// 毎フレーム更新
	virtual void  Update(float deltaTime) {}

	virtual void Destroy() {}
};