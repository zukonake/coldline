#pragma once

#include <EngineError.hpp>

namespace chunk
{

class InvalidEntityError : public EngineError
{
	public:
	using EngineError::EngineError;
};

}
