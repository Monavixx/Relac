#include "lexer/lexer.h"

Lexer::Lexer(std::string&& code, std::vector<std::string>&& separators) noexcept
    : code(std::move(code)), separators(std::move(separators))
{
    this->code.erase(std::remove(this->code.begin(), this->code.end(), '\r'), this->code.end());
}

std::vector<Token> Lexer::tokenize() noexcept
{
    Logger::note().log("Lexer started");

    while (i < code.size()) {
        process();
    }
    add_any_word();

    return std::move(res);
}

void Lexer::process() noexcept
{
    Logger::note().log(1, code[i]);
    if (isOpenQuotes) {
        handling_when_quote_is_open();
    }
    else {
        if (code[i] == '\n') {
            add_any_word();
            line_break();
            space_symbol();
        }
        else if (code[i] == '\t' || code[i] == ' ') {
            add_any_word();
            space_symbol();
        }
        else if (code[i] == '/') {
            add_any_word();
            slash();
        }
        else if (code[i] == '"') {
            add_any_word();
            isOpenQuotes = true;
            anyWord += '"';
            ++i;
        }
        else {
            process_next_word();
        }
    }
}

void Lexer::line_break() noexcept
{
    ++currentNumberLine;
}

void Lexer::space_symbol() noexcept
{
    ++i;
}

void Lexer::slash() noexcept
{
    if (is_not_last_and_not_more()) {
        if (code[i + 1] == '/') {
            ++i;
            while (!is_end()) {
                if (code[i] == '\n') {
                    line_break();
                    space_symbol();
                    break;
                }
                ++i;
            }
        }
        else {
            process_next_word();
        }
    }
}

void Lexer::process_next_word() noexcept
{
    size_t sizeNextOp = size_next_operator();
    if (sizeNextOp == 0) {
        anyWord += code[i++];
    }
    else {
        add_any_word();
        res.emplace_back(mid(code, i, sizeNextOp), currentNumberLine);
        i += sizeNextOp;
    }
}

void Lexer::handling_when_quote_is_open() noexcept
{
    if (code[i] == '"') {
        anyWord += '"';
        isOpenQuotes = false;
        add_any_word();
    }
    else {
        anyWord += code[i];
        if (code[i] == '\n') {
            ++currentNumberLine;
        }
    }
    ++i;
}

size_t Lexer::size_next_operator() noexcept
{
    std::string word;
    

    size_t j = i;
    bool isEqualOperator = false;
    bool isPrevEqualOperator = false;
    bool updateIsPrevEqualOperator = true;
    std::string lastEqual;
    
    while (!is_end()) {
        word.push_back(code[j++]);

        size_t amountMaybeOperator = 0;

        isEqualOperator = false;
        updateIsPrevEqualOperator = !updateIsPrevEqualOperator;
        if (updateIsPrevEqualOperator) {
            isPrevEqualOperator = false;
        }

        for (auto& item : separators) {
            if (item.starts_with(word)) {
                ++amountMaybeOperator;
                if (item == word) {
                    lastEqual = word;
                    isEqualOperator = true;
                    isPrevEqualOperator = true;
                }
            }
        }
        if (isEqualOperator && amountMaybeOperator == 1) {
            return word.size();
        }
        else if (amountMaybeOperator == 0) {
            if (isPrevEqualOperator) {
                return word.size() - 1;
            }
            if (!lastEqual.empty()) {
                return lastEqual.size();
            }
            return 0;
        }
        
    }
    if (isEqualOperator) {
        return word.size();
    }
    return 0;
}
