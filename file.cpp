/*
    Файл с функциями для работы с файлами (чтение, запись)
*/

#include "file.h"
#include "config_func.h"
#include "sort_func.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <span>


// Получение записей из файла
// ======================================================================================
int get_records_from_file(char file_name[], Train* &trains, int& count)
{
    std::ifstream file(file_name, std::ios::binary);  // Создание потока чтения из файла

    if (!file) {  // Проверка на ошибки при открытии файла
        std::cout << "Файл не открыт!!!" << std::endl;
        return 1;
    }

    int train_count_in_file;
    file.read((char*)(&train_count_in_file), sizeof(train_count_in_file));

    for (int i = 0; i < train_count_in_file; i++) {  // Если файл открыт, то считываем данные
        add_memory_train(trains, count);
        file.read((char*)(&trains[count]), sizeof(Train));
        count++;
    }

    return 0;
}


// Запись данных в файл
// ======================================================================================
int put_records_in_file(char file_name[], Train* trains, int count)
{
    std::ofstream file(file_name, std::ios::binary);  // Создание потока записи в файл
    std::ofstream text_file("output_file.txt");

    if (!file) {
        std::cout << "Файл не открыт!!!" << std::endl;
        return 1;
    }

    file.write((char*)(&count), sizeof(count));  // Запись количества записей в файл

    text_file << "  Номер" << '|' << "    Конечная станция" << '|' << "      Дни следования" << '|'
    << " Отправление" << '|' << "Время в пути" << '|' << " Кол-во остановок" << '|' << "Время в пути в сутках";
    text_file << std::endl;  // Запись шапки в текстовый файл

    for (auto & train: std::span(trains, count)) {  // Цикл по количеству записей
        file.write((char*)(&train), sizeof(Train));  // Запись структуры в файл

        // Запись полей структуры в текстовый файл
        text_file << std::setw(7) << train.number << '|'; 
        text_file << std::setw(20) << train.end_station << '|';
        text_file << std::setw(20) << train.days << '|';
        text_file << std::setw(12) << train.time_departure << '|';
        text_file << std::setw(12) << train.time_way << '|';
        text_file << std::setw(17) << train.stop_count << '|';

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

        text_file << std::setw(21) << time_in_hours / 24.;
        text_file << std::endl;
    }
    
    return 0;
}


// Функция создания индексных файлов
// ======================================================================================
void create_index_file(Train* trains, int count)
{
    Train* trains_buffer = new Train[count];
    int* index = new int[count];
    for (int i = 0; i < count; i++) {
        trains_buffer[i] = trains[i];
    }
    number_sort(trains_buffer, index, count);
    std::ofstream file("index_file/number_sort.txt", std::ios::binary);

    file.write((char*)(&count), sizeof(int));
    for (int i = 0; i < count; i++) {
        file.write((char*)(&index[i]), sizeof(int));
    }
    file.close();

    for (int i = 0; i < count; i++) {
        trains_buffer[i] = trains[i];
    }
    end_station_sort(trains_buffer, index, count);
    file.open("index_file/end_station_sort.txt", std::ios::binary);

    file.write((char*)(&count), sizeof(int));
    for (int i = 0; i < count; i++) {
        file.write((char*)(&index[i]), sizeof(int));
    }
    file.close();

    for (int i = 0; i < count; i++) {
        trains_buffer[i] = trains[i];
    }
    departure_time_sort(trains_buffer, index, count);
    file.open("index_file/departure_time_sort.txt", std::ios::binary);

    file.write((char*)(&count), sizeof(int));
    for (int i = 0; i < count; i++) {
        file.write((char*)(&index[i]), sizeof(int));
    }
    file.close();

    for (int i = 0; i < count; i++) {
        trains_buffer[i] = trains[i];
    }
    way_time_sort(trains_buffer, index, count);
    file.open("index_file/way_time_sort.txt", std::ios::binary);

    file.write((char*)(&count), sizeof(int));
    for (int i = 0; i < count; i++) {
        file.write((char*)(&index[i]), sizeof(int));
    }
    file.close();

    for (int i = 0; i < count; i++) {
        trains_buffer[i] = trains[i];
    }
    stop_count_sort(trains_buffer, index, count);
    file.open("index_file/stop_count_sort.txt", std::ios::binary);

    file.write((char*)(&count), sizeof(int));
    for (int i = 0; i < count; i++) {
        file.write((char*)(&index[i]), sizeof(int));
    }
    file.close();
}
