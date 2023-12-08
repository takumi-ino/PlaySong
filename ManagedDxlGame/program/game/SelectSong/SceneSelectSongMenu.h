#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/SoundManager.h"

#define GENRE_NUM 7 //�Ȃ̑S�W������


class Scenes;
class PlaySong;


// ������\���A���͏����ݒ�
class SelectSongMenu : public Scenes {

public:

	SelectSongMenu(){}

	void Render() override;
	void Update(float deltaTime) override;

	bool moveToPlayScene = false;

	void SongGenreTotalCount();

	//// �Ȃ̃^�C�g��
	static const char* _songTitle[PLAYLIST_NUM];

	//// �e�ȑΉ��̃W������
	static const char* _songGenre[PLAYLIST_NUM];

	//// �{��i�Ŏ�舵�������Ȃ̃W�������ꗗ
	static const char* _songGenreRefAll[GENRE_NUM];

	//// ��Փx���ځi���e�����j�AEasy����Abyss�܂�
	static const char* _songLevels[4];

private:


	// ��ʍ���
	void Render_TotalSongGenreList();

	void SelectingSongByInput();

	void PickOneSongByInput();

	void BackToPreviousByInput();

	void SelectingLevelByInput();


	// �Q�[���J�n
	void StartPlaySongByInput();

	// �ȃ^�C�g���F�ύX
	void RenderAndChangeColor_SongTitle();

	// �ȃ��x���F�ύX
	void RenderAndChangeColor_SongLevel();

	// �����ɕ\���̋ȃ^�C�g��
	void RenderBigSizeTitle_AtCenter();

	bool SeqIdle(float deltaTime);

	tnl::Sequence<SelectSongMenu> sequence = tnl::Sequence<SelectSongMenu>(this, &SelectSongMenu::SeqIdle);
	
	// �����ɑI�𒆂̋Ȗ���傫���\��
	int songTitleXPos_leftSide = 360;
	int	songTitleYPos_leftSide = 280;

	int songIndex = 0; // �I�𒆂̋Ȃ̃C���f�b�N�X
	int levelIndex = 0; // �I�𒆂̓�Փx�̃C���f�b�N�X
	bool songSelect = true; // �ȑI�𒆂��ǂ���
	bool levelSelect = false; // ��Փx�I�𒆂��ǂ���
	int dimScreen_alphaSize = 50;
	int notesAllNum;
	bool backToTitle = false;




	const int _LEVEL_NUM = 4; // ��Փx�̐�
	const int _PLAYLIST_X_POS = 895;
	const int _PLAYLIST_Y_POS = 70;
	const int _LEVELLIST_X_POS = 310;
	const int _LEVELLIST_Y_POS = 580;


	// �v���C�V�[���ɔ�ԑO�ɕ\������A�I�������Ȗ��� X��
	const int _SELECTED_SONG_TEXT_POS_X = 355;
	const int _SELECTED_SONG_TEXT_POS_Y = 120;

	const int _SELECTED_LEVEL_TEXT_POS_X = 580;
	const int _SELECTED_LEVEL_TEXT_POS_Y = 250;

	const int _START_TEXT_POS_X = 445;
	const int _BACK_TEXT_POS_X = 785;
	const int _STARTBACK_TEXT_POS_Y = 450;

	const int _BIGSIZE_TITLE_POS_X = 330;
	const int _BIGSIZE_TITLE_POS_Y = 380;


	// �ȃ^�C�g�������ʒu�I�t�Z�b�g
	const int _defaultSongXPos = 1050;

	// �I�𒆕�������W�ړ�
	const int nowSelectedSong_offsetX = _defaultSongXPos - 15;

	// ��Փx���I����Ԃ̐F
	const int defaultSong_color = GetColor(255, 255, 255);

	// �I�𒆓�Փx�̘g�̐F
	const int nowSelectedSong_color = GetColor(255, 0, 0);

	bool show_finalCheck_before_startPlaySong = false;
};