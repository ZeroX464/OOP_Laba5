using namespace std;
#include <stdio.h>
#include <random>
#include <iostream>

class Number {
private:
	int value;
public:
	Number() : value(0) {}
	Number(int value) : value(value) {}
	Number(const Number& s) : value(s.value) {}
	~Number() {}
	void printInf() {
		printf("Number object with value: %d\n", value);
	}
};

class Point {
protected:
	int x, y, z;
public:
	Point() : x(0), y(0), z(0) {
        printf("Point()\n");
    }
	Point(int x, int y, int z) : x(x), y(y), z(z) {
        printf("Point(int x, int y, int z)\n");
    }
	Point(const Point& p) : x(p.x), y(p.y), z(p.z) {
        printf("Point(const Point &p)\n");
    }
	virtual ~Point() {
        printf("~Point()\n");
    }
	void printInf() {
		printf("Point object with coordinates: %d, %d, %d\n", x, y, z);
	}
    virtual void printInf2() {
        printf("Point object with coordinates: %d, %d, %d\n", x, y, z);
    }
    virtual void printInf3() {
        printf("Point object with coordinates: %d, %d, %d\n", x, y, z);
    }
    virtual string classname() {
        return "Point";
    }
    virtual string classname2() const { // const ��������, ��� ����� �� �������� ��������� ������� ����� ��������
        return "Point";
    }
    virtual bool isA(string classname) const {
        return "Point" == classname;
    }
};

class UndefinedPoint : public Point {
public:
    int range;
public:
    UndefinedPoint() : Point(), range(0) {
        printf("UndefinedPoint()\n");
    }
    UndefinedPoint(int x, int y, int z, int randomRange) : Point(x, y, z), range(randomRange) {
        printf("UndefinedPoint(int x, int y, int z)\n");
    }
    UndefinedPoint(const UndefinedPoint& p) : Point(p), range(p.range) {
        printf("UndefinedPoint(const Point &p)\n");
    }
    ~UndefinedPoint() {
        printf("%d, %d, %d, Range = %d\n", x, y, z, range);
        printf("~UndefinedPoint()\n");
    }
    void printInf2() override {
        printf("UndefinedPoint object with coordinates : %d, %d, %d\n", x, y, z);
    }
    string classname() override {
        return "UndefinedPoint";
    }
    string classname2() const override {
        return "UndefinedPoint";
    }
    bool isA(string classname) const override {
        return "UndefinedPoint" == classname || Point::isA(classname);
    }
};

void print1(Point obj) {
    cout << "Classname: " << obj.classname() << endl;
}
void print2(const Point& obj) {
    cout << "Classname: " << obj.classname2() << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    printf("������������� ������:\n");
    {
        UndefinedPoint p;
        p.printInf(); // ����������� �����
        p.printInf2(); // ������������� �����
    }
    printf("����������� ������:\n");
    {
        Point p;
        UndefinedPoint p2;

        p.printInf3(); // ����������� ������� �����
        p2.printInf3(); // ����������� ����������� �����

        /*
        Point* p = new UndefinedPoint();
        p->printInf(); // ����������� �����, ��������� ����� �������� ������
        p->printInf2(); // ������������� �����, ��������� ����� ������������ ������
        delete p; // ���������� �������� ��������� ������������ �����������
        UndefinedPoint* p2 = new UndefinedPoint();
        p2->printInf(); // ����������� �����, ��������� ����� ������������ ������
        p2->printInf2();
        delete p2;
        */
    }
    printf("�������� �� �������������� ������:\n");
    {
        Point* p = new UndefinedPoint();
        UndefinedPoint* p2 = new UndefinedPoint();
        string str1 = p->classname();
        string str2 = p2->classname();
        printf("p: %s\np2: %s\n", str1.c_str(), str2.c_str());

        print1(*p); // ����� ������ ��������� � ������� �� �������� �.�. ���������� ��� ������ ������ Point
        print1(*p2); // ���������� � ���, ��� ��� ������ ������ UndefinedPoint ��������

        print2(*p); // ����� ������ ��������� �� ������, �� ���������
        print2(*p2);

        Point p3;

        if (p3.isA("UndefinedPoint")) { printf("Yes\n"); } // ����� isA ���������� ���, ��� �� ��������� �������� �� ������ �������� ���������� ������
        else { printf("No\n"); }

        if (p2->isA("UndefinedPoint")) { printf("Yes\n"); }
        else { printf("No\n"); }

        delete p, p2;
    }
    printf("������� ���������� ����� + isA:\n");
    {
        
        Point p;
        Point* p2 = &p;
        if (p2->isA("Point")) {
            UndefinedPoint* p3 = static_cast<UndefinedPoint*>(p2); // ������ �� ���������
            cout << p3->range << endl << p3->classname() << endl; // �� range ���������� � ��������������������� ������
        }
         
        Point* p4 = new Point();
        if (p4->isA("Point")) {
            UndefinedPoint* p5 = static_cast<UndefinedPoint*>(p4);
            cout << p5->range << endl << p5->classname() << endl;

        }
        delete p4;
        
        Point* p6 = new UndefinedPoint(); // ����� �� ���������
        if (p6->isA("UndefinedPoint")) {
            UndefinedPoint* p7 = static_cast<UndefinedPoint*>(p6);
            cout << p7->range << endl << p7->classname() << endl;

        }
        delete p6;
    }
    printf("Dynamic cast:\n");
    {
        Point p;
        Point* p2 = &p;
        UndefinedPoint* p21 = dynamic_cast<UndefinedPoint*>(p2); // p21 ����� nullptr �.�. ������ ��������� ��������� �� ������ � ��������� �� �������
        if (p21 != nullptr) { cout << p21->range << endl << p21->classname() << endl; }
        else { printf("p21 was nullptr\n"); }

        Point* p3 = new Point();
        UndefinedPoint* p31 = dynamic_cast<UndefinedPoint*>(p3);
        if (p31 != nullptr) { cout << p31->range << endl << p31->classname() << endl; }
        else { printf("p31 was nullptr\n"); }
        delete p3;

        Point* p4 = new Point();
        Point* p41 = dynamic_cast<Point*>(p4); // ����� �� ���������
        if (p41 != nullptr) { cout << p41->classname() << endl; }
        else { printf("p41 was nullptr\n"); }
        delete p4;


    }
    printf("���������� ���������� ����� �������\n");
    {

    }
    printf("����� ���������:\n");
    {

    }
    printf("�������� ��������� �������� �������� ��� ���������� � �������:\n");
    {

    }
    printf("�������� ��������� �������� �������� ��� ���������� � �������:\n");
    {

    }
	return 0;
}