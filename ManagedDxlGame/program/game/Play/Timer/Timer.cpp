#include "Timer.h"


void Timer::Resume() {

	if (_isPaused) {
		// �X�^�[�g������̌o�ߎ��� + ���݂̌o�ߎ��� - �|�[�Y���̎���
		_startTime += std::chrono::high_resolution_clock::now() - _pausedTime;
		_isPaused = false;
	}
}


double Timer::Elapsed() {

	if (_isPaused) {
		return std::chrono::duration<double>(_pausedTime - _startTime).count();
	}
	else {
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - _startTime).count();
	}
}


void Timer::Start() {

	//�@�v���C�J�n�Ɠ����Ɍv���J�n
	_startTime = std::chrono::high_resolution_clock::now();
	_isPaused = false;
}


void Timer::Pause() {

	if (!_isPaused) {
		// �|�[�Y���̌o�ߎ��Ԃ��擾
		_pausedTime = std::chrono::high_resolution_clock::now();
		_isPaused = true;
	}
}


void Timer::Reset() {

	_startTime = std::chrono::high_resolution_clock::now();
	_pausedTime = _startTime;
}