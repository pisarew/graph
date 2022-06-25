#include "stack.h"
#include <stdlib.h>

node* init(char num) {
    node* head = malloc(sizeof(struct node));
    head->num = num;
    head->next = NULL;
    return head;
}
node* push(node* head, char num) {
    node* new_head = malloc(sizeof(struct node));
    new_head->num = num;
    new_head->next = head;
    return new_head;
}
node* pop(node* head) {
    node* buf = head;
    head = head->next;
    free(buf);
    return head;
}
void destroy(node* head) {
    while (head->next) {
        struct node* buf = head;
        head = head->next;
        free(buf);
    }
    free(head);
}
