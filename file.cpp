/*
    Файл с функциями для работы с файлами (чтение, запись)
*/

#include "file.h"
#include "train_func.h"
#include "sort_func.h"
#include <fstream>
#include <iostream>
#include <cstring>


// Получение записей из файла
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
int put_records_in_file(char file_name[], Train* trains, int count)
{
    std::ofstream file(file_name, std::ios::binary);  // Создание потока записи в файл

    if (!file) {
        std::cout << "Файл не открыт!!!" << std::endl;
        return 1;
    }

    file.write((char*)(&count), sizeof(count));
    for (int i = 0; i < count; i++) {  // Цикл по количеству записей
        file.write((char*)(&trains[i]), sizeof(Train));
    }
    
    return 0;
}


// Функция создания индексных файлов
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
