#pragma once

#include <QAbstractTableModel>
#include "Oferta.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Oferta> oferte;
public:
	MyTableModel(const std::vector<Oferta>& oferte) :oferte{ oferte } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return oferte.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		
		if (role == Qt::DisplayRole) {

			Oferta p = oferte[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.denumire);
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.destinatie);
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.tip);
			}
			else if (index.column() == 3) {
				return QString::number(p.pret);
			}
			else {
				return QString::number(p.id);
			}
		}

		return QVariant{};
	}

	void setOfterte(const vector<Oferta>& oferte) {
		this->oferte = oferte;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
		QModelIndex bottomRight1 = createIndex(0, 0);
		QModelIndex topLeft1 = createIndex(rowCount(), columnCount());
		emit dataChanged(bottomRight1, topLeft1);
		emit layoutChanged();
	}
};


class MyListModel : public QAbstractTableModel {
	std::vector<Oferta> oferte;
public:
	MyListModel(const std::vector<Oferta>& oferte) : oferte{ oferte } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return oferte.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		/*if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto sp = oferte[index.row()].getSpecies();
			return QString::fromStdString(sp);
		}
		if (role == Qt::UserRole) {
			auto tp = oferte[index.row()].getType();
			return QString::fromStdString(tp);
		}*/

		return QVariant{};
	}
};