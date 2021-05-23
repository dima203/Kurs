/*
    Файл с функциями для удаления записей
*/

#include "delete_func.h"
#include "config_func.h"
#include "file.h"

#include <iostream>
#include <cstring>


// Удаление поезда по номеру
// ======================================================================================
void delete_train_by_number(Train* &trains, int& count, char number[5]) 
{
    int i = 0;
    while (i < count) {
        if (strcmp(trains[i].number, number) == 0) {  // Сравнение номеров
            if (i != count - 1) {
                for (int j = i; j < count - 1; j++) {  // Сдвиг записей на один назад
                    trains[j] = trains[j + 1];
                }

                sub_memory_train(trains, count);
                count--;
                break;
            }
            else {
                sub_memory_train(trains, count);
                count--;
                break;
            }
        }
        i++;
    }
    create_index_file(trains, count);
}


// Удаление поездов по названию конечной станции
// ======================================================================================
void delete_train_by_end_station(Train* &trains, int& count, char end_station[256])
{
    int i = 0;
    while (i < count) {
        bool is_equal = true;
        if (strlen(trains[i].end_station) < strlen(end_station)) {  // Проверка на длину
            is_equal = false;
        }
        else {
            for (int j = 0; j < strlen(end_station); j++) {  // Сравнение названия станции
                if (trains[i].end_station[j] != end_station[j]) {
                    is_equal = false;
                    break;
                }
            }
        }
        if (is_equal) {
            for (int j = i; j < count - 1; j++) {  // Сдвиг на один назад
                trains[j] = trains[j + 1];
            }
            i--;
            sub_memory_train(trains, count);
            count--;
        }
        i++;
    }
    create_index_file(trains, count);
}


// Удаление поездов по времени отправления
// ======================================================================================
void delete_train_by_departure_time(Train* &trains, int& count, char departure_time[7])
{
    int i = 0;
    while (i < count) {
        bool is_equal = true;
        if (strlen(trains[i].time_departure) < strlen(departure_time)) {  // Проверка на длину
            is_equal = false;
        }
        else {
            for (int j = 0; j < strlen(departure_time); j++) {  // Сравнение времени отправления
                if (trains[i].time_departure[j] != departure_time[j]) {
                    is_equal = false;
                    break;
                }
            }
        }
        if (is_equal) {
            for (int j = i; j < count - 1; j++) {  // Сдвиг на один назад
                trains[j] = trains[j + 1];
            }
            i--;
            sub_memory_train(trains, count);
            count--;
        }
        i++;
    }
    create_index_file(trains, count);
}


// Удаление поездов по времени в пути
// ======================================================================================
void delete_train_by_way_time(Train* &trains, int& count, char way_time[7])
{
    int i = 0;
    while (i < count) {
        bool is_equal = true;
        if (strlen(trains[i].time_way) < strlen(way_time)) {  // Проверка на длину
            is_equal = false;
        }
        else {
            for (int j = 0; j < strlen(way_time); j++) {  // Сравнение времени в пути
                if (trains[i].time_way[j] != way_time[j]) {
                    is_equal = false;
                    break;
                }
            }
        }
        if (is_equal) {
            for (int j = i; j < count - 1; j++) {  // Сдвиг на один назад
                trains[j] = trains[j + 1];
            }
            i--;
            sub_memory_train(trains, count);
            count--;
        }
        i++;
    }
    create_index_file(trains, count);
}


// Удаление поездов по количеству остановок
// ======================================================================================
void delete_train_by_stop_count(Train* &trains, int& count, int stop_count)
{
    int i = 0;
    while (i < count) {
        if (trains[i].stop_count == stop_count) {  // Сравнение количества остановок
            for (int j = i; j < count - 1; j++) {  // Сдвиг на один назад
                trains[j] = trains[j + 1];
            }
            i--;
            sub_memory_train(trains, count);
            count--;
        }
        i++;
    }
    create_index_file(trains, count);
}
