#include "../../Main.h"
#include "PauseOption.h"
#include "../../utility/tnlSequence.h"
#include "../../utility/DxLib_Engine.h"
#include "../Timer/Timer.h"
#include "../../Play/ScenePlaySong.h"
#include "../../Manager/SoundManager.h"


namespace {

	const int PAUSEOPTION_MAXITEM_NUM = 2;  // VOLUME��SCREEN_EFFECT
	const int EFFECTOPTION_MAXITEM_NUM = 3; // low, medium, high

	const int LEFTSIDE = 50;
	const int UPSIDE = 100;
}


void PauseOption::UpdatePauseMenuCursor_ByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
	{
		menuIndex--;
		if (menuIndex < 0) menuIndex = MENU_INDEX - 1;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
	{
		menuIndex++;
		if (menuIndex >= MENU_INDEX) menuIndex = 0;
	}
}


void PauseOption::RenderMenuItems_AndDescriptions() {

	int rightSide = 500;
	int r = -1, g = -1, b = -1, a = -1;

	for (int i = 0; i < MENU_INDEX; i++) {

		if (i == menuIndex && menuIndex == 0)	// �Q�[���ĊJ
		{
			r = GetColor(255, 255, 0);
			DrawStringEx(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, -1, "You Ready?");
		}
		else if (i == menuIndex && menuIndex == 1)	// �I�v�V����
		{
			g = GetColor(255, 255, 0);
			DrawStringEx(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, -1, "You can Fix kind of Settings");
		}
		else if (i == menuIndex && menuIndex == 2)	// ���߂����蒼��
		{
			b = GetColor(255, 255, 0);
			DrawStringEx(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, -1, "Try again,\n I'm sure you can do it");
		}
		else if (i == menuIndex && menuIndex == 3)	// �I�𒆂̋ȂȂ�F��ς���
		{
			a = GetColor(255, 255, 0);
			DrawStringEx(rightSide, DXE_WINDOW_HEIGHT / 2 - 50, -1, "That's ok! We'll be waiting \n for your next challenge");
		}
		//-------------------------------------------- 
		int leftSide = 140;
		DrawStringEx(leftSide, DXE_WINDOW_HEIGHT / 3 - 30, r, "CONTINUE");
		DrawStringEx(leftSide, DXE_WINDOW_HEIGHT / 3, g, "OPTION");
		DrawStringEx(leftSide, DXE_WINDOW_HEIGHT / 3 + 30, b, "RESTART");
		DrawStringEx(leftSide, DXE_WINDOW_HEIGHT / 3 + 60, a, "QUIT");
	}
}


bool PauseOption::isRetryGame;

void PauseOption::PickMenuItemByInput() {

	if (menuIndex == 0) { // �Q�[���ĊJ	

		PlaySong::_timer->Resume();
	}

	if (menuIndex == 1) { // �I�v�V�������J��
	 
		showOption = true; 
	}  

	if (menuIndex == 2) { // ���g���C

		isRetryGame = true;
	}

	if (menuIndex == 3) { // �ȑI���֖߂�

		StopSoundMem(pause_BGM_hdl);  // �|�[�Y���BGM��~
		SetCurrentPositionSoundMem(0, pause_BGM_hdl);
		PlaySong::currentState = 2;
	}
}



void PauseOption::UpdatePauseOptionCursor_ByInput() {

	if (!isAdjustVolume && !selectEffectColor) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
		{
			optionIndex--;

			if (optionIndex < 0) 
				optionIndex = PAUSEOPTION_MAXITEM_NUM - 1;
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
		{
			optionIndex++;

			if (optionIndex >= PAUSEOPTION_MAXITEM_NUM) 
				optionIndex = 0;
		}
	}
}



void PauseOption::ChangePauseOptionColor() {

	int opt1_color = -1, opt2_color = -1;

	for (int i = 0; i < PAUSEOPTION_MAXITEM_NUM; i++) {

		if (i == optionIndex && optionIndex == 0)
			opt1_color = GetColor(255, 255, 0);    // Screen Effect�̐F					
		else if (i == optionIndex && optionIndex == 1)
			opt2_color = GetColor(255, 255, 0);    // Volume�̐F
	}

	int x1_opt1 = LEFTSIDE, y1_opt1 = 100;
	int x1_opt2 = 50, y1_opt2 = y1_opt1 + 150;

	SetFontSize(50);
	// ���ʒ���
	DrawStringEx(x1_opt1, y1_opt1, opt1_color, "Volume");
	// ���邳����
	DrawStringEx(x1_opt2, y1_opt2, opt2_color, "Screen Effect");
}



void PauseOption::GoNextOrGoBack() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) { // ����i�G���^�[�j

		if (optionIndex == 0)
			isAdjustVolume = true;        // Volume
		else if (optionIndex == 1)
			selectEffectColor = true;   // ScreenEffect
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0)) {  // �߂�i�o�b�N�X�y�[�X�j

		if (!isAdjustVolume && !selectEffectColor) {
			PauseOption::showOption = false;
			SetFontSize(35);
		}

		if (optionIndex == 0) 
			isAdjustVolume = false;
		else if (optionIndex == 1) 
			selectEffectColor = false;
	}
}


void PauseOption::AdjustVolumeByInput() {

	if (isAdjustVolume) {  // �ȉ��A���ʒ�������

		if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT) || tnl::Input::IsPadDown(ePad::KEY_RIGHT)) {

			volumeIndex += 3; // ���W�͈� 0�`300
			volumeNum++;      // ���ʔ͈� 0�`255

			ChangeVolumeSoundMem(volumeNum * 255 / 100, songList[PlaySong::songIndex]); // ���ʒ���
			ChangeVolumeSoundMem(volumeNum * 255 / 100, pause_BGM_hdl);
		}

		if (tnl::Input::IsKeyDown(eKeys::KB_LEFT) || tnl::Input::IsPadDown(ePad::KEY_LEFT)) {

			volumeIndex -= 3;
			volumeNum--;

			ChangeVolumeSoundMem(volumeNum * 255 / 100, songList[PlaySong::songIndex]);
			ChangeVolumeSoundMem(volumeNum * 255 / 100, pause_BGM_hdl);
		}

		if (volumeIndex <= 0)
			volumeIndex = 0;         // ���W
		else if (volumeIndex >= 350) 
			volumeIndex = 350;

		if (volumeNum <= 0)
			volumeNum = 0;           // ����
		else if (volumeNum >= 100) 
			volumeNum = 100;

		volNum_color = GetColor(0, 255, 255);
	}
}



void PauseOption::UpdateSelectEffectCursor_ByInput() {

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)) {

		effectIndex++;
		if (effectIndex >= (EFFECTOPTION_MAXITEM_NUM)) effectIndex = 0;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)) {

		effectIndex--;
		if (effectIndex < 0) effectIndex = EFFECTOPTION_MAXITEM_NUM - 1;
	}
}



void PauseOption::ChangeSelectEffectColorAndBrightness(int& eff1_color,int& eff2_color, int& eff3_color) {

	for (int i = 0; i < EFFECTOPTION_MAXITEM_NUM; i++) {

		if (i == effectIndex && effectIndex == 0) {

			eff1_color = GetColor(0, 255, 255);
			SetDrawBright(128, 128, 128); // Low
		}
		else if (i == effectIndex && effectIndex == 1) {

			eff2_color = GetColor(0, 255, 255);
			SetDrawBright(192, 192, 192); // Medium
		}
		else if (i == effectIndex && effectIndex == 2) {

			eff3_color = GetColor(0, 255, 255);
			SetDrawBright(255, 255, 255); // High
		}
	}
}



void PauseOption::RenderAdjustVolumeFunc() {

	volume_str = std::to_string(volumeNum);
	DrawStringEx(LEFTSIDE + 380, UPSIDE + 50, volNum_color, volume_str.c_str());
	DrawBox(LEFTSIDE, UPSIDE + 60, LEFTSIDE + 350, UPSIDE + 70, -1, true);
	DrawCircle(LEFTSIDE + volumeIndex, UPSIDE + 65, 10, -1, true);
}



void PauseOption::RenderLowMediumHighWord(int& eff1_color,int& eff2_color,int& eff3_color) {

	// ��ʂ̖��邳
	DrawStringEx(LEFTSIDE, UPSIDE + 210, eff1_color, "Low");           // ��
	DrawStringEx(LEFTSIDE + 140, UPSIDE + 210, eff2_color, "Medium");  // ��
	DrawStringEx(LEFTSIDE + 340, UPSIDE + 210, eff3_color, "High");    // ��
}