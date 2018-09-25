#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <glut.h>   //Подключение библиотеки glut.h

/*лабиринты*/
int labirint[10][10] = {
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0 },
	{ 0,1,1,0,1,0,0,1,1,1 },
	{ 0,0,1,0,0,1,1,0,0,0 },
	{ 1,0,1,0,0,1,0,1,0,0 },
	{ 0,0,1,1,1,1,0,0,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
};
int labirintt[10][10] = {
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0 },
	{ 0,1,1,0,1,0,0,1,1,1 },
	{ 0,0,1,0,0,1,1,0,0,0 },
	{ 1,0,1,0,0,1,0,1,0,0 },
	{ 0,0,1,1,1,1,0,0,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
};
int labirint2[9][16] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,1 },
	{ 0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0 },
	{ 1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};

//класс точка
struct Point {	
	int x; //х координата
	int y; //у координата
	//конструкторы
	Point() { x = 0; y = 0; }
	Point(int _x, int _y) {
		x = _x, y = _y;
	}
	//сравнение точек
	const bool operator == (const Point &v2)
	{
		if ((x == v2.x) && (y == v2.y))
			return true;
		else return false;
	}
	//присваивание
	Point operator = (Point v1)
	{
		this->x = v1.x, this->y = v1.y;
		return *this;
	}
	//хз особо не надо
	friend Point operator - (Point p1, Point p2 ) {
		return Point(p1.x - p2.x, p1.y - p2.y);
	}
	friend Point operator + (Point p1, Point p2) {
		return Point(p1.x + p2.x, p1.y + p2.y);
	}
};

void PrintMap() {
	//вывод карты на экран
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {
			//формирование сдвига для десятичного числа
			if (labirintt[i][j] / 10 >= 1)
				std::cout << labirintt[i][j] << " ";
			else std::cout << labirintt[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

//проверка на нахождение рядом точек
bool linked(Point one, Point two) {
	if (one.x == two.x) {
		//если они по одной орркдинате х и не далеко по у
		if (one.y == (two.y + 1) || one.y == (two.y - 1)) return true;
		else return false;
	}
	else {
		if (one.y == two.y) {
			//если они по одной координате у и не далеко по х
			if (one.x == (two.x + 1) || one.x == (two.x - 1)) return true;
			else return false;
		}
		else return false;
	}
}
//строим путь в квадратной карте
std::vector<Point> buildWay(int **map, int max) {
	int n = 10, mx = max; //размер поля и всего шагов сколько до цели
	std::vector<Point> res; //итоговый путь
	std::vector<std::vector<Point>> pp; //все существующие шаги
	int i = 0, j = 0;
	//инициализируем
	for (i = 0; i < max + 1; ++i)
		pp.push_back(res);
	//получаем все шаги впринципе написанные
	for (i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) 
			if (labirint[i][j] != 0 && labirint[i][j] != 1)
				pp[labirint[i][j]].push_back(Point(i, j));
	int cheked = 0, jgood = 0;
	Point badInd; //для возврата на предыдущий шаг
	res.push_back(pp[pp.size() - 1][0]);
	for (i = pp.size() - 2; i > 2; --i) {
		if (pp[i].size() == 1) res.push_back(pp[i][0]);
		else {
			for (j = jgood; j < pp[i].size(); ++j) {
				if (linked(res.back(), pp[i][j])) {
					badInd.x = i;
					badInd.y = j;
					res.push_back(pp[i][j]);
					break;
				}
				else cheked++; //на случай отсутствия пути
			}
			if (cheked == pp[i].size()) {
				jgood = badInd.y;
				while (i != badInd.x) {
					res.pop_back();
					i++; //на шаг назад вернемся
				}
				cheked = 0;
			}
			else {
				cheked = 0;
				jgood = 0;
			}
		}
	}
	return res;
}
//ищем путь в квадратной карте
std::vector<Point> searchWay(Point st, Point end, int **map) {
	std::vector<Point> p; //сам путь кладём сюды
	int n = 10, temp = 2; //n-размер поля
	bool fl = true; //флаг для 
	p.reserve(16*9); //выделяем место под путь
	labirint[st.x][st.y] = 2; //ставим на стартовую позицию 2
	while (labirint[end.x][end.y] == 0 && fl)
	{
		fl = false;
		//проходим по всему полю
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				//если натыкаемся на нужный шаг путя
				if (labirint[i][j] == temp) { 
					//расставляем следующие шаги
					if (j > 0 && labirint[i][j - 1] == 0)
					{
						labirint[i][j - 1] = temp + 1; 
						fl = true;
					}
					if (i > 0 && labirint[i - 1][j] == 0)
					{
						labirint[i - 1][j] = temp + 1;
						fl = true;
					}
					if (j < n - 1 && labirint[i][j + 1] == 0)
					{
						labirint[i][j + 1] = temp + 1;
						fl = true;
					}
					if (i < n - 1 && labirint[i + 1][j] == 0)
					{
						labirint[i + 1][j] = temp + 1;
						fl = true;
					}
				}
			}
		}
		temp++; //увеличиваем шаг путя
	}
	p = buildWay(map, temp);
	return p;
}
//строим путь
std::vector<Point> buildWayG(int **map, int max) {
	int n = 10, mx = max;
	std::vector<Point> res;
	std::vector<std::vector<Point>> pp;
	int i = 0, j = 0;
	for (i = 0; i < max + 1; ++i)
		pp.push_back(res);
	for (i = 0; i < 16; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (labirint2[i][j] != 0 && labirint2[i][j] != 1)
				pp[labirint2[i][j]].push_back(Point(i, j));
		}
	}
	int cheked = 0, jgood = 0;
	Point badInd;
	res.push_back(pp[pp.size() - 1][0]);
	for (i = pp.size() - 2; i > 2; --i) {
		if (pp[i].size() == 1) res.push_back(pp[i][0]);
		else {
			for (j = jgood; j < pp[i].size(); ++j) {
				if (linked(res.back(), pp[i][j])) {
					badInd.x = i;
					badInd.y = j;
					res.push_back(pp[i][j]);
					break;
				}
				else cheked++; //на случай отсутствия пути
			}
			if (cheked == pp[i].size()) {
				jgood = badInd.y;
				while (i != badInd.x) {
					res.pop_back();
					i++; //на шаг назад вернемся
				}
				cheked = 0;
			}
			else {
				cheked = 0;
				jgood = 0;
			}
		}
	}
	return res;
}
//ищем путь
std::vector<Point> searchWayG(Point st, Point end, int **map) {
	std::vector<Point> p; //way
	int nn = 10, temp = 2; //size
	bool fl = true;
	p.reserve(16 * 9);
	labirint2[st.x][st.y] = 2;
	while (labirint2[end.x][end.y] == 0 && fl)
	{
		fl = false;
		for (int i = 0; i < 16; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (labirint2[i][j] == temp) {
					if (j > 0 && labirint2[i][j - 1] == 0)
					{
						labirint2[i][j - 1] = temp + 1;
						fl = true;
					}
					if (i > 0 && labirint[i - 1][j] == 0)
					{
						labirint2[i - 1][j] = temp + 1;
						fl = true;
					}
					if (j < 8 && labirint2[i][j + 1] == 0)
					{
						labirint2[i][j + 1] = temp + 1;
						fl = true;
					}
					if (i < 15 && labirint2[i + 1][j] == 0)
					{
						labirint2[i + 1][j] = temp + 1;
						fl = true;
					}
				}
			}
		}
		temp++;
	}
	p = buildWayG(map, temp);
	return p;
}
