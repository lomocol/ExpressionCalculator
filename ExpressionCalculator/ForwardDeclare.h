#pragma once
#include "Token.h"
#include <memory>

using CBaseTokenPtr = std::shared_ptr<CBaseToken>;
using COperationTokenPtr = std::shared_ptr<COperationToken>;
using CFloatNumberTokenPtr = std::shared_ptr<CFloatNumberToken>;
using CIntNumberTokenPtr = std::shared_ptr<CIntNumberToken>;