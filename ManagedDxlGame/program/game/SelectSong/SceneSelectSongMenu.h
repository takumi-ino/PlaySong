#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/SoundManager.h"

#define GENRE_NUM 7 //曲の全ジャンル


class Scenes;
class PlaySong;


// 文字列表示、入力処理設定
class SelectSongMenu : public Scenes {

public:

	SelectSongMenu(){}

	void Render() override;
	void Update(float deltaTime) override;

	bool moveToPlayScene = false;

	void SongGenreTotalCount();

	//// 曲のタイトル
	static const char* _songTitle[PLAYLIST_NUM];

	//// 各曲対応のジャンル
	static const char* _songGenre[PLAYLIST_NUM];

	//// 本作品で取り扱いたい曲のジャンル一覧
	static const char* _songGenreRefAll[GENRE_NUM];

	//// 難易度項目（リテラル）、EasyからAbyssまで
	static const char* _songLevels[4];

private:


	// 画面左上
	void Render_TotalSongGenreList();

	void SelectingSongByInput();

	void PickOneSongByInput();

	void BackToPreviousByInput();

	void SelectingLevelByInput();


	// ゲーム開始
	void StartPlaySongByInput();

	// 曲タイトル色変更
	void RenderAndChangeColor_SongTitle();

	// 曲レベル色変更
	void RenderAndChangeColor_SongLevel();

	// 中央に表示の曲タイトル
	void RenderBigSizeTitle_AtCenter();

	bool SeqIdle(float deltaTime);

	tnl::Sequence<SelectSongMenu> sequence = tnl::Sequence<SelectSongMenu>(this, &SelectSongMenu::SeqIdle);
	
	// 左側に選択中の曲名を大きく表示
	int songTitleXPos_leftSide = 360;
	int	songTitleYPos_leftSide = 280;

	int songIndex = 0; // 選択中の曲のインデックス
	int levelIndex = 0; // 選択中の難易度のインデックス
	bool songSelect = true; // 曲選択中かどうか
	bool levelSelect = false; // 難易度選択中かどうか
	int dimScreen_alphaSize = 50;
	int notesAllNum;
	bool backToTitle = false;




	const int _LEVEL_NUM = 4; // 難易度の数
	const int _PLAYLIST_X_POS = 895;
	const int _PLAYLIST_Y_POS = 70;
	const int _LEVELLIST_X_POS = 310;
	const int _LEVELLIST_Y_POS = 580;


	// プレイシーンに飛ぶ前に表示する、選択した曲名の X軸
	const int _SELECTED_SONG_TEXT_POS_X = 355;
	const int _SELECTED_SONG_TEXT_POS_Y = 120;

	const int _SELECTED_LEVEL_TEXT_POS_X = 580;
	const int _SELECTED_LEVEL_TEXT_POS_Y = 250;

	const int _START_TEXT_POS_X = 445;
	const int _BACK_TEXT_POS_X = 785;
	const int _STARTBACK_TEXT_POS_Y = 450;

	const int _BIGSIZE_TITLE_POS_X = 330;
	const int _BIGSIZE_TITLE_POS_Y = 380;


	// 曲タイトル初期位置オフセット
	const int _defaultSongXPos = 1050;

	// 選択中文字列座標移動
	const int nowSelectedSong_offsetX = _defaultSongXPos - 15;

	// 難易度未選択状態の色
	const int defaultSong_color = GetColor(255, 255, 255);

	// 選択中難易度の枠の色
	const int nowSelectedSong_color = GetColor(255, 0, 0);

	bool show_finalCheck_before_startPlaySong = false;
};