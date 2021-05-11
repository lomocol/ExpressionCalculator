#include "ExpressionParser.h"
#include "TestHelper.h"
#include <iostream>
#include <vector>

int main()
{
	auto testHelper = TestHelper();
	testHelper.runAllTests();
	//testHelper.runCompleteSpeedTests();
	//std::string in = "-21 - (-21)";
	//std::getline(std::cin, in);
	/*auto queue = ExpressionParser::parseExpression(in);
	std::cout << ExpressionParser::toString(queue) << '\n';
	auto result = ExpressionParser::calculateExpression(std::move(queue));
	std::cout << "Result: " << result << '\n';*/


	//std::string in{};
	//std::getline(std::cin, in);
	//auto queue = ExpressionParser::parseExpression(in);
	//std::cout << ExpressionParser::toString(queue) << '\n';
}