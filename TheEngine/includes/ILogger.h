#pragma once

class ILogger {
public:
	virtual void Log(char* message) = 0;
	virtual ~ILogger() = default;
};