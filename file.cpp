/*
    Файл с функциями для работы с файлами (чтение, запись)
*/

#include "file.h"
#include <fstream>
#include <iostream>
#include <cstring>


// Получение записей из файла
int get_records_from_file(char file_name[], Train* trains, int& count)
{
    std::ifstream file(file_name);  // Создание потока чтения из файла

    if (!file) {  // Проверка на ошибки при открытии файла
        std::cout << "Файл не открыт!!!" << std::endl;
        return 1;
    }

    while (file) {  // Если файл открыт, то считываем данные
		char str_buffer[512];  // Буффер строки записи
		file.getline(str_buffer, 512);  // Получение записи из файла
        if (strlen(str_buffer) == 0) {  // Проверка по длинне строки
            break;
        }

        int row_number = 0;  // Номер поля
        int char_id = 0;  // Номер символа в поле структуры
        char stop_count[8];  // Строка количества остановок

		for (int ch = 0; ch < strlen(str_buffer); ch++) {  // Цикл по символам строки
            if (str_buffer[ch] == '\t') {  // Сравнение с табуляцией
                row_number++; 
                char_id = 0;
                continue;
            }

            if (str_buffer[ch] == '\n') {  // Если символ перевода строки
                break;
            }

            switch (row_number) {  // Действие, зависящее от номера поля
                case 0:  // Номер поезда
                    trains[count].number[char_id] = str_buffer[ch];
                    char_id++;
                    break;
                case 1:  // Конечная станция
                    trains[count].end_station[char_id] = str_buffer[ch];
                    char_id++;
                    break;
                case 2:  // Дни следования
                    trains[count].days[char_id] = str_buffer[ch];
                    char_id++;
                    break;
                case 3:  // Время отправления
                    trains[count].time_departure[char_id] = str_buffer[ch];
                    char_id++;
                    break;
                case 4:  // Время в пути
                    trains[count].time_way[char_id] = str_buffer[ch];
                    char_id++;
                    break;
                case 5:  // Количество остановок
                    stop_count[char_id] = str_buffer[ch];
                    char_id++;
                    break;
            }
        }

        trains[count].stop_count = std::stoi(stop_count);  // Перевод строки в число
        count++;  // Инкрементирование количества поездов 
    }

    return 0;
}


// Запись данных в файл
int put_records_in_file(char file_name[], Train* trains, int count)
{
    std::ofstream file(file_name);  // Создание потока записи в файл

    if (!file) {
        std::cout << "Файл не открыт!!!" << std::endl;
        return 1;
    }

    for (int i = 0; i < count; i++) {  // Цикл по количеству записей
        file << trains[i].number << '\t' << trains[i].end_station << '\t' << trains[i].days
        << '\t' << trains[i].time_departure << '\t' << trains[i].time_way << '\t' << trains[i].stop_count << std::endl;
    }
    
    return 0;
}