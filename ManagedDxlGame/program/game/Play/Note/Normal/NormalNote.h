#pragma once
#include "../Notes.h"


class NormalNote : public Notes
{
public:

	NormalNote() {}
	explicit NormalNote(const std::string& csv_ref);

	/*
	　 1.　X1座標
	   2.　Y1座標
	   3.　X方向速度
	   4.　Y方向速度
	   5.　サイズ
	   6.　カラー
	   7.　アクティブ状態
	*/

	NormalNote(
		float x1_normal, float y1_normal,
		float x_vel_normal, float y_vel_normal, 
		float size_normal, int color_normal, bool active_normal) 
		:	Notes(
			x1_normal, y1_normal,
			x_vel_normal, y_vel_normal,
			size_normal, 
			color_normal, 
			active_normal
	) {}

	void UpdateNotes(const double& timer, const float& deltaTime) override;

private:

	/*
	    DRY原則により似た処理はまとめて処理
	*/

	void UpdateNotes_DRY(
		std::vector<NormalNote>& normalNote,
		const double timer, 
		const std::vector<double> normalSpawnTime_eachLane,
		const float deltaTime,
		const int space = 0
	);

	void RenderNotes();

public:

	std::vector<NormalNote> normal_note_0{};
	std::vector<NormalNote> normal_note_1{};
	std::vector<NormalNote> normal_note_2{};
	std::vector<NormalNote> normal_note_3{};
};