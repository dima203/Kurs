/* 
    Главный файл программы
    Сюда подключены остальные файлы
*/

#include <iostream> 
#include "train.h"
#include "train_func.h"
#include "file.h"
#include "menu.h"
#include "clear.h"


int main() 
{ 
    setlocale(0, "");

    int train_count = 0;  // Количество поездов на данный момент
    Train* train_station = new Train[train_count];  // Массив структур

    int train_buffer_count = 0;  // Количество действий в буфере
    TrainBuffer* trains_buffer = new TrainBuffer[10];  // Буфер для хранения последних действий

    int is_file_not_open = 1;  // Флаг состояния открытия файла (изначально не открыт)
    char file_name[256];  // Строка с именем файла
    clear();
    while (is_file_not_open) {
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

        switch (action) {  // Меню выбора действия
            case 1:  // Вывод поездов на экран 
                print_train(train_station, train_count);
                break;

            case 2:  // Добавление нового поезда
                int pos;
                print_train(train_station, train_count);
                std::cout << "Введите позицию для добавления записи после указанной записи (-1 - в конец): ";
                std::cin >> pos;
                add_train(train_station, trains_buffer, train_count, train_buffer_count, pos);
                break;

            case 3:  // Изменение записи
                change_train(train_station, trains_buffer, train_count, train_buffer_count);
                break;

            case 4:  // Удаление поездов по полям
                int delete_type;  // Переменная типа удаления
                print_train(train_station, train_count);
                print_delete_menu();
                std::cout << "Введите тип удаления: ";
                std::cin >> delete_type;
                delete_train(train_station, trains_buffer, train_count, train_buffer_count, delete_type);
                break;

            case 5:  // Сортировка поездов
                int sort_type;  // Переменная типа сортировки
                bool reverse;  // Флаг направления сортировки (прямая / обратная)
                bool in_file;  // Флаг записи в файл
                print_sort_menu();  // Вывод меню типов сортировки
                std::cout << "Выберите тип сортировки: ";
                std::cin >> sort_type;
                print_reverse_menu();  // Вывод меню флагов сортировки
                std::cout << "Выберите порядок сортировки: ";
                std::cin >> reverse;
                print_file_menu();  // Вывод меню флагов записи в файл
                std::cout << "Выберите тип записи в файл: ";
                std::cin >> in_file;
                sort_train(train_station, trains_buffer, train_count, train_buffer_count, sort_type, reverse, in_file);
                break;
            
            case 6:  // Выборка записей по полям
                int select_type;
                print_train(train_station, train_count);
                print_selection_menu();
                std::cout << "Выберите тип выборки: ";
                std::cin >> select_type;
                select_train(train_station, train_count, select_type);
                break;

            case 7:  // Отмена последнего действия
                undo_action(train_station, trains_buffer, train_count, train_buffer_count);
                break;
            
            case 0:  // Выход из программы
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
