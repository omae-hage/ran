// Timer.h
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <iostream>

class Timer {
public:
    Timer(int seconds);         // タイマーを秒単位で設定
    void start();               // タイマーを開始し、カウントダウンを表示

private:
    int remainingTime;          // 残り時間（秒）
    const int initialTime;      // 初期の時間（秒）
    void displayTime() const;   // タイマーの状態を表示する
};

#endif // TIMER_H
