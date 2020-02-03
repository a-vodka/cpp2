#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

const int maxlen = 255;
#pragma pack(push, 1)
struct sworker {
    char fio[maxlen];
    int age;
};
#pragma pack(pop)

sworker arr[maxlen];
sworker arr_out[maxlen];
int worker_index = 0;

int menu();
void readFromFile(char* fileName);
void saveToFile(char* fileName);
void addNew();
void del();

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    while (1) {
        switch (menu()) {
        case 1:
            readFromFile("file.dat");
            break;
        case 2:
            saveToFile("file.dat");
            break;
        case 3:
            addNew();
            break;
        case 4:
            del();
            break;
        case 5:
            return 0;
        default:
            cout << "Невірний вибір" << endl;
        }
    }
}
int menu()
{
    cout << "\n";
    int ans;
    cout << "Оберіть\n";
    cout << "1-для зчитування з файла\n";
    cout << "2-для запису в файл\n";
    cout << "3-для додавання запису\n";
    cout << "4-для видалення запису\n";
    cout << "5-для виходу\n";
    cout << "\n";
    cout << "Ваш вибір  ";
    cin >> ans;
    return ans;
}
void saveToFile(char* fileName)
{
    ofstream f;
    f.open(fileName, ios::binary);
    f.write((char*)arr, sizeof(sworker) * worker_index);
    f.close();
    cout << "Введені дані збережено до файлу\n";
}
void readFromFile(char* fileName)
{
    ifstream f;
    f.open(fileName, ios::binary);
    if (!f) {
        cout << "Файлу не існує";
    }
    else {
        sworker worker;
        worker_index = 0;
        while (1) {
            f.read((char*)&worker, sizeof(worker));
            if (f.eof())
                break;
            arr_out[worker_index] = worker;
            worker_index++;
        }
        f.close();
        cout << "Дані зчитано з файлу\n";
        for (int i = 0; i < worker_index; i++) {
            cout << i + 1 << "\t" << arr_out[i].fio << "\t" << arr[i].age << endl;
        }
    }
}
void addNew()
{
    cout << "Додавання нового запису\n\n";
    cout << "Запис номер " << worker_index + 1 << "\n";
    cin.ignore();
    cout << "Введіть ПІБ  ";
    cin.getline(arr[worker_index].fio, maxlen);
    cout << "Введіть вік  ";
    cin >> arr[worker_index].age;
    worker_index++;
    cout << "\n";
    for (int i = 0; i < worker_index; i++) {
        cout << i + 1 << "\t" << arr[i].fio << "\t" << arr[i].age << endl;
    }
    cout << "\n";
}

void del()
{
    int d;
    cout << "Оберіть номер запису, який необхідно видалити ";
    cin >> d;
    for (int i = d - 1; i < worker_index; i++) {
        arr[i] = arr[i + 1];
        worker_index--;
    }
    cout << "\n";
    for (int i = 0; i < worker_index; i++) {
        cout << i + 1 << "\t" << arr[i].fio << "\t" << arr[i].age << endl;
    }
    cout << "\n";
}
