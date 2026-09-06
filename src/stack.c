/**
 * @file stack.c
 * @brief Implementation of dynamic linked-list stack.
 * @author i7modes
 * @license MIT
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

Stack* Stack_Create(void)
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        fprintf(stderr, "Error: Out of memory in Stack_Create.\n");
        return NULL;
    }

    s->top = NULL;
    s->size = 0;
    return s;
}

void Stack_Clear(Stack *s)
{
    if (s == NULL)
    {
        return;
    }

    StackNode *current = s->top;
    while (current != NULL)
    {
        StackNode *temp = current->next;
        free(current);
        current = temp;
    }

    s->top = NULL;
    s->size = 0;
}

void Stack_Destroy(Stack **s_ptr)
{
    if (s_ptr == NULL || *s_ptr == NULL)
    {
        return;
    }

    Stack_Clear(*s_ptr);
    free(*s_ptr);
    *s_ptr = NULL;
}

/* -------------------------------------------------------------------------- */
/*                               Core Operations                              */
/* -------------------------------------------------------------------------- */

bool Stack_IsEmpty(const Stack *s)
{
    return (s == NULL || s->top == NULL);
}

size_t Stack_Size(const Stack *s)
{
    return (s != NULL) ? s->size : 0;
}

bool Stack_Push(int value, Stack *s)
{
    if (s == NULL)
    {
        return false;
    }

    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Out of memory in Stack_Push.\n");
        return false;
    }

    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
    return true;
}

bool Stack_Pop(Stack *s, int *out_value)
{
    if (Stack_IsEmpty(s))
    {
        return false;
    }

    StackNode *temp = s->top;
    if (out_value != NULL)
    {
        *out_value = temp->data;
    }

    s->top = temp->next;
    free(temp);
    s->size--;
    return true;
}

bool Stack_Peek(const Stack *s, int *out_value)
{
    if (Stack_IsEmpty(s) || out_value == NULL)
    {
        return false;
    }

    *out_value = s->top->data;
    return true;
}

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

bool Stack_IsBalanced(const char *expression)
{
    if (expression == NULL)
    {
        return true;
    }

    Stack *s = Stack_Create();
    if (s == NULL)
    {
        return false;
    }

    for (size_t i = 0; expression[i] != '\0'; i++)
    {
        char c = expression[i];

        if (c == '(' || c == '[' || c == '{')
        {
            Stack_Push((int)c, s);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            int topChar;
            if (!Stack_Pop(s, &topChar))
            {
                Stack_Destroy(&s);
                return false; /* Unmatched closing bracket */
            }

            if ((c == ')' && topChar != '(') ||
                (c == ']' && topChar != '[') ||
                (c == '}' && topChar != '{'))
            {
                Stack_Destroy(&s);
                return false; /* Mismatched bracket type */
            }
        }
    }

    bool balanced = Stack_IsEmpty(s);
    Stack_Destroy(&s);
    return balanced;
}

bool Stack_EvaluatePostfix(const char *expression, int *result)
{
    if (expression == NULL || result == NULL)
    {
        return false;
    }

    Stack *s = Stack_Create();
    if (s == NULL)
    {
        return false;
    }

    const char *p = expression;

    while (*p != '\0')
    {
        /* Skip whitespace */
        while (*p != '\0' && isspace((unsigned char)*p))
        {
            p++;
        }

        if (*p == '\0')
        {
            break;
        }

        /* Check if current token is a number (including negative number) */
        if (isdigit((unsigned char)*p) || (*p == '-' && isdigit((unsigned char)*(p + 1))))
        {
            char *endptr;
            long val = strtol(p, &endptr, 10);
            Stack_Push((int)val, s);
            p = endptr;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
        {
            int val2, val1;
            if (!Stack_Pop(s, &val2) || !Stack_Pop(s, &val1))
            {
                Stack_Destroy(&s);
                return false; /* Not enough operands */
            }

            int computed = 0;
            switch (*p)
            {
                case '+':
                    computed = val1 + val2;
                    break;
                case '-':
                    computed = val1 - val2;
                    break;
                case '*':
                    computed = val1 * val2;
                    break;
                case '/':
                    if (val2 == 0)
                    {
                        Stack_Destroy(&s);
                        return false; /* Division by zero */
                    }
                    computed = val1 / val2;
                    break;
            }

            Stack_Push(computed, s);
            p++;
        }
        else
        {
            /* Unexpected token */
            Stack_Destroy(&s);
            return false;
        }
    }

    if (Stack_Size(s) != 1)
    {
        Stack_Destroy(&s);
        return false; /* Malformed expression */
    }

    Stack_Pop(s, result);
    Stack_Destroy(&s);
    return true;
}

size_t Stack_ToArray(const Stack *s, int *buffer, size_t max_len)
{
    if (s == NULL || buffer == NULL || max_len == 0)
    {
        return 0;
    }

    size_t count = 0;
    const StackNode *current = s->top;

    while (current != NULL && count < max_len)
    {
        buffer[count++] = current->data;
        current = current->next;
    }

    return count;
}

void Stack_Print(const Stack *s)
{
    if (s == NULL)
    {
        printf("(null)\n");
        return;
    }

    if (Stack_IsEmpty(s))
    {
        printf("[Top] -> [Bottom] (empty)\n");
        return;
    }

    printf("[Top]");
    const StackNode *current = s->top;

    while (current != NULL)
    {
        printf(" -> [%d]", current->data);
        current = current->next;
    }

    printf(" -> [Bottom]\n");
}
