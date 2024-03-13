#include "Notes.h"
#include "LoadCSV/NoteDataCsv.h"


Notes::Notes(const std::string& csv_key) {
		
	decltype(auto) csv = NoteDataCsv::GetInstance().LoadNoteCsv(csv_key);

	for (int i = 0; i < csv.size(); ++i) {                   // CSV縦列

		_justSpawnNoteTime_ms.emplace_back(csv[i][0].getFloat()); // floatに変換
		_lane.emplace_back(csv[i][1].getInt());               // Intに変換
		_noteType.emplace_back(csv[i][2].getString());        // std::stringに変換

		// 生成位置から判定エリアまでの移動時間差分を差し引く
		_justSpawnNoteTime_ms[i] -= static_cast<float>(_reachToJudgeZone_perfectSecond);

		switch (_lane[i]) // レーンが一致する各配列に末尾から要素を追加
		{

		case 0:

			if (_noteType[i] == "NORMAL") {

				_normal_note_row_num_lane0_base++;
				_normalSpawnTime_lane0_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_START") {

				_long_note_row_num_lane0_base++;
				_longStartTime_lane0_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_END") {

				_longEndTime_lane0_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			break;
		case 1:

			if (_noteType[i] == "NORMAL") {

				_normal_note_row_num_lane1_base++;
				_normalSpawnTime_lane1_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_START") {

				_long_note_row_num_lane1_base++;
				_longStartTime_lane1_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_END") {

				_longEndTime_lane1_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			break;
		case 2:

			if (_noteType[i] == "NORMAL") {

				_normal_note_row_num_lane2_base++;
				_normalSpawnTime_lane2_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_START") {

				_long_note_row_num_lane2_base++;
				_longStartTime_lane2_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_END") {

				_longEndTime_lane2_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			break;
		case 3:

			if (_noteType[i] == "NORMAL") {

				_normal_note_row_num_lane3_base++;
				_normalSpawnTime_lane3_base.emplace_back(_justSpawnNoteTime_ms[i]);

			}
			else if (_noteType[i] == "LONG_START") {

				_long_note_row_num_lane3_base++;
				_longStartTime_lane3_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			else if (_noteType[i] == "LONG_END") {

				_longEndTime_lane3_base.emplace_back(_justSpawnNoteTime_ms[i]);
			}
			break;
		}
	}
}


Notes::Notes(float _x1, float _y1, float _velocity_x, float _velocity_y, float size, int _color, bool _isActive) {

	this->_x1 = _x1;
	this->_y1 = _y1;
	this->_velocity_x = _velocity_x;
	this->_velocity_y = _velocity_y;
	this->_size = size;
	this->_color = _color;
	this->_isActive = _isActive;
}


Notes::Notes(float _longStart_x1, float _longEnd_x1, float _long_y1, float _velocity_x, float _velocity_y, float _long_size, int _color, bool _isActive) {

	this->_longStart_x1 = _longStart_x1;
	this->_longEnd_x1 = _longEnd_x1;
	this->_long_y1 = _long_y1;
	this->_velocity_x = _velocity_x;
	this->_velocity_y = _velocity_y;
	this->_long_size = _long_size;
	this->_color = _color;
	this->_isActive = _isActive;
}