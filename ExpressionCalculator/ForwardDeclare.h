#pragma once
#include "Token.h"
#include <memory>

using CBaseTokenPtr = std::shared_ptr<CBaseToken>;
using COperationTokenPtr = std::shared_ptr<COperationToken>;
using CNumberTokenPtr = std::shared_ptr<CNumberToken>;