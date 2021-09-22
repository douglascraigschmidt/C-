#include <stdio.h>

// Max size of the stack.
#define MAX_STACK 10

/**
 * This program shows a "bare-bones" C implementation of the stack
 * ADT, which clearly isn't very abstract here!
 */
int main() {
  // Define a stack of ints.
  int stack[MAX_STACK];

  // Keep track of the current "top" of the stack.
  int top = 0;

  // Keep looping until the stack is "full".
  while (top < MAX_STACK) {
      // Push items onto the stack;
      stack[top] = top;
      top++;
  }

  // Keep looping until the stack is "empty".
  while (--top >= 0)
    // Pop items off the stack and print them.
    printf("top item = %d\n", stack[top]);

  return 0;
}
