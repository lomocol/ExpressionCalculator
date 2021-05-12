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

class CFloatNumberToken : public CBaseToken
{
public:
	CFloatNumberToken(float value) : CBaseToken(ETokenType::FLOAT_NUMBER), m_value(value) {};
	~CFloatNumberToken() = default;
public:
	float getValue() const { return m_value; };
	virtual std::string toString() const ;
private:
	float m_value = 0.0f;
};

class CIntNumberToken : public CBaseToken
{
public:
	CIntNumberToken(int value) : CBaseToken(ETokenType::INTEGER_NUMBER), m_value(value) {};
	~CIntNumberToken() = default;
public:
	int getValue() const { return m_value; };
	virtual std::string toString() const { return std::to_string(m_value); };
private:
	int m_value = 0;
};

class COperationToken : public CBaseToken
{
public:
	COperationToken(EOperations operationType) ;
	~COperationToken() = default;
public:
	EOperations getOperationType() const { return m_operationType; };
	std::uint8_t getPrecedence() const { return m_precedence; };
	float applyOperator(float left, float right) const;
	int applyOperator(int left, int right) const;
	virtual std::string toString() const;
private:
	EOperations m_operationType = EOperations::UNKNOWN;
	std::uint8_t m_precedence = 0u;
};

