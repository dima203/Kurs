/*
    Файл с функциями выборки записей по полям
*/

#include "select_func.h"
#include "train_func.h"
#include "train.h"

#include <iostream>
#include <cstring>


// Выборка по номеру
void select_by_number(Train* trains, TrainBuffer* trains_buffer1, int count, int buffer_count, int down_number, int up_number)
{
    Train* trains_buffer = new Train[count];  // Буфер поездов для выборки
    int selection_count = 0;

    for (int i = 0; i < count; i++) {
        int _number = std::stoi(trains[i].number);
        if (_number >= down_number && _number <= up_number) {
            trains_buffer[selection_count] = trains[i];
            selection_count++;
        }
    }
    print_train(trains_buffer, trains_buffer1, selection_count, buffer_count);
    delete[] trains_buffer;
}


// Выборка по названию конечной станции
void select_by_end_station(Train* trains, TrainBuffer* trains_buffer1, int count, int buffer_count, char end_station[256])
{
    Train* trains_buffer = new Train[count];  // Буфер поездов для выборки
    int selection_count = 0;

    int i = 0;
    while (i < count) {
        bool is_equal = true;
        if (strlen(trains[i].end_station) < strlen(end_station)) {
            is_equal = false;
        }
        else {
            for (int j = 0; j < strlen(end_station); j++) {
                if (trains[i].end_station[j] != end_station[j]) {
                    is_equal = false;
                    break;
                }
            }
        }
        if (is_equal) {
            trains_buffer[selection_count] = trains[i];
            selection_count++;
        }
        i++;
    }
    print_train(trains_buffer, trains_buffer1, selection_count, buffer_count);
    delete[] trains_buffer;
}


// Выборка по времени отправления
void select_by_departure_time(Train* trains, TrainBuffer* trains_buffer1, int count, int buffer_count, char down_departure_time[7], char up_departure_time[7])
{
    Train* trains_buffer = new Train[count];  // Буфер поездов для выборки
    int selection_count = 0;

    float down_time, up_time;  // Пременные времени в часах (дробные)
    int end_ch;  // Индекс конца цифр часов

    char hours_str2[3] = "  ", minutes_str2[3] = "  ", hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут

    for (int ch = 0; ch < strlen(down_departure_time); ch++) {
        if (down_departure_time[ch] != ':') {  // Сравнение с двоеточием
            hours_str1[ch] = down_departure_time[ch];
        }
        else {  // Если равны, то записываем индекс
            end_ch = ch + 1;
            break;
        }
    }

    minutes_str1[0] = down_departure_time[end_ch];  // Запись минут i-ой записи
    minutes_str1[1] = down_departure_time[end_ch + 1];
    down_time = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени i-ой записи

    for (int ch = 0; ch < strlen(up_departure_time); ch++) {
        if (up_departure_time[ch] != ':') {
            hours_str2[ch] = up_departure_time[ch];
        }
        else {
            end_ch = ch + 1;
            break;
        }
    }
    
    minutes_str2[0] = up_departure_time[end_ch];
    minutes_str2[1] = up_departure_time[end_ch + 1];
    up_time = float(std::stoi(hours_str2)) + float(std::stoi(minutes_str2)) / 60.0;

    int i = 0;
    while (i < count) {
        bool is_equal = true;

        double _time; 
        char _hours_str[3] = "  ", _minutes_str[3] = "  ";

        for (int ch = 0; ch < strlen(trains[i].time_departure); ch++) {
            if (trains[i].time_departure[ch] != ':') {
                _hours_str[ch] = trains[i].time_departure[ch];
            }
            else {
                end_ch = ch + 1;
                break;
            }
        }
        
        _minutes_str[0] = trains[i].time_departure[end_ch];
        _minutes_str[1] = trains[i].time_departure[end_ch + 1];
        _time = float(std::stoi(_hours_str)) + float(std::stoi(_minutes_str)) / 60.0;

        if (_time >= down_time && _time <= up_time) {
            trains_buffer[selection_count] = trains[i];
            selection_count++;
        }
        i++;
    }
    print_train(trains_buffer, trains_buffer1, selection_count, buffer_count);
    delete[] trains_buffer;
}


// Выборка по времени в пути
void select_by_way_time(Train* trains, TrainBuffer* trains_buffer1, int count, int buffer_count, char down_way_time[7], char up_way_time[7])
{
    Train* trains_buffer = new Train[count];  // Буфер поездов для выборки
    int selection_count = 0;

    float down_time, up_time;  // Пременные времени в часах (дробные)
    int end_ch;  // Индекс конца цифр часов

    char hours_str2[3] = "  ", minutes_str2[3] = "  ", hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут

    for (int ch = 0; ch < strlen(down_way_time); ch++) {
        if (down_way_time[ch] != ':') {  // Сравнение с двоеточием
            hours_str1[ch] = down_way_time[ch];
        }
        else {  // Если равны, то записываем индекс
            end_ch = ch + 1;
            break;
        }
    }

    minutes_str1[0] = down_way_time[end_ch];  // Запись минут i-ой записи
    minutes_str1[1] = down_way_time[end_ch + 1];
    down_time = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени i-ой записи

    for (int ch = 0; ch < strlen(up_way_time); ch++) {
        if (up_way_time[ch] != ':') {
            hours_str2[ch] = up_way_time[ch];
        }
        else {
            end_ch = ch + 1;
            break;
        }
    }
    
    minutes_str2[0] = up_way_time[end_ch];
    minutes_str2[1] = up_way_time[end_ch + 1];
    up_time = float(std::stoi(hours_str2)) + float(std::stoi(minutes_str2)) / 60.0;

    int i = 0;
    while (i < count) {
        bool is_equal = true;

        double _time; 
        char _hours_str[3] = "  ", _minutes_str[3] = "  ";

        for (int ch = 0; ch < strlen(trains[i].time_way); ch++) {
            if (trains[i].time_way[ch] != ':') {
                _hours_str[ch] = trains[i].time_way[ch];
            }
            else {
                end_ch = ch + 1;
                break;
            }
        }
        
        _minutes_str[0] = trains[i].time_way[end_ch];
        _minutes_str[1] = trains[i].time_way[end_ch + 1];
        _time = float(std::stoi(_hours_str)) + float(std::stoi(_minutes_str)) / 60.0;

        if (_time >= down_time && _time <= up_time) {
            trains_buffer[selection_count] = trains[i];
            selection_count++;
        }
        i++;
    }
    print_train(trains_buffer, trains_buffer1, selection_count, buffer_count);
    delete[] trains_buffer;
}


// Выборка по количеству остановок
void select_by_stop_count(Train* trains, TrainBuffer* trains_buffer1, int count, int buffer_count, int down_stop_number, int up_stop_number)
{
    Train* trains_buffer = new Train[count];  // Буфер поездов для выборки
    int selection_count = 0;

    for (int i = 0; i < count; i++) {
        int _number = trains[i].stop_count;
        if (_number >= down_stop_number && _number <= up_stop_number) {
            trains_buffer[selection_count] = trains[i];
            selection_count++;
        }
    }
    print_train(trains_buffer, trains_buffer1, selection_count, buffer_count);
    delete[] trains_buffer;
}
