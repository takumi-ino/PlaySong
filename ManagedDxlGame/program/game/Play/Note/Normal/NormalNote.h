#pragma once
#include "../Notes.h"
#include <vector>
#include "../../../../dxlib_ext/dxlib_ext.h"


class NormalNote : public Notes
{
public:

	NormalNote() {}

	explicit NormalNote(const std::string& csv_ref);


	/*
	�@ 1.�@X1���W
	   2.�@Y1���W
	   3.�@X�������x
	   4.�@Y�������x
	   5.�@�T�C�Y
	   6.�@�J���[
	   7.�@�A�N�e�B�u���
	*/
	NormalNote(
		float x1_normal, float y1_normal, float x_vel_normal, float y_vel_normal, float size_normal, int color_normal, bool active_normal) :
		Notes(x1_normal, y1_normal, x_vel_normal, y_vel_normal, size_normal, color_normal, active_normal
		) {}

	void UpdateNotes(double _timer, float deltaTime) override;
	void RenderNotes();

public:

	std::vector<NormalNote> normal_note_0;
	std::vector<NormalNote> normal_note_1;
	std::vector<NormalNote> normal_note_2;
	std::vector<NormalNote> normal_note_3;
};