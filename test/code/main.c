#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ELEMENTS_TYPE int

/**
 * Estructura que representa la doble cola
 * @param size número de elementos en la cola
 * @param maxSize tamaño máximo de la cola
 * @param lastSize número de elementos en la cola desde el final
 * @param firstSize número de elementos en la cola desde el principio
 */
typedef struct DoubleQueue {
  ELEMENTS_TYPE *array;
  int maxSize;
  int size;
  int lastSize;
  int firstSize;
} DoubleQueue;

/**
 * Inicializa la doble cola con el tamaño dado
 */
void DoubleQueueInit(DoubleQueue *queue, int size) {
  queue->array = calloc(sizeof(ELEMENTS_TYPE), size);
  queue->maxSize = size;
  queue->size = 0;
  queue->firstSize = 0;
  queue->lastSize = 0;
}

/**
 * Función para imprimir información de depuración de la doble cola
 */
void printDQDebug(DoubleQueue *queue) {

  printf("\nQueue Head(%d): ", queue->firstSize);
  for (int i = 0; i < queue->firstSize; i++) {
    printf("%d ", queue->array[i]);
  }

  printf("\nQueue rear(%d): ", queue->lastSize);
  for (int i = 0; i < queue->lastSize; i++) {
    printf("%d ", queue->array[queue->maxSize - i]);
  }
}

/**
 * Agrega un elemento a la doble cola en el índice dado (0 para agregar
 * al principio, 1 para agregar al final)
 */
void DoubleQueueEnqueue(DoubleQueue *queue,
                        int queueIndex,
                        ELEMENTS_TYPE element) {
  /* Solo permitir el 1 o el 0 como índice */
  assert(queueIndex == 1 || queueIndex == 0);

  /* Verificar que haya espacio disponible en la cola */
  assert(queue->size < queue->maxSize);

  if (queueIndex) {
    (queue->array)[queue->maxSize - queue->lastSize] = element;
    (queue->lastSize)++;
  } else {
    (queue->array)[queue->firstSize] = element;
    (queue->firstSize)++;
  }

  (queue->size)++;
}

/**
 * Libera la memoria del arreglo
 */
void DoubleQueueFree(DoubleQueue *queue) {
  free(queue->array);
  queue->array = NULL;
  queue->firstSize = 0;
  queue->lastSize = 0;
  queue->size = 0;
  queue->maxSize = 0;
}

/**
 * Extrae el primer elemento de la doble cola en el índice dado (0 para
 * extraer del principio, 1 para extraer del final)
 */
ELEMENTS_TYPE DoubleQueueDequeue(DoubleQueue *queue, int queueIndex) {
  /* Solo permitir el 1 o el 0 como índice */
  assert(queueIndex == 1 || queueIndex == 0);

  ELEMENTS_TYPE element;
  ELEMENTS_TYPE *queueArray = queue->array;

  if (queueIndex) {
    assert(queue->lastSize > 0);
    element = queueArray[queue->maxSize];

    /* Reordenar la cola después de extraer el elemento */

    for (int i = 0; i < queue->lastSize; i++) {
      queueArray[queue->maxSize - i] = queueArray[queue->maxSize - i - 1];
    }

    (queue->lastSize)--;

  } else {
    assert(queue->firstSize > 0);
    element = queueArray[0];

    /* Reordenar la cola después de extraer el elemento */
    for (int i = 1; i < queue->firstSize; i++) {
      queueArray[i - 1] = queueArray[i];
    }

    (queue->firstSize)--;
  }

  (queue->size)--;
  return element;
}

ELEMENTS_TYPE DoubleQueueFront(DoubleQueue *queue, int queueIndex) {
  /* Solo permitir el 1 o el 0 como índice */
  assert(queueIndex == 1 || queueIndex == 0);

  ELEMENTS_TYPE element;
  ELEMENTS_TYPE *queueArray = queue->array;

  if (queueIndex) { /* last */
    assert(queue->lastSize > 0);
    element = queueArray[queue->maxSize];

  } else { /* first */
    assert(queue->firstSize > 0);
    element = queueArray[0];
  }

  return element;
}


int main() {
  DoubleQueue dq;
  int queue;
  int array_size;
  int op;

  /* array setup ---------------------------------------------------- */
 array_setup:
  printf("\n Setup \n"
         "Tamaño del Array: ");
  scanf("%d", &array_size);
  puts(" ");

  if(array_size <= 0) {
    goto exit;
  }

  DoubleQueueInit(&dq, array_size);
  goto queue_select;

  
  /* seleccionar cola ----------------------------------------------- */
 queue_select:

  printf("\n\n Select queue \n");
  printDQDebug(&dq);
  
  printf("\n"
         "1) first         \n"
         "2) last         \n"
         "0) Exit         \n");
  printf("> ");
  scanf("%d", &queue);

  if(queue) {
    queue--;
    goto operation_select;
  }
  
  goto exit;
 

  /* Menu ----------------------------------------------------------- */
 operation_select:
  printf("\n Operation \n"
         "1) Enqueue   \n"
         "2) Dequeue   \n"
         "0) Return    \n");

  printf("> ");
  scanf("%d", &op);

  switch (op) {
  case 1:
    printf("Enqueue value (int): ");
    int a;
    scanf("%d", &a);
    DoubleQueueEnqueue(&dq, queue, a);
    break;

  case 2:
    printf("Dequeue value: %d\n", DoubleQueueDequeue(&dq, queue));
    break;
  }

  goto queue_select;

  
  
 exit: 
  return 0;
}
