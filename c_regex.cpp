#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Помилка: не вдалося відкрити файл " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


void writeFile(const string& filename, const string& content) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Помилка: не вдалося записати файл " << filename << endl;
        return;
    }
    file << content;
}

void task1_findLinks_regex(const string& text) {
    cout << "\nЗадача 1: Гіперпосилання та слова перед ними (regex) \n\n";

    regex url_regex(R"((https?://[^\s<>"']+))", regex_constants::icase);

    sregex_iterator url_begin(text.begin(), text.end(), url_regex);
    sregex_iterator url_end;

    vector<pair<string, string>> results;

    for (sregex_iterator it = url_begin; it != url_end; ++it) {
        smatch url_match = *it;
        string url = url_match.str();
        size_t url_pos = url_match.position();

        string word_before = "";
        if (url_pos > 0) {
            size_t word_start = url_pos;

            while (word_start > 0 &&
                   (isspace(text[word_start - 1]) || ispunct(text[word_start - 1]))) {
                word_start--;
            }

            size_t word_end = word_start;
            while (word_start > 0 &&
                   !isspace(text[word_start - 1]) &&
                   !ispunct(text[word_start - 1])) {
                word_start--;
            }

            if (word_start < word_end) {
                word_before = text.substr(word_start, word_end - word_start);
            }
        }

        results.push_back({word_before, url});
    }

    if (results.empty()) {
        cout << "Гіперпосилання не знайдено.\n";
    } else {
        cout << "Знайдено " << results.size() << " гіперпосилань:\n";
        for (size_t i = 0; i < results.size(); i++) {
            cout << "\n[" << i + 1 << "]\n";
            cout << "Слово перед посиланням: \"" << results[i].first << "\"\n";
            cout << "URL: " << results[i].second << "\n";
        }
        cout << string(40, '-') << endl;
    }
}

string task2_convertDates_regex(const string& text) {
    cout << "\nЗадача 2: Конвертація дат (regex)\n\n";

    string result = text;

    regex date_regex(R"((\d{1,2})/(\d{1,2})/(\d{2}(?:\d{2})?))");

    vector<string> found_dates;

    sregex_iterator date_begin(result.begin(), result.end(), date_regex);
    sregex_iterator date_end;

    vector<smatch> matches;
    for (sregex_iterator it = date_begin; it != date_end; ++it) {
        matches.push_back(*it);
    }

    for (auto it = matches.rbegin(); it != matches.rend(); ++it) {
        smatch match = *it;

        string day_str = match[1].str();
        string month_str = match[2].str();
        string year_str = match[3].str();

        int year = stoi(year_str);
        if (year_str.length() == 2) {
            year = (year < 30) ? 2000 + year : 1900 + year;
            year_str = to_string(year);
        }

        const string months[] = {
            "січня", "лютого", "березня", "квітня", "травня", "червня",
            "липня", "серпня", "вересня", "жовтня", "листопада", "грудня"
        };

        int month = stoi(month_str);
        int day = stoi(day_str);

        if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
            string new_date = "(" + year_str + ") " + months[month - 1] + " (" + day_str + ")";

            found_dates.push_back(match.str());

            result.replace(match.position(), match.length(), new_date);
        }
    }

    cout << "Знайдено дат у форматі ДД/ММ/РР(РР): " << found_dates.size() << "\n";
    if (!found_dates.empty()) {
        for (size_t i = 0; i < found_dates.size(); i++) {
            cout << i + 1 << ". " << found_dates[i] << endl;
        }
    }

    return result;
}

// Задача 3
string task3_formatNumbers_regex(const string& text) {
    cout << "\nЗадача 3: Форматування чисел (regex)\n\n";

    string result = text;

    regex number_regex(R"(([+-]?\d+(?:[.,]\d+)?(?:[eE][+-]?\d+)?))");

    vector<string> found_numbers;

    sregex_iterator num_begin(result.begin(), result.end(), number_regex);
    sregex_iterator num_end;

    vector<smatch> matches;
    for (sregex_iterator it = num_begin; it != num_end; ++it) {
        matches.push_back(*it);
    }

    for (auto it = matches.rbegin(); it != matches.rend(); ++it) {
        smatch match = *it;
        string num_str = match.str();

        size_t pos = match.position();
        bool is_valid = true;

        if (pos > 0) {
            char before = result[pos - 1];
            if (isalpha(before) || before == '_') {
                is_valid = false;
            }
        }

        if (pos + num_str.length() < result.length()) {
            char after = result[pos + num_str.length()];
            if (isalpha(after) || after == '_') {
                is_valid = false;
            }
        }

        if (is_valid) {
            try {
                double number;

                string num_for_parse = num_str;
                replace(num_for_parse.begin(), num_for_parse.end(), ',', '.');

                number = stod(num_for_parse);

                stringstream formatted;
                formatted << fixed << setprecision(4) << number;

                string final_number = "(" + formatted.str() + ")";

                found_numbers.push_back(num_str + " -> " + final_number);

                result.replace(pos, num_str.length(), final_number);
            } catch (...) {
            }
        }
    }

    cout << "Знайдено та відформатовано чисел: " << found_numbers.size() << "\n";
    if (!found_numbers.empty()) {
        for (size_t i = 0; i < min(found_numbers.size(), size_t(10)); i++) {
            cout << i + 1 << ". " << found_numbers[i] << endl;
        }
        if (found_numbers.size() > 10) {
            cout << "... і ще " << found_numbers.size() - 10 << " чисел\n";
        }
    }

    return result;
}
// Задача 4
string task4_replaceWithCurrentDateTime_regex(const string& text) {
    cout << "\nЗадача 4: Заміна дат на поточні (regex)\n\n";

    string result = text;

    time_t now = time(nullptr);
    tm* local_time = localtime(&now);

    stringstream date_ss;
    date_ss << "(" << (local_time->tm_year + 1900) << ") ";

    const string ukr_months[] = {
        "січня", "лютого", "березня", "квітня", "травня", "червня",
        "липня", "серпня", "вересня", "жовтня", "листопада", "грудня"
    };

    date_ss << ukr_months[local_time->tm_mon] << " (" << local_time->tm_mday << ")";
    string current_date = date_ss.str();

    stringstream time_ss;
    time_ss << setw(2) << setfill('0') << local_time->tm_hour << ":"
            << setw(2) << setfill('0') << local_time->tm_min << ":"
            << setw(2) << setfill('0') << local_time->tm_sec;
    string current_time = time_ss.str();

    cout << "Поточна дата для заміни: " << current_date << endl;
    cout << "Поточний час для заміни: " << current_time << endl;

    regex date_format_regex(R"(\(\d{4}\) [а-яіїєА-ЯІЇЄ]+ \(\d{1,2}\))");

    sregex_iterator date_begin(text.begin(), text.end(), date_format_regex);
    sregex_iterator date_end;
    size_t date_count = distance(date_begin, date_end);

    result = regex_replace(result, date_format_regex, current_date);

    regex time_regex(R"(\b\d{2}:\d{2}:\d{2}\b)");
    result = regex_replace(result, time_regex, current_time);

    cout << "Замінено дат у форматі (рік) місяць (число): " << date_count << endl;

    return result;
}

void processTextWithRegex(const string& text, const string& output_filename) {
    cout << "\n" << string(70, '=') << "\n";
    cout << "Обробка тексту з використанням регулярних виразів (C++11 <regex>)\n";
    cout << string(70, '=') << "\n";

    cout << "\nПочатковий розмір тексту: " << text.length() << " символів\n";

    // Виконуємо всі 4 задачі послідовно
    cout << "\nЗАВДАННЯ 1: Пошук гіперпосилань\n";
    task1_findLinks_regex(text);

    cout << "\nЗАВДАННЯ 2: Конвертація дат\n";
    string after_dates = task2_convertDates_regex(text);

    cout << "\nЗАВДАННЯ 3: Форматування чисел \n";
    string after_numbers = task3_formatNumbers_regex(after_dates);

    cout << "\nЗАВДАННЯ 4: Заміна на поточну дату/час\n";
    string final_result = task4_replaceWithCurrentDateTime_regex(after_numbers);

    writeFile(output_filename, final_result);
    cout << "\nФінальний результат записано у файл: " << output_filename << endl;

    writeFile("regex_after_dates.txt", after_dates);
    writeFile("regex_after_numbers.txt", after_numbers);

    cout << "\n" << string(70, '=') << "\n";
    cout << "Обробка завершена успішно\n";
    cout << string(70, '=') << "\n";
}


int main(int argc, char* argv[]) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    string input_file, output_file;

    if (argc >= 3) {
        input_file = argv[1];
        output_file = argv[2];
    } else if (argc == 2) {
        input_file = argv[1];
        output_file = "output_regex.txt";
    } else {
        cout << "Обробка тексту з використанням регулярних виразів\n\n";

        cout << "Введіть шлях до вхідного файлу: ";
        getline(cin, input_file);

        if (input_file.empty()) {
            input_file = "test_input.txt";
            cout << "Використовується файл за замовчуванням: " << input_file << endl;

            ifstream test_file(input_file);
            if (!test_file.good()) {
                cout << "Створення тестового файлу...\n";
                ofstream create_file(input_file);
                if (create_file) {
                    create_file << "Приклад тексту з різними даними:\n\n";
                    create_file << "Відвідайте наш сайт: https://example.com для отримання інформації.\n";
                    create_file << "Дата події: 15/05/23 або 20/12/2023.\n";
                    create_file << "Числові дані: 123, -45.67, +3.14e-10, 1,000.50.\n";
                    create_file << "Поточна дата буде замінена: (2023) грудня (15).\n";
                    create_file << "Час події: 14:30:00.\n";
                    create_file << "Ще одне посилання: http://test.org/page.html.\n";
                    create_file.close();
                    cout << "Тестовий файл створено.\n";
                }
            }
        }

        cout << "Введіть шлях для вихідного файлу [output_regex.txt]: ";
        getline(cin, output_file);

        if (output_file.empty()) {
            output_file = "output_regex.txt";
        }
    }

    cout << "\nЧитання файлу: " << input_file << endl;
    string text = readFile(input_file);

    if (text.empty()) {
        cerr << "Помилка: файл порожній або не вдалося прочитати\n";

        cout << "\nНатисніть Enter для виходу...";
        cin.get();
        return 1;
    }

    cout << "Успішно прочитано " << text.length() << " символів.\n";

    processTextWithRegex(text, output_file);

    if (argc < 2) {
        cout << "\nНатисніть Enter для виходу";
        cin.ignore();
        cin.get();
    }

    return 0;
}