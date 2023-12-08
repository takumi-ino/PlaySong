#pragma once
#include "../../utility/DxLib_Engine.h"

#define JUDGE_NUM 4 // ����G���A

class ScoreCombo;
class NormalNote;
class LongNote;


static const int KEYS[JUDGE_NUM] =
{
	KEY_INPUT_D,
	KEY_INPUT_F,
	KEY_INPUT_J,
	KEY_INPUT_K
};


class JudgeZone {

public:

	JudgeZone(){}

	void RenderMap(); 	     // �S�̓I�ȕ`��

	void RenderJudgeZones(); // ����G���A�`��

	// �m�[�}���m�[�c�̓����蔻�菈��
	void JudgeNoteHit_ByInputKey(
		std::vector<NormalNote>& normal_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	// �����O�m�[�c�̓����蔻�菈��
	void JudgeNoteHit_ByInputKey(
		std::vector<LongNote>& long_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	void InitJudgeZone();

	void SetScoreComboRef(ScoreCombo* scoreComboRef) { _scoreComboRef = scoreComboRef; };

private:

	enum class JUDGE_TIMING
	{
		PERFECT,
		GREAT,
		GOOD,
		POOR,
		MISS
	};

	void JudgeGrade(std::vector<NormalNote>& normal_note, const int& row, const double& timer, std::vector<double>& should_input_time);
	void JudgeGrade(std::vector<LongNote>& long_note, const int& row, const double& timer, std::vector<double>& should_input_time);

	void RenderJudgeScore_OneMoment(JUDGE_TIMING);
	int  UpdateKeyFunc();


private:

	ScoreCombo* _scoreComboRef;

private:


	int perfect_time_size[4] = { 0 };     // ������������0�Ɠ����Ă���0�Ƃ���ʂ���
	int Key[256];                         // �L�[���͗p

	double perfect_times[136][4] = { 0 }; // ���胉�C���Ƀm�[�c�����B���鎞��
	const double judgeableDistance = 1000.0;
	double actualDistance = 0.0;

	// �����i����G���A�S�͈̔́j
	// ���	
	const int MARGIN_LEFT_AND_RIGHT = 50; // ����G���A�ƃE�B���h�E�[�Ƃ̋���
	const int AREA_HEIGHT_TOPPOS = 600;
	const int AREA_RANGE = 55;

	float judgeZoneX_left_1 = MARGIN_LEFT_AND_RIGHT;  //  �n�_X
	float judgeZoneY_top_1 = AREA_HEIGHT_TOPPOS;    //  �n�_Y
	float judgeZoneX_right_1 = DXE_WINDOW_WIDTH - MARGIN_LEFT_AND_RIGHT;  //  �I�_X
	float judgeZoneY_bottom_1 = 5.f;  // �I�_Y
	// ����
	float judgeZoneX_left_2 = 0.f;  //  �n�_X
	float judgeZoneY_top_2 = AREA_HEIGHT_TOPPOS + AREA_RANGE;  //  �n�_Y
	float judgeZoneX_right_2 = DXE_WINDOW_WIDTH;  //  �I�_X
	float judgeZoneY_bottom_2 = 5.f;  // �I�_Y

	//------------------------------------------------------------

	// �c���i�΂߁j���T�{ ����G���A���S������
	const int VERTICAL_STARTPOS = 100;             //�@�n�_Y
	const int VERTICAL_ENDPOS = DXE_WINDOW_HEIGHT; //�@�I�_Y

	float base_x1 = 490;                // �΂ߐ��̎n�_X
	float base_y1 = VERTICAL_STARTPOS;  // �΂ߐ��̎n�_Y
	float base_y2 = VERTICAL_ENDPOS;	// �΂ߐ��̏I�_Y

	//------------------------------------------------------------

	// �e����G���A�̉���
	const int EACHAREA_WIDTH = DXE_WINDOW_WIDTH / JUDGE_NUM;

	// ����G���A1�`4�@�e����ݒ�
	float x1;  // x������W
	float y1;  // ��������W
	float x2;  // ���E�����W
	float y2;  // ���E�����W
	float size;
	int color;
	int column;

	bool active = true;

	// ����G���A�̖��x����
	int alpha;
	const int BRIGHTNESS_ON = 170;
	const int BRIGHTNESS_OFF = 70;
};