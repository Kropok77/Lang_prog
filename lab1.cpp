//ошибки плохо работает система обработки ошибки на ввод даты
//уходит в бесконечный цикд


#include "iostream"
#include "string"
#include "fstream"
#include "vector"
#include "sstream"
#include "algorithm"
#include "cstdlib"
#include "limits"

//#define DEBUG
using namespace std;

vector<pair<int, string>> nameknmark;//массив с парами типа (оценка книги; название книги)


struct knig {//структура отвечающая за класс книг которая принимает на вход имя книги, автора, дату написания, оценку
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



string rep(string h,char from,char to){
    string ot="";
    for (auto x: h){
        if (x==from){
            ot.push_back(to);

        }else{
            ot.push_back(x);
        }
    }
    return ot;
}

//структура отвечающая за запись параметров структуры knig в файл

void writefl(string n, string a, int d, int m) {
    ofstream out("books.txt", ios::app);
    if (out.is_open()) {
        out << n << " " << a << " " << d << " " << m << "\n";
    }
    out.close();
}

void cl(){
    cin.ignore();
    cin.get();
    system("clear");
}


//чтение праарметров каждой из книги в файл

int readf(string namef, int k) {
    string line;
    string n, a;
    int m, d;
    ifstream in(namef);

    if (in.is_open()) {
        if (k==1){
            cout<< "Название Автор Дата прочтения оценка"<<endl;
            cout<< "===================================="<<endl;
        }

        while (getline(in, line)) {
            stringstream ss(line);
            ss >> n >> a >> d >> m;
            if (k == 1) {
                cout << rep(n,'_',' ') <<"  "<<rep(a,'_',' ')<< "   " <<d<<"    "<< m << endl;
            }
            nameknmark.push_back({m, rep(n,'_',' ')});

        }
    }else{
        cout<<"Добавьте книги!"<<endl<<endl;
        cout<<"Нажмите Enter для продолжения"<<endl;
        cl();
        return 1;
    }
    if (k==1){
        cout<<endl;
        cout<<"Нажмите Enter для продолжения";
        cl();
    }
    in.close();
    return 0;
}


//функция сравнения для sort
bool compare(pair<int, string> a, pair<int, string> b) {
    return a.first > b.first;
}


//получение статистики из книг

void getstat() {
    int j=readf("books.txt",0);
    if (j==1){
        return;
    }
    cout << "Количество прочитанных книг: " << nameknmark.size() << endl;
    sort(nameknmark.begin(), nameknmark.end(), compare);
    float k = 0;
    int ch = 0;
    for (auto x: nameknmark) {
        string n;
        k += x.first;
        ch += 1;
    }
    cout << "Средняя оценка: " << k / static_cast<float>(ch) << endl;
    int sch = 0;
    cout << "Топ произведений: " << endl;
    do {

        cout << nameknmark[sch].second << " " << nameknmark[sch].first << endl;
        sch++;
    } while (nameknmark[sch].first == nameknmark[sch - 1].first && sch < ch);
    cout<<endl;
    cout<<"Нажмите Enter для продолжения";
    cl();
}


//обработка ввод с клавиатуры для проги

void func(int key) {
    nameknmark.resize(0);
    knig bobrik("", "", 0, 0);
    switch (key) {
        case 1: {

            metk1:
            cout << "Название (до 100 символов)\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin,bobrik.name);
            bobrik.name=rep(bobrik.name,' ','_');
            if ((bobrik.name).length() >= 100) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();
                goto metk1;
            }
            metk2:
            cout << "Автор (до 50 символов)\n";
            getline(cin,bobrik.author);
            bobrik.author=rep(bobrik.author,' ','_');

            if ((bobrik.author).length() >= 50) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();
                goto metk2;
            }


            metk3:
            cout << "Год прочтения" << endl;
            string s;
            cin >> s;
            try {
                bobrik.date = stoi(s);
            } catch (const std::invalid_argument &e) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();
                goto metk3;
            }
            if (bobrik.date >= 2026 || bobrik.date <= 0) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();
                goto metk3;
            }
            metk4:
            cout << "Оценка по 10 бальной шкале\n";
            string s1;
            cin >> s1;
            try {
                bobrik.mark = stoi(s1);

            } catch (const std::invalid_argument &e) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();
                goto metk4;
            }

            if (bobrik.mark > 10 || bobrik.mark < 0) {
                system("clear");
                cout << "Неверный формат" << endl;
                cl();

                goto metk4;
            }
#ifdef DEBUG
            cout<<bobrik.name<<"\n"<<bobrik.author<<"\n"<<bobrik.date<<"\n"<<bobrik.mark;
#endif
            writefl(bobrik.name, bobrik.author, bobrik.date, bobrik.mark);
            break;
        }
        case 2: {
            readf("books.txt",1);
            break;
        }
        case 3: {
            getstat();
            break;
        }
    }


}

void start() {
    int a = 0;
    system("clear");
    while (a != 4) {
        metk5:
        cout << "=============########===============" << endl;
        cout << "Для добавления книги нажмите 1\n";
        cout << "Для показа списка книг нажмите 2\n";
        cout << "Для просмотра статистики нажмите 3\n";
        cout << "Для выхода нажмите 4\n";
        string s2;
        cin >> s2;
        system("clear");
        try {
            a = stoi(s2);

        } catch (const std::invalid_argument &e) {
            cout << "Неверный формат" << endl;
            goto metk5;
        }
        if (!(a > 0 && a < 5)) {
            goto metk5;
        }
        func(a);
        cout << "\n";
    }
}

int main() {
    cout<<endl;
    start();
}