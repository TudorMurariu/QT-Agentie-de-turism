#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Agentiedeturismqt.h"

class Agentiedeturismqt : public QMainWindow
{
    Q_OBJECT

public:
    Agentiedeturismqt(QWidget *parent = Q_NULLPTR);

private:
    Ui::AgentiedeturismqtClass ui;
};
