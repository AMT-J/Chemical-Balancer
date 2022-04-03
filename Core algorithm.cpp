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
int d1[N], d2[N];									// d1Ϊ����ϵ����d2Ϊԭ����ʽ��ϵ��
int ma[N][N], ma1[N][N];							//maΪ�������,ma1Ϊ���ؾ���
map<string, int> elem;								//������Ŷ�ӦԪ�ص�����
map<string, int>::iterator  iter;					//������
string s;
string s1[N];										//��������ÿһ����Ӧ���������
int left_sum = 0, right_sum = 0, iloc;				//�ֱ��¼��Ӧ�����������͵Ⱥŵ��±�
int sum, D;										//sum=left_sum+right_sum,DΪ����ʽ��ֵ
int flag = 1;										//1�����н�
inline int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
void ReadElem() {									//��ȡ���е�����
	for (register int i = 0; i < iloc; i++) {	//��Ϊԭ���غ�����ֻ��ȡ��ߵ�
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
int check(int i) {									//�ж�����
	return i < left_sum ? 1 : -1;
}
string check1(int k) {								//�ж�ϵ���Ƿ�Ϊ1
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
		if (i == iloc) {							//�����Ⱥ�
			count += 1;
			s1[count] = s.substr(head, i - head);
			head = i + 1;

		}
		if (i == s.length() - 1) {					//���һ��
			count += 1;
			s1[count] = s.substr(head, i + 1 - head);
		}
	}
	left_sum++, right_sum++;
	sum = left_sum + right_sum;
	//��������ѧʽ��Ϊ��ʽ����ʽ������ÿһ����Ӧ�����������Ƭ��s1[0,left_sum-1]Ϊ��ʽ��s1[left_sum,sum-1]Ϊ��ʽ
}
inline int GetInt(string temp, int pos) {			 //����
	pos++;
	if (islower(temp[pos]))pos++;					 //Сд
	if (!isdigit(temp[pos]))return 1;				 //�����־���1
	else {
		int x = 0;
		while (isdigit(temp[pos])) {				 //��Ԫ�غ��������
			x = (x << 1) + (x << 3) + int(char(temp[pos]) - '0');
			pos++;
		}
		return x;
	}
}
void ToMatr() {
	for (register int i = 0; i < sum; i++) {		//����ÿһ����Ӧ(����)��
		for (iter = elem.begin(); iter != elem.end(); iter++)
			iter->second = 0;						//��ʼ��map
		string temp = s1[i];						//��ʱ����
		int k1 = 1, k2 = 1;							//�ֱ����()������֣�[]������֡�
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
	for (int i = 0; i < n; i++)				//��
		for (int j = i + 1; j < n; j++) {	//��
			while (ma1[i][i]) {				//շת�����Ԫ
				int x = ma1[j][i] / ma1[i][i];
				for (int k = i; k < n; k++)			//ת��������������ʽ
					ma1[j][k] -= x * ma1[i][k];
				swap(ma1[i], ma1[j]), v = -v;		//���� 4
			}
			swap(ma1[i], ma1[j]), v = -v;
		}
	for (int i = 0; i < n; i++)
		ans *= ma1[i][i];			//�Խ�����ֵ
	return ans * v;
}
void solve() {
	flag = 1;
	int ele = elem.size();
	for (register int i = 0; i < ele; i++)	//Ĭ�����һ��������ϵ��Ϊ1
		ma[i][sum - 1] *= -1;
	for (int i = 0; i < sum - 1; i++)				//��
		for (int j = i + 1; j < ele; j++) {	//��
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
		D = determinant(ele);							//������ʽ
		for (register int i = 0; i < ele; i++) {		//�ֱ��sum-1������ʽ��ֵ
			for (register int j = 0; j < ele; j++) 	//��
				for (register int k = 0; k < ele; k++) {//��
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
	cout << "              *                  �򵥻�ѧ(����)����ʽ��ƽ,֧�ּ���Ƿ���ƽ                               *" << endl;
	cout << "              *       ���ִ�Сд����ʱ��֧�ּ�����������ԭ��Ӧ,�л�������ʡ�Ի�ѧ��,���ӷ�������<>       *" << endl;
	cout << "              ********************************************************************************************" << endl;
	while (1) {
		InitAll();
		cout << "��������ȷ�Ļ�ѧ����ʽ: " << endl;
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
				cout << "��ƽ���: ";
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
				cout << "����ƽ!" << endl;
		}
		else {
			SetConsoleTextAttribute(Get, FOREGROUND_INTENSITY | FOREGROUND_RED);
			cout << "ERROR: �޷���⣡" << endl;
			SetConsoleTextAttribute(Get, White);
		}
		cout << endl;
	}
	return 0;
}