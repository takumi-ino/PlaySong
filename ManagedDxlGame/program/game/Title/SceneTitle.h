#pragma once
#include "../Manager/Scene/SceneBase.h"


class Title : public Scenes 
{
public:

	Title();

	void Update(float deltaTime) override;

	void ApplyFlushEffectOnText();

	void MoveToSelectSongMenu();

	void StopTitleBGM();

private:

	float brightnessAlpha = 0.f;

	bool  _moveToSongSelect = false;
	bool  _soundPlayed = false;      // SE‰¹˜A‘Å–hŽ~—p
};