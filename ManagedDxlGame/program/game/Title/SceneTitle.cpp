#include "../Title/SceneTitle.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Play/ScenePlaySong.h"
#include "../Result/SceneResult.h"
#include "../Main.h"


namespace {

	const int _maxAlphaSize = 38;

	const int _titleLog_x = 444;
	const int _START_TEXT_POS_X = 580;
	const int _start_text_y = 480;
}


void Title::Update(float deltaTime) {

	sequence.update(deltaTime);

	// îwåiêFÉZÉbÉg
	if (fadeIO) {

		int brightnessAlpha = static_cast<int>((sequence.getProgressTime() / 1.0f * 255.0f));

		if (brightnessAlpha >= _maxAlphaSize)  
			brightnessAlpha = _maxAlphaSize;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightnessAlpha);
		DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, whiteImg, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}


	brightnessAlpha = (brightnessAlpha < 360.0f) ? brightnessAlpha += 0.1f : brightnessAlpha = 0.0f;

	float flash = sin(brightnessAlpha) * 120.f;

	SetFontSize(60);
	DrawStringEx(_titleLog_x, DXE_WINDOW_HEIGHT / 4, -1, "Play Song");
	SetFontSize(30);
	DrawStringEx(_START_TEXT_POS_X, _start_text_y, GetColor((int)flash, (int)flash, (int)flash), "start");
}


bool Title::SeqIdle(float deltaTime) {

	if (sequence.isStart()) {

		fadeIO = true;
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