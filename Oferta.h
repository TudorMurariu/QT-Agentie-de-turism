#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>

#include <vector>
using namespace std;

class Oferta
{
public:
	string denumire, destinatie, tip;
	double pret;
	int id;

	Oferta();
	Oferta(string denumire, string destinatie, string tip, double pret, int id);
	Oferta& operator =(const Oferta& x);
	bool operator ==(const Oferta& ot) noexcept {
		return id == ot.id;
	}
	Oferta(const Oferta& x);
	~Oferta() = default;
	void show_oferta() const;
};