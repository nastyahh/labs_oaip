/* B10
���� ���������:�������,�������,����
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

//���-������� � ������������ ���������� ��� ����������� ������� �������� � ���-�������
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
    //�������� ��������� ������� �������� 
    setlocale(0, "ru");
    vector<Person> array(8);
    cout << "������� ���������� � �����:\n";
    for (int i = 0; i < array.size(); i++) {
        cout << "������� #" << i + 1 << ":\n";
        cout << "�������: ";
        cin >> array[i].lastName;
        cout << "�������: ";
        cin >> array[i].age;
        cout << "����: ";
        cin >> array[i].height;
        cout << "\n";
    }

    //�������� ���-�������
    const int tableSize = 10;
    vector<list<Person>> hashTable(tableSize);

    //���������� ���-�������
    for (int i = 0; i < array.size(); i++) {
        int index = hashFunction(array[i].height, tableSize);
        hashTable[index].push_back(array[i]);
    }


    //����� ��������� �������
    cout << "�������� ������:\n";
    for (int i = 0; i < array.size(); i++) {
        cout << "������� #" << i + 1 << ":\n";
        cout << "�������: " << array[i].lastName << "\n";
        cout << "�������: " << array[i].age << "\n";
        cout << "����: " << array[i].height << "\n\n";
    }
    cout << "\n";

    //����� ���-�������
    cout << "���-�������:\n";
    for (int i = 0; i < hashTable.size(); i++) {
        cout << "������ " << i << ":\n";
        for (const Person& person : hashTable[i]) {
            cout << "�������: " << person.lastName << "\n";
            cout << "�������: " << person.age << "\n";
            cout << "����: " << person.height << "\n\n";
        }
    }
    cout << "\n";

    //����� �������� �� ����� � ���-�������
    double searchHeight;
    cout << "������� ���� ��� ������: ";
    cin >> searchHeight;

    int searchIndex = hashFunction(searchHeight, tableSize);
    bool found = false;
    for (const Person& person : hashTable[searchIndex]) {
        if (person.height == searchHeight) {
            found = true;
            cout << "��������� �������:\n";
            cout << "�������: " << person.lastName << "\n";
            cout << "�������: " << person.age << "\n";
            cout << "����: " << person.height << "\n\n";
        }
    }

    if (!found) {
        cout << "������� � ��������� ������ �� ������ � ���-�������.\n";
    }

    return 0;
}