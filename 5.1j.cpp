#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataManager.h"

int main() {
    // очистим dump.dat
    std::ofstream clear("dump.dat", std::ios::binary | std::ios::trunc);
    clear.close();

    DataManager<int>    dmInt;
    DataManager<double> dmDouble;
    DataManager<char>   dmChar;

    int    a[] = { 1, 2, 3, 4, 5 };
    double b[] = { 1.1, 2.2, 3.3 };
    char   c[] = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };

    dmInt.push(a, 5);
    dmDouble.push(b, 3);
    dmChar.push(c, sizeof(c) / sizeof(c[0]));

    std::cout << "Int DataManager: ";
    std::copy(dmInt.begin(), dmInt.end(),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    std::cout << "Double DataManager: ";
    std::copy(dmDouble.begin(), dmDouble.end(),
        std::ostream_iterator<double>(std::cout, " "));
    std::cout << "\n";

    std::cout << "Char DataManager: ";
    std::copy(dmChar.begin(), dmChar.end(),
        std::ostream_iterator<char>(std::cout, ""));
    std::cout << "\n";

    std::cout << "peek int: " << dmInt.peek() << "\n";
    std::cout << "peek char: " << dmChar.peek() << "\n";

    std::cout << "Char popUpper(): " << dmChar.popUpper() << "\n";
    std::cout << "Char popLower(): " << dmChar.popLower() << "\n";

    return 0;
}
