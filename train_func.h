#ifndef TRAIN_FUNC_H
#define TRAIN_FUNC_H

#include "train.h"


void add_memory_train(Train*&, int&);
void sub_memory_train(Train*&, int&);
void print_train(Train*, int);
void add_train(Train*&, TrainBuffer*, int&, int&);
void delete_train(Train*&, TrainBuffer*, int&, int&, int);
void sort(Train*, int, int, bool, bool);
void undo_action(Train*&, TrainBuffer*, int&, int&);

#endif