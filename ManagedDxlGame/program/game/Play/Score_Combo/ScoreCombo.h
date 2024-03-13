#pragma once


class ScoreCombo 
{
public:

	void SetScoreComboRef(ScoreCombo* scRef) { _scoreCombo_ref = scRef; };

	void RenderCombo();

	void RenderScore();

public:

	int _myScore{};
	int _myCombo{};

	int _perfectCount{};
	int	_greatCount{};
	int	_goodCount{};
	int	_poorCount{};
	int	_missCount{};

	int _comboAnimationFrames = 0;
	int _comboAnimationDuration = 1; // �A�j���[�V�����̎����t���[����

	const int x1_combo = 590;
	int _combo_y1 = 450;       // �R���{(���l)�̍��W�B��u���˂鉉�o�̂��� y �͔� const

private:

	ScoreCombo* _scoreCombo_ref = nullptr;

private:

	std::string _scoreString{};
	std::string _comboString{};
};