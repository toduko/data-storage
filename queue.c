#include "queue.h"

#define QUEUE_SIZE 17

QUEUE_DATA queue[QUEUE_SIZE];

uint32_t front = -1;
uint32_t rear = -1;

int Is_Empty()
{
  return (front == -1 && rear == -1);
}

int Is_Full()
{
  return (rear + 1) % QUEUE_SIZE == front ? 1 : 0;
}

void Enqueue(QUEUE_DATA data)
{
  if (!Is_Full())
  {
    if (Is_Empty())
    {
      front = 0;
      rear = 0;
    }
    else
    {
      rear = (rear + 1) % QUEUE_SIZE;
    }
    queue[rear] = data;
  }
}

void Dequeue()
{
  if (!Is_Empty())
  {
    if (front == rear)
    {
      rear = -1;
      front = -1;
    }
    else
    {
      front = (front + 1) % QUEUE_SIZE;
    }
  }
}

QUEUE_DATA Front()
{
  QUEUE_DATA result;

  if (front != -1)
  {
    result = queue[front];
  }

  return result;
}
