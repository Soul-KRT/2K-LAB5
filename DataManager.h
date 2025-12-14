#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <cctype>
#include <stdexcept>

// обобщённый шаблон
template <typename T>
class DataManager {
    static const size_t CAPACITY = 64;
    T data[CAPACITY];
    size_t count = 0; // сколько элементов сейчас в наборе

    size_t startIndex() const { return CAPACITY - count; }

    void dumpToFile() {
        std::ofstream out("dump.dat", std::ios::binary | std::ios::app);
        if (!out) return;
        out.write(reinterpret_cast<const char*>(data + startIndex()),
            static_cast<std::streamsize>(count * sizeof(T)));
        out.close();
        count = 0;
    }

    void loadFromFile() {
        std::ifstream in("dump.dat", std::ios::binary);
        if (!in) return;

        in.seekg(0, std::ios::end);
        std::streamsize fileSize = in.tellg();
        if (fileSize <= 0) return;
        std::streamsize elemCount = fileSize / static_cast<std::streamsize>(sizeof(T));
        if (elemCount <= 0) return;

        std::streamsize toRead = std::min<std::streamsize>(elemCount, CAPACITY);
        std::streamoff offset = (elemCount - toRead) * static_cast<std::streamoff>(sizeof(T));
        in.seekg(offset, std::ios::beg);

        in.read(reinterpret_cast<char*>(data + (CAPACITY - toRead)),
            toRead * static_cast<std::streamsize>(sizeof(T)));
        count = static_cast<size_t>(toRead);
        in.close();
    }

public:
    DataManager() = default;

    void push(T elem) {
        if (count == CAPACITY)
            dumpToFile();
        data[CAPACITY - 1 - count] = elem;
        ++count;
    }

    void push(T elems[], size_t n) {
        for (size_t i = 0; i < n; ++i)
            push(elems[i]);
    }

    T peek() const {
        if (count == 0)
            return T{};
        if (count % 2 == 0)
            return T{};
        size_t s = startIndex();
        size_t mid = s + count / 2;
        return data[mid];
    }

    T pop() {
        if (count == 0) {
            const_cast<DataManager<T>*>(this)->loadFromFile();
            if (count == 0)
                throw std::runtime_error("DataManager is empty");
        }
        size_t idx = CAPACITY - 1;
        T value = data[idx];

        size_t s = startIndex();
        for (size_t i = idx; i > s; --i)
            data[i] = data[i - 1];

        --count;

        if (count == 0)
            loadFromFile();

        return value;
    }

    size_t size() const { return count; }

    const T* begin() const { return data + startIndex(); }
    const T* end()   const { return data + CAPACITY; }
};

// явная специализация для char
template <>
class DataManager<char> {
    static const size_t CAPACITY = 64;
    char data[CAPACITY];
    size_t count = 0;

    size_t startIndex() const { return CAPACITY - count; }

    void dumpToFile() {
        std::ofstream out("dump.dat", std::ios::binary | std::ios::app);
        if (!out) return;
        out.write(data + startIndex(),
            static_cast<std::streamsize>(count * sizeof(char)));
        out.close();
        count = 0;
    }

    void loadFromFile() {
        std::ifstream in("dump.dat", std::ios::binary);
        if (!in) return;

        in.seekg(0, std::ios::end);
        std::streamsize fileSize = in.tellg();
        if (fileSize <= 0) return;
        std::streamsize elemCount = fileSize / static_cast<std::streamsize>(sizeof(char));
        if (elemCount <= 0) return;

        std::streamsize toRead = std::min<std::streamsize>(elemCount, CAPACITY);
        std::streamoff offset = (elemCount - toRead) * static_cast<std::streamoff>(sizeof(char));
        in.seekg(offset, std::ios::beg);

        in.read(data + (CAPACITY - toRead),
            toRead * static_cast<std::streamsize>(sizeof(char)));
        count = static_cast<size_t>(toRead);
        in.close();
    }

public:
    DataManager() = default;

    void push(char elem) {
        if (std::ispunct(static_cast<unsigned char>(elem)))
            elem = '_';
        if (count == CAPACITY)
            dumpToFile();
        data[CAPACITY - 1 - count] = elem;
        ++count;
    }

    void push(char elems[], size_t n) {
        for (size_t i = 0; i < n; ++i)
            push(elems[i]);
    }

    char peek() const {
        if (count == 0)
            return '\0';
        if (count % 2 == 0)
            return '\0';
        size_t s = startIndex();
        size_t mid = s + count / 2;
        return data[mid];
    }

    char pop() {
        if (count == 0) {
            const_cast<DataManager<char>*>(this)->loadFromFile();
            if (count == 0)
                throw std::runtime_error("DataManager<char> is empty");
        }
        size_t idx = CAPACITY - 1;
        char value = data[idx];

        size_t s = startIndex();
        for (size_t i = idx; i > s; --i)
            data[i] = data[i - 1];

        --count;

        if (count == 0)
            loadFromFile();

        return value;
    }

    char popUpper() {
        char c = pop();
        return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    char popLower() {
        char c = pop();
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    size_t size() const { return count; }

    const char* begin() const { return data + startIndex(); }
    const char* end()   const { return data + CAPACITY; }
};
