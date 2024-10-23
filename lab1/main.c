#include <stdlib.h>
#include <stdio.h>

struct item {
    int data;
    struct item *next;
};

// Функция для вывода списка
void print_list(const struct item *lst) {
    printf("list: ");
    for (; lst; lst = lst->next)
        printf("%d ", lst->data);
    printf("\n");
}

// Функция для преобразования массива в односвязный список
struct item *array_to_list(int *arr, int size) {
    struct item *tmp;
    if (!size)
        return NULL;
    tmp = malloc(sizeof(struct item));
    tmp->data = *arr;
    tmp->next = array_to_list(arr + 1, size - 1);
    return tmp;
}

// Функция для вставки элемента перед текущим элементом
void insert_item_list(struct item **pcur, int index, int data)
{
  int counter = 1;
  /*printf("pcur = %p\n", pcur);
  printf("*pcur = %p\n", *pcur);*/
  while(*pcur) {  
    if(index == counter) {
      struct item *tmp = malloc(sizeof(struct item));
      /*printf("tmp = %p\n", tmp);*/
      tmp->data = data;
      tmp->next = *pcur;
      *pcur = tmp;
      break;
    } else {
        pcur = &(*pcur)->next;
        counter++;
    }
  }
}

// Функция для вставки элемента после текущим элементом
void insert_after_item_list(struct item **pcur, int index, int data) {
    if (!pcur || index < 1) return;

    struct item *new_item = malloc(sizeof(struct item));
    new_item->data = data;

    struct item *current = *pcur;
    for (int counter = 1; current != NULL && counter < index; counter++)
        current = current->next;

    if (current == NULL) {
        free(new_item); // Освобождаем память, если индекс выходит за пределы
        return;
    }

    new_item->next = current->next;
    current->next = new_item;
}

// Функция для освобождения памяти списка
void free_list(struct item *lst) {
    struct item *tmp;
    while (lst) {
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int size = sizeof(arr) / sizeof(*arr);
    struct item *lst = array_to_list(arr, size);

    print_list(lst); // Вывод: 1 2 3

    insert_item_list(&lst, 2, 9); // Вставка перед вторым элементом
    print_list(lst); // Вывод: 1 9 2 3

    insert_after_item_list(&lst, 3, 10); // Вставка после третьего элемента
    print_list(lst); // Вывод: 1 9 2 10 3

    // Освобождение памяти
    free_list(lst);

    return 0;
}
