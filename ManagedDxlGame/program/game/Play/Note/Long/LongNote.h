#pragma once
#include "../Notes.h"


class LongNote : public Notes
{
public:

	LongNote() {}
	explicit LongNote(const std::string& csv_ref);

	/*
�@ 1.�@X1���W
   2.�@Y1���W
   3.�@X�������x
   4.�@Y�������x
   5.�@�T�C�Y
   6.�@�J���[
   7.�@�A�N�e�B�u���
�@�@*/

	LongNote(
		float _longStart_x1, float _longEnd_x1, 
		float _long_y1, 
		float x_vel_long, float y_vel_long,
		float _long_size, int color_long, bool active_long
	) :Notes(
		_longStart_x1, _longEnd_x1,
		_long_y1, 
		x_vel_long, y_vel_long,
		_long_size, 
		color_long,
		active_long
	) {}

	void UpdateNotes(const double& timer, const float& deltaTime) override;

private:

	 /*
	     DRY�����ɂ�莗�������͂܂Ƃ߂ď���
     */

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

	float _long_startAndend_distanceRatio = 1.5f;
};