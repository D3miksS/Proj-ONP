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
	Funkcja sprawdza piorytety znakĂłw i zapisuje do tablicy "piorytet"
	in:
		formula - wyraĹĽenie podawane przez uĹĽytkownika
		piorytet - tablica zawierajÄ…ca piorytety znkaĂłw z "formula"
		ilZnak - zmienna liczÄ…ca iloĹ›Ä‡ znakĂłw
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
		}
	}
}

/*
	Funkcja szuka maksimum w tavlicy "piorytet"
	in:
		formula - wyraĹĽenie podawane przez uĹĽytkownika
		piorytet - tablica zawierajÄ…ca piorytety znkaĂłw z "formula"
		maxId - zmienna przechowujÄ…ca nr pozycji najwiÄ™kszej liczby z tablicy "piorytet"
	out:
		maxId - zwaraca zmiennÄ… z nr pozycji najwiÄ™kszej liczby z tablicy "piorytet"
*/
int search_max(string& formula, short* piorytet, short& maxId) {
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
	Fuckcja odczytujÄ…ca aktualnÄ… danÄ… ze stosu
	in:
		pp - flaga informujÄ…ca o aktualnym poĹ‚oĹĽeniu n stosie
	out:
		true - stos jest peĹ‚ny
		false - stos nie jest peĹ‚ny
*/
bool czy_pelny(short& pp) {
	if (pp == 9)
		return true;
	else
		return false;
}

/*
	Fuckcja odczytujÄ…ca aktualnÄ… danÄ… ze stosu
	in:
		pp - flaga informujÄ…ca o aktualnym poĹ‚oĹĽeniu n stosie
	out:
		true - stos jest pusty
		false - stos nie jest pusty
*/
bool czy_pusty(short& pp) {
	if (pp == -1)
		return true;
	else
		return false;
}

/*
	Fuckcja dodajÄ…ca na stos
	in:
		nn - dana do dopisania na stos
		pp - flaga informujÄ…ca o aktualnym poĹ‚oĹĽeniu n stosie
		stoss - stos
	out:
		'a' - kod bĹ‚Ä™du oznaczjÄ…cy, ĹĽe stos jest peĹ‚ny
*/
void na_stos(double& nn, short& pp, double* stoss) {
	if (!czy_pelny(pp)) {
		pp++;
		stoss[pp] = nn;
	}
	else
		throw 'a';
}

/*
	Fuckcja odczytujÄ…ca aktualnÄ… danÄ… ze stosu
	in:
		pp - flaga informujÄ…ca o aktualnym poĹ‚oĹĽeniu n stosie
		stoss - stos
	out:
		z - dana z gĂłry stosu
		'b' - kod bĹ‚Ä™du oznaczajÄ…cy, ĹĽe stos jest pusty
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
}

/*
	Fuckcja odczytujÄ…ca aktualnÄ… danÄ… ze stosu
	in:
		pp - flaga informujÄ…ca o aktualnym poĹ‚oĹĽeniu n stosie
		stoss - stos
	out:
		stos[pp] - dana z gĂłry stosu
		'b' - kod bĹ‚Ä™du oznaczajÄ…cy, ĹĽe stos jest pusty
*/
double zobacz(short& pp, double* stoss) {
	if (!czy_pusty(pp)) {
		return	stoss[pp];;
	}
	else
		throw 'b';
}
// koniec stosu

/*
	Funkcja sprawdzajÄ…ca poprawnoĹ›Ä‡ wpisanych znakĂłw. Dobre tylko znaki dziaĹ‚aĹ„ matematycznych i cyfry
	in:
		formula - wyraĹĽenie podane przez urzytkownika, do sprawdzenia
		jj - pozycja znaku do sprawdzenia
	out:
		true - wpisany znak poprawny
		false - wpisany znak bĹ‚Ä™dny
*/
bool czy_liczba(string& formula, short& jj) {
	if ((formula[jj] > 47) && (formula[jj] < 58))
		return true;
	else if (formula[jj] == '+' || formula[jj] == '-' || formula[jj] == '/' || formula[jj] == '*')
		return true;
	else
		return false;
}

/*
	Funkcja zapisujÄ…ca wyraĹĽenie podane przez uĹĽytkownika w postacji ONP
	in:
		maxId - numer pozycji najwaĹĽniejszego znaku
		onp - tablica, w ktĂłrej zapisywane bÄ™dzie wyraĹĽenie ONP
		formula - wyraĹĽenie podane przez uĹĽytkownika
		piorytety - tablica przechowujÄ…ca wartoĹ›ci waĹĽnoĹ›ci kolejnych znakĂłw wyraĹĽenia
		onpI - wolna pozycja do zapisu w tablicy onp
		ujemna - tablica przechowujÄ…ca, na ktĂłrej pozycji sÄ… liczby ujemne
		ujemnaLicz - zmienna przesuwajÄ…ca pozycje w tablicy "ujemne ONP"
		ujemnaOnp - tablica przechowujÄ…ca, na ktĂłrej pozycji w zapisie ONP jest liczba ujemna
	out:
		NULL
*/
void add_to_onp(short maxId, char* onp, string& formula, short* piorytety, short& onpI, short* ujemna, short& ujemnaLicz, short* ujemnaOnp) {
	maxId = search_max(formula, piorytety, maxId);
	short id1 = maxId + 1;
	short id2 = maxId - 1;

	if (czy_liczba(formula, id2) && piorytety[id2] >= 0) { // sprawdza lewe miejsce
		if (ujemna[maxId] == -3) {
			ujemnaOnp[ujemnaLicz] = -2;
		};
		onp[onpI] = formula[id2];
		onpI++;
		piorytety[id2] = -1;
		ujemnaLicz++;
	}
	else if (formula[id2] == ')') {
		if (ujemna[id2 - 1] == -2 && piorytety[id2 - 1] >= 0) {
			ujemnaOnp[ujemnaLicz] = -2;
			onp[onpI] = formula[id2 - 1];
			onpI++;
			piorytety[id2 - 1] = -1;
		}
		ujemnaLicz++;
	};

	if (czy_liczba(formula, id1) && piorytety[id1] >= 0) { //sprawdza prawe miejsce
		if (ujemna[maxId] == -3) {
			ujemnaOnp[ujemnaLicz] = -2;
		};
		onp[onpI] = formula[id1];
		onpI++;
		ujemnaLicz++;
		piorytety[id1] = -1;
	}
	else if (formula[id1] == '(') {
		if (formula[id1 + 1] == '-') {
			if (ujemna[id1 + 2] == -2 && piorytety[id1 + 2] >= 0) {
				ujemnaOnp[ujemnaLicz] = -2;
				onp[onpI] = formula[id1 + 2];
				onpI++;
				piorytety[id1 + 2] = -1;
			}
		}
		ujemnaLicz++;
	};

	if (ujemna[maxId] != -3) { // sprawdza znak
		onp[onpI] = formula[maxId];
		onpI++;
		ujemnaLicz++;
	}
	piorytety[maxId] = -1;
}

/*
	Funkcja obliczajÄ…ca wynik dziaĹ‚ania dwĂłch liczb
	in:
		onp - wyraĹĽenie zapisane za pomocÄ… sposobu ONP
		ii - aktualna pozycja w tablicy "onp"
		wynik - zmienna przechowujÄ…ca wynik dziaĹ‚ania
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
	}
}

/*
	Funkcja obliczajÄ…ca dziaĹ‚anie na stosie
	in:
		onp - wyraĹĽenie zapisane w postaci onp
		onpI - pozycja aktualnej cyfry lub znaku branego do obliczeĹ„
		stos - tablica przechowujÄ…ca dane do aktualnych obliczeĹ„
		p - aktualna pozycja na stosie
		ujemnaOnp - tablica przechowujÄ…ca, na ktĂłrej pozycji w zapisie ONP jest liczba ujemna
	out:
		wynik - wynik obliczanego wyraĹĽenia
*/
double licz_wyraz(char* onp, short& onpI, double* stos, short& p, short* ujemnaOnp) {
	double wynik = 0;
	for (short i = 0; i < onpI; i++) {
		if ((onp[i] > 47) && (onp[i] < 58)) {
			double cyfra = onp[i] - 48;
			if (ujemnaOnp[i] == -2) {
				cyfra = cyfra * -1;
			}
			na_stos(cyfra, p, stos);
		}
		else if ((onp[i] == '+' || onp[i] == '-' || onp[i] == '/' || onp[i] == '*') && ujemnaOnp[i] != -3) {
			dzialanie(onp, stos, i, wynik, p);
		}
	}
	return wynik;
}

/*
	Funkcja odpowiadajÄ…ca za caĹ‚e podanie i obliczenie wyraĹĽenia
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
	short ujemnaLicz = 0;

	cout << "Podaj rĂłwnanie.\n";
	cin >> formula;

	check_priority(formula, piorytet, ilZnak);
	check_ujemna(formula, ujemna, piorytet);

	while (ilZnak > 0) {
		add_to_onp(maxId, onp, formula, piorytet, onpI, ujemna, ujemnaLicz, ujemnaOnp);
		ilZnak--;
	};

	cout << "WyraĹĽenie w postaci ONP: ";
	for (int i = 0; i < formula.length(); i++) {
		if (ujemnaOnp[i] == -2)
			cout << (onp[i] - 48) * -1 << " ";
		else
			cout << onp[i] << " ";
	}

	try {
		cout << "\nWynik to: " << licz_wyraz(onp, onpI, stos, p, ujemnaOnp) << endl;
	}
	catch (char numError) {
		if (numError == 'a') {
			cout << "\n---Stos jest peĹ‚ny---\n";
		}
		else if (numError == 'b') {
			cout << "\n---Stos jest pusty---\n";
		}
	}
}

/*
	Funcja odpowiadajÄ…ca za UI
	in:
		nr - zmienna przechuwujÄ…ca podany nr opcji przez uĹĽytkownika
	out:
		NULL
*/
void menu(short& nr) {
	if (nr == 0) {
		cout << "1. Wpisz dziaĹ‚anie do obiczenia\n2. Instrukcja\n3. Info\n4. ZakoĹ„cz program\n";
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
	}
}

/*
	Funkcja odpowiadajÄ…ca za menu powrotu
	in:
		nr - zmienna przechuwujÄ…ca podany nr opcji przez uĹĽytkownika
	out:
		NULL
*/
void menu_back(short& nr) {
	if (nr == 49) {
		cout << "----------\n1. WrĂłÄ‡ do menu gĹ‚Ăłwnego\n2. ZakoĹ„cz program\n3. PowtĂłrz\n";
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
		}
	}
	else {
		cout << "----------\n1. WrĂłÄ‡ do menu gĹ‚Ăłwnego\n2. ZakoĹ„cz program\n";
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
		}
	}
}

/*
	Funkcja proszÄ…ca o wybranie opcji menu i sprwadzajÄ…ca poprawnoĹ›Ä‡ wybieranej opcji menu
	in:
		nr - zmienna przechowujÄ…ca nr opcji w menu
		a - zmienna kontrolujÄ…ca z ktĂłrego menu przychodzimy
	out:
		nr - zwraca poprawny nr opcji menu
*/
short pod_nr_menu(short& nr, short a) {
	nr = _getch();
	if (a == 0) {
		if (nr >= 49 && nr <= 52)
			return nr;
		else {
			cout << "\nZĹ‚y numer opcji\n";
			pod_nr_menu(nr, 0);
		}
	}
	else if (a == 1) {
		if (nr >= 49 && nr <= 51)
			return nr;
		else {
			cout << "\nZĹ‚y numer opcji\n";
			pod_nr_menu(nr, 1);
		}
	}
	else {
		if (nr >= 49 && nr <= 50)
			return nr;
		else {
			cout << "\nZĹ‚y numer opcji\n";
			pod_nr_menu(nr, 2);
		}
	}
}

/*
	Funkcja sprawdzajÄ…ca czy dana liczba jest ujemna
	in:
		formula - ciÄ…g podany przez urzytkownika
		ujemna - tablica przechowujÄ…ca, na ktĂłej pozycji sÄ… liczby ujemne i znaki ujemnoĹ›ci
		piorytety - tablica piorytetĂłw wykonywania dziaĹ‚aĹ„
*/
void check_ujemna(string& formula, short* ujemna, short* piorytety) {
	for (int i = 0; i < formula.length(); i++) {
		if (formula[i] == '(') {
			if (formula[i + 1] == '-') {
				short jj = i + 2;
				if (czy_liczba(formula, jj)) {
					ujemna[i + 1] = -3;
					piorytety[i + 1] = 1;
					ujemna[i + 2] = -2;
				}
			}
		}
	}
}

/*
	Funkcja wyĹ›wietlajÄ…ca inforamcje o autorze
*/
void info() {
	char copyr = 169;
	cout << "Autor: Dominik Ficek\nMUP OĹ›wiÄ™cim\nInformatyka Rok I\nData: 2022\nWersja: 0.9\n";
}

/*
	Funkcja wyĹ›wietlajÄ…ca instrukcje do programu
*/
void instrukcja() {
	cout << "-----Instrukcja-----\nDozwolone znaki do wpisania:\n# cyfry od 0 do 9\n# +, -, *, /, (, )\n\nZapis liczb ujemnych: (-3), (-8)\n\nPodstawowe zasady:\n";
	cout << "# W nawiasach nie moĹĽe byÄ‡ samej cyfry\n# Przed nawiasem nie moĹĽe znajdowaÄ‡ sie znak bez poprzedzajÄ…cej go cyfry\n# Tylko wyĹĽej wymienione znaki gwarantujÄ… poprawoĹ›Ä‡ wykonania dziaĹ‚ania\n\n";
	cout << "PrzykĹ‚adowe wyraĹĽenie do obliczenia:\n(-2)*4-((5/2)*(-2))\n\nZapisy niedozwolone:\n# -(2*3)\n# a+2\n# 2-(3)\n\n";
}

int main(void) {
	setlocale(LC_CTYPE, "Polish");	// Polskie znaki w Ĺ›rodku kodu

	short nr = 0;
	menu(nr);

	return 0;
}
