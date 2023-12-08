#include "../Title/SceneTitle.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Play/ScenePlaySong.h"
#include "../Result/SceneResult.h"
#include "../Main.h"


void Title::Update(float deltaTime) {

	sequence.update(deltaTime);

	// ”wŒiFƒZƒbƒg
	if (_fadeIO) {

		int alpha = (sequence.getProgressTime() / 1.0f * 255.0f);

		if (alpha >= _maxAlphaSize)  alpha = _maxAlphaSize;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, whiteImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	if (_alpha < 360.f) {

		_alpha += 0.1f;


	}
	if (_alpha >= 360.f) {

		_alpha = 0.f;
	}

	float flash = sin(_alpha) * 120.f;


	SetFontSize(60);
	DrawStringEx(_titleLog_x, DXE_WINDOW_HEIGHT / 4, -1, "Play Song");
	SetFontSize(30);
	DrawStringEx(_START_TEXT_POS_X, _start_text_y, GetColor(flash, flash, flash), "start");
}




bool Title::SeqIdle(float deltaTime) {

	if (sequence.isStart()) {

		_fadeIO = true;
		whiteImg = LoadGraph("graphics/white.bmp");
	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

		if (!soundPlayed) {

			PlaySoundMem(titleToSelectMenu_hdl, DX_PLAYTYPE_BACK, TRUE);
			soundPlayed = true;
		}
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
		moveToSongSelect = true;
	}

	if (moveToSongSelect) {

		soundPlayed = false;
		StopSoundMem(title_BGM_hdl);
		SetCurrentPositionSoundMem(0, title_BGM_hdl);
	}
	else {

		PlaySoundMem(title_BGM_hdl, DX_PLAYTYPE_LOOP, FALSE);
	}

	return true;
}