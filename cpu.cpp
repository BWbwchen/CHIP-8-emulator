#include "cpu.hpp"

// public
CPU::CPU() {
    init();
    load_file();
}

void CPU::clock_cycle() {
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];
    // Decode Opcode
    // Execute Opcode
    switch (opcode & 0xF000) {
        case 0x0000:
            if (opcode == 0x00E0) {
                // CLS
                clear_graph();
            } else if (opcode == 0x00EE) {
                // RET
                pc = stack[sp--];
            } else {
                printf("[ERROR]Unknown code %04X", opcode);
                exit(127);
            }
            pc += 2;
            break;
        case 0x1000:
            // JP addr
            pc = opcode & 0x0FFF;
            pc += 2;
            break;
        case 0x2000:
            // CALL addr
            stack[++sp] = pc;
            pc = opcode & 0x0FFF;
            break;
        case 0x3000:
            // 3xkk
            // SE Vx, byte
            auto x = (opcode & 0x0F00) >> 8;
            auto byte = (opcode & 0x00FF);
            if (reg[x] == byte) {
                pc += 4;    
            } else {
                pc += 2;
            }
            break;
        case 0x4000:
            // 4xkk 
            // SNE Vx, byte
            auto x = (opcode & 0x0F00) >> 8;
            auto byte = (opcode & 0x00FF);
            if (reg[x] != byte) {
                pc += 4;    
            } else {
                pc += 2;
            }
            break;
        case 0x5000:
            // 5xy0 
            // SE Vx, Vy
            auto x = (opcode & 0x0F00) >> 8;
            auto y = (opcode & 0x00F0) >> 4;
            if (reg[x] == reg[y]) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        case 0x6000:
            // 6xkk 
            // LD Vx, byte
            auto x = (opcode & 0xF00) >> 8;
            auto byte = (opcode & 0x00FF);
            reg[x] = byte;
            pc += 2;
            break;
        case 0x7000:
            // 7xkk 
            // ADD Vx, byte
            auto x = (opcode & 0xF00) >> 8;
            auto byte = (opcode & 0x00FF);
            reg[x] += byte;
            pc += 2; 
            break;
        case 0x8000:
            auto x = (opcode & 0x0F00) >> 8;
            auto y = (opcode & 0x00F0) >> 4;
            switch (opcode & 0x000F) {
                case 0x0:
                    // 8xy0 - LD Vx, Vy
                    reg[x] = reg[y];
                    pc += 2;
                    break;
                case 0x1: 
                    // 8xy1 - OR Vx, Vy
                    reg[x] |= reg[y];
                    pc += 2;
                    break;
                case 0x2:
                    // 8xy2 - AND Vx, Vy
                    reg[x] &= reg[y];
                    pc += 2;
                    break;
                case 0x3:
                    // 8xy3 - XOR Vx, Vy
                    reg[x] ^= reg[y];
                    pc += 2;
                    break;
                case 0x4:
                    // 8xy4 - ADD Vx, Vy
                    if (reg[x] > (0xFF - reg[y])) {
                        reg[0xF] = 1;
                    } else {
                        reg[0xF] = 0;
                    }
                    reg[x] += reg[y];
                    pc += 2;
                    break;
                case 0x5:
                    // 8xy5 - SUB Vx, Vy
                    if (reg[x] > reg[y]) {
                        reg[0xF] = 1;
                    } else {
                        reg[0xF] = 0;
                    }
                    reg[x] -= reg[y];
                    pc += 2;
                    break;
                case 0x6:
                    // 8xy6 - SHR Vx {, Vy}
                    if (reg[x] & 0x01) {
                        reg[0xF] = 1;
                    } else {
                        reg[0xF] = 0;
                    }
                    reg[x] >> 1;
                    pc += 2;
                    break;
                case 0x7:
                    // 8xy7 - SUBN Vx, Vy
                    if (reg[x] < reg[y]) {
                        reg[0xF] = 1;
                    } else {
                        reg[0xF] = 0;
                    }
                    reg[x] = reg[y] - reg[x];
                    pc += 2;
                    break;
                case 0xE:
                    // 8xyE - SHL Vx {, Vy}
                    if (reg[x] & 0x80) {
                        reg[0xF] = 1;
                    } else {
                        reg[0xF] = 0;
                    }
                    reg[x] << 1;
                    pc += 2;
                    break;
                default:
                    printf("[ERROR]Unknown code %04X", opcode);
                    exit(127);
            }
            break;
        case 0x9000:
            // 9xy0 - SNE Vx, Vy
            auto x = (opcode & 0x0F00) >> 8;
            auto y = (opcode & 0x00F0) >> 4;
            if (reg[x] != reg[y]) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        case 0xA000:
            // Annn - LD I, addr
            I = opcode & 0x0FFF;
            pc += 2;
            break;
        case 0xB000:
            // Bnnn - JP V0, addr
            pc = reg[0] + (opcode & 0x0FFF);
            break;
        case 0xC000:
            // Cxkk - RND Vx, byte
            auto rnum = rand() % 256; // 0 ~ 255
            auto x = (opcode & 0x0F00) >> 8;
            reg[x] = rnum & (opcode & 0x00FF);
            pc += 2;
            break;
        case 0xD000:
            // Dxyn - DRW Vx, Vy, nibble

            break;
        case 0xE000:
            if (opcode & 0x000F == 0xE) {
                // Ex9E - SKP Vx

            } else if (opcode & 0x000F === 0x1) {
                // ExA1 - SKNP Vx

            } else {

            }
            break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x07:
                    // Fx07 - LD Vx, DT

                case 0x0A:
                    // Fx0A - LD Vx, K

                case 0x15:
                    // Fx15 - LD DT, Vx

                case 0x18:
                    // Fx18 - LD ST, Vx

                case 0x1E:
                    // Fx1E - ADD I, Vx

                case 0x29:
                    // Fx29 - LD F, Vx

                case 0x33:
                    // Fx33 - LD B, Vx

                case 0x55:
                    // Fx55 - LD [I], Vx

                case 0x65:
                    // Fx65 - LD Vx, [I]

                default:

            }
            break;
        default :

    }
}

bool CPU::get_draw_flag() {}

void CPU::draw() {}

// private

void CPU::init() {
    // memory
    for (int i = 0; i < 4096; ++i) memory[i] = 0;
    // register
    for (int i = 0; i < 16; ++i) reg[i] = 0;
    // graph
    clear_graph();
    // stack
    for (int i = 0; i < 16; ++i) stack[i] = 0;

    sp = 0;
    I = 0;
    pc = 0x200;
    opcode = 0;
    delay_timer = 0;
    sound_timer = 0;

    // random
    srand(time(NULL));
}

void CPU::load_file() {
    // load font
    for (int i = 0; i < 80; ++i) {
        memory[i] = font_set[i];
    }

    // load game file
    // TODO : can do better
    std::streampos file_size;
    std::ifstream file("roms/PONG2", std::ios::binary);

    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> a(file_size);
    file.read((char*)&a[0], file_size);

    // push into memory
    for (int i = 0; i < file_size; ++i) {
        memory[i + 512] = a[i];
    }

    std::cout << "init finished" << std::endl;
}

void CPU::clear_graph(Inaccessible)() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            graph[i][j] = 0;
        }
    }
}
