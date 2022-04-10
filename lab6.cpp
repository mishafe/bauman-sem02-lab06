#include <iostream>
#include <cmath>

#define PI 3.14

using namespace std;

class Triangle;

// класс точки
class Point
{
private:
    float x;
    float y;
    friend class Triangle;
    friend istream& operator>>(istream&, Point&);
public:
    Point(float x = 0, float y = 0) {
        this->x = x;
        this->y = y;
    }
    float getx() { return x; };
    float gety() { return y; };
};

// класс треугольника
class Triangle
{
private:
    Point a;
    Point b;
    Point c;
public:
    Triangle(Point& a, Point& b, Point& c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    void angles();
    friend double side(Point, Point);
    friend double law_of_cosines(double, double, double);
};

// рассчет стороны по двум точкам
double side(Point a, Point b) {
    double n = sqrt(pow((b.getx() - a.getx()), 2) + pow((b.gety() - a.gety()), 2));
    return n;
}

// теорема косинусов 
double law_of_cosines(double a, double b, double c) {
    double angle;
    angle = 180 / PI * acos((a*a + b*b - c*c) / (2*a*b)); // радианы в градусы
    return angle;
}

// вычисление углов
void Triangle::angles()
{
    double ab, bc, ac;
    double cosA, cosB, cosC;
    ab = side(a, b);
    bc = side(b, c);
    ac = side(a, c);
    cosA = law_of_cosines(ab, bc, ac);
    cosB = law_of_cosines(ac, ab, bc);
    cosC = law_of_cosines(bc, ac, ab);
    cout << cosA << ", " << cosB << ", " << cosC << endl;
}

// перегрузка ввода
istream& operator>>(istream& input, Point& p)
{
    char semicolon = ';';
    input >> p.x >> semicolon >> p.y;
    return input;
}

// проверка точек треугольника
bool triangle_check(Point a, Point b, Point c) {
    if (((a.getx() == b.getx()) && (a.gety() == b.gety())) || ((a.getx() == c.getx()) && (a.gety() == c.gety())) || ((b.getx() == c.getx()) && (b.gety() == c.gety()))) {
        cout << "Points cannot match!" << endl;
        return 0;
    };
    if ((side(a, b) <= abs(side(b, c) - side(a, c))) || (side(a, b) >= (side(b, c) + side(a, c)))) {
        cout << "Points lie on the same line!" << endl;
        return 0;
    }
    return 1;
}

int main()
{
    Point A, B, C;
    cout << "Input x;y x1;y1 x2;y2 or exit" << endl;
    while (cin >> A >> B >> C) {
        if (triangle_check(A, B, C)) {
            Triangle T(A, B, C);
            cout << "Triangle's angles: ";
            T.angles();
            cout << endl;
        }
        cout << "Input x;y x1;y1 x2;y2 or exit" << endl;
    }
    return 0;
}