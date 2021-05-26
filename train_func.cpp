/*
    Файл с функциями для работы с записями
*/

#include "train_func.h"
#include "delete_func.h"
#include "select_func.h"
#include "config_func.h"
#include "menu.h"
#include "file.h"
#include "clear.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <span>


// Вывод всех поездов
// ======================================================================================
void print_train(Train*& trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{ 
    std::cout << "  Номер" << '|' << "    Конечная станция" << '|' << "      Дни следования" << '|'
    << " Отправление" << '|' << "Время в пути" << '|' << " Кол-во остановок" << '|' << "Время в пути в сутках";
    std::cout << std::endl;

    for (auto train: std::span(trains, count)) {  // Цикл по всем записям
        std::cout << std::setw(7) << train.number << '|'; 
        std::cout << std::setw(20) << train.end_station << '|';
        std::cout << std::setw(20) << train.days << '|';
        std::cout << std::setw(12) << train.time_departure << '|';
        std::cout << std::setw(12) << train.time_way << '|';
        std::cout << std::setw(17) << train.stop_count << '|';

        // Расчет поля время в пути в сутках
        char hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;
        double time_in_hours;

        for (int ch = 0; ch < strlen(train.time_way); ch++) {  // Запись часов записи
            if (train.time_way[ch] != ':') {  // Сравнение с двоеточием
                hours_str1[ch] = train.time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str1[0] = train.time_way[end_ch];  // Запись минут записи
        minutes_str1[1] = train.time_way[end_ch + 1];
        time_in_hours = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени записи

        std::cout << std::setw(21) << time_in_hours / 24.;
        std::cout << std::endl;
    }
}


// Добавление нового поезда
// ======================================================================================
void add_train(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    print_train(trains, trains_buffer, count, buffer_count);
    bool is_false = true;
    
    save_trains_in_buffer(trains, trains_buffer, count, buffer_count);

    add_memory_train(trains, count);

    int pos;  // Позиция для добавления

    while (true) {
        std::cout << "Введите позицию для добавления записи после указанной записи (-1 - в конец): ";
        std::cin >> pos;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            if (pos < -1) {
                std::cout << "Позиция для добавления должна быть больше или равна -1!!!" << std::endl;
            } 
            else if (pos == -1 || pos > count) {  // Проверка на добавление в конец
                pos = count;
                break;
            } 
            else {
                for (int i = count - 1; i >= pos; i--) {  // Сдвиг элементов на один вперед
                    trains[i + 1] = trains[i];
                }
                break;
            }
        }
    }

    while (is_false) {  // Проверка на правильность ввода
        std::cout << "Номер поезда: ";
        char input_buffer[1024];
        std::cin.getline(input_buffer, 1024);

        is_false = false;
        if (strlen(input_buffer) > 4) {
            std::cout << "Номер поезда должен состоять из менее, чем 5 символов!!!" << std::endl;
            is_false = true;
            continue;
        }
        else {
            for (int i = 0; i < strlen(input_buffer); i++) {
                if (int(input_buffer[i]) < 48 || int(input_buffer[i]) > 57) {
                    is_false = true;
                    std::cout << "Номер должен состоять из цифр!!!" << std::endl;
                    break;
                }
            }
            if (is_false) {
                continue;
            }
            strcpy(trains[pos].number, input_buffer);
        }
        for (int i = 0; auto train: std::span(trains, count)) {  // Цикл по всем записям
            if (i == pos) continue;
            if (strcmp(trains[pos].number, train.number) == 0) {  // Проверка на равенство номеров
                is_false = true;
                std::cout << "Такой номер уже есть в базе данных!!!" << std::endl;
            }
            i++;
        }
    }

    std::cout << "Конечная станция: ";
    std::cin.getline(trains[pos].end_station, 256);

    std::cout << "Дни следования: ";
    std::cin.getline(trains[pos].days, 64);

    is_false = true;
    while (is_false) {
        std::cout << "Время отправления: ";
        std::cin.getline(trains[pos].time_departure, 7);

        char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;

        for (int ch = 0; ch < strlen(trains[pos].time_departure); ch++) {  // Запись часов записи
            if (trains[pos].time_departure[ch] != ':' && trains[pos].time_departure[ch] != '.') {  // Сравнение с двоеточием
                hours_str[ch] = trains[pos].time_departure[ch];
            }
            else {  // Если равны, то записываем индекс
                if (trains[pos].time_departure[ch] == '.') {
                    trains[pos].time_departure[ch] = ':';
                }
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str[0] = trains[pos].time_departure[end_ch];  // Запись минут записи
        minutes_str[1] = trains[pos].time_departure[end_ch + 1];

        int hours = std::stoi(hours_str);  // Перевод в целое число 
        int mins = std::stoi(minutes_str);

        if (hours < 0 || mins < 0 || mins >= 60) {  // Проверка условий
            std::cout << "Неправильно задано время!!!" << std::endl;
            is_false = true;
        }
        else {
            is_false = false;
        }
    }

    is_false = true;
    while (is_false) {
        std::cout << "Время в пути: ";
        std::cin.getline(trains[pos].time_way, 7);

        char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;

        for (int ch = 0; ch < strlen(trains[pos].time_way); ch++) {  // Запись часов записи
            if (trains[pos].time_way[ch] != ':' && trains[pos].time_way[ch] != '.') {  // Сравнение с двоеточием
                hours_str[ch] = trains[pos].time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                if (trains[pos].time_way[ch] == '.') {
                    trains[pos].time_way[ch] = ':';
                }
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str[0] = trains[pos].time_way[end_ch];  // Запись минут записи
        minutes_str[1] = trains[pos].time_way[end_ch + 1];

        int hours = std::stoi(hours_str);  // Перевод в целое число 
        int mins = std::stoi(minutes_str);

        if (hours < 0 || mins < 0 || mins >= 60) {  // Проверка условий
            std::cout << "Неправильно задано время!!!" << std::endl;
            is_false = true;
        }
        else {
            is_false = false;
        }
    }

    is_false = true;
    while (true) {  // Проверка на правильность ввода
        std::cout << "Количество остановок: ";
        std::cin >> trains[pos].stop_count;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            if (trains[pos].stop_count <= 0) {
                std::cout << "Количество остановок должно быть больше нуля!!!" << std::endl;
            }
            else {
                break;
            }
        }
    }

    count++;  // Увеличение количества поездов на 1
    create_index_file(trains, count);
}


// Функция изменения полей записи
// ======================================================================================
void change_train(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    char _number[5];  // Номер записи для изменения
    bool is_stock = false;  // Флаг наличия номера
    int _index = 0;  // Индекс найденного элемента

    save_trains_in_buffer(trains, trains_buffer, count, buffer_count);

    while (!is_stock) {  // Проверка на правильность ввода
        print_train(trains, trains_buffer, count, buffer_count);
        std::cout << "Введите номер поезда для изменения: ";
        std::cin.getline(_number, 5);

        for (int i = 0; auto train: std::span(trains, count)) {  // Цикл по всем записям
            if (strcmp(_number, train.number) == 0) {  // Проверка на равенство номеров
                is_stock = true;
                _index = i;
                break;
            }
            i++;
        }
        clear();
        if (!is_stock) {
            std::cout << "Такого номера нет!!!" << std::endl;
        }
    }   

    bool is_working = true;  // Флаг работы программы
    while (is_working) {
        int action;

        std::cout << "  Номер" << '|' << "    Конечная станция" << '|' << "      Дни следования" << '|'
        << " Отправление" << '|' << "Время в пути" << '|' << " Кол-во остановок" << '|' << "Время в пути в сутках";

        std::cout << std::endl;
        std::cout.width(7);
        std::cout << trains[_index].number;
        std::cout << '|'; 
        std::cout.width(20);
        std::cout << trains[_index].end_station;
        std::cout << '|';
        std::cout.width(20);
        std::cout << trains[_index].days;
        std::cout << '|';
        std::cout.width(12);
        std::cout << trains[_index].time_departure;
        std::cout << '|';
        std::cout.width(12);
        std::cout << trains[_index].time_way;
        std::cout << '|';
        std::cout.width(17);
        std::cout << trains[_index].stop_count;

        char hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;
        double time_in_hours;

        for (int ch = 0; ch < strlen(trains[_index].time_way); ch++) {  // Запись часов записи
            if (trains[_index].time_way[ch] != ':') {  // Сравнение с двоеточием
                hours_str1[ch] = trains[_index].time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str1[0] = trains[_index].time_way[end_ch];  // Запись минут записи
        minutes_str1[1] = trains[_index].time_way[end_ch + 1];
        time_in_hours = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени записи

        std::cout << '|';
        std::cout.width(21);
        std::cout << time_in_hours / 24.;
        std::cout << std::endl;

        print_change_menu();
        while (true) {
            std::cout << "Выберите действие: ";
            std::cin >> action;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(32767, '\n');
                std::cout << "Неправильный ввод!!!" << std::endl;
            }
            else {
                std::cin.ignore(32767, '\n');
                break;
            }
        }

        clear();

        bool is_false = true;
        switch (action) {
            case 1:  // Изменение номера
                is_false = true;
                while (is_false) {  // Проверка на правильность ввода
                    std::cout << "Номер поезда:";
                    char input_buffer[1024];
                    std::cin.getline(input_buffer, 1024);

                    is_false = false;
                    if (strlen(input_buffer) > 4) {
                        std::cout << "Номер поезда должен состоять из менее, чем 5 символов!!!" << std::endl;
                        is_false = true;
                        continue;
                    }
                    else {
                        for (int i = 0; i < strlen(input_buffer); i++) {
                            if (int(input_buffer[i]) < 48 || int(input_buffer[i]) > 57) {
                                is_false = true;
                                std::cout << "Номер должен состоять из цифр!!!" << std::endl;
                                break;
                            }
                        }
                        if (is_false) {
                            continue;
                        }
                        strcpy(trains[_index].number, input_buffer);
                    }
                    for (int i = 0; auto train: std::span(trains, count)) {  // Цикл по всем записям
                        if (i == _index) continue;
                        if (strcmp(trains[_index].number, train.number) == 0) {  // Проверка на равенство номеров
                            is_false = true;
                            std::cout << "Такой номер уже есть в базе данных!!!" << std::endl;
                        }
                        i++;
                    }
                }
                break;
            case 2:  // Изменение конечной станции
                std::cout << "введите новое название конечной станции: ";
                std::cin.getline(trains[_index].end_station, 256);
                break;
            case 3:  // Изменение дней следования
                std::cout << "Введите новые дни следования: ";
                std::cin.getline(trains[_index].days, 64);
                break;
            case 4:  // Изменение времени отправления
                is_false = true;
                while (is_false) {
                    std::cout << "Введите новое время отправления: ";
                    std::cin.getline(trains[_index].time_departure, 7);

                    char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
                    int end_ch;

                    for (int ch = 0; ch < strlen(trains[_index].time_departure); ch++) {  // Запись часов записи
                        if (trains[_index].time_departure[ch] != ':' && trains[_index].time_departure[ch] != '.') {  // Сравнение с двоеточием
                            hours_str[ch] = trains[_index].time_departure[ch];
                        }
                        else {  // Если равны, то записываем индекс
                            if (trains[_index].time_departure[ch] == '.') {
                                trains[_index].time_departure[ch] = ':';
                            }
                            end_ch = ch + 1;
                            break;
                        }
                    }

                    minutes_str[0] = trains[_index].time_departure[end_ch];  // Запись минут записи
                    minutes_str[1] = trains[_index].time_departure[end_ch + 1];

                    int hours = std::stoi(hours_str);  // Перевод в целое число 
                    int mins = std::stoi(minutes_str);

                    if (hours < 0 || mins < 0 || mins >= 60) {  // Проверка условий
                        std::cout << "Неправильно задано время!!!" << std::endl;
                        is_false = true;
                    }
                    else {
                        is_false = false;
                    }
                }
                break;
            case 5:  // Изменение времени в пути
                is_false = true;
                while (is_false) {
                    std::cout << "Введите новое время в пути: ";
                    std::cin.getline(trains[_index].time_way, 7);

                    char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
                    int end_ch;

                    for (int ch = 0; ch < strlen(trains[_index].time_way); ch++) {  // Запись часов записи
                        if (trains[_index].time_way[ch] != ':' && trains[_index].time_way[ch] != '.') {  // Сравнение с двоеточием
                            hours_str[ch] = trains[_index].time_way[ch];
                        }
                        else {  // Если равны, то записываем индекс
                            if (trains[_index].time_way[ch] == '.') {
                                trains[_index].time_way[ch] = ':';
                            }
                            end_ch = ch + 1;
                            break;
                        }
                    }

                    minutes_str[0] = trains[_index].time_way[end_ch];  // Запись минут записи
                    minutes_str[1] = trains[_index].time_way[end_ch + 1];

                    int hours = std::stoi(hours_str);  // Перевод в целое число 
                    int mins = std::stoi(minutes_str);

                    if (hours < 0 || mins < 0 || mins >= 60) {  // Проверка условий
                        std::cout << "Неправильно задано время!!!" << std::endl;
                        is_false = true;
                    }
                    else {
                        is_false = false;
                    }
                }
                break;
            case 6:  // Изменение количества остановок
                while (true) {
                    std::cout << "Введите новое количество остановок: ";
                    std::cin >> trains[_index].stop_count;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');
                        std::cout << "Неправильный ввод!!!" << std::endl;
                    }
                    else {
                        std::cin.ignore(32767, '\n');
                        if (trains[_index].stop_count <= 0) {  // Проверка условия
                            std::cout << "Количество остановок не может быть отрицательным или равным нулю!!!" << std::endl;
                        }
                        else {
                            break;
                        }
                    }
                }
                break;
            case 0:  // Завершить изменение
                is_working = false;
                break;
            default:
                std::cout << "Такого действия нет" << std::endl;
                break;
        }
    }
    create_index_file(trains, count);
}


// Удаление поезда по номеру в таблице
// ======================================================================================
void delete_train(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    print_train(trains, trains_buffer, count, buffer_count);
    print_delete_menu();

    int type;  // Переменная типа удаления

    while (true) {
        std::cout << "Выберите тип удаления: ";
        std::cin >> type;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            if (type < 0 || type > 5) {
                std::cout << "Такого типа нет!!!" << std::endl;
            }
            else {
                break;
            }
        }
    }

    switch (type) {  // Выбор по типу удаления
        case 1:  // Удаление по номеру
            char number[5];
            std::cout << "Введите номер: ";
            std::cin.getline(number, 5);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_number(trains, count, number);
            break;
        case 2:  // Удаление по конечной станции
            char end_station[256];
            std::cout << "Введите название станции: ";
            std::cin.getline(end_station, 256);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_end_station(trains, count, end_station);
            break;
        case 3:  // Удаление по времени отправления
            char departure_time[7];
            std::cout << "Введите время: ";
            std::cin.getline(departure_time, 7);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_departure_time(trains, count, departure_time);
            break;
        case 4:  // Удаление по времени в пути
            char way_time[7];
            std::cout << "Введите время: ";
            std::cin.getline(way_time, 7);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_way_time(trains, count, way_time);
            break;
        case 5:  // Удаление по количеству остановок
            int stop_count;
            while (true) {  // Проверка на правильность ввода
                std::cout << "Введите количество остановок: ";
                std::cin >> stop_count;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Неправильный ввод!!!" << std::endl;
                }
                else {
                    std::cin.ignore(32767, '\n');
                    if (stop_count <= 0) {
                        std::cout << "Количество остановок должно быть больше нуля!!!" << std::endl;
                    }
                    else {
                        break;
                    }
                }
            }
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_stop_count(trains, count, stop_count);
            break;
        case 0:  // Отмена
            break;
    }
    create_index_file(trains, count);
}


// Сортировка поездов
// ======================================================================================
void sort_train(Train*& trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    int type;  // Переменная типа сортировки
    bool reverse;  // Флаг направления сортировки (прямая / обратная)
    bool in_file;  // Флаг записи в файл

    print_sort_menu();  // Вывод меню типов сортировки
    while (true) {
        std::cout << "Выберите тип сортировки: ";
        std::cin >> type;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            if (type < 0 || type > 5) {
                std::cout << "Такого типа нет!!!" << std::endl;
            }
            else {
                break;
            }
        }
    }

    print_reverse_menu();  // Вывод меню флагов сортировки
    while (true) {
        std::cout << "Выберите порядок сортировки: ";
        std::cin >> reverse;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            break;
        }
    }
    
    print_file_menu();  // Вывод меню флагов записи в файл
    while (true) {
        std::cout << "Выберите тип записи в файл: ";
        std::cin >> in_file;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            break;
        }
    }

    Train* sort_trains = new Train[count];  // Создание временного массива поездов
    for (int i = 0; auto train: std::span(trains, count)) {  // Переписываем все поезда из оригинального массива
        sort_trains[i] = train;
        i++;
    }
    std::ifstream file;
    int index[count];
    bool is_end = false;
    switch (type) {  // Выбор по типу сортировки
        case 1:  // Сортировка по номеру
            file.open("index_file/number_sort.txt", std::ios::binary);
            break;
        case 2:  // Сортировка по названию станции
            file.open("index_file/end_station_sort.txt", std::ios::binary);
            break;
        case 3:  // Сортировка по времени отправления
            file.open("index_file/departure_time_sort.txt", std::ios::binary);
            break;
        case 4:  // Сортировка по времени в пути
            file.open("index_file/way_time_sort.txt", std::ios::binary);
            break;
        case 5:  // Сортировка по количеству остановок
            file.open("index_file/stop_count_sort.txt", std::ios::binary);
            break;
        case 0:  // Отмена
            is_end = true;
            break;
    }
    if (!is_end) {
        // Чтение индексного файла
        file.read((char*)&count, sizeof(int));
        for (auto & i: std::span(index, count)) {
            file.read((char*)(&i), sizeof(int));
        }

        // Сортировка в срртветствии с индексами
        int index_index = (reverse) ? count - 1 : 0;
        for (int i = 0; i < count; i++) {
            sort_trains[i] = trains[index[index_index]];
            if (reverse) {
                index_index--;
            }
            else {
                index_index++;
            }
        }

        print_train(sort_trains, trains_buffer, count, buffer_count);  // Вывод поездов на экран

        if (in_file) {
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            for (int i = 0; auto train: std::span(sort_trains, count)) {
                trains[i] = train;
                i++;
            }
            create_index_file(trains, count);
        }
    }

    delete[] sort_trains;  // Очищение выделенной памяти
}


// Функция выборки записей по полям
// ======================================================================================
void select_train(Train*& trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    int type;  // Тип выборки/поиска
    print_train(trains, trains_buffer, count, buffer_count);
    print_selection_menu();
    while (true) {
        std::cout << "Выберите тип выборки: ";
        std::cin >> type;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неправильный ввод!!!" << std::endl;
        }
        else {
            std::cin.ignore(32767, '\n');
            if (type < 0 || type > 5) {
                std::cout << "Такого типа нет!!!" << std::endl;
            }
            else {
                break;
            }
        }
    }

    switch (type) {
        case 1:  // Выборка по номеру
            int down_number, up_number;  // Диапазон номеров
            std::cout << "Введите диапазон значений" << std::endl;

            while (true) {  // Проверка на правильность ввода
                std::cout << "Нижняя граница: ";
                std::cin >> down_number;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Неправильный ввод!!!" << std::endl;
                }
                else {
                    std::cin.ignore(32767, '\n');
                    if (down_number > 9999 || down_number <= 0) {
                        std::cout << "Номер поезда должен состоять из менее, чем 5 символов, и быть больше нуля!!!" << std::endl;
                    }
                    else {
                       break;
                    }
                }
            }
            
           while (true) {  // Проверка на правильность ввода
                std::cout << "Верхняя граница: ";
                std::cin >> up_number;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Неправильный ввод!!!" << std::endl;
                }
                else {
                    std::cin.ignore(32767, '\n');
                    if (up_number > 9999 || up_number <= 0) {
                        std::cout << "Номер поезда должен состоять из менее, чем 5 символов, и быть больше нуля!!!" << std::endl;
                    }
                    else {
                       break;
                    }
                }
            }
            
            select_by_number(trains, trains_buffer, count, buffer_count, down_number, up_number);
            break;
        case 2:  // Выборка по названию конечной станции
            char end_station[256];
            std::cout << "Введите название конечной станции: ";
            std::cin.getline(end_station, 256);
            select_by_end_station(trains, trains_buffer, count, buffer_count, end_station);
            break;
        case 3:  // Выборка по времени отправления
            char down_departure_time[7], up_departure_time[7];  // Диапазон веремени отправления
            std::cout << "Введите диапазон значений" << std::endl;
            std::cout << "Нижняя граница: ";
            std::cin.getline(down_departure_time, 7);
            std::cout << "Верхняя граница: ";
            std::cin.getline(up_departure_time, 7);
            select_by_departure_time(trains, trains_buffer, count, buffer_count, down_departure_time, up_departure_time);
            break;
        case 4:  // Выборка по времени в пути
            char down_way_time[7], up_way_time[7];  // Диапазон времени в пути
            std::cout << "Введите диапазон значений" << std::endl;
            std::cout << "Нижняя граница: ";
            std::cin.getline(down_way_time, 7);
            std::cout << "Верхняя граница: ";
            std::cin.getline(up_way_time, 7);
            select_by_way_time(trains, trains_buffer, count, buffer_count, down_way_time, up_way_time);
            break;
        case 5:  // Выборка по количеству остановок
            int down_stop_number, up_stop_number;  // Диапазон количества остановок
            std::cout << "Введите диапазон значений" << std::endl;
            while (true) {  // Проверка на правильность ввода
                std::cout << "Нижняя граница: ";
                std::cin >> down_stop_number;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Неправильный ввод!!!" << std::endl;
                }
                else {
                    std::cin.ignore(32767, '\n');
                    if (down_stop_number <= 0) {
                        std::cout << "Количество остановок должно быть больше нуля!!!" << std::endl;
                    }
                    else {
                       break;
                    }
                }
            }
            
           while (true) {  // Проверка на правильность ввода
                std::cout << "Верхняя граница: ";
                std::cin >> up_stop_number;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(32767, '\n');
                    std::cout << "Неправильный ввод!!!" << std::endl;
                }
                else {
                    std::cin.ignore(32767, '\n');
                    if (up_stop_number <= 0) {
                        std::cout << "Количество остановок должно быть больше нуля!!!" << std::endl;
                    }
                    else {
                       break;
                    }
                }
            }
            select_by_stop_count(trains, trains_buffer, count, buffer_count, down_stop_number, up_stop_number);
            break;
        case 0:  // Отмена
            break;
    }
}


// Функция отмены последнего действия
// ======================================================================================
void undo_action(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count) 
{
    if (buffer_count != 0) {  // Проверка на наличие состояний для отмены
        count = trains_buffer[buffer_count - 1].count;  // Получение количества поездов
        delete[] trains;  // Удаление указателя
        trains = new Train[count];  // Создание нового с новым количеством
        for (int i = 0; auto train: std::span(trains_buffer[buffer_count - 1].trains, count)) {
            trains[i] = train;  // Перепись данных из буфера в массив
            i++;
        }
        delete[] trains_buffer[buffer_count - 1].trains;  // Удаление буфера
        buffer_count--;  // Уменьшение количества сохраненных состояний
        create_index_file(trains, count);
    }
}
