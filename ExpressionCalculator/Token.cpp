#include "Token.h"

float COperationToken::applyOperator(float left, float right) const
{
	switch (m_operationType)
	{
	case EOperations::SUBSTRACTION:
        return left - right;
		break;
	case EOperations::ADDITION:
		return left + right;
		break;
	case EOperations::DIVISION:
		return left / right;
		break;
	case EOperations::MULTIPLICATION:
		return left * right;
		break;
	}
	return 0.0f;
}

std::string COperationToken::toString() const
{
    char ch = '_';
	switch (m_operationType)
	{
    case EOperations::SUBSTRACTION:
        ch = '-';
        break;
    case EOperations::ADDITION:
        ch = '+';
        break;
    case EOperations::DIVISION:
        ch = '/';
        break;
    case EOperations::MULTIPLICATION:
        ch = '*';
        break;
    case EOperations::UNKNOWN:
        ch = '?';
        break;
    default:
        break;
	}
	return std::string() += ch;
}

std::string CNumberToken::toString() const
{
    std::string result = std::to_string(m_value);
    result.pop_back();
    result.pop_back();
    result.pop_back();
    result.pop_back();
    //result.pop_back();
    //result.pop_back();
    //result.pop_back();

    return  result;
}

std::string CBaseToken::toString() const
{
    if (m_type == ETokenType::LEFT_PARENTHESIS)
        return "(";
    else
        if (m_type == ETokenType::RIGHT_PARENTHESIS)
            return ")";
        else
            return "?";
}
