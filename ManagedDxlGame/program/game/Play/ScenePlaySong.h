#pragma once
#include "../Manager/Scene/SceneBase.h"


class Scenes;
class NormalNote;
class LongNote;
class Notes;
class JudgeZone;
class ScoreCombo;
class ScoreCombo;
class PauseOption;
class Timer;


extern JudgeZone judgeZone[4];


class PlaySong : public Scenes
{
public:

	PlaySong() {}
	PlaySong(const char* title, const char* level, const int _songIndex, const int levelIdx);

	void Destroy() override;

	void Render() override;
	void Update(float delta_time) override;

private:

	// �u�t�z�z���C�u�������BSequence�N���X�� �^�C�}�[�֐����g�p����
	tnl::Sequence<PlaySong> sequence = tnl::Sequence<PlaySong>(this, &PlaySong::SeqIdle);
	bool SeqIdle(float delta_time) { return true; };
			
	// �Q�b�^�[----------------------------------------------------------
	float GetDeltaTime() const { return _deltaTime; }

	// ���[�h----------------------------------------------------------
	void LoadImages();
	void LoadSelectedSongNotes(); 	// �I�������Ȃ̃m�[�c�����[�h

	// �e��@�\--------------------------------------------------------
	void SetSongBPM();
	void FadeScreenByAlpha();         // �v���C�J�n�̃t�F�[�h���o
	void ShowSongInfo_BeforeStart();  // �v���C�J�n�O�ɋȖ���\��
	void CheckIfSongEndByTimer();     // �ȏI���܂Ŏ��Ԍv��
	void PlaySongUntilSongEnd();      // �ȏI���܂ŋȂ𗬂�
	void BackToSelectSongMenu();      // �ȑI���֖߂�
	void RetryGame();                 // �Q�[������蒼��
	void MoveToResult();              // ���U���g�֔��
	void ActivatePauseMenu();         // �|�[�Y���j���[���J��
	void RevertAllChanges();          // �v���C�V�[�����痣���Ƃ��ɑS�Ă̕ύX�����Z�b�g����

	// �`��------------------------------------------------------------
	void RenderMetaData(); // �I���ȁA�I���Փx

public:

	static Timer* _timer;

private:

	Notes*       _normal_downcastRef = nullptr;
	Notes*       _long_downcastRef = nullptr;
	NormalNote*  _normal_noteRef = nullptr;
	LongNote*    _long_noteRef = nullptr;

	ScoreCombo*  _scoreCombo = nullptr;
	PauseOption* _pauseOption = nullptr;

public:

	static constexpr int _COVERALBUM_NUM = 4; // �J�o�[�A���o����
	static int           _currentState;       // ���j���[��ʂ̃X�e�[�g���
	static int           _songIndex;          // �Ȕԍ�
	static bool          _isPaused;
	static bool          _moveToSongSelect;
	static bool          _moveToResult;
	static bool          _isRetryGame;

private:

	int   _songBpm{};              // BPM
	int   _levelIndex{};

	float _songDuration{};         // �Ȃ̒���
	float _elapsed{};              // �o�ߎ���
	float _progress_ratio{};       // �t�F�[�h�̕ω���
	float brightnessAlpha{};      // ���x
	float _deltaTime{};            // ��������deltaTime���擾�ł��Ȃ��P�[�X�Ŏg�p����

	bool  _isFadeIn = false;                //  �ȃ^�C�g���\�����o
	bool  _showInfo_beforeStartGame = true; //  �ȃ^�C�g���\�����o
};