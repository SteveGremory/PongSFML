#pragma once

#include <chrono>

/**
 * @brief Simple timer class to keep track of the elapsed time
 */
class Timer {
public:
	Timer() : start(std::chrono::high_resolution_clock::now()) {}

	// Re-captures starting time point to high_resolution_clock::now
	void reset() { start = std::chrono::high_resolution_clock::now(); }

	// Returns the elapsed time in seconds
	auto elapsed_time() -> float {
		auto const end = std::chrono::high_resolution_clock::now();

		return std::chrono::duration_cast<std::chrono::microseconds>(end -
																	 start)
				   .count() /
			   1000000.0f;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start = {};
};