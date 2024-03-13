#include "NormalNote.h"
#include "../../../utility/DxLib_Engine.h"
#include "../../ScenePlaySong.h"
#include "../../JudgeZone/JudgeZone.h"


NormalNote::NormalNote(const std::string& csv_ref) : Notes(csv_ref) {

	normal_note_0.reserve(_normal_note_row_num_lane0_base);
	normal_note_1.reserve(_normal_note_row_num_lane1_base);
	normal_note_2.reserve(_normal_note_row_num_lane2_base);
	normal_note_3.reserve(_normal_note_row_num_lane3_base);

	for (int row = 0; row < _normal_note_row_num_lane0_base; ++row) {

		this->_x1 = _STARTPOS_X1;   // x左上
		this->_y1 = _STARTPOS_Y1;   // y左上 
		this->_velocity_x = -70.0f;     // x方向の速度
		this->_velocity_y = 120.0f;     // y方向の速度
		this->_size = 1.f;         // サイズ
		this->_color = GetColor(255, 105, 180);  // 色
		this->_isActive = true;      // アクティブ状態

		normal_note_0.emplace_back(

			this->_x1,
			this->_y1,
			this->_velocity_x,
			this->_velocity_y,
			this->_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane1_base; ++row) {

		this->_x1 = _STARTPOS_X1 + _NOTE_SPACE;
		this->_y1 = _STARTPOS_Y1;
		this->_velocity_x = -12.0f;
		this->_velocity_y = 90.0f;
		this->_size = 1.f;
		this->_color = GetColor(255, 105, 180);
		this->_isActive = true;

		normal_note_1.emplace_back(

			this->_x1,
			this->_y1,
			this->_velocity_x,
			this->_velocity_y,
			this->_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane2_base; ++row) {

		this->_x1 = _STARTPOS_X1 + (_NOTE_SPACE * 2);
		this->_y1 = _STARTPOS_Y1;
		this->_velocity_x = 21.0f;
		this->_velocity_y = 70.0f;
		this->_size = 1.f;
		this->_color = GetColor(255, 105, 180);
		this->_isActive = true;

		normal_note_2.emplace_back(

			this->_x1,
			this->_y1,
			this->_velocity_x,
			this->_velocity_y,
			this->_size,
			this->_color,
			this->_isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane3_base; ++row) {

		this->_x1 = _STARTPOS_X1 + (_NOTE_SPACE * 3);
		this->_y1 = _STARTPOS_Y1;
		this->_velocity_x = 50.0f;
		this->_velocity_y = 65.0f;
		this->_size = 1.f;
		this->_color = GetColor(255, 105, 180);
		this->_isActive = true;

		normal_note_3.emplace_back(

			this->_x1,
			this->_y1,
			this->_velocity_x,
			this->_velocity_y,
			this->_size,
			this->_color,
			this->_isActive
		);
	}
}


void NormalNote::UpdateNotes_DRY(std::vector<NormalNote>& normal_note, const double timer, std::vector<double> normalSpawnTime_eachLane, const float deltaTime, const int space) {

	for (auto it_lane = normal_note.begin(); it_lane != normal_note.end(); it_lane++) {

		// ノーツと当たり判定エリアの距離を取得
		int lane_row = std::distance(normal_note.begin(), it_lane);

		if ((*it_lane)._isActive) {  // アクティブなら

			//　開始時間
			if (timer > normalSpawnTime_eachLane[std::distance(normal_note.begin(), it_lane)]) {

				(*it_lane).RenderNotes();

				// ノーツの位置とサイズを更新
				(*it_lane)._x1 += (*it_lane)._velocity_x * 3 * deltaTime;    // x座標
				(*it_lane)._y1 += (*it_lane)._velocity_y * 3 * deltaTime;    // y座標
				(*it_lane)._size += (*it_lane)._velocity_y * 80 * deltaTime; // サイズ
			}

			//　画面外に出たら
			if ((*it_lane)._y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane, 1) != normal_note.end()) {

					auto next = std::next(it_lane, 1);

					// 次のノーツを元の位置に戻す
					(*next)._x1 = _STARTPOS_X1 + space;
					(*next)._y1 = _STARTPOS_Y1;
					(*next)._size = 1.0f;
				}

				//　現在のノーツは無効化
				(*it_lane)._isActive = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note, lane_row, timer, normalSpawnTime_eachLane);
		}
	}
}



void NormalNote::UpdateNotes(const double& timer, const float& deltaTime) {

	UpdateNotes_DRY(normal_note_0, timer, _normalSpawnTime_lane0_base, deltaTime);
	UpdateNotes_DRY(normal_note_1, timer, _normalSpawnTime_lane1_base, deltaTime, _NOTE_SPACE);
	UpdateNotes_DRY(normal_note_2, timer, _normalSpawnTime_lane2_base, deltaTime, _NOTE_SPACE * 2);
	UpdateNotes_DRY(normal_note_3, timer, _normalSpawnTime_lane3_base, deltaTime, _NOTE_SPACE * 3);
}



void NormalNote::RenderNotes() {

	DrawRoundRectAA
	(
		_x1 - _size / 100 * 1.25f,
		_y1 - _size / 100 * 0.15f,
		_x1 + _size / 200 * 1.25f,
		_y1 + _size / 200 * 0.15f,
		5.f, 0.2f, 4, _color, true, 1.5f
	);
}