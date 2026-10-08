#include <iostream>
#include "stopwatch.h"

/**
 * @brief Entry point of the application
 * @return Exit code (0 for success)
 */
int main() {
	size_t n = 0;                                          ///< Loop counter
	std::string result = "duration: ";                     ///< String to accumulate output

	{
		// Create stopwatch timer measuring in nanoseconds
		stopwatch<std::chrono::nanoseconds> sw(result);

		// Measured code section - simple loop operation
		while (n < 100000) {
			if (n & 1)
				n += 1;
			n += 1;
		}
	}                                                      // Stopwatch destructor records duration here

	std::cout << result << "\n";                           // Print measurement result
	return 0;                                              // Successful termination
}
