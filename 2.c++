#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    double score;
    static double total;
    static int count;
    Student(string n, double s) {
        name = n;
        score = s;
        count++;
        total += s;
    }
    static void average() {
        if (count > 0) {
            total = total / count;
            cout << "平均分：" << total << endl;
        }
        else {
            cout << "没有学生记录" << endl;
        }
    }
};

double Student::total = 0;
int Student::count = 0;

int main() {
    string name;
    double score;
    char choice;
    do {
        cout << "请输入学生姓名和成绩：" << endl;
        cin >> name >> score;
        Student s(name, score);
        cout << "是否继续输入？(Y/N)" << endl;
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    cout << "学生个数：" << Student::count << endl;
    cout << "总分：" << Student::total << endl;
    Student::average();

    system("pause");
    return 0;
} 
