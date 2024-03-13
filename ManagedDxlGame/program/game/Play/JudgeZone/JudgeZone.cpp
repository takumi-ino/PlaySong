#include "../../utility/DxLib_Engine.h"
#include "JudgeZone.h"
#include "../Note/Long/LongNote.h"
#include "../Note/Normal/NormalNote.h"
#include "../Score_Combo/ScoreCombo.h"
#include "../ScenePlaySong.h"


namespace {

	// 横線（判定エリア全体範囲）---------------------------------------------------------------------------------------------------------
	const int _MARGIN_LEFT_AND_RIGHT = 50; // 判定エリアとウィンドウ端との距離
	const int _AREA_HEIGHT_TOPPOS = 600;
	const int _AREA_RANGE = 55;

	// 上辺	------------------------------------------------------------
	const float _judgeZone_x1_ceilingLine = (float)_MARGIN_LEFT_AND_RIGHT;                     //  始点X
	const float _judgeZone_x2_ceilingLine = (float)DXE_WINDOW_WIDTH - _MARGIN_LEFT_AND_RIGHT;  //  終点X
	const float _judgeZone_y1_ceilingLine = (float)_AREA_HEIGHT_TOPPOS;                        //  始点Y
	const float _judgeZone_y2_ceilingLine = 5.f;                                               //  終点Y

	// 下辺------------------------------------------------------------
	const float _judgeZone_x1_bottomLine = 0.f;                                      //  始点X
	const float _judgeZone_x2_bottomLine = (float)DXE_WINDOW_WIDTH;                  //  終点X
	const float _judgeZone_y1_bottomLine = (float)_AREA_HEIGHT_TOPPOS + _AREA_RANGE; //  始点Y
	const float _judgeZone_y2_bottomLine = 5.f;                                      //  終点Y

	// 縦線（斜め）※５本 判定エリアを４等分に----------------------------------------------------------------------------------------------
	const float _diagonalLine_x1 = 490.f;                    // 斜め線の始点X
	const float _diagonalLine_y1 = 100.f;                    // 斜め線の始点Y
	const float _diagonalLine_y2 = (float)DXE_WINDOW_HEIGHT; // 斜め線の終点Y

	// 各判定エリアの横幅----------------------------------------
	const int EACHAREA_WIDTH = DXE_WINDOW_WIDTH / JUDGE_NUM;

	// 明度------------------------------------------------------------
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

//　初期化----------------------------------------------------------------------------------------------------
JudgeZone::JudgeZone() {

	_scoreComboRef = new ScoreCombo();
}


void JudgeZone::InitJudgeZone() {

	for (_column = 0; _column < JUDGE_NUM; _column++) {

		// x軸は20から開始
		// ｙ軸は上辺600、下辺650で固定
		switch (_column)
		{
		case 0:// レーン0
			judgeZone[_column]._x1 = _judgeZone_x1_ceilingLine;
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = _judgeZone_x1_ceilingLine + _judgeZone_x2_bottomLine / JUDGE_NUM;
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 1: // レーン1
			judgeZone[_column]._x1 = _judgeZone_x1_ceilingLine + _judgeZone_x2_bottomLine / JUDGE_NUM;
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = (_judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2) - 45);
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 2: // レーン2
			judgeZone[_column]._x1 = (_judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2) - 45);
			judgeZone[_column]._y1 = _judgeZone_y1_ceilingLine;
			judgeZone[_column]._x2 = _judgeZone_x1_ceilingLine + (_judgeZone_x2_bottomLine / JUDGE_NUM * 2.5f + 65);
			judgeZone[_column]._y2 = _judgeZone_y1_bottomLine;
			judgeZone[_column]._color = GetColor(0, 200, 200);
			break;
		case 3: // レーン3
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


//　判定処理----------------------------------------------------------------------------------------------------
void JudgeZone::JudgeGrade(
	std::vector<NormalNote>& normal_note, 
	const int& row, 
	const double& timer, 
	std::vector<double>& should_input_time)
{

	// 入力すべきタイミングと実際の入力タイミングとの差を取得
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

	// 入力すべきタイミングと実際の入力タイミングとの差を取得
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

				// ノーマルノーツの当たり判定
				if (normal_note[row]._isActive) {

					JudgeGrade(normal_note, row, timer, should_input_time);
				}

				// キーを入力したら色が変わる
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (_receiveKeyInputBuf[KEYS[_column]] == 0) {

				// 放したら色を戻す
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

				// ロングノーツの当たり判定
				if (long_note[row]._isActive) {

					JudgeGrade(long_note, row, timer, should_input_time);
				}

				// キーを入力したら色が変わる
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (_receiveKeyInputBuf[KEYS[_column]] == 0) {

				// 放したら色を戻す
				judgeZone[_column].brightnessAlpha = BRIGHTNESS_OFF;
			}
		}
	}
}


//　入力処理--------------------------------------------------------------------------------
int JudgeZone::UpdateInputKey() {

	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0) // キーコードに対応するキーが押されていたら
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


// 描画----------------------------------------------------------------------------------------------------
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



// １回ごとの判定結果を小さく表示
void JudgeZone::RenderJudgeScore_OneMoment(TIMING j) {

	// スコア対応表
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
	// 判定結果
	DrawStringEx(judgeZone[_column]._x1 + 100, judgeZone[_column]._y1 - 80, 0xFF00CED1, grade);
	// 獲得スコア
	DrawStringEx(judgeZone[_column]._x1 + 100, judgeZone[_column]._y1 - 50, 0xFF00CED1, score);
	SetFontSize(DEFAULT_FONT_SIZE);
}


void JudgeZone::RenderMap() {

	// 横線描画
	DrawLineAA(_judgeZone_x1_ceilingLine, _judgeZone_y1_ceilingLine, _judgeZone_x2_ceilingLine, _judgeZone_y1_ceilingLine, -1, 2.0f); // 上辺
	DrawLineAA(_judgeZone_x1_bottomLine, _judgeZone_y1_bottomLine, _judgeZone_x2_bottomLine, _judgeZone_y1_bottomLine, -1, 2.0f); // 下辺

	float space = 50.0f;
	float _x1;  // 始点X
	float _x2;  // 終点X

	// 斜め線5本描画
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

		// 斜め線描画
		DrawLineAA(_x1, _diagonalLine_y1, _x2, _diagonalLine_y2, -1, 2.0f);
	}
}
