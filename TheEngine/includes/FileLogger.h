#pragma once
#include "ILogger.h"

class FileLogger final : public ILogger {
public:
	virtual ~FileLogger() = default;
	virtual void Log(char* message) override;
};