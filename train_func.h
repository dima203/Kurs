#ifndef TRAIN_FUNC_H
#define TRAIN_FUNC_H

#include "train.h"


void add_memory_train(Train*&, int&);
void sub_memory_train(Train*&, int&);
void print_train(Train*, int);
void add_train(Train*&, int&);
void delete_train(Train*, int&, int);
void sort(Train*, int, int type = 1, bool reverse = false, bool file = false);

#endif