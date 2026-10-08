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
inline std::string duration_unit() {
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
	 * @brief Starts the stopwatch with the given output string
	 * 
	 * @param output Rvalue reference to the string where the result will be stored
	 */
	void run(std::string&& output)
	{
		output_ = std::move(output);
		start_ = steady_clock::now();
	}

	/**
	 * @brief Stops the stopwatch and returns the elapsed time string
	 * 
	 * Resets start_ to allow reuse of this stopwatch instance.
	 * 
	 * @return std::string The formatted elapsed time string
	 * @pre run() must have been called before
	 */
	std::string stop() {
		auto end = steady_clock::now();
		auto dur = std::chrono::duration_cast<Dur>(end - start_).count();
		output_.append(std::to_string(dur));
		output_.append(duration_unit<Dur>());
		start_ = steady_clock::time_point{};  // Reset for potential reuse
		return output_;
	}

	/**
	 * @brief Checks if the stopwatch has been started
	 * @return true if run() has been called, false otherwise
	 */
	bool is_running() const {
		return start_ != steady_clock::time_point{};
	}

	stopwatch() = default;
	// Copy prohibition
	stopwatch(const stopwatch&) = delete;
	stopwatch& operator=(const stopwatch&) = delete;

private:
	std::string output_;                     ///< Output string storage
	steady_clock::time_point start_;         ///< Timestamp of the start measurement
};
