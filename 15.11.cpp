#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>

class Book {
public:
    std::string title;
    std::string author;
    int pages;
    int year;

    Book() : pages(0), year(0) {}

    Book(const std::string& t, const std::string& a, int p, int y)
        : title(t), author(a), pages(p), year(y) {}

    void display() const {
        std::cout << "Name: " << title
                  << " | Author: " << author
                  << " | Page: " << pages
                  << " | Year: " << year << "\n";
    }

    std::string to_file_string() const {
        const std::string delimiter = "|~|";
        return title + delimiter + author + delimiter + std::to_string(pages) + delimiter + std::to_string(year);
    }

    void from_file_string(const std::string& line) {
        const std::string delimiter = "|~|";
        size_t pos = 0;
        std::string token;
        std::vector<std::string> parts;

        std::string s = line;

        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            parts.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        parts.push_back(s);

        if (parts.size() == 4) {
            title = parts[0];
            author = parts[1];
            try {
                pages = std::stoi(parts[2]);
                year = std::stoi(parts[3]);
            } catch (const std::exception& e) {
                pages = 0;
                year = 0;
            }
        }
    }
};

void save_catalog(const std::vector<Book>& catalog, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& book : catalog) {
            file << book.to_file_string() << "\n";
        }
        file.close();
        std::cout << "Catalog successfully saved to file: " << filename << "\n";
    } else {
        std::cerr << "Error file could not be opened for writing: " << filename << "\n";
    }
}

std::vector<Book> load_catalog(const std::string& filename) {
    std::vector<Book> catalog;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                Book book;
                book.from_file_string(line);
                catalog.push_back(book);
            }
        }
        file.close();
        std::cout << "Каталог успішно завантажено з файлу: " << filename << ". Кількість книг: " << catalog.size() << "\n";
    } else {
        std::cerr << "Попередження: Файл каталогу не знайдено або не вдалося відкрити: " << filename << ". Створено порожній каталог.\n";
    }
    return catalog;
}

void search_books(const std::vector<Book>& catalog) {
    std::string search_author, search_title;
    std::cout << "\n--- Пошук книжки ---\n";

    std::cout << "Введіть ім'я автора (або натисніть Enter, щоб пропустити): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, search_author);

    std::cout << "Введіть назву книжки (або натисніть Enter, щоб пропустити): ";
    std::getline(std::cin, search_title);

    auto to_lower = [](const std::string& str) {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return lower_str;
    };

    std::string lower_author = to_lower(search_author);
    std::string lower_title = to_lower(search_title);

    bool found = false;
    std::cout << "\n--- Результати пошуку ---\n";

    for (const auto& book : catalog) {
        bool match_author = lower_author.empty() || to_lower(book.author).find(lower_author) != std::string::npos;
        bool match_title = lower_title.empty() || to_lower(book.title).find(lower_title) != std::string::npos;

        if (match_author && match_title) {
            book.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Нічого не знайдено за заданими критеріями.\n";
    }
}

int main() {
    const std::string CATALOG_FILE = "book_catalog.txt";

    std::vector<Book> book_catalog = load_catalog(CATALOG_FILE);

    if (book_catalog.empty()) {
        std::cout << "\nСтворення початкового каталогу...\n";
        book_catalog.push_back(Book("Кобзар", "Тарас Шевченко", 400, 1840));
        book_catalog.push_back(Book("Тигролови", "Іван Багряний", 250, 1946));
        book_catalog.push_back(Book("Майстер і Маргарита", "Михайло Булгаков", 450, 1967));
        book_catalog.push_back(Book("Сто років самотності", "Габріель Гарсіа Маркес", 417, 1967));
        book_catalog.push_back(Book("Заповіт", "Тарас Шевченко", 10, 1845));

        save_catalog(book_catalog, CATALOG_FILE);
    }

    std::cout << "\n======================================\n";
    std::cout << "Поточний каталог:\n";
    for(const auto& book : book_catalog) {
        book.display();
    }
    std::cout << "======================================\n";

    search_books(book_catalog);
    return 0;
}