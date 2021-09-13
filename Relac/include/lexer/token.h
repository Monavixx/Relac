#pragma once

#include <string>

class Token
{
public:
	enum class Type
	{
		NONE,
		WORD,
		STRING_LITERAL,
		IMPORT,
		CLS,
		AREA,
		ACCESS_MODIFIER,
		OPEN_BRACE,
		CLOSE_BRACE,
		OPEN_CURLY_BRACE,
		CLOSE_CURLY_BRACE,
		DOT,
		SEMICOLON,
		COLON,
		STATIC,
		COMMA
	};

public:
	Token(std::string&& word, size_t numberLine) noexcept : word(std::move(word)), numberLine(numberLine)
	{
		process_type();
	}
	Token(const std::string& word, size_t numberLine) noexcept : word(word), numberLine(numberLine)
	{
		process_type();
	}

	const std::string& get_word() const noexcept { return word; }
	size_t get_number_line() const noexcept { return numberLine; }

private:
	void process_type() noexcept
	{
		using enum Type;
		if (word == "import") type = IMPORT;
		else if (word == "cls") type = CLS;
		else if (word == "area") type = AREA;
		else if (word == "open" || word == "close" || word == "defen") type = ACCESS_MODIFIER;
		else if (word == "(") type = OPEN_BRACE;
		else if (word == ")") type = CLOSE_BRACE;
		else if (word == "{") type = OPEN_CURLY_BRACE;
		else if (word == "}") type = CLOSE_CURLY_BRACE;
		else if (word == ".") type = DOT;
		else if (word == ";") type = SEMICOLON;
		else if (word == ",") type = COMMA;
		else if (word == ":") type = COLON;
		else if (word == "static") type = STATIC;
		else if (word[0] == '"' && word[word.size() - 1] == '"') type = STRING_LITERAL;
		else type = WORD;
	}

private:
	std::string word;
	size_t numberLine;
	Type type;
};