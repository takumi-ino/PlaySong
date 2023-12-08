#pragma once
#include "../../utility/DxLib_Engine.h"

#define JUDGE_NUM 4 // 判定エリア

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

	void RenderMap(); 	     // 全体的な描画

	void RenderJudgeZones(); // 判定エリア描画

	// ノーマルノーツの当たり判定処理
	void JudgeNoteHit_ByInputKey(
		std::vector<NormalNote>& normal_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	// ロングノーツの当たり判定処理
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


	int perfect_time_size[4] = { 0 };     // 初期化処理の0と入ってくる0とを区別する
	int Key[256];                         // キー入力用

	double perfect_times[136][4] = { 0 }; // 判定ラインにノーツが到達する時刻
	const double judgeableDistance = 1000.0;
	double actualDistance = 0.0;

	// 横線（判定エリア全体範囲）
	// 上辺	
	const int MARGIN_LEFT_AND_RIGHT = 50; // 判定エリアとウィンドウ端との距離
	const int AREA_HEIGHT_TOPPOS = 600;
	const int AREA_RANGE = 55;

	float judgeZoneX_left_1 = MARGIN_LEFT_AND_RIGHT;  //  始点X
	float judgeZoneY_top_1 = AREA_HEIGHT_TOPPOS;    //  始点Y
	float judgeZoneX_right_1 = DXE_WINDOW_WIDTH - MARGIN_LEFT_AND_RIGHT;  //  終点X
	float judgeZoneY_bottom_1 = 5.f;  // 終点Y
	// 下辺
	float judgeZoneX_left_2 = 0.f;  //  始点X
	float judgeZoneY_top_2 = AREA_HEIGHT_TOPPOS + AREA_RANGE;  //  始点Y
	float judgeZoneX_right_2 = DXE_WINDOW_WIDTH;  //  終点X
	float judgeZoneY_bottom_2 = 5.f;  // 終点Y

	//------------------------------------------------------------

	// 縦線（斜め）※５本 判定エリアを４等分に
	const int VERTICAL_STARTPOS = 100;             //　始点Y
	const int VERTICAL_ENDPOS = DXE_WINDOW_HEIGHT; //　終点Y

	float base_x1 = 490;                // 斜め線の始点X
	float base_y1 = VERTICAL_STARTPOS;  // 斜め線の始点Y
	float base_y2 = VERTICAL_ENDPOS;	// 斜め線の終点Y

	//------------------------------------------------------------

	// 各判定エリアの横幅
	const int EACHAREA_WIDTH = DXE_WINDOW_WIDTH / JUDGE_NUM;

	// 判定エリア1～4　各種情報設定
	float x1;  // x左上座標
	float y1;  // ｙ左上座標
	float x2;  // ｘ右下座標
	float y2;  // ｙ右下座標
	float size;
	int color;
	int column;

	bool active = true;

	// 判定エリアの明度調整
	int alpha;
	const int BRIGHTNESS_ON = 170;
	const int BRIGHTNESS_OFF = 70;
};