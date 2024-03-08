#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"


class Title : public Scenes 
{
public:

	void Update(float deltaTime) override;

private:

	tnl::Sequence<Title> sequence = tnl::Sequence<Title>(this, &Title::SeqIdle);
	bool SeqIdle(float deltaTime);

private:

	int   whiteImg{};	// ƒV[ƒ“‘JˆÚ—p‰æ‘œ
	float brightnessAlpha = 0;

	bool  fadeIO = false;
	bool  moveToSongSelect = false;
	bool  soundPlayed = false;
};