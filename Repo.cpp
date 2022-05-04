#include "Repo.h"

Repo::Repo(vector<Oferta> l)
{
	this->Lista_oferte = l;
}

vector<Oferta> Repo::get_list()
{
	return this->Lista_oferte;
}

int Repo::cauta_id(int id)
{
	/* cautam un id dat */
	Oferta x;
	x.id = id;
	vector<Oferta>::iterator it = find(this->Lista_oferte.begin(), this->Lista_oferte.end(), x);

	int poz = distance(this->Lista_oferte.begin(), it);
	if (it != this->Lista_oferte.end())
		return poz;
	return -1;
}

Oferta Repo::cauta_denumire(string denumire)
{
	/* cautam dupa o denumire */
	Oferta x;
	vector<Oferta>::iterator it = find_if(
		this->Lista_oferte.begin(),
		this->Lista_oferte.end(),
		[denumire](const Oferta& x)
		{
			return x.denumire == denumire;
		});
	if (it == this->Lista_oferte.end())
		return x;
	return *it;
}

void Repo::Add(Oferta& x)
{
	/* Adaugam un element la finalul listei */
	this->Lista_oferte.push_back(x);

	//unique_ptr<Undo> new_undo = make_unique<Undo_Add>(this);
	this->Undo_List.push_back(make_unique<Undo_Add>(*this));
}

string Repo::Sterge(int id)
{
	/* Stergem elementul cu id ul id daca acesta exista , altfel trimitem
	un mesaj de eroare */

	const int poz = this->cauta_id(id);
	if (poz != -1)
	{
		this->Undo_List.push_back(make_unique<Undo_Delete>(*this, this->Lista_oferte.at(poz)));
		this->Lista_oferte.erase(this->Lista_oferte.begin() + poz);
		return "";
	}

	return "Nu exista o oferta cu id-ul dat";
}


string Repo::Modificare(Oferta x)
{
	/* Cautam un mesaj pentru a il modifica */

	const int poz = this->cauta_id(x.id);
	if (poz != -1)
	{
		this->Undo_List.push_back(make_unique<Undo_Modify>(*this, this->Lista_oferte.at(poz)));
		this->Lista_oferte.at(poz) = x;
		return "";
	}

	return "Nu exista o oferta cu id-ul dat";
}

void Repo::Delete_Last()
{
	// Delets the last element added
	this->Lista_oferte.pop_back();
}

void Repo::Delete_All()
{
	this->Lista_oferte.clear();
	this->Undo_List.clear();
}

string Repo::Undo_()
{
	if (this->Undo_List.empty())
		return "Nu avem la ce da undo!!!";

	this->Undo_List.back()->undo();
	this->Undo_List.pop_back();

	return "";
}