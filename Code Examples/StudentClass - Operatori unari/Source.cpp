//Tema:
//1. Implementati operatorul de cast la int care returneaza varsta studentului
//2. Implementati operatorul de cast la char* care returneaza numele studentului

#include <iostream>
using namespace std;

class Student
{
private:
	int varsta;
	char* nume;
	int nrNote;
	int *note;
public:
#pragma region Constructori, Destructor
	//constructor fara parametrii
	Student()
	{
		nume = NULL;
		varsta = 0;
		nrNote = 0;
		note = NULL;
	}
	Student(char* nume, int varsta, int nrNote, int*note)
		:varsta(varsta), nrNote(nrNote)
	{
		//this->varsta = varsta;
		//this->nrNote = nrNote;
		//nume
		//this->nume = nume; //gresit
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		//note
		//this->note = note; //gresit
		this->note = new int[nrNote];
		for (int i = 0; i < nrNote; i++)
			this->note[i] = note[i];
	}
	//constructor copiere
	Student(const Student & source)
	{
		cout << "Constructor copiere" << endl;

		//copiere nume
		if (source.nume == NULL)
			this->nume = NULL;
		else
		{
			this->nume = new char[strlen(source.nume) + 1];
			strcpy(this->nume, source.nume);
		}

		//copiere varsta
		this->varsta = source.varsta;

		//copiere nrNote
		this->nrNote = source.nrNote;

		//copiere note
		if (source.note == NULL)
			this->note = NULL;
		else
		{
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = source.note[i];
		}
	}
	//destructor
	~Student()
	{
		//dezalocare spatiu (doar daca exista spatiu alocat)
		if (nume != NULL)
			delete[] nume;
		//dezalocare spatiu (doar daca exista spatiu alocat)
		if (note != NULL)
			delete[] note;
	}
#pragma endregion 

#pragma region Metode acces
	//Get/Set Varsta
	int getVarsta() const
	{
		return varsta;
	}
	void setVarsta(int varstaNoua)
	{
		if (varstaNoua >= 0 && varstaNoua < 150)
			varsta = varstaNoua;
		else
			throw new exception("Varsta intre 0 si 150!");
	}

	//Get/Set Nume
	char* getNume() const {
		return nume;
	}
	void setNume(char* numeNou) {
		if (numeNou == NULL)
			throw new exception("Nume nu poate fi NULL!");
		else
		{
			if (this->nume != NULL)
				delete[] this->nume;
			this->nume = new char[strlen(numeNou) + 1];
			strcpy(this->nume, numeNou);
		}
	}

	//Get/Set Note & NrNote
	int getNrNote() const
	{
		return nrNote;
	}
	int* getNote() const
	{
		return note;
	}
	void setNote(int nrNote, int*note)
	{
		this->nrNote = nrNote;

		if (this->note != NULL)
			delete[] this->note;
		this->note = new int[nrNote];
		for (int i = 0; i < nrNote; i++)
			this->note[i] = note[i];
	}
#pragma endregion 

#pragma region Operatori

#pragma region Operator atribuire
	//supraincarcare operator=
	Student & operator=(const Student & source)
	{
		cout << "Operator =" << endl;

		//1.
		this->varsta = source.varsta;
		this->nrNote = source.nrNote;

		//2. copiere atribute *

		//Nume
		//a) stergere spatiu existent
		if (this->nume != NULL)
			delete[] this->nume;

		if (source.nume == NULL)
			this->nume = NULL;
		else
		{
			//b) alocare spatiu
			this->nume = new char[strlen(source.nume) + 1];
			//c) copiere
			strcpy(this->nume, source.nume);
		}

		//Note
		//a) stergere spatiu existent
		if (this->note != NULL)
			delete[] this->note;

		if (source.note == NULL)
			this->note = NULL;
		else
		{
			//b) alocare spatiu
			this->note = new int[this->nrNote];
			//c) copiere
			for (int i = 0; i < this->nrNote; i++)
				this->note[i] = source.note[i];
		}

		return  *this;
	}
#pragma endregion

#pragma region Operatori unari
	//supraincarcare operator!
	bool operator!() const
	{
		if (this->nrNote == 0)
			return true;
		else
			return false;
	}

	//supraincarcare operator++ prefixat
	const Student& operator++()
	{
		this->varsta++;
		return *this;
	}

	//supraincarcare operator++ postfixat
	const Student operator++(int)
	{
		Student copie = *this; //constructor copiere
		this->varsta++; // echivalent cu ++(*this); care apeleaza forma prefixata a operatorului (implementata mai sus)
		return copie;
	}

	//supraincarcare operator-- prefixat
	const Student& operator--()
	{
		this->varsta--;
		return *this;
	}

	//supraincarcare operator-- postfixat
	const Student operator--(int)
	{
		Student copie = *this; //constructor copiere
		--(*this);
		return copie;
	}

	//supraincarcare operator() cast la float
	explicit operator float() const
	{
		float medie = 0;
		if (this->nrNote > 0)
		{
			for (int i = 0; i < this->nrNote; i++)
				medie += this->note[i];
			medie /= this->nrNote;
		}
		return medie;
	}
#pragma endregion
#pragma endregion
};

ostream & operator<<(ostream & consola, const Student & st)
{
	consola << endl << "Nume: ";
	if (st.getNume() != NULL)
		consola << st.getNume();
	consola << endl << "Varsta: " << st.getVarsta();
	consola << endl << "Note: ";
	for (int i = 0; i < st.getNrNote(); i++)
		consola << " " << st.getNote()[i];

	return consola;
}

istream & operator >> (istream & consola, Student & st)
{
#pragma region Nume
	cout << endl << "Nume: ";
	char buffer[200];
	consola >> buffer;

	/*if (st.nume != NULL)
	delete[] st.nume;
	st.nume = new char[strlen(buffer) + 1];
	strcpy(st.nume, buffer);*/
	st.setNume(buffer);
#pragma endregion

#pragma region Varsta
	cout << "Varsta: ";
	//cin >> st.varsta;
	int varsta;
	cin >> varsta;
	st.setVarsta(varsta);
#pragma endregion

#pragma region Note
	cout << "NrNote: ";
	/*
	cin >> st.nrNote;
	if (st.note != NULL)
	delete[] st.note;
	st.note = new int[st.nrNote];
	for (int i = 0; i < st.nrNote; i++)
	{
	cout << "nota[" << i << "]: ";
	cin >> st.note[i];
	}*/

	int nrNote;
	cin >> nrNote;
	int *note = new int[nrNote];
	for (int i = 0; i < nrNote; i++)
	{
		cout << "nota[" << i << "]: ";
		cin >> note[i];
	}
	st.setNote(nrNote, note);
	delete[]note;
#pragma endregion

	return consola;
}

void main()
{
	int marks[] = { 10,9 };
	Student s("Nume", 21, 2, marks);
	
	//operator++ prefixat
	cout << (++s)<<endl; //afiseaza 22
	
	//operator++ postfixat
	//cout << (s++)<<endl; //afiseaza 21
	//cout << s<<endl; // afiseaza 22

	//operator cast
	cout << "Media: "<<(float)s << endl;
}

