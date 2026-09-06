/**
 * @file stack.h
 * @brief Dynamic Linked-List-Based Stack Implementation in C.
 * @author i7modes
 * @license MIT
 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Individual node within the linked-list stack.
 */
typedef struct StackNode {
    int data;                   /**< Data payload */
    struct StackNode *next;     /**< Pointer to the next node down */
} StackNode;

/**
 * @brief Stack handle tracking the top pointer and element count.
 */
typedef struct Stack {
    StackNode *top;             /**< Pointer to the top element */
    size_t size;                /**< Element count for O(1) size queries */
} Stack;

/* -------------------------------------------------------------------------- */
/*                         Lifecycle & Memory Management                      */
/* -------------------------------------------------------------------------- */

/**
 * @brief Allocates and initializes an empty stack.
 * @return Pointer to new Stack, or NULL if allocation failed.
 */
Stack* Stack_Create(void);

/**
 * @brief Removes and frees all elements in the stack.
 * @param s Pointer to the stack.
 */
void Stack_Clear(Stack *s);

/**
 * @brief Frees all elements and the stack container, setting *s_ptr to NULL.
 * @param s_ptr Pointer to the Stack pointer variable.
 */
void Stack_Destroy(Stack **s_ptr);

/* -------------------------------------------------------------------------- */
/*                               Core Operations                              */
/* -------------------------------------------------------------------------- */

/**
 * @brief Checks if the stack contains any elements.
 * @param s Pointer to the stack.
 * @return true if empty or s is NULL, false otherwise.
 */
bool Stack_IsEmpty(const Stack *s);

/**
 * @brief Returns the number of elements in the stack in O(1) time.
 * @param s Pointer to the stack.
 * @return Number of elements.
 */
size_t Stack_Size(const Stack *s);

/**
 * @brief Pushes a new value onto the top of the stack in O(1) time.
 * @param value The value to push.
 * @param s Pointer to the stack.
 * @return true on success, false on memory allocation failure.
 */
bool Stack_Push(int value, Stack *s);

/**
 * @brief Pops and removes the top value from the stack in O(1) time.
 * @param s Pointer to the stack.
 * @param out_value Optional pointer to receive the popped value (can be NULL).
 * @return true on success, false if stack is empty or s is NULL.
 */
bool Stack_Pop(Stack *s, int *out_value);

/**
 * @brief Peeks at the top value of the stack without removing it in O(1) time.
 * @param s Pointer to the stack.
 * @param out_value Pointer to receive the top value (must not be NULL).
 * @return true if top exists, false if stack is empty or s is NULL.
 */
bool Stack_Peek(const Stack *s, int *out_value);

/* -------------------------------------------------------------------------- */
/*                           Algorithms & Utilities                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Evaluates whether bracket pairs '()', '[]', '{}' in an expression are balanced.
 * @param expression Null-terminated string containing brackets.
 * @return true if all brackets are properly paired and nested, false otherwise.
 */
bool Stack_IsBalanced(const char *expression);

/**
 * @brief Evaluates a postfix (Reverse Polish Notation) arithmetic expression.
 * Supports '+', '-', '*', '/', and multi-digit integers separated by spaces.
 * Example: "5 1 2 + 4 * + 3 -" evaluates to 14.
 * @param expression Null-terminated string.
 * @param result Pointer to receive the evaluated integer.
 * @return true if valid expression, false on error (division by zero, invalid format).
 */
bool Stack_EvaluatePostfix(const char *expression, int *result);

/**
 * @brief Copies all elements from top to bottom into a provided buffer.
 * @return Number of elements copied.
 */
size_t Stack_ToArray(const Stack *s, int *buffer, size_t max_len);

/**
 * @brief Prints the stack vertically / horizontally in ASCII:
 *        [Top] -> [30] -> [20] -> [10] -> [Bottom]
 * @param s Pointer to the stack.
 */
void Stack_Print(const Stack *s);

/* -------------------------------------------------------------------------- */
/*                       Legacy API Compatibility Layer                       */
/* -------------------------------------------------------------------------- */

typedef struct Node {
    int Element;
    struct Node *Next;
} *PtrToNode;

typedef PtrToNode LegacyStack;

static inline LegacyStack CreateStack(void) {
    LegacyStack S = (LegacyStack)malloc(sizeof(struct Node));
    if (S == NULL) return NULL;
    S->Next = NULL;
    S->Element = 0;
    return S;
}

static inline int isEmpty(LegacyStack S) {
    return (S == NULL || S->Next == NULL) ? 1 : 0;
}

static inline void Pop(LegacyStack S) {
    if (isEmpty(S)) {
        printf("Empty stack!\n");
        return;
    }
    PtrToNode firstCell = S->Next;
    S->Next = firstCell->Next;
    free(firstCell);
}

static inline void MakeEmpty(LegacyStack S) {
    if (S == NULL) return;
    while (!isEmpty(S)) {
        Pop(S);
    }
}

static inline int Top(LegacyStack S) {
    if (!isEmpty(S)) {
        return S->Next->Element;
    }
    printf("Empty stack!\n");
    return 0;
}

static inline void Push(int X, LegacyStack S) {
    if (S == NULL) return;
    PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
    if (temp == NULL) return;
    temp->Element = X;
    temp->Next = S->Next;
    S->Next = temp;
}

static inline void DisposeStack(LegacyStack S) {
    if (S == NULL) return;
    MakeEmpty(S);
    free(S);
}

#ifdef __cplusplus
}
#endif

#endif /* STACK_H */
