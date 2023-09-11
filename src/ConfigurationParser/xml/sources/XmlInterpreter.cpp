#include "../headers/XmlInterpreter.h"

namespace Helper
{
    // string'i belirli bir ayırıcıya göre bölme işlevi
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // string'deki çevreleyici parantezleri kaldırma işlevi
    std::string stripParentheses(const std::string& s) {
        if (s.front() == '(' && s.back() == ')') {
            return s.substr(1, s.length() - 2);
        }
        return s;
    }

    // string'i ayrı tuple string'lerine bölme işlevi
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

    // Bir string'i ayrı grup string'lerine böler - dış grupları ayırır
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
}

