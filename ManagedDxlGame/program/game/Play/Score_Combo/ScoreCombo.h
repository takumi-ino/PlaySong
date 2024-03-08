#pragma once
#include "../../utility/DxLib_Engine.h"


class ScoreCombo {

public:

	void SetScoreComboRef(ScoreCombo* scRef) { _scoreCombo_ref = scRef; };

	void RenderCombo();

	void RenderScore();

public:

	int myScore{};
	int myCombo{};

	int perfect_count{};
	int	great_count{};
	int	good_count{};
	int	poor_count{};
	int	miss_count{};

	int comboAnimationFrames = 0;
	int comboAnimationDuration = 1; // �A�j���[�V�����̎����t���[����

	int y1_combo = 450;       // �R���{(���l)�̍��W�B��u���˂鉉�o�̂��� y �͔� const
	const int x1_combo = 590;

private:

	ScoreCombo* _scoreCombo_ref = nullptr;

private:

	int highScore{};
	int highCombo{};

	std::string score_str{};
	std::string combo_str{};
};