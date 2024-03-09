#include "Timer.h"


void Timer::Resume() {

	if (isPaused) {
		// �X�^�[�g������̌o�ߎ��� + ���݂̌o�ߎ��� - �|�[�Y���̎���
		start_time += std::chrono::high_resolution_clock::now() - paused_time;
		isPaused = false;
	}
}


double Timer::Elapsed() {

	if (isPaused) {
		return std::chrono::duration<double>(paused_time - start_time).count();
	}
	else {
		return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
}


void Timer::Start() {

	//�@�v���C�J�n�Ɠ����Ɍv���J�n
	start_time = std::chrono::high_resolution_clock::now();
	isPaused = false;
}


void Timer::Pause() {

	if (!isPaused) {
		// �|�[�Y���̌o�ߎ��Ԃ��擾
		paused_time = std::chrono::high_resolution_clock::now();
		isPaused = true;
	}
}


void Timer::Reset() {

	start_time = std::chrono::high_resolution_clock::now();
	paused_time = start_time;
}