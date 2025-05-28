#include <Arduino.h>
#include "components.h"


// put global variables here:
uint16_t bytecode_len;
uint16_t stack_len;
uint16_t gpio_len;
uint8_t *stack;

void setup() {
  Serial.begin(115200);

  // read first two bytes
  bytecode_len = read16(PLD_BYTECODE, 0);
  Serial.print("Bytecode length: ");
  Serial.println(bytecode_len);

  stack_len = read16(PLD_BYTECODE, 2);
  Serial.print("Stack length: ");
  Serial.println(stack_len);

  gpio_len = read16(PLD_BYTECODE, 4);
  Serial.print("GPIO length: ");
  Serial.println(gpio_len);

  // Initialize stack memory

  stack = (uint8_t *)malloc(ceil(stack_len * 8));
  if (stack == NULL) {
    Serial.println("Failed to allocate memory for stack");
    while (true);
  }
  memset(stack, 0, ceil(stack_len * 8)); // Initialize stack memory to zero
  Serial.println("Memory allocated for stack");

  // Initialize GPIO pins

  for (uint16_t i = 0; i < gpio_len; i++) {
    pinMode(PLD_BYTECODE[6 + i*2], PLD_BYTECODE[6 + i*2 + 1]); // Set GPIO pins as input
    #ifdef DEBUG
    Serial.print("GPIO ");
    Serial.print(PLD_BYTECODE[6 + i*2]);
    Serial.print(" set as ");
    if (PLD_BYTECODE[6 + i*2 + 1] == INPUT) {
      Serial.println("INPUT");
    } else if (PLD_BYTECODE[6 + i*2 + 1] == OUTPUT) {
      Serial.println("OUTPUT");
    } else {
      Serial.print("UNKNOWN MODE (");
      Serial.print(PLD_BYTECODE[6 + i*2 + 1]);
      Serial.println(")");
    }
    #endif
  }
}

void loop() {
  uint8_t offset = 6 + gpio_len * 2; // Code starts after all definitions

  #ifdef DEBUG
  Serial.println("--- Loop Start ---");
  #endif
  
  while (offset < bytecode_len) {
    uint8_t t = PLD_BYTECODE[offset++]; // Component type

    #ifdef DEBUG
    Serial.print("component=");
    Serial.print(t);
    Serial.print(", offset=");
    Serial.println(offset);
    #endif

    uint16_t param_len = execComponent(stack, t, offset);

    #ifdef DEBUG
    Serial.print("param=");
    for (uint16_t i = 0; i < param_len; i++) {
      Serial.print(PLD_BYTECODE[offset + i]);
      Serial.print(" ");
    }
    Serial.print(", param_len=");
    Serial.println(param_len);
    #endif

    offset += param_len; // Move to the next component
  }

  #ifdef DEBUG
  Serial.println("--- Loop End ---");
  #endif

  #ifdef DELAY_MS
  delay(DELAY_MS); // Delay for a while to avoid flooding the serial output
  #endif
}
