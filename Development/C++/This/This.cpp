#include <iostream>

class ThisTest{
private:
	int a;
public:
	void call();
	void setA(int a);
	void printA();
};

void ThisTest::call(){
	setA(5);
}

void ThisTest::setA(int a){
	this->a = a;
}

void ThisTest::printA(){
	std::cout << this->a << "\n";
}

int main(int argc, char * argv[]){
	ThisTest t;
	t.call();
	t.printA();
}
