#pragma once
#include "../Notes.h"
#include "../../../../dxlib_ext/dxlib_ext.h"

class LongNote : public Notes
{
public:

	LongNote() {}
	explicit LongNote(const std::string& csv_ref);

	/*
　 1.　X1座標
   2.　Y1座標
   3.　X方向速度
   4.　Y方向速度
   5.　サイズ
   6.　カラー
   7.　アクティブ状態
　　*/

	LongNote(
		float x1_long_start, float x1_long_end, 
		float y1_long, 
		float x_vel_long, float y_vel_long,
		float size_long, int color_long, bool active_long
	) :Notes(
		x1_long_start, x1_long_end,
		y1_long, 
		x_vel_long, y_vel_long,
		size_long, 
		color_long,
		active_long
	) {}

	void UpdateNotes(const double& timer, const float& deltaTime) override;

private:

	void UpdateLongNotes_DRY(
		std::vector<LongNote>& longNote,
		const double timer,
		const std::vector<double> longSpawnTime_eachLane,
		const std::vector<double> longEndSpawnTime_eachLane,
		const float deltaTime,
		const int space = 0
	);

	void RenderStartNotes();
	void RenderEndNotes();

public:

	std::vector<LongNote> long_note_0{};
	std::vector<LongNote> long_note_1{};
	std::vector<LongNote> long_note_2{};
	std::vector<LongNote> long_note_3{};

private:

	float long_start_end_distanceRatio = 1.5f;
};