#ifndef XMLINTERPRETER_H
#define XMLINTERPRETER_H

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <typeinfo>
#include <stdexcept>
#include <type_traits>

namespace Helper
{
    // string'i belirli bir ayırıcıya göre bölme işlevi
    std::vector<std::string> split(const std::string& s, char delimiter);

    // string'deki çevreleyici parantezleri kaldırma işlevi
    std::string stripParentheses(const std::string& s);

    // string'i ayrı tuple string'lerine bölme işlevi
    std::vector<std::string> splitTuples(const std::string& s);

    // Bir string'i ayrı grup string'lerine böler - dış grupları ayırır
    std::vector<std::string> splitOuterGroups(const std::string& s);
}

// Özelleştirilebilir temel parser şablonu
template<typename T>
struct ValueParser {
    static T parse(const std::string& /*value*/) {
        std::cerr << "Trying to parse unsupported type: " << typeid(T).name() << std::endl;
        throw std::runtime_error("Unsupported type.");
    }
};

// Recursive vektör ayrıştırma işlevi, iç içe vektör yapısını ayrıştırır
template<typename T>
std::vector<T> parseRecursiveVector(const std::string& value, bool isOutermost = true) {
    std::cerr << "Parsing recursive vector from string: " << value << std::endl;
    std::vector<T> result;
    std::vector<std::string> items;

    if (isOutermost) {
        items = Helper::splitOuterGroups(value);
    } else {
        items = Helper::split(value, ',');
    }

    for (const auto& itemStr : items) {
        result.push_back(ValueParser<T>::parse(Helper::stripParentheses(itemStr)));
    }
    return result;
}

// Bir türün vektör olup olmadığını kontrol eden yardımcı yapı
template<typename T, typename = void>
struct is_vector : std::false_type {};

template<typename T>
struct is_vector<T, std::enable_if_t<std::is_same<T, std::vector<typename T::value_type>>::value>> : std::true_type {};

// Tuple elemanlarını iç içe olarak ayrıştırma işlevi - recursive şablon (yavaşlatıyor -> belki kaldırmak gerekebilir, onur hocaya sor)
template<std::size_t Index = 0, typename... TupleTypes>
inline typename std::enable_if<Index == sizeof...(TupleTypes), void>::type
parseTupleElements(const std::vector<std::string>& /*values*/, std::tuple<TupleTypes...>& /*tuple*/) {}

template<std::size_t Index = 0, typename... TupleTypes>
inline typename std::enable_if<Index < sizeof...(TupleTypes), void>::type
parseTupleElements(const std::vector<std::string>& values, std::tuple<TupleTypes...>& tuple) {
    std::get<Index>(tuple) = ValueParser<typename std::tuple_element<Index, std::tuple<TupleTypes...>>::type>::parse(values[Index]);
    parseTupleElements<Index + 1, TupleTypes...>(values, tuple);
}

/*
 * Bazı temel türler için ValueParser özelleştirmeleri
*/

// Pair'leri vektörü için özelleştirilmiş parser
template<typename T1, typename T2>
struct ValueParser<std::vector<std::pair<T1, T2>>> {
    static std::vector<std::pair<T1, T2>> parse(const std::string& value) {
        //std::cout << "Parsing vector of pairs from string: " << value << std::endl;  // Debug

        std::vector<std::pair<T1, T2>> result;
        auto pairStrings = Helper::splitOuterGroups(value);
        for (const auto& pairStr : pairStrings) {
            //std::cout << "Pair string: " << pairStr << std::endl;  // Debug
            result.push_back(ValueParser<std::pair<T1, T2>>::parse(pairStr));
        }
        return result;
    }
};

// Tuple'ların bir vektörü için özelleştirilmiş parser
template<typename... Ts>
struct ValueParser<std::vector<std::tuple<Ts...>>> {
    static std::vector<std::tuple<Ts...>> parse(const std::string& value) {
        std::vector<std::tuple<Ts...>> result;
        for (const auto& tupleStr : Helper::splitTuples(value)) {
            result.push_back(ValueParser<std::tuple<Ts...>>::parse(tupleStr));
        }
        return result;
    }
};

// Vektör için özelleştirilmiş parser, vektörlerin iç içe ayrıştırılmasını yönetir
template<typename T>
struct ValueParser<std::vector<T>> {
    static std::vector<T> parse(const std::string& value) {
        // T vektör ise en dış olarak al
        if constexpr (is_vector<T>::value) {
            return parseRecursiveVector<T>(value, true);
        } else {
            return parseRecursiveVector<T>(value, false);
        }
    }
};

// Pair için özelleştirilmiş parser
template<typename T1, typename T2>
struct ValueParser<std::pair<T1, T2>> {
    static std::pair<T1, T2> parse(const std::string& value) {
        std::string strippedValue = Helper::stripParentheses(value);  // Parantezleri çıkar
        std::stringstream ss(strippedValue);
        std::string item1, item2;
        std::getline(ss, item1, ',');
        std::getline(ss, item2, ',');
        return {ValueParser<T1>::parse(item1), ValueParser<T2>::parse(item2)};
    }
};

// Tuple için özelleştirilmiş parser
template<typename... Ts>
struct ValueParser<std::tuple<Ts...>> {
    static std::tuple<Ts...> parse(const std::string& value) {
        //std::cout << "Parsing tuple from string: " << value << std::endl;  // Debug

        std::tuple<Ts...> result;
        std::string strippedValue = Helper::stripParentheses(value);
        //std::cout << "Stripped value: " << strippedValue << std::endl;  // Debug

        std::vector<std::string> values = Helper::split(strippedValue, ',');
        /*for (const auto& val : values) {
            std::cout << "Tuple element: " << val << std::endl;  // Debug
        }*/

        parseTupleElements(values, result);
        return result;
    }
};

// Float
template<>
struct ValueParser<float> {
    static float parse(const std::string& value) {
        try {
            return std::stof(value);
        } catch (const std::exception& e) {
            std::cerr << "Error converting string to float: " << value << " - " << e.what() << std::endl;
            throw;
        }
    }
};

// Double
template<>
struct ValueParser<double> {
    static double parse(const std::string& value) {
        try {
            return std::stod(value);
        } catch (const std::exception& e) {
            std::cerr << "Error converting string to double: " << value << " - " << e.what() << std::endl;
            throw;
        }
    }
};

// int
template<>
struct ValueParser<int> {
    static int parse(const std::string& value) {
        try {
            return std::stoi(value);
        } catch (const std::exception& e) {
            std::cerr << "Error converting string to int: " << value << " - " << e.what() << std::endl;
            throw;
        }
    }
};

// String
template<>
struct ValueParser<std::string> {
    static std::string parse(const std::string& value) {
        try {
            // Burada daha fazla bir işlem yapmıyoruz çünkü value zaten bir string.
            // Ancak, gerekiyorsa gelecekteki değişiklikler için bir yer bırakıyoruz.
            return value;
        } catch (const std::exception& e) {
            std::cerr << "Error processing string value: " << value << " - " << e.what() << std::endl;
            throw;
        }
    }
};

// Bool
template<>
struct ValueParser<bool> {
    static bool parse(const std::string& value) {
        try {
            // bool türünü parse et
            bool valueBool = false;
            if(value == "true" || value == "TRUE" || value == "1") {
                valueBool = true;
                return valueBool;
            } else if (value == "false" || value == "FALSE" || value == "0") {
                return valueBool;
            } else {
                throw("Bool type format is incorrect!");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing string value: " << value << " - " << e.what() << std::endl;
            throw;
        }
    }
};


class XmlInterpreter {
public:
    XmlInterpreter(const std::map<std::string, std::string>& dataMap) : data(dataMap) {}

    // Anahtar üzerinden veriyi yorumlama işlevi
    template<typename T>
    T interpret(const std::string& key) {
        std::cerr << "Interpreting key: " << key << std::endl;
        auto it = data.find(key);
        if (it == data.end()) {
            throw std::runtime_error("Key not found in data map.");
        }
        try {
            return parseValue<T>(it->second);
        } catch(const std::exception& e) {
            std::cerr << "Failed to parse value for key " << key << ": " << e.what() << std::endl;
            throw;
        }
    }

    std::vector<std::string> split(const std::string& s, char delimiter);

private:
    const std::map<std::string, std::string>& data;

    // Değer parser işlemi, ValueParser yapıları aracılığıyla gerçekleştirilir
    template<typename T>
    T parseValue(const std::string& value) {
        try {
            return ValueParser<T>::parse(value);
        } catch(const std::exception& e) {
            std::cerr << "Failed to parse value: " << value << ": " << e.what() << std::endl;
            throw;
        }
    }
};

#endif // XMLINTERPRETER_H
