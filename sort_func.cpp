/*
    Файл с функциями сортировки записей по полям
*/

#include "sort_func.h"
#include <cstring>
#include <iomanip>


// Сортировка по номеру
void number_sort(Train* trains, int count, bool reverse)
{
    if (reverse) {  // Проверка по флагу наравления сортировки
        for (int i = 0; i < count - 1; i++) {  // Цикл по записям
            int max = std::stoi(trains[i].number);  // Максимальный номер приравнивается номеру i-й записи
            int max_index = i;  // Индекс поезда с максимальным номером
            for (int j = i; j < count; j++) {  // Цикл по записям (от i до конца)
                if (max < std::stoi(trains[j].number)) {  // Сравнение максимального и текущего номера
                    max = std::stoi(trains[j].number);
                    max_index = j;
                }
            }
            // Обмен поездов (i-го с максимальным)
            Train temp = trains[i];
            trains[i] = trains[max_index];
            trains[max_index] = temp;
        }
    }
    else {  // Тоже самое, но с минимальным номером
        for (int i = 0; i < count - 1; i++) {
            int min = std::stoi(trains[i].number);
            int min_index = i;
            for (int j = i; j < count; j++) {
                if (min > std::stoi(trains[j].number)) {
                    min = std::stoi(trains[j].number);
                    min_index = j;
                }
            }
            Train temp = trains[i];
            trains[i] = trains[min_index];
            trains[min_index] = temp;
        }
    }
}


// Сортировка по названию станции
void end_station_sort(Train* trains, int count, bool reverse)
{
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

            if (reverse) {  // проверк флага направления
                if(strcmp(temp_str1, temp_str2) < 0) {  // Сравнение строк 
                    Train temp = trains[i];  // Обмен записей
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
            else {  // То же самое, но в обратном порядке
                if(strcmp(temp_str1, temp_str2) > 0) {
                    Train temp = trains[i];
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
        } 
    }
}


// Сортировка по времени отправления
void departure_time_sort(Train* trains, int count, bool reverse)
{
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

            // ТО же самое для j-ой записи
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
            
            if (reverse) {  // Проверка флага направления 
                if (time1 < time2) {
                    Train temp = trains[i];  // Обмен записей
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
            else {  // То же самое, но в обратном порядке
                if (time1 > time2) {
                    Train temp = trains[i];
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
        }
    }
}


// Сортировка по времени в пути
// ОТличие только в поле, по которому сортируем
void way_time_sort(Train* trains, int count, bool reverse)
{
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
            
            if (reverse) {
                if (time1 < time2) {
                    Train temp = trains[i];
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
            else {
                if (time1 > time2) {
                    Train temp = trains[i];
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
        }
    }
}


// Сортировка по количеству остановок
void stop_count_sort(Train* trains, int count, bool reverse) 
{
    for (int i = 0; i < count - 1; i++) {  // Цикл по записям
        for (int j = i + 1; j < count; j++) {  // Цикл по записям (от i-ой до конца)
            if (reverse) {  // проверка флага направления
                if(trains[i].stop_count < trains[j].stop_count) {
                    Train temp = trains[i];  // Обмен записей
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
            else {  // То же самое, но в обратном порядке
                if(trains[i].stop_count > trains[j].stop_count) {
                    Train temp = trains[i];
                    trains[i] = trains[j];
                    trains[j] = temp;
                }
            }
        } 
    }
}