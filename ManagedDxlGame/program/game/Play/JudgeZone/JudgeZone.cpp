#include "../../utility/DxLib_Engine.h"
#include "JudgeZone.h"
#include "../Note/Long/LongNote.h"
#include "../Note/Normal/NormalNote.h"
#include "../Score_Combo/ScoreCombo.h"
#include "../ScenePlaySong.h"


namespace {

	// �����i����G���A�S�͈̔́j---------------------------------------------------------------------------------------------------------
	const int _MARGIN_LEFT_AND_RIGHT = 50; // ����G���A�ƃE�B���h�E�[�Ƃ̋���
	const int _AREA_HEIGHT_TOPPOS = 600;
	const int _AREA_RANGE = 55;

	// ���	------------------------------------------------------------
	const float _judgeZone_x1_ceilingLine = (float)_MARGIN_LEFT_AND_RIGHT;                     //  �n�_X
	const float _judgeZone_x2_ceilingLine = (float)DXE_WINDOW_WIDTH - _MARGIN_LEFT_AND_RIGHT;  //  �I�_X
	const float _judgeZone_y1_ceilingLine = (float)_AREA_HEIGHT_TOPPOS;                        //  �n�_Y
	const float _judgeZone_y2_ceilingLine = 5.f;                                               //  �I�_Y

	// ����------------------------------------------------------------
	const float _judgeZone_x1_bottomLine = 0.f;                                      //  �n�_X
	const float _judgeZone_x2_bottomLine = (float)DXE_WINDOW_WIDTH;                  //  �I�_X
	const float _judgeZone_y1_bottomLine = (float)_AREA_HEIGHT_TOPPOS + _AREA_RANGE; //  �n�_Y
	const float _judgeZone_y2_bottomLine = 5.f;                                      //  �I�_Y

	// �c���i�΂߁j���T�{ ����G���A���S������----------------------------------------------------------------------------------------------
	const float _diagonalLine_x1 = 490.f;                    // �΂ߐ��̎n�_X
	const float _diagonalLine_y1 = 100.f;                    // �΂ߐ��̎n�_Y
	const float _diagonalLine_y2 = (float)DXE_WINDOW_HEIGHT; // �΂ߐ��̏I�_Y

	// �e����G���A�̉���----------------------------------------
	const int EACHAREA_WIDTH = DXE_WINDOW_WIDTH / JUDGE_NUM;

	// ���x------------------------------------------------------------
	const int BRIGHTNESS_ON = 170;
	const int BRIGHTNESS_OFF = 70;
}


static const int KEYS[JUDGE_NUM] =
{
	KEY_INPUT_D,
	KEY_INPUT_F,
	KEY_INPUT_J,
	KEY_INPUT_K
};

//�@������----------------------------------------------------------------------------------------------------
JudgeZone::JudgeZone() {

	_scoreComboRef = new ScoreCombo();
}


void JudgeZone::InitJudgeZone() {

	for (_column = 0; _column < JUDGE_NUM; _column++) {

		// x����20����J�n
		// �����͏��600�A����650�ŌŒ�
		switch (_column)
		{
		case 0:// ���[��0
			judgeZone[_column]._x1 = _judgeZone_x1_ceilingLine;
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = _judgeZone_x1_ceilingLine + _judgeZone_x2_bottomLine / JUDGE_NUM;
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 1: // ���[��1
			judgeZone[_column]._x1 = _judgeZone_x1_ceilingLine + _judgeZone_x2_bottomLine / JUDGE_NUM;
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = (_judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2) - 45);
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 2: // ���[��2
			judgeZone[_column]._x1 = (_judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2) - 45);
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = _judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2.5f + 65);
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 3: // ���[��3
			judgeZone[_column]._x1 = _judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2.5f + 65);
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = _judgeZone_x2_ceilingLine;
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		}

		judgeZone[_column]._isActive = true;
	}
}


//�@���菈��----------------------------------------------------------------------------------------------------
void JudgeZone::JudgeGrade(
	std::vector<NormalNote>& normal_note, 
	const int& row, 
	const double& timer, 
	std::vector<double>& should_input_time)
{

	// ���͂��ׂ��^�C�~���O�Ǝ��ۂ̓��̓^�C�~���O�Ƃ̍����擾
	double timeDiff = abs(should_input_time[row] - timer);

	if (timeDiff > 1.8) return;

		normal_note[row]._isActive = false;

	if (timeDiff < 0.2) {

		_scoreComboRef->_myScore += 1000;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_perfectCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		_scoreComboRef->_combo_y1 -= 5;
		RenderJudgeScore_OneMoment(TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.4) {

		_scoreComboRef->_myScore += 750;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_greatCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		RenderJudgeScore_OneMoment(TIMING::GREAT);
		return;
	}
	else if (timeDiff < 0.6) {

		_scoreComboRef->_myScore += 500;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_goodCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		RenderJudgeScore_OneMoment(TIMING::GOOD);
		return;
	}
	else if (timeDiff < 0.8) {

		_scoreComboRef->_myScore += 200;
		_scoreComboRef->_myCombo = 0;
		_scoreComboRef->_poorCount++;
		RenderJudgeScore_OneMoment(TIMING::POOR);
		return;
	}
	else if (timeDiff < 1.0) {

		_scoreComboRef->_myCombo = 0;
		_scoreComboRef->_missCount++;
		RenderJudgeScore_OneMoment(TIMING::MISS);
		return;
	}
}


void JudgeZone::JudgeGrade(
	std::vector<LongNote>& long_note,
	const int& row, 
	const double& timer,
	std::vector<double>& should_input_time)
{

	// ���͂��ׂ��^�C�~���O�Ǝ��ۂ̓��̓^�C�~���O�Ƃ̍����擾
	double timeDiff = abs(should_input_time[row] - timer);

	if (timeDiff > 1.8) return;

	long_note[row]._isActive = false;

	if (timeDiff < 0.6) {

		_scoreComboRef->_myScore += 1000;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_perfectCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		_scoreComboRef->_combo_y1 -= 5;
		RenderJudgeScore_OneMoment(TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.8) {

		_scoreComboRef->_myScore += 750;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_greatCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		RenderJudgeScore_OneMoment(TIMING::GREAT);
		return;
	}
	else if (timeDiff < 1.0) {

		_scoreComboRef->_myScore += 500;
		_scoreComboRef->_myCombo++;
		_scoreComboRef->_goodCount++;
		_scoreComboRef->_comboAnimationFrames = _scoreComboRef->_comboAnimationDuration;
		RenderJudgeScore_OneMoment(TIMING::GOOD);
		return;
	}
	else if (timeDiff < 1.2) {

		_scoreComboRef->_myScore += 200;
		_scoreComboRef->_myCombo = 0;
		_scoreComboRef->_poorCount++;
		RenderJudgeScore_OneMoment(TIMING::POOR);
		return;
	}
}


void JudgeZone::JudgeNoteHit_ByInputKey(
	std::vector<NormalNote>& normal_note,
	const int& row,
	const double& timer,
	std::vector<double>& should_input_time)
{

	UpdateInputKey();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (_column = 0; _column < JUDGE_NUM; _column++) {

			if (_receiveKeyInputBuf[KEYS[_column]] == 1) {

				// �m�[�}���m�[�c�̓����蔻��
				if (normal_note[row]._isActive) {

					JudgeGrade(normal_note, row, timer, should_input_time);
				}

				// �L�[����͂�����F���ς��
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (_receiveKeyInputBuf[KEYS[_column]] == 0) {

				// ��������F��߂�
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_OFF;
			}
		}
	}
}


void JudgeZone::JudgeNoteHit_ByInputKey(
	std::vector<LongNote>& long_note,
	const int& row,
	const double& timer,
	std::vector<double>& should_input_time) 
{

	UpdateInputKey();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (_column = 0; _column < JUDGE_NUM; _column++) {

			if (_receiveKeyInputBuf[KEYS[_column]]) {

				// �����O�m�[�c�̓����蔻��
				if (long_note[row]._isActive) {

					JudgeGrade(long_note, row, timer, should_input_time);
				}

				// �L�[����͂�����F���ς��
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (_receiveKeyInputBuf[KEYS[_column]] == 0) {

				// ��������F��߂�
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_OFF;
			}
		}
	}
}


//�@���͏���--------------------------------------------------------------------------------
int JudgeZone::UpdateInputKey() {

	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0) // �L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		{
			_receiveKeyInputBuf[i]++;
		}
		else
		{
			_receiveKeyInputBuf[i] = 0;
		}
	}
	return 0;
}


// �`��----------------------------------------------------------------------------------------------------
void JudgeZone::RenderJudgeZones() {

	for (_column = 0; _column < JUDGE_NUM; _column++) {

		switch (_column)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, judgeZone[_column].brightnessAlpha);

			DrawRoundRectAA(
				judgeZone[_column]._x1,
				judgeZone[_column]._y1,
				judgeZone[_column]._x2,
				judgeZone[_column]._y2,
				10.f, 0.1f, 4,
				judgeZone[_column]._color, true, 1.5f
			);
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}



// �P�񂲂Ƃ̔��茋�ʂ��������\��
void JudgeZone::RenderJudgeScore_OneMoment(TIMING j) {

	// �X�R�A�Ή��\
	const char* scoreTable[32] = { "1000","750","500","200","0" };
	char score[16];
	char grade[10];

	switch (j)
	{
	case TIMING::PERFECT:
		strcpy_s(grade, "PERFECT");
		strcpy_s(score, scoreTable[0]);
		break;
	case TIMING::GREAT:
		strcpy_s(grade, "GREAT");
		strcpy_s(score, scoreTable[1]);
		break;
	case TIMING::GOOD:
		strcpy_s(grade, "GOOD");
		strcpy_s(score, scoreTable[2]);
		break;
	case TIMING::POOR:
		strcpy_s(grade, "POOR");
		strcpy_s(score, scoreTable[3]);
		break;
	case TIMING::MISS:
		strcpy_s(grade, "MISS");
		strcpy_s(score, scoreTable[4]);
		break;
	}

	SetFontSize(25);
	// ���茋��
	DrawStringEx(judgeZone[_column]._x1 + 100, judgeZone[_column]._y1 - 80, 0xFF00CED1, grade);
	// �l���X�R�A
	DrawStringEx(judgeZone[_column]._x1 + 100, judgeZone[_column]._y1 - 50, 0xFF00CED1, score);
	SetFontSize(DEFAULT_FONT_SIZE);
}


void JudgeZone::RenderMap() {

	// �����`��
	DrawLineAA(_judgeZone_x1_ceilingLine, _judgeZone_y1_ceilingLine, _judgeZone_x2_ceilingLine, _judgeZone_y1_ceilingLine, -1, 2.0f); // ���
	DrawLineAA(_judgeZone_x1_bottomLine, _judgeZone_y1_bottomLine, _judgeZone_x2_bottomLine, _judgeZone_y1_bottomLine, -1, 2.0f); // ����

	float space = 50.0f;
	float _x1;  // �n�_X
	float _x2;  // �I�_X

	// �΂ߐ�5�{�`��
	for (int i = 0; i < JUDGE_NUM + 1; i++) {

		switch (i)
		{
		case 1:
			_x1 = _diagonalLine_x1 + 2 * space;
			_x2 = EACHAREA_WIDTH;
			break;
		case 2:
			_x1 = _diagonalLine_x1 + 3 * space;
			_x2 = EACHAREA_WIDTH * 2;
			break;
		case 3:
			_x1 = _diagonalLine_x1 + 4 * space;
			_x2 = EACHAREA_WIDTH * 3;
			break;
		case 4:
			_x1 = _diagonalLine_x1 + 5 * space;
			_x2 = EACHAREA_WIDTH * 4.2f;
			break;
		default:
			_x1 = _diagonalLine_x1 + space;
			_x2 = EACHAREA_WIDTH * -0.2f;
			break;
		}

		// �΂ߐ��`��
		DrawLineAA(_x1, _diagonalLine_y1, _x2, _diagonalLine_y2, -1, 2.0f);
	}
}
