#include "Token.h"

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
    result.pop_back();

    return  result;
}
