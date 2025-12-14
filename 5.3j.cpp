#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
class Book {
    std::string name;
    std::string author;
    int year;
public:
    Book(const std::string& n, const std::string& a, int y)
        : name(n), author(a), year(y) {
    }

    const std::string& getName() const { return name; }
    const std::string& getAuthor() const { return author; }
    int getYear() const { return year; }
};

// функтор сортировки: по автору, потом по названию
struct BookSorter {
    bool operator()(const Book* lhs, const Book* rhs) const {
        if (lhs->getAuthor() < rhs->getAuthor())
            return true;
        if (lhs->getAuthor() > rhs->getAuthor())
            return false;
        return lhs->getName() < rhs->getName();
    }
};

// функтор поиска по диапазону годов
struct BookFinder {
    int fromYear;
    int toYear;

    BookFinder(int from, int to)
        : fromYear(from), toYear(to) {
    }

    bool operator()(const Book* b) const {
        int y = b->getYear();
        return y >= fromYear && y <= toYear;
    }

};


int main() {
    setlocale(LC_ALL, "RUSSIAN");

    std::vector<Book*> books;
    books.push_back(new Book("Война и мир", "Толстой Л.Н.", 2010));
    books.push_back(new Book("Подросток", "Достоевский Ф.М.", 2004));
    books.push_back(new Book("Обрыв", "Гончаров И.А.", 2010));
    books.push_back(new Book("Анна Каренина", "Толстой Л.Н.", 1999));
    books.push_back(new Book("Обыкновенная история", "Гончаров И.А.", 2011));
    books.push_back(new Book("Утраченные иллюзии", "Бальзак О.", 2009));
    books.push_back(new Book("Оливер Твист", "Диккенс Ч.", 2001));
    books.push_back(new Book("Фауст", "Гёте И.В.", 2010));
    books.push_back(new Book("Лилия долины", "Бальзак О.", 1998));

    std::cout << "\nКниги в алфавитном порядке:\n\n";

    BookSorter book_sorter;
    std::sort(books.begin(), books.end(), book_sorter);

    std::vector<Book*>::iterator i;
    for (i = books.begin(); i != books.end(); ++i) {
        std::cout << (*i)->getAuthor()
            << " \"" << (*i)->getName() << "\" ("
            << (*i)->getYear() << ")"
            << std::endl;
    }

    BookFinder book_finder(2005, 2014);
    std::vector<Book*>::iterator finder =
        std::find_if(books.begin(), books.end(), book_finder);

    std::cout << "\nКниги в диапазоне года издания 2005 - 2014:\n\n";
    while (finder != books.end()) {
        std::cout << (*finder)->getAuthor()
            << " \"" << (*finder)->getName() << "\" ("
            << (*finder)->getYear() << ")"
            << std::endl;

        finder = std::find_if(++finder, books.end(), book_finder);
    }

    struct YearExtractor {
        int operator()(const Book* b) const {
            return b->getYear();
        }
    };

    YearExtractor getYear;
    auto newerThan2009 = std::bind2nd(std::greater<int>(), 2009);

    int countNew =
        std::count_if(books.begin(), books.end(),
            [&](const Book* b) {
                return newerThan2009(getYear(b));
            });

    std::cout << "\nКниг новее 2009 года: " << countNew << std::endl;

    for (i = books.begin(); i != books.end(); ++i) {
        delete (*i);
    }

    return 0;
}