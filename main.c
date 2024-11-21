#include <stdio.h>
#include <stdlib.h>

typedef int timestamp;

struct subtitle_node {
    timestamp begin;
    timestamp end;
    struct subtitle_node* next;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void reduce_list(struct subtitle_node* list)
{
    if (list->next == NULL)
    {
        return;
    }
    else if (list->end >= list->next->begin)
    {
        list->end = max(list->end, list->next->end);
        list->next = list->next->next;
        reduce_linked_list(list);
    }
    else
    {
        reduce_linked_list(list->next);
    }
}

void print_list(struct subtitle_node* list)
{
    while (list != NULL)
    {
        printf("[%d, %d] -> ", list->begin, list->end);
        list = list->next;
    }
}

struct subtitle_node* random_node(int begin)
{
    struct subtitle_node* new = NULL;
    new = malloc(sizeof(struct subtitle_node));
    new->begin = begin;
    new->end = new->begin + 1 + rand() % 10;
    new->next=NULL;
    return new;
}

int main()
{
    srand(12); // Set a random seed for testing
    struct subtitle_node* head = NULL;

    int begin = 0;
    head = random_node(begin);
    
    struct subtitle_node* current = head;
    for (int i = 0; i < 100; i++)
    {
        begin += 1 + rand() % 5;
        current->next = random_node(begin);
        current = current->next;
    }
    
    print_list(head);
    printf("\n\n\n");
    reduce_list(head);
    print_list(head);

    return 0;
}
