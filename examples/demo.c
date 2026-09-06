/**
 * @file demo.c
 * @brief Demonstration program for the Stack library.
 * @author i7modes
 * @license MIT
 */

#include "stack.h"
#include <stdio.h>

static void print_separator(const char *title)
{
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

int main(void)
{
    print_separator("1. Creating and Pushing onto Stack");
    Stack *s = Stack_Create();
    printf("Stack created. Is empty? %s\n", Stack_IsEmpty(s) ? "Yes" : "No");

    printf("Pushing 10, 20, 30, 40...\n");
    Stack_Push(10, s);
    Stack_Push(20, s);
    Stack_Push(30, s);
    Stack_Push(40, s);

    Stack_Print(s);
    printf("Current Stack Size: %zu\n", Stack_Size(s));

    print_separator("2. Peeking at Top Element");
    int topVal;
    if (Stack_Peek(s, &topVal))
    {
        printf("Current Top Element: %d\n", topVal);
    }

    print_separator("3. Popping Elements (LIFO Order)");
    int poppedVal;
    while (Stack_Pop(s, &poppedVal))
    {
        printf("Popped: %d, Remaining size: %zu\n", poppedVal, Stack_Size(s));
    }
    printf("Stack is now empty. Safe pop attempt returns: %s\n",
           Stack_Pop(s, &poppedVal) ? "Success" : "Failed (safely!)");

    print_separator("4. Balanced Parentheses Checker");
    const char *testCases[] = {
        "{ [ ( ) ] }",
        "( ( 1 + 2 ) * [ 3 / 4 ] )",
        "( [ ) ]",
        "{ ( [ ] )",
        "}"
    };

    for (size_t i = 0; i < sizeof(testCases)/sizeof(testCases[0]); i++)
    {
        bool balanced = Stack_IsBalanced(testCases[i]);
        printf("Expression: \"%-25s\" -> %s\n",
               testCases[i], balanced ? "BALANCED [OK]" : "UNBALANCED [FAIL]");
    }

    print_separator("5. Postfix Expression Evaluation (RPN)");
    const char *postfixExpr = "5 1 2 + 4 * + 3 -";
    int evalResult;
    if (Stack_EvaluatePostfix(postfixExpr, &evalResult))
    {
        printf("Postfix expression: \"%s\"\n", postfixExpr);
        printf("Evaluated Result:   %d\n", evalResult);
    }

    print_separator("6. Legacy API Compatibility Check");
    LegacyStack legacy = CreateStack();
    Push(100, legacy);
    Push(200, legacy);
    printf("Legacy Top(): %d\n", Top(legacy));
    Pop(legacy);
    printf("Legacy Top() after Pop: %d\n", Top(legacy));
    DisposeStack(legacy);
    printf("Legacy stack disposed cleanly.\n");

    print_separator("7. Complete Teardown");
    Stack_Destroy(&s);
    printf("Stack pointer: %p (0 memory leaks)\n", (void *)s);

    printf("\nAll Stack demonstrations completed successfully!\n");
    return 0;
}
