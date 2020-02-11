#include <chrono>
#include <thread>

#include "cpu.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("[ERROR] Usage: ./(executable) (filename)\n");
        exit(130);
    }
    // initial
    std::string file = argv[1];
    CPU t(file);

    while (true) {

        t.clock_cycle();

        t.draw();

        // keyboard
        t.deal_keyboard();

        // maybe deal with the key
        std::this_thread::sleep_for(std::chrono::microseconds(120));
    }
}
