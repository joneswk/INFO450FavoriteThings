// ConsoleApplication37.cpp : Defines the entry point for the console application.
//

// ConsoleApplication34.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;

class Pizza
{
	string PizzaName;
	string PizzaToppings;
	string PizzaPlace;
	int	PizzaRating;

public:
	Pizza();
	Pizza(string name, string toppings, string place, int rating);
	void CapturePizzaItem();
	void ShowPizzaItem();
	int SavePizzaItem(ofstream &outfile);
};

class PizzaList
{
	Pizza **list;
	int numOfPizzas;
	int listsize;
	int ReallocateArray();
public:
	PizzaList();
	~PizzaList();
	void GetUserInput();
	void ShowPizzaList();
	int SavePizzaList(string filename);
	int ReadPizzaList(string filename);
};

// default constructor - initialize empty
Pizza::Pizza()
{
	PizzaName = ""; PizzaToppings = ""; PizzaPlace = "";  PizzaRating = 0;
}
// overload constructor inialize w/ values
Pizza::Pizza(string name, string toppings, string place, int rating)
{
	PizzaName = name;
	PizzaToppings = toppings;
	PizzaPlace = place;
	PizzaRating = rating;
}
// Capture Item from end users
void Pizza::CapturePizzaItem()
{
	cout << "What is the name of your Favorite Pizza? -->";
	getline(cin, PizzaName);
	cout << "What toppings are on your Favorite Pizza?  -->";
	getline(cin, PizzaToppings);
	cout << "Where can I get your favorite pizza?  -->";
	getline(cin, PizzaPlace);
	cout << "Rate your favorite pizza (From # 1 - 10)? -->";
	cin >> PizzaRating;
	cin.ignore();
	cin.clear();
}
// Display item to console
void Pizza::ShowPizzaItem()
{
	cout << "------------------------" << endl;
	cout << "Name of Favorite Pizza: " << PizzaName << endl;
	cout << "Toppings On Favorite Pizza : " << PizzaToppings << endl;
	cout << "Place To Get Favorite Pizza: " << PizzaPlace << endl;
	cout << "Pizza Rating: " << PizzaRating << endl;
}
// Save inventory item to file given input file stream
int Pizza::SavePizzaItem(ofstream& outfile)
{
	if (outfile.is_open())
	{
		outfile << PizzaName << "|" << PizzaToppings << "|" << PizzaPlace << "|" << PizzaRating << endl;
		return 0;
	}
	else
		return WRITEERROR;
	return 0;
}

// Inventory LIst constructor -allocate default space for array
PizzaList::PizzaList()
{
	list = new Pizza*[ARRAYSIZE];
	numOfPizzas = 0;
	listsize = ARRAYSIZE;
}
// deconstructor - free allocated memory
PizzaList::~PizzaList()
{
	for (int i = 0; i < numOfPizzas; i++)
	{
		delete list[i];
	}
	delete[]list;
}
// Reallocate memory if already at array capacity
int PizzaList::ReallocateArray()
{
	Pizza**temp;
	temp = new Pizza*[listsize + ARRAYSIZE];
	listsize = listsize + ARRAYSIZE;
	for (int i = 0; i < numOfPizzas; i++)
	{
		temp[i] = list[i];
	}
	delete[]list;
	list = temp;
	return 0;
}

// get user input for the list
void PizzaList::GetUserInput()
{
	string answer = "Y";
	bool check = true;
	cout << "Thank you for visiting Fav Pizza Survey!!!" << endl;
	cout << "Would you like to complete a survey about your favorite pizza? Enter (Y)es or (N)o" << endl;
	getline(cin, answer);
	while (answer == "Y" || answer == "y")
	{
		list[numOfPizzas] = new Pizza();
		list[numOfPizzas]->CapturePizzaItem();

		for (int i = 0; i < numOfPizzas; i++)
		{
			if (list[numOfPizzas] = list[i])
			{
				check = false;
			}
			i++;
		}

		if (check == false)
		{
			cout << "Error: Duplicate entered" << endl;
			delete list[numOfPizzas];
			cout << "enter another pizza (Y)es or (N)o?" << endl;
			getline(cin, answer);
			check = true;
			continue;
		}
		numOfPizzas++;
		cout << "enter another item Y/N?" << endl;
		getline(cin, answer);
	}

}
// Show list to the console
void PizzaList::ShowPizzaList()
{
	for (int i = 0; i < numOfPizzas; i++)
		list[i]->ShowPizzaItem();
}
// Save entire list to file, given full-path file name
int PizzaList::SavePizzaList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (output)
	{
		for (int i = 0; i < numOfPizzas; i++)
		{
			list[i]->SavePizzaItem(output);
		}
		output.close();
	}
	else
	{
		return WRITEERROR;
	}
	return 0;
}
// Read inventory list from a file, given full-path filename
// If file not found or error, return error code
int PizzaList::ReadPizzaList(string filename)
{
	string iname, itoppings, iplace, irating;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading " << endl;
		return READERROR;
	}
	if (numOfPizzas == listsize)
	{
		ReallocateArray();
	}

	while (!infile.eof())
	{
		getline(infile, iname, '|');
		if (!iname.empty())
		{
			getline(infile, itoppings, '|');
			getline(infile, iplace, '|');
			getline(infile, irating, '|');
			int rating = stoi(irating);
			list[numOfPizzas] = new Pizza(iname, itoppings, iplace, rating);
		}
	}

	infile.close();
	return 0;

}


int main()
{
	string filename = "c:\\users\\Admin\\documents\\ConsoleApplication34.txt";
	cout << "What is the full path of the file you would like to use?" << endl;
	string answer;
	getline(cin, answer);
	PizzaList myPizza;
	int error;
	error = myPizza.ReadPizzaList(filename);
	if (error)
	{
		cout << "Cannot read Pizza Survey - continue creating new list? (Y)es or (N)o -->";
		getline(cin, answer);
		if (answer != "Y" && answer != "y")
		{
			return 1;
		}
	}
	myPizza.GetUserInput();
	myPizza.SavePizzaList(filename);
	myPizza.ShowPizzaList();

	return 0;
}


