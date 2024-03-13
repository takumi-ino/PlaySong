#pragma once

constexpr static int MENU_INDEX = 4;


class PauseOption
{
public:

	// 入力-----------------------------------------------------------------------------------------
	void GoNextOrGoBack();                // 選択
	void PickMenuItemByInput();           // 決定
	void AdjustVolumeByInput();           // 音量調整
	void AdjustScreenBrightnessByInput(); // 画面の明るさ調整

	// 詳細設定（音量・画面の明るさ）---------------------------------------------------------------
	void ChangePauseOptionColor();              // 色変更
	void ChangeSelectEffectColorAndBrightness(  // 画面の明るさ変更
		int& eff1_color, int& eff2_color, int& eff3_color
	);

	// 描画------------------------------------------------------------------------------------------
	void RenderBrightnessLevels(              // 画面の明るさ(Low, Medium, High) 
		int& eff1_color,
		int& eff2_color, 
		int& eff3_color
	);
	void RenderAdjustVolumeObject();          // 音量調整のための図形
	void RenderMenuItems_AndDescriptions();   // 各種ポーズメニューとその説明文

	// 更新(入力によって動くカーソル）---------------------------------------------------------------
	void UpdatePauseMenuCursor_ByInput();     // ポーズメニュー
	void UpdateDetailOptionCursor_ByInput();  // 詳細設定選択（音量・画面の明るさ）

public:

	bool _showOption{};
	bool _isSelectEffectColor{};

private:

	int  _screenBrightnessIndex = 2;

	int _menuIndex = 0;              // 最初のオプション（再開、詳細設定、やり直し、終了）
	int _detailOptionIndex{};        // 詳細設定（音量・画面の明るさ）

	int _volumeIndicator_x1 = 180;   // 音量を示す円の座標  座標は0から300まで
	int _volumeSize = 50;            // 音量の値  0から100で設定
	int _volumeNumberColor = -1;     // 音量(数字)の色

	bool _isAdjustingVolume{};
};