#include "Token.h"

COperationToken::COperationToken(ETokenType type, EOperations operationType) : CBaseToken(type), m_operationType(operationType)
{
    if (operationType == EOperations::ADDITION || operationType == EOperations::SUBSTRACTION)
	{
		m_precedence = 1u;
    }
    else
    if (operationType == EOperations::DIVISION || operationType == EOperations::MULTIPLICATION)
	{
		m_precedence = 2u;
    }
}

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
    case EOperations::UNKNOWN:
        throw std::exception("Wrong operator was tried to be applied");
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
	}
	return std::string() += ch;
}

std::string CFloatNumberToken::toString() const
{
    std::string result = std::to_string(m_value);
    result.erase(std::prev(result.end(), 7), result.end());

    return result;
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
