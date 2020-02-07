#pragma once

#include <stdlib.h>  // srand, rand
#include <time.h>    // time

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#define WIDTH 64
#define HEIGHT 32

class CPU {
   private:
    uint8_t memory[4096];          // 4KB
    uint8_t reg[16];               // register
    uint8_t graph[HEIGHT][WIDTH];  // draw
    uint8_t sp;                    // stack pointer
    uint8_t I;                     // index pointer
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t pc;         // program counter
    uint16_t stack[16];  // stack
    uint16_t opcode;

    const uint8_t font_set[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
        0x20, 0x60, 0x20, 0x20, 0x70,  // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
        0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
        0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
        0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
        0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
        0xF0, 0x80, 0xF0, 0x80, 0x80   // F
    };

   public:
    CPU();
    void clock_cycle();
    bool get_draw_flag();
    void draw();

   private:
    void init();
    void load_file();
    void clear_graph();
};