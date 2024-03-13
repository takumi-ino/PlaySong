#include "Timer.h"


void Timer::Resume() {

	if (_isPaused) {
		// スタート時からの経過時間 + 現在の経過時間 - ポーズ中の時間
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

	//　プレイ開始と同時に計測開始
	_startTime = std::chrono::high_resolution_clock::now();
	_isPaused = false;
}


void Timer::Pause() {

	if (!_isPaused) {
		// ポーズ中の経過時間を取得
		_pausedTime = std::chrono::high_resolution_clock::now();
		_isPaused = true;
	}
}


void Timer::Reset() {

	_startTime = std::chrono::high_resolution_clock::now();
	_pausedTime = _startTime;
}