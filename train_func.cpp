/*
    Файл с функциями для работы с записями
*/

#include "train_func.h"
#include "sort_func.h"
#include "delete_func.h"
#include <iostream>
#include <cstring>


// Вывод всех поездов
void print_train(Train* trains, int count)
{ 
    std::cout << "  Номер" << '|' << "    Конечная станция" << '|' << "      Дни следования" << '|'
    << " Отправление" << '|' << "Время в пути" << '|' << " Кол-во остановок";
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
        std::cout << std::endl;
    }
}


// Добавление нового поезда
void add_train(Train* trains, int& count)
{
    bool is_false = true;
    std::cin.ignore();  // Игнорирование предыдущего символа

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
            if (trains[count].time_departure[ch] != ':') {  // Сравнение с двоеточием
                hours_str[ch] = trains[count].time_departure[ch];
            }
            else {  // Если равны, то записываем индекс
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
            if (trains[count].time_way[ch] != ':') {  // Сравнение с двоеточием
                hours_str[ch] = trains[count].time_way[ch];
            }
            else {  // Если равны, то записываем индекс
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
}


// Удаление поезда по номеру в таблице
void delete_train(Train* trains, int& count, int type)
{
    std::cin.ignore();
    switch (type) {  // Выбор по типу удаления
        case 1:
            char number[5];
            std::cout << "Введите номер: ";
            std::cin.getline(number, 5);
            delete_train_by_number(trains, count, number);
            break;
        case 2:
            char end_station[256];
            std::cout << "Введите название станции: ";
            std::cin.getline(end_station, 256);
            delete_train_by_end_station(trains, count, end_station);
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

    switch (type) {  // Выбор по типу сортировки
        case 1:  // Сортировка по номеру
            number_sort(sort_trains, count, reverse);
            break;
        case 2:  // Сортировка по названию станции
            end_station_sort(sort_trains, count, reverse);
            break;
        case 3:  // Сортировка по времени отправления
            departure_time_sort(sort_trains, count, reverse);
            break;
        case 4:  // Сортировка по времени в пути
            way_time_sort(sort_trains, count, reverse);
            break;
        case 5:  // Сортировка по количеству остановок
            stop_count_sort(sort_trains, count, reverse);
            break;
        case 0:  // Отмена
            break;
        default:
            break;
    }

    print_train(sort_trains, count);  // Вывод поездов на экран

    if (in_file) {
        for (int i = 0; i < count; i++) {
            trains[i] = sort_trains[i];
        }
    }

    delete[] sort_trains;  // Очищение выделенной памяти
}