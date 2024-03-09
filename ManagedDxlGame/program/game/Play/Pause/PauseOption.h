#pragma once
#include <string>

constexpr static int MENU_INDEX = 4;


class PauseOption
{
public:

	// ����-----------------------------------------------------------------------------------------
	void GoNextOrGoBack();
	void AdjustVolumeByInput();
	void PickMenuItemByInput();

	// �F-------------------------------------------------------------------------------------------
	void ChangePauseOptionColor();
	void ChangeSelectEffectColorAndBrightness(int& eff1_color, int& eff2_color, int& eff3_color);

	// �`��------------------------------------------------------------------------------------------
	void RenderLowMediumHighWord(int& eff1_color, int& eff2_color, int& eff3_color);
	void RenderAdjustVolumeObject();
	void RenderMenuItems_AndDescriptions();

	// �X�V------------------------------------------------------------------------------------------
	void UpdatePauseMenuCursor_ByInput();
	void UpdatePauseOptionCursor_ByInput();
	void UpdateSelectEffectCursor_ByInput();

public:

	bool showOption{};    
	bool selectEffectColor{};
	int effectIndex = 2;

private:

	int menuIndex = 0;      // ���j���[
	int optionIndex{};      // �I�v�V����

	int volumeIndex = 180;  // ���ʂ������~�̍��W  ���W��0����300�܂�
	int volumeNum = 50;     // ���ʂ̒l �ܘ_ 0����100��
	int volNum_color = -1;  // ����(����)�̐F

	bool isAdjustVolume{};
	std::string volume_str{};
};