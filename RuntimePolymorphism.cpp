#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Circle;
class Triangle;

class Shape {
public:
	virtual bool intersect(const Shape&) const =0;
	virtual bool intersect(const Circle&) const =0;
	virtual bool intersect(const Triangle&) const =0;
};

class Circle : public Shape {
public:
	bool intersect(const Shape&) const override;
	virtual bool intersect(const Circle&) const override;
	virtual bool intersect(const Triangle&) const override;
};

class Triangle : public Shape {
public:
	bool intersect(const Shape&) const override;
	virtual bool intersect(const Circle&) const override;
	virtual bool intersect(const Triangle&) const override;
};

bool Circle::intersect(const Shape& s) const { 
	cout << "Circle::intersect(const Shape& s) const" << endl;
	return s.intersect(*(this)); 
}
bool Circle::intersect(const Circle&) const { cout <<"intersect(circle,circle)\n"; return true; }
bool Circle::intersect(const Triangle&) const { cout <<"intersect(circle,triangle)\n"; return true; }
bool Triangle::intersect(const Shape& s) const {
	cout << "Triangle::intersect(const Shape& s) const" << endl;
	return s.intersect(*(this));
}
bool Triangle::intersect(const Circle&) const { cout <<"intersect(triangle ,circle)\n"; return true; }
bool Triangle::intersect(const Triangle&) const { cout <<"intersect(triangle ,triangle)\n"; return true; }

void test(Triangle& t, Circle& c)
{
	vector<pair<Shape*,Shape*>> vs { {&t,&t}, {&t,&c}, {&c,&t}, {&c,&c} };
	// for (auto p : vs)
		// p.first->intersect(*p.second);
	
	t.intersect(t);
	t.intersect(c);
	c.intersect(t);
	c.intersect(c);
}

int main() {
	Triangle t1;
	Circle c1;
	test(t1, c1);
}
