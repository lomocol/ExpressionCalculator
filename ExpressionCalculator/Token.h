#pragma once
#include "Common.h"
#include <iostream>
#include <string>

class CBaseToken
{
public:
	CBaseToken(ETokenType type) : m_type(type) {};
	~CBaseToken() = default;
public:
	ETokenType getType() const { return m_type; };
	virtual std::string toString() const;
private:
	ETokenType m_type = ETokenType::UNKNOWN;
};

class CNumberToken : public CBaseToken
{
public:
	CNumberToken(ETokenType type, float value) : CBaseToken(type), m_value(value) {};
	~CNumberToken() = default;
public:
	float getValue() const { return m_value; };
	virtual std::string toString() const ;
private:
	float m_value = 0.0f;
};

class COperationToken : public CBaseToken
{
public:
	COperationToken(ETokenType type, EOperations operationType) : CBaseToken(type), m_operationType(operationType) 
	{
		if (operationType == EOperations::ADDITION || operationType == EOperations::SUBSTRACTION)
			m_precedence = 1u;
		else
		if (operationType == EOperations::DIVISION || operationType == EOperations::MULTIPLICATION)
			m_precedence = 2u;
	};
	~COperationToken() = default;
public:
	EOperations getOperationType() const { return m_operationType; };
	std::uint8_t getPrecedence() const { return m_precedence; };

	virtual std::string toString() const;
private:
	EOperations m_operationType = EOperations::UNKNOWN;
	std::uint8_t m_precedence = 0u;
};

