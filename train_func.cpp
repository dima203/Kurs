/*
    Файл с функциями для работы с записями
*/

#include "train_func.h"
#include "delete_func.h"
#include "file.h"
#include <iostream>
#include <cstring>
#include <fstream>


// Функция выделения дополнительной ячейки памяти
void add_memory_train(Train* &trains, int& count)
{
    Train* buffer_trains = new Train[count + 1];

    for (int i = 0; i < count; i++) {
        buffer_trains[i] = trains[i];
    }

    delete[] trains;
    trains = new Train[count + 1];

    for (int i = 0; i < count; i++) {
        trains[i] = buffer_trains[i];
    }
    delete[] buffer_trains;
}


// Функция очищения ячейки памяти
void sub_memory_train(Train* &trains, int& count)
{
    Train* buffer_trains = new Train[count - 1];

    for (int i = 0; i < count - 1; i++) {
        buffer_trains[i] = trains[i];
    }

    delete[] trains;
    trains = new Train[count - 1];

    for (int i = 0; i < count - 1; i++) {
        trains[i] = buffer_trains[i];
    }
    delete[] buffer_trains;
}


// Функция сохраниения состояния в буфер
void save_trains_in_buffer(Train* trains, TrainBuffer* trains_buffer, int count, int& buffer_count)
{
    if (buffer_count == 10) {
        delete[] trains_buffer[0].trains;
        for (int i = 0; i < buffer_count - 1; i++) {
            trains_buffer[i] = trains_buffer[i + 1];
        }
        buffer_count = 9;
    }

    trains_buffer[buffer_count].count = count;
    trains_buffer[buffer_count].trains = new Train[count];
    for (int i = 0; i < count; i++) {
        trains_buffer[buffer_count].trains[i] = trains[i];
    }

    buffer_count++;
}


// Вывод всех поездов
void print_train(Train* trains, int count)
{ 
    std::cout << "  Номер" << '|' << "    Конечная станция" << '|' << "      Дни следования" << '|'
    << " Отправление" << '|' << "Время в пути" << '|' << " Кол-во остановок" << '|' << "Время в пути в сутках";
    std::cout << std::endl;

    for (int i = 0; i < count; i++) {  // Цикл по всем записям
        std::cout.width(7);
        std::cout << trains[i].number;
        std::cout << '|'; 
        std::cout.width(20);
        std::cout << trains[i].end_station;
        std::cout << '|';
        std::cout.width(20);
        std::cout << trains[i].days;
        std::cout << '|';
        std::cout.width(12);
        std::cout << trains[i].time_departure;
        std::cout << '|';
        std::cout.width(12);
        std::cout << trains[i].time_way;
        std::cout << '|';
        std::cout.width(17);
        std::cout << trains[i].stop_count;

        // Расчет поля время в пути в сутках
        char hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;
        double time_in_hours;

        for (int ch = 0; ch < strlen(trains[i].time_way); ch++) {  // Запись часов записи
            if (trains[i].time_way[ch] != ':') {  // Сравнение с двоеточием
                hours_str1[ch] = trains[i].time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str1[0] = trains[i].time_way[end_ch];  // Запись минут записи
        minutes_str1[1] = trains[i].time_way[end_ch + 1];
        time_in_hours = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени записи

        std::cout << '|';
        std::cout.width(21);
        std::cout << time_in_hours / 24.;
        std::cout << std::endl;
    }
}


// Добавление нового поезда
void add_train(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count)
{
    bool is_false = true;
    std::cin.ignore();  // Игнорирование предыдущего символа
    
    save_trains_in_buffer(trains, trains_buffer, count, buffer_count);

    add_memory_train(trains, count);

    while (is_false) {  // Проверка на правильность ввода
        std::cout << "Номер поезда:" << std::endl;
        std::cin.getline(trains[count].number, 5);

        is_false = false;
        for (int i = 0; i < count; i++) {  // Цикл по всем записям
            if (strcmp(trains[count].number, trains[i].number) == 0) {  // Проверка на равенство номеров
                is_false = true;
                std::cout << "Такой номер уже есть в базе данных!!!" << std::endl;
            }
        }
    }

    std::cout << "Конечная станция:" << std::endl;
    std::cin.getline(trains[count].end_station, 256);

    std::cout << "Дни следования:" << std::endl;
    std::cin.getline(trains[count].days, 64);

    is_false = true;
    while (is_false) {
        std::cout << "Время отправления:" << std::endl;
        std::cin.getline(trains[count].time_departure, 7);

        char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;

        for (int ch = 0; ch < strlen(trains[count].time_departure); ch++) {  // Запись часов записи
            if (trains[count].time_departure[ch] != ':' && trains[count].time_departure[ch] != '.') {  // Сравнение с двоеточием
                hours_str[ch] = trains[count].time_departure[ch];
            }
            else {  // Если равны, то записываем индекс
                if (trains[count].time_departure[ch] == '.') {
                    trains[count].time_departure[ch] = ':';
                }
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str[0] = trains[count].time_departure[end_ch];  // Запись минут записи
        minutes_str[1] = trains[count].time_departure[end_ch + 1];

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
        std::cout << "Время в пути:" << std::endl;
        std::cin.getline(trains[count].time_way, 7);

        char hours_str[3] = "  ", minutes_str[3] = "  ";  // Промежуточные переменные для часов и минут
        int end_ch;

        for (int ch = 0; ch < strlen(trains[count].time_way); ch++) {  // Запись часов записи
            if (trains[count].time_way[ch] != ':' && trains[count].time_way[ch] != '.') {  // Сравнение с двоеточием
                hours_str[ch] = trains[count].time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                if (trains[count].time_way[ch] == '.') {
                    trains[count].time_way[ch] = ':';
                }
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str[0] = trains[count].time_way[end_ch];  // Запись минут записи
        minutes_str[1] = trains[count].time_way[end_ch + 1];

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
        std::cout << "Количество остановок:" << std::endl;
        std::cin >> trains[count].stop_count;

        if (trains[count].stop_count <= 0) {  // Проверка условия
            is_false = true;
            std::cout << "Количество остановок не может быть отрицательным или равным нулю!!!" << std::endl;
        }
        else {
            is_false = false;
        }
    }

    count++;  // Увеличение количества поездов на 1
    create_index_file(trains, count);
}


// Удаление поезда по номеру в таблице
void delete_train(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count, int type)
{
    std::cin.ignore();
    switch (type) {  // Выбор по типу удаления
        case 1:
            char number[5];
            std::cout << "Введите номер: ";
            std::cin.getline(number, 5);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_number(trains, count, number);
            break;
        case 2:
            char end_station[256];
            std::cout << "Введите название станции: ";
            std::cin.getline(end_station, 256);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_end_station(trains, count, end_station);
            break;
        case 3:
            char departure_time[7];
            std::cout << "Введите время: ";
            std::cin.getline(departure_time, 7);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_departure_time(trains, count, departure_time);
            break;
        case 4:
            char way_time[7];
            std::cout << "Введите время: ";
            std::cin.getline(way_time, 7);
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_way_time(trains, count, way_time);
            break;
        case 5:
            int stop_count;
            std::cout << "Введите количество остановок: ";
            std::cin >> stop_count;
            save_trains_in_buffer(trains, trains_buffer, count, buffer_count);
            delete_train_by_stop_count(trains, count, stop_count);
            break;
        case 0:  // Отмена
            break;
        default:
            break;
    }
}


// Сортировка поездов
void sort(Train* trains, int count, int type, bool reverse, bool in_file)
{
    Train* sort_trains = new Train[count];  // Создание временного массива поездов
    for (int i = 0; i < count; i++) {  // Переписываем все поезда из оригинального массива
        sort_trains[i] = trains[i];
    }
    std::ifstream file;
    int index[count];
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
            break;
        default:
            break;
    }
    // Чтение индексного файла
    file.read((char*)&count, sizeof(int));
    for (int i = 0; i < count; i++) {
        file.read((char*)(&index[i]), sizeof(int));
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

    print_train(sort_trains, count);  // Вывод поездов на экран

    if (in_file) {
        for (int i = 0; i < count; i++) {
            trains[i] = sort_trains[i];
        }
        create_index_file(trains, count);
    }

    delete[] sort_trains;  // Очищение выделенной памяти
}


// Функция отмены последнего действия
void undo_action(Train* &trains, TrainBuffer* trains_buffer, int& count, int& buffer_count) 
{
    if (buffer_count != 0) {
        count = trains_buffer[buffer_count - 1].count;
        delete[] trains;
        trains = new Train[count];
        for (int i = 0; i < count; i++) {
            trains[i] = trains_buffer[buffer_count - 1].trains[i];
        }
        delete[] trains_buffer[buffer_count - 1].trains;
        buffer_count--;
        create_index_file(trains, count);
    }
}
