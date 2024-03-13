#include <string>
#include "PauseOption.h"
#include "../../utility/DxLib_Engine.h"
#include "../../Play/ScenePlaySong.h"
#include "../../Manager/SoundManager.h"
#include "../Timer/Timer.h"


namespace {

	const int PAUSEOPTION_MAXITEM_NUM = 2;  // VOLUME��SCREEN_EFFECT
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

		if (i == _menuIndex && _menuIndex == 0)	// �Q�[���ĊJ
		{
			r = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "You Ready?", -1);
		}
		else if (i == _menuIndex && _menuIndex == 1)	// �I�v�V����
		{
			g = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "You can Fix kind of Settings", -1);
		}
		else if (i == _menuIndex && _menuIndex == 2)	// ���߂����蒼��
		{
			b = GetColor(255, 255, 0);
			DrawString(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, "Try again,\n I'm sure you can do it", -1);
		}
		else if (i == _menuIndex && _menuIndex == 3)	// �I�𒆂̋ȂȂ�F��ς���
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

	if (_menuIndex == 0) { // �Q�[���ĊJ	

		PlaySong::_timer->Resume();
		PlaySong::_isPaused = false;
	}

	if (_menuIndex == 1) { // �I�v�V�������J��
	 
		_showOption = true; 
	}  

	if (_menuIndex == 2) { // ���g���C

		PlaySong::_isRetryGame = true;
	}

	if (_menuIndex == 3) { // �ȑI���֖߂�

		StopSoundMem(pause_BGM_hdl);  // �|�[�Y���BGM��~
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
			opt1_color = GetColor(255, 255, 0);    // Screen Effect�̐F	

		else if (i == _detailOptionIndex && _detailOptionIndex == 1)
			opt2_color = GetColor(255, 255, 0);    // Volume�̐F
	}

	int x1_opt1 = LEFTSIDE, y1_opt1 = 100;
	int x1_opt2 = 50, y1_opt2 = y1_opt1 + 150;

	SetFontSize(50);
	// ���ʒ���
	DrawString(x1_opt1, y1_opt1, "Volume", opt1_color);
	// ���邳����
	DrawString(x1_opt2, y1_opt2, "Screen Effect", opt2_color);
}


void PauseOption::GoNextOrGoBack() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) { // ����i�G���^�[�j

		if (_detailOptionIndex == 0)
			_isAdjustingVolume = true;        // Volume

		else if (_detailOptionIndex == 1)
			_isSelectEffectColor = true;  // ScreenEffect
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0)) {  // �߂�i�o�b�N�X�y�[�X�j

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

	if (_isAdjustingVolume) {  // �ȉ��A���ʒ�������

		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {

			_volumeIndicator_x1 += 3; // ���W�͈� 0�`300
			_volumeSize++;      // ���ʔ͈� 0�`255

			ChangeVolumeSoundMem(_volumeSize * 255 / 100, songList[PlaySong::_songIndex]); // ���ʒ���
			ChangeVolumeSoundMem(_volumeSize * 255 / 100, pause_BGM_hdl);
		}

		if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {

			_volumeIndicator_x1 -= 3;
			_volumeSize--;

			ChangeVolumeSoundMem(_volumeSize * 255 / 100, songList[PlaySong::_songIndex]);
			ChangeVolumeSoundMem(_volumeSize * 255 / 100, pause_BGM_hdl);
		}

		if (_volumeIndicator_x1 <= 0)
			_volumeIndicator_x1 = 0;         // ���W�ύX

		else if (_volumeIndicator_x1 >= 350) 
			_volumeIndicator_x1 = 350;

		if (_volumeSize <= 0)
			_volumeSize = 0;           // ���ʕύX

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

	// ��ʂ̖��邳
	DrawStringEx(LEFTSIDE, UPSIDE + 210, eff1_color, "Low");           // ��
	DrawStringEx(LEFTSIDE + 140, UPSIDE + 210, eff2_color, "Medium");  // ��
	DrawStringEx(LEFTSIDE + 340, UPSIDE + 210, eff3_color, "High");    // ��
}