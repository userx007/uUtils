#include "uArgsParserExt.hpp"


int main(int argc, const char *argv[])
{
    CommandLineParser cli(argv[0]);

    cli.add_option("file", "f", "Path to input file", true);
    cli.add_option("mode", "m", "Execution mode", false, "normal");
    cli.add_option("verbose", "v", "Enable verbose output", false);

    cli.parse(argc, argv);

    if (!cli.check_required()) {
        std::cerr << "Missing required options!\n";
        cli.print_usage();
        return 1;
    }

    std::cout << "File: " << cli.get("file").value_or("not provided") << "\n";
    std::cout << "Mode: " << cli.get("mode").value_or("default") << "\n";

    if (cli.has("verbose")) {
        std::cout << "Verbose mode is ON\n";
    }

    auto positional = cli.get_positional();
    if (!positional.empty()) {
        std::cout << "Positional args:\n";
        for (const auto& arg : positional) {
            std::cout << "  " << arg << "\n";
        }
    }

    return 0;
}
