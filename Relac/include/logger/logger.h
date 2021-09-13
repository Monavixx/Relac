#pragma once

#include <mutex>

#include <fmt/core.h>
#include <fmt/color.h>



class Logger
{
public:
	enum class Type
	{
		NOTE,
		WARNING,
		ERROR
	};

public:
	Logger(Type type) noexcept : type(type)
	{
	}

	template<class ...Args>
	void log(Args&&... args) noexcept
	{
		mutex.lock();

		fmt::text_style ts;
		std::string typeStr;
		switch (type)
		{
		case Logger::Type::NOTE:
			ts = fmt::emphasis::bold | fmt::fg(fmt::color::aqua);
			typeStr = "[NOTE] ";
			break;
		case Logger::Type::WARNING:
			ts = fmt::emphasis::bold | fmt::fg(fmt::color::yellow);
			typeStr = "[WARNING] ";
			break;
		case Logger::Type::ERROR:
			ts = fmt::emphasis::bold | fmt::fg(fmt::color::red);
			typeStr = "[ERROR] ";
			break;
		}
		
		print(std::move(ts), "{}", typeStr + std::string(std::forward<Args>(args)...) + "\n");
		mutex.unlock();
	}

private:
	Type type;
	std::mutex mutex;


private:
	static inline Logger* _note;
	static inline Logger* _warning;
	static inline Logger* _error;

public:
	static Logger& note() noexcept
	{
		if (_note == nullptr)
			_note = new Logger(Type::NOTE);
		return *_note;
	}
	static Logger& warning() noexcept
	{
		if (_warning == nullptr)
			_warning = new Logger(Type::WARNING);
		return *_warning;
	}
	static Logger& error() noexcept
	{
		if (_error == nullptr)
			_error = new Logger(Type::ERROR);
		return *_error;
	}
};