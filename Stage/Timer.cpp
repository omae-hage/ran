// Timer.cpp
#include "Timer.h"

Timer::Timer(int seconds) : initialTime(seconds), remainingTime(seconds) {}

void Timer::start() {
    while (remainingTime > 0) {
        displayTime();             // タイマーの表示
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 1秒待機
        remainingTime--;           // 残り時間を1秒減らす
    }
    displayTime();  // 最後に0秒を表示
    std::cout << "ゲームオーバー！\n";
}

void Timer::displayTime() const {
    // ここで、タイマーの残り時間をゲーム風に表示
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    std::cout << "\r" << "残り時間: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << std::flush;
}
