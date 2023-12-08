#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"


class Title : public Scenes {
public:

	// メンバ変数初期化
	Title() : _maxAlphaSize(38) {}

	void Update(float deltaTime) override;

private:

	int whiteImg;	// シーン遷移用画像

	const int _maxAlphaSize;

	const int _titleLog_x = 444;
	const int _START_TEXT_POS_X = 580;
	const int _start_text_y = 480;

	bool _fadeIO = false;
	bool moveToSongSelect = false;
	bool soundPlayed = false;


	float _alpha = 0;

	tnl::Sequence<Title> sequence = tnl::Sequence<Title>(this, &Title::SeqIdle);
	bool SeqIdle(float deltaTime);
};