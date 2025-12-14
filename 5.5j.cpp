#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// обобщённый шаблон кеша
template <typename T>
class Cache {
    std::vector<T> data;
public:
    void put(const T& elem) {
        data.push_back(elem);
    }

    // аналог put – оператор +=
    Cache<T>& operator+=(const T& elem) {
        put(elem);
        return *this;
    }

    bool contains(const T& elem) const {
        for (const auto& x : data)
            if (x == elem)
                return true;
        return false;
    }
};

// явная специализация для std::string
template <>
class Cache<std::string> {
    std::vector<std::string> data;
    static const size_t MAX_SIZE = 100;
public:
    void put(const std::string& elem) {
        if (data.size() >= MAX_SIZE)
            throw std::runtime_error("Cache<std::string> overflow (100 items)");
        data.push_back(elem);
    }

    Cache<std::string>& operator+=(const std::string& elem) {
        put(elem);
        return *this;
    }

    // contains: совпадение по первому символу строки
    bool contains(const std::string& elem) const {
        if (elem.empty())
            return false;
        char first = elem[0];
        for (const auto& s : data) {
            if (!s.empty() && s[0] == first)
                return true;
        }
        return false;
    }
};

int main() {
    Cache<int> cache;
    cache.put(1);   // так должно работать
    cache.put(2);
    cache.put(3);
    cache += 5;     // так тоже должно работать

    Cache<std::string> voc;
    voc.put("OK");

    std::cout << std::boolalpha;
    std::cout << voc.contains("Only") << std::endl;  // true (оба начинаются на 'O')
    std::cout << cache.contains(5) << std::endl;     // true

    return 0;
}
