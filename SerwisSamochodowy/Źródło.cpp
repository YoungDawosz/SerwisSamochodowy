#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
System wynajmu samochodów
£atwy projekt wynajmu samochodu.J eœli mia³eœ do czynienia z systemem zarz¹dzania bibliotek¹,
koncepcja systemu wynajmu samochodów powinna byæ dla Ciebie bu³k¹ z mas³em.
To jeden z najbardziej podstawowy C++ projekty dla pocz¹tkuj¹cych, a wystarczy
zmieniæ kilka rzeczy z systemu bibliotecznego. By³by to jednak dobry pocz¹tek,
gdybyœ nie zarz¹dza³ bibliotek¹. Mo¿esz tak¿e czerpaæ inspiracjê z aplikacji takich jak Ola i Uber.

Najwa¿niejsze informacje o projekcie

1. Projekt wymaga trzech serwerów – jednego dla firmy wynajmuj¹cej,
serwera administracyjnego, drugiego dla kierowców i na koniec jednego dla klientów.

2. Twoje menu g³ówne powinno pozwoliæ Ci zalogowaæ siê jako administrator, kierowca lub klient.

3. Powinieneœ dodaæ funkcje dla punktów odbioru i adresów nadania.

4. Powinno równie¿ istnieæ menu umo¿liwiaj¹ce klientowi wybór spoœród samochodów dostêpnych do wynajêcia.

*/

class Samochod
{
private:
	string marka, model;
	int rok_produkcji;
	bool jestDostepny;
public:
	bool czyJestDostepny()
	{
		if (jestDostepny == true)
		{
			cout << "Jest dostepne!" << endl;
			return true;
		}
		else
		{
			cout << "Nie jest dostepne!" << endl;
			return false;
		}
	}
	void wypozyczSamochod()
	{
		if (jestDostepny == false)
		{
			//trzeba to rozbudowac
			cout << "Auto jest niedostepne!" << endl;
			return;
		}
		else
		{
			jestDostepny = false;
			cout << "Auto zostalo wypozyczone" << endl;
			daneSamochodu();
		}
	}
	void zwrocSamochod()
	{
		if (jestDostepny == true)
		{
			//trzeba to rozbudowac
			cout << "Auto jest niedostepne!" << endl;
			return;
		}
		else
		{
			jestDostepny = false;
			cout << "Auto zostalo wypozyczone" << endl;
			daneSamochodu();
		}
	}
	void daneSamochodu()
	{
		cout << "Marka: " << marka << endl << "model: " << model << "rok produkcji: " << rok_produkcji << endl;
	}

};

void zmienHaslo(string login)
{
	int wybor2;
	string pierw, powt;

	cout << "Haslo ktorego uzytkownika ma byc zmienione?" << endl;
	cout << "1. Admin" << endl << "2. Kierowca" << endl << "3. Klient" << endl << endl;
	cin >> wybor2;

	switch (wybor2)
	{
	case 1:
		char t;
		cout << "Czy napewno chcesz zmienic haslo admina? (t/n): ";
		cin >> t;
		cout << endl;
		if (t == 't')
		{
			cout << "Podaj nowe haslo: ";
			cin >> pierw;
			cout << endl;
			cout << "Powtorz nowe haslo: ";
			cin >> powt;
			cout << endl;

			if (pierw == powt)
			{
				ifstream inputFile("LogPass.txt");
				string line;
				vector<string> lines;

				if (inputFile.is_open())
				{
					while (getline(inputFile, line))
					{
						size_t delimiterPos = line.find(":");
						if (delimiterPos != string::npos)
						{
							string storedLogin = line.substr(0, delimiterPos);

							if (login == storedLogin)
							{
								line = login + ":" + pierw;
							}
						}
						lines.push_back(line);
					}
					inputFile.close();

					ofstream outputFile("LogPass.txt");
					if (outputFile.is_open())
					{
						for (const string& updatedLine : lines)
						{
							outputFile << updatedLine << endl;
						}
						outputFile.close();

						cout << "Haslo zostalo zmienione!" << endl;
						Sleep(1500);
					}
					else
					{
						cout << "Nie udalo sie otworzyc pliku do zapisu." << endl;
						Sleep(1500);
					}
				}
				else
				{
					cout << "Nie udalo sie otworzyc pliku do odczytu." << endl;
					Sleep(1500);
				}
			}
			else
			{
				cout << "Podane hasla roznia sie!" << endl;
				Sleep(1500);
			}
		}
		break;

	case 2:
		break;

	case 3:
		break;
	}
}

void admin()
{
	string login, pass, line;
	int wybor, wybor2;
	bool loginMatch = false, passMatch = false;
	ifstream file("LogPass.txt");

	cout << "Podaj login: " << endl;
	cin >> login;

	cout << "Podaj haslo: " << endl;
	cin >> pass;

	if (!file.is_open())
	{
		cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
		return;
	}

	while (getline(file, line))
	{
		size_t delimeterPos = line.find(":");
		if (delimeterPos != string::npos)
		{
			string storedLogin = line.substr(0, delimeterPos);
			string storedPass = line.substr(delimeterPos + 1);

			if (login == storedLogin)
			{
				loginMatch = true;

				if (pass == storedPass)
				{
					passMatch = true;
					break;
				}

				if (pass != storedPass)
				{
					cout << "Nie poprawne dane logowania!" << endl;
					Sleep(2000);
					system("cls");
					break;
				}
			}
			else
			{
				cout << "Nie poprawne dane!" << endl;
				Sleep(1000);
				system("cls");
				break;
			}
		}
	}
	file.close();

	if (loginMatch && passMatch)
	{
		bool ext = false;
		string pokazPassA, pokazLoginA, pokazPassB, pokazLoginB, pokazLoginC, pokazPassC;

		system("cls");
		cout << "------------------------------------" << endl;
		cout << "|--Zostales zalogowany jako admin--|" << endl;
		cout << "------------------------------------" << endl;
		Sleep(2000);
		cout << endl;

		ext = false; // Dodaj deklaracjê ext jako typu bool i ustaw na false

		while (!ext) // U¿yj operatora ! (negacji), aby sprawdziæ, czy ext jest false
		{
			ifstream file("LogPass.txt");
			string storedLoginA, storedLoginB, storedLoginC;
			string storedPassA, storedPassB, storedPassC;
			size_t delimeterPos = string::npos;
			size_t delimeterPos2 = string::npos;
			size_t delimeterPos3 = string::npos;
			string line;

			system("cls");
			cout << "****ADMIN****" << endl;
			cout << "1. Zmien haslo" << endl;
			cout << "2. Zmien login" << endl;
			cout << "3. Podglad hasel i loginow" << endl;
			cout << "4. Wyloguj sie z konta administratora" << endl;
			cin >> wybor;
			cout << endl;

			/* //to zakomentowalem bo nie chuja nie wiem po co to tu jest (po to aby moc wybrac ktorego uzytkownika chcesz zobaczyc login i haslo)
			int podg;
			cout << "1. Admin" << endl << "2. Kierowca" << endl << "3. Klient" << endl;
			cin >> podg;
			*/
			switch (wybor)//tutaj zmienilem z podg na wybor
			{
			case 1:
				zmienHaslo(login);
				break;

			case 2:

				break;

			case 3: //troche pozmieniac
				if (file.is_open())
                {
                    string line;
                    int userCount = 0;

                    while (getline(file, line) && userCount < 3)
                    {
                        size_t pos = line.find(':');
                        if (pos != string::npos)
                        {
                            string username = line.substr(0, pos);
                            string password = line.substr(pos + 1);

                            switch (userCount)
                            {
                                case 0:
                                    cout << "1. Admin:" << endl;
                                    break;
                                case 1:
                                    cout << "2. Kierowca:" << endl;
                                    break;
                                case 2:
                                    cout << "3. Klient:" << endl;
                                    break;
                            }

                            cout << "Login: " << username << endl << "Haslo: " << password << endl << endl;
                            userCount++;
                        }
                    }
                    Sleep(6000);

                    file.close();
                }
                else
                {
                    cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
                    return; // Zwróć błąd
                }

				break;

			case 4:
				cout << "Zostales wylogowany!" << endl;
				Sleep(1000);
				system("cls");
				ext = true; // Ustaw ext na true, aby wyjœæ z pêtli
				break;

			default:
				cout << "Niepoprawny wybor!" << endl;
				break;
			}
		}
	}
}

void kierowca()
{

}

void klient()
{

}

int main()
{
	int sposob;
	cout << "------------------------------------" << endl;
	cout << "|----SYSTEM WYNAJMOW SAMOCHODOW----|" << endl;
	cout << "------------------------------------" << endl;
	cout << endl;

	while (true)
	{
		cout << "------------------------------------" << endl;
		cout << "|-----WYBIERZ SPOSOB LOGOWANIA-----|" << endl;
		cout << "|--1. admin 2. kierowca 3. klient--|" << endl;
		cout << "|---4. exit (wyjscie z programu)---|" << endl;
		cout << "------------------------------------" << endl;
		cin >> sposob;
		system("cls");

		switch (sposob)
		{
		case 1:
			admin();
			break;

		case 2:
			kierowca();
			break;

		case 3:
			klient();
			break;

		case 4:
			cout << "Wyjscie z programu." << endl;
			return 0;
			break;

		default:
			cout << "Zly wybor!" << endl;
			Sleep(1000);
			system("cls");
			main();
		}
	}

	return 0;
}
