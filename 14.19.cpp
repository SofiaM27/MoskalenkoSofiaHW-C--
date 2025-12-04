#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

std::string clean_word(const std::string& s) {
    if (s.empty()) {
        return s;
    }

    size_t first = 0;
    while (first < s.length() && std::ispunct(static_cast<unsigned char>(s[first]))) {
        first++;
    }

    size_t last = s.length() - 1;
    if (first >= s.length()) {
        return "";
    }
    while (last > first && std::ispunct(static_cast<unsigned char>(s[last]))) {
        last--;
    }

    return s.substr(first, last - first + 1);
}

void process_file(const std::string& input_filename, const std::string& output_filename, char target_char) {
    std::ifstream input_file(input_filename);
    std::ofstream output_file(output_filename);

    if (!input_file.is_open()) {
        std::cerr << "Error: " << input_filename << "\n";
        return;
    }

    if (!output_file.is_open()) {
        std::cerr << "Error: " << output_filename << "\n";
        return;
    }

    char target_char_lower = std::tolower(static_cast<unsigned char>(target_char));
    int found_count = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        std::string word;

        while (ss >> word) {
            std::string cleaned = clean_word(word);

            if (!cleaned.empty()) {
                char first_char_lower = std::tolower(static_cast<unsigned char>(cleaned[0]));

                if (first_char_lower == target_char_lower) {
                    output_file << cleaned << "\n";
                    found_count++;
                }
            }
        }
    }

    input_file.close();
    output_file.close();

    std::cout << "\n--Result--\n";
    std::cout << "Обробка завершена. Знайдено і записано " << found_count << " слів.\n";
    std::cout << "Результат у файлі: " << output_filename << "\n";
}


int main() {
    const std::string INPUT_FILE = "input.txt";
    const std::string OUTPUT_FILE = "output.txt";
    char search_char;

    std::ofstream test_input(INPUT_FILE);
    if (test_input.is_open()) {
        test_input << "Це тестовий файл. Він містить різні слова,\n";
        test_input << "як, наприклад, 'Книга', 'кіт', '(Квітка)',\n";
        test_input << "або 'кава.', і слово 'комп\'ютер'.\n";
        test_input.close();
        std::cout << "Створено тестовий вхідний файл: " << INPUT_FILE << "\n";
    } else {
        std::cerr << "Неможливо створити тестовий файл.\n";
        return 1;
    }

    std::cout << "\nВведіть прописну латинську літеру для пошуку: ";
    if (!(std::cin >> search_char)) {
        std::cerr << "Помилка вводу.\n";
        return 1;
    }

    process_file(INPUT_FILE, OUTPUT_FILE, search_char);

    return 0;
}