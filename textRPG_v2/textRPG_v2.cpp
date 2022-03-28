﻿
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

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

#define NAME_SIZE	32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory	tInventory;
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

struct _tagLevelUpStatus
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHPMin;
	int iHPMax;
	int iMPMin;
	int iMPMax;
};

// Exp for level up 
const int g_iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
_tagLevelUpStatus g_tLvUpTable[JOB_END - 1] = {};

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

int SelectJob()
{
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. Knight" << endl;
		cout << "2. Archer" << endl;
		cout << "3. Wizard" << endl;
		cout << "Choose a job : ";
		iJob = InputInt();

		if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

void SetPlayer(_tagPlayer* pPlayer)
{
	cout << "Name : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SelectJob();
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "Knight");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "Archer");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHPMax = 400;
		pPlayer->iHP = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "Wizard");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

_tagMonster CreateMonster(const char* pName, int iAttackMin,
	int iAttackMax, int iArmorMin, int iArmorMax, int iHP,
	int  iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax)
{
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr)
{
	pMonsterArr[0] = CreateMonster("Gobline", 20, 30, 2, 5,
		100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("Troll", 80, 130, 60, 90,
		2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("Dragon", 250, 500, 200, 400,
		30000, 20000, 10, 30000, 20000, 50000);
}

void OutputBattleTag(int iMenu)
{
	switch (iMenu)
	{
	case MT_EASY:
		cout << "********************** Easy ***********************" << endl;
		break;
	case MT_NORMAL:
		cout << "********************** Normal ***********************" << endl;
		break;
	case MT_HARD:
		cout << "********************** Hard ***********************" << endl;
		break;
	}
}

void OutputPlayer(_tagPlayer* pPlayer)
{
	// Output player info.
	cout << "======================== Player ========================" << endl;
	cout << "Name : " << pPlayer->strName << "\tJob : " <<
		pPlayer->strJobName << endl;
	cout << "Level : " << pPlayer->iLevel << "\tExp : " <<
		pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// Add item attack to player. 
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "Attack : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else
	{

		cout << "Attack : " << pPlayer->iAttackMin << " - " <<
			pPlayer->iAttackMax;
	}

	// Add item armor to player. 
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\tArmor : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else
	{

		cout << "\tArmor : " << pPlayer->iArmorMin << " - " <<
			pPlayer->iArmorMax << endl;
	}

	cout << "HP : " << pPlayer->iHP << " / " << pPlayer->iHPMax <<
		"\tMP : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "Equip Weapon : " << pPlayer->tEquip[EQ_WEAPON].strName;

	else
		cout << "Equip Weapon : None";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\tEquip Armor : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

	else
		cout << "\tEquip Armor : None" << endl;

	cout << "Gold : " << pPlayer->tInventory.iGold << " Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster)
{
	// Monster info.
	cout << "======================== Monster ========================" << endl;
	cout << "Name : " << pMonster->strName << "\tLevel : " <<
		pMonster->iLevel << endl;
	cout << "Attack : " << pMonster->iAttackMin << " - " <<
		pMonster->iAttackMax << "\tArmor : " << pMonster->iArmorMin <<
		" - " << pMonster->iArmorMax << endl;
	cout << "HP : " << pMonster->iHP << " / " << pMonster->iHPMax <<
		"\tMP : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "Exp : " << pMonster->iExp << "\tGold : " <<
		pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int OutputBattleMenu()
{
	cout << "1. Attack" << endl;
	cout << "2. Run away" << endl;
	cout << "Choose a menu : ";
	int iMenu = InputInt();
	
	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;
}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster)
{
	int iAttackMin = pPlayer->iAttackMin;
	int iAttackMax = pPlayer->iAttackMax;

	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) +
		pMonster->iArmorMin;

	int iDamage = iAttack - iArmor;

	iDamage = iDamage < 1 ? 1 : iDamage;

	// Monster HP after attacked.
	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << " deals " << iDamage <<
		" damage to " << pMonster->strName << endl;

	// if Monster dies.
	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << " is dead." << endl;

		pPlayer->iExp += pMonster->iExp;
		int iGold = (rand() % (pMonster->iGoldMax = pMonster->iGoldMin + 1) +
			pMonster->iGoldMin);
		pPlayer->tInventory.iGold += iGold;

		cout << "You gained " << pMonster->iExp << " EXP" << endl;
		cout << "You gained " << iGold << " Gold" << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		// Level up check
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			// Exp after level up
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			// Level up
			++pPlayer->iLevel;

			cout << "Level Up" << endl;

			// Ability up
			// Get Job index
			int iJobIndex = pPlayer->eJob - 1;
			int iHPUp = rand() % (g_tLvUpTable[iJobIndex].iHPMax - g_tLvUpTable[iJobIndex].iHPMin + 1) +
				g_tLvUpTable[iJobIndex].iHPMin;
			int iMPUp = rand() % (g_tLvUpTable[iJobIndex].iMPMax - g_tLvUpTable[iJobIndex].iMPMin + 1) +
				g_tLvUpTable[iJobIndex].iMPMin;

			pPlayer->iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;

			pPlayer->iHPMax += iHPUp;
			pPlayer->iMPMax += iMPUp;

			// Full HP and MP after Level up
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;

		} 
		return;
	}

	// Monster attack player.
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) +
		pMonster->iAttackMin;

	int iArmorMin = pPlayer->iArmorMin;
	int iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) +
		iArmorMin;

	iDamage = iAttack - iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;


	// Plyaer HP after attacked.
	pPlayer->iHP -= iDamage;
	cout << pMonster->strName << " deals " << iDamage <<
		" damage to " << pPlayer->strName << endl;


	// if player dies.
	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << " is dead." << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << "You lost " << pMonster->iExp << " EXP" << endl;
		cout << "You lost " << iGold << " Gold" << endl;

		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;

	}
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr,
	int iMenu)
{
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true)
	{
		system("cls"); 
		OutputBattleTag(iMenu);
		
		// Output player
		OutputPlayer(pPlayer);

		// Output monster
		OutputMonster(&tMonster);

		switch (OutputBattleMenu())
		{
		case BATTLE_ATTACK:
			Battle(pPlayer, &tMonster); 
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

int OutputMapMenu()
{
	system("cls");

	cout << "********************** Map ***********************" << endl;
	cout << "1. Easy" << endl;
	cout << "2. Normal" << endl;
	cout << "3. Hard" << endl;
	cout << "4. Back" << endl;
	cout << "Choose Map : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;

	return iMenu;
}

// Handles map loops
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr)
{
	bool bLoop = true;
	while (bLoop)
	{
		int iMenu = OutputMapMenu();

		if (MT_BACK == iMenu)
			return;

		// Start battle
		RunBattle(pPlayer, pMonsterArr, iMenu);
	}
}

_tagLevelUpStatus CreateLvUpStatus(int iAttackMin, int iAttackMax,
	int iArmorMIn, int iArmorMax, int iHPMin, int iHPMax,
	int iMPMin, int iMPMax)
{
	_tagLevelUpStatus tStatus = {};

	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMIn;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHPMin = iHPMin;
	tStatus.iHPMax = iHPMax;
	tStatus.iMPMin = iMPMin;
	tStatus.iMPMax = iMPMax;

	return tStatus;
}

int main()
{
	srand((unsigned int)time(0));
	
	// Make player
	_tagPlayer	tPlayer = {};

	// Setting player info
	SetPlayer(&tPlayer);

	// Make monster
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	SetMonster(tMonsterArr); 

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10,
		8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15,
		5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20,
		3, 7, 20, 40, 50, 100);

	bool bLoop = true;

	while (bLoop)
	{
		switch (OutputMainMenu())
		{
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);
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




























