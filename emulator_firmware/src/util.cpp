#include <util.h>

uint8_t read8(const unsigned char *data, int offset) {
  return pgm_read_byte_near(data + offset);
}
uint8_t read8(const unsigned char *data) {
  return read8(data, 0);
}
uint16_t read16(const unsigned char *data, int offset) {
  return pgm_read_byte_near(data + offset) << 8 | (pgm_read_byte_near(data + offset + 1));
}
uint16_t read16(const unsigned char *data) {
  return read16(data, 0);
}
/**
 * Reads a number of bits from the PLD stack memory.
 * @param pointer The address of the first bit to read. (in bits)
 * @param size The number of bits to read. Default is 1. Max is 32
 * @return The value read from the memory.
 */
int stackread(uint8_t *stack, int pointer, int size) {
  int value = 0;
  for (int i = 0; i < size; i++) {
    value |= ((stack[(pointer + i) / 8] >> ((pointer + i) % 8)) & 1) << (size - 1 - i);
  }

  #ifdef DEBUG
  Serial.print(">stackread: pointer=");
  Serial.print(pointer);
  Serial.print(", value=");
  Serial.print(value, BIN);
  Serial.print(", size=");
  Serial.println(size);
  #endif

  return value;
}
int stackread(uint8_t *stack, int pointer) {
  return stackread(stack, pointer, 1);
}
int stackread_pgrm(uint8_t *stack, int offset, int size) {
  return stackread(stack, read16(PLD_BYTECODE, offset), size);
}
int stackread_pgrm(uint8_t *stack, int offset) {
  return stackread(stack, read16(PLD_BYTECODE, offset));
}

/**
 * Writes a number of bits to the PLD stack memory.
 * @param pointer The address of the first bit to write. (in bits)
 * @param value The value to write. (in bits)
 * @param size The number of bits to write. Default is 1. Max is 32
 */
void stackset(uint8_t *stack, int pointer, int value, int size) {
  for (int i = 0; i < size; i++) {
    if (value & (1 << (size - 1 - i))) {
      stack[(pointer + i) / 8] |= (1 << ((pointer + i) % 8));
    } else {
      stack[(pointer + i) / 8] &= ~(1 << ((pointer + i) % 8));
    }
  }

  #ifdef DEBUG
  Serial.print(">stackset: pointer=");
  Serial.print(pointer);
  Serial.print(", value=");
  Serial.print(value, BIN);
  Serial.print(", size=");
  Serial.println(size);
  #endif
}
void stackset(uint8_t *stack, int pointer, int value) {
  stackset(stack, pointer, value, 1);
}
void stackset_pgrm(uint8_t *stack, int offset, int value, int size) {
  stackset(stack, read16(PLD_BYTECODE, offset), value, size);
}
void stackset_pgrm(uint8_t *stack, int offset, int value) {
  stackset(stack, read16(PLD_BYTECODE, offset), value);
}