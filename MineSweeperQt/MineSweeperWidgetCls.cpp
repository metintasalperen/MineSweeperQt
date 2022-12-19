#include "MineSweeperWidgetCls.h"
#include "ui_MineSweeperWidgetCls.h"

#include <QDebug>

MineSweeperWidgetCls::MineSweeperWidgetCls(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MineSweeperWidgetCls)
{
    ui->setupUi(this);


    // Initialize data
    selectedDifficulty = Difficulty_NotSelected;
    cellArr = Q_NULLPTR;
    cellCount = 0;
    mineSweeperObj = new MineSweeperCls();


    // Initializing game settings popup
    QStringList labels;
    labels.append(EASY_CHECKBOX_TEXT);
    labels.append(MEDIUM_CHECKBOX_TEXT);
    labels.append(HARD_CHECKBOX_TEXT);
    QStringListIterator it(labels);

    popup = new QListWidget(this);
    popup->setWindowFlags(Qt::Popup);

    while (it.hasNext())
    {
        QListWidgetItem* item = new QListWidgetItem(it.next(), popup);
        item->setCheckState(Qt::Unchecked);
        popup->addItem(item);
    }

    QListWidgetItem* item = new QListWidgetItem(APPLY_BUTTON_TEXT, popup);
    popup->addItem(item);

    // Setting font and palette for popup
    QFont font = QFont("Times", 12, QFont::Bold);
    popup->setFont(font);

    QPalette palette = popup->palette();
    palette.setColor(QPalette::Window, Qt::green);
    popup->setPalette(palette);


    // Set up connections
    connect(ui->startButton, &QPushButton::pressed, this, &MineSweeperWidgetCls::handleStartButtonPressed);
    connect(ui->startButton, &QPushButton::released, this, &MineSweeperWidgetCls::handleStartButtonReleased);
    connect(popup, &QListWidget::itemClicked, this, &MineSweeperWidgetCls::handlePopupClicked);
}

MineSweeperWidgetCls::~MineSweeperWidgetCls()
{
    if (cellArr != Q_NULLPTR)
    {
        destroyCells();
    }

    delete ui;
}

void MineSweeperWidgetCls::createCells()
{
    qint32 row = 0;
    qint32 col = 0;
    if (selectedDifficulty == Difficulty_Easy)
    {
        cellCount = EASY_ROW * EASY_COL;
        row = EASY_ROW;
        col = EASY_COL;
        this->setFixedSize(QSize(EASY_COL * CELL_SIZE_X, (EASY_ROW + 1) * CELL_SIZE_Y));
    }
    else if (selectedDifficulty == Difficulty_Medium)
    {
        cellCount = MEDIUM_ROW * MEDIUM_COL;
        row = MEDIUM_ROW;
        col = MEDIUM_COL;
        this->setFixedSize(QSize(MEDIUM_COL * CELL_SIZE_X, (MEDIUM_ROW + 1) * CELL_SIZE_Y));
    }
    else if (selectedDifficulty == Difficulty_Hard)
    {
        cellCount == HARD_ROW * HARD_COL;
        row = HARD_ROW;
        col = HARD_COL;
        this->setFixedSize(QSize(HARD_COL * CELL_SIZE_X, (HARD_ROW + 1) * CELL_SIZE_Y));
    }

    cellArr = new ClickableLabel * [cellCount];

    QPixmap pix = QPixmap(":/tiles/tiles/unopened.png");

    for (qint32 i = 0; i < cellCount; i++)
    {
        // Create new cell
        ClickableLabel* cell = new ClickableLabel(this);

        // Set unopened cell picture
        cell->setPixmap(pix);

        // Set coordinate
        QPoint point((i % col) * CELL_SIZE_X, (i / row) * CELL_SIZE_Y + CELL_SIZE_Y);
        cell->setGeometry(QRect(point, QSize(CELL_SIZE_X, CELL_SIZE_Y)));

        // Set visibility
        cell->setVisible(true);

        // Set row and col data
        cell->row = i / row;
        cell->col = i % col;

        // Save cell address
        cellArr[i] = cell;

        // Set up event handlers for cells
        connect(cellArr[i], SIGNAL(leftClicked()), this, SLOT(handleCellLeftClicked()));
        connect(cellArr[i], SIGNAL(rightClicked()), this, SLOT(handleCellRightClicked()));
    }
}

void MineSweeperWidgetCls::processMineField()
{
    const QPixmap flagged = QPixmap(TILE_FLAGGED);
    const QPixmap openedEmpty = QPixmap(TILE_OPENED_EMPTY);
    const QPixmap bomb = QPixmap(TILE_BOMB);
    const QPixmap unopened = QPixmap(TILE_UNOPENED);
    const QPixmap one = QPixmap(TILE_ONE);
    const QPixmap two = QPixmap(TILE_TWO);
    const QPixmap three = QPixmap(TILE_THREE);
    const QPixmap four = QPixmap(TILE_FOUR);
    const QPixmap five = QPixmap(TILE_FIVE);
    const QPixmap six = QPixmap(TILE_SIX);
    const QPixmap seven = QPixmap(TILE_SEVEN);
    const QPixmap eight = QPixmap(TILE_EIGHT);

    qint32 rowLimit = 0;
    qint32 colLimit = 0;
    if (selectedDifficulty == Difficulty_Easy)
    {
        rowLimit = EASY_ROW;
        colLimit = EASY_COL;
    }
    else if (selectedDifficulty == Difficulty_Medium)
    {
        rowLimit = MEDIUM_ROW;
        colLimit = MEDIUM_COL;
    }
    else if (selectedDifficulty == Difficulty_Hard)
    {
        rowLimit = HARD_ROW;
        colLimit = HARD_COL;
    }

    for (qint32 row = 0; row < rowLimit; row++)
    {
        for (qint32 col = 0; col < colLimit; col++)
        {
            qint32 index = mineSweeperObj->CalculateIndex(row, col);

            if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Unopened)
            {
                cellArr[index]->setPixmap(unopened);
            }
            else if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Flagged)
            {
                cellArr[index]->setPixmap(flagged);
            }
            else if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Opened)
            {
                if (mineSweeperObj->MineField[index].MineStatus == MineStatus_Exist)
                {
                    cellArr[index]->setPixmap(bomb);
                }
                else if (mineSweeperObj->MineField[index].MineStatus == MineStatus_NotExist)
                {
                    qint32 adjacentMineCount = mineSweeperObj->FindAdjacentMineCount(row, col);
                    switch (adjacentMineCount)
                    {
                        case 0:
                        {
                            cellArr[index]->setPixmap(openedEmpty);
                            break;
                        }
                        case 1:
                        {
                            cellArr[index]->setPixmap(one);
                            break;
                        }
                        case 2:
                        {
                            cellArr[index]->setPixmap(two);
                            break;
                        }
                        case 3:
                        {
                            cellArr[index]->setPixmap(three);
                            break;
                        }
                        case 4:
                        {
                            cellArr[index]->setPixmap(four);
                            break;
                        }
                        case 5:
                        {
                            cellArr[index]->setPixmap(five);
                            break;
                        }
                        case 6:
                        {
                            cellArr[index]->setPixmap(six);
                            break;
                        }
                        case 7:
                        {
                            cellArr[index]->setPixmap(seven);
                            break;
                        }
                        case 8:
                        {
                            cellArr[index]->setPixmap(eight);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

void MineSweeperWidgetCls::handleCellLeftClicked()
{
    ClickableLabel* cell = qobject_cast<ClickableLabel*>(sender());
    mineSweeperObj->ProcessUserInput(cell->row, cell->col, UserAction_Open);
    processMineField();
}

void MineSweeperWidgetCls::handleCellRightClicked()
{
    ClickableLabel* cell = qobject_cast<ClickableLabel*>(sender());
    mineSweeperObj->ProcessUserInput(cell->row, cell->col, UserAction_Flag);
    processMineField();
}

void MineSweeperWidgetCls::destroyCells()
{
    for (qint32 i = 0; i < cellCount; i++)
    {
        QLabel* cell = cellArr[i];
        delete cell;
    }

    delete[] cellArr;

    cellArr = Q_NULLPTR;

    cellCount = 0;
}

void MineSweeperWidgetCls::handlePopupClicked(QListWidgetItem* item)
{
    if (item->text() == APPLY_BUTTON_TEXT)
    {
        if (selectedDifficulty != Difficulty_NotSelected)
        {
            for (qint32 i = 0; i < Difficulty_NotSelected; i++)
            {
                popup->item(i)->setCheckState(Qt::Unchecked);
            }

            popup->setVisible(false);

            if (cellArr != Q_NULLPTR)
            {
                destroyCells();
                mineSweeperObj->DestroyMineField();
            }

            createCells();

            if (selectedDifficulty == Difficulty_Easy)
            {
                mineSweeperObj->SetOptions(EASY_ROW, EASY_COL, EASY_MINE_COUNT);
            }
            else if (selectedDifficulty == Difficulty_Medium)
            {
                mineSweeperObj->SetOptions(MEDIUM_ROW, MEDIUM_COL, MEDIUM_MINE_COUNT);
            }
            else if (selectedDifficulty == Difficulty_Hard)
            {
                mineSweeperObj->SetOptions(HARD_ROW, HARD_COL, HARD_MINE_COUNT);
            }
            
        }
    }
    else if (item->text() == EASY_CHECKBOX_TEXT)
    {
        selectedDifficulty = Difficulty_Easy;

        for (qint32 i = 0; i < Difficulty_NotSelected; i++)
        {
            popup->item(i)->setCheckState(Qt::Unchecked);
        }
        item->setCheckState(Qt::Checked);
    }
    else if (item->text() == MEDIUM_CHECKBOX_TEXT)
    {
        selectedDifficulty = Difficulty_Medium;

        for (qint32 i = 0; i < Difficulty_NotSelected; i++)
        {
            popup->item(i)->setCheckState(Qt::Unchecked);
        }
        item->setCheckState(Qt::Checked);
    }
    else if (item->text() == HARD_CHECKBOX_TEXT)
    {
        selectedDifficulty = Difficulty_Hard;

        for (qint32 i = 0; i < Difficulty_NotSelected; i++)
        {
            popup->item(i)->setCheckState(Qt::Unchecked);
        }
        item->setCheckState(Qt::Checked);
    }
}

void MineSweeperWidgetCls::handleStartButtonPressed()
{
    QIcon icon = QIcon(FACE_ON_CLICKED);
    ui->startButton->setIcon(icon);
}

void MineSweeperWidgetCls::handleStartButtonReleased()
{
    QIcon icon = QIcon(FACE_MAIN);
    ui->startButton->setIcon(icon);

    popup->setVisible(true);
    adjustPopup();
}

void MineSweeperWidgetCls::adjustPopup()
{
    if (popup->isVisible() == true)
    {
        QRect rect = ui->startButton->geometry();
        QPoint bottom = rect.bottomRight();
        bottom.setX(bottom.x() - 165);
        QPoint point = this->mapToGlobal(bottom);
        popup->setGeometry(QRect(point, QSize(300, 400)));
    }
}

void MineSweeperWidgetCls::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    adjustPopup();

    QSize screenSize = MineSweeperWidgetCls::size();

    ui->mineCounterFirstDigit->setGeometry(QRect(QPoint(screenSize.width() - 30, 0), QSize(30, 30)));
    ui->mineCounterSecondDigit->setGeometry(QRect(QPoint(screenSize.width() - 60, 0), QSize(30, 30)));
    ui->mineCounterThirdDigit->setGeometry(QRect(QPoint(screenSize.width() - 90, 0), QSize(30, 30)));

    ui->timeCounterFirstDigit->setGeometry(QRect(QPoint(60, 0), QSize(30, 30)));
    ui->timeCounterSecondDigit->setGeometry(QRect(QPoint(30, 0), QSize(30, 30)));
    ui->timeCounterThirdDigit->setGeometry(QRect(QPoint(0, 0), QSize(30, 30)));

    ui->startButton->setGeometry(QRect(QPoint((screenSize.width() - 30) / 2, 0), QSize(30, 30)));
}

void MineSweeperWidgetCls::moveEvent(QMoveEvent* event)
{
    QWidget::moveEvent(event);
    adjustPopup();

    QSize screenSize = MineSweeperWidgetCls::size();

    ui->mineCounterFirstDigit->setGeometry(QRect(QPoint(screenSize.width() - 30, 0), QSize(30, 30)));
    ui->mineCounterSecondDigit->setGeometry(QRect(QPoint(screenSize.width() - 60, 0), QSize(30, 30)));
    ui->mineCounterThirdDigit->setGeometry(QRect(QPoint(screenSize.width() - 90, 0), QSize(30, 30)));

    ui->timeCounterFirstDigit->setGeometry(QRect(QPoint(60, 0), QSize(30, 30)));
    ui->timeCounterSecondDigit->setGeometry(QRect(QPoint(30, 0), QSize(30, 30)));
    ui->timeCounterThirdDigit->setGeometry(QRect(QPoint(0, 0), QSize(30, 30)));

    ui->startButton->setGeometry(QRect(QPoint((screenSize.width() - 30) / 2, 0), QSize(30, 30)));
}
