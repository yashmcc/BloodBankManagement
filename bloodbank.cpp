#include <iostream>
#include <string>
#include "bloodbankdef.h"
using namespace std;

string accept_id();
string accept_name();
string accept_bgrp();

int main()
{
	Bloodbank bb;
	int ch;
	
	cout<<"BLOOD BANK";

	do{
		cout << "\n1. Insert a new record\n";
		cout << "2. Delete an existing record\n";
		cout << "3. Display all records\n";
		cout << "4. Search by ID\n";
		cout << "5. Search By Blood group\n";
		cout << "6. Exit\n\n";
		cout << "Enter your choice : ";cin >> ch;
		switch (ch)
		{
		case 1:
		{
			string name, id, bgrp;
			name = accept_name();
			id = accept_id();
			bgrp = accept_bgrp();
			bb.Insert_Record(id, name, bgrp);
			break;
		}

		case 2:
		{
			string id;
			id = accept_id();
			bb.Delete_Record(id);
			cout << "\nThe record has been deleted !\n";
			break;
		}

		case 3:
		{
			bb.ct = 0;
			if (bb.Is_Empty())
			{
				cout << endl
					 << "\nNo records\n";
				break;
			}
			bb.Display_Records(bb.root);
			cout << endl;
			break;
		}

		case 4:
		{
			string id;
			id = accept_id();
			bb.search_key(id);
			break;
		}

		case 5:
		{
			string search_bgrp;
			search_bgrp = accept_bgrp();

			if (!bb.bgrp_found(search_bgrp))
				cout << "\nNo donors with Blood group " << search_bgrp << endl;

			else
			{
				cout << "\n*******************\n";
				cout << "Name\t\tID" << endl;
				cout << "*******************\n";
				bb.search_by_bgrp(search_bgrp);

				cout << "*******************\n";
			}
			break;
		}
		}

	} while (ch != 6);
	cout << "\nExiting program!\n";
	return 0;
}

string accept_id()
{
	string id;
	cout << endl
		 << "Enter the ID : ";
	getline(cin >> ws, id);
	return id;
}

string accept_name()
{
	string name;
	cout << endl
		 << "Enter the donor's name : ";
	getline(cin >> ws, name);
	return name;
}

string accept_bgrp()
{
	string bgrp;
	cout << endl
		 << "Enter the donors's blood group : ";
	getline(cin >> ws, bgrp);
	return bgrp;
}
