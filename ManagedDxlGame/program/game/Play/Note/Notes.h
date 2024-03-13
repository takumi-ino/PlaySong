#pragma once
#include "../../utility/DxLib_Engine.h"


class Notes {

public:

	Notes() {}
	Notes(const std::string& csv_key);

	Notes(
		float _x1,
		float _y1,
		float _velocity_x,
		float _velocity_y,
		float size,
		int _color,
		bool _isActive
	);

	Notes(
		float _longStart_x1,
		float _longEnd_x1,
		float _long_y1,
		float _velocity_x,
		float _velocity_y,
		float _long_size,
		int _color,
		bool _isActive
	);

	virtual void UpdateNotes(
		const double& timer, const float& deltaTime) 
	{}

public:

	bool  _isActive{};

protected:

	// �������p�萔------------------------------------------------------------
	const int   _NOTE_COL_NUM = 4;
	const int   _NOTE_SPACE = 50;
	const float _STARTPOS_X1 = 565.f;   // �m�[�c[0] ����X
	const float _STARTPOS_Y1 = 100.f;   // �m�[�c[0] ����Y
	const float _STARTPOS_X2 = 0.1f;    // �m�[�c[0] �E��X
	const float _STARTPOS_Y2 = 0.01f;   // �m�[�c[0] �E��Y

	// �����O�m�[�c------------------------------------------------------------
	float _longStart_x1{};
	float _longEnd_x1{};
	float _long_y1{};
	float _long_size = 2.0f; // ���̒��� (�����O�m�[�c�̏I���ʒu�Ŏg�p�j

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
	int   _color{};

	float _x1{};
	float _y1{};
	float _velocity_x{};   // �������ɓ������x
	float _velocity_y{};   // �c�����ɓ������x
	float _size{};   	   // �T�C�Y

	std::vector<std::string> _noteType{};      // �m�[�c�^�C�v
	std::vector<int>         _lane{};          // �����ʒu�i���[���j

private:

	// 1�b�Ԃɉ��s�N�Z���ړ����邩
	double _moveSpeed_perPixel = 600.0;
	// �����ʒu���画��ʒu�܂ł̋��� �iNotes�N���X��JudgeZone�N���X�Q��
	double _noteMoveWayDistance = 500.0;

	// ����G���A�ɓ��B����܂ł̎���
	//����G���A�ɓ��B���鎞�����������o�������Ȃ��Ă͂Ȃ�Ȃ����߁A���Ԃ�����
	double _reachToJudgeZone_perfectSecond = _noteMoveWayDistance / _moveSpeed_perPixel;

	std::vector<float> _justSpawnNoteTime_ms{};  // �����^�C�~���O
};