#pragma once
#include "../Manager/Scene/SceneBase.h"


class Result : public Scenes 
{
public:

	Result(){}
	Result(
		int score, 
		int maxCombo,
		int Perfect,
		int Great,
		int Good,
		int Poor, 
		int Miss, 
		const char* songName,
		const char* songLevel
	);

	void Render() override;
	void Update(float deltaTime) override;

private:

	const char* GetRank(int resultScore);  // �X�R�A�ɉ����������N��Ԃ�

	void LoadMyPastHighScore();            // �ߋ��̃n�C�X�R�A�����[�h

	void CheckIfNeed_OverwriteHighScore(); // �n�C�X�R�A��K�v�ɉ����čX�V

	void DrawResult(                       // �e��e�L�X�g�ɉ����ĕ`��
		const float x, 
		const float y,
		const int fontSize, 
		const std::string text,
		const int value = -1
    );

private:

	// �����X�R�A----------------------------------------
	int         _score{};
	int         _highScore{};
	int         _maxCombo{};

	// �e��X�R�A----------------------------------------
	int         _perfect{};
	int         _great{};
	int         _good{};
	int         _poor{};
	int         _miss{};

	// ----------------------------------------
	char*       _songName{};    // �Ȗ�
	char*       _songLevel{};   // ��Փx
	const char* _rank{};        // �����N

	// ----------------------------------------
	bool        _isResultScene = true;
};