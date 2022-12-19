#pragma once

#include <QtWidgets/QWidget>
#include "ui_MineSweeperWidgetCls.h"

class MineSweeperWidgetCls : public QWidget
{
    Q_OBJECT

public:
    MineSweeperWidgetCls(QWidget *parent = nullptr);
    ~MineSweeperWidgetCls();

private:
    Ui::MineSweeperWidgetClsClass ui;
};
