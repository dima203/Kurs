/* 
    Главный файл программы
    Сюда подключены остальные файлы
*/

#include "train.h"
#include "train_func.h"
#include "file.h"
#include "menu.h"
#include "clear.h"

#include <iostream> 


int main() 
{ 
    setlocale(0, "");

    int train_count = 0;  // Количество поездов на данный момент
    Train* train_station = new Train[train_count];  // Массив структур

    int train_buffer_count = 0;  // Количество действий в буфере
    TrainBuffer* trains_buffer = new TrainBuffer[10];  // Буфер для хранения последних действий

    // Массив указателей на функции
    void(*menu_func_arr[])(Train*&, TrainBuffer*, int&, int&) = {print_train, add_train, change_train, delete_train, sort_train, select_train, undo_action};

    int is_file_not_open = 1;  // Флаг состояния открытия файла (изначально не открыт)
    char file_name[256];  // Строка с именем файла
    clear();
    while (is_file_not_open) {  // Цикл открытия файла
        std::cout << "Введите имя файла: ";
        std::cin.getline(file_name, 256);  // Ввод имени файла
        is_file_not_open = get_records_from_file(file_name, train_station, train_count);  // Получение записей из файла и флага состояния
    }

    create_index_file(train_station, train_count);  // Создание индексных файлов

    bool is_working = true;  // Флаг работы программы
    while (is_working) {  // Цикл работы программы
        int action;  // Переменная действия
        print_menu(); // Вывод меню действий на экран
        std::cout << "Выберите действие: ";
        std::cin >> action;
        clear();

        if (action >= 0 and action <= 7) {
            if (action == 0) {
                is_working = false;
            }
            else {
                menu_func_arr[action - 1](train_station, trains_buffer, train_count, train_buffer_count);
            }
        }
        else {
            std::cout << "Такого действия нет" << std::endl;
        }

        put_records_in_file(file_name, train_station, train_count);  // Запись данных в файл
    }

    delete[] train_station;  // Очистка пямяти
    return 0; 
}
