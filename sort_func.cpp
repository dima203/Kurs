/*
    Файл с функциями сортировки записей по полям
*/

#include "sort_func.h"
#include <cstring>
#include <iomanip>


// Сортировка по номеру
void number_sort(Train* trains, int* index, int count)
{
    int _number[count];
    for (int i = 0; i < count; i++) {
        index[i] = i;
        _number[i] = std::stoi(trains[i].number);
    }
    for (int i = 0; i < count - 1; i++) {
        int min = _number[i];
        int min_index = i;
        for (int j = i; j < count; j++) {
            if (min > _number[j]) {
                min = _number[j];
                min_index = j;
            }
        }
        int temp = _number[i];
        _number[i] = _number[min_index];
        _number[min_index] = temp;
        temp = index[i];
        index[i] = index[min_index];
        index[min_index] = temp;
    }
}


// Сортировка по названию станции
void end_station_sort(Train* trains, int* index, int count)
{
    for (int i = 0; i < count; i++) {
        index[i] = i;
    }
    for (int i = 0; i < count - 1; i++) {  // Цикл по записям
        for (int j = i + 1; j < count; j++) {  // Цикл по записям (от i-ой до конца)
            char temp_str1[256];  // Промежуточные строки для сравнения
            char temp_str2[256];
            
            for (int ch = 0; ch < strlen(trains[i].end_station); ch++) {  // Запись i-ой j-ой строк в промежуточные с приведением символов в нижний регистр
                temp_str1[ch] = tolower(trains[i].end_station[ch]);
            }
            for (int ch = 0; ch < strlen(trains[j].end_station); ch++) {
                temp_str2[ch] = tolower(trains[j].end_station[ch]);
            }

            if(strcmp(temp_str1, temp_str2) > 0) {
                Train temp = trains[i];
                trains[i] = trains[j];
                trains[j] = temp;
                int index_temp = index[i];
                index[i] = index[j];
                index[j] = index_temp;
            }
        } 
    }
}


// Сортировка по времени отправления
void departure_time_sort(Train* trains, int* index, int count)
{
    for (int i = 0; i < count; i++) {
        index[i] = i;
    }
    for (int i = 0; i < count - 1; i++) {  // Цикл по записям
        float time1, time2;  // Пременные времени в часах (дробные)
        int end_ch;  // Индекс конца цифр часов

        for (int j = i + 1; j < count; j++) {  // Цикл по записям (от i-ой до конца)
            char hours_str2[3] = "  ", minutes_str2[3] = "  ", hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут

            for (int ch = 0; ch < strlen(trains[i].time_departure); ch++) {  // Запись часов i-ой записи
                if (trains[i].time_departure[ch] != ':') {  // Сравнение с двоеточием
                    hours_str1[ch] = trains[i].time_departure[ch];
                }
                else {  // Если равны, то записываем индекс
                    end_ch = ch + 1;
                    break;
                }
            }

            minutes_str1[0] = trains[i].time_departure[end_ch];  // Запись минут i-ой записи
            minutes_str1[1] = trains[i].time_departure[end_ch + 1];
            time1 = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени i-ой записи

            // То же самое для j-ой записи
            for (int ch = 0; ch < strlen(trains[j].time_departure); ch++) {
                if (trains[j].time_departure[ch] != ':') {
                    hours_str2[ch] = trains[j].time_departure[ch];
                }
                else {
                    end_ch = ch + 1;
                    break;
                }
            }
            
            minutes_str2[0] = trains[j].time_departure[end_ch];
            minutes_str2[1] = trains[j].time_departure[end_ch + 1];
            time2 = float(std::stoi(hours_str2)) + float(std::stoi(minutes_str2)) / 60.0;
        
            if (time1 > time2) {
                Train temp = trains[i];
                trains[i] = trains[j];
                trains[j] = temp;
                int index_temp = index[i];
                index[i] = index[j];
                index[j] = index_temp;
            }
        }
    }
}


// Сортировка по времени в пути
// Отличие только в поле, по которому сортируем
void way_time_sort(Train* trains, int* index, int count)
{
    for (int i = 0; i < count; i++) {
        index[i] = i;
    }
    for (int i = 0; i < count - 1; i++) {
        float time1, time2;
        int end_ch;

        for (int j = i + 1; j < count; j++) {
            char hours_str1[3] = "  ", hours_str2[3] = "  ", minutes_str1[3] = "  ", minutes_str2[3] = "  ";

            for (int ch = 0; ch < strlen(trains[i].time_way); ch++) {
                if (trains[i].time_way[ch] != ':') {
                    hours_str1[ch] = trains[i].time_way[ch];
                }
                else {
                    end_ch = ch + 1;
                    break;
                }
            }

            minutes_str1[0] = trains[i].time_way[end_ch];
            minutes_str1[1] = trains[i].time_way[end_ch + 1];
            time1 = float(std::stoi(hours_str1)) + float(std::stoi(minutes_str1)) / 60.0;

            for (int ch = 0; ch < strlen(trains[j].time_way); ch++) {
                if (trains[j].time_way[ch] != ':') {
                    hours_str2[ch] = trains[j].time_way[ch];
                }
                else {
                    end_ch = ch + 1;
                    break;
                }
            }
            
            minutes_str2[0] = trains[j].time_way[end_ch];
            minutes_str2[1] = trains[j].time_way[end_ch + 1];
            time2 = float(std::stoi(hours_str2)) + float(std::stoi(minutes_str2)) / 60.0;
            
            if (time1 > time2) {
                Train temp = trains[i];
                trains[i] = trains[j];
                trains[j] = temp;
                int index_temp = index[i];
                index[i] = index[j];
                index[j] = index_temp;
            }
        }
    }
}


// Сортировка по количеству остановок
void stop_count_sort(Train* trains, int* index, int count) 
{
    for (int i = 0; i < count; i++) {
        index[i] = i;
    }
    for (int i = 0; i < count - 1; i++) {  // Цикл по записям
        for (int j = i + 1; j < count; j++) {  // Цикл по записям (от i-ой до конца)
            if(trains[i].stop_count > trains[j].stop_count) {
                Train temp = trains[i];
                trains[i] = trains[j];
                trains[j] = temp;
                int index_temp = index[i];
                index[i] = index[j];
                index[j] = index_temp;
            }
        } 
    }
}
