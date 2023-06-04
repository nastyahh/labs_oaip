/* A10
n=11, m=15, На основе связанных списков
*/
#include <iostream>
#include <cmath>
using namespace std;

struct tstk {
    int inf;
    tstk* a;
};

tstk** sv_create(int m) {
    tstk** H = new tstk * [m];
    for (int i = 0; i < m; i++)
        H[i] = nullptr;
    return H;
}

void sv_add(int inf, int m, tstk** H) {
    tstk* spt = new tstk;
    spt->inf = inf;
    int i = inf % m;

    if (H[i] == nullptr) {
        H[i] = spt;
        spt->a = nullptr;
    }
    else {
        spt->a = H[i];
        H[i] = spt;
    }
}

tstk* sv_search(int inf, int m, tstk** H) {
    int i = abs(inf % m);
    tstk* spt = H[i];
    while (spt != nullptr) {
        if (spt->inf == inf)
            return spt;
        spt = spt->a;
    }
    return nullptr;
}

void sv_delete(int m, tstk** H) {
    tstk* spt, * sp;
    for (int i = 0; i < m; i++) {
        cout << "H[" << i << "]";
        sp = H[i];
        while (sp != nullptr) {
            cout << sp->inf << " ";
            spt = sp;
            sp = sp->a;
            delete spt;
        }
        cout << endl;
    }
    delete[] H;
}

void realizB() {
    setlocale(0, "ru");
    int n = 11;
    int mas[] = { 63147 ,27660, 54661, 56807, 26160, 46959, 76029, 41624, 76591, 28447, 57753 };
    int m = 15;
    int i;

    tstk** H;
    H = sv_create(m);
    for (i = 0; i < n; i++)
        sv_add(mas[i], m, H);

    int ss;
    tstk* p;
    cout << "Введите искомый элемент" << endl;
    cin >> ss;
    while (ss != -1) {
        p = sv_search(ss, m, H);
        if (p == nullptr)
            cout << "Нет элемента" << endl;
        else
            cout << p->inf << endl;
        cout << "Введите искомый элемент" << endl;
        cin >> ss;
    }
    sv_delete(m, H);
}

int main() {
    realizB();
    return 0;
}
