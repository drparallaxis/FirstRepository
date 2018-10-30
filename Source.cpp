//By Alan Kokaev project "Thir" for lab of graphs
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

class Graph
{
public:
	struct Top 
	{
		int turn; //черёд/id строки
		double id, x, y, z;

	};
	struct Edge
	{
		int id;
		double* et1; //информация о первой вершине ребра
		double* et2; //информация о второй вершине ребра
		double itsedge; //длина ребра 
		Edge()
		{
			et1 = new double[3];
			et2 = new double[3];
			for (int i = 0; i < 3; i++)
				et1[i] = et2[i] = 0.0;

			itsedge = 0.0;
		}
		~Edge() { delete[] et1; delete[] et2; }
	};
	Top* tops;
	string path;
	int NumberOfTops;
	Edge* myEdge;
	int countOfEdge; //количество рёбер
	Graph() {}

	Graph(string& pth, int nt) 
	{ 
		path = pth;
		NumberOfTops = nt;

		tops = new Top[NumberOfTops];
		for (int i = 0; i < NumberOfTops; i++)
		{
			tops[i].turn = i;
			tops[i].id = tops[i].x = tops[i].y = tops[i].z = 0.0;
		}

		countOfEdge = NumberOfTops-1;
		for (int i = 0; i < NumberOfTops-2; i++)
			countOfEdge += (NumberOfTops-2) - i;

		myEdge = new Edge[countOfEdge];
		for (int i = 0; i < countOfEdge; i++)
		{
			myEdge[i].id = 0;
			myEdge[i].itsedge = 0.0;
		}

	}

	int getCountOfEdge() { return countOfEdge; }

	int counter(string path, int status)
	{
		int CountColumns = 0, count = 0;
		string str;
		ifstream cinput;

		cinput.open(path);

		while (!cinput.eof())
		{
			if (status == 1)
				if ((count % 4) == 0)
					CountColumns++;
			cinput >> str;
			count++;
		}

		cinput.close();

		if (status == 1)
			return CountColumns;
		else return count;
	}
	
	~Graph() { delete[] tops; delete[] myEdge; }
};

class Solution : public Graph
{
	string path1, path2;
	int NumberOfElements1, NumberOfElements2;
	int NumberOfTops1, NumberOfTops2;
public:
	//virtual int Solution::getGraph() override;
	Solution()
	{
		NumberOfElements1 = NumberOfElements2 = NumberOfTops1 = NumberOfTops2 = 0;

		path1 = "C:\\Users\\miste\\Desktop\\files\\test\\FirstFile.gjf";
		path2 = "C:\\Users\\miste\\Desktop\\files\\test\\SecondFile.gjf";

		NumberOfElements1 = counter(path1, 0);
		NumberOfElements2 = counter(path2, 0);
		NumberOfTops1 = counter(path1, 1);
		NumberOfTops2 = counter(path2, 1);
	}
	
	void InitGraph()
	{
		Graph G1(path1, NumberOfTops1);
		Graph G2(path2, NumberOfTops2);

		InitOfSubgraph(G1, G2);

		int counter1 = G1.getCountOfEdge();
		int counter2 = G2.getCountOfEdge();

		int not1 = NumberOfTops1 - 1;
		int not2 = NumberOfTops2 - 1;

		int LocalCountOfTops = 0; //для счётчика вершин
		int LocalCountOfSecondCounter = 0; //для счётчика вложенного цикла 

		int accelerator = 0;

		for (int i = counter1; i>0; i-=not1)
		{
			for (int j = LocalCountOfSecondCounter; j <= LocalCountOfSecondCounter+not1; j++)
			{
				cout << j << ",   ";
				//G1.myEdge[j].id = j;
				//G1.myEdge[j].et1[0] = G1.tops[LocalCountOfTops].x;
				//G1.myEdge[j].et1[1] = G1.tops[LocalCountOfTops].y;
				//G1.myEdge[j].et1[2] = G1.tops[LocalCountOfTops].z;
				///*if (j == (LocalCountOfSecondCounter + not1) && !((LocalCountOfTops+1) > (NumberOfTops1-1)))
				//{
				//	accelerator = LocalCountOfTops+1;
				//	for (int k = LocalCountOfSecondCounter; k <= LocalCountOfSecondCounter + not1; k++)
				//	{
				//		G1.myEdge[k].et2[0] = G1.tops[accelerator].x;
				//		G1.myEdge[k].et2[1] = G1.tops[accelerator].y;
				//		G1.myEdge[k].et2[2] = G1.tops[accelerator].z;
				//		accelerator++;
				//	}
				//}*/
			}
			not1--;
			LocalCountOfSecondCounter += not1;
			LocalCountOfTops++;
		}

		for (int i = 0; i < counter1; i++)
		{
			//cout << G1.myEdge[i].id << ",     ";
		}
	}


	void simple(Graph& Sgraph, int NumberOfElements, int status)
	{
		double* buffer = new double[NumberOfElements];
		ifstream fin;
		if(status == 1)
			fin.open(path1);
		if (status == 2)
			fin.open(path2);

		int cntr1, cntr2, cntr3, cntr4;
		cntr1 = cntr2 = cntr3 = cntr4 = 0;

		if (!fin.is_open()) { "Warning!\n"; }
		else
		{
			for (int i = 0; i < NumberOfElements1; i++)
			{
				fin >> buffer[i];
				if ((i % 4) == 0)
				{
					Sgraph.tops[cntr1].id = buffer[i];
					cntr1++;
				}
				if (((i - 1) % 4) == 0 && i != 0 || i == 1)
				{
					Sgraph.tops[cntr2].x = buffer[i];
					cntr2++;
				}
				if (((i - 2) % 4) == 0 && i != 0 && i != 1 || i == 2)
				{
					Sgraph.tops[cntr3].y = buffer[i];
					cntr3++;
				}
				if (((i - 3) % 4) == 0 && i > 2 || i == 3)
				{
					Sgraph.tops[cntr4].z = buffer[i];
					cntr4++;
				}
			}
		}
		fin.close();
		delete[] buffer;
	}

	void InitOfSubgraph(Graph& Sgraph1, Graph& Sgraph2)
	{
		simple(Sgraph1, NumberOfElements1, 1);
		simple(Sgraph2, NumberOfElements2, 2);
	}

	void ffg()
	{
		Graph G1(path1, NumberOfTops1);
		Graph G2(path2, NumberOfTops2);

		int y = NumberOfTops1;
		int counter = 0;
		for (int i = G1.getCountOfEdge(); i > 0; i -= y)
		{
			cout << i << ",  ";
			y--;
			counter++;
		}
		cout << "\ncounter = " << counter;

		cout << "\n\nКол-во элементов в 1-ом графе: " << NumberOfElements1 \
			<< ",  Кол-во элементов во 2-ом графе: " << NumberOfElements2 \
			<< "\nКол-во вершин в 1-ом графе: " << NumberOfTops1 << ",  Кол-во вершин во 2-ом графе: " \
			<< NumberOfTops2 << "\n\nКол-во рёбер в 1-ом графе: " << G1.getCountOfEdge() \
			<< ",  Кол-во ребёр во 2-ом графе: " << G2.getCountOfEdge();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Solution A, B;

	A.InitGraph();
	A.ffg();

	_getch();
}

//int Solution::getGraph()
//{
//	return 0;
//}


/*et = new double*[3];
for (int i = 0; i < 3; i++)
et[i] = new double[count-2];*/
/*for (int i = 0; i < 3; i++)
delete[] et[i];
delete[] et;*/
//for (int i = 0; i < NumberOfTops1 - 1; i++)
//{

	/*if ((i % 4) == 0)
	cout << "\n\n";
	myEdge[i].et1[0] = G1.tops[i].x;
	myEdge[i].et1[1] = G1.tops[i].y;
	myEdge[i].et1[2] = G1.tops[i].z;

	myEdge[i].et2[0] = G1.tops[i + 1].x;
	myEdge[i].et2[1] = G1.tops[i + 1].y;
	myEdge[i].et2[2] = G1.tops[i + 1].z;*/
	//находим длину ребра
	/*myEdge[i].itsedge = sqrt(pow(myEdge[i].et2[0]-myEdge[i].et1[0],2)+ pow(myEdge[i].et2[1] - myEdge[i].et1[1], 2)+ pow(myEdge[i].et2[2] - myEdge[i].et1[2], 2));
	cout << myEdge[i].itsedge << ",  ";*/
//}

//for (int i = 0; i < NumberOfTops2 - 1; i++)
//{
//	if ((i % 4) == 0)
//		cout << "\n\n";
//	myEdge2[i].et1[0] = G2.tops[i].x;
//	myEdge2[i].et1[1] = G2.tops[i].y;
//	myEdge2[i].et1[2] = G2.tops[i].z;
//
//	myEdge2[i].et2[0] = G2.tops[i + 1].x;
//	myEdge2[i].et2[1] = G2.tops[i + 1].y;
//	myEdge2[i].et2[2] = G2.tops[i + 1].z;
//
//	//находим длину ребра
//	myEdge2[i].itsedge = sqrt(pow(myEdge2[i].et2[0] - myEdge2[i].et1[0], 2) + pow(myEdge2[i].et2[1] - myEdge2[i].et1[1], 2) + pow(myEdge2[i].et2[2] - myEdge2[i].et1[2], 2));
//	cout << myEdge2[i].itsedge << ",  ";
//}
//	}
