#include "NormalNote.h"
#include "../Notes.h"
#include "../../JudgeZone/JudgeZone.h"
#include "../../ScenePlaySong.h"


NormalNote::NormalNote(const std::string& csv_ref) : Notes(csv_ref) {

	normal_note_0.reserve(_normal_note_row_num_lane0_base);
	normal_note_1.reserve(_normal_note_row_num_lane1_base);
	normal_note_2.reserve(_normal_note_row_num_lane2_base);
	normal_note_3.reserve(_normal_note_row_num_lane3_base);

	for (int row = 0; row < _normal_note_row_num_lane0_base; ++row) {

		this->x1 = STARTPOS_X1;   // x����
		this->y1 = STARTPOS_Y1;   // y���� 
		this->x_vel = -70.0f;     // x�����̑��x
		this->y_vel = 120.0f;     // y�����̑��x
		this->size = 1.f;         // �T�C�Y
		this->color = GetColor(255, 105, 180);  // �F
		this->isActive = true;      // �A�N�e�B�u���

		normal_note_0.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane1_base; ++row) {

		this->x1 = STARTPOS_X1 + noteSpace;
		this->y1 = STARTPOS_Y1;
		this->x_vel = -12.0f;
		this->y_vel = 90.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->isActive = true;

		normal_note_1.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane2_base; ++row) {

		this->x1 = STARTPOS_X1 + (noteSpace * 2);
		this->y1 = STARTPOS_Y1;
		this->x_vel = 21.0f;
		this->y_vel = 70.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->isActive = true;

		normal_note_2.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->isActive
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane3_base; ++row) {

		this->x1 = STARTPOS_X1 + (noteSpace * 3);
		this->y1 = STARTPOS_Y1;
		this->x_vel = 50.0f;
		this->y_vel = 65.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->isActive = true;

		normal_note_3.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->isActive
		);
	}
}


void NormalNote::UpdateNotes_DRY(std::vector<NormalNote>& normal_note, const double timer, std::vector<double> normalSpawnTime_eachLane, const float deltaTime, const int space) {

	for (auto it_lane = normal_note.begin(); it_lane != normal_note.end(); it_lane++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(normal_note.begin(), it_lane);

		if ((*it_lane).isActive) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (timer > normalSpawnTime_eachLane[std::distance(normal_note.begin(), it_lane)]) {

				(*it_lane).RenderNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane).x1 += (*it_lane).x_vel * 3 * deltaTime;    // x���W
				(*it_lane).y1 += (*it_lane).y_vel * 3 * deltaTime;    // y���W
				(*it_lane).size += (*it_lane).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@��ʊO�ɏo����
			if ((*it_lane).y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane, 1) != normal_note.end()) {

					auto next = std::next(it_lane, 1);

					// ���̃m�[�c�����̈ʒu�ɖ߂�
					(*next).x1 = STARTPOS_X1 + space;
					(*next).y1 = STARTPOS_Y1;
					(*next).size = 1.0f;
				}

				//�@���݂̃m�[�c�͖�����
				(*it_lane).isActive = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note, lane_row, timer, normalSpawnTime_eachLane);
		}
	}
}



void NormalNote::UpdateNotes(const double& timer, const float& deltaTime) {

	UpdateNotes_DRY(normal_note_0, timer, _normalSpawnTime_lane0_base, deltaTime);
	UpdateNotes_DRY(normal_note_1, timer, _normalSpawnTime_lane1_base, deltaTime, noteSpace);
	UpdateNotes_DRY(normal_note_2, timer, _normalSpawnTime_lane2_base, deltaTime, noteSpace * 2);
	UpdateNotes_DRY(normal_note_3, timer, _normalSpawnTime_lane3_base, deltaTime, noteSpace * 3);
}



void NormalNote::RenderNotes() {

	DrawRoundRectAA
	(
		x1 - size / 100 * 1.25f,
		y1 - size / 100 * 0.15f,
		x1 + size / 200 * 1.25f,
		y1 + size / 200 * 0.15f,
		5.f, 0.2f, 4, color, true, 1.5f
	);
}