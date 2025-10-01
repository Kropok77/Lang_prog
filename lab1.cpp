//ошибки плохо работает система обработки ошибки на ввод даты
//уходит в бесконечный цикд


#include <iostream>
#include <string>
#include <fstream>
#include "limits"
#pragma GCC optimize("O3")//проверить
using namespace std;

struct knig{
    string name,author;
    int mark=0;
    int date=0;
    knig(string a1,string a2,int a3,int a4){
        name=a1;
        author=a2;
        date=a3;
        mark=a4;
    }
};
void func(int key){
    switch (key) {
        case 1:
            knig bobrik("","",0,0);
            metk1:
            cout<<"Название (до 100 символов)\n";

            cin>>bobrik.name;

            if ((bobrik.name).length()>=100){
                cout<<"Неверный формат\n";
                goto metk1;
            }
            metk2:
            cout<<"Автор (до 50 символов)\n";

            cin>>bobrik.author;

            if ((bobrik.author).length()>=50){
                cout<<"Неверный формат\n";
                goto metk2;
            }
            metk3:
            cout<<"Год прочтения\n";
            int k;

            cin>>bobrik.date;

            if (bobrik.date>=2026 || bobrik.date<=0){
                cout<<"Неверный формат\n";

                goto metk3;
            }
            metk4:
            cout<<"Оценка по 10 бальной шкале\n";

            cin>>bobrik.mark;

            if (bobrik.mark>10 || bobrik.mark<0){
                cout<<"Неверный формат\n";goto metk4;
            }
            cout<<bobrik.name<<"\n"<<bobrik.author<<"\n"<<bobrik.date<<"\n"<<bobrik.mark;
            break;
    }
}
void start(){
    int a=0;
    while (a!=4) {
        cout << "Для добавления книги нажмите 1\n";
        cout << "Для показа списка книг нажмите 2\n";
        cout << "Для просмотра статистики нажмите 3\n";
        cout << "Для выхода нажмите 4\n";
        cin >> a;
        func(a);
        cout<<"\n";
    }
}

int main(){
    start();
}