#include "../headers/XmlInterpreter.h"

XmlInterpreter::XmlInterpreter(const std::map<std::string, std::string>& dataMap) : data(dataMap) {}

template<typename T>
struct ValueParser {
    static T parse(const std::string& /*value*/) {
        std::cerr << "Trying to parse unsupported type: " << typeid(T).name() << std::endl;
        throw std::runtime_error("Unsupported type.");
    }
};

// Helper function to split a string based on a delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to remove surrounding parentheses from a string
std::string stripParentheses(const std::string& s) {
    if (s.front() == '(' && s.back() == ')') {
        return s.substr(1, s.length() - 2);
    }
    return s;
}

// Helper function to split a string into individual tuple strings
std::vector<std::string> splitTuples(const std::string& s) {
    std::vector<std::string> tuples;
    std::string tuple;
    bool insideTuple = false;
    for (char c : s) {
        if (c == '(') {
            insideTuple = true;
        }
        if (insideTuple) {
            tuple += c;
        }
        if (c == ')') {
            insideTuple = false;
            tuples.push_back(tuple);
            tuple.clear();
        }
    }
    return tuples;
}

// Helper function to split a string into individual pair strings
std::vector<std::string> splitOuterGroups(const std::string& s) {
    std::vector<std::string> result;
    int depth = 0;
    std::string currentGroup;
    for (char c : s) {
        if (c == '(') {
            if (depth == 0 && !currentGroup.empty()) {
                result.push_back(currentGroup);
                currentGroup.clear();
            } else {
                currentGroup.push_back(c);
            }
            depth++;
        } else if (c == ')') {
            depth--;
            if (depth == 0) {
                currentGroup.push_back(c);
                result.push_back(currentGroup);
                currentGroup.clear();
            } else {
                currentGroup.push_back(c);
            }
        } else if (c == ',' && depth == 0) {
            if (!currentGroup.empty()) {
                result.push_back(currentGroup);
                currentGroup.clear();
            }
        } else {
            currentGroup.push_back(c);
        }
    }
    if (!currentGroup.empty()) {
        result.push_back(currentGroup);
    }
    return result;
}

template<typename T>
std::vector<T> parseRecursiveVector(const std::string& value, bool isOutermost = true) {
    std::cerr << "Parsing recursive vector from string: " << value << std::endl;
    std::vector<T> result;
    std::vector<std::string> items;

    if (isOutermost) {
        items = splitOuterGroups(value);
    } else {
        items = split(value, ',');
    }

    for (const auto& itemStr : items) {
        result.push_back(ValueParser<T>::parse(stripParentheses(itemStr)));
    }
    return result;
}

// Specialization for vector of pairs
template<typename T1, typename T2>
struct ValueParser<std::vector<std::pair<T1, T2>>> {
    static std::vector<std::pair<T1, T2>> parse(const std::string& value) {
        //std::cout << "Parsing vector of pairs from string: " << value << std::endl;  // Debugging statement

        std::vector<std::pair<T1, T2>> result;
        auto pairStrings = splitOuterGroups(value);
        for (const auto& pairStr : pairStrings) {
            //std::cout << "Pair string: " << pairStr << std::endl;  // Debugging statement
            result.push_back(ValueParser<std::pair<T1, T2>>::parse(pairStr));
        }
        return result;
    }
};

// Specialization for vector of tuples
template<typename... Ts>
struct ValueParser<std::vector<std::tuple<Ts...>>> {
    static std::vector<std::tuple<Ts...>> parse(const std::string& value) {
        std::vector<std::tuple<Ts...>> result;
        for (const auto& tupleStr : splitTuples(value)) {
            result.push_back(ValueParser<std::tuple<Ts...>>::parse(tupleStr));
        }
        return result;
    }
};

// Helper to check if a type is a vector
template<typename T, typename = void>
struct is_vector : std::false_type {};

template<typename T>
struct is_vector<T, std::enable_if_t<std::is_same<T, std::vector<typename T::value_type>>::value>> : std::true_type {};


// specialization for a vector
template<typename T>
struct ValueParser<std::vector<T>> {
    static std::vector<T> parse(const std::string& value) {
        // If T is also a vector type, then treat it as outermost
        if constexpr (is_vector<T>::value) {
            return parseRecursiveVector<T>(value, true);
        } else {
            return parseRecursiveVector<T>(value, false);
        }
    }
};

template<typename T1, typename T2>
struct ValueParser<std::pair<T1, T2>> {
    static std::pair<T1, T2> parse(const std::string& value) {
        std::string strippedValue = stripParentheses(value);  // Strip the parentheses
        std::stringstream ss(strippedValue);
        std::string item1, item2;
        std::getline(ss, item1, ',');
        std::getline(ss, item2, ',');
        return {ValueParser<T1>::parse(item1), ValueParser<T2>::parse(item2)};
    }
};


// ... More specializations for other types like tuple, etc.

template<typename T>
T XmlInterpreter::interpret(const std::string& key) {
    std::cerr << "Interpreting key: " << key << std::endl;
    auto it = data.find(key);
    if (it == data.end()) {
        throw std::runtime_error("Key not found in data map.");
    }
    return parseValue<T>(it->second);
}

// Helper to recursively parse tuple elements
template<std::size_t Index = 0, typename... TupleTypes>
inline typename std::enable_if<Index == sizeof...(TupleTypes), void>::type
parseTupleElements(const std::vector<std::string>& /*values*/, std::tuple<TupleTypes...>& /*tuple*/) {}

template<std::size_t Index = 0, typename... TupleTypes>
inline typename std::enable_if<Index < sizeof...(TupleTypes), void>::type
parseTupleElements(const std::vector<std::string>& values, std::tuple<TupleTypes...>& tuple) {
    std::get<Index>(tuple) = ValueParser<typename std::tuple_element<Index, std::tuple<TupleTypes...>>::type>::parse(values[Index]);
    parseTupleElements<Index + 1, TupleTypes...>(values, tuple);
}

// Specialization for tuple
template<typename... Ts>
struct ValueParser<std::tuple<Ts...>> {
    static std::tuple<Ts...> parse(const std::string& value) {
        //std::cout << "Parsing tuple from string: " << value << std::endl;  // Debugging statement

        std::tuple<Ts...> result;
        std::string strippedValue = stripParentheses(value);
        //std::cout << "Stripped value: " << strippedValue << std::endl;  // Debugging statement

        std::vector<std::string> values = split(strippedValue, ',');
        /*for (const auto& val : values) {
            std::cout << "Tuple element: " << val << std::endl;  // Debugging statement
        }*/

        parseTupleElements(values, result);
        return result;
    }
};

template<typename T>
T XmlInterpreter::parseValue(const std::string& value) {
    return ValueParser<T>::parse(value);
}

template<>
struct ValueParser<float> {
    static float parse(const std::string& value) {
        return std::stof(value);
    }
};

template<>
struct ValueParser<double> {
    static double parse(const std::string& value) {
        return std::stod(value);
    }
};

template<>
struct ValueParser<int> {
    static int parse(const std::string& value) {
        try {
            return std::stoi(value);
        } catch (const std::exception& e) {
            std::cerr << "Error converting string to int: " << value << std::endl;
            throw;
        }
    }
};

template<>
struct ValueParser<std::string> {
    static std::string parse(const std::string& value) {
        return value;
    }
};

