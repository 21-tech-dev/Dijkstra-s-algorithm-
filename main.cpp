#include<fstream>
#include<iostream>
#include<vector>
#include"Header.h"

using namespace std;

//выбор действия
int Action(Graph& g, int choise)
{
	system("cls");
	switch (choise)
	{
	case 1:
	{
		g.WriteDot("Graph.dot");
		system("dot Graph.dot -Tpng > Graph.png");
		system("Graph.png");
		cout << "Success, Graph.png created!\n";
		break;
	}
	case 2:
	{
		cout << "Select start vertex (from 0 to " << g.Size() - 1 << "): ";
		int vertex;
		cin >> vertex;
		g.Dijkstra(vertex, "Ways.dot");
		system("dot Ways.dot -Tpng > Ways.png");
		system("Ways.png");
		cout << "Success, Ways.png created!\n";
		int c = getchar();
		c = getchar();
		break;
	}
	default:
		break;
	}
	return 0;
}

//выбор файля для построения графа
int ReadGraph(Graph& g)
{
	int choise = -1;
	char* str = new char[256];
	while (g.Size() == 0)
	{
		system("cls");
		cout << "Enter the path to the file (or press 0 to choose from the standard ones or exit): ";
		cin >> str;
		if (*str == '0')
		{
			system("cls");
			cout << "Please select:\n";
			cout << "1 : \"input.txt\"\n";
			cout << "2 : \"input1.txt\"\n";
			cout << "0 : Exit\n";
			cin >> choise;
			if (choise == 0)
			{
				delete[]str;
				return choise;
			}
			else if (choise == 1)
			{
				try
				{
					g.ReadGraph("input.txt");
				}
				catch (exception err)
				{
					cerr << err.what() << endl;
					int c = getchar();
					c = getchar();
				}
			}
			else
			{
				try
				{
					g.ReadGraph("input1.txt");
				}
				catch (exception err)
				{
					cerr << err.what() << endl;
					int c = getchar();
					c = getchar();
				}
			}
		}
		else
		{
			try
			{
				g.ReadGraph(str);
			}
			catch (exception err)
			{
				cerr << err.what() << endl;
				int c = getchar();
				c = getchar();
			}
		}
	}
	delete[]str;
	return choise;
}

//меню
int Menu()
{
	Graph g;
	int choise = ReadGraph(g);
	while (choise != 0)
	{
		system("cls");
		cout << "Choose an action:\n";
		cout << "1 : Draw a graph\n";
		cout << "2 : Apply Dijkstra's algorithm\n";
		cout << "0 : Exit\n";
		cin >> choise;
		if (choise == 0)
		{
			return 0;
		}
		Action(g, choise);
	}
	return 0;
}

int main()
{
	Menu();

	return 0;
}
