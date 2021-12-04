#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int size;
    int total_elements;
} DynamicArray;

void init_array(DynamicArray *dynamic_array, int size)
{
    dynamic_array->size = size;
    dynamic_array->total_elements = 0;
    dynamic_array->data = (int *)malloc(sizeof(int) * dynamic_array->size);
}

void addElement(int data, DynamicArray *dynamic_array)
{
    if (dynamic_array->size == dynamic_array->total_elements)
    {
        dynamic_array->size *= 2;
        dynamic_array->data = (int *)realloc(dynamic_array->data, sizeof(int) * (dynamic_array->size));
    }

    dynamic_array->data[(dynamic_array->total_elements)++] = data;
}

void resize_array(DynamicArray *dynamic_array)
{
    dynamic_array->size /= 4;
    dynamic_array->data = (int *)realloc(dynamic_array->data, sizeof(int) * (dynamic_array->size));
}

void remove_last_element(DynamicArray *dynamic_array)
{
    dynamic_array->data[(dynamic_array->total_elements)--] = 0;

    if (dynamic_array->total_elements == dynamic_array->size / 4)
    {
        resize_array(dynamic_array);
    }
}

void free_array(DynamicArray *dynamic_array)
{
    free(dynamic_array->data);

    dynamic_array->data = NULL;
    dynamic_array->size = dynamic_array->total_elements = 0;
}

int main()
{
    DynamicArray dynamic_array;
    init_array(&dynamic_array, 5);

    for (int i = 0; i < 12; i++)
    {
        addElement(i, &dynamic_array);
    }

    for (int i = 0; i < dynamic_array.total_elements; i++)
    {
        printf("%d ", dynamic_array.data[i]);
    }

    printf("\n");

    for (int i = 0; i < 10; i++)
    {
        remove_last_element(&dynamic_array);
    }

    printf("%d %d\n", dynamic_array.size, dynamic_array.total_elements);

    for (int i = 0; i < dynamic_array.total_elements; i++)
    {
        printf("%d ", dynamic_array.data[i]);
    }

    free(dynamic_array.data);

    return 0;
}
