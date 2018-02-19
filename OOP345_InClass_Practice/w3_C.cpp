#include<cstring>
#include<iostream>


class Name {
	char* name = nullptr;
public:
	Name(const char* n) {
		std::cout << "Name(const char* n)" << std::endl;
		this->name = new char[std::strlen(n) + 1];
		std::strcpy(this->name, n);
	}
	Name(const Name& rhs) {
		std::cout << "Name(const Name& rhs)" << std::endl;
		*this = rhs;                           //direct call
	}
	Name& operator=(const Name& rhs) {
		if (this != &rhs) {
			std::cout << "Name& operator=(const Name& rhs)" << std::endl;
			delete this->name;
			this->name = new char[std::strlen(rhs.name) + 1];
			std::strcpy(this->name, rhs.name);
		}
		return *this;
	}
	~Name() {
		std::cout << "delete[] name;" << std::endl;
		delete[] name;
	}
	const char* get() const {
		std::cout << "const char* get() const;" << std::endl;
		return this->name;
	}
	void set(const char* rhs) {
		std::cout << "void set(const char* rhs)" << std::endl;
		delete[] name;
		name = new char[std::strlen(rhs) + 1];
		std::strcpy(this->name, rhs);
	}
};


//Composition - SubObject Version
/*
> the composer object owns the component object
> one class completely contains another class and determines its lifetime
> has a relationsip between classes that implements complete ownership
> more flexiable than inheritance
> update to the component class need not affect the composer class
*/

class Person_S {
	Name name;              //subobject
	int age;
public:
	Person_S(const char* n, int a) : name{ n }, age{ a } {
		std::cout << "Person_S(const char* n, int a) : name{ n }, age{ a }" << std::endl;
	};
	void display() const {
		std::cout << "void display() const" << std::endl;
		std::cout << age << " " << name.get() << std::endl;
	}
	void set(const char* n) {
		std::cout << "void set(const char* n)" << std::endl;
		name.set(n);
	}
};

//Composition - Pointer Version
class Person_P {
	Name* name = nullptr;
	int age;
public:
	Person_P(const char* n, int a) {
		std::cout << "Person_P(const char* n, int a)" << std::endl;
		this->name = new Name{ n };
		this->age = a;
	}
	Person_P(const Person_P& rhs) {
		std::cout << "Person_P(const Person_P& rhs)" << std::endl;
		*this = rhs;
	}

	Person_P& operator=(const Person_P& rhs) {
		std::cout << "Person_P& operator=(const Person_P& rhs))" << std::endl;
		if (this != &rhs) {
			delete name;
			name = new Name(*rhs.name);
			age = rhs.age;
		}
		return *this;
	}

	~Person_P() {
		std::cout << "~Person_P()" << std::endl;
		delete name;
	}

	void display() const {
		std::cout << "void display() const" << std::endl;
		std::cout << age << " " << name->get() << std::endl;
	}

	void set(const char* n) {
		std::cout << "void set(const char* n)" << std::endl;
		name->set(n);
	}
};

//Aggregation
/*
> a conposition that does not manage the creation or destruction of the objects it uses
> the responsibility for creating and destroying the objects lies outside the aggregator type
> the aggregator is complete whether or not any of the objects that it uses exists
> the objects survive the destruction of aggretator
> Member functions added to the aggregatee type do not require forwarding member functions in aggregator type
*/

//Aggregation example
/*
The club has or may have members, but can exist without any.
A name can be removed from its list of members before the club is disbanded
and the name is not destroyed if the club is disbanded
*/


//Aggregation - club
class Name;
const int M = 50;

class Club {
	const Name* name[M]{};
	int m = 0;
public:
	Club& operator+=(const Name& n) {
		std::cout << "Club& operator+=(const Name& n)" << std::endl;
		if (m < M) {
			name[m++] = &n;
		}
		return *this;
	}
	Club& operator-=(const Name& n) {
		std::cout << "Club& operator-=(const Name& n)" << std::endl;
		bool found = false;
		int i;
		for (i = 0; i < m && !found; i++) {
			if (!std::strcmp(this->name[i]->get(), n.get())) {
				found = true;
			}
		}
		if (found) {
			for (; i < m; i++) {
				name[i - 1] = name[i];
			}
			if (m) {
				name[m - 1] = nullptr;
				m--;
			}
		}
		return *this;
	}
	void display() const {
		std::cout << "void display() const" << std::endl;
		for (int i = 0; i < m; i++) {
			std::cout << name[i]->get() << std::endl;
		}
	}
	~Club() {
		delete[] this->name;
	}
};


//Association
/*
> an association is a service relationship and does not invlove onwership of one type by another
> Each type is wholly independent and complete without the related type
> member function added too an association type do not require forwarding member functions in the related type
*/

//Association example - Course and Room
/*
> a course uses a room and a room booked for a course
> both exist independently of one other
> a room can be booked for a course and a course can be assignment to a room
> Neigher is destroyed when the other is destroyed
*/

class Room;

class Course {
	Name name;
	int code;
	Room* room = nullptr;
public:
	Course(const char* n, int c) : name{ n }, code{ c } {};
	void book(Room& r) {
		if (room) room->unbooked();
		room = &r;
	}
	void unbooked() {
		room = nullptr;
	}
	const char* get() const {
		return this->name.get();
	}
	void display() const {
		std::cout << (room ? room->get() : "****") << " " << code << " " << name.get() << std::endl;
	}
};


class Course;

class Room {
	Name name;                            //SubObject composition of class Name
	Course* course = nullptr;
public:
	Room(const char* n) : name{ n } {};
	void book(Course& c) {
		if (this->course != nullptr) {
			this->course->unbooked();
		}
		this->course = &c;
	}
	void unbooked() {
		course = nullptr;
	}
	const char* get() const {
		return name.get();
	}
	void display() const {
		std::cout << name.get() << " " << (course ? course->get() : "avaliable") << std::endl;
	}
};




class Course;
class Name;
class Room;

void book(Course& c, Room& r) {
	c.book(r);
	r.book(c);
}

int main() {
	std::cout << "--------------------------------Composition--------------------------------" << std::endl;
	//Person_P p("Harry", 23);
	//Person_P q = p;
	//p.display();
	//q.display();
	//q.set("Lawrence");
	//p.display();
	//q.display();
	//p = q;
	//p.display();

	//Person_S s("Jerry", 25);
	//Person_S t = s;                            //only call copy constructor and copy assignment operator on Name class
	//s.display();
	//t.display();
	//t.set("John");
	//s.display();
	//t.display();
	//s = t;
	//s.display();

	std::cout << "--------------------------------Aggregations--------------------------------" << std::endl;
	//Name jane("Jane");
	//Name john("John");
	//Name alice("Alice");
	//Name frank("Frank");
	//Name nancy("Nancy");
	//Club c;
	//c += jane;
	//c += john;
	//c += alice;
	//c += frank;
	//c += nancy;
	//c.display();
	//c -= alice;
	//c -= john;
	//c -= nancy;
	//c.display();
	//std::cout << alice.get() << std::endl;    //Alice still exist even its deleted from Club name list

	std::cout << "--------------------------------Association--------------------------------" << std::endl;

	Room t2108("T2108");
	Room t2109("T2109");
	Room t2110("T2110");
	Course btp105("Intro to Programming", 105);
	Course btp205("Intro to O-O Prg", 205);
	Course btp305("O-O Programming", 305);
	btp105.display();
	btp205.display();
	btp305.display();
	t2108.display();
	t2109.display();
	t2110.display();
	book(btp205, t2110);
	book(btp305, t2108);
	btp105.display();
	btp205.display();
	btp305.display();
	t2108.display();
	t2109.display();
	t2110.display();
	book(btp205, t2108);
	book(btp305, t2109);
	btp105.display();
	btp205.display();
	btp305.display();
	t2108.display();
	t2109.display();
	t2110.display();
}