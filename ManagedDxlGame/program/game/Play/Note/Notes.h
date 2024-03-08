#pragma once
#include "../../utility/DxLib_Engine.h"
#include "../../utility/tnlSequence.h"


class Notes {

public:

	Notes() {}
	Notes(const std::string& csv_key);

	Notes(
		float x1,
		float y1,
		float x_vel,
		float y_vel,
		float size,
		int color,
		bool isActive
	);

	Notes(
		float x1_long_start,
		float x1_long_end,
		float y1_long,
		float x_vel,
		float y_vel,
		float size_long,
		int color,
		bool isActive
	);

	virtual void UpdateNotes(const double& timer, const float& deltaTime) {}

public:

	bool  isActive{};

protected:

	// 初期化用定数------------------------------------------------------------
	const int   NOTE_COL_NUM = 4;
	const int   noteSpace = 50;
	const float   STARTPOS_X1 = 565.f;     // ノーツ[0] 左上X
	const float   STARTPOS_Y1 = 100.f;     // ノーツ[0] 左上Y
	const float STARTPOS_X2 = 0.1f;    // ノーツ[0] 右下X
	const float STARTPOS_Y2 = 0.01f;   // ノーツ[0] 右下Y

	// ロングノーツ------------------------------------------------------------
	float x1_long_start{};
	float x1_long_end{};
	float y1_long{};
	float size_long = 2.0f; // 線の長さ (ロングノーツの終了位置で使用）

	std::vector<double> _longStartTime_lane0_base{};
	std::vector<double> _longStartTime_lane1_base{};
	std::vector<double> _longStartTime_lane2_base{};
	std::vector<double> _longStartTime_lane3_base{};

	std::vector<double> _longEndTime_lane0_base{};
	std::vector<double> _longEndTime_lane1_base{};
	std::vector<double> _longEndTime_lane2_base{};
	std::vector<double> _longEndTime_lane3_base{};

	int         _long_note_row_num_lane0_base{};
	int         _long_note_row_num_lane1_base{};
	int         _long_note_row_num_lane2_base{};
	int         _long_note_row_num_lane3_base{};

	// ノーマルノーツ------------------------------------------------------------
	std::vector<double> _normalSpawnTime_lane0_base{};
	std::vector<double> _normalSpawnTime_lane1_base{};
	std::vector<double> _normalSpawnTime_lane2_base{};
	std::vector<double> _normalSpawnTime_lane3_base{};

	int         _normal_note_row_num_lane0_base{};
	int         _normal_note_row_num_lane1_base{};
	int         _normal_note_row_num_lane2_base{};
	int         _normal_note_row_num_lane3_base{};

	// ノーマル・ロング共通----------------------------------------
	int   color{};

	float x1{};
	float y1{};
	float x_vel{};   // 横方向に動く速度
	float y_vel{};   // 縦方向に動く速度
	float size{};	 // サイズ
	float speed{};   // スピード

	std::vector<std::string> NoteType{};      // ノーツタイプ
	std::vector<int>         lane{};          // 生成位置（レーン）

private:

	// 1秒間に何ピクセル移動するか
	double moveSpeed_pixel = 600.0;
	// 生成位置から判定位置までの距離 （NotesクラスとJudgeZoneクラス参照
	double moveDistance = 500.0;
	//判定エリアに到達する時刻よりも早く出現させなくてはならないため時間を引く
	double moveToJudgeZoneSecond = moveDistance / moveSpeed_pixel;

	std::vector<float>       justSpawnTime_ms{};  // 生成タイミング
};