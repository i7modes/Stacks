/**
 * @file test_stack.c
 * @brief Automated unit test suite for Stack library.
 * @author i7modes
 * @license MIT
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int total_tests = 0;
static int passed_tests = 0;

#define TEST_ASSERT(expr, msg) do { \
    total_tests++; \
    if (expr) { \
        passed_tests++; \
        printf("  [PASS] %s\n", msg); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", msg, __LINE__); \
    } \
} while (0)

static void test_lifecycle_and_empty_safety(void)
{
    printf("\n--- Test: Lifecycle & Empty Safety ---\n");
    Stack *s = Stack_Create();
    TEST_ASSERT(s != NULL, "Stack_Create returns non-NULL");
    TEST_ASSERT(Stack_IsEmpty(s) == true, "New stack is empty");
    TEST_ASSERT(Stack_Size(s) == 0, "New stack size is 0");

    int val;
    TEST_ASSERT(Stack_Pop(s, &val) == false, "Pop on empty stack returns false safely");
    TEST_ASSERT(Stack_Peek(s, &val) == false, "Peek on empty stack returns false safely");

    Stack_Destroy(&s);
    TEST_ASSERT(s == NULL, "Stack_Destroy nullifies pointer");
}

static void test_push_pop_lifo_order(void)
{
    printf("\n--- Test: Push, Pop & LIFO Order ---\n");
    Stack *s = Stack_Create();

    Stack_Push(10, s);
    Stack_Push(20, s);
    Stack_Push(30, s);

    TEST_ASSERT(Stack_Size(s) == 3, "Stack size is 3 after 3 pushes");
    TEST_ASSERT(Stack_IsEmpty(s) == false, "Stack is not empty");

    int peekVal;
    TEST_ASSERT(Stack_Peek(s, &peekVal) && peekVal == 30, "Peek returns 30 (top)");
    TEST_ASSERT(Stack_Size(s) == 3, "Peek did not modify stack size");

    int buffer[3];
    size_t copied = Stack_ToArray(s, buffer, 3);
    TEST_ASSERT(copied == 3, "Copied 3 items to array");
    TEST_ASSERT(buffer[0] == 30 && buffer[1] == 20 && buffer[2] == 10,
                "Array matches top-to-bottom order (30, 20, 10)");

    int poppedVal;
    TEST_ASSERT(Stack_Pop(s, &poppedVal) && poppedVal == 30, "Popped 30");
    TEST_ASSERT(Stack_Pop(s, &poppedVal) && poppedVal == 20, "Popped 20");
    TEST_ASSERT(Stack_Pop(s, &poppedVal) && poppedVal == 10, "Popped 10");

    TEST_ASSERT(Stack_IsEmpty(s) == true, "Stack is empty after popping all elements");
    TEST_ASSERT(Stack_Size(s) == 0, "Stack size is 0");

    // Test clear and re-push
    Stack_Push(99, s);
    Stack_Push(100, s);
    Stack_Clear(s);
    TEST_ASSERT(Stack_IsEmpty(s) == true, "Stack_Clear empties stack");
    TEST_ASSERT(Stack_Size(s) == 0, "Size is 0 after Stack_Clear");

    Stack_Destroy(&s);
}

static void test_balanced_parentheses(void)
{
    printf("\n--- Test: Balanced Parentheses Algorithm ---\n");

    TEST_ASSERT(Stack_IsBalanced("") == true, "Empty string is balanced");
    TEST_ASSERT(Stack_IsBalanced("()") == true, "'()' is balanced");
    TEST_ASSERT(Stack_IsBalanced("()[]{}") == true, "'()[]{}' is balanced");
    TEST_ASSERT(Stack_IsBalanced("{[()]}") == true, "'{[()]}' is balanced");
    TEST_ASSERT(Stack_IsBalanced("(1 + [2 * {3 + 4}])") == true, "Mixed expression with math is balanced");

    TEST_ASSERT(Stack_IsBalanced("(]") == false, "'(]' is unbalanced (type mismatch)");
    TEST_ASSERT(Stack_IsBalanced("([)]") == false, "'([)]' is unbalanced (interleaved)");
    TEST_ASSERT(Stack_IsBalanced("(") == false, "'(' is unbalanced (unclosed)");
    TEST_ASSERT(Stack_IsBalanced(")") == false, "')' is unbalanced (extra closing)");
    TEST_ASSERT(Stack_IsBalanced("(((") == false, "'(((' is unbalanced");
    TEST_ASSERT(Stack_IsBalanced(")))") == false, "')))' is unbalanced");
}

static void test_postfix_evaluation(void)
{
    printf("\n--- Test: Postfix Evaluation (RPN) ---\n");

    int res;
    TEST_ASSERT(Stack_EvaluatePostfix("2 3 +", &res) && res == 5, "'2 3 +' evaluates to 5");
    TEST_ASSERT(Stack_EvaluatePostfix("10 4 -", &res) && res == 6, "'10 4 -' evaluates to 6");
    TEST_ASSERT(Stack_EvaluatePostfix("3 7 *", &res) && res == 21, "'3 7 *' evaluates to 21");
    TEST_ASSERT(Stack_EvaluatePostfix("20 4 /", &res) && res == 5, "'20 4 /' evaluates to 5");

    // Complex: 5 1 2 + 4 * + 3 - = 5 + ((1 + 2) * 4) - 3 = 5 + 12 - 3 = 14
    TEST_ASSERT(Stack_EvaluatePostfix("5 1 2 + 4 * + 3 -", &res) && res == 14,
                "'5 1 2 + 4 * + 3 -' evaluates to 14");

    // Negative numbers
    TEST_ASSERT(Stack_EvaluatePostfix("-5 10 +", &res) && res == 5, "'-5 10 +' evaluates to 5");

    // Error handling
    TEST_ASSERT(Stack_EvaluatePostfix("10 0 /", &res) == false, "Division by zero fails safely");
    TEST_ASSERT(Stack_EvaluatePostfix("2 +", &res) == false, "Missing operand fails safely");
    TEST_ASSERT(Stack_EvaluatePostfix("+", &res) == false, "Only operator fails safely");
    TEST_ASSERT(Stack_EvaluatePostfix("2 3 4 +", &res) == false, "Unused operands fail safely");
}

int main(void)
{
    printf("========================================\n");
    printf("  Stack Automated Tests\n");
    printf("========================================\n");

    test_lifecycle_and_empty_safety();
    test_push_pop_lifo_order();
    test_balanced_parentheses();
    test_postfix_evaluation();

    printf("\n========================================\n");
    printf("  Results: %d/%d assertions passed\n", passed_tests, total_tests);
    printf("========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
