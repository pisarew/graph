#include "stack.h"
#include <stdlib.h>

node* init(int num) {
    node* head = malloc(sizeof(node));
    head->num = num;
    head->next = NULL;
    return head;
}
node* push(node* head, int num) {
    if (!head)
        return NULL;
    node* new_head = malloc(sizeof(node));
    new_head->num = num;
    new_head->next = head;
    return new_head;
}
node* pop(node* head) {
    if (!head)
        return NULL;
    node* buf = head;
    head = head->next;
    free(buf);
    return head;
}
void destroy(node* head) {
    if (!head)
        return;
    while (head->next) {
        struct node* buf = head;
        head = head->next;
        free(buf);
    }
    free(head);
}
