#pragma once

constexpr static int JUDGE_NUM = 4; // 判定エリア

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

	// 初期化--------------------------------------------------------------------------------
	void InitJudgeZone();
	void SetScoreComboRef(ScoreCombo* _scoreComboRef) { _scoreComboRef = _scoreComboRef; };

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
	void RenderJudgeScore_OneMoment(TIMING);  // 判定処理1回ごとに一瞬 Grade（ PerfectやGreatなど ）と獲得スコアを表示
	int  UpdateInputKey();                    // キー入力受付

private:

	ScoreCombo* _scoreComboRef = nullptr;

private:

	int   _receiveKeyInputBuf[256]{}; // キー入力情報取得
	int   brightnessAlpha{};	     // 判定エリアの明度調整

	bool  _isActive = true;

	// 判定エリア1～4　各種情報----------------------------------
	int   _color{};
	int   _column{};

	float _x1{};    // x左上座標
	float _y1{};    // ｙ左上座標
	float _x2{};    // ｘ右下座標
	float _y2{};    // ｙ右下座標
};