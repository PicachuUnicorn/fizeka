#include "FiguresRainPolygon.h"
#include "FiguresRainScene.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <ostream>
#include <ctime> // ��������� ����� ��� �������
#include <cstdlib> // ���������� �������
#include <stdlib.h>

using namespace std;

const auto SCENE_WIDTH = 20;
const auto SCENE_HEIGHT = 100;
const auto TIME_STEP = 0.1;

// ����� ������ ���� ������ ��� �������� �����.
// ������ ����� ����������� �� VisPolygon, ��������� ��� ���������.
// ������ ����� ����� ����� ����� ����������.
// ����� ��� ������ ������� � ������� ������ ��� ������������.

// ����� ������������.
// ����� ������� � ������� *���* - ��� � ��� �����, �� � ����������.
// ���������� ���� ����� *��* ����. �� ��� ������ ��� �������.
// ��� ��� ���� ������� ����, ��� ����� ������� � ������� ������, ������ ����� �������� ����������� �����.
class Triangle : public VisPolygon {
protected:
	// ��������, ������ ������ ���� �����. ������ ��� ���� �� ����� ����. (����� ����)
	// � ������ ������� ������ ��� �������� ��������� ������ ��� ���� ����� ��������� � �����.
	// � ��� ��������� ������� "��������������" ����� �� ����� ���������� ��������.
	double x;
	double y;
	// ����� ����������� ������ ������ ������������.
	// ������� � ��������. ���������������� ����� �����. ��� ������ - ���� ����.
	// ���� �������� "� ����� ����" ������ �� ����� ������.
	double size;
	// �������� ������, ���� �� ��� ��
	double vx;
	double vy;

public:
	// �����������
	Triangle(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}

	// ����� �����-�� ���� ������, ����� �� ��������� � VisPolygon.
	// ��������, � ������ ������� ���� ����� �������� �� �������� ������ ������������ ����� �������.
	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// ����� ������� ���������� � ������� ������
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // ���� �� �� �������, ������ �����������
	}

	// ����� �������� ������ ������
	bool CheckHeight() { // ���� ������, �� true
		return (y > SCENE_HEIGHT);
	}

	// ��� ����� ���������� ������� ���������� �� ���� *�����* ����������.
	// ������������ ��� ���� ���������� ��� ����� ������� � ����� �� ���������� *��* ����.
	// � ������ ������� ������ ����� ��� ������������ "��������������" �� ���� �� ���� ����� �������� �����.
	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(3);
		vertices[0] = VisPoint(x, y + size);
		vertices[1] = VisPoint(x + size * cos(3.14/6), y-size/2);
		vertices[2] = VisPoint(x - size * cos(3.14 / 6), y - size/2);
		return vertices;
	}

	// ������ ���������� ��
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

class Square : public VisPolygon {
protected:

	double x;
	double y;
	double size;
	double vx;
	double vy;

public:
	// �����������
	Square(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}


	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// ����� ������� ���������� � ������� ������
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // ���� �� �� �������, ������ �����������
	}

	// ����� �������� ������ ������
	bool CheckHeight() { // ���� ������, �� true
		return (y > SCENE_HEIGHT);
	}

	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(4);
		vertices[0] = VisPoint(x + size / 2, y + size / 2);
		vertices[1] = VisPoint(x + size / 2, y - size / 2);
		vertices[2] = VisPoint(x - size / 2, y - size / 2);
		vertices[3] = VisPoint(x - size / 2, y + size / 2);
		return vertices;
	}

	// ������ ���������� ��
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

class Rhombus : public VisPolygon {
protected:

	double x;
	double y;
	double size;
	double vx;
	double vy;

public:
	// �����������
	Rhombus(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}


	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// ����� ������� ���������� � ������� ������
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // ���� �� �� �������, ������ �����������
	}

	// ����� �������� ������ ������
	bool CheckHeight() { // ���� ������, �� true
		return (y > SCENE_HEIGHT);
	}

	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(4);
		vertices[0] = VisPoint(x, y + size / 2);
		vertices[1] = VisPoint(x + size / 2, y);
		vertices[2] = VisPoint(x, y - size / 2);
		vertices[3] = VisPoint(x - size / 2, y);
		return vertices;
	}

	// ������ ���������� ��
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

// ��� ����� �����. � �� ��� �������� ������. ���������� � ����������� �����, ��������� ������ - �� �����.
// ����� ����������� �� FiguresRainScene, ��������� ��������� � �������� getNumberOfFigures / getFigure / doTimeStep.
class SampleScene : public FiguresRainScene {
protected:
	// � ���� ������� � ��� �������� ������������. (�������� � �����)
	// � ����� ���������� ������ ������ ���� ������. �����. �� ������.
	vector<Triangle> bodiesT;
	vector<Square> bodiesS;
	vector<Rhombus> bodiesR;

public:
	// ����� ���������� ������� ���������� �� ���� *�����* ������

	//����� � ��� �����
	unsigned int getNumberOfFigures() const override {
		return bodiesT.size()+ bodiesS.size() + bodiesR.size() ;
	}

	//��������� �� ������ ��� ������� (?)
	const VisPolygon* getFigure(unsigned int number) const override {
		return &bodiesT.at(number);
	}

	//������ ���� "���"
	void doTimeStep() override {
		for (Triangle& t : bodiesT) {
			t.move(0.1);
			t.getVertices();
			t.CheckWidth();
		}
		for (Square& t : bodiesS) {
			t.move(0.1);
			t.getVertices();
			t.CheckWidth();
		}
		for (Rhombus& t : bodiesR) {
			t.move(0.1);
			t.getVertices();
			t.CheckWidth();
		}
	}

	// ���� � ������ �������
	void clear() {
		int i = 0;
		while (i < bodiesT.size()) {
			if (bodiesT[i].CheckHeight()) {
				bodiesT.erase(bodiesT.begin() + i);
			}
			else { i++; }
		}
		i = 0;
		while (i < bodiesS.size()) {
			if (bodiesS[i].CheckHeight()) {
				bodiesS.erase(bodiesS.begin() + i);
			}
			else { i++; }
		}
		i = 0;
		while (i < bodiesR.size()) {
			if (bodiesR[i].CheckHeight()) {
				bodiesR.erase(bodiesR.begin() + i);
			}
			else { i++; }
		}
	}

	// ������� ��� �� ��� ����
	void getXY() {
		for (Triangle& t : bodiesT) {
			t.getXY();
		}
		for (Square& t : bodiesS) {
			t.getXY();
		}
		for (Rhombus& t : bodiesR) {
			t.getXY();
		}
	}

	// �����, ��������, ��� �����-�� ���� ����� �������, � ����������� �� ���������
	// ...

	// �����-�� ������ �� �����, ��������.
	// ����� � ��� ����� ��� ������������ �� ���� �����. ������ �� ����������� � �� ������������. � �������� �������.
	void initScene(int numberT, int numberS, int numberR) {
		// ��������� �������� ������� �����
		for (int i = 0; i < numberT; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % SCENE_WIDTH;
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			//���������� � ���� ������ ����������� �� ��������
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH  +  rand() % SCENE_WIDTH ;
			bodiesT.push_back(Triangle(x, 0, size, vx, vy));
		}
		for (int i = 0; i < numberS; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % (SCENE_WIDTH / 2);
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH + rand() % SCENE_WIDTH;
			bodiesS.push_back(Square(x, 0, size, vx, vy));
		}
		for (int i = 0; i < numberR; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % (SCENE_WIDTH / 2);
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH + rand() % SCENE_WIDTH;
			bodiesR.push_back(Rhombus(x, 0, size, vx, vy));
		}

		// bodiesT.push_back(Triangle(5, 0, 1, 2, 1)); // y=0 !! x < ������ ������
		// bodiesT.push_back(Triangle(-5, 0, 1, -1, 2)); // vy>0 !!
	}
};

// �������, ������� ������� ��� ����� � ���������� ������� ������.
// ���� ����� ������ �� ����� � �������, �������� ���� ������� - ��� �����.
FiguresRainScene* getScene()
{
	// ��������, ���� ����� ����� ���� ������� ���������� ���.
	// �� ��� ���-�� �����.
	// ��������� ��� � ��� ���, ������� ����� � ����� ������.
	SampleScene* s = new SampleScene();
	int numberT = 1 + rand() % 33;
	int numberS = 1 + rand() % 33;
	int numberR = 1 + rand() % 33;
	s->initScene(numberT, numberS, numberR);
	return s;
}


// ��� ���������� main
int main()
{
	setlocale(LC_ALL, "Russian"); // ������������ ������������
	srand(time(NULL)); // ��������� ������

	// ������ �����
	SampleScene* scene = (SampleScene*)getScene();

	// ����� ������ �� ������ � ������ ����� �������
	// for(...) {
	//     scene->doTimeStep();
	//     scene->print();
	//     scene->whatever();
	// }
	cout << "� ������ � ��� "  << scene->getNumberOfFigures() << " ����� c ������������ ";//��� ������������, �������� ������ ����
	scene->getXY(); // ���������� ����������
	cout << endl;

	for (int i = 0; i < 100; i++) {
		scene->doTimeStep();
		scene->clear();
		cout << "�� ����� "<< i <<"-�� ���� � ��� "<< scene->getNumberOfFigures() << " ����� c ������������ " ;//��� ������������, �������� ������ ����
		scene->getXY(); // ���������� ����������
		cout << endl;
	}

	// ������� �����
	delete scene;

	return 0;
};
