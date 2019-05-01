#include "FiguresRainPolygon.h"
#include "FiguresRainScene.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <ostream>
#include <ctime> // Библиотка время для рандома
#include <cstdlib> // Библеотека рандома
#include <stdlib.h>

using namespace std;

const auto SCENE_WIDTH = 20;
const auto SCENE_HEIGHT = 100;
const auto TIME_STEP = 0.1;

// Нужно задать ваши классы для описания фигур.
// Каждый класс унаследован от VisPolygon, реализует его интерфейс.
// Внутри класс может иметь любую реализацию.
// Здесь дан только быстрый и грязный пример для треугольника.

// Класс треугольника.
// Набор классов в решении *ваш* - что в них нужно, то и реализуете.
// Копировать этот класс *не* надо. Он тут только для примера.
// Как уже было сказано выше, это очень быстрый и грязный пример, просто чтобы показать технические приёмы.
class Triangle : public VisPolygon {
protected:
	// Например, храним только одну точку. Причём это даже не центр масс. (центр масс)
	// В данном примере фигура при движении считается равной вот этой самой некоторой её точке.
	// А все остальные вершины "дорисовываются" чисто на этапе построения картинки.
	double x;
	double y;
	// Некий характерный размер нашего треугольника.
	// Выражен в попугаях. Интерпретируется нашим кодом. Как именно - наше дело.
	// Этот параметр "в сыром виде" наружу не виден вообще.
	double size;
	// Скорость фигуры, куда же без неё
	double vx;
	double vy;

public:
	// Конструктор
	Triangle(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}

	// Далее какие-то ваши методы, никак не связанные с VisPolygon.
	// Например, в данном примере этот метод отвечает за движение нашего треугольника нашим движком.
	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// Метод поверки нахождения в стенках фигуры
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // если ЦМ за стенкой, меняем направление
	}

	// Метод проверки высоты фигуры
	bool CheckHeight() { // если улетел, то true
		return (y > SCENE_HEIGHT);
	}

	// Ещё нужна реализация методов интерфейса на базе *ваших* переменных.
	// Переписывать всю свою реализацию под имена методов и полей из интерфейса *не* надо.
	// В данном примере вообще точки для визуализации "дорисовываются" на лету на базе одной хранимой точки.
	vector<VisPoint> getVertices() const override {
		vector<VisPoint> vertices = vector<VisPoint>(3);
		vertices[0] = VisPoint(x, y + size);
		vertices[1] = VisPoint(x + size * cos(3.14/6), y-size/2);
		vertices[2] = VisPoint(x - size * cos(3.14 / 6), y - size/2);
		return vertices;
	}

	// Вернем координаты ЦМ
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
	// Конструктор
	Square(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}


	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// Метод поверки нахождения в стенках фигуры
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // если ЦМ за стенкой, меняем направление
	}

	// Метод проверки высоты фигуры
	bool CheckHeight() { // если улетел, то true
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

	// Вернем координаты ЦМ
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
	// Конструктор
	Rhombus(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
	}


	void move(double dt) {
		x += vx * dt;
		y += vy * dt;
	}



	// Метод поверки нахождения в стенках фигуры
	void CheckWidth() {
		if (abs(x) > SCENE_WIDTH / 2) { vx *= -1; } // если ЦМ за стенкой, меняем направление
	}

	// Метод проверки высоты фигуры
	bool CheckHeight() { // если улетел, то true
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

	// Вернем координаты ЦМ
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

// Ваш класс сцены. В нём вся основная логика. Порождение и уничтожение фигур, обработка стенок - всё здесь.
// Класс унаследован от FiguresRainScene, реализует интерфейс с методами getNumberOfFigures / getFigure / doTimeStep.
class SampleScene : public FiguresRainScene {
protected:
	// В этом примере у нас сплошные треугольники. (квадраты и ромбы)
	// В вашей реализации фигуры должны быть разные. Любые. Но разные.
	vector<Triangle> bodiesT;
	vector<Square> bodiesS;
	vector<Rhombus> bodiesR;

public:
	// Далее реализация методов интерфейса на базе *ваших* данных

	//всего у нас фигур
	unsigned int getNumberOfFigures() const override {
		return bodiesT.size()+ bodiesS.size() + bodiesR.size() ;
	}

	//указатель на фигуру под номером (?)
	const VisPolygon* getFigure(unsigned int number) const override {
		return &bodiesT.at(number);
	}

	//делаем один "шаг"
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

	// Ищем и чистим вектора
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

	// Выводим все ЦМ для всех
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

	// Далее, возможно, ещё какая-то куча ваших методов, с интерфейсом не связанных
	// ...

	// Какая-то работа по иниту, например.
	// Здесь у нас всего два треугольника во всей сцене. Ничего не порождается и не уничтожается. И никакого рандома.
	void initScene(int numberT, int numberS, int numberR) {
		// Заполняем случайно вектора фигур
		for (int i = 0; i < numberT; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % SCENE_WIDTH;
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			//Логическое с неба взятое ограничение на скорости
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

		// bodiesT.push_back(Triangle(5, 0, 1, 2, 1)); // y=0 !! x < ширины стенок
		// bodiesT.push_back(Triangle(-5, 0, 1, -1, 2)); // vy>0 !!
	}
};

// Функция, которая готовит всю сцену и возвращает готовый объект.
// Если нужно читать из файла и консоли, вызывать кучу методов - это здесь.
FiguresRainScene* getScene()
{
	// Например, инит сцены может быть устроен технически так.
	// Ну или как-то иначе.
	// Приведите это в тот вид, который нужен в вашем случае.
	SampleScene* s = new SampleScene();
	int numberT = 1 + rand() % 33;
	int numberS = 1 + rand() % 33;
	int numberR = 1 + rand() % 33;
	s->initScene(numberT, numberS, numberR);
	return s;
}


// Ваш отладочный main
int main()
{
	setlocale(LC_ALL, "Russian"); // Руссификация комментариев
	srand(time(NULL)); // Рандомный рандом

	// Создаём сцену
	SampleScene* scene = (SampleScene*)getScene();

	// Некая работа со сценой в рамках вашей отладки
	// for(...) {
	//     scene->doTimeStep();
	//     scene->print();
	//     scene->whatever();
	// }
	cout << "в начале у нас "  << scene->getNumberOfFigures() << " фигур c координатами ";//нет визуализации, проверка роботы кода
	scene->getXY(); // Посмотрели координаты
	cout << endl;

	for (int i = 0; i < 100; i++) {
		scene->doTimeStep();
		scene->clear();
		cout << "на время "<< i <<"-го шага у нас "<< scene->getNumberOfFigures() << " фигур c координатами " ;//нет визуализации, проверка роботы кода
		scene->getXY(); // Посмотрели координаты
		cout << endl;
	}

	// Удаляем сцену
	delete scene;

	return 0;
};
