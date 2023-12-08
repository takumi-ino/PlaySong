#pragma once
#include <string>

#define MENU_INDEX 4


class PauseOption
{
public:

	void UpdatePauseMenuCursor_ByInput();

	void UpdatePauseOptionCursor_ByInput();

	void UpdateSelectEffectCursor_ByInput();

	void ChangePauseOptionColor();

	void ChangeSelectEffectColorAndBrightness(int& eff1_color, int& eff2_color, int& eff3_color);

	void GoNextOrGoBack();

	void AdjustVolumeByInput();

	void RenderAdjustVolumeFunc();

	void RenderMenuItems_AndDescriptions();

	void PickMenuItemByInput();

	void RenderLowMediumHighWord(int& eff1_color, int& eff2_color, int& eff3_color);

public:

	bool isRetryGame ;    // ���ʂ������~�̍��W  ���W��0����300�܂�
	bool showOption;      // ���ʂ̒l �ܘ_ 0����100��
	bool selectEffColor;  // ����(����)�̐F
	int effectIndex = 2;  // �𑜓x�̃��x��

private:

	int menuIndex = 0;   // ���j���[
	int optionIndex;     // �I�v�V����
	const int PAUSEOPTION_MAXITEM_NUM = 2;  // VOLUME��SCREEN_EFFECT
	const int EFFECTOPTION_MAXITEM_NUM = 3; // low, medium, high

	const int LEFTSIDE = 50;
	const int UPSIDE = 100;

	int volumeIndex = 180; // ���ʂ������~�̍��W  ���W��0����300�܂�
	int volumeNum = 50;    // ���ʂ̒l �ܘ_ 0����100��
	int volNum_color = -1; // ����(����)�̐F

	bool isAdjustVolume;
	std::string volume_str;
};