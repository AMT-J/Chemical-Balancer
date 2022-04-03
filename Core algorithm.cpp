/*
* Author:AMT
* Date:2022.1.28
*/
#include<bits/stdc++.h>
#include<windows.h>
#define Get GetStdHandle(STD_OUTPUT_HANDLE)
#define White  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
using namespace std;
const int N = 100;
int d1[N], d2[N];									// d1为最终系数，d2为原方程式的系数
int ma[N][N], ma1[N][N];							//ma为增广矩阵,ma1为判重矩阵
map<string, int> elem;								//用来存放对应元素的数量
map<string, int>::iterator  iter;					//迭代器
string s;
string s1[N];										//用来储存每一个反应物和生成物
int left_sum = 0, right_sum = 0, iloc;				//分别记录反应物、生成物种类和等号的下标
int sum, D;										//sum=left_sum+right_sum,D为行列式的值
int flag = 1;										//1代表有解
inline int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
void ReadElem() {									//读取所有的物质
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
inline int E_GetInt(string temp, int pos) {
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
int check(int i) {									//判断正负
	return i < left_sum ? 1 : -1;
}
string check1(int k) {								//判断系数是否为1
	return k == 1 ? "" : to_string(k);
}
void InitElem() {
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
inline int GetInt(string temp, int pos) {			 //读数
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
void ToMatr() {
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
int determinant(int n) {
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
void solve() {
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
void InitAll() {
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
void print(int i) {
	SetConsoleTextAttribute(Get, FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << check1(d1[i]);
	SetConsoleTextAttribute(Get, White);
}
string DelSpace(string s) {
	string ans = "";
	for (register int i = 0; i < s.length(); i++) {
		if (char(s[i]) != ' ')
			ans.push_back(char(s[i]));
	}
	return ans;
}
int main() {
	system("mode con cols=120 lines=30");
	ios::sync_with_stdio(false);
	cin.tie(0);
	system("color 0F");
	cout << "              ********************************************************************************************" << endl;
	cout << "              *                  简单化学(离子)方程式配平,支持检测是否配平                               *" << endl;
	cout << "              *       区分大小写，暂时不支持极少数氧化还原反应,有机方程请省略化学键,离子方程请用<>       *" << endl;
	cout << "              ********************************************************************************************" << endl;
	while (1) {
		InitAll();
		cout << "请输入正确的化学方程式: " << endl;
		getline(cin, s);
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
				cout << "配平结果: ";
				for (register int i = 0; i < sum; i++) {
					if (i == left_sum - 1) {
						print(i);
						cout << s1[i] << '=';
					}
					else if (i == sum - 1) {
						print(i);
						cout << s1[i];
					}
					else {
						print(i);
						cout << s1[i] << '+';
					}
				}
				cout << endl;
			}
			else
				cout << "已配平!" << endl;
		}
		else {
			SetConsoleTextAttribute(Get, FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "ERROR: 无法求解！" << endl;
			SetConsoleTextAttribute(Get, White);
		}
		cout << endl;
	}
	return 0;
}