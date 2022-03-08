#include <iostream>
#include <string.h>
using namespace std;

// Dominik Ficek

/*
	Fuckcja sprawdza piorytety znaków i zapisuje do tablicy "piorytet"
	in:
		formula - wyrażenie podawane przez użytkownika
		d - zmienna pomocnicza przechowująca aktualny piorytet znaku
		piorytet - tablica zawierająca piorytety znkaów z "formula"
		
*/
void  checkPriority(string &formula, short &d, short *piorytet ) {
	for (int i = 0; i < formula.length(); i++) {
		if (formula[i] == '(')
			d += 10;
		else if (formula[i] == ')')
			d -= 10;

		if (formula[i] == '-' || formula[i] == '+')
			piorytet[i] = 1 + d;
		else if (formula[i] == '*' || formula[i] == '/')
			piorytet[i] = 2 + d;
	}
}

/*
	Funkcja szuka maksimum w tavlicy "piorytet"
	in:
		formula - wyrażenie podawane przez użytkownika
		piorytet - tablica zawierająca piorytety znkaów z "formula"
		maxId - zmienna przechowująca nr pozycji największej liczby z tablicy "piorytet"
	out:
		maxId - zwaraca zmienną z nr pozycji największej liczby z tablicy "piorytet"
*/
int searchMax(string &formula, short *piorytet, short &maxId) {
	int max = 0;
	for (int j = 0; j < formula.length(); j++) {
		if (piorytet[j] > max) {
			max = piorytet[j];
			maxId = j;
		}
	}
	return maxId;
}

//stos

/*
	Fuckcja dodająca na stos
	in:
		nn - dana do dopisania na stos
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
*/
void na_stos(char &nn, int &pp, char *stoss) {
	if (!czy_pelny(pp)) {
		stoss[pp] = nn;
		pp++;
	}
	else
		;	// bląd stos pełny
}

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
	out:
		z - dana z góry stosu
		-11 - kod błędu oznaczający, że stos jest pusty
*/
char ze_stosu(int &pp, char *stoss) {
	char z;
	if (!czy_pusty) {
		z = stoss[pp];
		pp--;
		return z;
	}
	else
		return -11; // błąd stos pusty 
}

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
	out:
		true - stos jest pełny
		false - stos nie jest pełny
*/
bool czy_pelny(int &pp) {
	if (pp == 9)
		return true;
	else
		return false;
}

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
	out:
		true - stos jest pusty
		false - stos nie jest pusty
*/
bool czy_pusty(int &pp) {
	if (pp == -1)
		return true;
	else
		return false;
}

/*
	Fuckcja odczytująca aktualną daną ze stosu
	in:
		pp - flaga informująca o aktualnym położeniu n stosie
		stoss - stos
	out:
		stos[pp] - dana z góry stosu
		-11 - kod błędu oznaczający, że stos jest pusty
*/
char zobacz(int &pp, char *stoss) {
	if (!czy_pusty) {
		return	stoss[pp];;
	}
	else
		return -11; // błąd stos pusty 
}

int main(void) {
	setlocale(LC_CTYPE, "Polish");	// Polskie znaki w środku kodu

	string formula;
	short piorytet[100] = { 0 };
	short d = 0;
	char onp[100] = { 0 };
	short maxId = 0;
	char stos[10] = { 0 };
	char n;
	int p = -1;

	cout << "Podaj równanie.\n";
	cin >> formula;

	//piorytety liczenia
	checkPriority(formula, d, piorytet);

	//max
	searchMax(formula, piorytet, maxId);

	// doadać zerowanie najwêkszego w piorytety

	//zamiana na onp
	//for(int n = 0; n < fun.length(); n++){ }
	//int n = 0;
	//do {
	//	onp[n] = funkcja[maxId - 1];
	//	n++;
	//	onp[n] = funkcja[maxId + 1];
	//	n++;
	//	onp[n] = funkcja[maxId];
	//	n++;

	//} while ();
	
	//wyświetlanie piorytety
	for (int i = 0; i < formula.length(); i++) {
		cout << piorytet[i] << ", ";
	}
	
	return 0;
}
