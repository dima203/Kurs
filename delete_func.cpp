/*
    Файл с функциями для удаления записей
*/

#include "delete_func.h"
#include "train_func.h"
#include <iostream>
#include <cstring>


// 
void delete_train_by_number(Train* &trains, int& count, char number[5]) 
{
    int i = 0;
    while (i < count) {
        if (strcmp(trains[i].number, number) == 0) {
            if (i != count - 1) {
                for (int j = i; j < count - 1; j++) {
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
}


// 
void delete_train_by_end_station(Train* &trains, int& count, char end_station[256])
{
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
            for (int j = i; j < count - 1; j++) {
                trains[j] = trains[j + 1];
            }
            i--;
            sub_memory_train(trains, count);
            count--;
        }
        i++;
    }
}