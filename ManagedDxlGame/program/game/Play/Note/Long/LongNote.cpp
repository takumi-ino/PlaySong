#include "LongNote.h"
#include "../../ScenePlaySong.h"
#include "../../JudgeZone/JudgeZone.h"




LongNote::LongNote(const std::string& csv_ref) : Notes(csv_ref) {

	long_note_0.reserve(_long_note_row_num_lane0_base);
	long_note_1.reserve(_long_note_row_num_lane1_base);
	long_note_2.reserve(_long_note_row_num_lane2_base);
	long_note_3.reserve(_long_note_row_num_lane3_base);


	for (int row = 0; row < _long_note_row_num_lane0_base; ++row) {

		this->x1_long_start = STARTPOS_X1;   // x����
		this->x1_long_end = STARTPOS_X1;   // x����
		this->y1_long = STARTPOS_Y1;   // y���� 

		this->x_vel = -70.0f;     // x�����̑��x
		this->y_vel = 120.0f;     // y�����̑��x
		this->size_long = 1.f;         // �T�C�Y
		this->color = GetColor(147, 112, 219);  // �F
		this->active = true;      // �A�N�e�B�u���


		long_note_0.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->active
		);
	}

	for (int row = 0; row < _long_note_row_num_lane1_base; ++row) {

		this->x1_long_start = STARTPOS_X1 + noteSpace;
		this->x1_long_end = STARTPOS_X1 + noteSpace;
		this->y1_long = STARTPOS_Y1;

		this->x_vel = -12.0f;
		this->y_vel = 90.0f;
		this->size_long = 1.f;
		this->color = GetColor(147, 112, 219);
		this->active = true;

		long_note_1.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->active
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
		this->active = true;

		long_note_2.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->active
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
		this->active = true;


		long_note_3.emplace_back(

			this->x1_long_start,
			this->x1_long_end,
			this->y1_long,

			this->x_vel,
			this->y_vel,
			this->size_long,
			this->color,
			this->active
		);
	}
}



void LongNote::UpdateNotes(double _timer, float deltaTime) {


	for (auto it_lane0 = long_note_0.begin(); it_lane0 != long_note_0.end(); it_lane0++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(long_note_0.begin(), it_lane0);

		if ((*it_lane0).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _longStartTime_lane0_base[std::distance(long_note_0.begin(), it_lane0)]) {

				(*it_lane0).RenderStartNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane0).x1_long_start += (*it_lane0).x_vel * 3 * deltaTime;    // x���W
				(*it_lane0).y1_long += (*it_lane0).y_vel * 3 * deltaTime;    // y���W
				(*it_lane0).size_long += (*it_lane0).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@�I������
			if (_timer > _longEndTime_lane0_base[std::distance(long_note_0.begin(), it_lane0)]) {

				(*it_lane0).RenderEndNotes();

				if (std::next(it_lane0, 1) != long_note_0.end()) {

					auto next = std::next(it_lane0, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					(*next).x1_long_start = STARTPOS_X1;
					(*next).y1_long = STARTPOS_Y1;
					(*next).size_long = 1.0f;
				}

				(*it_lane0).active = false;
			}
			else {

				(*it_lane0).x1_long_end += (*it_lane0).x_vel * 3 * deltaTime;    // x���W
				(*it_lane0).y1_long += (*it_lane0).y_vel * 3 * deltaTime;    // y���W
				(*it_lane0).size_long += (*it_lane0).y_vel * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(long_note_0, lane_row, _timer, _longStartTime_lane0_base);
			judgeZone->JudgeNoteHit_ByInputKey(long_note_0, lane_row, _timer, _longEndTime_lane0_base);
		}
	}

	for (auto it_lane1 = long_note_1.begin(); it_lane1 != long_note_1.end(); it_lane1++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(long_note_1.begin(), it_lane1);

		if ((*it_lane1).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _longStartTime_lane1_base[std::distance(long_note_1.begin(), it_lane1)]) {

				(*it_lane1).RenderStartNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane1).x1_long_start += (*it_lane1).x_vel * 3 * deltaTime;    // x���W
				(*it_lane1).y1_long += (*it_lane1).y_vel * 3 * deltaTime;    // y���W
				(*it_lane1).size_long += (*it_lane1).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@�I������
			if (_timer > _longEndTime_lane1_base[std::distance(long_note_1.begin(), it_lane1)]) {

				(*it_lane1).RenderEndNotes();

				if (std::next(it_lane1, 1) != long_note_1.end()) {

					auto next = std::next(it_lane1, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					(*next).x1_long_start = STARTPOS_X1 + noteSpace;
					(*next).y1_long = STARTPOS_Y1;
					(*next).size_long = 1.0f;
				}

				(*it_lane1).active = false;
			}
			else {

				(*it_lane1).x1_long_end += (*it_lane1).x_vel * 3 * deltaTime;    // x���W
				(*it_lane1).y1_long += (*it_lane1).y_vel * 3 * deltaTime;    // y���W
				(*it_lane1).size_long += (*it_lane1).y_vel * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(long_note_1, lane_row, _timer, _longStartTime_lane1_base);
			judgeZone->JudgeNoteHit_ByInputKey(long_note_1, lane_row, _timer, _longEndTime_lane1_base);
		}
	}

	for (auto it_lane2 = long_note_2.begin(); it_lane2 != long_note_2.end(); it_lane2++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(long_note_2.begin(), it_lane2);

		if ((*it_lane2).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _longStartTime_lane2_base[std::distance(long_note_2.begin(), it_lane2)]) {

				(*it_lane2).RenderStartNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane2).x1_long_start += (*it_lane2).x_vel * 3 * deltaTime;    // x���W
				(*it_lane2).y1_long += (*it_lane2).y_vel * 3 * deltaTime;    // y���W
				(*it_lane2).size_long += (*it_lane2).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@�I������
			if (_timer > _longEndTime_lane2_base[std::distance(long_note_2.begin(), it_lane2)]) {

				(*it_lane2).RenderEndNotes();


				if (std::next(it_lane2, 1) != long_note_2.end()) {

					auto next = std::next(it_lane2, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					(*next).x1_long_start = STARTPOS_X1 + (noteSpace * 2);
					(*next).y1_long = STARTPOS_Y1;
					(*next).size_long = 1.0f;
				}

				(*it_lane2).active = false;
			}
			else {

				(*it_lane2).x1_long_end += (*it_lane2).x_vel * 3 * deltaTime;    // x���W
				(*it_lane2).y1_long += (*it_lane2).y_vel * 3 * deltaTime;    // y���W
				(*it_lane2).size_long += (*it_lane2).y_vel * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(long_note_2, lane_row, _timer, _longStartTime_lane2_base);
			judgeZone->JudgeNoteHit_ByInputKey(long_note_2, lane_row, _timer, _longEndTime_lane2_base);
		}
	}

	for (auto it_lane3 = long_note_3.begin(); it_lane3 != long_note_3.end(); it_lane3++) {

		// �m�[�c�Ɠ����蔻��G���A�̋������擾
		int lane_row = std::distance(long_note_3.begin(), it_lane3);

		if ((*it_lane3).active) {  // �A�N�e�B�u�Ȃ�

			//�@�J�n����
			if (_timer > _longStartTime_lane3_base[std::distance(long_note_3.begin(), it_lane3)]) {

				(*it_lane3).RenderStartNotes();

				// �m�[�c�̈ʒu�ƃT�C�Y���X�V
				(*it_lane3).x1_long_start += (*it_lane3).x_vel * 3 * deltaTime;    // x���W
				(*it_lane3).y1_long += (*it_lane3).y_vel * 3 * deltaTime;    // y���W
				(*it_lane3).size_long += (*it_lane3).y_vel * 80 * deltaTime; // �T�C�Y
			}

			//�@�I������
			if (_timer > _longEndTime_lane3_base[std::distance(long_note_3.begin(), it_lane3)]) {

				(*it_lane3).RenderEndNotes();

				if (std::next(it_lane3, 1) != long_note_3.end()) {

					auto next = std::next(it_lane3, 1);

					// �����ɂȂ����m�[�c�����̈ʒu�ɖ߂�
					next->x1_long_start = STARTPOS_X1 + (noteSpace * 3);
					next->y1_long = STARTPOS_Y1;
					next->size_long = 1.0f;
				}

				(*it_lane3).active = false;
			}
			else {

				(*it_lane3).x1_long_end += (*it_lane3).x_vel * 3 * deltaTime;    // x���W
				(*it_lane3).y1_long += (*it_lane3).y_vel * 3 * deltaTime;    // y���W
				(*it_lane3).size_long += (*it_lane3).y_vel * 80 * deltaTime;
			}

			judgeZone->JudgeNoteHit_ByInputKey(long_note_3, lane_row, _timer, _longStartTime_lane3_base);
			judgeZone->JudgeNoteHit_ByInputKey(long_note_3, lane_row, _timer, _longStartTime_lane3_base);
		}
	}
}



void LongNote::RenderStartNotes() {


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	// �J�n�m�[�c
	DrawRoundRectAA(
		x1_long_start - size_long / 100 * 1.25f / 1.5f,
		y1_long - size_long / 100 * 0.15f / 1.5f,
		x1_long_start + size_long / 200 * 1.25f / 1.5f,
		y1_long + size_long / 200 * 0.15f / 1.5f,
		5.f, 0.2f, 4, color, true, 1.5f);


	// �����O�m�[�c�̊J�n�ƏI���̃m�[�c���Ȃ���
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

	// �I���m�[�c
	DrawRoundRectAA(
		x1_long_end * long_start_end_distanceRatio - size_long / 100 * 1.25f,
		y1_long * long_start_end_distanceRatio - size_long / 100 * 0.15f,
		x1_long_end * long_start_end_distanceRatio + size_long / 200 * 1.25f,
		y1_long * long_start_end_distanceRatio + size_long / 200 * 0.15f,
		5.f, 0.2f, 4, color, true, 1.5f);


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