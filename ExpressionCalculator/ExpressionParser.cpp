#include "ExpressionParser.h"
#include <string_view>


std::queue<CBaseTokenPtr> ExpressionParser::parseExpression(const std::string& exp)
{
	auto strw = std::string_view{ exp };
	auto mStack = std::stack<CBaseTokenPtr>{};
	auto mQueue = std::queue<CBaseTokenPtr>{};

	bool canBeNegativeNumber = true;
	while (!strw.empty())
	{
		const auto token = getNextToken(strw, canBeNegativeNumber);

		if (token == nullptr)
			continue;

		switch (token->getType())
		{
		case ETokenType::FLOAT_NUMBER:
		case ETokenType::INTEGER_NUMBER:
		{
			mQueue.push(token);
			canBeNegativeNumber = false;
		}
		break;
		case ETokenType::OPERATOR:
		{
			processOperator(mStack, mQueue, token);
			canBeNegativeNumber = true;
		}
		break;
		case ETokenType::LEFT_PARENTHESIS:
		{
			mStack.push(token);
			canBeNegativeNumber = true;
		}
		break;
		case ETokenType::RIGHT_PARENTHESIS:
		{
			processRightParenthesis(mStack, mQueue, token);
			canBeNegativeNumber = false;
		}
		break;
		case ETokenType::UNKNOWN:
		{
			throw std::exception("UNKNOWN TOKEN");
		}
		break;
		}
	}

	while (!mStack.empty())
	{
		if (mStack.top()->getType() == ETokenType::LEFT_PARENTHESIS ||
			mStack.top()->getType() == ETokenType::RIGHT_PARENTHESIS)
		{
			throw std::exception("Extra Parenthesis");
		}

		mQueue.push(mStack.top());
		mStack.pop();
	}

	if (!mStack.empty())
		throw std::exception("Too many operators or something else;");

	return mQueue;
}

CBaseTokenPtr ExpressionParser::getNextToken(std::string_view& sv, bool canBeNegativeNumber)
{
	CBaseTokenPtr token = nullptr;

	const auto firstInd = sv.find_first_not_of(' ', 0);

	if (firstInd == std::string::npos)
		return token;

	sv.remove_prefix(firstInd);
	const char symbol = sv.front();

	if (isNumber(symbol))
	{
		token = makeNumberToken(sv, false);
	}
	else
		if (symbol == ')')
		{
			token = std::make_shared<CBaseToken>(ETokenType::RIGHT_PARENTHESIS);
			sv.remove_prefix(1);
		}
		else
			if (symbol == '(')
			{
				token = std::make_shared<CBaseToken>(ETokenType::LEFT_PARENTHESIS);
				sv.remove_prefix(1);
			}
			else
			{
				auto operand = isOperator(symbol);
				if (operand != EOperations::UNKNOWN)
				{
					if (operand == EOperations::SUBSTRACTION && canBeNegativeNumber)
					{
						sv.remove_prefix(1);
						if (!sv.empty() && isNumber(sv.front()))
						{
							token = makeNumberToken(sv, true);
						}
					}
					else
					{
						token = std::make_shared<COperationToken>(ETokenType::OPERATOR, operand);
						sv.remove_prefix(1);
					}
				}
				else
				{
					if(symbol != ' ')
						throw std::exception("Wrong Operator");
					sv.remove_prefix(1);
				}
			}
				
	return token;
}

bool ExpressionParser::isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

EOperations ExpressionParser::isOperator(char ch)
{
	if (ch == '*')
	{
		return EOperations::MULTIPLICATION;
	}else
		if (ch == '/')
		{
			return EOperations::DIVISION;
		}
		else
			if (ch == '+')
			{
				return EOperations::ADDITION;
			}
			else
				if (ch == '-')
				{
					return EOperations::SUBSTRACTION;
				}

	return EOperations::UNKNOWN;
}

float ExpressionParser::toFloat(std::string_view& sv, size_t pointPosition)
{
	float rank = 1u;

	float number = 0.0f;
	while (!sv.empty() && isNumber(sv.front()))
	{
		rank *= 10u;
		int x = sv.front() - '0';
		number += x / rank;

		sv.remove_prefix(1);
	}
	number *= rank;

	if (sv.empty())
		return number;

	if (sv.front() == '.' || sv.front() == ',')
	{
		sv.remove_prefix(1);

		float digitsAfterPoint = 1u;

		while (!sv.empty() && isNumber(sv.front()))
		{
			digitsAfterPoint *= 10u;

			int x = sv.front() - '0';
			number += x / digitsAfterPoint;

			sv.remove_prefix(1);
		}

		if (digitsAfterPoint == 1u)
			throw std::exception("0 digist after point!");
	}

	return number;
}

bool ExpressionParser::firstIsGreaterOrEqual(const CBaseTokenPtr first, const CBaseTokenPtr second)
{
	const auto first_type = std::static_pointer_cast<COperationToken>(first);
	const auto second_type = std::static_pointer_cast<COperationToken>(second);
	const auto result = first_type->getPrecedence() >= second_type->getPrecedence();
	return result;
}

bool ExpressionParser::areEqual(const CBaseTokenPtr first, const CBaseTokenPtr second)
{
	auto first_type = std::static_pointer_cast<COperationToken>(first);
	auto second_type = std::static_pointer_cast<COperationToken>(second);
	auto result = first_type->getPrecedence() == second_type->getPrecedence();
	return result;
}

size_t ExpressionParser::findFirstNotNumber(const std::string_view& sv)
{
	size_t position = std::string::npos;
	for (size_t i = 0; i < sv.size(); i++)
	{
		if (!isNumber(sv[i]))
		{
			position = i;
			break;
		}
	}

	return position;
}

size_t ExpressionParser::findPoint(const std::string_view& sv, size_t offset)
{
	size_t position = std::string::npos;
	for (size_t i = offset; i < sv.size(); i++)
	{
		if (sv[i] == '.' || sv[i] == ',')
		{
			position = i;
			break;
		}
		else
		{
			if (!isNumber(sv[i]))
			{
				break;
			}
		}
	}

	return position;
}

size_t ExpressionParser::parseNumber(const std::string_view& sv, size_t numbersNum)
{
	size_t number = 0u;
	size_t rank = 1u;
	for (int i = numbersNum - 1; i >= 0; i--)
	{
		size_t tmpNumber = sv[i] - '0';
		number += tmpNumber * rank;
		rank *= 10u;
	}
	return number;
}

float ExpressionParser::parseFloatingPart(const std::string_view& sv, size_t numbersNum)
{
	float number = 0u;
	size_t rank = 10u;
	for (size_t i = 0 ; i < numbersNum; i++)
	{
		size_t tmpNumber = sv[i] - '0';
		number += tmpNumber / rank;
		rank *= 10u;
	}
	return number;
}

size_t ExpressionParser::powerOfTen(size_t power)
{
	size_t number = 1u;
	for (size_t i = 0; i < power; i++)
	{
		number *= 10u;
	}
	return number;
}


std::string ExpressionParser::toString(std::queue<CBaseTokenPtr> queue)
{
	std::string str{};
	while (!queue.empty())
	{
		str += queue.front()->toString();
		str += ' ';
		queue.pop();
	}

	return str;
}

void ExpressionParser::processOperator(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token)
{
	while (!mStack.empty() &&
		mStack.top()->getType() != ETokenType::LEFT_PARENTHESIS &&
		(firstIsGreaterOrEqual(mStack.top(), token)))
	{
		mQueue.push(mStack.top());
		mStack.pop();
	}
	mStack.push(token);
}

void ExpressionParser::processRightParenthesis(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token)
{
	while (mStack.top()->getType() != ETokenType::LEFT_PARENTHESIS)
	{
		mQueue.push(mStack.top());
		mStack.pop();
		if (mStack.empty())
			throw std::exception("To many '}'");
	}

	if (mStack.top()->getType() == ETokenType::LEFT_PARENTHESIS)
	{
		mStack.pop();
	}
}

float ExpressionParser::parseFloat(std::string_view& sv, bool minus, size_t pointPos)
{
	auto integerPart = parseNumber(sv, pointPos);
	sv.remove_prefix(pointPos + 1);
	auto numbersAfterPoint = findFirstNotNumber(sv);

	if (numbersAfterPoint == 0)
		throw std::exception("Empty after point part of number");

	if (numbersAfterPoint == std::string::npos)
		numbersAfterPoint = sv.size();

	auto floatingPart = parseFloatingPart(sv, numbersAfterPoint);
	sv.remove_prefix(numbersAfterPoint);

	float result = integerPart + floatingPart;

	if (minus)
		result *= -1;
	return result;
}

CBaseTokenPtr ExpressionParser::makeNumberToken(std::string_view& sv, bool minusFirst)
{
	CBaseTokenPtr token = nullptr;
	const auto pointPos = findPoint(sv, minusFirst);

	// parse float
	if (pointPos != std::string::npos)
	{
		float number = parseFloat(sv, minusFirst, pointPos);
		token = std::make_shared<CFloatNumberToken>(number);
	}
	// parse integer number
	else
	{
		int number = parseInteger(sv, minusFirst);
		token = std::make_shared<CIntNumberToken>(number);
	}

	return token;
}

int ExpressionParser::parseInteger(std::string_view& sv, bool minus)
{
	auto numberOfNumbers = findFirstNotNumber(sv);
	if (numberOfNumbers == std::string::npos)
		numberOfNumbers = sv.size();

	int number = parseNumber(sv, numberOfNumbers);
	sv.remove_prefix(numberOfNumbers);
	if (minus)
		number *= -1;
	return number;
}

float ExpressionParser::calculateExpression(std::queue<CBaseTokenPtr>&& mQueue)
{
	std::stack<CBaseTokenPtr> mStack{};

	while (!mQueue.empty())
	{
		const auto frontToken = mQueue.front();
		if (frontToken->getType() == ETokenType::INTEGER_NUMBER || frontToken->getType() == ETokenType::FLOAT_NUMBER)
		{
			mStack.push(frontToken);
		}else
			if (frontToken->getType() == ETokenType::OPERATOR)
			{
				const auto second = std::static_pointer_cast<CFloatNumberToken>(mStack.top())->getValue();
				mStack.pop(); 

				float first = std::static_pointer_cast<CFloatNumberToken>(mStack.top())->getValue();
				mStack.pop();

				const auto result = std::static_pointer_cast<COperationToken>(frontToken)->applyOperator(first, second);
				mStack.push(std::make_shared<CFloatNumberToken>(result));
			}

		mQueue.pop();
	}

	return std::static_pointer_cast<CFloatNumberToken>(mStack.top())->getValue();
}

float ExpressionParser::calculateExpression(const std::string& expression)
{
	auto mQueue = parseExpression(expression);
	return calculateExpression(std::move(mQueue));
}
