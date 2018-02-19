#include <iostream>
#include "Course.h"
#include "Room.h"


Course::Course(const char* n, int c) :
	name{ n }, code{ c } {}
void Course::book(Room& r) {
	if (room) room->unbook();
	room = &r;
}
void Course::unbook() {
	room = nullptr;
}
const char* Course::get() const {
	return name.get();
}
const int Course::getCode() const {
	return this->code;
}
void Course::display() const {
	std::cout <<
		(room ? room->get() : "*****")
		<< ' ' << code << ' ' << name.get()
		<< std::endl;
}
//.