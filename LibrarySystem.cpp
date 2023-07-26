#include<iostream>
#include <iomanip>
#include <Vector>
#include "Array.h"
#include <fstream>
#include <cctype>

const string BookDataBase = "Books.txt";


enum enLibraryChoice{ enAddBook = 1 ,enSearchBooksByPref = 2,enPrintWhoborrowedBookByName = 3,
						enPrintLibraryById = 4,enPrintLibraryByName = 5,enAddUser = 6,enUserBorrowBook = 7,enUserReturnBook = 8,
							enPrintUsers = 9 , enExit = 10};

struct stBooks
{
	string name;
	int id;
	int TotalQuentity;

};
struct stUsers
{
	string name;
	string national_id;
	vector <int> BookBorrow;
};
bool isPrefix(string Word, string Prefix)
{
	return (Prefix == Word.substr(0, Prefix.length()));
}
stBooks AddBook()
{
	stBooks Books;
	cout << "\nEnter Book Name : ";
	cin >> Books.name;
	cout << "Enter Book id : ";
	cin >> Books.id;
	cout << "Enter Book Total Quentity : ";
	cin >> Books.TotalQuentity;
	return Books;

}
stUsers AddUser()
{
	stUsers User;
	cout << "Enter User Name : ";
	cin >> User.name;
	cout << "Enter User National id : ";
	cin >> User.national_id;
	return User;
}
string ConvertFromBookRecordToLine(stBooks Books , string delim = "#//#")
{
	string S1 = "";
	S1 += to_string(Books.id) + delim;
	S1 += Books.name + delim;
	S1 += to_string(Books.TotalQuentity);
	return S1;
}
vector <string> SplitFunction(string Words , string delim = "#//#")
{
	vector <string> vString;
	short pos;
	string S1;
	while ((pos = Words.find(delim)) != string::npos)
	{
		S1 = Words.substr(0, pos);
		if (S1 != "")
		{
			vString.push_back(S1);
		}
		Words.erase(0, pos + delim.length());
	}
	if (Words != "")
	{
		vString.push_back(Words);
	}
	return vString;
}
stBooks ConvertBookDataFromLineToRecord(string Line)
{
	stBooks Books;
	vector <string> vString = SplitFunction(Line);
	Books.id = stoi(vString[0]);
	Books.name = vString[1];
	Books.TotalQuentity = stoi(vString[2]);
	return Books;
}
void PutBookDataToFile(vector <stBooks>& vBooks, string FileName = BookDataBase)
{
	fstream File;
	File.open(FileName, ios::out | ios::app);
	if (!File.is_open())
	{
		cout << "There is Problem Opening File ,,";
		File.close();
	}
	else
	{
		for (stBooks& i : vBooks)
		{
			File << ConvertFromBookRecordToLine(i,"#//#") << endl;
		}
		File.close();
	}
}
void ReloadBookDataFromVectorToFile(vector <stBooks> vBooks, string FileName = BookDataBase)
{
	fstream File;
	File.open(FileName, ios::out );
	if (!File.is_open())
	{
		cout << "There is Problem Opening File ,,";
		File.close();
	}
	else
	{
		for (stBooks& i : vBooks)
		{
			File << ConvertFromBookRecordToLine(i, "#//#") << endl;
		}
		File.close();
	}
}
vector <stBooks> PutBookDataFromFileToVector(string FileName = BookDataBase)
{
	fstream File;
	vector <stBooks> vBooks;
	File.open(FileName, ios::in);
	if (!File.is_open())
	{
		cout << "There is Problem Opening File ,,";
		File.close();
	}
	else
	{
		string line;
		while (getline(File,line))
		{
			vBooks.push_back(ConvertBookDataFromLineToRecord(line));
		}
	}
	return vBooks;
}
void AddBooks()
{
	vector <stBooks> vBooks;
	cout << "\n-----------------------------------\n";
	cout << "\Add Book Screen";
	cout << "\n-----------------------------------\n";

	char Answer;
	do
	{
		vBooks.push_back(AddBook());
	
		cout << "\n Do You Want To Add More Books ? [y/n] ";
		cin >> Answer;
	} while (toupper(Answer) == 'Y');
	PutBookDataToFile(vBooks, BookDataBase);
}
void AddUsers(vector <stUsers> &vUsers)
{
	cout << "\n-----------------------------------\n";
	cout << "\Add User Screen";
	cout << "\n-----------------------------------\n";

	char Answer;
	do
	{
		vUsers.push_back(AddUser());

		cout << "\n Do You Want To Add More Users ? [y/n] ";
		cin >> Answer;
	} while (toupper(Answer) == 'Y');
	
}
vector <stBooks> OrdredBooksById()
{
	vector<stBooks> vBooks = PutBookDataFromFileToVector();
	int i;
	int j;
	for (int i = 0 ;  i < vBooks.size() ; i++)
	{
		for (int j = i; j < vBooks.size(); j++)
		{
			if (vBooks[i].id > vBooks[j].id)
			{
				int temp = vBooks[i].id;
				vBooks[i].id =vBooks[j].id;
				vBooks[j].id= temp;
			}
		}
	}
	return vBooks;
}
vector <stBooks> OrdredBooksByName()
{
	vector<stBooks> vBooks = PutBookDataFromFileToVector();
	for (int i = 0; i < vBooks.size(); i++)
	{
		for (int j = i; j < vBooks.size(); j++)
		{
			if (vBooks[i].name > vBooks[j].name)
			{
				string temp = vBooks[i].name;
				vBooks[i].name = vBooks[j].name;
				vBooks[j].name = temp;
			}
		}
	}
	return vBooks;
}
void PrintUsers(vector <stUsers> &vUsers)
{
	if(!vUsers.empty())
	for (stUsers& i : vUsers)
	{
		cout << "\nName : " << i.name << endl;
		cout << "National id " << i.national_id << endl;
		cout << "Borrow Books : \n";
		if (!i.BookBorrow.empty())
		{
			for (auto& j : i.BookBorrow)
			{
				cout << j << " ";
			}
		}
		cout << "\n________________________________________________";
	}
	else
	{
		cout << "There is No Users\n";
	}
}
void PrintLibraryByid()
{
	vector <stBooks> vBooks = OrdredBooksById();
	cout << "\n-----------------------------------\n";
	cout << "\Print Library Book By Id ";
	cout << "\n-----------------------------------\n";

	for (stBooks& i : vBooks)
	{
		cout << "\nBook Name : " << i.name << endl;
		cout << "Book id " << i.id << endl;
		cout << "Book id " << i.TotalQuentity << endl;
		cout << "________________________________________________";
	}
}
void PrintLibraryByName()
{
	vector <stBooks> vBooks = OrdredBooksByName();
	cout << "\n-----------------------------------\n";
	cout << "\Print Library Book By Name ";
	cout << "\n-----------------------------------\n";

	for (stBooks& i : vBooks)
	{
		cout << "\nBook Name : " << i.name << endl;
		cout << "Book id " << i.id << endl;
		cout << "Book id " << i.TotalQuentity << endl;
		cout << "________________________________________________";
	}
}
void SearchBooksByPrefix()
{
	vector <stBooks> vBooks = PutBookDataFromFileToVector();
	string prefix;
	cout << "\n-----------------------------------\n";
	cout << "\Search Book By Refrence Screen";
	cout << "\n-----------------------------------\n";

	cout << "Ennter Book name Prefix : ";
	cin >> prefix;
	for (auto& i : vBooks)
	{
		if (isPrefix(i.name,prefix))
		{
			cout << i.name << endl;
		}

	}
}
bool isUserFound(vector <stUsers> &vUsers,string UserName , stUsers &User)
{
	 ;
	for (auto& i : vUsers)
	{
		if (i.name == UserName)
		{
			User = i;
			return true;
		}
	}

	return false;
}
bool isBookFound(string BookName ,stBooks &Book)
{
	vector <stBooks> vBooks = PutBookDataFromFileToVector();
	for (auto& i : vBooks)
	{
		if (i.name == BookName)
		{
			Book = i;
			return true;
		}
		}
	return false;
}
void ReadUserAndBookName(string &UserName ,string &BookName)
{
	cout << "Enter User Name : ";
	cin >> UserName;
	cout << "Enter Book Name : ";
	cin >> BookName;
}
void UserBorroWBook(vector <stUsers> &vUsers)
{
	string UserName;
	string BookName;
	stUsers User;
	stBooks Book;
	cout << "\n-----------------------------------\n";
	cout << "\ User Borrow Book";
	cout << "\n-----------------------------------\n";

	vector <stBooks> vBooks = PutBookDataFromFileToVector();
	ReadUserAndBookName(UserName, BookName);
	while (!isBookFound(BookName,Book) || !isUserFound(vUsers,UserName,User))
	{
		cout << "User Or Book Not found Please search again  : \n\n";
		ReadUserAndBookName(UserName, BookName);
	}
	for (auto& i : vBooks)
	{
		if (i.name == Book.name)
		{
			i.TotalQuentity--;
		}
	}
	for (auto& i : vUsers)
	{
		if (i.name == User.name)
		{
			i.BookBorrow.push_back(Book.id);
		}
	}
	ReloadBookDataFromVectorToFile(vBooks);
}
void UserReturnBook(vector <stUsers>& vUsers)
{
	string UserName;
	string BookName;
	stUsers User;
	stBooks Book;
	vector <stBooks> vBooks = PutBookDataFromFileToVector();
	ReadUserAndBookName(UserName, BookName);
	while (!isBookFound(BookName, Book) || !isUserFound(vUsers, UserName, User))
	{
		cout << "User Or Book Not found Please search again  : \n\n";
		ReadUserAndBookName(UserName, BookName);
	}
	for (auto& i : vBooks)
	{
		if (i.name == Book.name)
		{
			i.TotalQuentity++;
		}
	}
	for (int j = 0; j < vUsers.size(); j++)
	{
		if (vUsers[j].name == User.name)
		{
			vUsers[j].BookBorrow.erase(vUsers[j].BookBorrow.begin() + j);
		}
	}
	ReloadBookDataFromVectorToFile(vBooks);

}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 10]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void ShowMenu()
{
	system("cls");
	cout << "==================================================================" << endl << endl;
	cout << "\t\t\t\Library System\n\n";
	cout << "==================================================================" << endl << endl;
	cout << "\t[1] Add Book." << endl;
	cout << "\t[2] Search Books By Prefix." << endl;
	cout << "\t[3] Print Who Borrowed Book By Name." << endl;
	cout << "\t[4] Print Library By Id." << endl;
	cout << "\t[5] Print Library By Name." << endl;
	cout << "\t[6] Add User." << endl;
	cout << "\t[7] User Borrow Book." << endl;
	cout << "\t[8] User Return Book." << endl;
	cout << "\t[9] Print Users." << endl;

}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	LibrarySystem();

}
void LibrarySystem()
{
	ShowMenu();
	static vector <stUsers> vUsers;
	short Answer = ReadMainMenueOption();
	switch ((enLibraryChoice)Answer)
	{
	case enLibraryChoice::enAddBook:
		system("cls");
		AddBooks();
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enSearchBooksByPref:
		system("cls");
		SearchBooksByPrefix();
		GoBackToMainMenue();
	case enLibraryChoice::enPrintWhoborrowedBookByName:
		system("cls");
		GoBackToMainMenue();
	case enLibraryChoice::enPrintLibraryById:
		system("cls");
		PrintLibraryByid();
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enPrintLibraryByName:
		system("cls");
		PrintLibraryByName();
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enAddUser:
		system("cls");
		AddUsers(vUsers);
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enUserBorrowBook:

		system("cls");
		UserBorroWBook(vUsers);
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enUserReturnBook:
		system("cls");
		UserReturnBook(vUsers);
		GoBackToMainMenue();
		break;
	case enLibraryChoice::enPrintUsers:
		system("cls");
		PrintUsers(vUsers);
		GoBackToMainMenue();
		break;
	default:
			exit(0);
			break;
	}
}
int main()
{
	//LibrarySystem();
}