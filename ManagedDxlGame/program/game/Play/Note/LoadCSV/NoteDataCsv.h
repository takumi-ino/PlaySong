#pragma once


class NoteDataCsv
{
public:

	static NoteDataCsv& GetInstance() {

		static NoteDataCsv instance;
		return instance;
	}

	// unordered_map のキーと値を初期設定
	void InitNoteKeyValue();

	// CSV（ノーツデータ）ロード
	std::vector<std::vector<tnl::CsvCell>>& LoadNoteCsv(const std::string& key);

private:

	// 選択曲に対応したCSVの string型のキーを返す
	std::string GetNoteCsvMapKey(const std::string& key);

	std::vector<std::vector<tnl::CsvCell>>       _csvFile;
	std::unordered_map<std::string, std::string> _keyValue;
};