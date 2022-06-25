#include <stdio.h>
#include <string.h>
#include "stack.h"

#define OPERATOR "+-*/"

int priority(char chr);
void create_postfix(char* input, node* root, char* output);

int main(int argc, const char * argv[]) {
    char input[50];
    fgets(input, 50, stdin);
    char output[50];
    node* root = init(0);
    create_postfix(input, root, output);
    puts(input);
    puts(output);
    return 0;
}

void create_postfix(char* input, node* root, char* output) {
    int k = 0;
    
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == 'x' || (input[i] <= '9' && input[i] >= '0')) {
            output[k] = input[i];
            k++;
        }
        if (input[i] == '(')
            root = push(root, input[i]);
        if (input[i] == ')') {
            while(root->num != '(') {
                output[k] = root->num;
                root = pop(root);
                k++;
            }
            root = pop(root);
        }
        if (strchr(OPERATOR, input[i])) {
            while (priority(input[i]) < priority(root->num)) {
                output[k] = root->num;
                root = pop(root);
                k++;
            }
            root = push(root, input[i]);
        }
    }
    while (root->num != 0) {
        output[k] = root->num;
        root = pop(root);
        k++;
    }
}

int priority(char chr) {
    int result = 0;
    switch (chr) {
        case '(':
            result = 0;
            break;
        case '+':
            result = 1;
            break;
        case '-':
            result = 1;
            break;
        case '*':
            result = 2;
            break;
        case '/':
            result = 2;
            break;
        default:
            break;
    }
    return result;
}
