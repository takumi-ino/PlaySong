#include "../Timer/Timer.h"
#include "LoadCSV/NoteDataCsv.h"
#include "Notes.h"


Notes::Notes(const std::string& csv_key) {
		
	decltype(auto) csv = NoteDataCsv::GetInstance().LoadNoteCsv(csv_key);

	for (int i = 0; i < csv.size(); ++i) {                   // CSV縦列

		justSpawnTime_ms.emplace_back(csv[i][0].getFloat()); // floatに変換
		lane.emplace_back(csv[i][1].getInt());               // Intに変換
		NoteType.emplace_back(csv[i][2].getString());        // std::stringに変換

		// 生成位置から判定エリアまでの移動時間差分を差し引く
		justSpawnTime_ms[i] -= static_cast<float>(moveToJudgeZoneSecond);

		switch (lane[i]) // レーンが一致する各配列に末尾から要素を追加
		{

		case 0:

			if (NoteType[i] == "NORMAL") {

				_normal_note_row_num_lane0_base++;
				_normalSpawnTime_lane0_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_START") {

				_long_note_row_num_lane0_base++;
				_longStartTime_lane0_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_END") {

				_longEndTime_lane0_base.emplace_back(justSpawnTime_ms[i]);
			}
			break;
		case 1:

			if (NoteType[i] == "NORMAL") {

				_normal_note_row_num_lane1_base++;
				_normalSpawnTime_lane1_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_START") {

				_long_note_row_num_lane1_base++;
				_longStartTime_lane1_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_END") {

				_longEndTime_lane1_base.emplace_back(justSpawnTime_ms[i]);
			}
			break;
		case 2:

			if (NoteType[i] == "NORMAL") {

				_normal_note_row_num_lane2_base++;
				_normalSpawnTime_lane2_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_START") {

				_long_note_row_num_lane2_base++;
				_longStartTime_lane2_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_END") {

				_longEndTime_lane2_base.emplace_back(justSpawnTime_ms[i]);
			}
			break;
		case 3:

			if (NoteType[i] == "NORMAL") {

				_normal_note_row_num_lane3_base++;
				_normalSpawnTime_lane3_base.emplace_back(justSpawnTime_ms[i]);

			}
			else if (NoteType[i] == "LONG_START") {

				_long_note_row_num_lane3_base++;
				_longStartTime_lane3_base.emplace_back(justSpawnTime_ms[i]);
			}
			else if (NoteType[i] == "LONG_END") {

				_longEndTime_lane3_base.emplace_back(justSpawnTime_ms[i]);
			}
			break;
		}
	}
}


Notes::Notes(float x1, float y1, float x_vel, float y_vel, float size, int color, bool isActive) {

	this->x1 = x1;
	this->y1 = y1;
	this->x_vel = x_vel;
	this->y_vel = y_vel;
	this->size = size;
	this->color = color;
	this->isActive = isActive;
}


Notes::Notes(float x1_long_start, float x1_long_end, float y1_long, float x_vel, float y_vel, float size_long, int color, bool isActive) {

	this->x1_long_start = x1_long_start;
	this->x1_long_end = x1_long_end;
	this->y1_long = y1_long;
	this->x_vel = x_vel;
	this->y_vel = y_vel;
	this->size_long = size_long;
	this->color = color;
	this->isActive = isActive;
}