#pragma once


class NoteDataCsv
{
public:

	static NoteDataCsv& GetInstance() {

		static NoteDataCsv instance;
		return instance;
	}

	// unordered_map �̃L�[�ƒl�������ݒ�
	void InitNoteKeyValue();

	// CSV�i�m�[�c�f�[�^�j���[�h
	std::vector<std::vector<tnl::CsvCell>>& LoadNoteCsv(const std::string& key);

private:

	// �I���ȂɑΉ�����CSV�� string�^�̃L�[��Ԃ�
	std::string GetNoteCsvMapKey(const std::string& key);

	std::vector<std::vector<tnl::CsvCell>>       _csvFile;
	std::unordered_map<std::string, std::string> _keyValue;
};