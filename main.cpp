#include <chrono>
#include <thread>

#include "cpu.hpp"

int main() {
    // initial
    CPU t;
    while (true) {

        t.clock_cycle();

        t.draw();

        // keyboard
        t.deal_keyboard();

        // maybe deal with the key
        //std::this_thread::sleep_for(std::chrono::microseconds(1200));
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }
}
