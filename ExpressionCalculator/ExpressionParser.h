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
public:
	static std::string parseExpression(const std::string& expression);

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

