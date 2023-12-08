#pragma once
#include <vector>
#include <map>
#include "../library/tnl_sequence.h"
#include "../Manager/Scene/SceneBase.h"
#include "../Manager/SceneManager.h"
#include "Note/Notes.h"
#include "Timer/Timer.h"


class Scenes;
class NormalNote;
class LongNote;
class JudgeZone;
class ScoreCombo;
class ScoreCombo;
class PauseOption;


extern JudgeZone judgeZone[4];


class PlaySong :public Scenes {

public:

	PlaySong() {}
	PlaySong(const char* title, const char* level, int songIndex, int levelIdx);

	explicit PlaySong(std::unordered_map<std::string, std::string>) {}

	void Destroy() override;

	void Render() override;
	void Update(float delta_time) override;

	tnl::Sequence<PlaySong> sequence = tnl::Sequence<PlaySong>(this, &PlaySong::SeqIdle);
	bool SeqIdle(float delta_time);

	void Audio_MP3();

private:

	void LoadSelectedSongNotes();
	void SetSongBPM();
	void FadeScreenByAlpha();
	void ShowSongInfo_BeforeStart();
	void RenderScore();  // スコア表示
	void RenderMetaData(); // 選択曲、選択難易度
	void RenderCombo();
	void CheckIfSongEndByTimer();
	void LoadImages();

public:

	static Timer* _timer;

private:

	Notes* _normal_downcastRef;
	Notes* _long_downcastRef;
	NormalNote* _normal_noteRef;
	LongNote* _long_noteRef;

	ScoreCombo* _scoreCombo;
	PauseOption* _pauseOption;

public:

	static constexpr int COVERALBUM_NUM = 4; // カバーアルバム数
	static bool isPaused;
	static bool moveToResult;
	static int currentState;  // メニュー画面のステート状態
	static int songIndex;     // 曲番号

private:

	int songBpm;
	int songNotesNum;
	int levelIndex;
	float songDuration;       // 曲の長さ
	float timeCount_start = 0.f;

	const int _COVERALBUM_POS_X1 = 320;
	const int _COVERALBUM_POS_X2 = 960;

	const char* songName;     // 曲名
	const char* songLevel;    // 難易度

	double spawnNotesDuration = 60.0 / songBpm; // ノーツの１拍あたりの生成間隔	

	float elapsed;
	float progress_ratio;
	float alpha;
	float* raw_deltaTime_value;
	float duration = 4.0f; // 曲情報表示時間

	bool showInfo_beforeStart_playSong = true;
	bool isFadeIn = false;
	bool moveToSongSelect = false;
};