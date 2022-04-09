#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QBitmap>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setWindowFlags(Qt::FramelessWindowHint);   //设置无边框窗口
    form = new Form();
    QFile qss(":/img/style.qss");
    if(!qss.open(QFile::ReadOnly))
    {
       qDebug()<<"Error: void setStyleQss()"<<qss.errorString();
       return;
    }
    this->setStyleSheet(qss.readAll());
    qss.close();
    ui->leInput->installEventFilter(this);
    ui->leInput->setPlaceholderText("Enter here");
    ui->leOutput->setPlaceholderText("The result are presented here");
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush(Qt::white));
    //painter.setPen(Qt::transparent);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    //painter.drawRoundedRect(rect, 10, 10);

    //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, 15, 15);

        painter.drawPath(painterPath);
        //painterPath.drawPath(painterPath);
    }

    QWidget::paintEvent(event);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        last_mouse_position_ = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
            return;
    const QPoint position = pos() + event->globalPos() - last_mouse_position_; //the position of mainfrmae + (current_mouse_position - last_mouse_position)
    move(position.x(), position.y());
    last_mouse_position_ = event->globalPos();
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QKeyEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);    //转换事件类型
        QLineEdit *m_lineEdit = static_cast<QLineEdit *>(watched);
        if(keyEvent->key() == Qt::Key_Enter ||
           keyEvent->key() == Qt::Key_Return){
            ui->leOutput->setText(cal(m_lineEdit->text()));
            return true;    //返回true确认拦截该事件
        }
    }
    return false;       //返回false对此次事件不进行拦截
}

QString MainWindow::cal(QString old)
{
    InitAll();
    rslt.clear();
    s = old.toStdString();
    s = DelSpace(s);
    InitElem();
    for (register int i = 0; i < sum; i++) {
        if (!isdigit(s1[i][0]))
            d2[i] = 1;
        else {
            int x = 0, pos = 0;
            while (isdigit(s1[i][pos])) {
                x = (x << 1) + (x << 3) + int(char(s1[i][pos]) - '0');
                pos++;
            }
            d2[i] = x;
            string m = to_string(x);
            s1[i] = s1[i].substr(m.length(), s1[i].length() - m.length());
        }
    }
    ReadElem();
    ToMatr();
    solve();
    if (flag) {
        int cnt = 0;
        for (cnt = 0; cnt < sum; cnt++)
            if (d1[cnt] != d2[cnt]) break;
        if (cnt < sum) {
            qDebug() << "配平结果: ";
            QString tempStr1;
            QString tempStr;
            for (register int i = 0; i < sum; i++) {
                if (i == left_sum - 1) {
                    qDebug() << d1[i];
                    qDebug() << QString::fromStdString(s1[i]) << '=';
                    tempStr = QString::fromStdString(s1[i]);
                    if(d1[i] == 1)
                        tempStr1 = QString("%2 = ").arg(tempStr);
                    else
                        tempStr1 = QString("%1%2 = ").arg(d1[i]).arg(tempStr);
                }
                else if (i == sum - 1) {
                    qDebug() << d1[i];
                    qDebug() << QString::fromStdString(s1[i]);
                    tempStr = QString::fromStdString(s1[i]);
                    if(d1[i] == 1)
                        tempStr1 = QString("%2").arg(tempStr);
                    else
                        tempStr1 = QString("%1%2").arg(d1[i]).arg(tempStr);
                }
                else {
                    qDebug() << d1[i];
                    qDebug() << QString::fromStdString(s1[i]) << '+';
                    tempStr = QString::fromStdString(s1[i]);
                    if(d1[i] == 1)
                        tempStr1 = QString("%2 + ").arg(tempStr);
                    else
                        tempStr1 = QString("%1%2 + ").arg(d1[i]).arg(tempStr);
                }
                rslt += tempStr1;

            }
            qDebug() << rslt;
            return rslt;
        }
        else{
            qDebug() << "已配平!" << "endl";
            return QString("已配平!");
        }
    }
    else {
        qDebug() << "ERROR: 无法求解！" << endl;
        return QString("ERROR: 无法求解！");
    }
}
void MainWindow::InitElem() {
    for (register int i = 0; i < s.length(); i++)
        if (s[i] == '=') {
            iloc = i;
            break;
        }
    int head = 0, count = -1;
    for (register int i = 0; i < s.length(); i++) {
        if (s[i] == '+' && s[i + 1] != '>') {
            if (i < iloc)left_sum++;
            else right_sum++;
            count += 1;
            s1[count] = s.substr(head, i - head);
            head = i + 1;
        }
        if (i == iloc) {							//读到等号
            count += 1;
            s1[count] = s.substr(head, i - head);
            head = i + 1;

        }
        if (i == s.length() - 1) {					//最后一个
            count += 1;
            s1[count] = s.substr(head, i + 1 - head);
        }
    }
    left_sum++, right_sum++;
    sum = left_sum + right_sum;
    //上述将化学式分为左式和右式，并将每一个反应物和生成物切片。s1[0,left_sum-1]为左式，s1[left_sum,sum-1]为右式
}
inline int MainWindow::gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
void MainWindow::ReadElem() {									//读取所有的物质
    for (register int i = 0; i < iloc; i++) {	//因为原子守恒所以只读取左边的
        string temp = "";
        if (isupper(s[i])) {
            if (islower(s[i + 1])) {
                temp = string("") + char(s[i]) + char(s[i + 1]);
            }
            else
                temp = string("") + char(s[i]);
            elem[temp] = 0;
        }
        else if (s[i] == '<')
            elem["e"] = 0;
    }
}
inline int MainWindow::E_GetInt(string temp, int pos) {
    pos++; int x = 0;
    if (isdigit(temp[pos])) {
        while (isdigit(temp[pos])) {
            x = (x << 1) + (x << 3) + int(char(temp[pos]) - '0');
            pos++;
        }
    }
    else x = 1;
    if (temp[pos] == '+') return x;
    else return ~(x - 1);
}
int MainWindow::check(int i) {									//判断正负
    return i < left_sum ? 1 : -1;
}
string MainWindow::check1(int k) {								//判断系数是否为1
    return k == 1 ? "" : to_string(k);
}
inline int MainWindow::GetInt(string temp, int pos) {			 //读数
    pos++;
    if (islower(temp[pos]))pos++;					 //小写
    if (!isdigit(temp[pos]))return 1;				 //非数字就是1
    else {
        int x = 0;
        while (isdigit(temp[pos])) {				 //读元素后面的数字
            x = (x << 1) + (x << 3) + int(char(temp[pos]) - '0');
            pos++;
        }
        return x;
    }
}
void MainWindow::ToMatr() {
    for (register int i = 0; i < sum; i++) {		//遍历每一个反应(生成)物
        for (iter = elem.begin(); iter != elem.end(); iter++)
            iter->second = 0;						//初始化map
        string temp = s1[i];						//临时存贮
        int k1 = 1, k2 = 1;							//分别代表()后的数字，[]后的数字。
        for (register int j = 0; j < temp.length(); j++) {
            if (temp[j] == '(') {
                int m = j + 1;
                while (temp[m] != ')')m++;
                k1 = GetInt(temp, m);
            }
            if (temp[j] == ')')k1 = 1;
            if (temp[j] == '[') {
                int m = j + 1;
                while (temp[m] != ']')m++;
                k2 = GetInt(temp, m);
            }
            if (temp[j] == ']')k2 = 1;
            if (isupper(temp[j])) {
                if (islower(temp[j + 1])) {
                    string temp1 = string("") + char(temp[j]) + char(temp[j + 1]);
                    elem[temp1] += GetInt(temp, j) * k1 * k2 * check(i);
                }
                else {
                    string temp1 = string("") + char(temp[j]);
                    elem[temp1] += GetInt(temp, j) * k1 * k2 * check(i);
                }
            }
            else if (temp[j] == '<')
                elem["e"] = E_GetInt(temp, j) * check(i);
        }
        iter = elem.begin();
        int x = 0;
        while (iter != elem.end()) {
            ma[x][i] = iter->second;
            x++;
            iter++;
        }
    }
}
int MainWindow::determinant(int n) {
    int ans = 1, v = 1;
    for (int i = 0; i < n; i++)				//列
        for (int j = i + 1; j < n; j++) {	//行
            while (ma1[i][i]) {				//辗转相除消元
                int x = ma1[j][i] / ma1[i][i];
                for (int k = i; k < n; k++)			//转换成下三角行列式
                    ma1[j][k] -= x * ma1[i][k];
                swap(ma1[i], ma1[j]), v = -v;		//性质 4
            }
            swap(ma1[i], ma1[j]), v = -v;
        }
    for (int i = 0; i < n; i++)
        ans *= ma1[i][i];			//对角线求值
    return ans * v;
}
void MainWindow::solve() {
    flag = 1;
    int ele = elem.size();
    for (register int i = 0; i < ele; i++)	//默认最后一个生成物系数为1
        ma[i][sum - 1] *= -1;
    for (int i = 0; i < sum - 1; i++)				//列
        for (int j = i + 1; j < ele; j++) {	//行
            while (ma[i][i]) {
                int x = ma[j][i] / ma[i][i];
                for (int k = i; k < sum; k++)
                    ma[j][k] -= x * ma[i][k];
                swap(ma[i], ma[j]);
            }
            swap(ma[i], ma[j]);
        }
    if (sum - ele >= 2) {
        flag = 0;
        return;
    }
    else {
        ele = min(ele, sum - 1);
        for (register int i = 0; i < ele; i++)
            for (register int j = 0; j < ele; j++)
                ma1[i][j] = ma[i][j];
        D = determinant(ele);							//求行列式
        for (register int i = 0; i < ele; i++) {		//分别对sum-1个行列式求值
            for (register int j = 0; j < ele; j++) 	//行
                for (register int k = 0; k < ele; k++) {//列
                    if (k == i)	ma1[j][k] = ma[j][ele];
                    else ma1[j][k] = ma[j][k];
                }
            d1[i] = determinant(ele);
        }
        d1[sum - 1] = D;
        int Gcd = d1[0];
        for (register int i = 1; i < sum; i++)
            Gcd = gcd(Gcd, d1[i]);
        if (Gcd == 0) {
            flag = 0;
            return;
        }
        for (register int i = 0; i < sum; i++) {
            d1[i] /= Gcd;
            if (d1[i] <= 0) {
                flag = 0;
                return;
            }
        }
    }
}
void MainWindow::InitAll() {
    s = "";
    elem.clear();
    left_sum = right_sum = iloc = D = 0;
    for (register int i = 0; i < N; i++) {
        d1[i] = 0;
        d2[i] = 1;
        s1[i] = "";
        for (register int j = 0; j < N; j++)
            ma1[i][j] = ma[i][j] = 0;
    }
}
string MainWindow::DelSpace(string s) {
    string ans = "";
    for (register int i = 0; i < s.length(); i++) {
        if (char(s[i]) != ' ')
            ans.push_back(char(s[i]));
    }
    return ans;
}

void MainWindow::on_pushButton_3_clicked()
{
    form->close();
    close();

}


void MainWindow::on_pushButton_clicked()
{
    showMinimized();
}


void MainWindow::on_pushButton_2_clicked()
{
    form->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->leInput->clear();
    ui->leOutput->clear();
}

