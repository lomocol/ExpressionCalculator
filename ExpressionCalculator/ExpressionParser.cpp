#include "ExpressionParser.h"
#include <string_view>


std::queue<CBaseTokenPtr> ExpressionParser::parseExpression(const std::string& exp)
{
	auto strw = std::string_view{ exp };
	auto mStack = std::stack<CBaseTokenPtr>{};
	auto mQueue = std::queue<CBaseTokenPtr>{};
	auto str = std::string{};

	while (!strw.empty())
	{
		const auto token = getNextToken(strw);

		if (token == nullptr)
			continue;;
			//throw std::exception("WRONG TOKEN");

		switch (token->getType())
		{
		case ETokenType::NUMBER:
		{
			//std::cout << "Add token to output :" << token->toString() << std::endl;
			mQueue.push(token);
		}
		break;
		case ETokenType::OPERATOR:
		{
			processOperator(mStack, mQueue, token);
		}
		break;
		case ETokenType::LEFT_PARENTHESIS:
		{
			//std::cout << "Push token to stack :" << token->toString() << std::endl;
			mStack.push(token);
		}
		break;
		case ETokenType::RIGHT_PARENTHESIS:
		{
			processRightParenthesis(mStack, mQueue, token);
		}
		break;
		case ETokenType::UNKNOWN:
		{
			throw std::exception("UNKNOWN TOKEN");
		}
		break;
		default:
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

		//std::cout << "Pop token from stack :" << mStack.top()->toString() << std::endl;
		//std::cout << "Push token to output :" << mStack.top()->toString() << std::endl;
		mQueue.push(mStack.top());
		mStack.pop();
	}

	if (!mStack.empty())
		throw std::exception("Too many operators or something else;");

	return mQueue;
}

CBaseTokenPtr ExpressionParser::getNextToken(std::string_view& sv)
{
	CBaseTokenPtr token = nullptr;

	const auto firstInd = sv.find_first_not_of(' ', 0);

	if (firstInd == std::string::npos)
		return token;

	sv.remove_prefix(firstInd);
	const char symbol = sv.front();
	if (symbol == '(')
	{
		token = std::make_shared<CBaseToken>(ETokenType::LEFT_PARENTHESIS);
		sv.remove_prefix(1);
	}
	else
		if (symbol == ')')
		{
			token = std::make_shared<CBaseToken>(ETokenType::RIGHT_PARENTHESIS);
			sv.remove_prefix(1);
		}
		else
			if (isNumber(symbol))
			{
				const float number = toNumber(sv);
				token = std::make_shared<CNumberToken>(ETokenType::NUMBER, number);
			}
			else
			{
				auto operand = isOperator(symbol);
				if (operand != EOperations::UNKNOWN)
				{
					token = std::make_shared<COperationToken>(ETokenType::OPERATOR, operand);
				}
				else
				{
					if(symbol != ' ' && symbol != '\n')
						throw std::exception("Wrong Operator");
				}
				sv.remove_prefix(1);
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

float ExpressionParser::toNumber(std::string_view& sv)
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

bool ExpressionParser::firstIsGreater(const CBaseTokenPtr first, const CBaseTokenPtr second)
{
	auto first_type = std::static_pointer_cast<COperationToken>(first);
	auto second_type = std::static_pointer_cast<COperationToken>(second);
	auto result = first_type->getPrecedence() > second_type->getPrecedence();
	return result;
}

bool ExpressionParser::areEqual(const CBaseTokenPtr first, const CBaseTokenPtr second)
{
	auto first_type = std::static_pointer_cast<COperationToken>(first);
	auto second_type = std::static_pointer_cast<COperationToken>(second);
	auto result = first_type->getPrecedence() == second_type->getPrecedence();
	return result;
}

bool ExpressionParser::leftAssociative(const CBaseTokenPtr first)
{
	return true;
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
		(firstIsGreater(mStack.top(), token) || (areEqual(mStack.top(), token) && leftAssociative(token))))
	{
		//std::cout << "Pop token from stack :" << mStack.top()->toString() << std::endl;
		//std::cout << "Push token to output :" << mStack.top()->toString() << std::endl;
		mQueue.push(mStack.top());
		mStack.pop();
	}
	//std::cout << "Push token to stack :" << token->toString() << std::endl;
	mStack.push(token);
}

void ExpressionParser::processRightParenthesis(std::stack<CBaseTokenPtr>& mStack, std::queue<CBaseTokenPtr>& mQueue, CBaseTokenPtr token)
{
	while (mStack.top()->getType() != ETokenType::LEFT_PARENTHESIS)
	{
		//std::cout << "Pop token from stack :" << mStack.top()->toString() << std::endl;
		//std::cout << "Push token to output :" << mStack.top()->toString() << std::endl;
		mQueue.push(mStack.top());
		mStack.pop();
		if (mStack.empty())
			throw std::exception("To many '}'");
	}
	if (mStack.top()->getType() == ETokenType::LEFT_PARENTHESIS)
	{
		//std::cout << "Pop token from stack :" << mStack.top()->toString() << std::endl;
		mStack.pop();
	}
}

float ExpressionParser::calculateExpression(std::queue<CBaseTokenPtr>& mQueue)
{
	std::stack<CBaseTokenPtr> mStack{};

	while (!mQueue.empty())
	{
		const auto frontToken = mQueue.front();
		if (frontToken->getType() == ETokenType::NUMBER)
		{
			mStack.push(frontToken);
		}else
			if (frontToken->getType() == ETokenType::OPERATOR)
			{
				if (mQueue.size() < 10)
					int x = 5;
				auto second = std::static_pointer_cast<CNumberToken>(mStack.top())->getValue();
				mStack.pop();
				auto first = std::static_pointer_cast<CNumberToken>(mStack.top())->getValue();
				mStack.pop();
				auto result = std::static_pointer_cast<COperationToken>(frontToken)->applyOperator(first, second);
				mStack.push(std::make_shared<CNumberToken>(ETokenType::OPERATOR, result));
			}

		mQueue.pop();
	}

	return std::static_pointer_cast<CNumberToken>(mStack.top())->getValue();
}
