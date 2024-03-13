#include "../Title/SceneTitle.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Play/ScenePlaySong.h"
#include "../Result/SceneResult.h"


namespace {

	const int _maxAlphaSize = 38;

	const int _titleLog_x = 444;
	const int _START_TEXT_POS_X = 580;
	const int _start_text_y = 480;
}


Title::Title() {

	SoundManager::GetInstance()->LoadPlayListSongs();
}


void Title::ApplyFlushEffectOnText()
{
	// アルファ値を変更
	brightnessAlpha = (brightnessAlpha < 360.0f) ? brightnessAlpha += 0.1f : brightnessAlpha = 0.0f;

	float flash = sin(brightnessAlpha) * 120.f;

	SetFontSize(60);
	DrawStringEx(_titleLog_x, DXE_WINDOW_HEIGHT / 4, -1, "Play Song");
	SetFontSize(30);
	DrawStringEx(_START_TEXT_POS_X, _start_text_y, GetColor((int)flash, (int)flash, (int)flash), "start");
}


void Title::MoveToSelectSongMenu()
{
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		if (!_soundPlayed) {

			PlaySoundMem(titleToSelectMenu_hdl, DX_PLAYTYPE_BACK, TRUE);
			_soundPlayed = true;
		}

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
		_moveToSongSelect = true;
	}
}


void Title::StopTitleBGM()
{
	if (_moveToSongSelect) {

		_soundPlayed = false;
		StopSoundMem(title_BGM_hdl);
		SetCurrentPositionSoundMem(0, title_BGM_hdl);
	}
	else {

		PlaySoundMem(title_BGM_hdl, DX_PLAYTYPE_LOOP, FALSE);
	}
}


void Title::Update(float deltaTime) {

	ApplyFlushEffectOnText();

	MoveToSelectSongMenu();

	StopTitleBGM();
}