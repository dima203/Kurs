/*
    Файл с функциями для работы с памятью
*/

#include "config_func.h"


// Функция выделения дополнительной ячейки памяти
// ======================================================================================
void add_memory_train(Train* &trains, int& count)
{
    Train* buffer_trains = new Train[count];  // Создание временного буфера

    for (int i = 0; i < count; i++) {  // Перепись данных в буфер
        buffer_trains[i] = trains[i];
    }

    delete[] trains;  // Удаление указателя
    trains = new Train[count + 1];  // Создание нового указателя с большим количеством элементов

    for (int i = 0; i < count; i++) {  // Перепись данных из буфера в массив
        trains[i] = buffer_trains[i];
    }
    delete[] buffer_trains;  // Удаление буфера
}


// Функция очищения ячейки памяти
// ======================================================================================
void sub_memory_train(Train* &trains, int& count)
{
    Train* buffer_trains = new Train[count - 1];  // Создание временного буфера

    for (int i = 0; i < count - 1; i++) {  // Перепись данных в буфер
        buffer_trains[i] = trains[i];
    }

    delete[] trains;  // Удаление указателя
    trains = new Train[count - 1];  // Создание нового указателя с меньшим количеством элементов

    for (int i = 0; i < count - 1; i++) {  // Перепись данных из буфера в массив
        trains[i] = buffer_trains[i];
    }
    delete[] buffer_trains;  // Удаление буфера
}


// Функция сохраниения состояния массива в буфер для отмены
// ======================================================================================
void save_trains_in_buffer(Train* trains, TrainBuffer* trains_buffer, int count, int& buffer_count)
{
    if (buffer_count == 10) {
        delete[] trains_buffer[0].trains;  // Удаление первого состояния
        for (int i = 0; i < buffer_count - 1; i++) {  // Сдвиг всех элементов назад на один
            trains_buffer[i] = trains_buffer[i + 1];
        }
        buffer_count = 9;  // Изменение количества
    }

    trains_buffer[buffer_count].count = count;  // Запись количества поездов
    trains_buffer[buffer_count].trains = new Train[count];  // Запись поездов
    for (int i = 0; i < count; i++) {  // Перепись поездов из массива в буфер для отмены
        trains_buffer[buffer_count].trains[i] = trains[i];
    }

    buffer_count++;  // Увеличение количества состояний в буфере
}
