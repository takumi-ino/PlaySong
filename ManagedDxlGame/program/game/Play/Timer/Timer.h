#pragma once
#include <chrono>


class Timer {
public:

	Timer() : _isPaused(false) {}

	void Start();      // �J�n

	void Pause();      // �ꎞ��~

	void Resume();     // �ĊJ

	void Reset();      // ���Z�b�g

	double Elapsed();  // �o��

public:

	bool   _isPaused{};

	double _currentTime{};

	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _pausedTime;
};