#pragma once
#include "../Manager/SoundManager.h"

constexpr static int GENRE_NUM = 7; //曲の全ジャンル

class Scenes;
class PlaySong;


// 文字列表示、入力処理設定
class SelectSongMenu : public Scenes 
{
public:

	void SongGenreTotalCount();

	void Render() override;
	void Update(float deltaTime) override;

private:

	// 入力--------------------------------------------------------------------------------
	void SelectingSongByInput();            // 曲選択
	void PickOneSongByInput();              // 曲決定
	void MoveToScenePlaySong();
	void BackToPreviousByInput();           // 1つ前に戻る
	void SelectingLevelByInput();           // 難易度選択

	// 描画--------------------------------------------------------------------------------
	void RenderTotalSongGenreList();	    // 画面左上
	void RenderAndChangeColor_SongTitle();	// 曲タイトル色変更
	void RenderAndChangeColor_SongLevel();	// 曲レベル色変更
	void RenderBigSizeTitle_AtCenter();	    // 中央に表示の曲タイトル

	// 明るさ調整--------------------------------------------------------------------------
	void SetDimScreenAtFinalCheck();	    // ゲーム開始前の最終確認で

public:

	//// 曲のタイトル
	static const char* _SONG_TITLE[PLAYLIST_NUM];

	//// 収録曲のみに対応したジャンル
	static const char* _SONG_GENRE[PLAYLIST_NUM];

	//// 本作品で取り扱いたい曲の全ジャンル表
	static const char* _SONG_GENRE_ALL_LIST[GENRE_NUM];

	//// 難易度項目（リテラル）、EasyからAbyssまで
	static const char* _SONG_LEVELS[4];

private:


	int  _songIndex = 0;            // 選択中の曲のインデックス
	int  _levelIndex = 0;           // 選択中の難易度のインデックス

	bool _songSelect = true;        // 曲選択中かどうか
	bool _levelSelect = false;      // 難易度選択中かどうか
	bool _backToTitle = false;
	bool _moveToPlayScene = false;
	bool _showFinalCheck_beforeStartPlaySong = false;
};