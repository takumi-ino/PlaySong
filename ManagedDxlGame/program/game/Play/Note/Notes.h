#pragma once
#include "../../utility/DxLib_Engine.h"


class Notes {

public:

	Notes() {}
	Notes(const std::string& csv_key);

	Notes(
		float _x1,
		float _y1,
		float _velocity_x,
		float _velocity_y,
		float size,
		int _color,
		bool _isActive
	);

	Notes(
		float _longStart_x1,
		float _longEnd_x1,
		float _long_y1,
		float _velocity_x,
		float _velocity_y,
		float _long_size,
		int _color,
		bool _isActive
	);

	virtual void UpdateNotes(
		const double& timer, const float& deltaTime) 
	{}

public:

	bool  _isActive{};

protected:

	// 初期化用定数------------------------------------------------------------
	const int   _NOTE_COL_NUM = 4;
	const int   _NOTE_SPACE = 50;
	const float _STARTPOS_X1 = 565.f;   // ノーツ[0] 左上X
	const float _STARTPOS_Y1 = 100.f;   // ノーツ[0] 左上Y
	const float _STARTPOS_X2 = 0.1f;    // ノーツ[0] 右下X
	const float _STARTPOS_Y2 = 0.01f;   // ノーツ[0] 右下Y

	// ロングノーツ------------------------------------------------------------
	float _longStart_x1{};
	float _longEnd_x1{};
	float _long_y1{};
	float _long_size = 2.0f; // 線の長さ (ロングノーツの終了位置で使用）

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
	int   _color{};

	float _x1{};
	float _y1{};
	float _velocity_x{};   // 横方向に動く速度
	float _velocity_y{};   // 縦方向に動く速度
	float _size{};   	   // サイズ

	std::vector<std::string> _noteType{};      // ノーツタイプ
	std::vector<int>         _lane{};          // 生成位置（レーン）

private:

	// 1秒間に何ピクセル移動するか
	double _moveSpeed_perPixel = 600.0;
	// 生成位置から判定位置までの距離 （NotesクラスとJudgeZoneクラス参照
	double _noteMoveWayDistance = 500.0;

	// 判定エリアに到達するまでの時間
	//判定エリアに到達する時刻よりも早く出現させなくてはならないため、時間を引く
	double _reachToJudgeZone_perfectSecond = _noteMoveWayDistance / _moveSpeed_perPixel;

	std::vector<float> _justSpawnNoteTime_ms{};  // 生成タイミング
};