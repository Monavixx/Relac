#pragma once
#include <string>
#include <vector>


inline constexpr std::vector<std::string> get_lexer_separators() noexcept
{
	return {
		"{",
		"}",
		"(",
		")",
		"[",
		"]",
		".",
		",",
		";",
	};
}

