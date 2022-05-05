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
#include "Service.h"

class Cos : public QWidget {
	friend class Service;
	friend class console;
private:
	Service& srv;

	QPushButton* goleste_cos;
	QPushButton* add;
	QPushButton* genereaza;
	QPushButton* getCos;
	QPushButton* Export;

public:
	Cos(Service& srv);
	void build_UI();
	void connectSignalsSlots();
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

	QRadioButton* radioSrt_denumire = new QRadioButton(QString::fromStdString("denumire"));
	QRadioButton* radioSrt_destinatie = new QRadioButton(QString::fromStdString("destinatie"));
	QRadioButton* radioSrt_tip_pret = new QRadioButton(QString::fromStdString("tip si pret"));
	QPushButton* btnSortOferte;

	QLabel* lblFilterCriteria = new QLabel{ "Dupa ce filtram:" };
	QLineEdit* editFilterGen;
	QPushButton* btnFilterOferte1;
	QPushButton* btnFilterOferte2;

	QPushButton* btnReloadData;

	QTableWidget* tableSongs;

public:
	console(Service& srv);
	void reloadList(vector<Oferta> lista_oferte);
	void build_UI();
	void connectSignalsSlots();
	void guiAddOferta();
};
 