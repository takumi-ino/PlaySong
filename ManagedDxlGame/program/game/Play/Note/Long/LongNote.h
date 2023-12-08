#pragma once
#include "../Notes.h"
#include <vector>
#include "../../../../dxlib_ext/dxlib_ext.h"


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
		float x1_long_start, float x1_long_end, float y1_long, float x_vel_long, float y_vel_long, float size_long, int color_long, bool active_long) :
		Notes(x1_long_start, x1_long_end, y1_long, x_vel_long, y_vel_long, size_long, color_long, active_long
	) {}

	void UpdateNotes(double _timer, float deltaTime) override;
	void RenderStartNotes();
	void RenderEndNotes();

public:

	std::vector<LongNote> long_note_0;
	std::vector<LongNote> long_note_1;
	std::vector<LongNote> long_note_2;
	std::vector<LongNote> long_note_3;
};