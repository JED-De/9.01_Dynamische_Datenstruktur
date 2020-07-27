#include <iostream>

#include <string> // wegen "std::to_string" aus der Vorgabe der aufgabenstellung in liste_als_string(TListenKnoten * anker)

using namespace std;

struct TListenKnoten
{
	int data;
	TListenKnoten *next;
	TListenKnoten *prev; //eingefügt, Listenknoten prev
};

void hinten_anfuegen(TListenKnoten *&anker, const int wert)
{
	TListenKnoten *neuer_eintrag = new TListenKnoten;
	neuer_eintrag->data = wert;
	neuer_eintrag->next = nullptr;
	neuer_eintrag->prev = nullptr; //iniziallisieren als Nullpointer
	if (anker == nullptr)
		anker = neuer_eintrag;
	else
	{
		TListenKnoten *ptr = anker;
		while (ptr->next != nullptr)
			ptr = ptr->next;
		ptr->next = neuer_eintrag; // (gegeben) setzen des next pointers auf den neuen Knotenpunkt
		neuer_eintrag->prev = ptr; // setzen des Aktuellen Pointers in den Prev pointer des neuen Knotenpunktes
	}
}

void in_liste_einfuegen(TListenKnoten* &anker, int wert_neu, int vor_wert)
{
	TListenKnoten *neuer_eintrag = new TListenKnoten;
	neuer_eintrag->data = wert_neu;
	neuer_eintrag->next = nullptr;
	neuer_eintrag->prev = nullptr; //iniziallisieren als Nullpointer
	if (anker == nullptr)
		anker = neuer_eintrag;
	else
	{
		TListenKnoten *ptr = anker;
		while (ptr->next != nullptr)
		{
			if (ptr->data != vor_wert)
			{
				ptr = ptr->next;
			}
			else
				break;
		}
		if (ptr->next == nullptr && ptr->data != vor_wert)
		{
			ptr->next = neuer_eintrag; // (gegeben) setzen des next pointers auf den neuen Knotenpunkt
			neuer_eintrag->prev = ptr; // prev auf ptr, damit die verlinkung auch Rueckwaerts geht.
		}
		else
		{
			neuer_eintrag->next = ptr;  //in den Struct neuer entrag wird der next pointer auf den ptr pointer gesetzt, der auf dem Struct liegt, was nach dem strict kommen soll.
			neuer_eintrag->prev = ptr->prev; //der ptr hat noch den pointer auf den eintrag, der vor den neuen Eintrag liegen wird, somit übernehmen wir den wert des pointers in prev des neuen eintrages
			ptr->prev = neuer_eintrag; //wir setzten den prev pointer ders ptr struct auf den neuen eintrag (somit ist ptr nun fertig geaendert)
			if (neuer_eintrag->prev != nullptr)
			{
				neuer_eintrag->prev->next = neuer_eintrag; // hier setzen wir den next pointer des Objects neu, welches davor liegt, hierfuer gehen wir ueber den prev pointer des neuer_eintrag Objektes (zuvor gesetzt in Zeile 60) auf das Objekt davor, und setzen desen next Pointer von ptr auf neuer_eintrag 
			}
			else
			{
				anker = neuer_eintrag; //für den fall das wir ganz an anfang sind, setzen wir den anker auf das Objekt neuer_eintrag
			}
		}
	}
}

void liste_loeschen(TListenKnoten* &anker)
{
	TListenKnoten *ptr = anker;
	if (ptr != nullptr)
	{
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
			delete ptr->prev;
		}
		delete ptr;
		anker = nullptr;
	}
}

string liste_als_string(TListenKnoten * anker)
{
	string resultat = "";
	if (anker == nullptr)
		return resultat;
	else
	{
		resultat += "[ ";
		TListenKnoten *ptr = anker;
		do
		{
			resultat += std::to_string(ptr->data);
			if (ptr->next != nullptr) resultat += " , ";
			else resultat += " ";
			ptr = ptr->next;
		} while (ptr != nullptr);
		resultat += "]";
	}
	return resultat;
}

string liste_als_string_rueckwaerts(TListenKnoten * anker)
{
	string resultat = "";
	if (anker == nullptr)
		return resultat;
	else
	{
		resultat += "[ ";
		TListenKnoten *ptr = anker;
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		do
		{
			resultat += std::to_string(ptr->data);
			if (ptr->prev != nullptr) resultat += " , ";
			else resultat += " ";
			ptr = ptr->prev;
		} while (ptr != nullptr);
		resultat += "]";
	}
	return resultat;
}

void liste_ausgeben(TListenKnoten * anker)
{
	if (liste_als_string(anker) == "")	//für denn fall, das da leere Liste stehen sollte, nicht eindeutig
		cout << "Leere Liste." << endl;
	else
		cout << liste_als_string(anker) << endl;
}

void liste_ausgeben_rueckwaerts(TListenKnoten* anker)
{
	if (liste_als_string_rueckwaerts(anker) == "") //für denn fall, das da leere Liste stehen sollte, nicht eindeutig
		cout << "Leere Liste." << endl;
	else
		cout << liste_als_string_rueckwaerts(anker) << endl;
}

//=============Main aus den einzelnen Teilaufgaben=============//

int main1() 
{ 
	int laenge = 10;   
	TListenKnoten *anker = nullptr;    
	liste_ausgeben(anker);
	for (int i = 0; i < laenge; i++)  
		hinten_anfuegen(anker, i*i);   
	liste_ausgeben(anker);   
	system("PAUSE");  
	return 0;
}

int main2() 
{
	int laenge = 10;  
	TListenKnoten *anker = nullptr;    
	liste_ausgeben(anker);  
	liste_ausgeben_rueckwaerts(anker);    
	for (int i = 0; i < laenge; i++)       
		hinten_anfuegen(anker, i*i);    
	liste_ausgeben(anker);   
	liste_ausgeben_rueckwaerts(anker);  
	system("PAUSE");   
	return 0; 
}

int main3() {
	const int laenge = 10; 
	TListenKnoten *anker = nullptr;    
	for (int i = 0; i < laenge; i++)    
		in_liste_einfuegen(anker, i*i, 9999);   
	liste_ausgeben(anker);   
	liste_ausgeben_rueckwaerts(anker);   
	int wert_neu, vor_wert;   
	cout << "Einzufuegender Wert: "; 
	cin >> wert_neu; 
	cout << "Vor welchem Wert? "; 
	cin >> vor_wert;    
	in_liste_einfuegen(anker, wert_neu, vor_wert);  
	liste_ausgeben(anker);  
	liste_ausgeben_rueckwaerts(anker);
	system("PAUSE");  
	return 0;
}

int main4()
{
	const int laenge = 10;
	TListenKnoten *anker = nullptr;
	liste_ausgeben(anker);
	liste_loeschen(anker);
	for (int i = 0; i < laenge; i++)
		in_liste_einfuegen(anker, i*i, 9999);
	liste_ausgeben(anker);
	liste_ausgeben_rueckwaerts(anker);
	in_liste_einfuegen(anker, 99, 0);
	in_liste_einfuegen(anker, 99, 25);
	in_liste_einfuegen(anker, 99, 81);
	in_liste_einfuegen(anker, 99, 9999); // Achtung: geändert 99 => 9999
	liste_ausgeben(anker);
	liste_ausgeben_rueckwaerts(anker);
	liste_loeschen(anker);
	liste_ausgeben(anker);
	liste_ausgeben_rueckwaerts(anker);
	system("PAUSE");
	return 0;
}

int main()
{
	/*main1(); 
	cout << endl << "================================================" << endl << endl;
	main2();
	cout << endl << "================================================" << endl << endl;
	main3();
	cout << endl << "================================================" << endl << endl;
	*/
	main4();
}