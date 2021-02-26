#include <stdlib.h>
#include <time.h>

void *generate_random_string(char *str, int size)
{
  srand(time(NULL) * size);
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (size) {
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = 0;
    }
}