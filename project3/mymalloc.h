//Reggie Barnett
//Project 3
//Header File

#define MALLOC(x) my_nextfit_malloc(x)
#define FREE(x) my_free(x)
 
typedef struct NODE
{
  int size;
  int used;
  struct NODE *next;
  struct NODE *previous;
} NODE;
 
void *my_nextfit_malloc(int size);
 
void my_free (void *ptr);