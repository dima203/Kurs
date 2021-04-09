#ifndef DELETE_FUNC_H
#define DELETE_FUNC_H

#include "train.h"


void delete_train_by_number(Train*, int&, char[5]);
void delete_train_by_end_station(Train*, int&, char[256]);

#endif