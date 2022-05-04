#include "UI.h"

console::console(Service& s) : srv(s) {}

void console ::build_UI()
{
	// coloram background-ul
	QPalette pal = QPalette();
	QFont font("Times", 12, QFont::Bold);
	//#9999ff
	pal.setColor(QPalette::Window, "#008080");
	pal.setColor(QPalette::WindowText, "#000080");
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->setFont(font);

    //main layout
    // layout orizontal
    QHBoxLayout* lyMain = new QHBoxLayout;
    this->setLayout(lyMain);
	lyMain->setSpacing(10);

	/*QPushButton* b = new QPushButton("meow");
	lyMain->addWidget(b);*/

    //left part of the window
    //pentru aceasta parte setam layout vertical
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    // partea dreapta
    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);
    editDenumire = new QLineEdit;
    editDestinatie = new QLineEdit;
    editTip = new QLineEdit;
    editPret = new QLineEdit;

    lyForm->addRow(lblDenumire, editDenumire);
    lyForm->addRow(lblDestinatie, editDestinatie);
    lyForm->addRow(lblTip, editTip);
    lyForm->addRow(lblPret, editPret);
    btnAddOferta = new QPushButton("Adauga");
	btnStergeOferta = new QPushButton("Sterge");
	btnModificaOferta = new QPushButton("Modifica");

	QWidget* butoane_faine = new QWidget;
	QHBoxLayout* hl = new QHBoxLayout;
	hl->addWidget(btnAddOferta);
	hl->addWidget(btnStergeOferta);
	hl->addWidget(btnModificaOferta);
	butoane_faine->setLayout(hl);

	lyForm->addWidget(butoane_faine);

    //adaugam toate componentele legate de adaugare melodie
    //in layout-ul care corespunde partii din stanga a ferestrei
    lyLeft->addWidget(form);


	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrt_denumire);
	lyRadioBox->addWidget(radioSrt_destinatie);
	lyRadioBox->addWidget(radioSrt_tip_pret);

	btnSortOferte = new QPushButton("Sorteaza oferte");
	lyRadioBox->addWidget(btnSortOferte);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa gen 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterGen = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterGen);
	btnFilterOferte1 = new QPushButton("Filtreaza oferte dupa destinatie");
	btnFilterOferte2 = new QPushButton("Filtreaza oferte dupa pret");

	lyLeft->addWidget(formFilter);
	QWidget* filter_btns = new QWidget;
	QHBoxLayout* hl_filter = new QHBoxLayout;
	filter_btns->setLayout(hl_filter);
	hl_filter->addWidget(btnFilterOferte1);
	hl_filter->addWidget(btnFilterOferte2);

	lyLeft->addWidget(filter_btns);
	//lyLeft->addStretch();

	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);


	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 5;
	this->tableSongs = new QTableWidget{ noLines, noColumns }; 

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Denumire" << "Destinatie" << "Tip" << "Pret" << "ID";
	this->tableSongs->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableSongs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	btnAdaugaPredefinite = new QPushButton("Adauga Predefinite");

	lyRight->addWidget(tableSongs);
	lyRight->addWidget(btnAdaugaPredefinite);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}

void console::reloadList(vector<Oferta> lista_oferte) {
	this->tableSongs->clearContents();
	this->tableSongs->setRowCount(lista_oferte.size());

	int lineNumber = 0;
	for (auto& oferta : lista_oferte) {
		this->tableSongs->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(oferta.denumire)));
		this->tableSongs->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(oferta.destinatie)));
		this->tableSongs->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(oferta.tip)));
		this->tableSongs->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(oferta.pret)));
		this->tableSongs->setItem(lineNumber, 4, new QTableWidgetItem(QString::number(oferta.id)));
		lineNumber++;
	}
}

void console::connectSignalsSlots() {
	QObject::connect(btnAddOferta, &QPushButton::clicked, this, &console::guiAddOferta);

	QObject::connect(btnSortOferte, &QPushButton::clicked, [&]() {
		if (this->radioSrt_denumire->isChecked())
			this->reloadList(srv.Sortare(1, srv.get_list()));
		else if (this->radioSrt_destinatie->isChecked())
			this->reloadList(srv.Sortare(2, srv.get_list()));
		else if (this->radioSrt_tip_pret->isChecked())
			this->reloadList(srv.Sortare(3, srv.get_list()));
		});

	QObject::connect(btnFilterOferte1, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		this->reloadList(srv.Filtrare1(filterC,srv.get_list()));
		});

	QObject::connect(btnFilterOferte2, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		Valid v;
		if (!v.is_pret(filterC))
		{
			QMessageBox::warning(this, QString::fromStdString("Eroare!!!"), QString::fromStdString("Pret incorect"));
			return;
		}
		double pret = stod(filterC);
		this->reloadList(srv.Filtrare2(pret, srv.get_list()));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadList(srv.get_list());
		});

	QObject::connect(btnAdaugaPredefinite, &QPushButton::clicked, [&]() {
		this->srv.Adaugare_Predefinite();
		});
}

void console::guiAddOferta()
{
	string denumire = this->editDenumire->text().toStdString();
	string destinatie = this->editDestinatie->text().toStdString();
	string tip = this->editTip->text().toStdString();
	string pret = this->editPret->text().toStdString();

	string error = srv.Adauga(denumire, destinatie, tip, pret);
	if (error != "") // daca apare eroare
		QMessageBox::warning(this, QString::fromStdString("Eorare!!!"), QString::fromStdString(error));
}