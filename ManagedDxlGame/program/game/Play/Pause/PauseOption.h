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

	bool isRetryGame ;    // 音量を示す円の座標  座標は0から300まで
	bool showOption;      // 音量の値 勿論 0から100で
	bool selectEffColor;  // 音量(数字)の色
	int effectIndex = 2;  // 解像度のレベル

private:

	int menuIndex = 0;   // メニュー
	int optionIndex;     // オプション
	const int PAUSEOPTION_MAXITEM_NUM = 2;  // VOLUMEとSCREEN_EFFECT
	const int EFFECTOPTION_MAXITEM_NUM = 3; // low, medium, high

	const int LEFTSIDE = 50;
	const int UPSIDE = 100;

	int volumeIndex = 180; // 音量を示す円の座標  座標は0から300まで
	int volumeNum = 50;    // 音量の値 勿論 0から100で
	int volNum_color = -1; // 音量(数字)の色

	bool isAdjustVolume;
	std::string volume_str;
};