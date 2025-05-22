#include "components.h"

/**
 * Executes a component of the PLD bytecode.
 * @param stack The stack memory.
 * @param t The type of the component, should already be consumed from the bytecode.
 * @param offset The offset of the component in the bytecode, after the type byte.
 * @return The number of bytes consumed by the component parameters
 */
uint16_t execComponent(uint8_t *s, uint8_t t, uint16_t offset) {
  switch (t) {
    case 0: // NOP
        return 0;
    case 1: // GPIO Input
        memset_pgrm(s, offset+2, digitalRead(PLD_BYTECODE[offset]));
        return 3;
    case 2: // GPIO Output
        digitalWrite(PLD_BYTECODE[offset+2], memread_pgrm(s, offset));
        return 3;
    case 3: // Digital High
        memset_pgrm(s, offset, 1);
        return 2;
    case 4: // Digital Low
        memset_pgrm(s, offset, 0);
        return 2;
    case 5: // INV
        memset_pgrm(s, offset+2, !memread_pgrm(s, offset));
        return 4;
    case 10: // AND2
        memset_pgrm(s, offset+4, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2)
        );
        return 6;
    case 11: // AND3
        memset_pgrm(s, offset+6, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4)
        );
        return 8;
    case 12: // AND4
        memset_pgrm(s, offset+8, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6)
        );
        return 10;
    case 13: // AND5
        memset_pgrm(s, offset+10, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8)
        );
        return 12;
    case 14: // AND6
        memset_pgrm(s, offset+12, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10)
        );
        return 14;
    case 15: // AND7
        memset_pgrm(s, offset+14, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10) &&
          memread_pgrm(s, offset+12)
        );
        return 16;
    case 16: // AND8
        memset_pgrm(s, offset+16, 
          memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10) &&
          memread_pgrm(s, offset+12) &&
          memread_pgrm(s, offset+14)
        );
        return 18;
    case 20: // NAND2
        memset_pgrm(s, offset+4, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2))
        );
        return 6;
    case 21: // NAND3
        memset_pgrm(s, offset+6, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4))
        );
        return 8;
    case 22: // NAND4
        memset_pgrm(s, offset+8, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6))
        );
        return 10;
    case 23: // NAND5
        memset_pgrm(s, offset+10, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8))
        );
        return 12;
    case 24: // NAND6
        memset_pgrm(s, offset+12, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10))
        );
        return 14;
    case 25: // NAND7
        memset_pgrm(s, offset+14, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10) &&
          memread_pgrm(s, offset+12))
        );
        return 16;
    case 26: // NAND8
        memset_pgrm(s, offset+16, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10) &&
          memread_pgrm(s, offset+12) &&
          memread_pgrm(s, offset+14))
        );
        return 18;
    case 27: // NAND13
        memset_pgrm(s, offset+26, 
          !(memread_pgrm(s, offset) && 
          memread_pgrm(s, offset+2) &&
          memread_pgrm(s, offset+4) &&
          memread_pgrm(s, offset+6) &&
          memread_pgrm(s, offset+8) &&
          memread_pgrm(s, offset+10) &&
          memread_pgrm(s, offset+12) &&
          memread_pgrm(s, offset+14) &&
          memread_pgrm(s, offset+16) &&
          memread_pgrm(s, offset+18) &&
          memread_pgrm(s, offset+20) &&
          memread_pgrm(s, offset+22) &&
          memread_pgrm(s, offset+24))
        );
        return 28;
    case 30: // OR2
        memset_pgrm(s, offset+4, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2)
        );
        return 6;
    case 31: // OR3
        memset_pgrm(s, offset+6, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4)
        );
        return 8;
    case 32: // OR4
        memset_pgrm(s, offset+8, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6)
        );
        return 10;
    case 33: // OR5
        memset_pgrm(s, offset+10, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8)
        );
        return 12;
    case 34: // OR6
        memset_pgrm(s, offset+12, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10)
        );
        return 14;
    case 35: // OR7
        memset_pgrm(s, offset+14, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10) ||
          memread_pgrm(s, offset+12)
        );
        return 16;
    case 36: // OR8
        memset_pgrm(s, offset+16, 
          memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10) ||
          memread_pgrm(s, offset+12) ||
          memread_pgrm(s, offset+14)
        );
        return 18;
    case 40: // NOR2
        memset_pgrm(s, offset+4, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2))
        );
        return 6;
    case 41: // NOR3
        memset_pgrm(s, offset+6, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4))
        );
        return 8;
    case 42: // NOR4
        memset_pgrm(s, offset+8, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6))
        );
        return 10;
    case 43: // NOR5
        memset_pgrm(s, offset+10, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8))
        );
        return 12;
    case 44: // NOR6
        memset_pgrm(s, offset+12, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10))
        );
        return 14;
    case 45: // NOR7
        memset_pgrm(s, offset+14, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10) ||
          memread_pgrm(s, offset+12))
        );
        return 16;
    case 46: // NOR8
        memset_pgrm(s, offset+16, 
          !(memread_pgrm(s, offset) || 
          memread_pgrm(s, offset+2) ||
          memread_pgrm(s, offset+4) ||
          memread_pgrm(s, offset+6) ||
          memread_pgrm(s, offset+8) ||
          memread_pgrm(s, offset+10) ||
          memread_pgrm(s, offset+12) ||
          memread_pgrm(s, offset+14))
        );
        return 18;
    case 50: // XOR2
        memset_pgrm(s, offset+4, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2)
        );
        return 6;
    case 51: // XOR3
        memset_pgrm(s, offset+6, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4)
        );
        return 8;
    case 52: // XOR4
        memset_pgrm(s, offset+8, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6)
        );
        return 10;
    case 53: // XOR5
        memset_pgrm(s, offset+10, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8)
        );
        return 12;
    case 54: // XOR6
        memset_pgrm(s, offset+12, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8) ^
          memread_pgrm(s, offset+10)
        );
        return 14;
    case 55: // XOR7
        memset_pgrm(s, offset+14, 
          memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8) ^
          memread_pgrm(s, offset+10) ^
          memread_pgrm(s, offset+12)
        );
        return 16;
    case 60: // XNOR2
        memset_pgrm(s, offset+4, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2))
        );
        return 6;
    case 61: // XNOR3
        memset_pgrm(s, offset+6, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4))
        );
        return 8;
    case 62: // XNOR4
        memset_pgrm(s, offset+8, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6))
        );
        return 10;
    case 63: // XNOR5
        memset_pgrm(s, offset+10, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8))
        );
        return 12;
    case 64: // XNOR6
        memset_pgrm(s, offset+12, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8) ^
          memread_pgrm(s, offset+10))
        );
        return 14;
    case 65: // XNOR7
        memset_pgrm(s, offset+14, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8) ^
          memread_pgrm(s, offset+10) ^
          memread_pgrm(s, offset+12))
        );
        return 16;
    case 66: // XNOR8
        memset_pgrm(s, offset+16, 
          !(memread_pgrm(s, offset) ^ 
          memread_pgrm(s, offset+2) ^
          memread_pgrm(s, offset+4) ^
          memread_pgrm(s, offset+6) ^
          memread_pgrm(s, offset+8) ^
          memread_pgrm(s, offset+10) ^
          memread_pgrm(s, offset+12) ^
          memread_pgrm(s, offset+14))
        );
        return 18;
    case 70: // BUF
        memset_pgrm(s, offset+2, memread_pgrm(s, offset+4));
        memset_pgrm(s, offset+4, memread_pgrm(s, offset));
        return 6;
    case 71: // BUF_INV
        memset_pgrm(s, offset+2, !memread_pgrm(s, offset+4));
        memset_pgrm(s, offset+4, memread_pgrm(s, offset));
        return 6;
    case 80: // DFF
        // Rising edge of clock
        if (memread_pgrm(s, offset+2) == 1 && memread_pgrm(s, offset+8) == 0) {
            // Update stored value from D
            memset_pgrm(s, offset+10, memread_pgrm(s, offset));
        }
        // Update last value of clock
        memset_pgrm(s, offset+8, memread_pgrm(s, offset+2));
        // Update Q and Qneg
        memset_pgrm(s, offset+4, memread_pgrm(s, offset+10));
        memset_pgrm(s, offset+6, !memread_pgrm(s, offset+10));
        return 12;
    case 90: // DEC_BCD_7
    {
        // Ignoring LT, RBI, and BI
        const int dec = memread_pgrm(s, offset) << 3 | 
          memread_pgrm(s, offset+2) << 2 | 
          memread_pgrm(s, offset+4) << 1 | 
          memread_pgrm(s, offset+6);

        int out = 0; // bits of 7-segment display
        if (dec == 0) out = 0b00111111; // 0
        else if (dec == 1) out = 0b00000110; // 1
        else if (dec == 2) out = 0b01011011; // 2
        else if (dec == 3) out = 0b01001111; // 3
        else if (dec == 4) out = 0b01100110; // 4
        else if (dec == 5) out = 0b01101101; // 5
        else if (dec == 6) out = 0b01111101; // 6
        else if (dec == 7) out = 0b00000111; // 7
        else if (dec == 8) out = 0b01111111; // 8
        else if (dec == 9) out = 0b01101111; // 9
        else if (dec == 10) out = 0b01110111; // A
        else if (dec == 11) out = 0b01111100; // B
        else if (dec == 12) out = 0b00111001; // C
        else if (dec == 13) out = 0b01011110; // D
        else if (dec == 14) out = 0b01111001; // E
        else if (dec == 15) out = 0b01110001; // F
        else out = 0b00000000; // Invalid value, turn off all segments
        
        // Set the output to the 7-segment display
        memset_pgrm(s, offset+14, out);
        memset_pgrm(s, offset+16, out >> 1);
        memset_pgrm(s, offset+18, out >> 2);
        memset_pgrm(s, offset+20, out >> 3);
        memset_pgrm(s, offset+22, out >> 4);
        memset_pgrm(s, offset+24, out >> 5);
        memset_pgrm(s, offset+26, out >> 6);
        return 28;
    }
    default:
        // Invalid component type
        Serial.print("Invalid component type: ");
        Serial.println(t);
        Serial.print(" Offset: ");
        Serial.println(offset);
        return 0;
  }
}