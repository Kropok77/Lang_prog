#include <iostream>
#include <string>
#include <fstream>
#pragma GCC optimize("O3")//проверить
using namespace std;

struct knig{
    string name,author,date_read,mark;
    knig(string a1,string a2,string a3,string a4){
        name=a1;
        author=a2;
        date_read=a3;
        mark=a4;
    }
};
void start(){
    int a=0;
    while (a!=4) {
        cout << "Для добавления книги нажмите 1\n";
        cout << "Для показа списка книг нажмите 2\n";
        cout << "Для просмотра статистики нажмите 3\n";
        cout << "Для выхода нажмите 4\n";
        cin >> a;
        cout<<"\n";
    }
}
int main(){
    start();
}