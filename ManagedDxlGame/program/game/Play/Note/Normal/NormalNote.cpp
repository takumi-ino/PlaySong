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
		this->active = true;      // �A�N�e�B�u���

		normal_note_0.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->active
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane1_base; ++row) {

		this->x1 = STARTPOS_X1 + noteSpace;
		this->y1 = STARTPOS_Y1;
		this->x_vel = -12.0f;
		this->y_vel = 90.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->active = true;

		normal_note_1.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->active
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane2_base; ++row) {

		this->x1 = STARTPOS_X1 + (noteSpace * 2);
		this->y1 = STARTPOS_Y1;
		this->x_vel = 21.0f;
		this->y_vel = 70.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->active = true;

		normal_note_2.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->active
		);
	}

	for (int row = 0; row < _normal_note_row_num_lane3_base; ++row) {

		this->x1 = STARTPOS_X1 + (noteSpace * 3);
		this->y1 = STARTPOS_Y1;
		this->x_vel = 50.0f;
		this->y_vel = 65.0f;
		this->size = 1.f;
		this->color = GetColor(255, 105, 180);
		this->active = true;

		normal_note_3.emplace_back(

			this->x1,
			this->y1,
			this->x_vel,
			this->y_vel,
			this->size,
			this->color,
			this->active
		);
	}
}



void NormalNote::UpdateNotes(double _timer, float deltaTime) {


	for (auto it_lane0 = normal_note_0.begin(); it_lane0 != normal_note_0.end(); it_lane0++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(normal_note_0.begin(), it_lane0);

		if ((*it_lane0).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _normalSpawnTime_lane0_base[std::distance(normal_note_0.begin(), it_lane0)]) {

				(*it_lane0).RenderNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane0).x1 += (*it_lane0).x_vel * 3 * deltaTime;    // x���W
				(*it_lane0).y1 += (*it_lane0).y_vel * 3 * deltaTime;    // y���W
				(*it_lane0).size += (*it_lane0).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@��ʊO�ɏo����
			if ((*it_lane0).y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane0, 1) != normal_note_0.end()) {

					auto next = std::next(it_lane0, 1);

					// ���̃m�[�c�����̈ʒu�ɖ߂�
					(*next).x1 = STARTPOS_X1;
					(*next).y1 = STARTPOS_Y1;
					(*next).size = 1.0f;
				}

				//�@���݂̃m�[�c�͖�����
				(*it_lane0).active = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note_0, lane_row, _timer, _normalSpawnTime_lane0_base);
		}
	}

	for (auto it_lane1 = normal_note_1.begin(); it_lane1 != normal_note_1.end(); it_lane1++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(normal_note_1.begin(), it_lane1);

		if ((*it_lane1).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _normalSpawnTime_lane1_base[std::distance(normal_note_1.begin(), it_lane1)]) {

				(*it_lane1).RenderNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane1).x1 += (*it_lane1).x_vel * 3 * deltaTime;    // x���W
				(*it_lane1).y1 += (*it_lane1).y_vel * 3 * deltaTime;    // y���W
				(*it_lane1).size += (*it_lane1).y_vel * 80 * deltaTime; // �T�C�Y

			}

			if ((*it_lane1).y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane1, 1) != normal_note_1.end()) {

					auto next = std::next(it_lane1, 1);

					(*next).x1 = STARTPOS_X1 + noteSpace;
					(*next).y1 = STARTPOS_Y1;
					(*next).size = 1.0f;
				}

				(*it_lane1).active = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note_1, lane_row, _timer, _normalSpawnTime_lane1_base);
		}
	}

	for (auto it_lane2 = normal_note_2.begin(); it_lane2 != normal_note_2.end(); it_lane2++) {


		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(normal_note_2.begin(), it_lane2);

		if ((*it_lane2).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _normalSpawnTime_lane2_base[std::distance(normal_note_2.begin(), it_lane2)]) {

				(*it_lane2).RenderNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane2).x1 += (*it_lane2).x_vel * 3 * deltaTime;    // x���W
				(*it_lane2).y1 += (*it_lane2).y_vel * 3 * deltaTime;    // y���W
				(*it_lane2).size += (*it_lane2).y_vel * 80 * deltaTime; // �T�C�Y
			}


			if ((*it_lane2).y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane2, 1) != normal_note_2.end()) {

					auto next = std::next(it_lane2, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					(*next).x1 = STARTPOS_X1 + (noteSpace * 2);
					(*next).y1 = STARTPOS_Y1;
					(*next).size = 1.0f;
				}

				(*it_lane2).active = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note_2, lane_row, _timer, _normalSpawnTime_lane2_base);
		}
	}

	for (auto it_lane3 = normal_note_3.begin(); it_lane3 != normal_note_3.end(); it_lane3++) {


		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(normal_note_3.begin(), it_lane3);

		if ((*it_lane3).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _normalSpawnTime_lane3_base[std::distance(normal_note_3.begin(), it_lane3)]) {

				(*it_lane3).RenderNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane3).x1 += it_lane3->x_vel * 3 * deltaTime;    // x���W
				(*it_lane3).y1 += it_lane3->y_vel * 3 * deltaTime;    // y���W
				(*it_lane3).size += it_lane3->y_vel * 80 * deltaTime; // �T�C�Y

			}

			if ((*it_lane3).y1 > DXE_WINDOW_HEIGHT) {

				if (std::next(it_lane3, 1) != normal_note_3.end()) {

					auto next = std::next(it_lane3, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					(*next).x1 = STARTPOS_X1 + (noteSpace * 3);
					(*next).y1 = STARTPOS_Y1;
					(*next).size = 1.0f;
				}

				(*it_lane3).active = false;
			}

			judgeZone->JudgeNoteHit_ByInputKey(normal_note_3, lane_row, _timer, _normalSpawnTime_lane3_base);
		}
	}
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