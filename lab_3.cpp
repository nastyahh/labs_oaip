#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Student {
    string surname;
    int group_num;
    stack<int>* grades; 
};

struct Node {
    Student student;
    Node* left;
    Node* right;
};

Node* add_node(Node* root, Student student) { //функция добавления нового студента в дерево

    if (!root) {
        root = new Node();
        root->student = student;
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (student.surname < root->student.surname) {
        root->left = add_node(root->left, student);
    }
    else {
        root->right = add_node(root->right, student);
    }
    return root;
}

void search_by_surname(Node* root, string surname) {
    if (!root) {
        return;
    }
    if (root->student.surname == surname) {
        cout << "Surname: " << root->student.surname << endl;
        cout << "Group number: " << root->student.group_num << endl;
        cout << "Grades: ";
        stack<int> temp = *(root->student.grades); /*Для вывода оценок используется временный стек temp,
        в котором создается копия стека оценок студента из root->student.grades.
        Затем элементы стека выводятся на экран с помощью цикла while.*/
        while (!temp.empty()) {
            cout << temp.top() << " "; //top-верхний элемент стека
            temp.pop(); //pop-удаляет последний элемент
        }
        cout << endl;
    }
    else if (surname < root->student.surname) {
        search_by_surname(root->left, surname);
    }
    else {
        search_by_surname(root->right, surname);
    }
}

void search_by_group_num(Node* root, int group_num) {
    if (!root) {
        return;
    }
    if (root->student.group_num == group_num) {
        cout << "Surname: " << root->student.surname << endl;
        cout << "Group number: " << root->student.group_num << endl;
        cout << "Grades: ";
        stack<int> temp = *(root->student.grades);
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
    search_by_group_num(root->left, group_num);
    search_by_group_num(root->right, group_num);
}

void delete_students_with_bad_grades(Node*& root) {
    if (!root) {
        return;
    }
    delete_students_with_bad_grades(root->left);
    delete_students_with_bad_grades(root->right);
    int count = 0;
    stack<int> temp = *(root->student.grades);
    while (!temp.empty()) {
        if (temp.top() < 4) {
            ++count;
        }
        temp.pop();
    }
    if (count >= 3) {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            root = temp;
        }
        else {
            Node* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->student = temp->student;
            delete_students_with_bad_grades(root->right);
        }
    }
}

void edit_student_information(Node* root, string surname) {
    if (!root) {
        return;
    }
    if (root->student.surname == surname) {
        cout << "Enter new group number: ";
        cin >> root->student.group_num;
        cout << "Enter new grades: ";
        while (!root->student.grades->empty()) {
            root->student.grades->pop(); 
        }
        for (int i = 0; i < 5; ++i) {
            int grade;
            cin >> grade;
            root->student.grades->push(grade); //добавление новых оценок в стек
        }
    }
    else if (surname < root->student.surname) {
        edit_student_information(root->left, surname);
    }
    else {
        edit_student_information(root->right, surname);
    }
}

void print_students(Node* root) {
    if (!root) {
        return;
    }
    print_students(root->left);

    cout << "Surname: " << root->student.surname << endl;
    cout << "Group number: " << root->student.group_num << endl;
    cout << "Grades: ";
    stack<int> temp = *(root->student.grades);
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    print_students(root->right);
}

int main() {
    Node* root = nullptr;
    int choice;
    while (true) {
        cout << "1. Add student" << endl;
        cout << "2. Search by surname" << endl;
        cout << "3. Search by group number" << endl;
        cout << "4. Delete students with bad grades" << endl;
        cout << "5. Edit student information" << endl;
        cout << "6. Print all students" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        switch (choice) {
        case 1: {
            Student student;
            cout << "Enter student surname: ";
            cin >> student.surname;
            cout << "Enter group number: ";
            cin >> student.group_num;
            student.grades = new stack<int>(); // новый стек для оценок
            cout << "Enter grades: ";
            for (int i = 0; i < 5; ++i) {
                int grade;
                cin >> grade;
                student.grades->push(grade); 
            }
            root = add_node(root, student);
            break;
        }
        case 2: {
            string surname;
            cout << "Enter surname to search: ";
            cin >> surname;
            search_by_surname(root, surname);
            break;
        }
        case 3: {
            int group_num;
            cout << "Enter group number to search: ";
            cin >> group_num;
            search_by_group_num(root, group_num);
            break;
        }
        case 4: {
            delete_students_with_bad_grades(root);
            cout << "Students with marks below 4 were deleted." << endl;
            break;
        }
        case 5: {
            string surname;
            cout << "Enter surname to edit: ";
            cin >> surname;
            edit_student_information(root, surname);
            break;
        }
        case 6: {
            print_students(root);
            break;
        }
        case 0: {
            return 0;
        }
        default: {
            cout << "Invalid choice, please enter a valid choice" << endl;
            break;
        }
        }
    }
}


