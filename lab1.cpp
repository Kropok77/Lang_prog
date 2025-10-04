//ошибки плохо работает система обработки ошибки на ввод даты
//уходит в бесконечный цикд


#include "iostream"
#include "string"
#include "fstream"
#include "vector"
#include "sstream"


//#define DEBUG
using namespace std;

vector<pair<string, int>> nameknmark;


struct knig {
    string name, author;
    int mark = 0;
    int date = 0;

    knig(string a1, string a2, int a3, int a4) {
        name = a1;
        author = a2;
        date = a3;
        mark = a4;
    }
};

void writefl(string n, string a, int d, int m) {
    ofstream out("books.txt", ios::app);
    if (out.is_open()) {
        out << n << " " << a << " " << d << " " << m << "\n";
    }
    out.close();
}

void readf(string namef) {
    string line;
    string n,a;
    int m,d;
    ifstream in(namef);
    if (in.is_open()) {
        while (getline(in, line)) {
            stringstream ss(line);
            ss>>n>>a>>d>>m;
            nameknmark.push_back({n,m});
            cout << n<<" "<<m << endl;
        }
    }
}

void func(int key) {
    knig bobrik("", "", 0, 0);
    switch (key) {
        case 1: {

            metk1:
            cout << "Название (до 100 символов)\n";

            cin >> bobrik.name;

            if ((bobrik.name).length() >= 100) {
                cout << "Неверный формат" << endl;
                goto metk1;
            }
            metk2:
            cout << "Автор (до 50 символов)\n";

            cin >> bobrik.author;

            if ((bobrik.author).length() >= 50) {
                cout << "Неверный формат" << endl;
                goto metk2;
            }


            metk3:
            cout << "Год прочтения" << endl;
            string s;
            cin >> s;
            try {
                bobrik.date = stoi(s);
            } catch (const std::invalid_argument &e) {
                cout << "Неверный формат" << endl;
                goto metk3;
            }
            if (bobrik.date >= 2026 || bobrik.date <= 0) {
                cout << "Неверный формат" << endl;
                goto metk3;
            }
            metk4:
            cout << "Оценка по 10 бальной шкале\n";
            string s1;
            cin >> s1;
            try {
                bobrik.mark = stoi(s1);

            } catch (const std::invalid_argument &e) {
                cout << "Неверный формат" << endl;
                goto metk4;
            }

            if (bobrik.mark > 10 || bobrik.mark < 0) {
                cout << "Неверный формат" << endl;
                goto metk4;
            }
#ifdef DEBUG
            cout<<bobrik.name<<"\n"<<bobrik.author<<"\n"<<bobrik.date<<"\n"<<bobrik.mark;
#endif
            writefl(bobrik.name, bobrik.author, bobrik.date, bobrik.mark);
            break;
        }
        case 2: {
            readf("books.txt");
            break;
        }
    }


}

void start() {
    int a = 0;

    while (a != 4) {
        metk5:
        cout << "Для добавления книги нажмите 1\n";
        cout << "Для показа списка книг нажмите 2\n";
        cout << "Для просмотра статистики нажмите 3\n";
        cout << "Для выхода нажмите 4\n";
        string s2;
        cin >> s2;

        try {
            a = stoi(s2);

        } catch (const std::invalid_argument &e) {
            cout << "Неверный формат" << endl;
            goto metk5;
        }
        func(a);
        cout << "\n";
    }
}

int main() {
    start();
}