#pragma once

#include "logger/logger.h"
#include "token.h"
#include "functions/stringFunctions.h"

class Lexer
{
public:
	Lexer(std::string&& code, std::vector<std::string>&& separators) noexcept;

	std::vector<Token> tokenize() noexcept;

private:

	void process() noexcept;

	void line_break() noexcept;
	void space_symbol() noexcept;
	void slash() noexcept;
	void process_next_word() noexcept;
	void add_any_word() noexcept
	{
		if (!anyWord.empty()) {
			res.emplace_back(std::move(anyWord), currentNumberLine);
		}
	}
	void handling_when_quote_is_open() noexcept;

	size_t size_next_operator() noexcept;

	bool is_end() const noexcept
	{
		return i > code.size() - 1;
	}
	bool is_not_last_and_not_more() const noexcept
	{
		return i < code.size() - 1;
	}

private:
	std::string code;
	const std::vector<std::string> separators;

	std::vector<Token> res;
	size_t currentNumberLine = 1;
	bool isOpenQuotes = false;
	size_t i = 0;
	std::string anyWord;
};