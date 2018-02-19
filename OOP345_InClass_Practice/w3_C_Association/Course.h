#include "name.h"
class Room;

class Course {
	Name name;
	int code;
	Room* room = nullptr;
public:
	Course(const char*, int);
	void book(Room&);
	void unbook();
	const char* get() const;
	const int getCode() const;
	void display() const;
	//...
};
