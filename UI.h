#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qboxlayout.h>
#include <QPushButton>
#include <QLineEdit>
#include <QtWidgets/qformlayout.h>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <qwindow.h>
#include "Service.h"
#include "oberver.h"

class CosReadOnlyGUI;

class Cos : public QWidget , public Observable {
	friend class Service;
	friend class console;
	friend class CosReadOnlyGUI;
private:
	Service& srv;

	QPushButton* goleste_cos;
	QPushButton* add;
	QPushButton* genereaza;
	QPushButton* getCos;
	QPushButton* Export;
	QPushButton* Reload;

	QGroupBox* groupBox1 = new QGroupBox(tr("ADD"));
	QGroupBox* groupBox2 = new QGroupBox(tr("Genereaza"));
	QGroupBox* groupBox3 = new QGroupBox(tr("Export"));

	QLineEdit* editAdd;
	QLineEdit* editGenereaza;
	QLineEdit* editExport;

	QLabel* lAdd = new QLabel("Denumire : ");
	QLabel* lGenereaza = new QLabel("Numarul de elemente : ");
	QLabel* lExport = new QLabel("Nume fisier : ");

	QTableWidget* tableOferte;
	QListWidget* lista_Oferte;

public:
	Cos(Service& srv);
	void build_UI();
	void connectSignalsSlots();
	void reloadList(vector<Oferta> lista_oferte);
};

class CosReadOnlyGUI : public QWidget , public Observer {
	friend class Cos;
	Cos* cos;

	QListWidget* lista_Oferte;
public:
	CosReadOnlyGUI(Cos* c) : cos(c) 
	{
		this->build_UI();
		cos->addObserver(this);
	}
	void build_UI()
	{
		lista_Oferte = new QListWidget();
		QHBoxLayout* mainly = new QHBoxLayout;
		mainly->addWidget(lista_Oferte);
		this->setLayout(mainly);
	}
	void update() override {
		this->reloadList();
	}
	void reloadList()
	{
		lista_Oferte->clear();
		for (auto elem : cos->srv.get_cos())
		{
			lista_Oferte->addItem(QString::fromStdString(elem.denumire));
		}
	}
	~CosReadOnlyGUI()
	{
		cos->removeObserver(this);
	}
};

class sterge_oferta_UI : public QWidget {
	friend class Service;
	friend class console;
private:
	Service& srv;

	QPushButton* btn;
	QLabel* label_id = new QLabel("ID-ul ofertei:");
	QLineEdit* editID;
public:
	sterge_oferta_UI(Service& srv);
	void build_UI();
	void connectSignalsSlots();
};

class modifica_oferta_UI : public QWidget {
	friend class Service;
	friend class console;
private:
	Service& srv;

	QPushButton* btn;

	QLabel* lblDenumire = new QLabel{ "Denumirea ofertei:" };
	QLabel* lblDestinatie = new QLabel{ "Destinatia ofertei:" };
	QLabel* lblTip = new QLabel{ "Tipul ofertei:" };
	QLabel* lblPret = new QLabel{ "Pretul ofertei:" };
	QLabel* label_id = new QLabel("ID-ul ofertei:");

	QLineEdit* editDenumire;
	QLineEdit* editDestinatie;
	QLineEdit* editTip;
	QLineEdit* editPret;
	QLineEdit* editID;
public:
	modifica_oferta_UI(Service& srv);
	void build_UI();
	void connectSignalsSlots();
};

class console : public QWidget {
	friend class Service;
private:
	Service& srv;

	// variabilele pentru ui :

	Cos* cos;
	CosReadOnlyGUI* cosROnly;
	sterge_oferta_UI* sterge;
	modifica_oferta_UI* modifica;

	QPushButton* open_cos;
	QPushButton* UNDO;

	QLabel* lblDenumire = new QLabel{ "Denumirea ofertei:" };
	QLabel* lblDestinatie = new QLabel{ "Destinatia ofertei:" };
	QLabel* lblTip = new QLabel{ "Tipul ofertei:" };
	QLabel* lblPret = new QLabel{ "Pretul ofertei:" };

	QLineEdit* editDenumire;
	QLineEdit* editDestinatie;
	QLineEdit* editTip;
	QLineEdit* editPret;

	QPushButton* btnAddOferta;
	QPushButton* btnStergeOferta;
	QPushButton* btnModificaOferta;

	QPushButton* btnAdaugaPredefinite;

	QPushButton* btnExport;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));
	QGroupBox* groupBox2 = new QGroupBox();
	QGroupBox* groupBox3 = new QGroupBox(tr("Tip filtrare"));

	QRadioButton* radioSrt_denumire = new QRadioButton(QString::fromStdString("denumire"));
	QRadioButton* radioSrt_destinatie = new QRadioButton(QString::fromStdString("destinatie"));
	QRadioButton* radioSrt_tip_pret = new QRadioButton(QString::fromStdString("tip si pret"));
	QPushButton* btnSortOferte;

	QLabel* lblFilterCriteria = new QLabel{ "Dupa ce filtram:" };
	QLineEdit* editFilterGen;
	QPushButton* btnFilterOferte1;
	QPushButton* btnFilterOferte2;

	QPushButton* btnReloadData;

	QTableWidget* tableOferte;
	QListWidget* lista_Oferte;

public:
	console(Service& srv);
	void reloadList(vector<Oferta> lista_oferte);
	void build_UI();
	void connectSignalsSlots();
	void guiAddOferta();
};
 