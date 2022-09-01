#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iomanip>

using namespace std;

struct Ad {
    int id;
    char name[30];
    int duration;
    int sequence;

    Ad *next;
};

struct Channels {
    int id;
    char name[30];

    struct Ad *ads;

    Channels *next;
};

// Структуры для сетки вещания

struct Broadcast_ads {
    char name[30];
    int duration;
    int hour;
    int minute;

    Broadcast_ads *next;
};

struct Broadcast {
    char name[30];

    struct Broadcast_ads *broadcast_ads;

    Broadcast *next;
};

Channels *create_channels(const char *filename);

void *create_total_structure(Channels *p_begin, const char *filename);


#define CHANNEL_LIST "/home/ubuntu/CLionProjects/task5cpp/channels.txt" // адрес основного текста
#define ADS_LIST "/home/ubuntu/CLionProjects/task5cpp/ads.txt" // адрес дополнительного текста
#define TOTAL_LIST "/home/apheyhys/CLionProjects/task5cpp/total_list.txt" // адрес итогового текста

Broadcast *broadcast_structure(Channels *p_begin);

void print_structure(Broadcast *p_begin);


int main() {
    cout << "--------------------------------" << endl;
    cout << "\nДемонстрация работы каналов:   \n" << endl;
    Channels *channels_list = create_channels(CHANNEL_LIST);

    create_total_structure(channels_list, ADS_LIST);

    Broadcast *broadcast_struct = broadcast_structure(channels_list);
    print_structure(broadcast_struct);

    return 0;
}

void print_structure(Broadcast *p_begin) {
    // Печатаем до последнего символа
    while (p_begin != nullptr) {
        if (p_begin->next != nullptr) {
            cout << "--------------------------------" << endl;
            cout << "Название канала: " << p_begin->name << endl;
            cout << "--------------------------------" << endl;
//            while (p_begin->broadcast_ads->next != nullptr) {
//                cout << "Время начала ролика: " << setfill('0') << setw(2) << p_begin->broadcast_ads->hour << ":" << setfill('0')
//                     << setw(2) << p_begin->broadcast_ads->minute << " Название ролика: " << p_begin->broadcast_ads->name <<
//                     " Длительность: " <<  p_begin->broadcast_ads->duration << " ceк."
//                     << endl;
//
//
//
//                p_begin->broadcast_ads = p_begin->broadcast_ads->next;
//            }
            p_begin = p_begin->next;
        }


    }
}


Broadcast *broadcast_structure(Channels *p_begin) {
    Channels *p = p_begin;

    // Инициализируем структуру, в которую будет записывать вещание
    Broadcast *b_begin = nullptr;
    Broadcast *b = nullptr;
    // Выделяем память
    b_begin = (Broadcast *) malloc(sizeof(Broadcast)); // Выделяем память под первую ячейку структуры
    b = b_begin;
    b->next = nullptr;

    // Генератор псевдослучайных чисел определения часа, в котором будет происходить вещание
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 23.0);
    int random_hour = dist(mt);

    while (p != nullptr) {
        // Переписываем названия каналов
        int name_count = 0;
        for (char t: p->name) {
            b->name[name_count] = t;
            name_count++;
        }

        int position_count = 0;

        int ads_count = 0;

        int ads_priority = 0;

        Ad *a = p->ads; // Запоминаем голову списка рекламных роликов

        int ads_arr[20];

        // Первый раз обходим список и подсчитываем количество роликов в каждом канале, также находим ролик с максимальным приоритетом
        while (p->ads != nullptr) {

            if (p->ads->sequence > ads_priority) {
                ads_priority = p->ads->sequence;
            }
            ads_arr[ads_count] = p->ads->id;
            ads_count++;

            p->ads = p->ads->next;
        }
        p->ads = a;


        int broadcasting_count = 0;

        int priority = ads_priority;

        int current_id;

        while (broadcasting_count < 60 && p->ads != nullptr) {
            int rand_ads = ads_arr[random() % ads_count];

            // Если рандомный ролик из массива равен текущему и его приоритет меньше предыдущего и текущий id ролика не равен предыдущему
            if (rand_ads == p->ads->id && priority > p->ads->sequence && current_id != rand_ads) {
//                cout << "Время начала ролика: " << setfill('0') << setw(2) << random_hour << ":" << setfill('0')
//                     << setw(2) << position_count << " Название ролика: " << p->ads->name <<
//                     " Длительность: " << p->ads->duration << " ceк." << " Приоритет: " << p->ads->sequence
//                     << endl;



                struct Broadcast_ads *temp, *ab;
                temp = (Broadcast_ads *) malloc(sizeof(Broadcast_ads)); // выделяем память для вложенной структуры

                ab = b->broadcast_ads; // сохранение указателя на следующий узел
//                ab
//                temp->next = nullptr;
                b->broadcast_ads = temp; // предыдущий узел указывает на создаваемый

                temp->duration = p->ads->duration;

                int word_count = 0;

                for (char s: p->ads->name) {
                    temp->name[word_count] = s;
                    word_count++;
                }
                temp->hour = random_hour;
                temp->minute = position_count;



//                temp->next = nullptr;

//                while (temp->next) {
//                    ab = ab->next;
//                }

//                temp->next = ab;
//                b->broadcast_ads = temp;
ab->next = (Broadcast_ads *) malloc(sizeof(Broadcast_ads));
               temp = ab->next;
//                ab = ab->next;

                priority = p->ads->sequence;
                current_id = p->ads->id;
                broadcasting_count++;
                position_count++;
            }
            p->ads = p->ads->next;
            if (p->ads == nullptr) {
                priority = ads_priority;
                p->ads = a;
            }
        }
        if (p->next != nullptr) {
            b->next = (Broadcast *) malloc(sizeof(Broadcast));
            b = b->next;
        }
        p = p->next;
    }

    return b_begin;
}


void *create_total_structure(Channels *p_begin, const char *filename) {
    // Открываем файл
    ifstream readfile(filename, ios::in);
    // Читаем все символы, включая пробелы
    readfile >> std::noskipws;

    Channels *p = p_begin;

    char id[30]{};

    if (!readfile) {
        cout << "Ошибка открытия файла" << endl;
        return reinterpret_cast<Channels *>(-1);
    } else {
        while (true) {
            readfile.getline(id, 30);

            if (!readfile.eof()) {
                unsigned int limit1[5]{};
                unsigned int limit2 = 0;

                size_t i = 0;

                int two_point_count = 0;

                for (auto x: id) {

                    if (id[i] == ':') {
                        limit1[two_point_count] = i;
                        two_point_count++;
                    }
                    if (id[i] == ';') {
                        limit2 = i;
                        break;
                    }
                    i++;
                }

                char ads_id[2];

                char name[30]{};

                char duration[2]{};

                char sequence[2]{};

                char channels_id_arr[4]{};

                int sequence_count = 0;

                int channels_id_count = 0;

                int name_count = 0;

                int duration_count = 0;

                int ads_id_count = 0;

                for (int k = 0; k < limit2; k++) {
                    if (k < limit1[0]) {
                        ads_id[ads_id_count] = id[k];
                        ads_id_count++;
                    }
                    if (k > limit1[0] && k < limit1[1]) {
                        name[name_count] = id[k];
                        name_count++;
                    }
                    if (k > limit1[1] && k < limit1[2]) {
                        duration[duration_count] = id[k];
                        duration_count++;
                    }
                    if (k > limit1[2] && k < limit1[3]) {
                        if (id[k] != ',') {
                            channels_id_arr[channels_id_count] = id[k];
                            channels_id_count++;
                        }
                    }
                    if (k > limit1[3] && k < limit2) {
                        sequence[sequence_count] = id[k];
                        sequence_count++;
                    }
                }

                int convert_id;

                if (ads_id[1]) {
                    convert_id = (int(ads_id[0]) - 48) * 10 + int(ads_id[1]) - 48;
                } else {
                    convert_id = int(ads_id[0]) - 48;
                }

                int convert_duration = (int(duration[0]) - 48) * 10 + int(duration[1] - 48);

                int convert_sequence = (int(sequence[0]) - 48) * 10 + int(sequence[1] - 48);

                for (char t: channels_id_arr) {
                    while (p != nullptr) {
                        if (int(t) - 48 == p->id) {
                            struct Ad *temp, *a;
                            temp = (Ad *) malloc(sizeof(Ad)); // выделяем память для вложенной структуры
                            a = p->ads; // сохранение указателя на следующий узел
                            p->ads = temp; // предыдущий узел указывает на создаваемый
                            temp->id = convert_id; // сохранение поля данных добавляемого узла
                            temp->duration = convert_duration;

                            int word_count = 0;

                            for (char s: name) {
                                temp->name[word_count] = s;
                                word_count++;
                            }

                            temp->sequence = convert_sequence;
                            temp->next = a;  // созданный узел указывает на следующий элемент
                        }
                        p = p->next;
                    }
                    p = p_begin;
                }
            } else break;
        }

        readfile.close();
//        return p_begin;
    }
}


Channels *create_channels(const char *filename) {
    // Открываем файл
    ifstream readfile(filename, ios::in);
    // Читаем все символы, включая пробелы
    readfile >> std::noskipws;

    Channels *p_begin = nullptr;
    Channels *p = nullptr;
    // Выделяем память
    p_begin = (Channels *) malloc(sizeof(Channels)); // Выделяем память под первую ячейку структуры
    p = p_begin;
    p->next = nullptr;

    char id[30]{};

    if (!readfile) {
        cout << "Ошибка открытия файла" << endl;
        return reinterpret_cast<Channels *>(-1);
    } else {
        while (true) {
            readfile.getline(id, 30);

            if (!readfile.eof()) {
                unsigned int limit1 = 0;
                unsigned int limit2 = 0;

                size_t i = 0;

                for (auto x: id) {
                    if (id[i] == ':') {
                        limit1 = i;
                    }
                    if (id[i] == ';') {
                        limit2 = i;
                    }
                    i++;
                }

                char channel_id;

                char name[30]{};

                int name_count = 0;

                for (int k = 0; k < limit2; k++) {
                    if (k < limit1) {
                        channel_id = id[k];
                    }
                    if (k > limit1 && k < limit2) {
                        name[name_count] = id[k];
                        name_count++;
                    }
                }

                p->id = int(channel_id) - 48;
                for (int n = 0; n < 30; n++) {
                    p->name[n] = name[n];
                }

                p->next = (Channels *) malloc(sizeof(Channels));
                p = p->next;

                p->next = nullptr;
            } else break;
        }

        readfile.close();
        return p_begin;
    }
}
