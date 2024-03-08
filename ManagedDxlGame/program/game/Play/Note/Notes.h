#pragma once
#include "../../utility/DxLib_Engine.h"
#include "../../utility/tnlSequence.h"


class Notes {

public:

	Notes() {}
	Notes(const std::string& csv_key);

	Notes(
		float x1,
		float y1,
		float x_vel,
		float y_vel,
		float size,
		int color,
		bool isActive
	);

	Notes(
		float x1_long_start,
		float x1_long_end,
		float y1_long,
		float x_vel,
		float y_vel,
		float size_long,
		int color,
		bool isActive
	);

	virtual void UpdateNotes(const double& timer, const float& deltaTime) {}

public:

	bool  isActive{};

protected:

	// �������p�萔------------------------------------------------------------
	const int   NOTE_COL_NUM = 4;
	const int   noteSpace = 50;
	const float   STARTPOS_X1 = 565.f;     // �m�[�c[0] ����X
	const float   STARTPOS_Y1 = 100.f;     // �m�[�c[0] ����Y
	const float STARTPOS_X2 = 0.1f;    // �m�[�c[0] �E��X
	const float STARTPOS_Y2 = 0.01f;   // �m�[�c[0] �E��Y

	// �����O�m�[�c------------------------------------------------------------
	float x1_long_start{};
	float x1_long_end{};
	float y1_long{};
	float size_long = 2.0f; // ���̒��� (�����O�m�[�c�̏I���ʒu�Ŏg�p�j

	std::vector<double> _longStartTime_lane0_base{};
	std::vector<double> _longStartTime_lane1_base{};
	std::vector<double> _longStartTime_lane2_base{};
	std::vector<double> _longStartTime_lane3_base{};

	std::vector<double> _longEndTime_lane0_base{};
	std::vector<double> _longEndTime_lane1_base{};
	std::vector<double> _longEndTime_lane2_base{};
	std::vector<double> _longEndTime_lane3_base{};

	int         _long_note_row_num_lane0_base{};
	int         _long_note_row_num_lane1_base{};
	int         _long_note_row_num_lane2_base{};
	int         _long_note_row_num_lane3_base{};

	// �m�[�}���m�[�c------------------------------------------------------------
	std::vector<double> _normalSpawnTime_lane0_base{};
	std::vector<double> _normalSpawnTime_lane1_base{};
	std::vector<double> _normalSpawnTime_lane2_base{};
	std::vector<double> _normalSpawnTime_lane3_base{};

	int         _normal_note_row_num_lane0_base{};
	int         _normal_note_row_num_lane1_base{};
	int         _normal_note_row_num_lane2_base{};
	int         _normal_note_row_num_lane3_base{};

	// �m�[�}���E�����O����----------------------------------------
	int   color{};

	float x1{};
	float y1{};
	float x_vel{};   // �������ɓ������x
	float y_vel{};   // �c�����ɓ������x
	float size{};	 // �T�C�Y
	float speed{};   // �X�s�[�h

	std::vector<std::string> NoteType{};      // �m�[�c�^�C�v
	std::vector<int>         lane{};          // �����ʒu�i���[���j

private:

	// 1�b�Ԃɉ��s�N�Z���ړ����邩
	double moveSpeed_pixel = 600.0;
	// �����ʒu���画��ʒu�܂ł̋��� �iNotes�N���X��JudgeZone�N���X�Q��
	double moveDistance = 500.0;
	//����G���A�ɓ��B���鎞�����������o�������Ȃ��Ă͂Ȃ�Ȃ����ߎ��Ԃ�����
	double moveToJudgeZoneSecond = moveDistance / moveSpeed_pixel;

	std::vector<float>       justSpawnTime_ms{};  // �����^�C�~���O
};