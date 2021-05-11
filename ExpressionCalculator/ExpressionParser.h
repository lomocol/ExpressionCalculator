#pragma once
#include "Common.h"
#include "ForwardDeclare.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <string>

#define Parser() ExpressionParser::getInstance()

class ExpressionParser
{
	friend class TestHelper;
public:

	static ExpressionParser& getInstance() 
	{
		static ExpressionParser parser{};
		return parser;
	};
	float calculateExpression(const std::string& expression);

	std::queue<CBaseTokenPtr> parseExpression(const std::string& expression);
	float calculateExpression(std::queue<CBaseTokenPtr>&& mQueue);
	std::string toString(std::queue<CBaseTokenPtr> queue);
private:

	CBaseTokenPtr getNextToken(std::string_view& sv, bool operatorWasBefore);
	bool isNumber(char);
	EOperations isOperator(char);
	float toFloat(std::string_view& sv, size_t pointPosition);
	void processOperator(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token);
	void processRightParenthesis(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token);

	CBaseTokenPtr makeNumberToken(std::string_view& sv, bool minusFirst);

	// comparison
	bool firstIsGreaterOrEqual(const CBaseTokenPtr first, const CBaseTokenPtr second);
	bool areEqual(const CBaseTokenPtr first, const CBaseTokenPtr second);

	size_t findFirstNotNumber(const std::string_view& sv);
	size_t parseNumber(const std::string_view& sv, size_t numbersNum);
	size_t powerOfTen(size_t power);

	// parse integer
	int parseInteger(std::string_view& sv, bool minus);

	//float parse
	size_t findPoint(const std::string_view& sv, size_t offset);
	float parseFloat(std::string_view& sv, bool minus, size_t pointPos);
	float parseFloatingPart(const std::string_view& sv, size_t numbersNum);
private:
	ExpressionParser() = default;
};

