#include "ExpressionParser.h"
#include "TestHelper.h"
#include <iomanip>

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
			std::string resultStr{ std::to_string(result) };

			// round
			const auto precision = 2u;
			result = std::round(result * std::pow(10, precision)) / std::pow(10, precision);

			auto pos = resultStr.find('.');
			if (pos != std::string::npos)
			{
				const auto numsAfterPoint = resultStr.size() - pos - 1;
				if (numsAfterPoint > precision)
				{
					const auto numsToErase = numsAfterPoint - precision;
					resultStr.erase(std::prev(resultStr.end(), resultStr.size() - numsAfterPoint - 1), resultStr.end());
				}
			}

			std::cout << "Result: " << resultStr << '\n';
		}
		catch (std::exception& e) {
			std::cerr << "Wrong expression: " << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}
}