#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<math.h>
using namespace std;
struct data
{
	string label,condition;
	float h;
	vector<vector<string>> table;
	vector<string> father;
};
typedef struct data DATA;

struct node
{	
	DATA data;
	vector<struct node*> pNext;
};
typedef struct node NODE;

struct tree
{
	NODE* root;
};
typedef struct tree TREE;

NODE* KhoiTaoNODE(DATA x)
{
	vector<struct node*> v;
	NODE* p = new NODE;
	p->data = x;
	p->pNext = v;
	return p;
}

int dem(vector<vector<string>> table, int index, string value, string result) {
	int dem = 0;
	for (int i = 0; i < table.size(); i++) {
		if (table[i][index] == value && table[i][4] == result)
			dem++;
	}
	return dem;
}

int dem(vector<vector<string>> table, string result) {
	int dem = 0;
	for (int i = 0; i < table.size(); i++) {
		if (table[i][4] == result)
			dem++;
	}
	return dem;
}

double tinhH(vector<int> v, int size) {
	double h=0;
	for (int i = 0; i < v.size(); i++) {
		cout << (double)v[i] / (double)size  << endl;
		h -= (double)v[i] / (double)size * ((log(v[i]) - log(size)) / log(2));
	}
	h = roundf(h*100)/100;
	return h;
}
bool check(vector<vector<string>> values, string value,int column) {
	for (int i = 0; i < values[column].size(); i++) {
		if (value == values[column][i])
			return false;
	}
	return true;
}

vector<vector<string>> getValue(vector<vector<string>> table) {
	vector<vector<string>> values;
	for (int i = 0; i < 5; i++) {
		vector<string> s;
		values.push_back(s);
		for (int j = 0; j < table.size(); j++) {
			if (check(values, table[j][i], i)) {
				values[i].push_back(table[j][i]);
			}
		}
	}
	return values;
}

void initTree(TREE &tree, vector<vector<string>> table, vector<vector<string>> values) {
	vector<int> v;
	for (int i = 0; i < values[4].size(); i++) {
		v.push_back(dem(table, values[4][i]));
	}
	cout<<tinhH(v, table.size());
}

int main() {
	ifstream in;
	in.open("data.txt", ios_base::in);
	vector<vector<string>> table;
	int i = 0;
	while (!in.eof())
	{
		vector<string> v;
		table.push_back(v);
		for (int j = 0; j < 5; j++) {
			string tmp;
			if (j < 4) {
				getline(in, tmp, ' ');
				table[i].push_back(tmp);
			}
			else
			{
				getline(in, tmp, '\n');
				table[i].push_back(tmp);
			}
		}
		i++;
	}
	in.close();
	vector<vector<string>> values = getValue(table);
	sort(values[4].begin(), values[4].end());
	for (int j = 0; j < values.size(); j++) {
		for (int k = 0; k < values[j].size(); k++) {
			cout << values[j][k] << " ";
		}
		cout << endl;
	}
	TREE tree;
	initTree(tree, table, values);
}