#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <pld_bytecode.h>
#include "config.h"

uint8_t read8(const unsigned char *data, int offset);
uint8_t read8(const unsigned char *data);
uint16_t read16(const unsigned char *data, int offset);
uint16_t read16(const unsigned char *data);

int stackread(uint8_t *stack, int pointer, int size);
int stackread(uint8_t *stack, int pointer);
int stackread_pgrm(uint8_t *stack, int offset, int size);
int stackread_pgrm(uint8_t *stack, int offset);

void stackset(uint8_t *stack, int pointer, int value, int size);
void stackset(uint8_t *stack, int pointer, int value);
void stackset_pgrm(uint8_t *stack, int offset, int value, int size);
void stackset_pgrm(uint8_t *stack, int offset, int value);

#endif