#include "../../../utility/DxLib_Engine.h"
#include "NoteDataCsv.h"
#include <stdexcept>


void NoteDataCsv::InitNoteKeyValue() {

	_keyValue.insert({ "�����ȑ�9��", "csv/note_symphonyNo9.csv" });
	_keyValue.insert({ "BadApple!!", "csv/note_badApple.csv" });
	_keyValue.insert({ "���\���o�[�Y", "csv/note_two-facedLovers.csv" });
	_keyValue.insert({ "�c���ȓV�g�̃e�[�[", "csv/note_cruel_angel's _thesis.csv" });
}


std::string NoteDataCsv::GetNoteCsvMapKey(const std::string& key) {

	if (!_keyValue.count(key) > 0)
		return "ERROR";

	return _keyValue[key];
}


std::vector<std::vector<tnl::CsvCell>>& NoteDataCsv::LoadNoteCsv(const std::string& key) {

	try {

		std::string value = GetNoteCsvMapKey(key);

		if (value == "ERROR") 
			throw "Please check Key again";

		_csvFile = tnl::LoadCsv(value.c_str());
	}
	catch (const char* c) {

		throw std::runtime_error(c);
	}

	return _csvFile;
}