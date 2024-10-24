#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

void helpCommands() {
    std::cout << "Usage: torspy [OPTIONS] [URL]\n";
    std::cout << "Options:\n";
    std::cout << "  --display                         Display the content of a .onion site\n";
    std::cout << "  -s [filename]                    Save output to a specified file\n";
    std::cout << "  -d [directory]                   Move output to a specified directory\n";
    std::cout << "  --search 'search query'           Search for content on the onion site\n";
    std::cout << "  --find 'search query'             Search for specific text and save results\n";
    std::cout << "  --dir [directory-file]            Find directories from the specified file\n";
    std::cout << "  --sub [subdomain-file]            Find subdomains from the specified file\n";
    std::cout << "  --analyze                         Analyze content of the onion site\n";
    std::cout << "  --download -s [filename]          Download content from the onion site\n";
    std::cout << "  --links                           Find all links on the onion site\n";
    std::cout << "  --service                         Get service info of the onion site\n";
    std::cout << "  --help                            Display this help message\n";
}

void executeTorspy(const std::vector<std::string>& args) {
    std::ostringstream command;
    command << "torspy";

    for (const auto& arg : args) {
        command << " " << arg;
    }

    int result = system(command.str().c_str());
    if (result == -1) {
        std::cerr << "Error executing torspy command." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        helpCommands();
        return 1;
    }

    std::string command = argv[1];

    if (command == "--display") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({argv[2]});
    } else if (command == "--search") {
        if (argc < 4) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--search", argv[2], argv[3]});
    } else if (command == "--find") {
        if (argc < 4) {
            helpCommands();
            return 1;
        }
        std::vector<std::string> args = {"--find", argv[2], argv[3]};
        if (argc >= 5 && std::string(argv[4]) == "-s") {
            args.push_back("-s");
            args.push_back(argv[5]);
        }
        if (argc >= 7 && std::string(argv[6]) == "-d") {
            args.push_back("-d");
            args.push_back(argv[7]);
        }
        executeTorspy(args);
    } else if (command == "--dir") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--dir", "directories-list.txt", argv[2]});
        if (argc >= 4 && std::string(argv[3]) == "-s") {
            executeTorspy({"--dir", "directories-list.txt", argv[2], "-s", argv[4]});
        }
    } else if (command == "--sub") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--sub", "subdomain-list.txt", argv[2]});
        if (argc >= 4 && std::string(argv[3]) == "-s") {
            executeTorspy({"--sub", "subdomain-list.txt", argv[2], "-s", argv[4]});
        }
    } else if (command == "--analyze") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--analyze", argv[2]});
        if (argc >= 4 && std::string(argv[3]) == "-s") {
            executeTorspy({"--analyze", argv[2], "-s", argv[4]});
        }
    } else if (command == "--download") {
        if (argc < 4) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--download", argv[2], "-s", argv[3]});
    } else if (command == "--links") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--links", argv[2]});
        if (argc >= 4 && std::string(argv[3]) == "-s") {
            executeTorspy({"--links", argv[2], "-s", argv[4]});
        }
    } else if (command == "--service") {
        if (argc < 3) {
            helpCommands();
            return 1;
        }
        executeTorspy({"--service", argv[2]});
    } else if (command == "--help") {
        helpCommands();
    } else {
        executeTorspy({argv[1]});
    }

    return 0;
}