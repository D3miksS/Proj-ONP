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
	for (int j = 0; j < formula.length(); j++) {
		int max = 0;
		if (piorytet[j] > max) {
			max = piorytet[j];
			maxId = j;
		}
	}
	return maxId;
}

//stos

int main(void) {
	setlocale(LC_CTYPE, "Polish");	// Polskie znaki w środku kodu

	string formula;
	short piorytet[100] = { 0 };
	short d = 0;
	char onp[100] = { 0 };
	short maxId = 0;

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