#pragma once
#include "ILogger.h"

class ConsoleLogger final : public ILogger {
public:
	ConsoleLogger();
	virtual ~ConsoleLogger();
	virtual void Log(char* message) override;
};