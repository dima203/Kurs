#ifndef TRAIN_H
#define TRAIN_H


// Структура "Поезд"
#pragma pack(push, 1)
struct Train {
    char number[5];
    char end_station[256];
    char days[64];
    char time_departure[7];
    char time_way[7];
    int stop_count;
};

// Структура буфера для отмены действий
struct TrainBuffer {
    int count;
    Train* trains;
};
#pragma pack (pop)

#endif