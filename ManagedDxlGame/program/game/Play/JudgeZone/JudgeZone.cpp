#include "JudgeZone.h"
#include "../Score_Combo/ScoreCombo.h"
#include "../../Main.h"
#include "../Note/Normal/NormalNote.h"
#include "../Note/Long/LongNote.h"
#include "../ScenePlaySong.h"


void JudgeZone::InitJudgeZone() {


	for (column = 0; column < JUDGE_NUM; column++) {

		// x����20����J�n
		// �����͏��600�A����650�ŌŒ�
		switch (column)
		{
		case 0:// ���[��0
			judgeZone[column].x1 = judgeZoneX_left_1;
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_left_1 + judgeZoneX_right_2 / JUDGE_NUM;
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 1: // ���[��1
			judgeZone[column].x1 = judgeZoneX_left_1 + judgeZoneX_right_2 / JUDGE_NUM;
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = (judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2) - 45);
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 2: // ���[��2
			judgeZone[column].x1 = (judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2) - 45);
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2.5f + 65);
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 3: // ���[��3
			judgeZone[column].x1 = judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2.5f + 65);
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_right_1;
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		}
		judgeZone[column].active = true;
	}
}



void JudgeZone::RenderMap() {

	// �����`��
	DrawLineAA(judgeZoneX_left_1, judgeZoneY_top_1, judgeZoneX_right_1, judgeZoneY_top_1, -1, 2.0f); // ���
	DrawLineAA(judgeZoneX_left_2, judgeZoneY_top_2, judgeZoneX_right_2, judgeZoneY_top_2, -1, 2.0f); // ����

	// �΂ߐ�5�{�`��
	for (int i = 0; i < JUDGE_NUM + 1; i++) {

		float space = 50.0f;
		float x1;  //�n�_X
		float x2;  // �I�_X

		switch (i)
		{
		case 1:
			x1 = base_x1 + 2 * space;
			x2 = EACHAREA_WIDTH;
			break;
		case 2:
			x1 = base_x1 + 3 * space;
			x2 = EACHAREA_WIDTH * 2;
			break;
		case 3:
			x1 = base_x1 + 4 * space;
			x2 = EACHAREA_WIDTH * 3;
			break;
		case 4:
			x1 = base_x1 + 5 * space;
			x2 = EACHAREA_WIDTH * 4.2f;
			break;
		default:
			x1 = base_x1 + space;
			x2 = EACHAREA_WIDTH * -0.2f;
			break;
		}
		// �΂ߐ��`��
		DrawLineAA(x1, base_y1, x2, base_y2, -1, 2.0f);
	}
}



void JudgeZone::RenderJudgeZones() {

	for (column = 0; column < JUDGE_NUM; column++) {

		switch (column)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, judgeZone[column].alpha);

			DrawRoundRectAA(
				judgeZone[column].x1,
				judgeZone[column].y1,
				judgeZone[column].x2,
				judgeZone[column].y2,
				10.f, 0.1f, 4,
				judgeZone[column].color, true, 1.5f);
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}



// �P�񂲂Ƃ̔��茋�ʂ��������\��
void JudgeZone::RenderJudgeScore_OneMoment(JUDGE_TIMING j) {

	// �X�R�A�Ή��\
	const char* scoreTable[32] = { "1000","750","500","200","0" };
	char score[16];
	char grade[10];

	switch (j)
	{
	case JUDGE_TIMING::PERFECT:
		strcpy_s(grade, "PERFECT");
		strcpy_s(score, scoreTable[0]);
		break;
	case JUDGE_TIMING::GREAT:
		strcpy_s(grade, "GREAT");
		strcpy_s(score, scoreTable[1]);
		break;
	case JUDGE_TIMING::GOOD:
		strcpy_s(grade, "GOOD");
		strcpy_s(score, scoreTable[2]);
		break;
	case JUDGE_TIMING::POOR:
		strcpy_s(grade, "POOR");
		strcpy_s(score, scoreTable[3]);
		break;
	case JUDGE_TIMING::MISS:
		strcpy_s(grade, "MISS");
		strcpy_s(score, scoreTable[4]);
		break;
	}

	SetFontSize(25);
	// ���茋��
	DrawStringEx(judgeZone[column].x1 + 100, judgeZone[column].y1 - 80, 0xFF00CED1, grade);
	// �l���X�R�A
	DrawStringEx(judgeZone[column].x1 + 100, judgeZone[column].y1 - 50, 0xFF00CED1, score);
	SetFontSize(DEFAULT_FONT_SIZE);
}



void JudgeZone::JudgeGrade(std::vector<NormalNote>& normal_note, const int& row, const double& _timer, std::vector<double>& should_input_time) {

	double timeDiff = abs(should_input_time[row] - _timer);

	if (timeDiff > 1.8) return;

	normal_note[row].active = false;


	if (timeDiff < 0.2) {

		_scoreComboRef->myScore += 1000;
		_scoreComboRef->myCombo++;
		_scoreComboRef->perfect_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		_scoreComboRef->y1_combo -= 5;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.4) {

		_scoreComboRef->myScore += 750;
		_scoreComboRef->myCombo++;
		_scoreComboRef->great_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GREAT);
		return;
	}
	else if (timeDiff < 0.6) {

		_scoreComboRef->myScore += 500;
		_scoreComboRef->myCombo++;
		_scoreComboRef->good_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GOOD);
		return;
	}
	else if (timeDiff < 0.8) {

		_scoreComboRef->myScore += 200;
		_scoreComboRef->myCombo = 0;
		_scoreComboRef->poor_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::POOR);
		return;
	}
	else if (timeDiff < 1.0) {
		_scoreComboRef->myCombo = 0;
		_scoreComboRef->miss_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::MISS);
		return;
	}
}



void JudgeZone::JudgeGrade(std::vector<LongNote>& long_note, const int& row, const double& timer, std::vector<double>& should_input_time) {

	double timeDiff = abs(should_input_time[row] - timer);

	if (timeDiff > 1.8) return;


	long_note[row].active = false;

	if (timeDiff < 0.6) {

		_scoreComboRef->myScore += 1000;
		_scoreComboRef->myCombo++;
		_scoreComboRef->perfect_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		_scoreComboRef->y1_combo -= 5;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.8) {

		_scoreComboRef->myScore += 750;
		_scoreComboRef->myCombo++;
		_scoreComboRef->great_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GREAT);
		return;
	}
	else if (timeDiff < 1.0) {

		_scoreComboRef->myScore += 500;
		_scoreComboRef->myCombo++;
		_scoreComboRef->good_count++;
		_scoreComboRef->comboAnimationFrames = _scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GOOD);
		return;
	}
	else if (timeDiff < 1.2) {

		_scoreComboRef->myScore += 200;
		_scoreComboRef->myCombo = 0;
		_scoreComboRef->poor_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::POOR);
		return;
	}
	
}



int JudgeZone::UpdateKeyFunc() {

	char tmpKey[256]; // �L�[���͏�Ԃ��i�[
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0) // �L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		{
			Key[i]++;       // ���Z
		}
		else
		{
			Key[i] = 0;
		}
	}
	return 0;
}




void JudgeZone::JudgeNoteHit_ByInputKey(std::vector<NormalNote>& normal_note, const int& row, const double& timer, std::vector<double>& should_input_time) {

	UpdateKeyFunc();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (column = 0; column < JUDGE_NUM; column++) {

			if (Key[KEYS[column]] == true) {

				// �m�[�}���m�[�c�̓����蔻��
				if(normal_note[row].active)
				JudgeGrade(normal_note, row, timer, should_input_time);

				// �L�[����͂�����F���ς��
				judgeZone[column].alpha = BRIGHTNESS_ON;
			}
			else if (Key[KEYS[column]] == 0) {

				// ��������F��߂�
				judgeZone[column].alpha = BRIGHTNESS_OFF;
			}
		}
	}
}



void JudgeZone::JudgeNoteHit_ByInputKey(std::vector<LongNote>& long_note, const int& row, const double& _timer, std::vector<double>& should_input_time) {

	UpdateKeyFunc();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (column = 0; column < JUDGE_NUM; column++) {

			if (Key[KEYS[column]] == true) {

				// �����O�m�[�c�̓����蔻��
				if (long_note[row].active)
				JudgeGrade(long_note, row, _timer, should_input_time);

				// �L�[����͂�����F���ς��
				judgeZone[column].alpha = BRIGHTNESS_ON;
			}
			else if (Key[KEYS[column]] == 0) {

				// ��������F��߂�
				judgeZone[column].alpha = BRIGHTNESS_OFF;
			}
		}
	}
}