# Dynamic Stack in C (Linked-List Implementation)

[![CI](https://github.com/i7modes/Stacks/actions/workflows/ci.yml/badge.svg)](https://github.com/i7modes/Stacks/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C Standard](https://img.shields.io/badge/C-C99-blue.svg)
![Memory Status](https://img.shields.io/badge/Valgrind-0%20Leaks-brightgreen.svg)

A clean, robust, and production-ready implementation of a **LIFO (Last-In First-Out) Stack** in C99 using a singly linked list. Features crash-safe error handling, $\mathcal{O}(1)$ dynamic operations, classic interview algorithms (bracket balancing, postfix evaluation), and zero memory leaks.

---

## Architecture: Dynamic Linked-List Stack

Unlike fixed-size array-based stacks, this implementation grows and shrinks dynamically in memory with zero capacity limits.

```text
              +--------------------+
[Top Pointer] | [data: 30 | next*] |
              +--------------------+
                        |
                        v
              +--------------------+
              | [data: 20 | next*] |
              +--------------------+
                        |
                        v
              +--------------------+
              | [data: 10 | next*] |
              +--------------------+
                        |
                        v
                      NULL
```

### Why use a Linked-List Stack?
1. **Unbounded Capacity**: Never runs out of memory until system heap exhaustion (no arbitrary `MAX_SIZE`).
2. **Guaranteed $\mathcal{O}(1)$ Ingestion**: Pushing and popping always execute in strict constant time without array reallocation overhead.
3. **Crash-Safe Semantics**: Rather than calling `exit(1)` upon an empty pop/peek, operations return boolean status codes (`bool Stack_Pop`, `bool Stack_Peek`).

---

## Features

- **Core Operations**: `Stack_Push`, `Stack_Pop`, `Stack_Peek`, `Stack_IsEmpty`, `Stack_Size`, `Stack_Clear`.
- **Classic Algorithms Included**:
  - **Balanced Brackets Validator (`Stack_IsBalanced`)**: Validates paired/nested `()`, `[]`, `{}` in expressions.
  - **Postfix / RPN Evaluator (`Stack_EvaluatePostfix`)**: Evaluates multi-digit arithmetic expressions in Reverse Polish Notation with zero-division protection.
- **Memory Safety**: `Stack_Destroy` deallocates all remaining nodes and container handles, setting pointers to `NULL`.
- **Legacy Compatibility**: Includes inline wrappers for classic academic signatures (`CreateStack`, `Push`, `Pop`, `Top`, `DisposeStack`, etc.).
- **Automated Testing & CI**: 40 unit test assertions tested on Ubuntu (Valgrind & Clang AddressSanitizer) and Windows (MinGW GCC).

---

## Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :---: | :---: | :--- |
| `Stack_Push` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Prepends node at top of stack |
| `Stack_Pop` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Removes and frees top node |
| `Stack_Peek` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Inspects top value without removal |
| `Stack_IsEmpty` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Checks if top is NULL |
| `Stack_Size` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Returns cached element count |
| `Stack_IsBalanced` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Validates matched brackets in string |
| `Stack_EvaluatePostfix` | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | Evaluates Reverse Polish Notation |
| `Stack_Destroy` | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | Deallocates all nodes and container |

---

## Project Structure

```text
Stacks/
├── include/
│   └── stack.h                  # Public API, types, and legacy aliases
├── src/
│   └── stack.c                  # Core stack & algorithms implementation
├── examples/
│   └── demo.c                   # Terminal demo with RPN & bracket validation
├── tests/
│   └── test_stack.c             # Automated unit test suite (40 assertions)
├── .github/
│   └── workflows/
│       └── ci.yml               # GitHub Actions CI matrix
├── Makefile                     # Cross-platform build script
├── LICENSE                      # MIT License
├── .gitignore                   # Ignore binaries and temporary files
└── README.md                    # Project documentation
```

---

## Quick Start

### 1. Clone the Repository
```bash
git clone https://github.com/i7modes/Stacks.git
cd Stacks
```

### 2. Build and Run Demo
```bash
make demo
make run-demo
```

### 3. Run Automated Unit Tests
```bash
make check
```

Expected output:
```text
========================================
  Stack Automated Tests
========================================

--- Test: Lifecycle & Empty Safety ---
  [PASS] Stack_Create returns non-NULL
  [PASS] New stack is empty
  [PASS] New stack size is 0
  [PASS] Pop on empty stack returns false safely
...
========================================
  Results: 40/40 assertions passed
========================================
```

### 4. Run Memory Leak Check (Linux / WSL)
```bash
make test
valgrind --leak-check=full --show-leak-kinds=all ./bin/test_runner
```

---

## Code Example

```c
#include "stack.h"
#include <stdio.h>

int main(void) {
    // 1. Create stack
    Stack *s = Stack_Create();

    // 2. Push elements
    Stack_Push(10, s);
    Stack_Push(20, s);
    Stack_Push(30, s);

    // 3. Print stack
    Stack_Print(s); // [Top] -> [30] -> [20] -> [10] -> [Bottom]

    // 4. Bracket balancing algorithm
    bool ok = Stack_IsBalanced("{ [ 1 + 2 ] * 3 }");
    printf("Is balanced? %s\n", ok ? "Yes" : "No");

    // 5. Postfix evaluation
    int result;
    Stack_EvaluatePostfix("5 1 2 + 4 * + 3 -", &result);
    printf("5 1 2 + 4 * + 3 - = %d\n", result); // Output: 14

    // 6. Clean up
    Stack_Destroy(&s); // s is now NULL, 0 memory leaks
    return 0;
}
```

---

## License

Distributed under the [MIT License](file:///c:/Users/i7mod/OneDrive/GitHub/Stacks/LICENSE). Created by [i7modes](https://github.com/i7modes).
