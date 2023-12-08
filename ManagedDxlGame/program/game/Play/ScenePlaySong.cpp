#include "../Main.h"
#include "ScenePlaySong.h"
#include "../Result/SceneResult.h"
#include "../SelectSong/SceneSelectSongMenu.h"
#include "../dxlib_ext/dxlib_ext.h"
#include "JudgeZone/JudgeZone.h"
#include "Score_Combo/ScoreCombo.h"
#include "Pause/PauseOption.h"
#include "Note/Notes.h"
#include "Note/LoadCSV/NoteDataCsv.h"
#include "Note/Normal/NormalNote.h"
#include "Note/Long/LongNote.h"


JudgeZone judgeZone[4];
Timer* PlaySong::_timer;


PlaySong::PlaySong(const char* title, const char* level, int index, int levelIdx) {

	songName = title;
	songLevel = level;
	songIndex = index;	// �I���ȃ^�C�g���ƃJ�o�[�A���o���ŋ��L
	levelIndex = levelIdx;

	songDuration = GetSoundTotalTime(songList[songIndex]);  // �Ȃ̒����擾

	// �f���^�^�C���B�e�N���X�ŋ��L
	raw_deltaTime_value = new float();

	NoteDataCsv::GetInstance().SetNoteKeyValue();

	LoadSelectedSongNotes();

	judgeZone->InitJudgeZone();
	_scoreCombo = new ScoreCombo();

	_scoreCombo->SetScoreComboRef(_scoreCombo);
	judgeZone->SetScoreComboRef(_scoreCombo);

	_normal_noteRef = dynamic_cast<NormalNote*>(_normal_downcastRef);
	_long_noteRef = dynamic_cast<LongNote*>(_long_downcastRef);

	_timer = new Timer();
	_pauseOption = new PauseOption();

	LoadImages();
	SetSongBPM();
}


int coverAlbum_hdl[PlaySong::COVERALBUM_NUM];


void PlaySong::LoadImages() {


	coverAlbum_hdl[0] = LoadGraph("graphics/symphonyNo9.jpg");
	// ���쌠�̊֌W��摜�͕\�����Ȃ�
	coverAlbum_hdl[1] = LoadGraph("");//graphics/badApple.jpg
	coverAlbum_hdl[2] = LoadGraph("");//graphics/two-facedLovers.jpg
	coverAlbum_hdl[3] = LoadGraph("");//graphics/cruel_angel's _thesis.jpg
}


void PlaySong::SetSongBPM() {

	if (songIndex == 0)	  	  songBpm = 125;
	else if (songIndex == 1)  songBpm = 130;
	else if (songIndex == 2)  songBpm = 140;
	else if (songIndex == 2)  songBpm = 110;
}


void PlaySong::LoadSelectedSongNotes() {

	// �I�������Ȃ̃m�[�c�����[�h

	if (songIndex == 0) {

		_normal_downcastRef = new NormalNote("�����ȑ�9��");
		_long_downcastRef = new LongNote("�����ȑ�9��");
	}

	else if (songIndex == 1) {

		_normal_downcastRef = new NormalNote("BadApple!!");
		_long_downcastRef = new LongNote("BadApple!!");
	}


	else if (songIndex == 2) {

		_normal_downcastRef = new NormalNote("���\���o�[�Y");
		_long_downcastRef = new LongNote("���\���o�[�Y");
	}

	else if (songIndex == 3) {

		_normal_downcastRef = new NormalNote("�c���ȓV�g�̃e�[�[");
		_long_downcastRef = new LongNote("�c���ȓV�g�̃e�[�[");
	}
}



void PlaySong::Audio_MP3() {

	if (!moveToResult)  PlaySoundMem(songList[songIndex], DX_PLAYTYPE_BACK, FALSE);
	else DeleteSoundMem(songList[songIndex]);
}



void PlaySong::RenderMetaData() {

	SetFontSize(25);
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 70, -1, songName); // �Ȗ�
	DrawStringEx(DXE_WINDOW_WIDTH - 240, 95, -1, songLevel); // ��Փx
}



void PlaySong::FadeScreenByAlpha() {

	// �V�[���J�ڌ�A�J�o�[�A���o���Ƌȃ^�C�g�����t�F�[�h�C��

	elapsed = sequence.getProgressTime();
	progress_ratio = elapsed / duration;
	alpha = 0;

	if (elapsed >= duration) {  // �t�F�[�h�C��

		isFadeIn = true;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}
	if (isFadeIn && elapsed >= duration) { // �t�F�[�h�A�E�g

		isFadeIn = false;
		elapsed = 0.f;
		progress_ratio = 0.f;
	}
	if (isFadeIn) {

		alpha = 255 * (1 * progress_ratio);
	}
	else {
		alpha = 255 * (1 - progress_ratio);
	}
}



void PlaySong::CheckIfSongEndByTimer() {

	_timer->currentTime = _timer->Elapsed();  // �^�C�}�[

	if (_timer->currentTime > (songDuration / 1000.0)) {  // �Ȃ��I�������

		moveToResult = true;  // ���U���g��
	}
}



void PlaySong::ShowSongInfo_BeforeStart() {

	if (moveToResult) moveToResult = false;

	FadeScreenByAlpha();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (alpha <= 0)	alpha = 0;
	// �J�o�[�A���o��
	DrawExtendGraph(_COVERALBUM_POS_X1, 70, _COVERALBUM_POS_X2, 620, coverAlbum_hdl[songIndex], false);
	SetFontSize(75);
	DrawStringEx(DXE_WINDOW_WIDTH / 3, 625, -1, songName); // �Ȗ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

	if (alpha == 0) {

		showInfo_beforeStart_playSong = false;
		elapsed = 0.f;
		progress_ratio = 0.f;

		_timer->Start();

		_timer->Reset();
		currentState = 1;
	}
}


bool PlaySong::isPaused = false;
bool PlaySong::moveToResult = false;
int PlaySong::songIndex = 0; // �Ȕԍ�
int PlaySong::currentState = 0;  // ���j���[��ʂ̃X�e�[�g���


void PlaySong::Render() {

	// �t�F�[�h�C����A�ȏ���\���B����܂ő��̏����͖���
	switch (currentState)
	{
	case 0:
		if (showInfo_beforeStart_playSong) {

			ShowSongInfo_BeforeStart();
		}
		break;
	case 1:
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_P) ||
			tnl::Input::IsPadDownTrigger(ePad::KEY_4)) {

			isPaused = true;
		}

		if (!isPaused) {

			if (!moveToResult) Audio_MP3();  // ����

			SetFontSize(35); // �^�C�}�[�\��
			std::string time = std::to_string(_timer->currentTime);
			DrawString(50, 50, time.c_str(), -1);

			StopSoundMem(pause_BGM_hdl);  // �|�[�Y���BGM��~
			SetCurrentPositionSoundMem(0, pause_BGM_hdl);


			RenderMetaData(); // �ȏ��`��

			_scoreCombo->RenderCombo(); // �R���{�`��

			_scoreCombo->RenderScore(); // �X�R�A�`��

			// �Ȃ��I�������ⓚ���p�Ń��U���g��
			CheckIfSongEndByTimer();

			judgeZone->RenderMap(); // �S�̃G���A�`��
			judgeZone->RenderJudgeZones();

			//�@�m�[�c�y�ѓ����蔻��G���A�����B���̊֐����őS�čs���Ă���B
			_normal_noteRef->UpdateNotes(_timer->currentTime, *(raw_deltaTime_value));
			_long_noteRef->UpdateNotes(_timer->currentTime, *(raw_deltaTime_value));

			DrawStringEx(5, 5, -1, "PAUSE�FP");
			break;
		}
		else
		{
			_timer->Pause();	// �|�[�Y���J�n���ꂽ�Ƃ��̎��Ԃ��L�^

			PlaySoundMem(pause_BGM_hdl, DX_PLAYTYPE_LOOP, false);

			StopSoundMem(songList[songIndex]);  // �����ꎞ��~

			if (!_pauseOption->showOption) {

				_pauseOption->UpdatePauseMenuCursor_ByInput();

				// �E�����ɕ\���̔��l
				_pauseOption->RenderMenuItems_AndDescriptions();

				// ����L�[�������ꂽ�ꍇ
				if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) || tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {

					_pauseOption->PickMenuItemByInput();
				}
			}
			else {   // �I�v�V�������J���Ă��鎞�̏���

				_pauseOption->UpdatePauseOptionCursor_ByInput();

				_pauseOption->ChangePauseOptionColor();

				_pauseOption->GoNextOrGoBack();

				_pauseOption->AdjustVolumeByInput();

				// low, medium, high�̐F 
				int eff1_color = -1, eff2_color = -1, eff3_color = -1;


				if (_pauseOption->selectEffColor) { // low, medium, high�̕�����̐F�̕ύX

					_pauseOption->UpdateSelectEffectCursor_ByInput();
					_pauseOption->ChangeSelectEffectColorAndBrightness(eff1_color, eff2_color, eff3_color);
				}

				SetFontSize(33);
				_pauseOption->RenderAdjustVolumeFunc();
				_pauseOption->RenderLowMediumHighWord(eff1_color, eff2_color, eff3_color);
			}
		}
		showInfo_beforeStart_playSong = true;
		break;
	case 2:
		moveToSongSelect = true;
		break;
	}
}



void PlaySong::Update(float delta_time) {

	_timer->UpdateDeltaTime();
	_timer->GetDeltaTime();

	raw_deltaTime_value = &delta_time;

	SetFontSize(30);
	DrawStringEx(10, 690, -1, "%f.2", GetFPS());

	sequence.update(delta_time);
}



bool PlaySong::SeqIdle(float delta_time) {


	if (moveToSongSelect) {

		StopSoundMem(songList[songIndex]);
		SetCurrentPositionSoundMem(0, songList[songIndex]);
		ClearDrawScreen();

		if (isPaused)	isPaused = false;
		_scoreCombo->myScore = 0;


		if (moveToResult) moveToResult = false;

		// �I�ȃV�[����
		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new SelectSongMenu());
	}

	if (_pauseOption->isRetryGame) {

		StopSoundMem(songList[songIndex]);
		SetCurrentPositionSoundMem(0, songList[songIndex]);
		ClearDrawScreen();


		_scoreCombo->myScore = 0;
		if (isPaused)	isPaused = false;

		_pauseOption->isRetryGame = false;

		if (moveToResult) moveToResult = false;

		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new PlaySong(
			SelectSongMenu::_songTitle[songIndex],  //�I����
			SelectSongMenu::_songLevels[levelIndex],  //�I���Փx�A
			songIndex,
			levelIndex)); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��
	}

	if (moveToResult) {

		StopSoundMem(songList[songIndex]);
		SetCurrentPositionSoundMem(0, songList[songIndex]);
		ClearDrawScreen();


		if (isPaused)	isPaused = false;


		auto mgr = SceneManager::GetInstance();
		mgr->SceneChange(new Result(
			_scoreCombo->myScore,
			_scoreCombo->myCombo,
			_scoreCombo->perfect_count,
			_scoreCombo->great_count,
			_scoreCombo->good_count,
			_scoreCombo->poor_count,
			_scoreCombo->miss_count,
			songName,
			songLevel)); // �I�񂾋Ȃ̔ԍ� �� PlaySong�V�[���ɓn��

		moveToResult = false;
	}

	return true;
}



void PlaySong::Destroy() {

	//delete raw_deltaTime_value;
	//raw_deltaTime_value = nullptr;

	delete _scoreCombo;
	_scoreCombo = nullptr;

	delete _pauseOption;
	_pauseOption = nullptr;

	delete _normal_downcastRef;
	_normal_downcastRef = nullptr;

	_long_downcastRef = nullptr;
	delete _long_downcastRef;

	//delete _normal_noteRef;
	//_normal_noteRef = nullptr;

	//delete _long_noteRef;
	//_long_noteRef = nullptr;
}