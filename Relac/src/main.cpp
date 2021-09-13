#include <iostream>

#include <boost/program_options.hpp>

#include "logger/logger.h"
#include "functions/readFile.h"
#include "lexer/lexer.h"
#include "lexer/config.h"


namespace bpo = boost::program_options;

int main(int argc, char* argv[])
{
    bpo::options_description desc("All options");

    desc.add_options()
        ("help,h", "produce help message")
        ("src,s", bpo::value<std::string>(), "source file")
        ("out,o", bpo::value<std::string>(), "output file");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.contains("help")) {
        std::cout << desc << '\n';
        return 0;
    }
    
    if (vm.contains("src")) {
        std::string code = readFile(vm["src"].as<std::string>());

        Lexer lexer{ std::move(code), get_lexer_separators() };
        auto tokens = lexer.tokenize();
        for (auto& item : tokens) {
            fmt::print("{}, ", item.get_word());
        }
    }
}