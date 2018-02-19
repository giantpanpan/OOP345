#include<iostream>
#include <typeinfo>
#include <cstring>
/*Function Template*/


template<typename T>
void swap(T& a, T& b) {
	T c;
	c = a;
	a = b;
	b = c;
}

template<typename T>
T maximum(T a, T b) {
	return a > b ? a : b;
}

//Specialization: defines an exception to a template definition
//"template<typename T>" applies to all fundermental type, but not to other types, like char*
//A specialization does not use template parameters, but declares specific types explcitly 

template<>
char* maximum<char*>(char* a, char* b) {
	return std::strcmp(a, b) > 0 ? a : b;
}

//Class Templates

template <typename T = int, int size = 50>      //Default template parameter values 
									       	    //int size is the non-type template parameter
class Array {
	T a[50];
	unsigned n;
	T dummy;
	static unsigned count;
public:
	Array() : n{ 0u }, dummy{ 0 } 
	{ std::cout << "Array() : n{ 0u }, dummy{ 0 }" << std::endl; 
	this->count++;
	}
	T& operator[](unsigned i) {
		std::cout << "int& operator[](unsigned i)" << std::endl;
		return i < 50u ? a[i] : dummy;
	}
	static unsigned cnt() { return count; }
};

template <typename T = int, int size = 50>
unsigned Array<T,size>::count = 0u;



int main(int argc, char* argv[]) {
	//std::cout << "argc = " << argc << std::endl;   //argc = 1 + 4, 1 is for program name 
	//if (argc > 4) {
	//	double a = atof(argv[1]);    //typeid(argv[i].name() is "char *". Using atof() to convert string(char *) to number
	//	double b = atof(argv[2]);
	//	long d = atol (argv[3]);
	//	std::cout << typeid(argv[3]).name() << std::endl;
	//	long e = atol(argv[4]);
	//	char* g = argv[5];
	//	char* h = argv[6];
	//	swap(a, b);
	//	std::cout << "Swapped values are " << a << " and " << b << std::endl;
	//	swap(d, e);
	//	std::cout << "Swapped values are " << d << " and " << e << std::endl;

	//	double c = maximum<int>(a, b);
	//	std::cout << "Greater of " << a << ", " << b << " is " << c << std::endl;

	//	const char* f = maximum(g, h);
	//	std::cout << "Greater of " << g << ", " << h << " is " << c << std::endl;
	//}


	//std::cout << maximum(1, 2) << std::endl;
	//std::cout << maximum(1.5, 2.5) << std::endl;

	//Class Template

	Array<> a, b;  //complier replaces type T with the arguement sepcified in the call to the Array
						  //template.
	for (int i = 0; i < 9; i++) {
		a[i] = i*i;
	}
	b = a;
	for (int i = 0; i < 9; i++) {
		std::cout << b[i] << " ";
	}
	std::cout << std::endl;

	Array<>s, t;
	Array<double>u;
	Array<int, 40> v;
	std::cout << Array<>::cnt() << std::endl;          //instance of class Array<>
	std::cout << Array<double>::cnt() << std::endl;    //instance of class Array<double>
	std::cout << Array<int, 40>::cnt() << std::endl;   //instance of class Array<int,40>

	//Each class is a separate instance of template Array
}

