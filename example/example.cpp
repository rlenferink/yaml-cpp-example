
#include <iostream>

#include <yaml-cpp/yaml.h>

struct Coord { double lat, lon; };

namespace YAML {
template<>
struct convert<Coord> {
    static Node encode(const Coord& rhs) {
        Node node;
        node.push_back(rhs.lat);
        node.push_back(rhs.lon);
        return node;
    }

    static bool decode(const Node& node, Coord& rhs) {
        if(node.Type() != YAML::NodeType::Map) {
            return false;
        }

        rhs.lat = node["lat"].as<double>();
        rhs.lon = node["lon"].as<double>();
        return true;
    }
};
}

void parse_file(const std::string& fileName) {
    std::cout << "Start of parsing '" << fileName << "' ...\n";
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

    // Example complex list
    auto exampleComplexList = config["example_complex_list"];
    if (!exampleComplexList.IsSequence()) {
        std::cerr << "ERROR: example_complex_list is not a list!\n";
    } else {
        std::cout << "Printing items of example_complex_list ...\n";
        for(YAML::const_iterator it = exampleComplexList.begin(); it != exampleComplexList.end(); ++it) {
            try {
                Coord c = it->as<Coord>();
                std::cout << "    Item: lat=" << c.lat << ", lon=" << c.lon << "\n";
            } catch (std::exception& e) {
                std::cerr << "ERROR: " << e.what() << "\n";            
            }
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

int main(int argc, const char* argv[]) {
    // Test parsing of YAML data
    parse_file("../example.yaml");

    std::cout << "\n\n";

    // Test parsing of JSON (since YAML claims to be a superset of JSON)
    parse_file("../example.json");
}
