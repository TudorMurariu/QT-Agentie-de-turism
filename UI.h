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

class console : public QWidget {
	friend class Service;
private:
	Service& srv;

	// variabilele pentru ui :

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
 