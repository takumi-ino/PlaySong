#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/SoundManager.h"

constexpr static int GENRE_NUM = 7; //曲の全ジャンル

class Scenes;
class PlaySong;


// 文字列表示、入力処理設定
class SelectSongMenu : public Scenes {

public:

	void SongGenreTotalCount();

	void Render() override;
	void Update(float deltaTime) override;

private:

	tnl::Sequence<SelectSongMenu> sequence = tnl::Sequence<SelectSongMenu>(this, &SelectSongMenu::SeqIdle);
	bool SeqIdle(float deltaTime);

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
	static const char* _songTitle[PLAYLIST_NUM];

	//// 各曲対応のジャンル
	static const char* _songGenre[PLAYLIST_NUM];

	//// 本作品で取り扱いたい曲のジャンル一覧
	static const char* _songGenreRefAll[GENRE_NUM];

	//// 難易度項目（リテラル）、EasyからAbyssまで
	static const char* _songLevels[4];

private:

	// 左側に選択中の曲名を大きく表示
	int songTitleXPos_leftSide = 360;
	int	songTitleYPos_leftSide = 280;

	int songIndex = 0;             // 選択中の曲のインデックス
	int levelIndex = 0;            // 選択中の難易度のインデックス
	int dimScreen_alphaSize = 50;
	int notesAllNum{};

	bool songSelect = true;        // 曲選択中かどうか
	bool levelSelect = false;      // 難易度選択中かどうか
	bool backToTitle = false;
	bool show_finalCheck_before_startPlaySong = false;
	bool moveToPlayScene = false;
};