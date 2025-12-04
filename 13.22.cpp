#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string transform_word(const std::string& word) {
    // 1. Перевірка довжини
    if (word.length() <= 2) {
        return word;
    }

    char penultimate_char = word[word.length() - 2];

    std::string result_word = "";
    for (char c : word) {
        if (c != penultimate_char) {
            result_word += c;
        }
    }

    return result_word;
}

std::string process_string(const std::string& input_string) {
    std::string result_string = "";
    std::string current_word;
    std::string current_whitespace;
    bool in_word = false;

    for (char c : input_string) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (in_word) {
                result_string += transform_word(current_word);
                current_word = "";
                in_word = false;
            }
            current_whitespace += c;

        } else {
            if (!current_whitespace.empty()) {
                result_string += current_whitespace;
                current_whitespace = "";
            }
            current_word += c;
            in_word = true;
        }
    }

    if (in_word) {
        result_string += transform_word(current_word);
    } else if (!current_whitespace.empty()) {
        result_string += current_whitespace;
    }

    return result_string;
}


int main() {
    std::string input_line;

    std::cout << "Введіть рядок (латинські літери, слова розділені пробілами):\n";
    std::getline(std::cin, input_line);

    std::cout << "\n--- Вхідні дані ---\n";
    std::cout << "Оригінальний рядок: '" << input_line << "'\n";

    std::string output_line = process_string(input_line);

    std::cout << "\n--- Результат ---\n";
    std::cout << "Перетворений рядок: '" << output_line << "'\n";



    return 0;
}