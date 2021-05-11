#include "TestHelper.h"
#include "ExpressionParser.h"

#include <numeric>

void TestHelper::runAllTests()
{
	TestRunner runner{};
	RUN_TEST(runner, TestHelper::runParsingTests);
	RUN_TEST(runner, TestHelper::runSpelling);
}

void TestHelper::runCompleteSpeedTests()
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

	std::string baseExpression = "- (2.03 - 4.34 - (23.34 * 324.34 / 21.34) - 228.34 + 43.34 - (21.34 * 789,91 / (21,91) - 2,91)) / (98,90 / (2,91 - 4,91 - (23,91 * 324,91 / 21) - 228,91 + 43,91))";

	const int epoch = 100;
	{
		auto expression = expressionCreator(stringSize1, baseExpression);
		LOG_DURATION("10 lines");

		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = Parser().parseExpression(expression);
			auto result = Parser().calculateExpression(std::move(resultQueue));
		}
	}
	{
		auto expression = expressionCreator(stringSize2, baseExpression);
		LOG_DURATION("100 lines");

		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = Parser().parseExpression(expression);
			auto result = Parser().calculateExpression(std::move(resultQueue));
		}
	}
	{
		auto expression = expressionCreator(stringSize3, baseExpression);
		LOG_DURATION("1000 lines");
		for (size_t i = 0; i < epoch; i++)
		{
			auto resultQueue = Parser().parseExpression(expression);
			auto result = Parser().calculateExpression(std::move(resultQueue));
		}
	}
}


void TestHelper::runParsingTests()
{
	{ // integers from 0 to 99
		std::vector<int> numbers(100);
		std::iota(numbers.begin(), numbers.end(), 0);
		for (auto number : numbers)
		{
			std::string str = std::to_string(number);
			std::string_view sv(str);

			auto result = Parser().parseInteger(sv, false);
			ASSERT_EQUAL(result, number);
			ASSERT(sv.empty());
		}
	}
	{ // floats from 0 to 99
		std::vector<float> numbers(100);
		std::iota(numbers.begin(), numbers.end(), 0);
		for (auto number : numbers)
		{
			std::string str = std::to_string(number);
			std::string_view sv(str);

			auto result = Parser().parseFloat(sv, false, std::abs(number) < 10 ? 1 : 2);
			ASSERT_EQUAL_FLOATS(result, number);
			ASSERT(sv.empty());
		}
	}
	{ // parsing some simple exspressions into RPN
		std::vector<std::string> expressions = 
		{
		"3 - 14",
		"-33 * 5",
		"365 / ( 13 + -1)",
		}; 
		
		std::vector<std::string> targets =
		{
		"3 14 - ",
		"-33 5 * ",
		"365 13 -1 + / ",
		};

		for (size_t i = 0; i < expressions.size(); i++)
		{
			const auto& expression = expressions[i];
			auto answerQueue = Parser().parseExpression(expression);
			const auto parserAnswer = Parser().toString(std::move(answerQueue));

			ASSERT_EQUAL(parserAnswer, targets[i]);
		}
	}
}

void TestHelper::runSpelling()
{


}
