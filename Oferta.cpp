#include "Oferta.h"

Oferta::Oferta()
{
	this->denumire = "";
	this->destinatie = "";
	this->pret = -1;
	this->tip = "";
	this->id = -1;
}

Oferta::Oferta(string denumire, string destinatie, string tip, double pret, int id)
{
	this->denumire = denumire;
	this->destinatie = destinatie;
	this->pret = pret;
	this->tip = tip;
	this->id = id;
}

Oferta& Oferta::operator =(const Oferta& x)
{
	this->denumire = x.denumire;
	this->destinatie = x.destinatie;
	this->id = x.id;
	this->pret = x.pret;
	this->tip = x.tip;
	return *this;
}

// Copy Constructor
Oferta::Oferta(const Oferta& x)
{
	this->denumire = x.denumire;
	this->destinatie = x.destinatie;
	this->id = x.id;
	this->pret = x.pret;
	this->tip = x.tip;
}

/// used for UI
void Oferta::show_oferta() const {
	/// afiseaza o oferta pe ecran
	cout << this->id << "       " << this->denumire << "       " << this->destinatie
		<< "       " << this->tip << "       " << this->pret << "$\n";
}