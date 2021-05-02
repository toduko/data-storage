#include <stdint.h>
#include "queue.h"
#include "utils.h"

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

DSError Enqueue(QUEUE_DATA data)
{
  DSError status = SUCCESS;

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
  else
  {
    status = QUEUE_FULL;
  }

  Log_Result(__FUNCTION__, status);
  return status;
}

DSError Dequeue()
{
  DSError status = SUCCESS;
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
  else
  {
    status = QUEUE_EMPTY;
  }

  Log_Result(__FUNCTION__, status);
  return status;
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
