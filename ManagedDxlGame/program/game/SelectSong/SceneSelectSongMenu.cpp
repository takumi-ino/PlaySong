#include "../dxlib_ext/dxlib_ext.h"
#include "../Manager/SceneManager.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../Title/SceneTitle.h"
#include "../Play/ScenePlaySong.h"


namespace {

	const int _LEVEL_NUM = 4; // ��Փx�̐�
	const int _PLAYLIST_X_POS = 895;
	const int _PLAYLIST_Y_POS = 70;
	const int _LEVELLIST_X_POS = 310;
	const int _LEVELLIST_Y_POS = 580;

	const int _LEVELSHAPES_X_POS = 335;  // ��Փx��������͂��}�`

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
	const int _SONGTITLE_POS_X = 1050;

	// �I�𒆕�������W�ړ�
	const int _NOWSELECTINGSONG_POS_X = _SONGTITLE_POS_X - 15;

	// ��Փx���I����Ԃ̐F
	const int _DEFAULT_SONG_COLOR = GetColor(255, 255, 255);

	// �I�𒆓�Փx�̘g�̐F
	const int _NOWSELECTINGSONG_COLOR = GetColor(255, 0, 0);

	const int _FINALCHECK_DIMSCREEN_ALPHA = 50;
}


const char* SelectSongMenu::_SONG_TITLE[PLAYLIST_NUM] =
{
	"�����ȑ�9��",
	"BadApple!!",
	"���\���o�[�Y" ,
	"�c���ȓV�g�̃e�[�["
};

const char* SelectSongMenu::_SONG_GENRE[PLAYLIST_NUM] =
{
	"�N���V�b�N",
	"����Vocal",
	"�{�[�J���C�h",
	"�A�j�\��"
};

const char* SelectSongMenu::_SONG_GENRE_ALL_LIST[GENRE_NUM] =
{
	"�N���V�b�N",
	"J-POP",
	"�A�j�\��",
	"����Vocal",
	"�{�[�J���C�h",
	"���b�N",
	"�Q�[���~���[�W�b�N"
};

const char* SelectSongMenu::_SONG_LEVELS[4] =
{
	"EASY",
	"BASIC",
	"HARD",
	"ABYSS"
};


// ����----------------------------------------------------------------------------------------------------
void SelectSongMenu::SelectingSongByInput() {

	if (_songSelect) {

		// ��L�[
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP) || tnl::Input::IsPadDownTrigger(ePad::KEY_UP))
		{
			StopSoundMem(songList[_songIndex]);
			// �Đ��ʒu�������ʒu�ɖ߂�
			SetCurrentPositionSoundMem(0, songList[_songIndex]);

			_songIndex--;

			if (_songIndex < 0) 
				_songIndex = PLAYLIST_NUM - 1;
		}
		// ���L�[
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN) || tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN))
		{
			StopSoundMem(songList[_songIndex]);
			// �Đ��ʒu�������ʒu�ɖ߂�
			SetCurrentPositionSoundMem(0, songList[_songIndex]);

			_songIndex++;

			if (_songIndex >= PLAYLIST_NUM) 
				_songIndex = 0;
		}
	}
}


void SelectSongMenu::PickOneSongByInput() {

	// �I�𒆂̋ȃ��[�v�Đ�
	PlaySoundMem(songList[_songIndex], DX_PLAYTYPE_LOOP, false);

	bool _soundPlayed = false;

	// ����L�[�������ꂽ�ꍇ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1))
	{
		// �ȑI�𒆂Ȃ��Փx�I���Ɉڍs����
		if (_songSelect) {
			_levelSelect = true;
			_songSelect = false;
		}
		// ��Փx�I�𒆂Ȃ�ŏI�m�F�������\��
		else if (_levelSelect)
		{
			_showFinalCheck_beforeStartPlaySong = true;
			_levelSelect = false;
		}
		// �ŏI�m�F���Ȃ�v���C�V�[���ɑJ��
		else if (_showFinalCheck_beforeStartPlaySong)
		{
			if (!_soundPlayed) {
				PlaySoundMem(titleToSelectMenu_hdl, DX_PLAYTYPE_BACK, TRUE);
				_soundPlayed = true;
			}

			_moveToPlayScene = true;

			MoveToScenePlaySong();
		}
	}

	if (_moveToPlayScene)
		_soundPlayed = false;
}



void SelectSongMenu::BackToPreviousByInput() {

	// �L�����Z���L�[�������ꂽ�ꍇ
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_BACK) || tnl::Input::IsPadDownTrigger(ePad::KEY_0))
	{
		// ��Փx�I�𒆂Ȃ�ȑI���ɖ߂�
		if (_levelSelect) {

			_levelIndex = 0;
			_levelSelect = false;
			_songSelect = true;
		}
		else if (_showFinalCheck_beforeStartPlaySong) {

			// �ŏI�m�F��ʂ�\�����Ȃ��Փx�I���ɖ߂�
			_showFinalCheck_beforeStartPlaySong = false;
			_levelSelect = true;
		}
	}
}



void SelectSongMenu::SelectingLevelByInput() {

	if (_levelSelect) {

		// ��Փx�I�𒆂Ȃ��Փx�̃C���f�b�N�X�����炷
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) || tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT))
		{
			_levelIndex--;
			if (_levelIndex < 0)
				_levelIndex = _LEVEL_NUM - 1;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) || tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT))
		{
			_levelIndex++;
			if (_levelIndex >= _LEVEL_NUM)
				_levelIndex = 0;
		}
	}
}

// ----------------------------------------------------------------------------------------------------
void SelectSongMenu::SetDimScreenAtFinalCheck() {

	if (_showFinalCheck_beforeStartPlaySong) {

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _FINALCHECK_DIMSCREEN_ALPHA);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		SetFontSize(100);
		DrawStringEx(_SELECTED_SONG_TEXT_POS_X, _SELECTED_SONG_TEXT_POS_Y, -1,
			_SONG_TITLE[_songIndex]);   // �I�������Ȗ�

		SetFontSize(50);

		DrawStringEx(_SELECTED_LEVEL_TEXT_POS_X, _SELECTED_LEVEL_TEXT_POS_Y, -1,
			_SONG_LEVELS[_levelIndex]); // �I��������Փx

		DrawStringEx(_START_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Start");
		DrawStringEx(_BACK_TEXT_POS_X, _STARTBACK_TEXT_POS_Y, -1, "Back");

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _FINALCHECK_DIMSCREEN_ALPHA);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// ���ݎ��^�ς݂̋Ȃ̃W���������Ƃ̑���
int numOfTotalSongs_eachGenre[GENRE_NUM];

void SelectSongMenu::SongGenreTotalCount() {

	// �ǉ��ς݃v���C���X�g
	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// �S�ȃW������
		for (int j = 0; j < GENRE_NUM; j++)
		{
			// �W������������v������J�E���g�𑝂₷
			if (strcmp(_SONG_GENRE[i], _SONG_GENRE_ALL_LIST[j]) == 0)
			{
				numOfTotalSongs_eachGenre[j]++;
				break; // ��v�����烋�[�v�𔲂���
			}
		}
	}
}

// �`��----------------------------------------------------------------------------------------------------
void SelectSongMenu::RenderTotalSongGenreList() {

	// �W�������ƋȐ���\��  �����c����
	for (int i = 0; i < GENRE_NUM; i++)
	{
		// �I�𒆂̋Ȃ̃W�������Ȃ�F��ς���
		if (strcmp(_SONG_GENRE[_songIndex], _SONG_GENRE_ALL_LIST[i]) == 0)
		{
			SetDrawBright(0, 255, 0); // �F��΂ɂ���
		}

		// �W�������ƋȐ���\������
		DrawFormatString(50, 20 + i * 33, -1, "%s�F%d", _SONG_GENRE_ALL_LIST[i], numOfTotalSongs_eachGenre[i]);
		SetDrawBright(255, 255, 255); // �F�𔒂ɖ߂�
	}
}


void SelectSongMenu::RenderAndChangeColor_SongTitle() {

	for (int i = 0; i < PLAYLIST_NUM; i++)
	{
		// �I�𒆂̋ȂȂ�F��ς���
		if (_songSelect && i == _songIndex)
		{
			SetDrawBright(255, 255, 0);   // �F�����F�ɂ���
		}
		else {
			SetDrawBright(255, 255, 255); // �F�𔒂ɖ߂�
		}

		// �Ȗ���\������
		DrawString(_PLAYLIST_X_POS, _PLAYLIST_Y_POS * (i + 1), _SONG_TITLE[i], -1);
	}
}


void SelectSongMenu::RenderAndChangeColor_SongLevel() {

	for (int i = 0; i < _LEVEL_NUM; i++)
	{
		// �I�𒆂̓�Փx�Ȃ�F��ς���				
		if (_levelSelect && i == _levelIndex)
		{
			SetDrawBright(255, 255, 0);   // �F�����F�ɂ���
		}
		else {
			SetDrawBright(255, 255, 255); // �F�𔒂ɖ߂�
		}

		// ��Փx��\������
		DrawOvalAA(
			static_cast<float>(_LEVELSHAPES_X_POS + ((i + 1) * 100)),
			_LEVELLIST_Y_POS,
			50, 50, 8, -1,
			false,
			1
		);

		SetFontSize(15);
		DrawString(
			_LEVELLIST_X_POS + ((i + 1) * 100),
			_LEVELLIST_Y_POS,
			_SONG_LEVELS[i],
			-1
		);
	}
}


void SelectSongMenu::RenderBigSizeTitle_AtCenter() {

	SetDrawBright(255, 255, 255);
	SetFontSize(80);	          //��Փx��ɑI�𒆂̋Ȃ̃^�C�g���i��j
	DrawFormatString(_BIGSIZE_TITLE_POS_X, _BIGSIZE_TITLE_POS_Y, -1, _SONG_TITLE[_songIndex]);

	SetFontSize(40);
	DrawStringEx(1070, 640, -1, "Enter");
	DrawStringEx(10, DXE_WINDOW_HEIGHT - 45, -1, "music select...");
}


void SelectSongMenu::Render() {

	// �v���C�V�[���ɂ܂����ł��Ȃ���Ε`��
	if (_moveToPlayScene) return;

	SetDimScreenAtFinalCheck();       // ���邳����

	RenderTotalSongGenreList();

	RenderAndChangeColor_SongTitle();

	RenderAndChangeColor_SongLevel();

	RenderBigSizeTitle_AtCenter();
}


// �X�V----------------------------------------------------------------------------------------------------
void SelectSongMenu::MoveToScenePlaySong()
{
	auto mgr = SceneManager::GetInstance();
	mgr->SceneChange(new PlaySong(
		_SONG_TITLE[_songIndex],     //�I����
		_SONG_LEVELS[_levelIndex],  //�I���Փx�A
		_songIndex, _levelIndex)); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��
}


void SelectSongMenu::Update(float deltaTime) {

	SelectingSongByInput();

	PickOneSongByInput();

	BackToPreviousByInput();

	SelectingLevelByInput();

	if (_moveToPlayScene) {

		StopSoundMem(songList[_songIndex]);
		SetCurrentPositionSoundMem(0, songList[_songIndex]);
		_songSelect = true;  // �܂��ȑI���ɖ߂��Ă����Ƃ��ɋȑI������n�߂���悤��
	}
}