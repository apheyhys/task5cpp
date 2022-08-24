#include <iostream>

struct Ad {
    int id;
    char name[10];
    int duration;
    int sequence;
};

struct Channels {
    int id;
    char name[10];

    Ad ads;
    struct Channels *prev;
    struct Channels *next;
};

Channels *create_channels();

#define CHANNEL_LIST "/home/ubuntu/CLionProjects/task5cpp/channels.txt" // адрес основного текста
#define ADS_LIST "/home/ubuntu/CLionProjects/task5cpp/ads.txt" // адрес дополнительного текста
#define TOTAL_LIST "/home/ubuntu/CLionProjects/task5cpp/total_list.txt" // адрес итогового текста


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


//List *create_struct(const char *N, int size) {
//    List *p_begin = nullptr;
//    List *p = nullptr;
//    // Выделяем память
//    p_begin = (List *) malloc(sizeof(List)); // Выделяем память под первую ячейку структуры
//    p = p_begin;
//    p->next = nullptr;
//    p->count = 0;
//
//    // Заполняем новую структуру данными
//    for (int k = 1; k < size; k++) {
//        p->count = k - 1;
//        p->value = N[k - 1];
//        if (k < size - 1) {
//            p->next = (List *) malloc(sizeof(List)); // Выделяем память под каждую новую ячейку структуры
//            // Следующий элемент
//            p = p->next;
//        }
//        p->next = nullptr;
//    }
//    return p_begin;
//}