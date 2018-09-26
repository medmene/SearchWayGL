#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#define graphics

#ifdef graphics
#include <glut.h>   //Подключение библиотеки glut.h
#endif // graphics

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


struct Point {	
	int x; 
	int y; 
	Point() { x = 0; y = 0; }
	Point(int _x, int _y) {
		x = _x, y = _y;
	}
	
	const bool operator == (const Point &v2)
	{
		if ((x == v2.x) && (y == v2.y))
			return true;
		else return false;
	}
	
	Point operator = (Point v1)
	{
		this->x = v1.x, this->y = v1.y;
		return *this;
	}
	
	friend Point operator - (Point p1, Point p2 ) {
		return Point(p1.x - p2.x, p1.y - p2.y);
	}
	friend Point operator + (Point p1, Point p2) {
		return Point(p1.x + p2.x, p1.y + p2.y);
	}
};

void PrintMap() {	
	int i, j;
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 10; ++j) {			
			if (labirintt[i][j] / 10 >= 1)
				std::cout << labirintt[i][j] << " ";
			else std::cout << labirintt[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

bool linked(Point one, Point two) {
	if (one.x == two.x) {
		if (one.y == (two.y + 1) || one.y == (two.y - 1)) return true;
		else return false;
	}
	else {
		if (one.y == two.y) {
			if (one.x == (two.x + 1) || one.x == (two.x - 1)) return true;
			else return false;
		}
		else return false;
	}
}
std::vector<Point> buildWay(int **map, int max) {
	int n = 10, mx = max; 
	std::vector<Point> res; 
	std::vector<std::vector<Point>> pp; 
	int i = 0, j = 0;
	for (i = 0; i < max + 1; ++i)
		pp.push_back(res);
	for (i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) 
			if (labirint[i][j] != 0 && labirint[i][j] != 1)
				pp[labirint[i][j]].push_back(Point(i, j));
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
				else cheked++; 
			}
			if (cheked == pp[i].size()) {
				jgood = badInd.y;
				while (i != badInd.x) {
					res.pop_back();
					i++; 
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
std::vector<Point> searchWay(Point st, Point end, int **map) {
	std::vector<Point> p; 
	int n = 10, temp = 2; 
	bool fl = true; 
	p.reserve(16*9); 
	labirint[st.x][st.y] = 2; 
	while (labirint[end.x][end.y] == 0 && fl)
	{
		fl = false;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (labirint[i][j] == temp) { 
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
		temp++; 
	}
	p = buildWay(map, temp);
	return p;
}
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
				else cheked++; 
			}
			if (cheked == pp[i].size()) {
				jgood = badInd.y;
				while (i != badInd.x) {
					res.pop_back();
					i++; 
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
