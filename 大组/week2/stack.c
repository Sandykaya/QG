#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

// Define structure for linked stack node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define structure for linked stack
typedef struct {
    Node* top;
} LinkedStack;

// Create a linked stack
LinkedStack* createStack() {
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    stack->top = NULL;
    return stack;
}

// Check if the stack is empty
int isEmpty(LinkedStack* stack) {
    return stack->top == NULL;
}

// Push operation
void push(LinkedStack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop operation
int pop(LinkedStack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        exit(1);
    }
    Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Peek operation
int peek(LinkedStack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        exit(1);
    }
    return stack->top->data;
}

// Compare operator precedence
int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Evaluate expression
int evaluateExpression(char* expression) {
    LinkedStack* operands = createStack();
    LinkedStack* operators = createStack();

    int index = 0;
    while (expression[index] != '\0') {
        if (isdigit(expression[index])) {
            int operand = 0;
            while (isdigit(expression[index])) {
                operand = operand * 10 + (expression[index] - '0');
                index++;
            }
            push(operands, operand);
        } else if (expression[index] == '+' || expression[index] == '-' || expression[index] == '*' || expression[index] == '/') {
            while (!isEmpty(operators) && precedence(peek(operators)) >= precedence(expression[index])) {
                int b = pop(operands);
                int a = pop(operands);
                char op = pop(operators);
                switch (op) {
                    case '+':
                        push(operands, a + b);
                        break;
                    case '-':
                        push(operands, a - b);
                        break;
                    case '*':
                        push(operands, a * b);
                        break;
                    case '/':
                        push(operands, a / b);
                        break;
                }
            }
            push(operators, expression[index]);
            index++;
        } else if (expression[index] == '(') {
            push(operators, expression[index]);
            index++;
        } else if (expression[index] == ')') {
            while (peek(operators) != '(') {
                int b = pop(operands);
                int a = pop(operands);
                char op = pop(operators);
                switch (op) {
                    case '+':
                        push(operands, a + b);
                        break;
                    case '-':
                        push(operands, a - b);
                        break;
                    case '*':
                        push(operands, a * b);
                        break;
                    case '/':
                        push(operands, a / b);
                        break;
                }
            }
            pop(operators);  // Pop '('
            index++;
        } else {
            index++;
        }
    }

    while (!isEmpty(operators)) {
        int b = pop(operands);
        int a = pop(operands);
        char op = pop(operators);
        switch (op) {
            case '+':
                push(operands, a + b);
                break;
            case '-':
                push(operands, a - b);
                break;
            case '*':
                push(operands, a * b);
                break;
            case '/':
                push(operands, a / b);
                break;
        }
    }

    int result = pop(operands);
    free(operands);
    free(operators);
    return result;
}

int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    int result = evaluateExpression(expression);
    printf("Result: %d\n", result);
    getch();
    return 0;
}

