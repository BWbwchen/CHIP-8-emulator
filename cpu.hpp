#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>  // srand, rand
#include <time.h>    // time

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#define WIDTH 64
#define HEIGHT 32

class CPU {
   private:
    // cpu
    uint8_t memory[4096];       // 4KB
    uint8_t reg[16];            // register
    bool graph[HEIGHT][WIDTH];  // draw
    uint8_t key[16];            // keyboard
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint16_t pc;         // program counter
    uint16_t stack[16];  // stack
    uint16_t sp;         // stack pointer
    uint16_t I;          // index pointer
    uint16_t opcode;

    bool draw_flag;

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

    const uint8_t keymap[16] = {SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w,
                                SDLK_e, SDLK_a, SDLK_s, SDLK_d, SDLK_z, SDLK_c,
                                SDLK_4, SDLK_r, SDLK_f, SDLK_v};

    // draw thing
    const uint32_t BLOCK_LONG = 10;
    const uint32_t SCREEN_WIDTH = WIDTH * BLOCK_LONG;
    const uint32_t SCREEN_HEIGHT = HEIGHT * BLOCK_LONG;

    // The window we'll be rendering to
    SDL_Window* window = nullptr;

    // The surface contained by the window
    SDL_Surface* screenSurface = nullptr;

    // The render
    SDL_Renderer* renderer;

    // The texture
    SDL_Texture* texture;

    std::vector<uint32_t> buffer;

    // event
    SDL_Event e;

   public:
    CPU(std::string);
    void clock_cycle();
    void draw();
    void deal_keyboard();

   private:
    void init();
    void init_sdl();
    void close();
    void load_file(std::string);
    void clear_graph();
    void refresh();
    void message(std::string, uint16_t , std::string);
};
