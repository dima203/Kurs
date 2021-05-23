#ifndef CONFIG_FUNC_H
#define CONFIG_FUNC_H

#include "train.h"


void add_memory_train(Train*&, int&);
void sub_memory_train(Train*&, int&);
void save_trains_in_buffer(Train*, TrainBuffer*, int, int&);

#endif