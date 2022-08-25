#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

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

Channels *create_channels(const char *filename);

char *find_splitter(char **line, int size);

void split(const char *str, char del);
//int l

#define CHANNEL_LIST "/home/ubuntu/CLionProjects/task5cpp/channels.txt" // адрес основного текста
#define ADS_LIST "/home/ubuntu/CLionProjects/task5cpp/ads.txt" // адрес дополнительного текста
#define TOTAL_LIST "/home/ubuntu/CLionProjects/task5cpp/total_list.txt" // адрес итогового текста


int main() {
    std::cout << "Hello, World!" << std::endl;

    Channels *channels_list = create_channels(CHANNEL_LIST);

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


//char * find_splitter(char *line, int size) {
//    char splitter_arr[size];
//
//    int tmp1 = 0;
//
//    int tmp2 = 0;
//
//    size_t i = 0;

//    for ( auto x : line) {
//
//        tmp1[i] = line[i];
//            cout << x << endl;
//
//        }
//        if (line[i]==';') {
//            cout << i << endl;
//
//        }
//        ++i;
//    }

//}

Channels *create_channels(const char *filename) {
    // Открываем файл
    ifstream readfile(filename, ios::in);
    // Читаем все символы, включая пробелы
    readfile >> std::noskipws;

//    List *p_begin = nullptr;
//    List *p = nullptr;
//    // Выделяем память
//    p_begin = (List *) malloc(sizeof(List)); // Выделяем память под первую ячейку структуры
//    p = p_begin;
//    p->next = nullptr;
//    p->count = 0;

    vector<string> Result_data_vector_1; //Сюда записываем считанные строки из файла до &
    vector<string> Result_data_vector_2; //Сюда записываем считанные строки из файла после &

    string Line_string;
    int status = 0;

    char id[30]{};



    const char *end_line = ";";
    const char *sep_line = ":";

    char first[30];

    int count = 0;

    if (!readfile) {
        cout << "Ошибка открытия файла" << endl;
        return reinterpret_cast<Channels *>(-1);
    } else {
        while (true) {
            readfile.getline(id, 30);
            if (!readfile.eof()) {
                char tmp1[30]{};
                char tmp2[30]{};

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
                    if (k>limit1&&k<limit2) {
                        name[name_count] = id[k];
                        name_count++;
                    }
                }

                cout << int(channel_id)-48 << endl;
                cout << name << endl;


            } else break;
        }


        readfile.close();
//        return arr;


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