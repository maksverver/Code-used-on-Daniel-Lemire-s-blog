#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

namespace {

#include "../include/digitcount.h"

static int CountDigitsNaive(uint64_t u) {
	int n = 1;
	while (u >= 10) u /= 10, ++n;
	return n;
}

template<class T> 
constexpr std::vector<std::pair<T, int>> GenerateTestCases() {
	std::vector<std::pair<T, int>> res;

  // Add special case 0 which has 1 digit
	res.push_back({0, 1});

  // Add numbers near powers of 10.
	const T LIM = std::numeric_limits<T>::max();
	T min = 1;
	for (int n = 1; ; ++n) {
		// Invariants:
    //  min is the minimum representable integer with exactly `n` digits
    //  max is the maximum representable integer with exactly `n` digits
		T max = min < LIM / 10 ? min * 10 - 1 : LIM;
		if (max - min + 1 < 1000) {
      // For small ranges, include all numbers in range.
			for (T i = min; i <= max; ++i) {
				res.push_back({i, n});
			}
		} else {
      // For larger ranges, include the first 100 numbers in range,
      // the last 100 numbers in range, and then some numbers in the middle.
			for (T i = min; i < min + 100; ++i) {
				res.push_back({i, n});
			}
			T step = (max - min + 1 - 200) / 797;
			for (int x = 1; x < 797; ++x) {
				T i = min + 100 + step*x;
				res.push_back({i, n});
			}
			for (T i = max - 100; i++ != max; ) {
				res.push_back({i, n});
			}
		}
		if (max == LIM) break;
		min = max + 1;
	}

	// Add numbers near powers of 2. We can start at 2048 because numbers
	// up to 1100 were all included above.
	for (int i = 11; i < std::numeric_limits<T>::digits; ++i) {
		T x = T{1} << i;
		for (T i = x - 5; i <= x + 5; ++i) {
			res.push_back({i, CountDigitsNaive(i)});
		}
	}

	return res;
}

template<class T> struct Test {
	std::vector<std::pair<T, int>> cases = GenerateTestCases<T>();

	int Validate(const char *name, int (*f)(T)) {
		int failures = 0;
		for (auto [input, expected] : cases) {
			int received = f(input);
			bool failed = expected != received;
			failures += failed;
			if (failed) {
				std::cerr << name
					<< " (" << std::numeric_limits<T>::digits << " bits) "
					<< " input=" << std::setw(20) << input
					<< " expected=" << std::setw(3) << expected
					<< " received=" << std::setw(3) << received
					<< ' ' << (failed ? "OK" : "FAILED!")
					<< std::endl;
			}
		}
		return failures;
	}
};

}  // namespace

int main() {
	int failures = 0;

	Test<uint32_t> test32;
	Test<uint64_t> test64;

	failures += test32.Validate("digit_count", digit_count);
	failures += test64.Validate("digit_count", digit_count);
	failures += test32.Validate("alternative_digit_count", alternative_digit_count);
	failures += test64.Validate("alternative_digit_count", alternative_digit_count);
	failures += test64.Validate("split_table_digit_count", split_table_digit_count);
	failures += test64.Validate("fast_digit_count", fast_digit_count);
	failures += test32.Validate("fast_digit_count", fast_digit_count);

	if (failures > 0) {
		std::cerr << failures << " failures!\n";
		return EXIT_FAILURE;
	}
	std::cerr << "All tests pass.\n";
}
