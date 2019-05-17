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

// Нужно задать ваши классы для описания фигур.
// Каждый класс унаследован от VisPolygon, реализует его интерфейс.
// Внутри класс может иметь любую реализацию.
// Здесь дан только быстрый и грязный пример для треугольника.

// Класс треугольника.
// Набор классов в решении *ваш* - что в них нужно, то и реализуете.
// Копировать этот класс *не* надо. Он тут только для примера.
// Как уже было сказано выше, это очень быстрый и грязный пример, просто чтобы показать технические приёмы.
class Figure : public VisPolygon {

protected:

	double x;
	double y;
	double size;
	double vx;
	double vy;
	double dt = 0.1; // Шаг по времени
					 // Вопрос : Почему выдает ошибку ссылки на удаленную
					 // Функцию если const double dt

public:

	Figure(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {}

	// Далее какие-то ваши методы, никак не связанные с VisPolygon.
	// Например, в данном примере этот метод отвечает за движение нашего треугольника нашим движком.
	void move() {
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


	// Вернем координаты ЦМ
	void getXY() {
		cout << "(" << x << ";" << y << ") ";
	}

};

class Triangle : public Figure {
public:
	// Конструктор
	Triangle(double x, double y, double size, double vx, double vy) : Figure(x, y, size, vx, vy) {}

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

};

class Square : public Figure {
public:
	// Конструктор
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
	// Конструктор
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

	//делаем один "шаг"
	void doTimeStep() override {
		for (Triangle& t : bodiesT) {
			t.move();
			t.getVertices();// хочу,чтобы после каждого шага были все точки доступны, дабы их потом передать
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

		int k = rand() % 4; // Число 0..3
		if (k == 1) {
			int numberT = 1 + rand() % 9;
			creatureT(numberT);
		}
		if (k == 2) {
			int numberS = 1 + rand() % 9;
			creatureS(numberS);
		}
		if (k == 3) {
			int numberR = 1 + rand() % 9;
			creatureR(numberR);
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
    void creatureT(int numberT) {
		// Заполняем случайно вектора фигур
		for (int i = 0; i < numberT; i++) {
			double x = -SCENE_WIDTH / 2 + rand() % SCENE_WIDTH; // Неявное приведение типа int от random() к double. Ошибка?
			double size = 1 + rand() % (SCENE_WIDTH / 4);
			//Логическое с неба взятое ограничение на скорости
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
	// Далее, возможно, ещё какая-то куча ваших методов, с интерфейсом не связанных
	// ...

	// Какая-то работа по иниту, например.
	// Здесь у нас всего два треугольника во всей сцене. Ничего не порождается и не уничтожается. И никакого рандома.
	void initScene(int numberT, int numberS, int numberR) {
		creatureT(numberT);
		creatureS(numberS);
		creatureR(numberR);
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
		cout << "на время "<< i <<"-го шага у нас "<< scene->getNumberOfFigures() << " фигур c координатами " ;//нет визуализации, проверка роботы кода
		//scene->getXY(); // Посмотрели координаты
		cout << endl;
	}

	// Удаляем сцену
	delete scene;


	return 0;
};

