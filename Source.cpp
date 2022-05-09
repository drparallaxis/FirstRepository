//By Alan Kokaev project "Thir" for lab of graphs, ИДБ-17-10
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
		//Структура с информацией о координатах направляющего вектора
		struct coordinatesDirectVector 
		{
			double x, y, z; 
		};
		int id;
		int IDFloatNumber1, IDFloatNumber2; // для идентификации присвоенных вершин, чтобы в дальнейшем упростить поиск конкретного ребра
		double* et1; //информация о первой вершине ребра
		double* et2; //информация о второй вершине ребра
		double itsedge; //длина ребра 
		coordinatesDirectVector directVectors;
		Edge()
		{
			directVectors.x = directVectors.y = directVectors.z = 0.0;
			et1 = new double[3];
			et2 = new double[3];
			for (int i = 0; i < 3; i++)
				et1[i] = et2[i] = 0.0;

			itsedge = 0.0;
			IDFloatNumber1 = 0, IDFloatNumber2 = 0;
		}
		~Edge() { delete[] et1; delete[] et2; }
	};
	struct Angle
	{
		double angle, cosOfAngle;
	};
	Top* tops;
	string path;
	int NumberOfTops;
	Edge* myEdge;
	Angle* angles;
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

		angles = new Angle[NumberOfTops*(NumberOfTops - 2)];
		for (int i = 0; i < NumberOfTops*(NumberOfTops - 2); i++)
			angles[i].angle = angles[i].cosOfAngle = 0.0;
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
	
	~Graph() { delete[] tops; delete[] myEdge; delete[] angles; }
};

class Solution : public Graph
{
	string path1, path2;
	int NumberOfElements1, NumberOfElements2;
	int NumberOfTops1, NumberOfTops2;
	int row;
public:
	//virtual int Solution::getGraph() override;
	Solution() //310 c 4 до 5:40
	{
		NumberOfElements1 = NumberOfElements2 = NumberOfTops1 = NumberOfTops2 = 0;

		path1 = "C:\\Users\\miste\\Desktop\\files\\test\\FirstFile.gjf";
		path2 = "C:\\Users\\miste\\Desktop\\files\\test\\SecondFile.gjf";

		NumberOfElements1 = counter(path1, 0);
		NumberOfElements2 = counter(path2, 0);
		NumberOfTops1 = counter(path1, 1);
		NumberOfTops2 = counter(path2, 1);
		row = 0;
	}
	
	void InitGraph()
	{
		Graph G1(path1, NumberOfTops1);
		Graph G2(path2, NumberOfTops2);
		InitOfSubgraph(G1, G2);

		int counter1 = G1.getCountOfEdge(), counter2 = G2.getCountOfEdge();
		int not1 = NumberOfTops1-1, not2 = NumberOfTops2-1;

		int identificator1 = 0;
		int buffer1 = not1; // временный буфер, который хранит значения not1 для вложенного цикла
		int CommonCounter1 = 0; //общий счётчик
		int floatingNumber1 = 0; // плавающий счётчик вершин
		int IfFloatNumber1 = 0; // cчётчик-условие для счётчика вершин
		int HalfFloatingNumber1 = (NumberOfTops1 / 2) + 1; // вторая половина узлов 1 графа
		
		while (!(not1 <= 0))
		{
			while (!(buffer1 < 1))
			{
				G1.myEdge[CommonCounter1].id = identificator1++;
				G1.myEdge[CommonCounter1].et1[0] = G1.tops[floatingNumber1].x;
				G1.myEdge[CommonCounter1].et1[1] = G1.tops[floatingNumber1].y;
				G1.myEdge[CommonCounter1].et1[2] = G1.tops[floatingNumber1].z;
				G1.myEdge[CommonCounter1].IDFloatNumber1 = floatingNumber1;
				if (HalfFloatingNumber1 != NumberOfTops1)
				{
					G1.myEdge[CommonCounter1].et2[0] = G1.tops[HalfFloatingNumber1].x;
					G1.myEdge[CommonCounter1].et2[1] = G1.tops[HalfFloatingNumber1].y;
					G1.myEdge[CommonCounter1].et2[2] = G1.tops[HalfFloatingNumber1].z;
					G1.myEdge[CommonCounter1].IDFloatNumber2 = HalfFloatingNumber1;
				}
				IfFloatNumber1++;
				if (IfFloatNumber1 == NumberOfTops1)
				{
					floatingNumber1++;
					HalfFloatingNumber1++;
					IfFloatNumber1 = 0;
				}
				CommonCounter1++;
				buffer1--;
			}
			not1--;
			buffer1 = not1;
		}

		int identificator2 = 0;
		int buffer2 = not2; // временный буфер, который хранит значения not1 для вложенного цикла
		int CommonCounter2 = 0; //общий счётчик
		int floatingNumber2 = 0; // плавающий счётчик вершин
		int IfFloatNumber2 = 0; // cчётчик-условие для счётчика вершин
		int HalfFloatingNumber2 = (NumberOfTops2 / 2) + 1; // вторая половина узлов 1 графа

		while (!(not2 <= 0))
		{
			while (!(buffer2 < 1))
			{
				G2.myEdge[CommonCounter2].id = identificator2++;
				G2.myEdge[CommonCounter2].et1[0] = G2.tops[floatingNumber2].x;
				G2.myEdge[CommonCounter2].et1[1] = G2.tops[floatingNumber2].y;
				G2.myEdge[CommonCounter2].et1[2] = G2.tops[floatingNumber2].z;
				G2.myEdge[CommonCounter2].IDFloatNumber1 = floatingNumber2;
				if (HalfFloatingNumber2 != NumberOfTops2)
				{
					G2.myEdge[CommonCounter2].et2[0] = G2.tops[HalfFloatingNumber2].x;
					G2.myEdge[CommonCounter2].et2[1] = G2.tops[HalfFloatingNumber2].y;
					G2.myEdge[CommonCounter2].et2[2] = G2.tops[HalfFloatingNumber2].z;
					G2.myEdge[CommonCounter2].IDFloatNumber2 = HalfFloatingNumber2;
					
				}
				IfFloatNumber2++;
				if (IfFloatNumber2 == NumberOfTops2)
				{
					floatingNumber2++;
					HalfFloatingNumber2++;
					IfFloatNumber2 = 0;
				}
				CommonCounter2++;
				buffer2--;
			}
			not2--;
			buffer2 = not2;
		}

		//Вычисление координат направляющих векторов для канон.ур
		for (int i = 0; i < counter1; i++)
		{
			if (row != 0)
			{
				G1.myEdge[i].itsedge = sqrt(pow((G1.myEdge[i].et2[0]-row) - (G1.myEdge[i].et1[0]-row), 2) + pow((G1.myEdge[i].et2[1] - row) - (G1.myEdge[i].et1[1] - row), 2) + pow((G1.myEdge[i].et2[2]-row) - (G1.myEdge[i].et1[2] - row), 2));
			}
			else
			     G1.myEdge[i].itsedge = sqrt(pow(G1.myEdge[i].et2[0] - G1.myEdge[i].et1[0], 2) + pow(G1.myEdge[i].et2[1] - G1.myEdge[i].et1[1], 2) + pow(G1.myEdge[i].et2[2] - G1.myEdge[i].et1[2], 2));
			/*G1.myEdge[i].directVectors.x = (G1.myEdge[i].et2[0] - G1.myEdge[i].et1[0]);
			G1.myEdge[i].directVectors.y = (G1.myEdge[i].et2[1] - G1.myEdge[i].et1[1]);
			G1.myEdge[i].directVectors.z = (G1.myEdge[i].et2[2] - G1.myEdge[i].et1[2]);*/
			//cout << "x = " << G1.myEdge[i].directVectors.x << ",  y = " << G1.myEdge[i].directVectors.y << ",  z = " << G1.myEdge[i].directVectors.z << ";\n";
		}
		cout << "\n\n\n";
		for (int i = 0; i < counter2; i++)
		{
			G2.myEdge[i].itsedge = sqrt(pow(G2.myEdge[i].et2[0] - G2.myEdge[i].et1[0], 2) + pow(G2.myEdge[i].et2[1] - G2.myEdge[i].et1[1], 2) + pow(G2.myEdge[i].et2[2] - G2.myEdge[i].et1[2], 2));
			//cout << G2.myEdge[i].itsedge << ", ";
			/*G2.myEdge[i].directVectors.x = (G2.myEdge[i].et2[0] - G2.myEdge[i].et1[0]);
			G2.myEdge[i].directVectors.y = (G2.myEdge[i].et2[1] - G2.myEdge[i].et1[1]);
			G2.myEdge[i].directVectors.z = (G2.myEdge[i].et2[2] - G2.myEdge[i].et1[2]);*/
			//cout << "x = " << G2.myEdge[i].directVectors.x << ",  y = " << G2.myEdge[i].directVectors.y << ",  z = " << G2.myEdge[i].directVectors.z << ";\n";
		}
		

		////Нахождение углов
		//int newCounter = 0;
		//double cosAngle = 0.0;
		//int CounterOfAngles = 0; // счётчик углов
		//for (int i = 0; i < NumberOfTops1; i++)
		//{
		//	while (!(newCounter == counter1))
		//	{
		//		if (G1.myEdge[newCounter].IDFloatNumber1 == i || G1.myEdge[newCounter].IDFloatNumber2 == i)
		//		{
		//			//G1.angles[CounterOfAngles].cosOfAngle;
		//			CounterOfAngles++;
		//		}
		//		newCounter++;
		//	}
		//}
		

	//	//Нахождение изоморфных подграфов
		int similarity = 0; 
		int buf = 0;
		int BufOutPut = 777;
		for (int lines = 0; lines < NumberOfTops1; lines++)
		{
			for (int columns = 0; columns < counter1; columns++)
			{
				if (lines == G1.myEdge[columns].IDFloatNumber1 && lines == G2.myEdge[columns].IDFloatNumber1 || lines == G1.myEdge[columns].IDFloatNumber2 && lines == G2.myEdge[columns].IDFloatNumber2)
				{
					//if(G1.angles[columns].angle == G2.angles[columns].angle) { }
					if (G1.myEdge[columns].itsedge == G2.myEdge[columns].itsedge && G1.tops[lines].id == G2.tops[lines].id || (G1.myEdge[columns].itsedge / G2.myEdge[columns].itsedge)>0 && G1.tops[lines].id == G2.tops[lines].id)
					{
						if (G1.tops[lines].x == G2.tops[lines].x && G1.tops[lines].y == G2.tops[lines].y && G1.tops[lines].z == G2.tops[lines].z)
							BufOutPut = lines;
						if (G1.tops[lines].x == G2.tops[lines].x && G1.tops[lines].y == G2.tops[lines].y && G1.tops[lines].z == G2.tops[lines].z && buf == lines)
						{
							similarity++;
						}
					}
				}
				buf = lines+1;
			}
			if (BufOutPut != 777)
			{
				if (row != 0)
				{
					cout << BufOutPut << ") In 1-st: " << G1.tops[BufOutPut].id << ",  " << G1.tops[BufOutPut].x+row << ",  " << G1.tops[BufOutPut].y+row << ",  " << G1.tops[BufOutPut].z+row << "\t\t";
				}
				else
					cout << BufOutPut << ") In 1-st: " << G1.tops[BufOutPut].id << ",  " << G1.tops[BufOutPut].x << ",  " << G1.tops[BufOutPut].y << ",  " << G1.tops[BufOutPut].z << "\t\t";
				cout << "In 2-nd: " << G2.tops[BufOutPut].id << ",  " << G2.tops[BufOutPut].x << ",  " << G2.tops[BufOutPut].y << ",  " << G2.tops[BufOutPut].z << endl;
				BufOutPut = 777;
			}		
		}
		if (similarity >= 2)
			cout << "\n\nIn the 1st graph there are isomorphic subgraphs of graph 2\nВ 1-м графе есть подграфы изоморфные подграфам 2-го графа";
	}


	void simple(Graph& Sgraph, int NumberOfElements, int status, int r)
	{
		double* buffer = new double[NumberOfElements];
		ifstream fin;
		if(status == 1)
			fin.open(path1);
		if (status == 2)
			fin.open(path2);

		int cntr1, cntr2, cntr3, cntr4;
		cntr1 = cntr2 = cntr3 = cntr4 = 0;

		int row = 0;

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
					if (r == 1)
						Sgraph.tops[cntr2].x = buffer[i] + row;
					else
						Sgraph.tops[cntr2].x = buffer[i];
					cntr2++;
				}
				if (((i - 2) % 4) == 0 && i != 0 && i != 1 || i == 2)
				{
					if (r == 1)
						Sgraph.tops[cntr3].y = buffer[i] + row;
					else
						Sgraph.tops[cntr3].y = buffer[i];
					cntr3++;
				}
				if (((i - 3) % 4) == 0 && i > 2 || i == 3)
				{
					if(r == 1)
						Sgraph.tops[cntr4].z = buffer[i]+row;
					else
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
		simple(Sgraph1, NumberOfElements1, 1, 1);
		simple(Sgraph2, NumberOfElements2, 2, 0);
	}

	void info()
	{
		cout << "\n\n\n\n\n";
		Graph G1(path1, NumberOfTops1);
		Graph G2(path2, NumberOfTops2);

		cout << "\n\nКол-во вершин в 1-ом графе: " << NumberOfTops1 << ",  Кол-во вершин во 2-ом графе: " \
			<< NumberOfTops2 << "\nКол-во рёбер в 1-ом графе: " << G1.getCountOfEdge() \
			<< ",  Кол-во ребёр во 2-ом графе: " << G2.getCountOfEdge() << "\nКоличество углов в 1-м графе: " << NumberOfTops1*(NumberOfTops1 - 2) << ", Количество углов во 2-м графе: " << NumberOfTops2*(NumberOfTops2 - 2);
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Solution A, B;

	A.InitGraph();
	//A.info();

	_getch();
}


//int Solution::getGraph()
//{
//	return 0;
//}
