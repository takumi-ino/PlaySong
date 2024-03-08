#include "LongNote.h"
#include "../../ScenePlaySong.h"
#include "../../JudgeZone/JudgeZone.h"


LongNote::LongNote(const std::string& csv_ref) : Notes(csv_ref) {

	long_note_0.reserve(_long_note_row_num_lane0_base);
	long_note_1.reserve(_long_note_row_num_lane1_base);
	long_note_2.reserve(_long_note_row_num_lane2_base);
	long_note_3.reserve(_long_note_row_num_lane3_base);


	for (int row = 0; row < _long_note_row_num_lane0_base; ++row) {

		this->x1_long_start = static_cast<float>(STARTPOS_X1);   // x左上
		this->x1_long_end = static_cast<float>(STARTPOS_X1);   // x左上
		this->y1_long = static_cast<float>(STARTPOS_Y1);   // y左上 

		this->x_vel = -70.0f;     // x方向の速度
		this->y_vel = 120.0f;     // y方向の速度
		this->size_long = 1.f;         // サイズ
		this->color = GetColor(147, 112, 219);  // 色
		this->isActive = true;      // アクティブ状態

		long_note_0.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane1_base; ++row) {

		this->x1_long_start = STARTPOS_X1 + noteSpace;
		this->x1_long_end = STARTPOS_X1 + noteSpace;
		this->y1_long = static_cast<float>(STARTPOS_Y1);

		this->x_vel = -12.0f;
		this->y_vel = 90.0f;
		this->size_long = 1.f;
		this->color = GetColor(147, 112, 219);
		this->isActive = true;

		long_note_1.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane2_base; ++row) {

		this->x1_long_start = STARTPOS_X1 + (noteSpace * 2);
		this->x1_long_end = STARTPOS_Y1;
		this->y1_long = STARTPOS_Y1;

		this->x_vel = 21.0f;
		this->y_vel = 70.0f;
		this->size_long = 1.f;
		this->color = GetColor(147, 112, 219);
		this->isActive = true;

		long_note_2.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane3_base; ++row) {

		this->x1_long_start = STARTPOS_X1 + (noteSpace * 3);
		this->x1_long_end = STARTPOS_X1 + (noteSpace * 3);

		this->y1_long = STARTPOS_Y1;
		this->x_vel = 50.0f;
		this->y_vel = 65.0f;
		this->size_long = 1.f;
		this->color = GetColor(147, 112, 219);
		this->isActive = true;

		long_note_3.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->isActive
		);
	}
}


void LongNote::UpdateLongNotes_DRY(
	std::vector<LongNote>& longNote,
	const double timer,
	std::vector<double> longStartSpawnTime_eachLane,
	std::vector<double> longEndSpawnTime_eachLane,
	const float deltaTime,
	const int space) 
{

	for (auto it_long = longNote.begin(); it_long != longNote.end(); it_long++) {

		// ノーツと当たり判定エリアの距離を取得
		int lane_row = static_cast<int>(std::distance(longNote.begin(), it_long));

		if ((*it_long).isActive) {  // アクティブなら

			//　開始時間
			if (timer > longStartSpawnTime_eachLane[std::distance(longNote.begin(), it_long)]) {

				(*it_long).RenderStartNotes();

				// ノーツの位置とサイズを更新
				(*it_long).x1_long_start += (*it_long).x_vel * 3 * deltaTime;  // x座標
				(*it_long).y1_long += (*it_long).y_vel * 3 * deltaTime;        // y座標
				(*it_long).size_long += (*it_long).y_vel * 80 * deltaTime;     // サイズ
			}

			//　終了時間
			if (timer > longEndSpawnTime_eachLane[std::distance(longNote.begin(), it_long)]) {

				(*it_long).RenderEndNotes();

				if (std::next(it_long, 1) != longNote.end()) {

					auto next = std::next(it_long, 1);

					// 無効になったノーツを元の位置に戻す
					(*next).x1_long_start = STARTPOS_X1 + space;
					(*next).y1_long = STARTPOS_Y1;
					(*next).size_long = 1.0f;
				}

				(*it_long).isActive = false;
			}
			else {

				(*it_long).x1_long_end += (*it_long).x_vel * 3 * deltaTime;    // x座標
				(*it_long).y1_long += (*it_long).y_vel * 3 * deltaTime;    // y座標
				(*it_long).size_long += (*it_long).y_vel * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(longNote, lane_row, timer, longStartSpawnTime_eachLane);
			judgeZone->JudgeNoteHit_ByInputKey(longNote, lane_row, timer, longEndSpawnTime_eachLane);
		}
	}
}


void LongNote::UpdateNotes(const double& timer, const float& deltaTime) {

	UpdateLongNotes_DRY(long_note_0, timer, _longStartTime_lane0_base, _longEndTime_lane0_base, deltaTime);
	UpdateLongNotes_DRY(long_note_1, timer, _longStartTime_lane1_base, _longEndTime_lane1_base, deltaTime, noteSpace);
	UpdateLongNotes_DRY(long_note_2, timer, _longStartTime_lane2_base, _longEndTime_lane2_base, deltaTime, noteSpace * 2);
	UpdateLongNotes_DRY(long_note_3, timer, _longStartTime_lane3_base, _longEndTime_lane3_base, deltaTime, noteSpace * 3);
}



void LongNote::RenderStartNotes() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	// 開始ノーツ
	DrawRoundRectAA(
		x1_long_start - size_long / 100 * 1.25f / 1.5f,
		y1_long - size_long / 100 * 0.15f / 1.5f,
		x1_long_start + size_long / 200 * 1.25f / 1.5f,
		y1_long + size_long / 200 * 0.15f / 1.5f,
		5.f, 0.2f, 4, color, true, 1.5f
	);

	// ロングノーツの開始と終了のノーツをつなぐ線
	DrawLineAA(
		x1_long_start - size_long / 100 * 1.25f / 1.5f,
		y1_long - size_long / 100 * 0.15f / 1.5f,
		x1_long_end * long_start_end_distanceRatio - size_long / 100 * 1.25f,
		y1_long * long_start_end_distanceRatio - size_long / 100 * 0.15f,
		color,
		1.5f
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void LongNote::RenderEndNotes() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	// 終了ノーツ
	DrawRoundRectAA(
		x1_long_end * long_start_end_distanceRatio - size_long / 100 * 1.25f,
		y1_long * long_start_end_distanceRatio - size_long / 100 * 0.15f,
		x1_long_end * long_start_end_distanceRatio + size_long / 200 * 1.25f,
		y1_long * long_start_end_distanceRatio + size_long / 200 * 0.15f,
		5.f, 0.2f, 4, color, true, 1.5f
	);

	DrawLineAA(
		x1_long_start + size_long / 200 * 1.25f / 1.5f,
		y1_long + size_long / 200 * 0.15f / 1.5f,
		x1_long_end * long_start_end_distanceRatio + size_long / 200 * 1.25f,
		y1_long * long_start_end_distanceRatio + size_long / 200 * 0.15f,
		color,
		1.5f
	);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}