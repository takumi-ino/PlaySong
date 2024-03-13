#pragma once

constexpr static int JUDGE_NUM = 4; // ����G���A

class ScoreCombo;
class NormalNote;
class LongNote;


class JudgeZone
{
private:

	enum class TIMING
	{
		PERFECT,
		GREAT,
		GOOD,
		POOR,
		MISS
	};

public:

	JudgeZone();

	// ������--------------------------------------------------------------------------------
	void InitJudgeZone();
	void SetScoreComboRef(ScoreCombo* _scoreComboRef) { _scoreComboRef = _scoreComboRef; };

	// �����蔻��--------------------------------------------------------------------------------
	void JudgeNoteHit_ByInputKey(	         // �m�[�}���m�[�c
		std::vector<NormalNote>& normal_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	void JudgeNoteHit_ByInputKey(	         // �����O�m�[�c
		std::vector<LongNote>& long_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	// �`��--------------------------------------------------------------------------------
	void RenderMap(); 	     // �S��
	void RenderJudgeZones(); // ����G���A

private:

	// ���菈��----------------------------------------------------------------------------
	void JudgeGrade(
		std::vector<NormalNote>& normal_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);
	void JudgeGrade(std::vector<LongNote>& long_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	// ------------------------------------------------------------------------------------
	void RenderJudgeScore_OneMoment(TIMING);  // ���菈��1�񂲂ƂɈ�u Grade�i Perfect��Great�Ȃ� �j�Ɗl���X�R�A��\��
	int  UpdateInputKey();                    // �L�[���͎�t

private:

	ScoreCombo* _scoreComboRef = nullptr;

private:

	int   _receiveKeyInputBuf[256]{}; // �L�[���͏��擾
	int   brightnessAlpha{};	     // ����G���A�̖��x����

	bool  _isActive = true;

	// ����G���A1�`4�@�e����----------------------------------
	int   _color{};
	int   _column{};

	float _x1{};    // x������W
	float _y1{};    // ��������W
	float _x2{};    // ���E�����W
	float _y2{};    // ���E�����W
};