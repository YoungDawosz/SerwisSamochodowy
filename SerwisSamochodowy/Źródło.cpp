#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
System wynajmu samochod�w
�atwy projekt wynajmu samochodu.J e�li mia�e� do czynienia z systemem zarz�dzania bibliotek�,
koncepcja systemu wynajmu samochod�w powinna by� dla Ciebie bu�k� z mas�em.
To jeden z najbardziej podstawowy C++ projekty dla pocz�tkuj�cych, a wystarczy
zmieni� kilka rzeczy z systemu bibliotecznego. By�by to jednak dobry pocz�tek,
gdyby� nie zarz�dza� bibliotek�. Mo�esz tak�e czerpa� inspiracj� z aplikacji takich jak Ola i Uber.

Najwa�niejsze informacje o projekcie

1. Projekt wymaga trzech serwer�w � jednego dla firmy wynajmuj�cej,
serwera administracyjnego, drugiego dla kierowc�w i na koniec jednego dla klient�w.

2. Twoje menu g��wne powinno pozwoli� Ci zalogowa� si� jako administrator, kierowca lub klient.

3. Powiniene� doda� funkcje dla punkt�w odbioru i adres�w nadania.

4. Powinno r�wnie� istnie� menu umo�liwiaj�ce klientowi wyb�r spo�r�d samochod�w dost�pnych do wynaj�cia.

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

//zrobic hasla i loginy w pliku tekstowym!!!!!!!!!!!!!

class Dane
{
private:
	string login_admin = "root";
	string pass_admin = "admin";

	string login_kierowca = "kierowca";
	string pass_kierowca = "1234";

	string login_klient = "klient";
	string pass_klient = "1234";

public:
	string LoginAdmin()
	{
		return login_admin;
	}

	string PassAdmin()
	{
		return pass_admin;
	}

	void setLoginAdmin(string login_admin)
	{
		this->login_admin = login_admin;
	}

	void setPassAdmin(string pass_admin)
	{

		this->pass_admin = pass_admin;
	}
};


void zmienHaslo(string login)//DZIALA
{
	Dane dane;
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
	Dane dane;
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

		ext = false; // Dodaj deklaracj� ext jako typu bool i ustaw na false

		while (!ext) // U�yj operatora ! (negacji), aby sprawdzi�, czy ext jest false
		{
			ifstream file("LogPass.txt");
			string storedLoginA, storedLoginB, storedLoginC;
			string storedPassA, storedPassB, storedPassC;
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
					while (getline(file, line))
					{
						size_t delimeterPos = line.find(":");
						size_t delimeterPos2 = line.find(":", delimeterPos + 1);
						size_t delimeterPos3 = line.find(":", delimeterPos2 + 1);

						if (delimeterPos != string::npos)
						{
							storedLoginA = line.substr(0, delimeterPos);
							storedPassA = line.substr(delimeterPos + 1);

							pokazLoginA = storedLoginA;
							pokazPassA = storedPassA;

							cout << "1. Admin:" << endl << "Login: " << pokazLoginA << endl << "Haslo: " << pokazPassA << endl << endl;

							if (delimeterPos2 != string::npos)
							{
								storedLoginB = line.substr(0, delimeterPos2);
								storedPassB = line.substr(delimeterPos2 + 1);

								pokazLoginB = storedLoginB;
								pokazPassB = storedPassB;

								cout << "2. Kierowca:" << endl << "Login: " << pokazLoginB << endl << "Haslo: " << pokazPassB << endl << endl;

								if (delimeterPos3 != string::npos)
								{
									storedLoginC = line.substr(0, delimeterPos3);
									storedPassC = line.substr(delimeterPos3 + 1);

									pokazLoginC = storedLoginC;
									pokazPassC = storedPassC;

									cout << "3. Klient:" << endl << "Login: " << pokazLoginC << endl << "Haslo: " << pokazPassC << endl << endl;
									Sleep(3000);
									break;
								}

								Sleep(3000);
								break;
							}

							Sleep(3000);
							break;
						}
						
					}
					file.close();
				}
				else
				{
					cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
					return; // Zwr�� b��d
				}
				
				break;

			case 4:
				cout << "Zostales wylogowany!" << endl;
				Sleep(1000);
				system("cls");
				ext = true; // Ustaw ext na true, aby wyj�� z p�tli
				break;

			default:
				cout << "Niepoprawny wybor!" << endl;
				break;
			}
		}
	}
}

/*
void admin()
{
	Dane dane;
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
		string pokazPass, pokazLogin;

		system("cls");
		cout << "------------------------------------" << endl;
		cout << "|--Zostales zalogowany jako admin--|" << endl;
		cout << "------------------------------------" << endl;
		Sleep(2000);
		cout << endl;

		ext = false; // Dodaj deklaracj� ext jako typu bool i ustaw na false

		while (!ext) // U�yj operatora ! (negacji), aby sprawdzi�, czy ext jest false
		{
			ifstream file("LogPass.txt");
			string storedLogin;
			string storedPass;
			string line;

			system("cls");
			cout << "****ADMIN****" << endl;
			cout << "1. Zmien haslo" << endl;
			cout << "2. Zmien login" << endl;
			cout << "3. Podglad hasel i loginow" << endl;
			cout << "4. Wyloguj sie z konta administratora" << endl;
			cin >> wybor;
			cout << endl;

			switch (wybor)
			{
			case 1:
				zmienHaslo(login);
				break;

			case 2:
				// Dodaj kod dla zmiany loginu
				break;

			case 3:
				int podg;
				cout << "1. Admin" << endl << "2. Kierowca" << endl << "3. Klient" << endl;
				cin >> podg;

				switch (podg)
				{
				case 1:
					if (file.is_open())
					{
						while (getline(file, line))
						{
							size_t delimeterPos = line.find(":");
							if (delimeterPos != string::npos)
							{
								storedLogin = line.substr(0, delimeterPos);
								storedPass = line.substr(delimeterPos + 1);
							}
						}
						file.close();
					}
					else
					{
						cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
						return; // Zwr�� b��d
					}

					pokazLogin = storedLogin;
					pokazPass = storedPass;

					cout << "Login: " << pokazLogin << endl << "Haslo: " << pokazPass << endl;
					Sleep(3000);
					break;

				case 2:
					// Dodaj kod dla podgl�du has�a i loginu dla kierowcy
					break;

				case 3:
					// Dodaj kod dla podgl�du has�a i loginu dla klienta
					break;

				default:
					cout << "Niepoprawny wybor!" << endl;
					break;
				}
				break;

			case 4:
				cout << "Zostales wylogowany!" << endl;
				Sleep(1000);
				system("cls");
				ext = true; // Ustaw ext na true, aby wyj�� z p�tli
				break;

			default:
				cout << "Niepoprawny wybor!" << endl;
				break;
			}
		}
	}
}
*/
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
			return 0;
		}
	}

	return 0;
}
//tutaj masz oryginal przed moimi zmianiami wiec wrazie wez to ale to nie dziala dokonca








/*
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/*
System wynajmu samochod�w
�atwy projekt wynajmu samochodu.J e�li mia�e� do czynienia z systemem zarz�dzania bibliotek�,
koncepcja systemu wynajmu samochod�w powinna by� dla Ciebie bu�k� z mas�em.
To jeden z najbardziej podstawowy C++ projekty dla pocz�tkuj�cych, a wystarczy
zmieni� kilka rzeczy z systemu bibliotecznego. By�by to jednak dobry pocz�tek,
gdyby� nie zarz�dza� bibliotek�. Mo�esz tak�e czerpa� inspiracj� z aplikacji takich jak Ola i Uber.

Najwa�niejsze informacje o projekcie

1. Projekt wymaga trzech serwer�w � jednego dla firmy wynajmuj�cej,
serwera administracyjnego, drugiego dla kierowc�w i na koniec jednego dla klient�w.

2. Twoje menu g��wne powinno pozwoli� Ci zalogowa� si� jako administrator, kierowca lub klient.

3. Powiniene� doda� funkcje dla punkt�w odbioru i adres�w nadania.

4. Powinno r�wnie� istnie� menu umo�liwiaj�ce klientowi wyb�r spo�r�d samochod�w dost�pnych do wynaj�cia.

*/
/*
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

//zrobic hasla i loginy w pliku tekstowym!!!!!!!!!!!!!

class Dane
{
private:
	string login_admin = "root";
	string pass_admin = "admin";

	string login_kierowca = "kierowca";
	string pass_kierowca = "1234";

	string login_klient = "klient";
	string pass_klient = "1234";

public:
	string LoginAdmin()
	{
		return login_admin;
	}

	string PassAdmin()
	{
		return pass_admin;
	}

	void setLoginAdmin(string login_admin)
	{
		this->login_admin = login_admin;
	}

	void setPassAdmin(string pass_admin)
	{

		this->pass_admin = pass_admin;
	}
};


void zmienHaslo(string login)//DZIALA
{
	Dane dane;
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
	Dane dane;
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
		string pokazPass, pokazLogin;

		system("cls");
		cout << "------------------------------------" << endl;
		cout << "|--Zostales zalogowany jako admin--|" << endl;
		cout << "------------------------------------" << endl;
		Sleep(2000);
		cout << endl;

		ext = false; // Dodaj deklaracj� ext jako typu bool i ustaw na false

		while (!ext) // U�yj operatora ! (negacji), aby sprawdzi�, czy ext jest false
		{
			ifstream file("LogPass.txt");
			string storedLogin;
			string storedPass;
			string line;

			system("cls");
			cout << "****ADMIN****" << endl;
			cout << "1. Zmien haslo" << endl;
			cout << "2. Zmien login" << endl;
			cout << "3. Podglad hasel i loginow" << endl;
			cout << "4. Wyloguj sie z konta administratora" << endl;
			cin >> wybor;
			cout << endl;


			int podg;
			cout << "1. Admin" << endl << "2. Kierowca" << endl << "3. Klient" << endl;
			cin >> podg;

			switch (podg)
			{
			case 1:
				zmienHaslo(login);
				break;

			case 2:

				break;

			case 3:
				if (file.is_open())
				{
					while (getline(file, line))
					{
						size_t delimeterPos = line.find(":");
						if (delimeterPos != string::npos)
						{
							storedLogin = line.substr(0, delimeterPos);
							//cout << "Testowo #1: " << line.substr(0, delimeterPos) << endl;
							storedPass = line.substr(delimeterPos + 1);
							//cout << "Testowa #2: " << line.substr(delimeterPos + 1)<<endl;
							break;
						}
					}
					file.close();
				}
				else
				{
					cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
					return; // Zwr�� b��d
				}

				pokazLogin = storedLogin;
				pokazPass = storedPass;

				cout << "Login: " << pokazLogin << endl << "Haslo: " << pokazPass << endl;
				Sleep(3000);
				break;

			case 4:
				cout << "Zostales wylogowany!" << endl;
				Sleep(1000);
				system("cls");
				ext = true; // Ustaw ext na true, aby wyj�� z p�tli
				break;

			default:
				cout << "Niepoprawny wybor!" << endl;
				break;
			}
			break;
		}
	}
}

/*
void admin()
{
	Dane dane;
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
		string pokazPass, pokazLogin;

		system("cls");
		cout << "------------------------------------" << endl;
		cout << "|--Zostales zalogowany jako admin--|" << endl;
		cout << "------------------------------------" << endl;
		Sleep(2000);
		cout << endl;

		ext = false; // Dodaj deklaracj� ext jako typu bool i ustaw na false

		while (!ext) // U�yj operatora ! (negacji), aby sprawdzi�, czy ext jest false
		{
			ifstream file("LogPass.txt");
			string storedLogin;
			string storedPass;
			string line;

			system("cls");
			cout << "****ADMIN****" << endl;
			cout << "1. Zmien haslo" << endl;
			cout << "2. Zmien login" << endl;
			cout << "3. Podglad hasel i loginow" << endl;
			cout << "4. Wyloguj sie z konta administratora" << endl;
			cin >> wybor;
			cout << endl;

			switch (wybor)
			{
			case 1:
				zmienHaslo(login);
				break;

			case 2:
				// Dodaj kod dla zmiany loginu
				break;

			case 3:
				int podg;
				cout << "1. Admin" << endl << "2. Kierowca" << endl << "3. Klient" << endl;
				cin >> podg;

				switch (podg)
				{
				case 1:
					if (file.is_open())
					{
						while (getline(file, line))
						{
							size_t delimeterPos = line.find(":");
							if (delimeterPos != string::npos)
							{
								storedLogin = line.substr(0, delimeterPos);
								storedPass = line.substr(delimeterPos + 1);
							}
						}
						file.close();
					}
					else
					{
						cout << "Nie mozna otworzyc pliku z haslami i loginami!" << endl;
						return; // Zwr�� b��d
					}

					pokazLogin = storedLogin;
					pokazPass = storedPass;

					cout << "Login: " << pokazLogin << endl << "Haslo: " << pokazPass << endl;
					Sleep(3000);
					break;

				case 2:
					// Dodaj kod dla podgl�du has�a i loginu dla kierowcy
					break;

				case 3:
					// Dodaj kod dla podgl�du has�a i loginu dla klienta
					break;

				default:
					cout << "Niepoprawny wybor!" << endl;
					break;
				}
				break;

			case 4:
				cout << "Zostales wylogowany!" << endl;
				Sleep(1000);
				system("cls");
				ext = true; // Ustaw ext na true, aby wyj�� z p�tli
				break;

			default:
				cout << "Niepoprawny wybor!" << endl;
				break;
			}
		}
	}
}
*/
/*

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
			return 0;
		}
	}

	return 0;
}*/