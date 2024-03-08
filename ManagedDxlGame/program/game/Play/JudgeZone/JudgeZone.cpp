#include "JudgeZone.h"
#include "../Score_Combo/ScoreCombo.h"
#include "../../Main.h"
#include "../Note/Normal/NormalNote.h"
#include "../Note/Long/LongNote.h"
#include "../ScenePlaySong.h"


namespace {

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


JudgeZone::JudgeZone() {

	scoreComboRef = new ScoreCombo();
}



void JudgeZone::InitJudgeZone() {

	for (column = 0; column < JUDGE_NUM; column++) {

		// x軸は20から開始
		// ｙ軸は上辺600、下辺650で固定
		switch (column)
		{
		case 0:// レーン0
			judgeZone[column].x1 = judgeZoneX_left_1;
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_left_1 + judgeZoneX_right_2 / JUDGE_NUM;
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 1: // レーン1
			judgeZone[column].x1 = judgeZoneX_left_1 + judgeZoneX_right_2 / JUDGE_NUM;
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = (judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2) - 45);
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 2: // レーン2
			judgeZone[column].x1 = (judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2) - 45);
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2.5f + 65);
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		case 3: // レーン3
			judgeZone[column].x1 = judgeZoneX_left_1 + (judgeZoneX_right_2 / JUDGE_NUM * 2.5f + 65);
			judgeZone[column].y1 = judgeZoneY_top_1;
			judgeZone[column].x2 = judgeZoneX_right_1;
			judgeZone[column].y2 = judgeZoneY_top_2;
			judgeZone[column].color = GetColor(0, 200, 200);
			break;
		}

		judgeZone[column].isActive = true;
	}
}



void JudgeZone::RenderMap() {

	// 横線描画
	DrawLineAA(judgeZoneX_left_1, judgeZoneY_top_1, judgeZoneX_right_1, judgeZoneY_top_1, -1, 2.0f); // 上辺
	DrawLineAA(judgeZoneX_left_2, judgeZoneY_top_2, judgeZoneX_right_2, judgeZoneY_top_2, -1, 2.0f); // 下辺

	float space = 50.0f;
	float x1;  // 始点X
	float x2;  // 終点X

	// 斜め線5本描画
	for (int i = 0; i < JUDGE_NUM + 1; i++) {

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

		// 斜め線描画
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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, judgeZone[column].brightnessAlpha);

			DrawRoundRectAA(
				judgeZone[column].x1,
				judgeZone[column].y1,
				judgeZone[column].x2,
				judgeZone[column].y2,
				10.f, 0.1f, 4,
				judgeZone[column].color, true, 1.5f
			);
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}



// １回ごとの判定結果を小さく表示
void JudgeZone::RenderJudgeScore_OneMoment(JUDGE_TIMING j) {

	// スコア対応表
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
	// 判定結果
	DrawStringEx(judgeZone[column].x1 + 100, judgeZone[column].y1 - 80, 0xFF00CED1, grade);
	// 獲得スコア
	DrawStringEx(judgeZone[column].x1 + 100, judgeZone[column].y1 - 50, 0xFF00CED1, score);
	SetFontSize(DEFAULT_FONT_SIZE);
}



void JudgeZone::JudgeGrade(std::vector<NormalNote>& normal_note, const int& row, const double& _timer, std::vector<double>& should_input_time) {

	// 入力すべきタイミングと実際の入力タイミングとの差を取得
	double timeDiff = abs(should_input_time[row] - _timer);

	if (timeDiff > 1.8) return;

		normal_note[row].isActive = false;

	if (timeDiff < 0.2) {


		scoreComboRef->myScore += 1000;
		scoreComboRef->myCombo++;
		scoreComboRef->perfect_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		scoreComboRef->y1_combo -= 5;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.4) {

		scoreComboRef->myScore += 750;
		scoreComboRef->myCombo++;
		scoreComboRef->great_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GREAT);
		return;
	}
	else if (timeDiff < 0.6) {

		scoreComboRef->myScore += 500;
		scoreComboRef->myCombo++;
		scoreComboRef->good_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GOOD);
		return;
	}
	else if (timeDiff < 0.8) {

		scoreComboRef->myScore += 200;
		scoreComboRef->myCombo = 0;
		scoreComboRef->poor_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::POOR);
		return;
	}
	else if (timeDiff < 1.0) {

		scoreComboRef->myCombo = 0;
		scoreComboRef->miss_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::MISS);
		return;
	}
}


void JudgeZone::JudgeGrade(std::vector<LongNote>& long_note, const int& row, const double& timer, std::vector<double>& should_input_time) {

	// 入力すべきタイミングと実際の入力タイミングとの差を取得
	double timeDiff = abs(should_input_time[row] - timer);

	if (timeDiff > 1.8) return;

	long_note[row].isActive = false;

	if (timeDiff < 0.6) {

		scoreComboRef->myScore += 1000;
		scoreComboRef->myCombo++;
		scoreComboRef->perfect_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		scoreComboRef->y1_combo -= 5;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::PERFECT);
		return;
	}
	else if (timeDiff < 0.8) {

		scoreComboRef->myScore += 750;
		scoreComboRef->myCombo++;
		scoreComboRef->great_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GREAT);
		return;
	}
	else if (timeDiff < 1.0) {

		scoreComboRef->myScore += 500;
		scoreComboRef->myCombo++;
		scoreComboRef->good_count++;
		scoreComboRef->comboAnimationFrames = scoreComboRef->comboAnimationDuration;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::GOOD);
		return;
	}
	else if (timeDiff < 1.2) {

		scoreComboRef->myScore += 200;
		scoreComboRef->myCombo = 0;
		scoreComboRef->poor_count++;
		RenderJudgeScore_OneMoment(JUDGE_TIMING::POOR);
		return;
	}
}


int JudgeZone::UpdateInputKey() {

	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);

	for (int i = 0; i < 256; i++)
	{
		if (tmpKey[i] != 0) // キーコードに対応するキーが押されていたら
		{
			ReceiveKeyInput[i]++;
		}
		else
		{
			ReceiveKeyInput[i] = 0;
		}
	}
	return 0;
}


void JudgeZone::JudgeNoteHit_ByInputKey(std::vector<NormalNote>& normal_note, const int& row, const double& timer, std::vector<double>& should_input_time) {

	UpdateInputKey();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (column = 0; column < JUDGE_NUM; column++) {

			if (ReceiveKeyInput[KEYS[column]] == 1) {

				// ノーマルノーツの当たり判定
				if (normal_note[row].isActive) {

					JudgeGrade(normal_note, row, timer, should_input_time);
				}

				// キーを入力したら色が変わる
				judgeZone[column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (ReceiveKeyInput[KEYS[column]] == 0) {

				// 放したら色を戻す
				judgeZone[column].brightnessAlpha = BRIGHTNESS_OFF;
			}
		}
	}
}


void JudgeZone::JudgeNoteHit_ByInputKey(std::vector<LongNote>& long_note, const int& row, const double& _timer, std::vector<double>& should_input_time) {

	UpdateInputKey();

	for (int i = 0; i < should_input_time.size(); i++) {

		for (column = 0; column < JUDGE_NUM; column++) {

			if (ReceiveKeyInput[KEYS[column]]) {

				// ロングノーツの当たり判定
				if (long_note[row].isActive) {

					JudgeGrade(long_note, row, _timer, should_input_time);
				}

				// キーを入力したら色が変わる
				judgeZone[column].brightnessAlpha = BRIGHTNESS_ON;
			}
			else if (ReceiveKeyInput[KEYS[column]] == 0) {

				// 放したら色を戻す
				judgeZone[column].brightnessAlpha = BRIGHTNESS_OFF;
			}
		}
	}
}