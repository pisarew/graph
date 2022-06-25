#include <stdio.h>
#include <string.h>
#include "stack.h"

#define OPERATOR "+-*/"

int priority(char chr);
void create_postfix(char* input, char* output);
int execute(int a, int b, char op);
int calculate(char* postfix);

int main(int argc, const char * argv[]) {
    char input[50];
    fgets(input, 50, stdin);
    char output[50];
    create_postfix(input, output);
    puts(input);
    puts(output);
    printf("res = %d", calculate(output));
    return 0;
}

void create_postfix(char* input, char* output) {
    int k = 0;
    node* root = init(0);
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
    destroy(root);
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
int execute(int a, int b, char op) {
    double result = 0;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        default:
            break;
    }
    return result;
}
int calculate(char* postfix) {
    node* root = init(0);
    for (int i = 0; i < strlen(postfix); i++) {
        if (postfix[i] <= '9' && postfix[i] >= '0') {
            root = push(root, postfix[i] - 48);
            continue;
        }
        if (strchr(OPERATOR, postfix[i])) {
            int a = root->num;
            root = pop(root);
            int b = root->num;
            root = pop(root);
            root = push(root, execute(b, a, postfix[i]));
        }
    }
    int result = root->num;
    destroy(root);
    return result;
}
