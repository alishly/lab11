#include "tasks.h"
#include <iostream>
#include "windows.h"

int main() {
    int choice;
    SetConsoleOutputCP(65001);
    SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(65001);
    SetConsoleCP(CP_UTF8);

    do {
        std::cout << "\n МЕНЮ " << std::endl;
        std::cout << "1. Задача 68 " << std::endl;
        std::cout << "2. Задача 42 " << std::endl;
        std::cout << "3. Задача 45 " << std::endl;
        std::cout << "4. Задача 48 " << std::endl;
        std::cout << "5. Задача 3 " << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            case 1:
                Zad1();
                break;
            case 2:
                Zad2();
                break;
            case 3:
                Zad3();
                break;
            case 4:
                Zad4();
                break;
            case 5:
                Zad5();
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);

    return 0;
}