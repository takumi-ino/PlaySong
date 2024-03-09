#include "Timer.h"


void Timer::Resume() {

	if (isPaused) {
		// スタート時からの経過時間 + 現在の経過時間 - ポーズ中の時間
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

	//　プレイ開始と同時に計測開始
	start_time = std::chrono::high_resolution_clock::now();
	isPaused = false;
}


void Timer::Pause() {

	if (!isPaused) {
		// ポーズ中の経過時間を取得
		paused_time = std::chrono::high_resolution_clock::now();
		isPaused = true;
	}
}


void Timer::Reset() {

	start_time = std::chrono::high_resolution_clock::now();
	paused_time = start_time;
}