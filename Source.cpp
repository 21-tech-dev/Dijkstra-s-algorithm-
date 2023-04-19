#include<fstream>
#include<iostream>
#include<vector>
#include<set>
#include"Header.h"

using namespace std;

//конструткор графа
Graph::Graph()
{
	size = 0;
}

//создание графа по файлу
void Graph::ReadGraph(const char* filename)
{
	ifstream fin(filename);
	if (!fin.is_open())
	{
		throw runtime_error("file don't found");
	}
	fin >> size;
	vector<pair<int, int>> tmp;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			int d;
			fin >> d;
			if (d != 0)
				tmp.push_back(make_pair(d, j));
		}
		cost_matrix.push_back(tmp);
		tmp.clear();
	}
}

//возвращает количество вершин графа
size_t Graph::Size()
{
	return size;
}

//возвращает рассояние между двумя вершинами графа
int Graph::Distance(int v_from, int v_to)
{
	for (auto it : cost_matrix[v_from])
	{
		if (it.second == v_to)
		{
			return it.first;
		}
	}
	return -1;
}

//оператор вывода
ostream& operator << (ostream& out, const Graph& g)
{
	for (size_t i = 0; i < g.size; i++)
	{
		out << "["<< i << "]" << " : ";
		for (const auto& it : g.cost_matrix[i])
			out << "\t" << it.second << "(" << it.first << ")";
		out << endl;
	}
	return out;
}

//создание .dot файлал для отрисовки графа с помощью graphviz
void Graph::WriteDot(const char* out_filename)
{
	ofstream out(out_filename);
	set<pair<int, int>> p;
	out << "graph {\n";
	for (size_t v = 0; v < cost_matrix.size(); ++v)
	{
		out << "   " << v << ";\n";
		for (auto u : cost_matrix[v])
		{
			if (p.find(make_pair(v, u.second)) == p.end() && p.find(make_pair(u.second, v)) == p.end())
			{
				out << "   " << v << " -- " << u.second << " [label=" << u.first << "]" << ";\n";
				p.insert(make_pair(v, u.second));
			}
		}
	}
	out << "}\n";
}

//применение алгоритма Дейкстра и построение кратчайших путей до всех вершин
void Graph::Dijkstra(const int start_v, const char* out_filename)
{
	vector<int> d(size, INT_MAX), p(size);
	d[start_v] = 0;
	set<pair<int, int>> tops;
	tops.insert(make_pair(d[start_v], start_v));
	while (!tops.empty())
	{
		int current_v = tops.begin()->second;
		tops.erase(tops.begin());
		for (auto it : cost_matrix[current_v])
		{
			if (d[current_v] + it.first < d[it.second])
			{
				tops.erase(make_pair(d[it.second], it.second));
				d[it.second] = d[current_v] + it.first;
				p[it.second] = current_v;
				tops.insert(make_pair(d[it.second], it.second));
			}
		}
	}
	for (size_t i = 0; i < d.size(); ++i)
	{
		cout << "Shortest distance from " << start_v << " to " << i << " = " << d[i] << "\n";
	}
	cout << endl;
	WriteDot_p(p, start_v, d, out_filename);
}

//создание .dot файла для описания всех путей (только после применения алгоритма Дейкстра)
void Graph::WriteDot_p(vector<int>& p, int start_v, vector<int> d, const char* out_filename)
{
	ofstream out(out_filename);
	out << "graph \"\" {\n";
	out << "label=\"Ways\"\n";
	out << "\n\n";
	for (size_t i = 0; i < p.size(); ++i)
	{
		vector<int> way;
		out << "subgraph cluster" << i << " {\n";
		out << "   label=\"" << "Shortest distance from " << start_v << " to " << i << " = " << d[i] << "\"\n";
		int x = i;
		while (x != start_v)
		{
			way.push_back(x);
			x = p[x];
		}
		way.push_back(x);
		for (int j = way.size() - 1; j >= 0; --j)
		{
			out << "   " << (char)('a' + i) << way[j] << " [label=" << way[j] << "] ;\n";
			if (j != 0)
				out << "   " << (char)('a' + i) << way[j] << " -- " << (char)('a' + i) << way[j - 1] << " [label=" << Distance(way[j], way[j - 1]) << "]" << ";\n";
		}
		out << "}\n";
	}
	out << "}";
}
