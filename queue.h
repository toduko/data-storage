#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
typedef int QUEUE_DATA;

int Is_Empty();

int Is_Full();

void Enqueue(QUEUE_DATA data);

void Dequeue();

QUEUE_DATA Front();

#endif
