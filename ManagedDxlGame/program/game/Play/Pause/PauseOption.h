#pragma once
#include <string>

constexpr static int MENU_INDEX = 4;


class PauseOption
{
public:

	// 入力-----------------------------------------------------------------------------------------
	void GoNextOrGoBack();
	void AdjustVolumeByInput();
	void PickMenuItemByInput();

	// 色-------------------------------------------------------------------------------------------
	void ChangePauseOptionColor();
	void ChangeSelectEffectColorAndBrightness(int& eff1_color, int& eff2_color, int& eff3_color);

	// 描画------------------------------------------------------------------------------------------
	void RenderLowMediumHighWord(int& eff1_color, int& eff2_color, int& eff3_color);
	void RenderAdjustVolumeObject();
	void RenderMenuItems_AndDescriptions();

	// 更新------------------------------------------------------------------------------------------
	void UpdatePauseMenuCursor_ByInput();
	void UpdatePauseOptionCursor_ByInput();
	void UpdateSelectEffectCursor_ByInput();

public:

	bool showOption{};    
	bool selectEffectColor{};
	int effectIndex = 2;

private:

	int menuIndex = 0;      // メニュー
	int optionIndex{};      // オプション

	int volumeIndex = 180;  // 音量を示す円の座標  座標は0から300まで
	int volumeNum = 50;     // 音量の値 勿論 0から100で
	int volNum_color = -1;  // 音量(数字)の色

	bool isAdjustVolume{};
	std::string volume_str{};
};