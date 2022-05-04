#pragma once
#include "Oferta.h"
#include <memory>

class Undo;

class Repo
{
private:
	//vector< Undo* > Undo_List;
	vector< unique_ptr<Undo> > Undo_List;
	vector<Oferta> Lista_oferte;

public:
	Repo(vector<Oferta> l);
	vector<Oferta> get_list();
	void Add(Oferta& x);
	int cauta_id(int id);
	Oferta cauta_denumire(string denumire);
	string Sterge(int id);
	string Modificare(Oferta x);
	void Delete_Last();
	void Delete_All();
	string Undo_();
};



class Undo {
public:
	//friend class Repo;
	virtual void undo() = 0;
	virtual ~Undo() = default;
};


class Undo_Add : public Undo {

public:
	Repo& repo;
	Undo_Add(Repo& Rep) : repo(Rep) {}
	void undo() override {
		repo.Delete_Last();
	}
};

class Undo_Delete : public Undo {

private:
	Repo& repo;
	Oferta x;

public:
	Undo_Delete(Repo& Rep, Oferta oferta) : repo(Rep), x(oferta) {}
	void undo() override {
		repo.Add(x);
	}
};

class Undo_Modify : public Undo {
private:
	Repo& repo;
	Oferta x;
public:
	Undo_Modify(Repo& Rep, Oferta oferta) : repo(Rep), x(oferta) {}
	void undo() override {
		repo.Modificare(x);
	}
};