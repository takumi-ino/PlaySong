#include "../../utility/DxLib_Engine.h"
#include "ScoreCombo.h"


void ScoreCombo::RenderCombo() {

	_scoreCombo_ref->_scoreString = std::to_string(_scoreCombo_ref->_myScore);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	SetFontSize(111);

	int comboYPos = _scoreCombo_ref->_combo_y1;

	if (_scoreCombo_ref->_comboAnimationFrames > 0) {

		comboYPos -= 5;
		_scoreCombo_ref->_comboAnimationFrames--; // アニメーションのフレーム数を減らす
	}
	// コンボ表示
	DrawStringEx(_scoreCombo_ref->x1_combo, comboYPos, GetColor(255, 190, 200), _scoreCombo_ref->_comboString.c_str());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void ScoreCombo::RenderScore() {

	_scoreCombo_ref->_comboString = std::to_string(_scoreCombo_ref->_myCombo);

	SetFontSize(35);
	// スコア表示
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 15, -1, _scoreCombo_ref->_scoreString.c_str());

	SetFontSize(35);
}