#pragma once
#include "../../utility/DxLib_Engine.h"

constexpr static int JUDGE_NUM = 4; // 判定エリア

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


	// 初期化--------------------------------------------------------------------------------
	void InitJudgeZone();
	void SetScoreComboRef(ScoreCombo* scoreComboRef) { scoreComboRef = scoreComboRef; };

	// 当たり判定--------------------------------------------------------------------------------
	void JudgeNoteHit_ByInputKey(	         // ノーマルノーツ
		std::vector<NormalNote>& normal_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);
	void JudgeNoteHit_ByInputKey(	         // ロングノーツ
		std::vector<LongNote>& long_note,
		const int& row,
		const double& timer,
		std::vector<double>& should_input_time
	);

	// 描画--------------------------------------------------------------------------------
	void RenderMap(); 	     // 全体
	void RenderJudgeZones(); // 判定エリア

private:

	// 判定処理----------------------------------------------------------------------------
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
	void RenderJudgeScore_OneMoment(JUDGE_TIMING);  // 判定処理1回ごとに一瞬 Grade（ PerfectやGreatなど ）と獲得スコアを表示
	int  UpdateInputKey();                          // キー入力受付

private:

	ScoreCombo* scoreComboRef = nullptr;

private:

	int ReceiveKeyInput[256]{}; // キー入力情報取得
	int brightnessAlpha{};	    // 判定エリアの明度調整

	bool isActive = true;

	// 横線（判定エリア全体範囲）-------------------------------------------------------------------

	// 上辺	------------------------------------------------------------
	const int MARGIN_LEFT_AND_RIGHT = 50; // 判定エリアとウィンドウ端との距離
	const int AREA_HEIGHT_TOPPOS = 600;
	const int AREA_RANGE = 55;

	float judgeZoneX_left_1 = (float)MARGIN_LEFT_AND_RIGHT;                      //  始点X
	float judgeZoneY_top_1 = (float)AREA_HEIGHT_TOPPOS;                          //  始点Y
	float judgeZoneX_right_1 = (float)DXE_WINDOW_WIDTH - MARGIN_LEFT_AND_RIGHT;  //  終点X
	float judgeZoneY_bottom_1 = 5.f;                                             //  終点Y

	// 下辺------------------------------------------------------------
	float judgeZoneX_left_2 = 0.f;                                        //  始点X
	float judgeZoneY_top_2 = (float)AREA_HEIGHT_TOPPOS + AREA_RANGE;      //  始点Y
	float judgeZoneX_right_2 = (float)DXE_WINDOW_WIDTH;                   //  終点X
	float judgeZoneY_bottom_2 = 5.f;                                      //  終点Y

	// 縦線（斜め）※５本 判定エリアを４等分に--------------------------------------------------------
	const int VERTICAL_STARTPOS = 100;              //　始点Y
	const int VERTICAL_ENDPOS = DXE_WINDOW_HEIGHT;  //　終点Y
	
	float base_x1 = 490.f;                          // 斜め線の始点X
	float base_y1 = (float)VERTICAL_STARTPOS;       // 斜め線の始点Y
	float base_y2 = (float)VERTICAL_ENDPOS;	        // 斜め線の終点Y

	// 判定エリア1～4　各種情報設定-------------------------------------------------------------------
	float x1{};    // x左上座標
	float y1{};    // ｙ左上座標
	float x2{};    // ｘ右下座標
	float y2{};    // ｙ右下座標
	float size{};
	int color{};
	int column{};
};