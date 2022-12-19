#ifndef MINESWEEPERWIDGETCLS_H
#define MINESWEEPERWIDGETCLS_H

#include "EnumPkg.h"
#include "ConstPkg.h"
#include "ClickableLabel.h"
#include "MineSweeperCls.h"

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MineSweeperWidgetCls; }
QT_END_NAMESPACE

class MineSweeperWidgetCls : public QWidget
{
    Q_OBJECT

public:
    MineSweeperWidgetCls(QWidget* parent = nullptr);
    ~MineSweeperWidgetCls();

private slots:
    void handleStartButtonPressed();
    void handleStartButtonReleased();
    void handlePopupClicked(QListWidgetItem* item);
    void handleCellLeftClicked();
    void handleCellRightClicked();

private:
    Ui::MineSweeperWidgetCls* ui;

protected:
    QListWidget* popup;

    void adjustPopup();
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);

    ClickableLabel** cellArr;

public:
    DifficultyEnum selectedDifficulty;
    qint32 mineCount;
    MineSweeperCls* mineSweeperObj;

private:
    void createCells();
    void destroyCells();
};
#endif // MINESWEEPERWIDGETCLS_H
