#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "double_stack.h"

#define OPERATOR "+-*/"
#define UNARY_OPERATOR "s"

int priority(char chr);
void create_postfix(char* input, char* output);
double execute(double a, double b, char op);
double calculate(char* postfix);
void switch_x(char* postfix, double x, char* result);
void graph(char* postfix);

int main(int argc, const char * argv[]) {
    char input[50];
    fgets(input, 50, stdin);
    char output[50];
    create_postfix(input, output);
    puts(input);
    puts(output);
    graph(output);
    return 0;
}
void graph(char* postfix) {
    const double pi = 3.14;
    double dx = (pi * 4) / 79;
    double x = 0;
    double dy = 2.0 / 24;
    double y = 1;
    for (int i = 0; i < 25; i++) {
        dx = (pi * 4) / 80;
        x = 0;
        for (int j = 0; j < 85; j++) {
            char res[20];
            switch_x(postfix, x, res);
            double X = calculate(res);
//            printf("\ny %lf x %lf\n", dy, X);
            if ((X <= (y + dy)) && X >= (y - dy))
                printf("*");
            else
                printf(".");
            x += dx;
        }
        printf("\n");
        y -= dy;
    }
}
void switch_x(char* postfix, double x, char* result) {
    int k = 0;
    for (int i = 0; i < strlen(postfix); i++) {
        if (postfix[i] == 'x') {
            char num[20];
            sprintf(num, "%.5f", x);
            for (int j = 0; j < strlen(num); j++) {
                result[k] = num[j];
                k++;
            }
        } else {
            result[k] = postfix[i];
            k++;
        }
    }
    result[k] = '\0';
}
void create_postfix(char* input, char* output) {
    int k = 0;
    node* root = init(0);
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == 'x' || (input[i] <= '9' && input[i] >= '0')) {
            output[k] = input[i];
            k++;
            output[k] = ' ';
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
        if (input[i] <= 122 && input[i] >= 97) {
            if (input[i] == 's' && input[i + 1] == 'i') {
                while (priority('s') < priority(root->num)) {
                    output[k] = root->num;
                    root = pop(root);
                    k++;
                }
                root = push(root, 's');
            }
            while (input[i] <= 122 && input[i] >= 97)
                i++;
        }
    }
    while (root->num != 0) {
        output[k] = root->num;
        root = pop(root);
        k++;
    }
    output[k] = '\0';
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
        case 's':
            result = 2;
            break;
        default:
            break;
    }
    return result;
}
double execute(double a, double b, char op) {
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
        case 's':
            result = sin(a);
            break;
        default:
            break;
    }
    return result;
}
double calculate(char* postfix) {
    d_node* root = d_init(0);
    for (int i = 0; i < strlen(postfix); i++) {
        if ((postfix[i] <= '9' && postfix[i] >= '0') || postfix[i] == '.') {
            char num[20];
            int k = 0;
            while ((postfix[i] <= '9' && postfix[i] >= '0') || postfix[i] == '.') {
                num[k] = postfix[i];
                k++;
                i++;
            }
            double d_num = atof(num);
            root = d_push(root, d_num);
            continue;
        }
        if (strchr(UNARY_OPERATOR, postfix[i])) {
            double a = root->num;
            root = d_pop(root);
            root = d_push(root, execute(a, 0, postfix[i]));
        }
        if (strchr(OPERATOR, postfix[i])) {
            double a = root->num;
            root = d_pop(root);
            double b = root->num;
            root = d_pop(root);
            root = d_push(root, execute(b, a, postfix[i]));
        }
        
    }
    double result = root->num;
    d_destroy(root);
//    printf("\n%lf\n", result);
    return result;
}
