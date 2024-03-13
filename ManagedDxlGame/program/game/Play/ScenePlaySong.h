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

	// 講師配布ライブラリより。Sequenceクラスの タイマー関数を使用する
	tnl::Sequence<PlaySong> sequence = tnl::Sequence<PlaySong>(this, &PlaySong::SeqIdle);
	bool SeqIdle(float delta_time) { return true; };
			
	// ゲッター----------------------------------------------------------
	float GetDeltaTime() const { return _deltaTime; }

	// ロード----------------------------------------------------------
	void LoadImages();
	void LoadSelectedSongNotes(); 	// 選択した曲のノーツをロード

	// 各種機能--------------------------------------------------------
	void SetSongBPM();
	void FadeScreenByAlpha();         // プレイ開始のフェード演出
	void ShowSongInfo_BeforeStart();  // プレイ開始前に曲名を表示
	void CheckIfSongEndByTimer();     // 曲終了まで時間計測
	void PlaySongUntilSongEnd();      // 曲終了まで曲を流す
	void BackToSelectSongMenu();      // 曲選択へ戻る
	void RetryGame();                 // ゲームをやり直す
	void MoveToResult();              // リザルトへ飛ぶ
	void ActivatePauseMenu();         // ポーズメニューを開く
	void RevertAllChanges();          // プレイシーンから離れるときに全ての変更をリセットする

	// 描画------------------------------------------------------------
	void RenderMetaData(); // 選択曲、選択難易度

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

	static constexpr int _COVERALBUM_NUM = 4; // カバーアルバム数
	static int           _currentState;       // メニュー画面のステート状態
	static int           _songIndex;          // 曲番号
	static bool          _isPaused;
	static bool          _moveToSongSelect;
	static bool          _moveToResult;
	static bool          _isRetryGame;

private:

	int   _songBpm{};              // BPM
	int   _levelIndex{};

	float _songDuration{};         // 曲の長さ
	float _elapsed{};              // 経過時間
	float _progress_ratio{};       // フェードの変化率
	float brightnessAlpha{};      // 明度
	float _deltaTime{};            // 引数からdeltaTimeを取得できないケースで使用する

	bool  _isFadeIn = false;                //  曲タイトル表示演出
	bool  _showInfo_beforeStartGame = true; //  曲タイトル表示演出
};