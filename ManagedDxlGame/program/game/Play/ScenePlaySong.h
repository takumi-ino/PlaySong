#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/SceneManager.h"
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
	PlaySong(const char* title, const char* level, const int songIndex, const int levelIdx);

	void Destroy() override;

	void Render() override;
	void Update(float delta_time) override;

private:

	tnl::Sequence<PlaySong> sequence = tnl::Sequence<PlaySong>(this, &PlaySong::SeqIdle);
	bool SeqIdle(float delta_time);

	void ResetGame();

	// �Q�b�^�[----------------------------------------------------------
	float GetDeltaTime() const { return deltaTime_ref; }

	// ���[�h----------------------------------------------------------
	void LoadImages();
	void LoadSelectedSongNotes(); 	// �I�������Ȃ̃m�[�c�����[�h

	// �e��@�\--------------------------------------------------------
	void SetSongBPM();
	void FadeScreenByAlpha();         // �v���C�J�n�̃t�F�[�h���o
	void ShowSongInfo_BeforeStart();  // �v���C�J�n�O�ɋȖ���\��
	void CheckIfSongEndByTimer();     // �ȏI���܂Ŏ��Ԍv��
	void PlaySongUntilSongEnd();      // �ȏI���܂ŋȂ𗬂�

	// �`��------------------------------------------------------------
	void RenderScore();
	void RenderCombo();
	void RenderMetaData(); // �I���ȁA�I���Փx

public:

	static Timer* _timer;

private:

	Notes* _normal_downcastRef = nullptr;
	Notes* _long_downcastRef = nullptr;
	NormalNote* _normal_noteRef = nullptr;
	LongNote* _long_noteRef = nullptr;

	ScoreCombo* _scoreCombo = nullptr;
	PauseOption* _pauseOption = nullptr;

public:

	static int currentState;                 // ���j���[��ʂ̃X�e�[�g���
	static int songIndex;                    // �Ȕԍ�
	static constexpr int COVERALBUM_NUM = 4; // �J�o�[�A���o����
	static bool isPaused;
	static bool moveToResult;

private:

	int songBpm{};
	int songNotesNum{};
	int levelIndex{};

	float songDuration{};                       // �Ȃ̒���
	float timeCount_start = 0.f;

	float elapsed{};                            // �o�ߎ���
	float progress_ratio{};                     // �t�F�[�h�̕ω���
	float brightnessAlpha{};                    // ���x
	float deltaTime_ref{};                     // ��������deltaTime���擾�ł��Ȃ��P�[�X�Ŏg�p����
	float duration = 4.0f;                      // �ȏ��\������

	double spawnNotesDuration{};                // �m�[�c�̂P��������̐����Ԋu	

	bool showInfo_beforeStart_playSong = true;
	bool isFadeIn = false;
	bool moveToSongSelect = false;
};