#pragma once

#include "test_runner.h"
#include "profile.h"

class TestHelper
{
public:
	void runAllTests();
private:
	static void runCompleteSpeedTests();
	static void runParsingTests();
	static void runCalculationTest();
};

