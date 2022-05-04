#include "wishlist_Repo.h"

void wish_list::goleste_cos() noexcept {
	this->Lista.clear();
}

void wish_list::add(Oferta x)
{
	this->Lista.push_back(x);
}

void wish_list::genereaza(int x, vector<Oferta> v)
{
	/// generam x oferte

	this->goleste_cos();

	shuffle(v.begin(), v.end(), default_random_engine(time(0)));
	for (int i = 0; i < x && !v.empty(); i++)
	{
		this->add(v.back());
		v.pop_back();
	}
}

vector<Oferta> wish_list::getList()
{
	return this->Lista;
}

void wish_list::Export(string nume_fisier)
{
	ofstream fout(nume_fisier);

	if (nume_fisier.at(0) % 2)
	{
		fout << "<html>";
		fout << "<style> p {text-align: center;} body{background-color: #E6E6FA;} </style>";
		fout << "<body>";
		fout << "<big><big><p><big><b>id &nbsp;&nbsp; denumire &nbsp;&nbsp; destinatie &nbsp;&nbsp; tip &nbsp;&nbsp; pret</b></big><br>";
		for (auto& x : this->Lista)
		{
			fout << x.id << "&nbsp;&nbsp;&nbsp;&nbsp;" << x.denumire << "&nbsp;&nbsp;&nbsp;&nbsp;" << x.destinatie
				<< "&nbsp;&nbsp;&nbsp;&nbsp;" << x.tip << "&nbsp;&nbsp;&nbsp;&nbsp;" << x.pret << "<br>";
		}
		fout << "</p></big></big></body>";
		fout << "<html>";
	}
	else
	{
		fout << "<html>";
		fout << "<style> table, th, td {border:1px solid black} body{background-color: #E6E6FA;} </style>";
		fout << "<body>";
		fout << "<table><tr><th>id</th> <th>denumire</th> <th>destinatie</th> <th>tip </th><th>pret</th></tr>";
		for (auto& x : this->Lista)
		{
			fout << "<tr><td>" << x.id << "<td>" << x.denumire << "</td><td>" << x.destinatie
				<< "</td><td>" << x.tip << "</td><td>" << x.pret << "</td></tr>";
		}
		fout << "</table></body>";
		fout << "<html>";
	}
}