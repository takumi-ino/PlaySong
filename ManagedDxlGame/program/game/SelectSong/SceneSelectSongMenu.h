#pragma once
#include "../Manager/SoundManager.h"

constexpr static int GENRE_NUM = 7; //�Ȃ̑S�W������

class Scenes;
class PlaySong;


// ������\���A���͏����ݒ�
class SelectSongMenu : public Scenes 
{
public:

	void SongGenreTotalCount();

	void Render() override;
	void Update(float deltaTime) override;

private:

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
	static const char* _SONG_TITLE[PLAYLIST_NUM];

	//// ���^�Ȃ݂̂ɑΉ������W������
	static const char* _SONG_GENRE[PLAYLIST_NUM];

	//// �{��i�Ŏ�舵�������Ȃ̑S�W�������\
	static const char* _SONG_GENRE_ALL_LIST[GENRE_NUM];

	//// ��Փx���ځi���e�����j�AEasy����Abyss�܂�
	static const char* _SONG_LEVELS[4];

private:


	int  _songIndex = 0;            // �I�𒆂̋Ȃ̃C���f�b�N�X
	int  _levelIndex = 0;           // �I�𒆂̓�Փx�̃C���f�b�N�X

	bool _songSelect = true;        // �ȑI�𒆂��ǂ���
	bool _levelSelect = false;      // ��Փx�I�𒆂��ǂ���
	bool _backToTitle = false;
	bool _moveToPlayScene = false;
	bool _showFinalCheck_beforeStartPlaySong = false;
};