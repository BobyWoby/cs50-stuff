#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int val;
    struct node *next;
} node;



void print_list(node *head);
node *newNode(int value);
void push(node *head, int val);
int main(void)
{
    node *head = NULL;
    for(int i = 0; i < 3; i++){
        if(i == 0){
            head = malloc(sizeof(node));
            head->val = i;
            head->next = NULL;
        }
        else{
            push(head, i);
        }

    }

    print_list(head);

    while(head != NULL){
        node *tmp = head->next;
        free(head);
        head = tmp;
    }

    return 0;
}


void print_list(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
}

void push(node * head, int val) {

    node *current = head;

    while(current->next != NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    current->next = malloc(sizeof(node));
    current->next->val = val;
    current->next->next = NULL;
}
