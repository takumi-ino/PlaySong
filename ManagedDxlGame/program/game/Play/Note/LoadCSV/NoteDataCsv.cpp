#include "NoteDataCsv.h"
#include <stdexcept>


void NoteDataCsv::SetNoteKeyValue() {

	_key_value.insert({ "�����ȑ�9��", "csv/note_symphonyNo9.csv" });
	_key_value.insert({ "BadApple!!", "csv/note_badApple.csv" });
	_key_value.insert({ "���\���o�[�Y", "csv/note_two-facedLovers.csv" });
	_key_value.insert({ "�c���ȓV�g�̃e�[�[", "csv/note_cruel_angel's _thesis.csv" });
}


std::string NoteDataCsv::GetNoteCsvMapKey(const std::string& key) {

	if (!_key_value.count(key) > 0) return "ERROR";

	return _key_value[key];
}



std::vector<std::vector<tnl::CsvCell>>& NoteDataCsv::LoadNoteCsv(const std::string& key) {

	try {

		std::string value = GetNoteCsvMapKey(key);

		if (value == "ERROR") 	throw "Please check Key again";

		_csvFile = tnl::LoadCsv(value.c_str());
	}
	catch (const char* c) {

		throw std::runtime_error(c);
	}

	return _csvFile;
}