/* B10
Поля структуры:фамилия,рост,возраст.
Ключевое поле:Рост.
n=8, M=10.
Схема хеширования: с произвольной адресацией.
*/
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Person {
    string lastName;
    int age;
    double height;
    Person() : lastName(""), age(0), height(0.0) {}

    Person(string _lastName, int _age, double _height) : lastName(_lastName), age(_age), height(_height) {}
};

//Хеш-функция с произвольной адресацией для определения индекса элемента в хеш-таблице
int hashFunction(double key, int tableSize) {
    int index = static_cast<int>(key) % tableSize;
    int step = 1;
    while (index < 0) {
        index = (index + step) % tableSize;
        step++;
    }
    return index;
}

int main() {
    //создание исходного массива структур  
    setlocale(0, "ru");
    vector<Person> array(8);
    cout << "Ââåäèòå èíôîðìàöèþ î ëþäÿõ:\n";
    for (int i = 0; i < array.size(); i++) {
        cout << "×åëîâåê #" << i + 1 << ":\n";
        cout << "Ôàìèëèÿ: ";
        cin >> array[i].lastName;
        cout << "Âîçðàñò: ";
        cin >> array[i].age;
        cout << "Ðîñò: ";
        cin >> array[i].height;
        cout << "\n";
    }

    //создание хеш-таблицы
    const int tableSize = 10;
    vector<list<Person>> hashTable(tableSize);

    //заполнение хеш-таблицы
    for (int i = 0; i < array.size(); i++) {
        int index = hashFunction(array[i].height, tableSize);
        hashTable[index].push_back(array[i]);
    }


    //вывод исходного массива
    cout << "Èñõîäíûé ìàññèâ:\n";
    for (int i = 0; i < array.size(); i++) {
        cout << "Человек #" << i + 1 << ":\n";
        cout << "Фамилия: " << array[i].lastName << "\n";
        cout << "Возраст: " << array[i].age << "\n";
        cout << "Рост: " << array[i].height << "\n\n";
    }
    cout << "\n";

    //вывод хеш-таблицы
    cout << "Исходный массив:\n";
    for (int i = 0; i < hashTable.size(); i++) {
       cout << "Индекс " << i << ":\n";
        for (const Person& person : hashTable[i]) {
            cout << "Фамилия: " << person.lastName << "\n";
            cout << "Возраст: " << person.age << "\n";
            cout << "Рост: " << person.height << "\n\n";
        }
    }
    cout << "\n";

    //поиск элемента по росту в хеш-таблице
    double searchHeight;
    cout << "Ââåäèòå ðîñò äëÿ ïîèñêà: ";
    cin >> searchHeight;

    int searchIndex = hashFunction(searchHeight, tableSize);
    bool found = false;
    for (const Person& person : hashTable[searchIndex]) {
        if (person.height == searchHeight) {
            found = true;
            cout << "Найденный элемент:\n";
            cout << "Фамилия: " << person.lastName << "\n";
            cout << "Возраст: " << person.age << "\n";
            cout << "Рост: " << person.height << "\n\n";
        }
    }

    if (!found) {
        cout << "Элемент с указанным ростом не найден в хеш-таблице.\n";
    }

    return 0;
}
