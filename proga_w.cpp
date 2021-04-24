/* 
    Главный файл программы
    Сюда подключены остальные файлы
*/

#include <iostream> 
#include "train.h"
#include "train_func.h"
#include "file.h"
#include "menu.h"


int main() 
{ 
    setlocale(0, "");

    int train_count = 0;  // Количество поездов на данный момент
    Train* train_station = new Train[train_count];  // Массив структур

    int is_file_not_open = 1;  // Флаг состояния открытия файла (изначально не открыт)
    char file_name[256];  // Строка с именем файла
    system("cls");
    while (is_file_not_open) {
        std::cout << "Введите имя файла: ";
        std::cin.getline(file_name, 256);  // Ввод имени файла
        is_file_not_open = get_records_from_file(file_name, train_station, train_count);  // Получение записей из файла и флага состояния
    }

    bool is_working = true;  // Флаг работы программы
    while (is_working) {  // Цикл работы программы
        int action;  // Переменная действия
        print_menu(); // Вывод меню действий на экран
        std::cout << "Выберите действие: ";
        std::cin >> action;
        system("cls");

        switch (action) {  // Меню выбора действия
            case 1:  // Вывод поездов на экран 
                print_train(train_station, train_count);
                break;

            case 2:  // Добавление нового поезда
                add_train(train_station, train_count);
                break;

            case 3:  // Удаление поезда по позиции
                int position;  // Переменная позиции поезда
                std::cout << "Введите позицию: ";
                std::cin >> position;
                delete_train(train_station, train_count, position);
                break;

            case 4:  // Сортировка поездов
                int type;  // Переменная типа сортировки
                bool reverse;  // Флаг направления сортировки (прямая / обратная)
                bool in_file;  // Флаг записи в файл
                print_sort_menu();  // Вывод меню типов сортировки
                std::cout << "Выберите тип сортировки: ";
                std::cin >> type;
                print_reverse_menu();  // Вывод меню флагов сортировки
                std::cout << "Выберите порядок сортировки: ";
                std::cin >> reverse;
                print_file_menu();  // Вывод меню флагов записи в файл
                std::cout << "Выберите тип записи в файл: ";
                std::cin >> in_file;
                sort(train_station, train_count, type, reverse);
                break;
            
            case 0:   // Выход из программы
                is_working = false;
                break;

            default:  // Если нет действия 
                std::cout << "Такого действия нет" << std::endl;
                break;
        }

        put_records_in_file(file_name, train_station, train_count);  // Запись данных в файл
    }

    delete[] train_station;  // Очистка пямяти
    return 0; 
}