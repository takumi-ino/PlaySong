#include <string>
#include "PauseOption.h"
#include "../../utility/DxLib_Engine.h"
#include "../../Play/ScenePlaySong.h"
#include "../../Manager/SoundManager.h"
#include "../Timer/Timer.h"


namespace {

	const int PAUSEOPTION_MAXITEM_NUM = 2;  // VOLUMEとSCREEN_EFFECT
	const int EFFECTOPTION_MAXITEM_NUM = 3; // low, medium, high

	const int LEFTSIDE = 50;
	const int UPSIDE = 100;
}


void PauseOption::UpdatePauseMenuCursor_ByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
	{
		_menuIndex--;
		if (_menuIndex < 0)
			_menuIndex = MENU_INDEX - 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
	{
		_menuIndex++;
		if (_menuIndex >= MENU_INDEX) 
			_menuIndex = 0;
	}
}


void PauseOption::RenderMenuItems_AndDescriptions() {

	int rightSide = 500;
	int r = -1, g = -1, b = -1, a = -1;

	for (int i = 0; i < MENU_INDEX; i++) {

		if (i == _menuIndex && _menuIndex == 0)	// ゲーム再開
		{
			r = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "You Ready?", -1);
		}
		else if (i == _menuIndex && _menuIndex == 1)	// オプション
		{
			g = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "You can Fix kind of Settings", -1);
		}
		else if (i == _menuIndex && _menuIndex == 2)	// 初めからやり直す
		{
			b = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "Try again,\n I'm sure you can do it", -1);
		}
		else if (i == _menuIndex && _menuIndex == 3)	// 選択中の曲なら色を変える
		{
			a = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "That's ok! We'll be waiting \n for your next challenge", -1);
		}

		//-------------------------------------------- 
		int leftSide = 140;
		DrawString(leftSide, DXE_WINDOW_HEIGHT / 3 - 30, "CONTINUE", r);
		DrawString(leftSide, DXE_WINDOW_HEIGHT / 3,      "OPTION", g);
		DrawString(leftSide, DXE_WINDOW_HEIGHT / 3 + 30, "RESTART", b);
		DrawString(leftSide, DXE_WINDOW_HEIGHT / 3 + 60, "QUIT", a);
	}
}


void PauseOption::PickMenuItemByInput() {

	if (_menuIndex == 0) { // ゲーム再開	

		PlaySong::_timer->Resume();
		PlaySong::_isPaused = false;
	}

	if (_menuIndex == 1) { // オプションを開く
	 
		_showOption = true; 
	}  

	if (_menuIndex == 2) { // リトライ

		PlaySong::_isRetryGame = true;
	}

	if (_menuIndex == 3) { // 曲選択へ戻る

		StopSoundMem(pause_BGM_hdl);  // ポーズ画面BGM停止
		SetCurrentPositionSoundMem(0, pause_BGM_hdl);

		PlaySong::_isPaused = false;
		PlaySong::_moveToSongSelect = true;
	}
}


void PauseOption::UpdateDetailOptionCursor_ByInput() {

	if (!_isAdjustingVolume && !_isSelectEffectColor) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
		{
			_detailOptionIndex--;

			if (_detailOptionIndex < 0) 
				_detailOptionIndex = PAUSEOPTION_MAXITEM_NUM - 1;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
		{
			_detailOptionIndex++;

			if (_detailOptionIndex >= PAUSEOPTION_MAXITEM_NUM) 
				_detailOptionIndex = 0;
		}
	}
}


void PauseOption::ChangePauseOptionColor() {

	int opt1_color = -1, opt2_color = -1;

	for (int i = 0; i < PAUSEOPTION_MAXITEM_NUM; i++) {

		if (i == _detailOptionIndex && _detailOptionIndex == 0)
			opt1_color = GetColor(255, 255, 0);    // Screen Effectの色	

		else if (i == _detailOptionIndex && _detailOptionIndex == 1)
			opt2_color = GetColor(255, 255, 0);    // Volumeの色
	}

	int x1_opt1 = LEFTSIDE, y1_opt1 = 100;
	int x1_opt2 = 50, y1_opt2 = y1_opt1 + 150;

	SetFontSize(50);
	// 音量調整
	DrawString(x1_opt1, y1_opt1, "Volume", opt1_color);
	// 明るさ調整
	DrawString(x1_opt2, y1_opt2, "Screen Effect", opt2_color);
}


void PauseOption::GoNextOrGoBack() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) { // 決定（エンター）

		if (_detailOptionIndex == 0)
			_isAdjustingVolume = true;        // Volume

		else if (_detailOptionIndex == 1)
			_isSelectEffectColor = true;  // ScreenEffect
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0)) {  // 戻る（バックスペース）

		if (!_isAdjustingVolume && !_isSelectEffectColor) {
			PauseOption::_showOption = false;
			SetFontSize(35);
		}

		if (_detailOptionIndex == 0) 
			_isAdjustingVolume = false;

		else if (_detailOptionIndex == 1) 
			_isSelectEffectColor = false;
	}
}


void PauseOption::AdjustVolumeByInput() {

	if (_isAdjustingVolume) {  // 以下、音量調整処理

		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {

			_volumeIndicator_x1 += 3; // 座標範囲 0～300
			_volumeSize++;      // 音量範囲 0～255

			ChangeVolumeSoundMem(_volumeSize * 255 / 100, songList[PlaySong::_songIndex]); // 音量調整
			ChangeVolumeSoundMem(_volumeSize * 255 / 100, pause_BGM_hdl);
		}

		if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {

			_volumeIndicator_x1 -= 3;
			_volumeSize--;

			ChangeVolumeSoundMem(_volumeSize * 255 / 100, songList[PlaySong::_songIndex]);
			ChangeVolumeSoundMem(_volumeSize * 255 / 100, pause_BGM_hdl);
		}

		if (_volumeIndicator_x1 <= 0)
			_volumeIndicator_x1 = 0;         // 座標変更

		else if (_volumeIndicator_x1 >= 350) 
			_volumeIndicator_x1 = 350;

		if (_volumeSize <= 0)
			_volumeSize = 0;           // 音量変更

		else if (_volumeSize >= 100) 
			_volumeSize = 100;

		_volumeNumberColor = GetColor(0, 255, 255);
	}
}


void PauseOption::AdjustScreenBrightnessByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)) {

		_screenBrightnessIndex++;
		if (_screenBrightnessIndex >= (EFFECTOPTION_MAXITEM_NUM)) 
			_screenBrightnessIndex = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)) {

		_screenBrightnessIndex--;
		if (_screenBrightnessIndex < 0) 
			_screenBrightnessIndex = EFFECTOPTION_MAXITEM_NUM - 1;
	}
}


void PauseOption::ChangeSelectEffectColorAndBrightness(int& eff1_color,int& eff2_color, int& eff3_color) {

	for (int i = 0; i < EFFECTOPTION_MAXITEM_NUM; i++) {

		if (i == _screenBrightnessIndex && _screenBrightnessIndex == 0) {

			eff1_color = GetColor(0, 255, 255);
			SetDrawBright(128, 128, 128); // Low
		}
		else if (i == _screenBrightnessIndex && _screenBrightnessIndex == 1) {

			eff2_color = GetColor(0, 255, 255);
			SetDrawBright(192, 192, 192); // Medium
		}
		else if (i == _screenBrightnessIndex && _screenBrightnessIndex == 2) {

			eff3_color = GetColor(0, 255, 255);
			SetDrawBright(255, 255, 255); // High
		}
	}
}


void PauseOption::RenderAdjustVolumeObject() {

	std::string volume_str = std::to_string(_volumeSize);
	DrawStringEx(LEFTSIDE + 380, UPSIDE + 50, _volumeNumberColor, volume_str.c_str());
	DrawBox(LEFTSIDE, UPSIDE + 60, LEFTSIDE + 350, UPSIDE + 70, -1, true);
	DrawCircle(LEFTSIDE + _volumeIndicator_x1, UPSIDE + 65, 10, -1, true);
}


void PauseOption::RenderBrightnessLevels(int& eff1_color,int& eff2_color,int& eff3_color) {

	// 画面の明るさ
	DrawStringEx(LEFTSIDE, UPSIDE + 210, eff1_color, "Low");           // 低
	DrawStringEx(LEFTSIDE + 140, UPSIDE + 210, eff2_color, "Medium");  // 中
	DrawStringEx(LEFTSIDE + 340, UPSIDE + 210, eff3_color, "High");    // 高
}