#pragma once

#include <stdexcept>

class EngineError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};
