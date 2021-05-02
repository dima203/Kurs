#ifndef SORT_FUNC_H
#define SORT_FUNC_H

#include "train.h"


void number_sort(Train*, int*, int);
void end_station_sort(Train*, int*, int);
void departure_time_sort(Train*, int*, int);
void way_time_sort(Train*, int*, int);
void stop_count_sort(Train*, int*, int);

void quick_sort(int*, int, int, int*);
void quick_sort(double*, int, int, int*);
void quick_sort(char[][256], int, int, int*);

#endif