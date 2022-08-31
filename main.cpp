#include <iostream>
#include <fstream>
//#include <cstring>
#include <vector>

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

Channels *head;

Channels *create_channels(const char *filename);

Channels *create_total_structure(Channels *p_begin, const char *filename);

char *find_splitter(char **line, int size);

void split(const char *str, char del);
//int l

#define CHANNEL_LIST "/home/ubuntu/CLionProjects/task5cpp/channels.txt" // адрес основного текста
#define ADS_LIST "/home/ubuntu/CLionProjects/task5cpp/ads.txt" // адрес дополнительного текста
#define TOTAL_LIST "/home/apheyhys/CLionProjects/task5cpp/total_list.txt" // адрес итогового текста


int main() {
    std::cout << "Hello, World!" << std::endl;

    Channels *channels_list = create_channels(CHANNEL_LIST);

    Channels *total_structure = create_total_structure(channels_list, ADS_LIST);



//
//    char largechars[] = "def1:def2:def3#abc1:abc2:abc3#ghi1:ghi2:ghi3";
//    vector<char*> v;
//    char* chars_array = strtok(largechars, "#");
//    while(chars_array)
//    {
//        v.push_back(chars_array);
//        chars_array = strtok(NULL, "#");
//    }
//
//    for(size_t n = 0; n < v.size(); ++n)
//    {
//        char* subchar_array = strtok(v[n], ":");
//        while (subchar_array) {
//            cout << subchar_array << '\n';
//            subchar_array = strtok(NULL, ":");
//        }
//    }


    return 0;
}

Channels *create_total_structure(Channels *p_begin, const char *filename) {
//    cout << p_begin[1].name << endl;
    // Открываем файл
    ifstream readfile(filename, ios::in);
    // Читаем все символы, включая пробелы
    readfile >> std::noskipws;

//    struct Channels* head = nullptr;


//    Channels *p_begin = nullptr;
//    Channels *a = nullptr;
    // Выделяем память
//    a_begin = (Channels *) malloc(sizeof(Channels)); // Выделяем память под первую ячейку структуры
//    p = p_begin;
//    p->name = 0;
//p_begin = head;
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
                        cout << id[i] << i << endl;
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
//                        ads_id[ads_id_count] = id.;
//                        id << ads_id[ads_id_count];
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

//                cout << "ID: " << convert_id << endl;
//                cout << "Name: " << name << endl;
//                cout << "Duration: " << convert_duration << endl;
//                cout << "Channels: " << channels_id_arr[0] << channels_id_arr[1] << channels_id_arr[2]
//                     << channels_id_arr[3] << endl;
//                cout << "Sequence: " << convert_sequence << endl;
                cout << id << endl;
                cout << "+++++++++++++" << endl;
//

                for (char t: channels_id_arr) {
                    while (p != nullptr) {
                        if (int(t) - 48 == p->id) {
                            cout << "Совпало" << endl;
                            struct Ad *temp, *a;
                            temp = (Ad *) malloc(sizeof(Ad)); // выделяем память
                            a = p->ads; // сохранение указателя на следующий узел
                            p->ads = temp; // предыдущий узел указывает на создаваемый
                            temp->id = convert_id; // сохранение поля данных добавляемого узла
                            temp->duration = convert_duration;
                            while(char s: name) {
                                temp->name += name[s];
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
        return p_begin;
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
//    p->name = 0;

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

//                cout << int(channel_id) - 48 << endl;
//                cout << name << endl;

                p->next = nullptr;
            } else break;
        }

        readfile.close();
        return p_begin;
    }
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


void split(const char *str, char del) {
    // declaring temp string to store the curr "word" upto del
//    string temp = "";
    char temp[30];

    for (int i = 0; i < 30; i++) {
        // If cur char is not del, then append it to the cur "word", otherwise
        // you have completed the word, print it, and start a new word.
        if (str[i] != del) {
            temp[i] = str[i];
        } else {
            cout << temp << " ";
//            temp = "";
        }
    }

    cout << temp;
}