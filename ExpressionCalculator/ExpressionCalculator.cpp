#include "ExpressionParser.h"
#include "TestHelper.h"
#include <iostream>
#include <vector>

int main()
{
	std::string in = "";
	std::getline(std::cin, in);
	if (in == "tests")
	{
		auto testHelper = TestHelper();
		testHelper.runAllTests();
	}
	else
	{
		try {
			auto result = Parser().calculateExpression(in);
			std::cout << "Result: " << result << '\n';
		}
		catch (std::exception& e) {
			std::cerr << "Wrong expression: " << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "Unknown exception caught" << std::endl;
		}

	}
}