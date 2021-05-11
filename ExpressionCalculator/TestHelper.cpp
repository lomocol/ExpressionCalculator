#include "TestHelper.h"
#include "ExpressionParser.h"

void TestHelper::runAllTests()
{
	//RUN_TEST(runner, &TestHelper::runSpelling);
}

void TestHelper::runSpeedTests()
{
	auto expressionCreator = [](size_t size, const std::string& baseExpression) -> std::string
	{
		std::string expression = "";
		for (size_t i = 0; i < size; i++)
		{
			expression += baseExpression;
			expression += '*';
		}

		expression.pop_back();
		return expression;
	};

	int stringSize1 = 10;
	int stringSize2 = 100;
	int stringSize3 = 1000;

	std::string baseExpression = "(2.03 - 4.34 - (23.34 * 324.34 / 21.34) - 228.34 + 43.34 - (21.34 * 789,91 / (21,91) - 2,91)) / (98,90 / (2,91 - 4,91 - (23,91 * 324,91 / 21) - 228,91 + 43,91))";

	const int epoch = 100;
	{
		auto expression = expressionCreator(stringSize1, baseExpression);
		LOG_DURATION("10 lines");

		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = ExpressionParser::parseExpression(expression);
			auto result = ExpressionParser::calculateExpression(resultQueue);
		}
	}
	{
		auto expression = expressionCreator(stringSize2, baseExpression);
		LOG_DURATION("100 lines");

		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = ExpressionParser::parseExpression(expression);
			auto result = ExpressionParser::calculateExpression(resultQueue);
		}
	}
	{
		auto expression = expressionCreator(stringSize3, baseExpression);
		LOG_DURATION("1000 lines");
		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = ExpressionParser::parseExpression(expression);
			auto result = ExpressionParser::calculateExpression(resultQueue);
		}
	}
}

void TestHelper::runSpelling()
{


}
