#include "Header.h"

#define graphics
std::vector<Point> vec;

#ifdef graphics
void Initialize()
{
	//Выбрать фоновый (очищающий) цвет
	glClearColor(1.0, 0.0, 1.0, 1.0);
	//Установить проекцию
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.6, 0.0, 0.9, -1.0, 1.0);
}
void DrawWebVert(double i) {
	glLineWidth(1);
	glColor3f(0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(i, 0);
	glVertex2f(i, 0.9);
	glEnd();
	glFlush();
}
void DrawWebGor(double j) {
	glLineWidth(1);
	glColor3f(0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0, j);
	glVertex2f(1.6, j);
	glEnd();
	glFlush();
}
void DrawSquad(double i, double j, int col) {
	glBegin(GL_POLYGON);	
	switch (col)
	{
	case 0:
		glColor3f(0.5, 0.5, 0.5);
		break;
	case 1:
		glColor3f(0, 0, 0);
		break;
	case 2:
		glColor3f(1, 1, 1);
		break;
	case 3:
		glColor3f(1, 0, 0);
		break;
	}
	glVertex2f(		  j,	    i);
	glVertex2f(j + 0.1,	    i);
	glVertex2f(j + 0.1, i + 0.1);
	glVertex2f(		  j, i + 0.1);
	glEnd();
	glFlush();
}
void Draw2() { 
	for (int i = 0; i < vec.size(); ++i) {
		DrawSquad(0.9 - vec[i].x*0.1, vec[i].y*0.1, 0);
	}
}
void Draw()
{	
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if(labirint[i][j]==1)DrawSquad(0.9 - i * 0.1, j * 0.1, 2);
			else DrawSquad(0.9 - i * 0.1, j * 0.1, 1);
		}
	}
	Draw2();
	for (int i = 0; i < 16; ++i)
		DrawWebVert(i*0.1);
	for (int i = 0; i < 10; ++i)
		DrawWebGor(i*0.1);
	DrawSquad(0.9 - 5 * 0.1, 5 * 0.1, 3);
	DrawSquad(0.9 - 6 * 0.1, 9 * 0.1, 3);
}
#endif // graphics

void main(int argc, char **argv) {
	Point st(5, 5), end(6,9);
	std::vector<Point> way;
	vec = searchWay(st, end, (int**)labirint);
#ifndef graphics
	for (int i = 0; i < vec.size(); ++i) {
		labirintt[vec[i].x][vec[i].y] = i + 2;
	}
	PrintMap();
	system("pause");
#else
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 225);		//Указываем размер окна
	glutInitWindowPosition(1000, 700);	//Позиция окна
	glutCreateWindow("Polygon");		//Имя окна
	Initialize();						//Вызов функции Initialize
	glutDisplayFunc(Draw);				//Вызов функции отрисовки

	
	glutMainLoop();
#endif // !graphics
}
