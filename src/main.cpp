#include <iostream>
#include "stopwatch.h"

/**
 * @brief Scope timer class that automatically prints duration on destruction
 * 
 * Inherits from stopwatch and automatically outputs the measured time
 * when the object goes out of scope. Implements the scope guard pattern.
 */
template<typename Dur = std::chrono::nanoseconds>
class scope_timer : public stopwatch<Dur> {
public:
	/**
	 * @brief Constructs scope_timer and starts measuring with "duration: " prefix
	 */
	scope_timer() {
		run("duration: ");
	}

	/**
	 * @brief Destructor - stops timer and prints the elapsed time
	 */
	~scope_timer() {
		std::cout << stop() << "\n";
	}
};

/**
 * @brief Entry point of the application
 * @return Exit code (0 for success)
 */
int main() {
	size_t n = 0;        ///< Loop counter

	// Create scope timer measuring in nanoseconds
	scope_timer st;

	// Measured code section - simple loop operation
	while (n < 100000) {
		if (n & 1)
			n += 1;
		n += 1;
	}

	//std::cout << "measuring complete\n";

	return 0;
}
