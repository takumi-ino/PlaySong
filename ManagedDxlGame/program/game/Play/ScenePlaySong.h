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

	// ゲッター----------------------------------------------------------
	float GetDeltaTime() const { return deltaTime_ref; }

	// ロード----------------------------------------------------------
	void LoadImages();
	void LoadSelectedSongNotes(); 	// 選択した曲のノーツをロード

	// 各種機能--------------------------------------------------------
	void SetSongBPM();
	void FadeScreenByAlpha();         // プレイ開始のフェード演出
	void ShowSongInfo_BeforeStart();  // プレイ開始前に曲名を表示
	void CheckIfSongEndByTimer();     // 曲終了まで時間計測
	void PlaySongUntilSongEnd();      // 曲終了まで曲を流す

	// 描画------------------------------------------------------------
	void RenderScore();
	void RenderCombo();
	void RenderMetaData(); // 選択曲、選択難易度

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

	static int currentState;                 // メニュー画面のステート状態
	static int songIndex;                    // 曲番号
	static constexpr int COVERALBUM_NUM = 4; // カバーアルバム数
	static bool isPaused;
	static bool moveToResult;

private:

	int songBpm{};
	int songNotesNum{};
	int levelIndex{};

	float songDuration{};                       // 曲の長さ
	float timeCount_start = 0.f;

	float elapsed{};                            // 経過時間
	float progress_ratio{};                     // フェードの変化率
	float brightnessAlpha{};                    // 明度
	float deltaTime_ref{};                     // 引数からdeltaTimeを取得できないケースで使用する
	float duration = 4.0f;                      // 曲情報表示時間

	double spawnNotesDuration{};                // ノーツの１拍あたりの生成間隔	

	bool showInfo_beforeStart_playSong = true;
	bool isFadeIn = false;
	bool moveToSongSelect = false;
};