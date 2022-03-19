#include <iostream>
#include <string>
using namespace std;
const int nUsers = 10;

int nLines[nUsers], iDs[nUsers], choice, currentLine, menuPages = 1, functions, currentUser = -1, currentUser2 = -1, choosenID, cardCounter = 0;
float amount, pType;
long long serialNumber;
bool isExit = true, isCheck = true, isMenuCheck = true;
string userPassword, pass[nUsers], phoneNums[30];

struct RenewalDate
{
	int day = 0, month = 0, year = 0;
};

struct StartDate
{
	int day = 0, month = 0, year = 0;
};

struct Lines
{
	string phoneNumber;
	float packageType = 0;
	float balance = 0;
	StartDate sDate;
	RenewalDate rDate;
};

struct UserData
{
	int iD = 0;
	string email, name, password, address;
	Lines line[3];
}user[nUsers];

void SignUp()
{
	//Insert data to the next pos in user array
	currentUser++;
	currentUser2++;
	currentUser = currentUser2;

	cout << "\t\t Welcome To Our Company Application\n";
	cout << "\t\tPlease fill the following to Sign Up\n";
	cout << "\t\t************************************\n";
	cout << "Enter your Name: ";
	cin >> user[currentUser].name;
	cout << "Enter your E-mail: ";
	cin >> user[currentUser].email;
	cout << "Enter your Address: ";
	cin >> user[currentUser].address;
	//ID
	cout << "Enter your ID: ";
	cin >> user[currentUser].iD;
	while (isCheck)
	{
		while (user[currentUser].iD <= 0)
		{
			cout << "Wronge ID !\n";
			cout << "Pleas enter another ID: ";
			cin >> user[currentUser].iD;
		}
		for (int i = 0;i < 9;i++)
		{
			if (user[currentUser].iD == iDs[i])
			{
				cout << "This ID has been already taken\n";
				break;
			}
			if (i == 8)
			{
				isCheck = false;
			}
		}//Number has been already taken
		if (isCheck)
		{
			cout << "Pleas enter another ID: "; 
			cin >> user[currentUser].iD;
		}
	}
	isCheck = true;
	//Enter the id into Log In-checking array
	iDs[currentUser] = user[currentUser].iD;
	//Password
	cout << "Enter your Password: "; 
	cin >> user[currentUser].password;
	pass[currentUser] = user[currentUser].password;
	//Lines
	cout << "How many Lines? ";
	cin >> nLines[currentUser];
	while (nLines[currentUser] <= 0 || nLines[currentUser] > 3)
	{
		if (nLines[currentUser] > 3)
		{
			cout << "Sorry, maximum number of Lines is 3\n";
			cout << "How many Lines? ";
			cin >> nLines[currentUser];
		}
		else if (nLines[currentUser] <= 0)
		{
			cout << "Sorry, minimum number of Lines is 1\n";
			cout << "How many Lines? "; 
			cin >> nLines[currentUser];
		}
	}
	for (int i = 0;i < nLines[currentUser];i++)
	{
		cout << "Enter the data for Line " << i + 1 << ":\n";
		//Phone Number
		while (isCheck)
		{
			cout << "Enter your Phone Number: ";
			cin >> user[currentUser].line[i].phoneNumber;
			for (int k = 0;k < 15; k++)
			{
				if (user[currentUser].line[i].phoneNumber == phoneNums[k])
				{
					cout << "This number has been already registered\n";
					break;
				}
				if (k == 14)
				{
					isCheck = false;
					break;
				}
			}
		}
		isCheck = true;
		phoneNums[currentUser] = user[currentUser].line[i].phoneNumber;
		//Balance
		cout << "Enter your Current Balance: ";
		cin >> user[currentUser].line[i].balance;
		while (user[currentUser].line[i].balance < 0)
		{
			cout << "Invalid Balance\n";
			cout << "Please enter your Current Balance: ";
			cin >> user[currentUser].line[i].balance;
		}
		//Package Type
		cout << "Enter your Package Type: ";
		cin >> user[currentUser].line[i].packageType;
		while (user[currentUser].line[i].packageType < 10)
		{
			cout << "Sorry, minimum number of Package Type is 10\n";
			cout << "Please enter your Package Type: ";
			cin >> user[currentUser].line[i].packageType;
		}
		//Start Date
		cout << "Enter your Start Date: ";
		cin >> user[currentUser].line[i].sDate.day >> user[currentUser].line[i].sDate.month >> user[currentUser].line[i].sDate.year;
		//Start date shoudn't be more than day(30), month(7), year(2020)
		while (user[currentUser].line[i].sDate.day > 30 || user[currentUser].line[i].sDate.month > 7 || user[currentUser].line[i].sDate.year > 2020)
		{
			cout << "Invalid Date\n";
			cout << "Please enter your Start Date correctly: ";
			cin >> user[currentUser].line[i].sDate.day >> user[currentUser].line[i].sDate.month >> user[currentUser].line[i].sDate.year;
		}
		//Start date shoudn't be less than day(1), month(1), year(2020)
		while (user[currentUser].line[i].sDate.day < 1 || user[currentUser].line[i].sDate.month < 1 || user[currentUser].line[i].sDate.year < 2020)
		{
			cout << "Invalid Date\n";
			cout << "Please enter your Start Date correctly: ";
			cin >> user[currentUser].line[i].sDate.day >> user[currentUser].line[i].sDate.month >> user[currentUser].line[i].sDate.year;
		}
		//Renewal Date
		cout << "Enter your Renewal Date: ";
		cin >> user[currentUser].line[i].rDate.day >> user[currentUser].line[i].rDate.month >> user[currentUser].line[i].rDate.year;
		while ((user[currentUser].line[i].rDate.day != user[currentUser].line[i].sDate.day) || (user[currentUser].line[i].rDate.month != (user[currentUser].line[i].sDate.month + 1)) || (user[currentUser].line[i].rDate.year != user[currentUser].line[i].sDate.year))
		{
			cout << "Invalid Date,Renewal Date must be greater than Start Date by 1 month (30 Days)\n";
			cout << "Please enter your Renewal Date correctly: ";
			cin >> user[currentUser].line[i].rDate.day >> user[currentUser].line[i].rDate.month >> user[currentUser].line[i].rDate.year;
		}
		if ((nLines[currentUser] == 2 && i == 0) || (nLines[currentUser] == 3 && i == 1))
		{
			cout << "\t\t********************\n";
		}
	}
	menuPages = 3;
}

void LogIn()
{
	cout << "1. Log In\n";
	cout << "2. New User? Sign Up\n";
	cout << "Select your choice: "; 
	cin >> choice;
	while (choice > 2 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Please select your choice: ";
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		menuPages = 0;
		functions = 5;
		break;
	case 2:
		menuPages = 1;
		break;
	}
}

void ID()
{
	cout << "\t\t********************\n";
	int userID;
	while (isCheck)
	{
		cout << "Please enter your ID: ";
		cin >> userID;
		//ID <=0
		while (userID <= 0)
		{
			cout << "Wronge ID !\n";
			cout << "Pleas enter another ID: "; 
			cin >> userID;
		}
		for (int i = 0;i < 10;i++)
		{
			if (userID == iDs[i])
			{
				//ID exist
				isCheck = false;
				functions = 6;
				//index of this user's ID
				choosenID = i;
				break;
			}
		}
		if (isCheck)
		{
			//ID does not exist
			cout << "Wronge ID !\n\n";
			cout << "1. Enter another ID\n";
			cout << "2. Sign Up\n";
			cout << "3. Exit\n";
			cout << "Select your choice: ";
			cin >> choice;
			while (choice > 3 || choice < 1)
			{
				cout << "Invalid choice !\n";
				cout << "Please select your choice: "; 
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				break;
			case 2:
				menuPages = 1;
				functions = 0;
				isCheck = false;
				break;
			case 3:
				menuPages = 0;
				functions = 0;
				isCheck = false;
				isExit = false;
				break;
			}
		}
	}
	isCheck = true;
}

void PASSWORD()
{
	while (isCheck)
	{
		cout << "Please enter your Password: ";
		cin >> userPassword;
		if (userPassword == pass[choosenID])
		{
			//Correct Password
			isCheck = false;
			isMenuCheck = true;
			break;
		}
		else
		{
			//Incorrect Password
			cout << "Wronge Password !\n\n";
			cout << "1. Re-enter Password\n";
			cout << "2. Enter another ID\n";
			cout << "3. Sign Up\n";
			cout << "4. Exit\n";
			cout << "Select your choice: "; 
			cin >> choice;
			while (choice > 4 || choice < 1)
			{
				cout << "Invalid choice !\n";
				cout << "Please select your choice: "; 
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				isMenuCheck = false;
				break;
			case 2:
				isMenuCheck = false;
				functions = 5;
				isCheck = false;
				break;
			case 3:
				menuPages = 1;
				functions = 0;
				isMenuCheck = false;
				isCheck = false;
				break;
			case 4:
				menuPages = 0;
				functions = 0;
				isMenuCheck = false;
				isCheck = false;
				isExit = false;
				break;
			}
		}
	}
	isCheck = true;
	if (isMenuCheck)
	{
		currentUser = choosenID;
		//Go to Menu of this user
		functions = 0;
		menuPages = 3;
	}
}

void Menu()
{
	cout << "\t\t********************\n";
	cout << "\t\tWelcome, " << user[currentUser].name << " !\n";
	cout << "\t\t********************\n";
	cout << "1. Your Balance\n";
	cout << "2. Your Package Type\n";
	cout << "3. Make a Call / Send a Message\n";
	cout << "4. Transfer Balance\n";
	cout << "5. New Account\n";
	cout << "6. Log Out\n";
	cout << "7. Exit\n";
	cout << "Select your choice: "; 
	cin >> choice;
	while (choice > 7 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Please select your choice: "; 
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		menuPages = 4;
		break;
	case 2:
		menuPages = 5;
		break;
	case 3:
		menuPages = 6;
		break;
	case 4:
		menuPages = 7;
		break;
	case 5:
		menuPages = 1;
		break;
	case 6:
		menuPages = 2;
		break;
	case 7:
		menuPages = 0;
		isExit = false;
		break;
	}
	cout << "\t\t********************\n";
}

void Balance()
{
	//Viewing the balance of this user's lines
	for (int i = 0;i < nLines[currentUser];i++)
	{
		cout << "Your current Balance for line " << i + 1 << " is " << user[currentUser].line[i].balance << " LE" << endl << endl;
	}
	cout << "1. Recharge your Balance\n";
	cout << "2. Main Menu\n";
	cout << "Select your choice: "; 
	cin >> choice;
	while (choice > 2 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Please select your choice: "; 
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		functions = 1;
		menuPages = 0;
		break;
	case 2:
		menuPages = 3;
		break;
	}
}

void Recharge()
{
	cout << "\t\t********************\n";
	if (nLines[currentUser] > 1)
	{
		cout << "What line do you want to recharge? ";
		cin >> currentLine;
		while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
		{
			cout << "Invalid number !\n";
			cout << "What line do you want to recharge? ";
			cin >> currentLine;
		}
	}
	else
	{
		currentLine = nLines[currentUser];
	}
	cout << "Enter the card serial number: ";
	cin >> serialNumber;
	while (true)
	{
		while (serialNumber <= 0)
		{
			cout << "Invalid serial number, it mustn't be less than or equal 0\n";
			cout << "Please enter the serial number correctly: ";
			cin >> serialNumber;
		}
		while (serialNumber > 0)
		{
			serialNumber /= 10;
			cardCounter++;
		}
		//Serial number must be 15 number
		if (cardCounter == 15)
		{
			cardCounter = 0;
			break;
		}
		else
		{
			cout << "Invalid serial number, it must be 15 numbers\n";
			cout << "Please enter the serial number correctly: ";
			cin >> serialNumber;
			cardCounter = 0;
		}
	}
	cout << "PLease enter the balance: ";
	cin >> amount;
	while (amount <= 0)
	{
		cout << "Invalid number !\n";
		cout << "PLease enter the balance correctly: ";
		cin >> amount;
	}

	user[currentUser].line[currentLine - 1].balance += amount;

	cout << "Your new balance for line " << currentLine << " is " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
	cout << "1. Recharge again\n";
	cout << "2. Main Menu\n";
	cout << "Select your choice:";
	cin >> choice;
	while (choice > 2 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Select your choice: ";
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		break;
	case 2:
		menuPages = 3;
		functions = 0;
		break;
	}
}

void PackageType()
{
	//Viewing the Package Type of this user's lines
	for (int i = 0;i < nLines[currentUser];i++)
	{
		cout << "Your current Package Type for line " << i + 1 << " is " << user[currentUser].line[i].packageType << "\n\n";
	}
	cout << "1. Renew your Subscription\n";
	cout << "2. Change your Subscription \n";
	cout << "3. Main Menu\n";
	cout << "Select your choice: "; 
	cin >> choice;
	while (choice > 3 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Please select your choice: "; 
		cin >> choice;
	}
	switch (choice)
	{
	//Renew subscription
	case 1:
		if (nLines[currentUser] > 1)
		{
			cout << "What line do you want to renew its Package Type? ";
			cin >> currentLine;
			while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
			{
				cout << "Invalid number !\n";
				cout << "What line do you want to renew its Package Type? ";
				cin >> currentLine;
			}
		}
		else
		{
			currentLine = nLines[currentUser];
		}
		if (user[currentUser].line[currentLine - 1].packageType <= user[currentUser].line[currentLine - 1].balance)
		{

			user[currentUser].line[currentLine - 1].balance -= user[currentUser].line[currentLine - 1].packageType;

			cout << "You have renewed your Subscription\n";
			cout << "Your new Balance is: " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
			cout << "1. Change your Subscription\n";
			cout << "2. Main Menu\n";
			cout << "Select your choice:"; 
			cin >> choice;
			while (choice > 2 || choice < 1)
			{
				cout << "Invalid choice !\n";
				cout << "Select your choice: "; 
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				menuPages = 0;
				functions = 2;
				break;
			case 2:
				menuPages = 3;
				break;
			}
		}//Not enough Balance
		else
		{
			cout << "Sorry, you must recharge your Balance to complete this Process\n\n";
			cout << "1. Your Balance\n";
			cout << "2. Main Menu\n";
			cout << "Select your choice: "; 
			cin >> choice;
			while (choice > 2 || choice < 1)
			{
				cout << "Invalid choice !\n";
				cout << "Please select your choice: ";
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				menuPages = 4;
				break;
			case 2:
				menuPages = 3;
				break;
			}

		}
		break;
	case 2:
		menuPages = 0;
		functions = 2;
		break;
	case 3:
		menuPages = 3;
		break;
	}
}

void ChangePackageType()
{
	cout << "\t\t********************\n";
	//Choose which line to change
	if (nLines[currentUser] > 1)
	{
		cout << "What line do you want to change its Package Type? ";
		cin >> currentLine;
		while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
		{
			cout << "Invalid number !\n";
			cout << "What line do you want to change its Package Type? ";
			cin >> currentLine;
		}
	}
	else
	{
		currentLine = nLines[currentUser];
	}
	cout << "Please enter your new Package Type: "; 
	cin >> pType;
	while (pType < 10)
	{
		cout << "Sorry, minimum number of Package Type is 10\n";
		cout << "Please enter your new Package Type: ";
		cin >> pType;
		if (pType >= 10)
		{
			break;
		}
	}
	//package type is less than or equal user's balance
	if (pType <= user[currentUser].line[currentLine - 1].balance)
	{
		user[currentUser].line[currentLine - 1].packageType = pType;

		user[currentUser].line[currentLine - 1].balance -= user[currentUser].line[currentLine - 1].packageType;

		cout << "Your new Subscription is " << user[currentUser].line[currentLine - 1].packageType << "\n";
		cout << "Your new Balance is: " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
		cout << "1. Change your Package Type again\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice:"; 
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Select your choice: "; 
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			break;
		case 2:
			menuPages = 3;
			functions = 0;
			break;
		}
	}//Not enough Balance
	else
	{
		cout << "Sorry, you must recharge your Balance to complete this Process\n\n";
		cout << "1. Your Balance\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice: "; 
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Please select your choice: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			functions = 0;
			menuPages = 4;
			break;
		case 2:
			functions = 0;
			menuPages = 3;
			break;
		}
	}
}

void CallAndMessage()
{
	cout << "1. Make a Phone Call\n";
	cout << "2. Send a Message\n";
	cout << "3. Main Menu\n";
	cout << "Select your choice: "; 
	cin >> choice;
	while (choice > 3 || choice < 1)
	{
		cout << "Invalid choice !\n";
		cout << "Please select your choice: "; 
		cin >> choice;
	}
	switch (choice)
	{
	case 1:
		menuPages = 0;
		functions = 3;
		break;
	case 2:
		menuPages = 0;
		functions = 4;
		break;
	case 3:
		menuPages = 3;
		break;
	}
}

void MakePhoneCall()
{
	cout << "\t\t********************\n";
	if (nLines[currentUser] > 1)
	{
		cout << "What line do you want to use? ";
		cin >> currentLine;
		while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
		{
			cout << "Invalid number !\n";
			cout << "What line do you want to use? ";
			cin >> currentLine;
		}
	}
	else
	{
		currentLine = nLines[currentUser];
	}
	//Check if the user have enough balance
	if (user[currentUser].line[currentLine - 1].balance >= 0.25)
	{

		user[currentUser].line[currentLine - 1].balance -= 0.25;

		cout << "The phone call has been done,\nYour new Balance is: " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
		cout << "1. Make another Phone Call\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice: "; 
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Please select your choice: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			functions = 3;
			break;
		case 2:
			functions = 0;
			menuPages = 3;
			break;
		}
	}//Not enough Balance
	else
	{
		cout << "Sorry, you must recharge your Balance to make a phone call,\nIt costs: 0.25 LE\n\n";
		cout << "1. Your Balance\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice: "; 
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Please select your choice: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			functions = 0;
			menuPages = 4;
			break;
		case 2:
			functions = 0;
			menuPages = 3;
			break;
		}
	}
}

void SendMessage()
{
	cout << "\t\t********************\n";
	if (nLines[currentUser] > 1)
	{
		cout << "What line do you want to use? ";
		cin >> currentLine;
		while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
		{
			cout << "Invalid number !\n";
			cout << "What line do you want to use? ";
			cin >> currentLine;
		}
	}
	else
	{
		currentLine = nLines[currentUser];
	}
	//Check if the user have enough balance
	if (user[currentUser].line[currentLine - 1].balance >= 0.25)
	{

		user[currentUser].line[currentLine - 1].balance -= 0.25;

		cout << "The message has been sent,\nYour new Balance is: " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
		cout << "1. Send another Message\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice: ";
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Please select your choice: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			functions = 4;
			break;
		case 2:
			functions = 0;
			menuPages = 3;
			break;
		}
	}//Not enough Balance
	else
	{
		cout << "Sorry, you must recharge your Balance to send a message,\nIt costs: 0.25 LE\n\n";
		cout << "1. Your Balance\n";
		cout << "2. Main Menu\n";
		cout << "Select your choice: "; 
		cin >> choice;
		while (choice > 2 || choice < 1)
		{
			cout << "Invalid choice !\n";
			cout << "Please select your choice: "; 
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
			functions = 0;
			menuPages = 4;
			break;
		case 2:
			functions = 0;
			menuPages = 3;
			break;
		}
	}
}

void Transfer()
{
	string transferedNumber;
	isMenuCheck = true;
	//Which line to use
	if (nLines[currentUser] > 1)
	{
		cout << "What line do you want to use? ";
		cin >> currentLine;
		while (currentLine <= 0 || currentLine > 3 || currentLine > nLines[currentUser])
		{
			cout << "Invalid number !\n";
			cout << "What line do you want to use? ";
			cin >> currentLine;
		}
	}
	else
	{
		currentLine = nLines[currentUser];
	}
	cout << "Please enter the number you want to send balance to: "; 
	cin >> transferedNumber;
	for (int i = 0;i < 3;i++)
	{
		//Check if the transfered number is one of the user's numbers
		if (transferedNumber == user[currentUser].line[i].phoneNumber)
		{
			cout << "Sorry, you can't send Balance to yourself\n\n";
			cout << "1. Enter another number\n";
			cout << "2. Main Menu\n";
			cout << "Select your choice: "; 
			cin >> choice;
			while (choice > 2 || choice < 1)
			{
				cout << "Invalid choice !\n";
				cout << "Please select your choice: "; 
				cin >> choice;
			}
			switch (choice)
			{
			case 1:
				isMenuCheck = false;
				break;
			case 2:
				menuPages = 3;
				break;
			}
		}
	}//Going to main menu or not
	if (menuPages != 3 && isMenuCheck == true)
	{
		//Search the entered number
		for (int i = 0;i < 10; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//Number exist
				if (transferedNumber == user[i].line[j].phoneNumber)
				{
					isMenuCheck = false;

					cout << "Please enter the balance: "; 
					cin >> amount;
					if (amount > user[currentUser].line[currentLine - 1].balance)
					{
						cout << "Sorry, you must recharge your Balance to complete this Process\n\n";
						cout << "1. Your Balance\n";
						cout << "2. Transfer again\n";
						cout << "3. Main Menu\n";
						cout << "Select your choice: "; 
						cin >> choice;
						while (choice > 3 || choice < 1)
						{
							cout << "Invalid choice !\n";
							cout << "Select your choice: "; 
							cin >> choice;
						}
						switch (choice)
						{
						case 1:
							menuPages = 4;
							break;
						case 2:
							break;
						case 3:
							menuPages = 3;
							break;
						}
					}//Not enough space
					else
					{
						user[currentUser].line[currentLine - 1].balance -= amount;
						user[i].line[j].balance += amount;

						cout << "The balance has been sent to: " << transferedNumber << "\nYour new balance is: " << user[currentUser].line[currentLine - 1].balance << " LE\n\n";
						cout << "1. Transfer again\n";
						cout << "2. Main Menu\n";
						cout << "Select your choice: ";
						cin >> choice;
						while (choice > 2 || choice < 1)
						{
							cout << "Invalid choice !\n";
							cout << "Please select your choice: ";
							cin >> choice;
						}
						switch (choice)
						{
						case 1:
							break;
						case 2:
							menuPages = 3;
							break;
						}
					}
				}//Number does not exist
				else if (i == 9 && j == 2 && isMenuCheck == true)
				{
					cout << "This number does not exist\n\n";
					cout << "1. Try another number\n";
					cout << "2. Main Menu\n";
					cout << "Select your choice: "; 
					cin >> choice;
					while (choice > 2 || choice < 1)
					{
						cout << "Invalid choice !\n";
						cout << "Please select your choice: "; 
						cin >> choice;
					}
					switch (choice)
					{
					case 1:
						break;
					case 2:
						menuPages = 3;
						break;
					}
				}
			}
		}
	}
	if (menuPages == 3 || menuPages == 4)
	{
		isMenuCheck = true;
	}
}

int main()
{
	while (isExit)
	{
		while (menuPages < 8 && menuPages > 0)
		{//Menu Windows
			switch (menuPages)
			{
			case 1:
				SignUp();
				break;
			case 2:
				LogIn();
				break;
			case 3:
				Menu();
				break;
			case 4:
				Balance();
				break;
			case 5:
				PackageType();
				break;
			case 6:
				CallAndMessage();
				break;
			case 7:
				Transfer();
				break;
			}
		}//Second Window
		while (functions < 7 && functions > 0)
		{
			switch (functions)
			{
			case 1:
				Recharge();
				break;
			case 2:
				ChangePackageType();
				break;
			case 3:
				MakePhoneCall();
				break;
			case 4:
				SendMessage();
				break;
			case 5:
				ID();
				break;
			case 6:
				PASSWORD();
				break;
			}
		}
	}
	return 0;
}