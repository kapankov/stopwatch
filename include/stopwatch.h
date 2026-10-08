#pragma once

#include <chrono>
#include <string>

/**
 * @brief Returns a string representation of the time unit for the given template type
 * 
 * Specialized template function that returns a string with the time unit name
 * depending on the template type T:
 * - std::chrono::milliseconds -> " ms"
 * - std::chrono::microseconds -> " μs"
 * - std::chrono::nanoseconds  -> " ns"
 * - std::chrono::seconds      -> " s"
 * 
 * @tparam T Time unit type (std::chrono::* duration)
 * @return std::string String representation of the time unit
 */
template<typename T>
static std::string duration_unit() {
    if constexpr (std::is_same_v<T, std::chrono::milliseconds>)
        return " ms";
    else if constexpr (std::is_same_v<T, std::chrono::microseconds>)
        return " μs";
    else if constexpr (std::is_same_v<T, std::chrono::nanoseconds>)
        return " ns";
    else if constexpr (std::is_same_v<T, std::chrono::seconds>)
        return " s";
    else
        return "";
}

/**
 * @brief Timer class for measuring code execution time
 * 
 * Stopwatch measures the time between the moment of object creation and the moment
 * of its destruction (leaving the scope). The time is output as a string
 * to the provided string variable.
 * 
 * Uses std::chrono::steady_clock for time measurement,
 * which is not affected by system time changes.
 * 
 * @tparam Dur Time unit type for storing the result. Default - std::chrono::milliseconds
 * 
 * @code
 * std::string result;
 * {
 *     stopwatch sw(result);
 *     // ... measured code ...
 * } // Time is written to result automatically when stopwatch is destroyed
 * @endcode
 * 
 * The object cannot be copied (copy constructor and assignment operator are deleted).
 */
template<typename Dur = std::chrono::milliseconds>
class stopwatch {
	using steady_clock = std::chrono::steady_clock;
public:
	/**
	 * @brief Creates stopwatch, records the start measurement time
	 * 
	 * @param output Reference to the string where the measurement result will be written
	 */
	explicit stopwatch(std::string& output)
		: output_(output)
		, start_(steady_clock::now()) {}

	/**
	 * @brief Stopwatch destructor - completes time measurement
	 * 
	 * Calculates the elapsed time, converts it to the specified Dur type
	 * and writes the result to output_ string in the format "<number><unit>"
	 */
	~stopwatch() {
		auto end = steady_clock::now();
		auto dur = std::chrono::duration_cast<Dur>(end - start_).count();
		output_.append(std::to_string(dur));
		output_.append(duration_unit<Dur>());
	}

	// Copy prohibition
	stopwatch(const stopwatch&) = delete;
	stopwatch& operator=(const stopwatch&) = delete;

private:
	std::string& output_;                     ///< Reference to the string for output result
	steady_clock::time_point start_;          ///< Timestamp of the start measurement
};
