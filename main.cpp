#include <bits/stdc++.h>

#include "cpu.hpp"

#include <chrono>
#include <thread>

int main() {
    // initial
    CPU t;

    t.clock_cycle();
    while (1) {
        // 1 clock cycle
        t.clock_cycle();
/*
        // draw
        if (t.get_draw_flag()) {
            t.draw();
        }
*/

        // maybe deal with the key
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}
