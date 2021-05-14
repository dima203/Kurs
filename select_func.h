#ifndef SELECT_FUNC_H
#define SELECT_FUNC_H

#include "train.h"


void select_by_number(Train*, TrainBuffer*, int, int, int, int);
void select_by_end_station(Train*, TrainBuffer*, int, int, char[256]);
void select_by_departure_time(Train*, TrainBuffer*, int, int, char[7], char[7]);
void select_by_way_time(Train*, TrainBuffer*, int, int, char[7], char[7]);
void select_by_stop_count(Train*, TrainBuffer*, int, int, int, int);

#endif