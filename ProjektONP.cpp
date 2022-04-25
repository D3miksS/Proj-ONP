#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;

// Dominik Ficek

void menu_back(short& nr);
short pod_nr_menu(short& nr, short a);
void check_ujemna(string& formula, short* ujemna, short* piorytety);
void info();
void instrukcja();

/*
	Funkcja sprawdza piorytety znaków i zapisuje do tablicy "piorytet"
	in:
		formula - wyrażenie podawane przez użytkownika
		piorytet - tablica zawierająca piorytety znkaów z "formula"
		ilZnak - zmienna licząca ilość znaków
	out:
		NULL
*/
void check_priority(string& formula, short* piorytet, short& ilZnak) {
	short d = 0;
	for (int i = 0; i < formula.length(); i++) {
		if (formula[i] == '(')
			d += 10;
		else if (formula[i] == ')')
			d -= 10;

		if (formula[i] == '-' || formula[i] == '+') {
			piorytet[i] = 1 + d;
			ilZnak++;
		}
		else if (formula[i] == '*' || formula[i] == '/') {
			piorytet[i] = 2 + d;
			ilZnak++;
		};
	};
};

/*
	Funkcja szuka maksimum w tavlicy "piorytet"
	in:
		formula - wyrażenie podawane przez użytkownika
		piorytet - tablica zawierająca piorytety znkaów z "formula"
		maxId - zmienna przechowująca nr pozycji największej liczby z tablicy "piorytet"
	out:
		maxId - zwaraca zmienną z nr pozycji największej liczby z tablicy "piorytet"
*/
int search_max(string& formula, short* piorytet, short& maxId) {
	int max = 0;
	for (int j = 0; j < formula.length(); j++) {
		if (piorytet[j] > max) {
			max = piorytet[j];
			maxId = j;
		};
	};
	return maxId;
};

//stos
/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
	out:
		true - stos jest pełny
		false - stos nie jest pełny
*/
bool czy_pelny(short& pp) {
	if (pp == 9)
		return true;
	else
		return false;
};

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
	out:
		true - stos jest pusty
		false - stos nie jest pusty
*/
bool czy_pusty(short& pp) {
	if (pp == -1)
		return true;
	else
		return false;
};

/*
	Fuckcja dodająca na stos
	in:
		nn - dana do dopisania na stos
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
	out:
		'a' - kod błędu oznaczjący, że stos jest pełny
*/
void na_stos(double& nn, short& pp, double* stoss) {
	if (!czy_pelny(pp)) {
		pp++;
		stoss[pp] = nn;
	}
	else
		throw 'a';
};

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
	out:
		z - dana z góry stosu
		'b' - kod błędu oznaczający, że stos jest pusty
*/
double ze_stosu(short& pp, double* stoss) {
	double z;
	if (!czy_pusty(pp)) {
		z = stoss[pp];
		pp--;
		return z;
	}
	else
		throw 'b';
};

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
	out:
		stos[pp] - dana z góry stosu
		'b' - kod błędu oznaczający, że stos jest pusty
*/
double zobacz(short& pp, double* stoss) {
	if (!czy_pusty(pp)) {
		return	stoss[pp];;
	}
	else
		throw 'b';
};
// koniec stosu

/*
	Funkcja zapisująca wyrażenie podane przez użytkownika w postacji ONP
	in:
		maxId - numer pozycji najważniejszego znaku
		onp - tablica, w której zapisywane będzie wyrażenie ONP
		formula - wyrażenie podane przez użytkownika
		piorytety - tablica przechowująca wartości ważności kolejnych znaków wyrażenia
		onpI - wolna pozycja do zapisu w tablicy onp
		ujemna - tablica przechowująca, na której pozycji są liczby ujemne
		ujemnaOnp - tablica przechowująca, na której pozycji w zapisie ONP jest liczba ujemna
	out:
		NULL
*/
void add_to_onp(short maxId, char* onp, string& formula, short* piorytety, short& onpI, short* ujemna, short* ujemnaOnp) {
	
	maxId = search_max(formula, piorytety, maxId);
	int id1 = maxId + 1;

	//dodaj wszystko z lewej do znaku
	for (int i = 0; i < maxId; i++) {
		if (((formula[i] > 47) && (formula[i] < 58)) && (piorytety[i] >= 0 || piorytety[i] == -3)) {
			if (ujemna[i] == -3) {
				ujemnaOnp[onpI] = -2;
			};
			onp[onpI] = formula[i];
			onpI++;
			piorytety[i] = -1;
		}
		else if (formula[i] == '(') {
			if (formula[i + 1] == '-') {
				if (ujemna[i + 2] == -2 && piorytety[i + 2] >= 0) {
					ujemnaOnp[onpI] = -2;
					onp[onpI] = formula[i + 2];
					onpI++;
					piorytety[i + 2] = -1;
				};
			};
		};
	};

	// dodaj jedną z prawej od znaku
	if (((formula[id1] > 47) && (formula[id1] < 58)) && piorytety[id1] >= 0) {
		if (ujemna[maxId] == -3) {
			ujemnaOnp[onpI] = -2;
		};
		onp[onpI] = formula[id1];
		onpI++;
		piorytety[id1] = -1;
	}
	else if (formula[id1] == '(') {
		if (formula[id1 + 1] == '-') {
			if (ujemna[id1 + 2] == -2 && piorytety[id1 + 2] >= 0) {
				ujemnaOnp[onpI] = -2;
				onp[onpI] = formula[id1 + 2];
				onpI++;
				piorytety[id1 + 2] = -1;
			};
		};
	};

	// sprawdza i dodaj znak
	if (ujemna[maxId] != -3 && piorytety[maxId] != -1) {
		onp[onpI] = formula[maxId];
		onpI++;
	};
	piorytety[maxId] = -1;
};

/*
	Funkcja obliczająca wynik działania dwóch liczb
	in:
		onp - wyrażenie zapisane za pomocą sposobu ONP
		ii - aktualna pozycja w tablicy "onp"
		wynik - zmienna przechowująca wynik działania
	out:
		NULL
*/
void dzialanie(char* onp, double* stos, short& ii, double& wynik, short& p) {
	double l2 = ze_stosu(p, stos);
	double l1 = ze_stosu(p, stos);
	switch (onp[ii])
	{
	case '+':
		wynik = l1 + l2;
		na_stos(wynik, p, stos);
		break;
	case '-':
		wynik = l1 - l2;
		na_stos(wynik, p, stos);
		break;
	case '*':
		wynik = l1 * l2;
		na_stos(wynik, p, stos);
		break;
	case '/':
		wynik = l1 / l2;
		na_stos(wynik, p, stos);
		break;
	default:
		break;
	};
};

/*
	Funkcja obliczająca działanie na stosie
	in:
		onp - wyrażenie zapisane w postaci onp
		onpI - pozycja aktualnej cyfry lub znaku branego do obliczeń
		stos - tablica przechowująca dane do aktualnych obliczeń
		p - aktualna pozycja na stosie
		ujemnaOnp - tablica przechowująca, na której pozycji w zapisie ONP jest liczba ujemna
	out:
		wynik - wynik obliczanego wyrażenia
*/
double licz_wyraz(char* onp, short& onpI, double* stos, short& p, short* ujemnaOnp) {
	double wynik = 0;
	for (short i = 0; i < onpI; i++) {
		if ((onp[i] > 47) && (onp[i] < 58)) {
			double cyfra = onp[i] - 48;
			if (ujemnaOnp[i] == -2) {
				cyfra = cyfra * -1;
			};
			na_stos(cyfra, p, stos);
		}
		else if ((onp[i] == '+' || onp[i] == '-' || onp[i] == '/' || onp[i] == '*') && ujemnaOnp[i] != -3) {
			dzialanie(onp, stos, i, wynik, p);
		};
	};
	return wynik;
};

/*
	Funkcja odpowiadająca za całe podanie i obliczenie wyrażenia
	in:
		NULL
	out:
		NULL
*/
void program() {
	string formula;
	short piorytet[100] = { 0 };
	short maxId = 0;
	char onp[100] = { 0 };
	short onpI = 0;
	double stos[10] = { 0 };
	short p = -1;
	short ilZnak = 0;
	short ujemna[100] = { 0 };
	short ujemnaOnp[100] = { 0 };

	cout << "Podaj równanie.\n";
	cin >> formula;

	check_priority(formula, piorytet, ilZnak);
	check_ujemna(formula, ujemna, piorytet);

	while (ilZnak > 0) {
		add_to_onp(maxId, onp, formula, piorytet, onpI, ujemna, ujemnaOnp);
		ilZnak--;
	};

	cout << "Wyrażenie w postaci ONP: ";
	for (int i = 0; i < formula.length(); i++) {
		if (ujemnaOnp[i] == -2)
			cout << (onp[i] - 48) * -1 << " ";
		else
			cout << onp[i] << " ";
	};

	try {
		cout << "\nWynik to: " << licz_wyraz(onp, onpI, stos, p, ujemnaOnp) << endl;
	}
	catch (char numError) {
		if (numError == 'a') {
			cout << "\n---Stos jest pełny---\n";
		}
		else if (numError == 'b') {
			cout << "\n---Stos jest pusty---\n";
		};
	};
};

/*
	Funcja odpowiadająca za UI
	in:
		nr - zmienna przechuwująca podany nr opcji przez użytkownika
	out:
		NULL
*/
void menu(short& nr) {
	if (nr == 0) {
		cout << "1. Wpisz działanie do obiczenia\n2. Instrukcja\n3. Info\n4. Zakończ program\n";
		pod_nr_menu(nr, 0);
	};

	switch (nr)
	{
	case 49:
		system("cls");
		program();
		menu_back(nr);
		break;
	case 50:
		system("cls");
		instrukcja();
		menu_back(nr);
		break;
	case 51:
		system("cls");
		info();
		menu_back(nr);
		break;
	case 52:
		break;
	default:
		break;
	};
};

/*
	Funkcja odpowiadająca za menu powrotu
	in:
		nr - zmienna przechuwująca podany nr opcji przez użytkownika
	out:
		NULL
*/
void menu_back(short& nr) {
	if (nr == 49) {
		cout << "----------\n1. Wróć do menu głównego\n2. Zakończ program\n3. Powtórz\n";
		pod_nr_menu(nr, 1);
		switch (nr)
		{
		case 49:
			system("cls");
			nr = 0;
			menu(nr);
			break;
		case 50:

			break;
		case 51:
			system("cls");
			nr = nr - 2;
			menu(nr);
			break;
		default:
			break;
		};
	}
	else {
		cout << "----------\n1. Wróć do menu głównego\n2. Zakończ program\n";
		pod_nr_menu(nr, 2);
		switch (nr)
		{
		case 49:
			system("cls");
			nr = 0;
			menu(nr);
			break;
		case 50:

			break;
		default:
			break;
		};
	};
};

/*
	Funkcja prosząca o wybranie opcji menu i sprwadzająca poprawność wybieranej opcji menu
	in:
		nr - zmienna przechowująca nr opcji w menu
		a - zmienna kontrolująca z którego menu przychodzimy
	out:
		nr - zwraca poprawny nr opcji menu
*/
short pod_nr_menu(short& nr, short a) {
	nr = _getch();
	if (a == 0) {
		if (nr >= 49 && nr <= 52)
			return nr;
		else {
			cout << "\nZły numer opcji\n";
			pod_nr_menu(nr, 0);
		};
	}
	else if (a == 1) {
		if (nr >= 49 && nr <= 51)
			return nr;
		else {
			cout << "\nZły numer opcji\n";
			pod_nr_menu(nr, 1);
		};
	}
	else {
		if (nr >= 49 && nr <= 50)
			return nr;
		else {
			cout << "\nZły numer opcji\n";
			pod_nr_menu(nr, 2);
		};
	};
};

/*
	Funkcja sprawdzająca czy dana liczba jest ujemna
	in:
		formula - ciąg podany przez urzytkownika
		ujemna - tablica przechowująca, na któej pozycji są liczby ujemne i znaki ujemności
		piorytety - tablica piorytetów wykonywania działań
*/
void check_ujemna(string& formula, short* ujemna, short* piorytety) {
	for (int i = 0; i < formula.length(); i++) {
		if (formula[i] == '(') {
			if (formula[i + 1] == '-') {
				int jj = i + 2;
				if ((formula[jj] > 47) && (formula[jj] < 58)) {
					ujemna[i + 1] = -3;
					piorytety[i + 1] = 1;
					ujemna[i + 2] = -2;
				};
			};
		};
	};
};

/*
	Funkcja wyświetlająca inforamcje o autorze
*/
void info() {
	char copyr = 169;
	cout << "Autor: Dominik Ficek\nMUP Oświęcim\nInformatyka Rok I\nData: 2022\nWersja: 0.9\n";
};

/*
	Funkcja wyświetlająca instrukcje do programu
*/
void instrukcja() {
	cout << "-----Instrukcja-----\nDozwolone znaki do wpisania:\n# cyfry od 0 do 9\n# +, -, *, /, (, )\n\nZapis liczb ujemnych: (-3), (-8)\n\nPodstawowe zasady:\n";
	cout << "# W nawiasach nie może być samej cyfry\n# Przed nawiasem nie może znajdować sie znak bez poprzedzającej go cyfry\n# Tylko wyżej wymienione znaki gwarantują poprawość wykonania działania\n\n";
	cout << "Przykładowe wyrażenie do obliczenia:\n(-2)*4-((5/2)*(-2))\n\nZapisy niedozwolone:\n# -(2*3)\n# a+2\n# 2-(3)\n\n";
};

int main(void) {
	setlocale(LC_CTYPE, "Polish");	// Polskie znaki w środku kodu

	short nr = 0;
	menu(nr);

	return 0;
};
