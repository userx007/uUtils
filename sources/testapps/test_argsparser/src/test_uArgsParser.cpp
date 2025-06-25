#include "uArgsParser.hpp"

int main(int argc, const char *argv[])
{
    CommandLineParser cli("My Tool");

    cli.add_option("file", "Input file path");
    cli.add_option("mode", "Execution mode");
    cli.add_option("debug", "Enable debug mode");

    cli.parse(argc, argv);

    if (cli.has("debug")) {
        std::cout << "Debugging enabled\n";
    }

    if (auto file = cli.get("file")) {
        std::cout << "File: " << *file << "\n";
    }

    if (auto mode = cli.get("mode")) {
        std::cout << "mode: " << *mode << "\n";
    }

    cli.print_usage();

    return 0;
}
