#pragma once
#include "Common.h"
#include "ForwardDeclare.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <string>

static class ExpressionParser
{
	friend class TestHelper;
public:
	static std::queue<CBaseTokenPtr> parseExpression(const std::string& expression);
	static float calculateExpression(std::queue<CBaseTokenPtr>& mQueue);
	static std::string toString(std::queue<CBaseTokenPtr> queue);

private:
	static CBaseTokenPtr getNextToken(std::string_view& sv);
	static bool isNumber(char);
	static EOperations isOperator(char);
	static float toNumber(std::string_view& sv);
	static void processOperator(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token);
	static void processRightParenthesis(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token);

	// comparison
	static bool firstIsGreater(const CBaseTokenPtr first, const CBaseTokenPtr second);
	static bool areEqual(const CBaseTokenPtr first, const CBaseTokenPtr second);
	static bool leftAssociative(const CBaseTokenPtr first);
private:
	ExpressionParser() = default;
};

