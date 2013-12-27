#include "LNC.h"
using namespace std;

void Display();


int main()
{

	Display();
	string input1;
	string input2;


	cout << "\t\tJustin's Large Number Collider" << endl;
	cout << "Enter first number: ";
	cin >> input1;
	cout << "Enter second number: ";
	cin >> input2;
	cout << "The results: " << endl;
	LargeNumber oLN1(input1);
	LargeNumber oLN2(input2);
	cout << (oLN1 + oLN2).ToString() << endl;

	cout << "\n\n\n" << endl;
	cout << "Nuclear Status: " << endl;
	cout << "Penguins and Engie Union" << endl;
	cout << "This was created as part of an ongoing research to crunch big numbers." << endl;


	system("PAUSE");
	return 0;
}


void Display()
{

	cout << "<!--......................................................" << endl;
	cout << "	.........................................................." << endl;
	cout << "	.........................................................." << endl;
	cout << "	.@@...@@..@@@@@@..@@.......@@@@....@@@@...@@...@@..@@@@@@." << endl;
	cout << "	.@@...@@..@@......@@......@@..@@..@@..@@..@@@.@@@..@@....." << endl;
	cout << "	.@@.@.@@..@@@@....@@......@@......@@..@@..@@.@.@@..@@@@..." << endl;
	cout << "	.@@@@@@@..@@......@@......@@..@@..@@..@@..@@...@@..@@....." << endl;
	cout << "	..@@.@@...@@@@@@..@@@@@@...@@@@....@@@@...@@...@@..@@@@@@." << endl;
	cout << "	.........................................................." << endl;
	cout << "	..................Justin Yang............................." << endl;
	cout << "	.........................................................." << endl;
	cout << "	.........................................................." << endl;
	cout << "	......................................Micropenguin.net-- >" << endl;



}