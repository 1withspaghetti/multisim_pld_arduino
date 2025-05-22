#include <Arduino.h>
#include "components.h"


// put global variables here:
uint16_t bytecode_len;
uint16_t stack_len;
uint8_t *stack;

void setup() {
  // read first two bytes
  bytecode_len = read16(PLD_BYTECODE, 0);
  stack_len = read16(PLD_BYTECODE, 2);

  stack = (uint8_t *)malloc(ceil(stack_len * 8));
  if (stack == NULL) {
    Serial.println("Failed to allocate memory for stack");
    while (true);
  }
}

void loop() {
  uint8_t offset = 4;
  
  while (offset < bytecode_len) {
    uint8_t t = PLD_BYTECODE[offset++]; // Component type
    offset += execComponent(stack, t, offset);
  }
}
