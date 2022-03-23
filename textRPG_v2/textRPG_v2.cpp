
#include <iostream>
#include <time.h>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

// Check input number
// return input if input is right
// return INT_MAX if input is wrong number
int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; 
	}

	return iInput;
}
 
int OutputMainMenu()
{
	system("cls");
	cout << "********************** Lobby ***********************" << endl;
	cout << "1. Map" << endl;
	cout << "2. Store" << endl;
	cout << "3. Invetory" << endl;
	cout << "4. Exit" << endl;
	cout << "Choose a menu : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}
int main()
{
	srand((unsigned int)time(0));

	bool bLoop = true;

	while (bLoop )
	{
		switch (OutputMainMenu())
		{
		case MM_MAP:
			break;
		case MM_STORE:
			break;
		case MM_INVENTORY:
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}
	return 0;
}




























