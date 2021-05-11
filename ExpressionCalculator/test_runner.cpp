#include "test_runner.h"

void AssertEqualFloats(float t, float u, const std::string& hint /*= {}*/)
{
	const float precision = 0.00001f;
	if ((t - u) > precision) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

