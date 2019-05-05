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
class Figure : public VisPolygon {

protected:

	double x;
	double y;
	double size;
	double vx;
	double vy;
	double dt = 0.1; // ��� �� �������
					 // ������ : ������ ������ ������ ������ �� ���������
					 // ������� ���� const double dt

public:

	Figure(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {}

	// ����� �����-�� ���� ������, ����� �� ��������� � VisPolygon.
	// ��������, � ������ ������� ���� ����� �������� �� �������� ������ ������������ ����� �������.
	void move() {
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


	// ������ ���������� ��
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

class Triangle : public Figure {
public:
	// �����������
	Triangle(double x, double y, double size, double vx, double vy) : Figure(x, y, size, vx, vy) {}

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

};

class Square : public Figure {
public:
	// �����������
	Square(double x, double y, double size, double vx, double vy) : Figure(x, y, size, vx, vy) {}

	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(4);
		vertices[0] = VisPoint(x + size / 2, y + size / 2);
		vertices[1] = VisPoint(x + size / 2, y - size / 2);
		vertices[2] = VisPoint(x - size / 2, y - size / 2);
		vertices[3] = VisPoint(x - size / 2, y + size / 2);
		return vertices;
	}

};

class Rhombus : public Figure {
public:
	// �����������
	Rhombus(double x, double y, double size, double vx, double vy) : Figure(x, y, size, vx, vy) {}

	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(4);
		vertices[0] = VisPoint(x, y + size / 2);
		vertices[1] = VisPoint(x + size / 2, y);
		vertices[2] = VisPoint(x, y - size / 2);
		vertices[3] = VisPoint(x - size / 2, y);
		return vertices;
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
		if (number< bodiesT.size()) {
			return &bodiesT.at(number);
		}
		else {
			if (number >= bodiesT.size() + bodiesS.size()) {
				return &bodiesR.at(number- bodiesT.size()- bodiesS.size());
			}
			else {
				return &bodiesS.at(number- bodiesT.size());
			}
		}
	}

	//������ ���� "���"
	void doTimeStep() override {
		for (Triangle& t : bodiesT) {
			t.move();
			t.getVertices();//������������ ���������� ����� ��������, ����� ����� ������ �� � ������������
			t.CheckWidth();
		}
		for (Square& t : bodiesS) {
			t.move();
			t.getVertices();
			t.CheckWidth();
		}
		for (Rhombus& t : bodiesR) {
			t.move();
			t.getVertices();
			t.CheckWidth();
		}
		clear();

		int k = rand() % 4; // ����� 0..3
		if (k = 1) {
			int numberT = 1 + rand() % 9;
			creatureT(numberT);
		}
		if (k = 2) {
			int numberS = 1 + rand() % 9;
			creatureS(numberS);
		}
		if (k = 3) {
			int numberR = 1 + rand() % 9;
			creatureR(numberR);
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
    void creatureT(int numberT) {
		// ��������� �������� ������� �����
		for (int i = 0; i < numberT; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % SCENE_WIDTH; // ������� ���������� ���� int �� random() � double. ������?
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			//���������� � ���� ������ ����������� �� ��������
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH + rand() % SCENE_WIDTH;
			bodiesT.push_back(Triangle(x, 0, size, vx, vy));
		}
	}

	void creatureS(int numberS) {
		for (int i = 0; i < numberS; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % (SCENE_WIDTH / 2);
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH + rand() % SCENE_WIDTH;
			bodiesS.push_back(Square(x, 0, size, vx, vy));
		}
	}

	void creatureR(int numberR) {
		for (int i = 0; i < numberR; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % (SCENE_WIDTH / 2);
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			double vy = rand() % SCENE_HEIGHT;
			double vx = -SCENE_WIDTH + rand() % SCENE_WIDTH;
			bodiesR.push_back(Rhombus(x, 0, size, vx, vy));
		}
	}
	// �����, ��������, ��� �����-�� ���� ����� �������, � ����������� �� ���������
	// ...

	// �����-�� ������ �� �����, ��������.
	// ����� � ��� ����� ��� ������������ �� ���� �����. ������ �� ����������� � �� ������������. � �������� �������.
	void initScene(int numberT, int numberS, int numberR) {
		creatureT(numberT);
		creatureS(numberS);
		creatureR(numberR);
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
		cout << "�� ����� "<< i <<"-�� ���� � ��� "<< scene->getNumberOfFigures() << " ����� c ������������ " ;//��� ������������, �������� ������ ����
		//scene->getXY(); // ���������� ����������
		cout << endl;
	}

	// ������� �����
	delete scene;


	return 0;
};
