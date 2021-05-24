/*
    Файл с функциями сортировки записей по полям
*/

#include "sort_func.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <span>


// Сортировка по номеру
// ======================================================================================
void number_sort(Train* trains, int* index, int count)
{
    int _number[count];
    for (int i = 0; auto train: std::span(trains, count)) {
        index[i] = i;
        _number[i] = std::stoi(train.number);
        i++;
    }
    quick_sort(_number, 0, count - 1, index);
}


// Сортировка по названию станции
// ======================================================================================
void end_station_sort(Train* trains, int* index, int count)
{
    char _end_station[count][256];
    for (int i = 0; auto train: std::span(trains, count)) {
        char temp[256];
        index[i] = i;
        strcpy(temp, train.end_station);
        for (int j = 0; j < strlen(temp); j++) {
            temp[j] = tolower(temp[j]);
        }
        strcpy(_end_station[i], temp);
        i++;
    }
    quick_sort(_end_station, 0, count - 1, index);
}


// Сортировка по времени отправления
// ======================================================================================
void departure_time_sort(Train* trains, int* index, int count)
{
    double _departure_time[count];
    for (int i = 0; auto train: std::span(trains, count)) {
        int end_ch;
        index[i] = i;
        char hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут

        for (int ch = 0; ch < strlen(trains[i].time_departure); ch++) {  // Запись часов i-ой записи
            if (train.time_departure[ch] != ':') {  // Сравнение с двоеточием
                hours_str1[ch] = train.time_departure[ch];
            }
            else {  // Если равны, то записываем индекс
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str1[0] = train.time_departure[end_ch];  // Запись минут i-ой записи
        minutes_str1[1] = train.time_departure[end_ch + 1];
        _departure_time[i] = double(std::stoi(hours_str1)) + double(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени i-ой записи
        i++;
    }

    quick_sort(_departure_time, 0, count - 1, index);
}


// Сортировка по времени в пути
// Отличие только в поле, по которому сортируем
// ======================================================================================
void way_time_sort(Train* trains, int* index, int count)
{
    double _way_time[count];
    for (int i = 0; auto train: std::span(trains, count)) {
        int end_ch;
        index[i] = i;
        char hours_str1[3] = "  ", minutes_str1[3] = "  ";  // Промежуточные переменные для часов и минут

        for (int ch = 0; ch < strlen(train.time_way); ch++) {  // Запись часов i-ой записи
            if (train.time_way[ch] != ':') {  // Сравнение с двоеточием
                hours_str1[ch] = train.time_way[ch];
            }
            else {  // Если равны, то записываем индекс
                end_ch = ch + 1;
                break;
            }
        }

        minutes_str1[0] = train.time_way[end_ch];  // Запись минут i-ой записи
        minutes_str1[1] = train.time_way[end_ch + 1];
        _way_time[i] = double(std::stoi(hours_str1)) + double(std::stoi(minutes_str1)) / 60.0;  // Подсчёт времени i-ой записи
        i++;
    }
    quick_sort(_way_time, 0, count - 1, index);
}


// Сортировка по количеству остановок
// ======================================================================================
void stop_count_sort(Train* trains, int* index, int count) 
{
    int _stop_count[count];
    for (int i = 0; auto train: std::span(trains, count)) {
        index[i] = i;
        _stop_count[i] = train.stop_count;
        i++;
    }

    quick_sort(_stop_count, 0, count - 1, index);
}


// Функции для быстрой сортировки
// ======================================================================================
void quick_sort(int* A, int from, int to, int* index) 
{
    int x, i, j, temp;

    if (from >= to) return; // Условие окончания рекурсии
    i = from; // Рассматриваем элементы с A[from] до A[to]
    j = to;
    x = A[(from + to) / 2]; // Выбираем средний элемент

    while ( i <= j ) {
        while (A[i] < x) i++; // Ищем пару для перестановки
        while (A[j] > x) j--;
            if (i <= j) {
                temp = A[i]; A[i] = A[j]; A[j] = temp; // Перестановка
                temp = index[i]; index[i] = index[j]; index[j] = temp;
                i++; // Двигаемся дальше
                j--;
            }
    }
    quick_sort(A, from, j, index); // Сортируем левую часть
    quick_sort(A, i, to, index); // Сортируем правую часть
}


// ======================================================================================
void quick_sort(double* A, int from, int to, int* index) 
{
    int i, j, index_temp;
    double temp, x;

    if (from >= to) return; // Условие окончания рекурсии
    i = from; // Рассматриваем элементы с A[from] до A[to]
    j = to;
    x = A[(from + to) / 2]; // Выбираем средний элемент

    while ( i <= j ) {
        while (A[i] < x) i++; // Ищем пару для перестановки
        while (A[j] > x) j--;
            if (i <= j) {
                temp = A[i]; A[i] = A[j]; A[j] = temp; // Перестановка
                index_temp = index[i]; index[i] = index[j]; index[j] = index_temp;
                i++; // Двигаемся дальше
                j--;
            }
    }
    quick_sort(A, from, j, index); // Сортируем левую часть
    quick_sort(A, i, to, index); // Сортируем правую часть
}


// ======================================================================================
void quick_sort(char A[][256], int from, int to, int* index) 
{
    int i, j, index_temp;
    char temp[256], x[256];

    if (from >= to) return; // Условие окончания рекурсии
    i = from; // Рассматриваем элементы с A[from] до A[to]
    j = to;

    strcpy(x, A[(from + to) / 2]); // Выбираем средний элемент
    while ( i <= j ) {
        while (strcmp(A[i], x) < 0) i++; // Ищем пару для перестановки
        while (strcmp(A[j], x) > 0) j--;
            if (i <= j) {
                strcpy(temp, A[i]); strcpy(A[i], A[j]); strcpy(A[j], temp); // Перестановка
                index_temp = index[i]; index[i] = index[j]; index[j] = index_temp;
                i++; // Двигаемся дальше
                j--;
            }
    }
    quick_sort(A, from, j, index); // Сортируем левую часть
    quick_sort(A, i, to, index); // Сортируем правую часть
}
