#ifndef MINESWEEPERWIDGETCLS_H
#define MINESWEEPERWIDGETCLS_H

#include "EnumPkg.h"
#include "ConstPkg.h"
#include "ClickableLabel.h"
#include "MineSweeperCls.h"

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QTimer>

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
    void timerUpdate();

private:
    Ui::MineSweeperWidgetCls* ui;

    ClickableLabel** cellArr;
    QListWidget* popup;

    MineSweeperCls* mineSweeperObj;

    DifficultyEnum selectedDifficulty;

    QTimer* timer;
    bool isFirstClick;
    quint32 secondsSinceStart;

    quint32 mineCount;
    quint32 cellCount;


    void adjustPopup();
    void resizeEvent(QResizeEvent* event);
    void moveEvent(QMoveEvent* event);

    void createCells();
    void destroyCells();

    void printMineField();

    void updateTimeCounter();
    void updateMineCounter();
};
#endif // MINESWEEPERWIDGETCLS_H
