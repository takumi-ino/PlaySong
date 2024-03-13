#include "LongNote.h"
#include "../../../utility/DxLib_Engine.h"
#include "../../ScenePlaySong.h"
#include "../../JudgeZone/JudgeZone.h"


LongNote::LongNote(const std::string& csv_ref) : Notes(csv_ref) {

	long_note_0.reserve(_long_note_row_num_lane0_base);
	long_note_1.reserve(_long_note_row_num_lane1_base);
	long_note_2.reserve(_long_note_row_num_lane2_base);
	long_note_3.reserve(_long_note_row_num_lane3_base);


	for (int row = 0; row < _long_note_row_num_lane0_base; ++row) {

		this->_longStart_x1 = static_cast<float>(_STARTPOS_X1);   // x左上
		this->_longEnd_x1 = static_cast<float>(_STARTPOS_X1);   // x左上
		this->_long_y1 = static_cast<float>(_STARTPOS_Y1);   // y左上 

		this->_velocity_x = -70.0f;     // x方向の速度
		this->_velocity_y = 120.0f;     // y方向の速度
		this->_long_size = 1.f;         // サイズ
		this->_color = GetColor(147, 112, 219);  // 色
		this->_isActive = true;      // アクティブ状態

		long_note_0.emplace_back(

			this->_longStart_x1,
			this->_longEnd_x1,
			this->_long_y1,

			this->_velocity_x,
			this->_velocity_y,
			this->_long_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane1_base; ++row) {

		this->_longStart_x1 = _STARTPOS_X1 + _NOTE_SPACE;
		this->_longEnd_x1 = _STARTPOS_X1 + _NOTE_SPACE;
		this->_long_y1 = static_cast<float>(_STARTPOS_Y1);

		this->_velocity_x = -12.0f;
		this->_velocity_y = 90.0f;
		this->_long_size = 1.f;
		this->_color = GetColor(147, 112, 219);
		this->_isActive = true;

		long_note_1.emplace_back(

			this->_longStart_x1,
			this->_longEnd_x1,
			this->_long_y1,

			this->_velocity_x,
			this->_velocity_y,
			this->_long_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane2_base; ++row) {

		this->_longStart_x1 = _STARTPOS_X1 + (_NOTE_SPACE * 2);
		this->_longEnd_x1 = _STARTPOS_Y1;
		this->_long_y1 = _STARTPOS_Y1;

		this->_velocity_x = 21.0f;
		this->_velocity_y = 70.0f;
		this->_long_size = 1.f;
		this->_color = GetColor(147, 112, 219);
		this->_isActive = true;

		long_note_2.emplace_back(

			this->_longStart_x1,
			this->_longEnd_x1,
			this->_long_y1,

			this->_velocity_x,
			this->_velocity_y,
			this->_long_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _long_note_row_num_lane3_base; ++row) {

		this->_longStart_x1 = _STARTPOS_X1 + (_NOTE_SPACE * 3);
		this->_longEnd_x1 = _STARTPOS_X1 + (_NOTE_SPACE * 3);

		this->_long_y1 = _STARTPOS_Y1;
		this->_velocity_x = 50.0f;
		this->_velocity_y = 65.0f;
		this->_long_size = 1.f;
		this->_color = GetColor(147, 112, 219);
		this->_isActive = true;

		long_note_3.emplace_back(

			this->_longStart_x1,
			this->_longEnd_x1,
			this->_long_y1,

			this->_velocity_x,
			this->_velocity_y,
			this->_long_size,
			this->_color,
			this->_isActive
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

		if ((*it_long)._isActive) {  // アクティブなら

			//　開始時間
			if (timer > longStartSpawnTime_eachLane[std::distance(longNote.begin(), it_long)]) {

				(*it_long).RenderStartNotes();

				// ノーツの位置とサイズを更新
				(*it_long)._longStart_x1 += (*it_long)._velocity_x * 3 * deltaTime;  // x座標
				(*it_long)._long_y1 += (*it_long)._velocity_y * 3 * deltaTime;        // y座標
				(*it_long)._long_size += (*it_long)._velocity_y * 80 * deltaTime;     // サイズ
			}

			//　終了時間
			if (timer > longEndSpawnTime_eachLane[std::distance(longNote.begin(), it_long)]) {

				(*it_long).RenderEndNotes();

				if (std::next(it_long, 1) != longNote.end()) {

					auto next = std::next(it_long, 1);

					// 無効になったノーツを元の位置に戻す
					(*next)._longStart_x1 = _STARTPOS_X1 + space;
					(*next)._long_y1 = _STARTPOS_Y1;
					(*next)._long_size = 1.0f;
				}

				(*it_long)._isActive = false;
			}
			else {

				(*it_long)._longEnd_x1 += (*it_long)._velocity_x * 3 * deltaTime;    // x座標
				(*it_long)._long_y1 += (*it_long)._velocity_y * 3 * deltaTime;    // y座標
				(*it_long)._long_size += (*it_long)._velocity_y * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(longNote, lane_row, timer, longStartSpawnTime_eachLane);
			judgeZone->JudgeNoteHit_ByInputKey(longNote, lane_row, timer, longEndSpawnTime_eachLane);
		}
	}
}


void LongNote::UpdateNotes(const double& timer, const float& deltaTime) {

	UpdateLongNotes_DRY(long_note_0, timer, _longStartTime_lane0_base, _longEndTime_lane0_base, deltaTime);
	UpdateLongNotes_DRY(long_note_1, timer, _longStartTime_lane1_base, _longEndTime_lane1_base, deltaTime, _NOTE_SPACE);
	UpdateLongNotes_DRY(long_note_2, timer, _longStartTime_lane2_base, _longEndTime_lane2_base, deltaTime, _NOTE_SPACE * 2);
	UpdateLongNotes_DRY(long_note_3, timer, _longStartTime_lane3_base, _longEndTime_lane3_base, deltaTime, _NOTE_SPACE * 3);
}



void LongNote::RenderStartNotes() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	// 開始ノーツ
	DrawRoundRectAA(
		_longStart_x1 - _long_size / 100 * 1.25f / 1.5f,
		_long_y1 - _long_size / 100 * 0.15f / 1.5f,
		_longStart_x1 + _long_size / 200 * 1.25f / 1.5f,
		_long_y1 + _long_size / 200 * 0.15f / 1.5f,
		5.f, 0.2f, 4, _color, true, 1.5f
	);

	// ロングノーツの開始と終了のノーツをつなぐ線
	DrawLineAA(
		_longStart_x1 - _long_size / 100 * 1.25f / 1.5f,
		_long_y1 - _long_size / 100 * 0.15f / 1.5f,
		_longEnd_x1 * _long_startAndend_distanceRatio - _long_size / 100 * 1.25f,
		_long_y1 * _long_startAndend_distanceRatio - _long_size / 100 * 0.15f,
		_color,
		1.5f
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void LongNote::RenderEndNotes() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	// 終了ノーツ
	DrawRoundRectAA(
		_longEnd_x1 * _long_startAndend_distanceRatio - _long_size / 100 * 1.25f,
		_long_y1 * _long_startAndend_distanceRatio - _long_size / 100 * 0.15f,
		_longEnd_x1 * _long_startAndend_distanceRatio + _long_size / 200 * 1.25f,
		_long_y1 * _long_startAndend_distanceRatio + _long_size / 200 * 0.15f,
		5.f, 0.2f, 4, _color, true, 1.5f
	);

	DrawLineAA(
		_longStart_x1 + _long_size / 200 * 1.25f / 1.5f,
		_long_y1 + _long_size / 200 * 0.15f / 1.5f,
		_longEnd_x1 * _long_startAndend_distanceRatio + _long_size / 200 * 1.25f,
		_long_y1 * _long_startAndend_distanceRatio + _long_size / 200 * 0.15f,
		_color,
		1.5f
	);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}