#pragma once

#include <EngineError.hpp>

namespace data
{

class InvalidDatasetKeyError : public EngineError
{
	public:
	using EngineError::EngineError;
};

}
