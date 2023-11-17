
#include <iostream>

#include <yaml-cpp/yaml.h>

int main(int argc, const char* argv[]) {
    std::cout << "Start of example ...\n";
    std::cout << "=========================\n";

    YAML::Node config = YAML::LoadFile("../example.yaml");

    auto exampleBool = config["example_bool"];
    std::cout << "Example bool: " << exampleBool.as<bool>() << "\n\n";

    auto exampleString = config["example_string"];
    std::cout << "Example string: \n" << exampleString.as<std::string>() << "\n";

    // Example list
    auto exampleList = config["example_list"];
    if (!exampleList.IsSequence()) {
        std::cerr << "ERROR: example_list is not a list!\n";
    } else {
        std::cout << "Printing items of example_list ...\n";
        for(YAML::const_iterator it = exampleList.begin(); it != exampleList.end(); ++it) {
            std::cout << "    Item: " << it->as<std::string>() << "\n";
        }
    }

    std::cout << "\n";

    // Example dict
    auto exampleDict = config["example_dict"];
    if (exampleDict.Type() != YAML::NodeType::Map) {
        std::cerr << "ERROR: example_dict is not a map!\n";
    } else {
        std::cout << "Printing items of example_dict ...\n";
        for(YAML::const_iterator it = exampleDict.begin(); it != exampleDict.end(); ++it) {
            auto& key = it->first;
            auto& value = it->second;

            switch (value.Type()) {
                case YAML::NodeType::Scalar:
                    std::cout << "    Item: " << key.as<std::string>() << "=" << value.as<std::string>()  << "\n";
                    break;
                case YAML::NodeType::Map:
                    std::cout << "    Item: " << key.as<std::string>() << "\n";
                    for(YAML::const_iterator subIt = value.begin(); subIt != value.end(); ++subIt) {
                        auto& subKey = subIt->first;
                        auto& subValue = subIt->second;

                        std::cout << "        Sub-item: " << subKey.as<std::string>() << "=" << subValue.as<std::string>()  << "\n";
                    }
                    break;
                default:
                    std::cerr << "ERROR: Unsupported type!\n";
                    break;
            }
        }
    }

    std::cout << "=========================\n";
    std::cout << "End of example ...\n";
}
