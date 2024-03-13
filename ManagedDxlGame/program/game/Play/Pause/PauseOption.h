#pragma once

constexpr static int MENU_INDEX = 4;


class PauseOption
{
public:

	// ����-----------------------------------------------------------------------------------------
	void GoNextOrGoBack();                // �I��
	void PickMenuItemByInput();           // ����
	void AdjustVolumeByInput();           // ���ʒ���
	void AdjustScreenBrightnessByInput(); // ��ʂ̖��邳����

	// �ڍאݒ�i���ʁE��ʂ̖��邳�j---------------------------------------------------------------
	void ChangePauseOptionColor();              // �F�ύX
	void ChangeSelectEffectColorAndBrightness(  // ��ʂ̖��邳�ύX
		int& eff1_color, int& eff2_color, int& eff3_color
	);

	// �`��------------------------------------------------------------------------------------------
	void RenderBrightnessLevels(              // ��ʂ̖��邳(Low, Medium, High) 
		int& eff1_color,
		int& eff2_color, 
		int& eff3_color
	);
	void RenderAdjustVolumeObject();          // ���ʒ����̂��߂̐}�`
	void RenderMenuItems_AndDescriptions();   // �e��|�[�Y���j���[�Ƃ��̐�����

	// �X�V(���͂ɂ���ē����J�[�\���j---------------------------------------------------------------
	void UpdatePauseMenuCursor_ByInput();     // �|�[�Y���j���[
	void UpdateDetailOptionCursor_ByInput();  // �ڍאݒ�I���i���ʁE��ʂ̖��邳�j

public:

	bool _showOption{};
	bool _isSelectEffectColor{};

private:

	int  _screenBrightnessIndex = 2;

	int _menuIndex = 0;              // �ŏ��̃I�v�V�����i�ĊJ�A�ڍאݒ�A��蒼���A�I���j
	int _detailOptionIndex{};        // �ڍאݒ�i���ʁE��ʂ̖��邳�j

	int _volumeIndicator_x1 = 180;   // ���ʂ������~�̍��W  ���W��0����300�܂�
	int _volumeSize = 50;            // ���ʂ̒l  0����100�Őݒ�
	int _volumeNumberColor = -1;     // ����(����)�̐F

	bool _isAdjustingVolume{};
};