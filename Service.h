#pragma once
#include "Oferta.h"
#include "Repo.h"
#include "Validators.h"
#include "wishlist_Repo.h"
#include <unordered_map>

class Service
{
	friend class console;
private:
	wish_list wish;
	Repo& repo;
	Valid valid;
public:
	Service() = default;
	Service(Repo& repo1, wish_list wish1, Valid valid1);
	string Adauga(string denumire, string destinatie, string tip, string pret);
	string Sterge(string id);
	string Modifica(string denumire, string destinatie, string tip, string pret, string id);
	vector<Oferta> Filtrare1(string dest, vector<Oferta> v);
	vector<Oferta> Filtrare2(double pret, vector<Oferta> v);
	vector<Oferta> Sortare(int x, vector<Oferta> v);
	void Adaugare_Predefinite();
	vector<Oferta> get_list();
	void goleste_cos();
	string add_in_wish(string denumire);
	void genereaza(int x);
	vector<Oferta> get_cos();
	unordered_map<string, int> getFrecvente();
	string Export(string fisier);
	string Undo();
	void Delete_All();
};

void test_service(Service& srv);
void test_adauga(Service& srv);
void test_stergere(Service& srv);
void test_modificare(Service& srv);
void test_Filtrare1(Service& srv);
void test_Filtrare2(Service& srv);
void test_Sortare(Service& srv);
void test_wish_list(Service& srv);
void test_map(Service& srv);
void test_Export(Service& srv);
void test_Undo(Service& srv);