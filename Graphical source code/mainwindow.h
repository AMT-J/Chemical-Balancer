#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <string>
#include <QPoint>
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace std;
QT_END_NAMESPACE
#define N 100


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    int d1[N], d2[N];									// d1为最终系数，d2为原方程式的系数
    int ma[N][N], ma1[N][N];							//ma为增广矩阵,ma1为判重矩阵
    map<string, int> elem;								//用来存放对应元素的数量
    map<string, int>::iterator  iter;					//迭代器
    string s;
    string s1[N];										//用来储存每一个反应物和生成物
    int left_sum = 0, right_sum = 0, iloc;				//分别记录反应物、生成物种类和等号的下标
    int sum, D;										//sum=left_sum+right_sum,D为行列式的值
    int flag = 1;
    ~MainWindow();

    int gcd(int a, int b);
    void ReadElem();
    int E_GetInt(string temp, int pos);
    int check(int i);
    string check1(int k);
    int GetInt(string temp, int pos);
    void ToMatr();
    int determinant(int n);
    void solve();
    void InitAll();
    string DelSpace(string s);
    QString rslt;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint last_mouse_position_;
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *watched, QEvent *event);
    QString cal(QString old);
    void InitElem();
    Form *form;


};
#endif // MAINWINDOW_H
