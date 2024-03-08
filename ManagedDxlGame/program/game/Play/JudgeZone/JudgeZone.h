#pragma once
#include "../../utility/DxLib_Engine.h"

constexpr static int JUDGE_NUM = 4; // ����G���A

class ScoreCombo;
class NormalNote;
class LongNote;


class JudgeZone
{
private:

	enum class JUDGE_TIMING
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
	void SetScoreComboRef(ScoreCombo* scoreComboRef) { scoreComboRef = scoreComboRef; };

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
	void RenderJudgeScore_OneMoment(JUDGE_TIMING);  // ���菈��1�񂲂ƂɈ�u Grade�i Perfect��Great�Ȃ� �j�Ɗl���X�R�A��\��
	int  UpdateInputKey();                          // �L�[���͎�t

private:

	ScoreCombo* scoreComboRef = nullptr;

private:

	int ReceiveKeyInput[256]{}; // �L�[���͏��擾
	int brightnessAlpha{};	    // ����G���A�̖��x����

	bool isActive = true;

	// �����i����G���A�S�͈̔́j-------------------------------------------------------------------

	// ���	------------------------------------------------------------
	const int MARGIN_LEFT_AND_RIGHT = 50; // ����G���A�ƃE�B���h�E�[�Ƃ̋���
	const int AREA_HEIGHT_TOPPOS = 600;
	const int AREA_RANGE = 55;

	float judgeZoneX_left_1 = (float)MARGIN_LEFT_AND_RIGHT;                      //  �n�_X
	float judgeZoneY_top_1 = (float)AREA_HEIGHT_TOPPOS;                          //  �n�_Y
	float judgeZoneX_right_1 = (float)DXE_WINDOW_WIDTH - MARGIN_LEFT_AND_RIGHT;  //  �I�_X
	float judgeZoneY_bottom_1 = 5.f;                                             //  �I�_Y

	// ����------------------------------------------------------------
	float judgeZoneX_left_2 = 0.f;                                        //  �n�_X
	float judgeZoneY_top_2 = (float)AREA_HEIGHT_TOPPOS + AREA_RANGE;      //  �n�_Y
	float judgeZoneX_right_2 = (float)DXE_WINDOW_WIDTH;                   //  �I�_X
	float judgeZoneY_bottom_2 = 5.f;                                      //  �I�_Y

	// �c���i�΂߁j���T�{ ����G���A���S������--------------------------------------------------------
	const int VERTICAL_STARTPOS = 100;              //�@�n�_Y
	const int VERTICAL_ENDPOS = DXE_WINDOW_HEIGHT;  //�@�I�_Y
	
	float base_x1 = 490.f;                          // �΂ߐ��̎n�_X
	float base_y1 = (float)VERTICAL_STARTPOS;       // �΂ߐ��̎n�_Y
	float base_y2 = (float)VERTICAL_ENDPOS;	        // �΂ߐ��̏I�_Y

	// ����G���A1�`4�@�e����ݒ�-------------------------------------------------------------------
	float x1{};    // x������W
	float y1{};    // ��������W
	float x2{};    // ���E�����W
	float y2{};    // ���E�����W
	float size{};
	int color{};
	int column{};
};