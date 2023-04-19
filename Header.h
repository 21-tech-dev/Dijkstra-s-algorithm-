#pragma once

class Graph
{
private:
	//количество вершин графа
	size_t size;
	//список смежности графа (с указанием стоимости)
	std::vector<std::vector<std::pair<int, int>>> cost_matrix;
	//создание .dot файла для описания всех путей (только после применения алгоритма Дейкстра)
	void WriteDot_p(std::vector<int>& p, int start_v, std::vector<int> d, const char* out_filename);
public:
	//конструткор графа
	Graph();
	//создание графа по файлу
	void ReadGraph(const char* filename);
	//возвращает количество вершин графа
	size_t Size();
	//возвращает рассояние между двумя вершинами графа
	int Distance(int v_from, int v_to);
	//оператор вывода
	friend std::ostream& operator << (std::ostream& out, const Graph& g);
	//создание .dot файлал для отрисовки графа с помощью graphviz
	void WriteDot(const char* out_filename);
	//применение алгоритма Дейкстра и построение кратчайших путей до всех вершин
	void Dijkstra(const int start_v, const char* out_filename);
};
