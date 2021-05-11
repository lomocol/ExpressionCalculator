#pragma once

#include "test_runner.h"
#include "profile.h"

class TestHelper
{
public:
	void runAllTests();
	void runSpeedTests();
private:
	void runSpelling();

private:
	TestRunner runner = {};
};

