#include <bits/stdc++.h>

#include <chrono>
#include <thread>

#include "cpu.hpp"

int main() {
    // initial
    CPU t;

    while (1) {
        // 1 clock cycle
        t.clock_cycle();
        // draw
        if (t.get_draw_flag()) {
            t.draw();
        }

        // keyboard
        t.deal_keyboard();

        // maybe deal with the key
        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }
}
