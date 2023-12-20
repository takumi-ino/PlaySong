#pragma once
#include "../../utility/DxLib_Engine.h"


class ScoreCombo {

public:

	ScoreCombo(){}

	void SetScoreComboRef(ScoreCombo* scRef) { _scoreCombo_ref = scRef; };

	void RenderCombo();

	void RenderScore();

public:

	int myScore;
	int myCombo;

	int  perfect_count;
	int	great_count;
	int	good_count;
	int	poor_count;
	int	miss_count;

	int comboAnimationFrames = 0;
	int comboAnimationDuration = 1; // アニメーションの持続フレーム数

	const int x1_combo = 590;
	int y1_combo = 450;// コンボ(数値)の座標

private:

	ScoreCombo* _scoreCombo_ref;

	int highScore;
	int highCombo;         // ハイスコア

	std::string score_str;
	std::string combo_str;
};