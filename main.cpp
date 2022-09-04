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

    Broadcast_ads *broadcast_ads;

    Broadcast *next;
};

struct Generator {
    int random_channel;
    int random_minute;
    int random_hour;
} generator;

Channels *create_channels(const char *filename);

void *create_total_structure(Channels *p_begin, const char *filename);

void gen_add_parameter(Channels *p_begin);


#define CHANNEL_LIST "/home/apheyhys/CLionProjects/task5cpp/channels.txt" // адрес основного текста
#define ADS_LIST "/home/apheyhys/CLionProjects/task5cpp/ads.txt" // адрес дополнительного текста
#define TOTAL_LIST "/home/apheyhys/CLionProjects/task5cpp/broadcast.txt" // адрес итогового текста



void appendBroadcast(Broadcast_ads **head_ref, const char *name, int duration, int minute, int hour);

Broadcast * print_structure(Broadcast *p_begin);

Broadcast *broadcast_structure(Channels *p_begin);

void write_broadcast(Broadcast *broadcast_struct, const char *filename);

int main() {
    cout << "--------------------------------" << endl;
    cout << "\nДемонстрация работы каналов:   \n" << endl;
    Channels *channels_list = create_channels(CHANNEL_LIST);

    create_total_structure(channels_list, ADS_LIST);

    Broadcast *broadcast_struct = broadcast_structure(channels_list);
    print_structure(broadcast_struct);

    write_broadcast(broadcast_struct, TOTAL_LIST);

    delete channels_list;

    delete broadcast_struct;

    return 0;
}


void write_broadcast(Broadcast *broadcast_struct, const char *filename) {
    ofstream writefile(filename, ios_base::trunc);
    Broadcast *p = broadcast_struct;


    while (p->next != nullptr) {
        writefile << "--------------------------------" << endl;
        writefile << "Название канала: " << p->name << endl;
        writefile << "--------------------------------" << endl;
        int minute_count = 0;
        while (p->broadcast_ads) {
            writefile << "Время начала ролика: " << setfill('0') << setw(2) << p->broadcast_ads->hour << ":"
                 << setfill('0')
                 << setw(2) << p->broadcast_ads->minute << " Название ролика: " << p->broadcast_ads->name <<
                 " Длительность: " << p->broadcast_ads->duration << " ceк."
                 << endl;
            minute_count++;
            p->broadcast_ads = p->broadcast_ads->next;
        }

        if (minute_count < 59) {
            writefile << "Трансляция была прервана..." << endl;
        }
        p = p->next;
    }

    writefile.close();
}


void gen_add_parameter(Channels *p_begin) {
    // Генератор псевдослучайных чисел, для определения часа, в котором будет происходить вещание
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 23.0);

    uniform_int_distribution<int> minute(1, 59);

    int random_hour = dist(mt);

    int random_minute = minute(mt);

    int channel_count = 0;
    while (p_begin->next != nullptr) {
        p_begin = p_begin->next;
        channel_count++;
    }

    uniform_int_distribution<int> channel(1, channel_count);

    int random_channel = channel(mt);

    // Выделяем память
    generator = *new Generator(); // (Broadcast *) malloc(sizeof(Broadcast));
    generator.random_channel = random_channel;
    generator.random_minute = random_minute;
    generator.random_hour = random_hour;
}



Broadcast * print_structure(Broadcast *p_begin) {
    Broadcast *p = p_begin;
    // Печатаем до последнего символа
    while (p->next != nullptr) {
        cout << "--------------------------------" << endl;
        cout << "Название канала: " << p->name << endl;
        cout << "--------------------------------" << endl;
        int minute_count = 0;
        Broadcast_ads *b_ads = p->broadcast_ads;
        while (p->broadcast_ads) {
            cout << "Время начала ролика: " << setfill('0') << setw(2) << p->broadcast_ads->hour << ":"
                 << setfill('0')
                 << setw(2) << p->broadcast_ads->minute << " Название ролика: " << p->broadcast_ads->name <<
                 " Длительность: " << p->broadcast_ads->duration << " ceк."
                 << endl;
            minute_count++;
            p->broadcast_ads = p->broadcast_ads->next;
        }
        p->broadcast_ads = b_ads;
        if (minute_count < 59) {
            cout << "Трансляция была прервана..." << endl;
        }
        p = p->next;
    }
    return p;
}

void appendBroadcast(Broadcast_ads **head_ref, const char *name, int duration, int minute, int hour) {

    // 1. allocate node
    auto *new_node = new Broadcast_ads();

    // Used in step 5
    Broadcast_ads *last = *head_ref;

    // 2. Put in the data
    for (int i = 0; i<30; i++) {
        new_node->name[i] = name[i];
    }

    new_node->duration = duration;
    new_node->hour = hour;
    new_node->minute = minute;

    // 3. This new node is going to be
    // the last node, so make next of
    // it as NULL
    new_node->next = nullptr;

    // 4. If the Linked List is empty,
    // then make the new node as head
    if (*head_ref == nullptr) {
        *head_ref = new_node;
        return;
    }

    // 5. Else traverse till the last node
    while (last->next != nullptr) {
        last = last->next;
    }

    // 6. Change the next of last node
    last->next = new_node;
}


Broadcast *broadcast_structure(Channels *p_begin) {
    Channels *p = p_begin;

    // Инициализируем структуру, в которую будет записывать вещание
    Broadcast *b_begin = nullptr;
    Broadcast *b = nullptr;
    // Выделяем память
    b_begin = new Broadcast(); // (Broadcast *) malloc(sizeof(Broadcast));
    b = b_begin;
    b->next = nullptr;

    gen_add_parameter(p);
    int random_hour = generator.random_hour;

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

        int iter_count = generator.random_channel == p->id ? generator.random_minute : 60; // Если сгенерированный канал совпадает с текущим, то подставляем ограничение по минутам

        while (broadcasting_count < iter_count && p->ads != nullptr) {
            int rand_ads = ads_arr[random() % ads_count];

            // Если рандомный ролик из массива равен текущему и его приоритет меньше предыдущего и текущий id ролика не равен предыдущему
            if (rand_ads == p->ads->id && priority > p->ads->sequence && current_id != rand_ads) {
                appendBroadcast(&(b->broadcast_ads), p->ads->name, p->ads->duration, position_count, random_hour);

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
