#pragma once
// Структура для рекламных роликов в сетке вещания
struct Broadcast_ad {
    char name[30];
    int duration;
    int hour;
    int minute;

    Broadcast_ad *next;
};