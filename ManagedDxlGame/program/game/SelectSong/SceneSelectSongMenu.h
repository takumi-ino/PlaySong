#pragma once
#include "../library/tnl_sequence.h"
#include "../Manager/SoundManager.h"

constexpr static int GENRE_NUM = 7; //�Ȃ̑S�W������

class Scenes;
class PlaySong;


// ������\���A���͏����ݒ�
class SelectSongMenu : public Scenes {

public:

	void SongGenreTotalCount();

	void Render() override;
	void Update(float deltaTime) override;

private:

	tnl::Sequence<SelectSongMenu> sequence = tnl::Sequence<SelectSongMenu>(this, &SelectSongMenu::SeqIdle);
	bool SeqIdle(float deltaTime);

	// ����--------------------------------------------------------------------------------
	void SelectingSongByInput();            // �ȑI��
	void PickOneSongByInput();              // �Ȍ���
	void MoveToScenePlaySong();
	void BackToPreviousByInput();           // 1�O�ɖ߂�
	void SelectingLevelByInput();           // ��Փx�I��

	// �`��--------------------------------------------------------------------------------
	void RenderTotalSongGenreList();	    // ��ʍ���
	void RenderAndChangeColor_SongTitle();	// �ȃ^�C�g���F�ύX
	void RenderAndChangeColor_SongLevel();	// �ȃ��x���F�ύX
	void RenderBigSizeTitle_AtCenter();	    // �����ɕ\���̋ȃ^�C�g��

	// ���邳����--------------------------------------------------------------------------
	void SetDimScreenAtFinalCheck();	    // �Q�[���J�n�O�̍ŏI�m�F��
	
public:

	//// �Ȃ̃^�C�g��
	static const char* _songTitle[PLAYLIST_NUM];

	//// �e�ȑΉ��̃W������
	static const char* _songGenre[PLAYLIST_NUM];

	//// �{��i�Ŏ�舵�������Ȃ̃W�������ꗗ
	static const char* _songGenreRefAll[GENRE_NUM];

	//// ��Փx���ځi���e�����j�AEasy����Abyss�܂�
	static const char* _songLevels[4];

private:

	// �����ɑI�𒆂̋Ȗ���傫���\��
	int songTitleXPos_leftSide = 360;
	int	songTitleYPos_leftSide = 280;

	int songIndex = 0;             // �I�𒆂̋Ȃ̃C���f�b�N�X
	int levelIndex = 0;            // �I�𒆂̓�Փx�̃C���f�b�N�X
	int dimScreen_alphaSize = 50;
	int notesAllNum{};

	bool songSelect = true;        // �ȑI�𒆂��ǂ���
	bool levelSelect = false;      // ��Փx�I�𒆂��ǂ���
	bool backToTitle = false;
	bool show_finalCheck_before_startPlaySong = false;
	bool moveToPlayScene = false;
};