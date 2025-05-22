#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <pld_bytecode.h>

uint8_t read8(const unsigned char *data, int offset);
uint8_t read8(const unsigned char *data);
uint16_t read16(const unsigned char *data, int offset);
uint16_t read16(const unsigned char *data);

int memread(uint8_t *stack, int pointer, int size);
int memread(uint8_t *stack, int pointer);
int memread_pgrm(uint8_t *stack, int offset, int size);
int memread_pgrm(uint8_t *stack, int offset);

void memset(uint8_t *stack, int pointer, int value, int size);
void memset(uint8_t *stack, int pointer, int value);
void memset_pgrm(uint8_t *stack, int offset, int value, int size);
void memset_pgrm(uint8_t *stack, int offset, int value);

#endif