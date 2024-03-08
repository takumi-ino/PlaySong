#pragma once
#include "../../../utility/tnlSequence.h"
#include "../../../utility/DxLib_Engine.h"


class NoteDataCsv
{
public:

	static NoteDataCsv& GetInstance() {

		static NoteDataCsv instance;
		return instance;
	}


	void SetNoteKeyValue();

	std::vector<std::vector<tnl::CsvCell>>& LoadNoteCsv(const std::string& key);

private:

	std::string GetNoteCsvMapKey(const std::string& key);

	std::unordered_map<std::string, std::string> _key_value;

	std::vector<std::vector<tnl::CsvCell>> _csvFile;
};