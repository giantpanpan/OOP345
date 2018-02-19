#include<iostream>
#include<typeinfo>  //for typeid




/*Dynamic type polymorphism, Specializing an operation for a dynamic type using dynamic_cast*/
class Shape {
public: 
	virtual double volumn() const = 0;
	virtual Shape* clone() const = 0;
	virtual void display() const = 0;
	virtual bool operator==(const Shape&) const = 0; //receives the address of an object and return true if the object has the same properties
	                                                 //as the current object
};

class Cube : public Shape {
	double len;
public:
	Cube(double l) : len{ l } { std::cout << "Cube(double l) : len{ l }" << std::endl; };
	double volumn() const {
		std::cout << "double volumn() const" << std::endl;
		return len*len*len;
	}
	Shape* clone()  const {
		std::cout << "Shape* clone()  const" << std::endl;
		return new Cube(*this);
	}
	void display() const {
		std::cout << "void display() const" << std::endl;
		std::cout << "length = " << this->len << std::endl;
	}
	bool operator==(const Shape& rhs) const{
		std::cout << "bool operator==(const Shape& rhs) const" << std::endl;
		std::cout << "current object is" << this << std::endl;
		const Cube *c = dynamic_cast<const Cube*>(&rhs);
		return c ? len == c->len : false;
	}
};

class Sphere :public Shape {
	double rad;
public:
	Sphere(double r) : rad{ r } { std::cout << "Sphere(double r)" << std::endl; };
	double volumn() const {
		std::cout << "double volumn() const" << std::endl;
		return rad*rad*rad*4.18879;
	}
	Shape* clone() const {
		std::cout << "Shape* clone() const" << std::endl;
		return new Sphere(*this);     //default constructor, returns the current object itself,but not address
	}
	void display() const {
		std::cout << "void display() const" << std::endl;
		std::cout << "radius = " << this->rad << std::endl;
	}
	bool operator==(const Shape& rhs) const {   
		std::cout << "bool operator==(const Shape& rhs) const" << std::endl;
		std::cout << "current object is" << this << std::endl;
		const Sphere* c = dynamic_cast<const Sphere*>(&rhs);  //use dynamic_cast template to cast the address received from an object
		                                                      //and return true if the object has the same properties as the current object
		return c ? this->rad == c->rad : false;
	}
};

void displayVolumn(const Shape* shape) {
	std::cout << "void displayVolumn(const Shape* shape)" << std::endl;
	if (shape) {
		std::cout << shape->volumn() << std::endl;   //need to use "->" rather than "." because shape is a pointer?
	}
	else {
		std::cout << "error" << std::endl;
	}
}

Shape* select() {
	std::cout << "Shape* select() " << std::endl;
	Shape* shape;
	double x;
	char c;
	std::cout << "s (sphere), c (cube) : ";
	std::cin >> c;
	if (c == 's') {
		std::cout << "dimension : ";
		std::cin >> x;
		shape = new Sphere(x);   //call constructor of Sphere
	}
	else if (c == 'c') {
		std::cout << "demision : ";
		std::cin >> x;
		shape = new Cube(x);
	}
	else {
		shape = nullptr;
	}
	return shape;
}

/*Dynamic Type Identification*/

class A{
	int x;
public:
	A(int a) : x(a) { std::cout << "A(int a) : x(a)" << std::endl; };
	virtual void display() const {
		std::cout << "virtual void display() const" << std::endl;
		std::cout << x << std::endl;
	}
};

class B : public A {
	int y;
public:
	B(int a, int b) : A(a), y(b) { std::cout << "B(int a, int b) : A(a), y(b)" << std::endl; };
	void display() const {
		std::cout << "void display() const" << std::endl;
		A::display();
		std::cout << y << std::endl;
	}
};

class C :public B {
	int z;
public:
	C(int a =4, int b=6, int c=7) : B(a, b), z(c) { std::cout << "C(int a =4, int b=6, int c=7) : B(a, b), z(c)" << std::endl; };
	void display() const {
		std::cout << "void display() const" << std::endl;
		B::display();
		std::cout << z << std::endl;
	}
};

void show(const A* a) {
	C cref;
	if (typeid(*a) != typeid(cref)) {
		a->display();
	}
	else {
		std::cout << typeid(cref).name() << " objects are private" << std::endl; //typeid(cref).name() returns the type name of cref, which is class C
	}
}

/*LISKOV SUBSTITUTION PRINCIPLE*/

/*Good Design(the derived class doesnt cause a change to the base class*/

class Square {
	double width;
public:
	void setWidth(double w) {
		this->width = w;
	}
	double getWidth() const {
		return this->width;
	}
};

class Rectangle : public Square {
	double height;
public:
	void setHeight(double h) {
		this->height = h;
	}
	double getHeight() const {
		return this->height;
	}
};

void set(Square& s, double d) {
	s.setWidth(d);
}

int main() {
	//Shape* shape = select();
	//Shape* clone = shape->clone(); //clone is a copy of shape, not sharing the same address with shape
	//displayVolumn(shape);
	//displayVolumn(clone);
	//Shape* s1 = select();
	//Shape* s2 = select();
	//if (*s1 == *s2) {
	//	std::cout << "Same" << std::endl;
	//}
	//else {
	//	std::cout << "Differnet" << std::endl;
	//}
	//delete clone;
	//delete shape;
	//delete s1;
	//delete s2;

	//Dynamic type identification

	//A* a[3];
	//a[0] = new A(3);
	//a[1] = new B(2, 5);
	//a[2] = new C(4, 6, 7);
	//for (int i = 0; i < 3; i++) {
	//	show(a[i]);
	//}
	//for (int i = 0; i < 3; i++) {
	//	delete a[i];
	//}

	//LISKOV SUBSTITUTION PRINCIPLE

	Square s;
	s.setWidth(20.0);
	std::cout << "Square : " << s.getWidth() << std::endl;
	set(s, 15.0);
	std::cout << "Square : " << s.getWidth() << typeid(s).name() << std::endl;
	Rectangle r;
	r.setWidth(10.0);
	r.setHeight(30.0);
	std::cout << typeid(r).name() << r.getWidth() << " , " << r.getHeight() << std::endl;
	set(r,25.0);
	std::cout << typeid(r).name() << r.getWidth() << " , " << r.getHeight() << std::endl;
	
}