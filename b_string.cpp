#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <locale>
#include <codecvt>

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

// Задача 1
void task1_findLinks(const string& text) {
    cout << "\nЗадача 1: Гіперпосилання та слова перед ними \n\n";

    vector<pair<string, string>> results;
    size_t pos = 0;

    while (pos < text.length()) {

        size_t http_pos = text.find("http://", pos);
        size_t https_pos = text.find("https://", pos);
        size_t url_start = string::npos;

        if (http_pos != string::npos && https_pos != string::npos) {
            url_start = min(http_pos, https_pos);
        } else if (http_pos != string::npos) {
            url_start = http_pos;
        } else if (https_pos != string::npos) {
            url_start = https_pos;
        }

        if (url_start == string::npos) break;

        size_t url_end = url_start;
        while (url_end < text.length() &&
               !isspace(text[url_end]) &&
               text[url_end] != '"' &&
               text[url_end] != '\'' &&
               text[url_end] != ')' &&
               text[url_end] != ']' &&
               text[url_end] != '>') {
            url_end++;
        }

        string url = text.substr(url_start, url_end - url_start);

        string word_before = "";
        if (url_start > 0) {
            size_t word_end = url_start - 1;


            while (word_end > 0 &&
                   (isspace(text[word_end]) || ispunct(text[word_end]))) {
                word_end--;
            }


            size_t word_start = word_end;
            while (word_start > 0 &&
                   !isspace(text[word_start - 1]) &&
                   !ispunct(text[word_start - 1])) {
                word_start--;
            }

            if (word_start <= word_end && word_start < text.length()) {
                word_before = text.substr(word_start, word_end - word_start + 1);
            }
        }

        results.push_back({word_before, url});
        pos = url_end;
    }


    if (results.empty()) {
        cout << "Гіперпосилання не знайдено.\n";
    } else {
        for (const auto& result : results) {
            cout << "Слово: \"" << result.first << "\"\n";
            cout << "URL: " << result.second << "\n";
            cout << string(40, '-') << endl;
        }
    }
}

// Задача 2
string task2_convertDates(const string& text) {
    cout << "\nЗадача 2: Конвертація дат\n\n";

    string result = text;
    vector<string> found_dates;

    size_t pos = 0;
    while (pos < result.length()) {
        size_t slash1 = result.find('/', pos);
        if (slash1 == string::npos || slash1 < 2) {
            pos++;
            continue;
        }

        size_t slash2 = result.find('/', slash1 + 1);
        if (slash2 == string::npos || slash2 - slash1 > 3) {
            pos = slash1 + 1;
            continue;
        }

        bool is_date = true;

        for (size_t i = slash1 - 2; i < slash1; i++) {
            if (i < result.length() && !isdigit(result[i])) {
                is_date = false;
                break;
            }
        }

        if (is_date) {
            for (size_t i = slash1 + 1; i < slash2; i++) {
                if (i < result.length() && !isdigit(result[i])) {
                    is_date = false;
                    break;
                }
            }
        }

        if (is_date) {
            size_t year_end = slash2 + 1;
            int digit_count = 0;

            while (year_end < result.length() && isdigit(result[year_end])) {
                digit_count++;
                year_end++;
            }

            if (digit_count != 2 && digit_count != 4) {
                is_date = false;
            }
        }

        if (is_date) {
            string day_str = result.substr(slash1 - 2, 2);
            string month_str = result.substr(slash1 + 1, slash2 - slash1 - 1);

            size_t year_start = slash2 + 1;
            size_t year_end = year_start;
            while (year_end < result.length() && isdigit(result[year_end])) {
                year_end++;
            }

            string year_str = result.substr(year_start, year_end - year_start);

            int year = stoi(year_str);
            if (year < 100) {
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
                string new_date = "(" + year_str + ") " + months[month - 1] + " (" + to_string(day) + ")";

                found_dates.push_back(result.substr(slash1 - 2, year_end - (slash1 - 2)));

                result.replace(slash1 - 2, year_end - (slash1 - 2), new_date);

                pos = slash1 - 2 + new_date.length();
            } else {
                pos = slash1 + 1;
            }
        } else {
            pos = slash1 + 1;
        }
    }

    cout << "Знайдені дати: " << found_dates.size() << "\n";
    for (const auto& date : found_dates) {
        cout << "- " << date << endl;
    }

    return result;
}

// Задача 3
string task3_formatNumbers(const string& text) {
    cout << "\nЗадача 3: Форматування чисел\n\n";

    string result = text;
    vector<string> found_numbers;

    size_t pos = 0;
    while (pos < result.length()) {
        if (isdigit(result[pos]) ||
            (result[pos] == '-' && pos + 1 < result.length() && isdigit(result[pos + 1])) ||
            (result[pos] == '+' && pos + 1 < result.length() && isdigit(result[pos + 1]))) {

            size_t num_start = pos;
            size_t num_end = pos;
            bool has_dot = false;
            bool has_comma = false;
            bool has_e = false;

            while (num_end < result.length()) {
                char c = result[num_end];

                if (isdigit(c)) {
                    num_end++;
                } else if (c == '.' && !has_dot && !has_comma && !has_e) {
                    has_dot = true;
                    num_end++;
                } else if (c == ',' && !has_dot && !has_comma && !has_e) {
                    has_comma = true;
                    num_end++;
                } else if ((c == 'e' || c == 'E') && !has_e) {
                    has_e = true;
                    num_end++;
                    if (num_end < result.length() &&
                        (result[num_end] == '+' || result[num_end] == '-')) {
                        num_end++;
                    }
                } else if ((c == '-' || c == '+') &&
                          (num_end == num_start ||
                           (has_e && (result[num_end - 1] == 'e' || result[num_end - 1] == 'E')))) {
                    num_end++;
                } else {
                    break;
                }
            }

            if (num_end - num_start > 0) {
                string num_str = result.substr(num_start, num_end - num_start);

                bool is_valid = true;
                if (num_start > 0) {
                    char before = result[num_start - 1];
                    if (isalpha(before) || before == '_') {
                        is_valid = false;
                    }
                }
                if (num_end < result.length()) {
                    char after = result[num_end];
                    if (isalpha(after) || after == '_') {
                        is_valid = false;
                    }
                }

                if (is_valid) {
                    try {
                        double number;

                        string num_for_parse = num_str;
                        size_t comma_pos = num_for_parse.find(',');
                        if (comma_pos != string::npos) {
                            num_for_parse[comma_pos] = '.';
                        }

                        number = stod(num_for_parse);

                        stringstream formatted;
                        formatted << fixed << setprecision(4) << number;

                        string final_number = "(" + formatted.str() + ")";

                        found_numbers.push_back(num_str + " -> " + final_number);

                        result.replace(num_start, num_end - num_start, final_number);

                        pos = num_start + final_number.length();
                        continue;
                    } catch (...) {
                    }
                }
            }
        }
        pos++;
    }

    cout << "Знайдені та відформатовані числа: " << found_numbers.size() << "\n";
    for (const auto& num : found_numbers) {
        cout << "- " << num << endl;
    }

    return result;
}

string task4_replaceWithCurrentDateTime(const string& text) {
    cout << "\nЗадача 4: Заміна дат на поточні \n\n";

    string result = text;

    time_t now = time(nullptr);
    tm* local_time = localtime(&now);

    stringstream date_ss;
    date_ss << put_time(local_time, "(%Y) ");

    int month = local_time->tm_mon;
    const string ukr_months[] = {
        "січня", "лютого", "березня", "квітня", "травня", "червня",
        "липня", "серпня", "вересня", "жовтня", "листопада", "грудня"
    };

    date_ss << ukr_months[month] << " (" << local_time->tm_mday << ")";
    string current_date = date_ss.str();

    stringstream time_ss;
    time_ss << put_time(local_time, "%H:%M:%S");
    string current_time = time_ss.str();

    cout << "Поточна дата для заміни: " << current_date << endl;
    cout << "Поточний час для заміни: " << current_time << endl;

    size_t date_count = 0;

    size_t pos = 0;
    while (pos < result.length()) {
        if (result[pos] == '(' && pos + 5 < result.length() && isdigit(result[pos + 1])) {

            size_t year_end = pos + 1;
            int year_digits = 0;
            while (year_end < result.length() && isdigit(result[year_end])) {
                year_digits++;
                year_end++;
            }

            if (year_digits == 4 && year_end < result.length() && result[year_end] == ')') {
                size_t day_start = result.find(" (", year_end);
                if (day_start != string::npos && day_start + 2 < result.length()) {
                    size_t day_end = day_start + 2;
                    while (day_end < result.length() && isdigit(result[day_end])) {
                        day_end++;
                    }

                    if (day_end < result.length() && result[day_end] == ')') {
                        result.replace(pos, day_end - pos + 1, current_date);
                        date_count++;
                        pos += current_date.length();
                        continue;
                    }
                }
            }
        }
        pos++;
    }

    pos = 0;
    while (pos < result.length()) {
        if (pos + 8 < result.length() &&
            isdigit(result[pos]) && isdigit(result[pos + 1]) &&
            result[pos + 2] == ':' &&
            isdigit(result[pos + 3]) && isdigit(result[pos + 4]) &&
            result[pos + 5] == ':' &&
            isdigit(result[pos + 6]) && isdigit(result[pos + 7])) {

            result.replace(pos, 8, current_time);
            pos += current_time.length();
        } else {
            pos++;
        }
    }

    cout << "Замінено дат: " << date_count << endl;

    return result;
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    if (argc < 2) {
        cerr << "Використання: " << argv[0] << " <вхідний_файл> [вихідний_файл]\n";
        cerr << "Приклад: " << argv[0] << " input.txt output.txt\n";
        return 1;
    }

    string input_file = argv[1];
    string output_file = (argc >= 3) ? argv[2] : "output.txt";

    cout << "Читання файлу: " << input_file << endl;
    string text = readFile(input_file);

    if (text.empty()) {
        cerr << "Файл порожній або не вдалося прочитати\n";
        return 1;
    }

    cout << "Розмір тексту: " << text.length() << " символів\n";

    // Виконуємо задачу 1
    task1_findLinks(text);

    // Виконуємо задачу 2
    string text_after_task2 = task2_convertDates(text);

    // Виконуємо задачу 3
    string text_after_task3 = task3_formatNumbers(text_after_task2);

    // Виконуємо задачу 4
    string final_text = task4_replaceWithCurrentDateTime(text_after_task3);

    cout << "\n Запис результату\n";
    writeFile(output_file, final_text);
    cout << "Результат записано у файл: " << output_file << endl;

    writeFile("task2_result.txt", text_after_task2);
    writeFile("task3_result.txt", text_after_task3);

    cout << "\nОбробка завершена успішно!\n";

    return 0;
}