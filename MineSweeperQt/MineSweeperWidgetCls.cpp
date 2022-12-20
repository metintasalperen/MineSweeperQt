#include "MineSweeperWidgetCls.h"
#include "ui_MineSweeperWidgetCls.h"

MineSweeperWidgetCls::MineSweeperWidgetCls(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MineSweeperWidgetCls)
{
    ui->setupUi(this);


    // Initialize data
    selectedDifficulty = Difficulty_NotSelected;
    cellArr = Q_NULLPTR;
    mineCount = 0;
    cellCount = 0;
    secondsSinceStart = 0;
    isFirstClick = true;
    mineSweeperObj = new MineSweeperCls();
    timer = new QTimer(this);
    timer->setInterval(ONE_SEC_IN_MSEC);

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
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

void MineSweeperWidgetCls::timerUpdate()
{
    secondsSinceStart = secondsSinceStart + 1;
    updateTimeCounter();
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
    quint32 col = 0;
    if (selectedDifficulty == Difficulty_Easy)
    {
        cellCount = EASY_ROW * EASY_COL;
        col = EASY_COL;
        this->setFixedSize(QSize(EASY_COL * CELL_SIZE_X, (EASY_ROW + 1) * CELL_SIZE_Y));
    }
    else if (selectedDifficulty == Difficulty_Medium)
    {
        cellCount = MEDIUM_ROW * MEDIUM_COL;
        col = MEDIUM_COL;
        this->setFixedSize(QSize(MEDIUM_COL * CELL_SIZE_X, (MEDIUM_ROW + 1) * CELL_SIZE_Y));
    }
    else if (selectedDifficulty == Difficulty_Hard)
    {
        cellCount = HARD_ROW * HARD_COL;
        col = HARD_COL;
        this->setFixedSize(QSize(HARD_COL * CELL_SIZE_X, (HARD_ROW + 1) * CELL_SIZE_Y));
    }

    cellArr = new ClickableLabel * [cellCount];

    QPixmap pix = QPixmap(":/tiles/tiles/unopened.png");

    for (quint32 i = 0; i < cellCount; i++)
    {
        // Create new cell
        ClickableLabel* cell = new ClickableLabel(this);

        // Set unopened cell picture
        cell->setPixmap(pix);

        // Set coordinate
        QPoint point(static_cast<qint32>((i % col) * CELL_SIZE_X), static_cast<qint32>((i / col) * CELL_SIZE_Y + CELL_SIZE_Y));
        cell->setGeometry(QRect(point, QSize(CELL_SIZE_X, CELL_SIZE_Y)));

        // Set visibility
        cell->setVisible(true);

        // Set row and col data
        cell->row = i / col;
        cell->col = i % col;

        // Save cell address
        cellArr[i] = cell;

        // Set up event handlers for cells
        connect(cellArr[i], SIGNAL(leftClicked()), this, SLOT(handleCellLeftClicked()));
        connect(cellArr[i], SIGNAL(rightClicked()), this, SLOT(handleCellRightClicked()));
    }
}

void MineSweeperWidgetCls::printMineField()
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

    GameStatusEnum gameStatus = mineSweeperObj->CheckGameStatus();
    bool isGameEnded = false;
    if (gameStatus == GameStatus_Win || gameStatus == GameStatus_Lose)
    {
        isGameEnded = true;
    }

    quint32 rowLimit = 0;
    quint32 colLimit = 0;
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

    for (quint32 row = 0; row < rowLimit; row++)
    {
        for (quint32 col = 0; col < colLimit; col++)
        {
            quint32 index = mineSweeperObj->CalculateIndex(row, col);

            if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Unopened)
            {
                if (isGameEnded == true)
                {
                    if (mineSweeperObj->MineField[index].MineStatus == MineStatus_Exist)
                    {
                        cellArr[index]->setPixmap(bomb);
                    }
                    else
                    {
                        cellArr[index]->setPixmap(unopened);
                    }
                }
                else
                {
                    cellArr[index]->setPixmap(unopened);
                }
            }
            else if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Flagged)
            {
                if (isGameEnded == true)
                {
                    cellArr[index]->setPixmap(bomb);
                }
                else
                {
                    cellArr[index]->setPixmap(flagged);
                }
            }
            else if (mineSweeperObj->MineField[index].TileStatus == TileStatus_Opened)
            {
                if (mineSweeperObj->MineField[index].MineStatus == MineStatus_Exist)
                {
                    cellArr[index]->setPixmap(bomb);
                }
                else if (mineSweeperObj->MineField[index].MineStatus == MineStatus_NotExist)
                {
                    quint32 adjacentMineCount = mineSweeperObj->FindAdjacentMineCount(row, col);
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

void MineSweeperWidgetCls::updateTimeCounter()
{
    qint32 firstDigit = 0;
    qint32 secondDigit = 0;
    qint32 thirdDigit = 0;

    if (secondsSinceStart > 999)
    {
        firstDigit = 9;
        secondDigit = 9;
        thirdDigit = 9;
    }
    else
    {
        firstDigit = secondsSinceStart % 10;
        secondDigit = (secondsSinceStart / 10) % 10;
        thirdDigit = secondsSinceStart / 100;
    }

    const QPixmap zero(COUNTER_ZERO);
    const QPixmap one(COUNTER_ONE);
    const QPixmap two(COUNTER_TWO);
    const QPixmap three(COUNTER_THREE);
    const QPixmap four(COUNTER_FOUR);
    const QPixmap five(COUNTER_FIVE);
    const QPixmap six(COUNTER_SIX);
    const QPixmap seven(COUNTER_SEVEN);
    const QPixmap eight(COUNTER_EIGHT);
    const QPixmap nine(COUNTER_NINE);

    switch (firstDigit)
    {
    case 0:
    {
        ui->timeCounterFirstDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->timeCounterFirstDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->timeCounterFirstDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->timeCounterFirstDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->timeCounterFirstDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->timeCounterFirstDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->timeCounterFirstDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->timeCounterFirstDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->timeCounterFirstDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->timeCounterFirstDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }

    switch (secondDigit)
    {
    case 0:
    {
        ui->timeCounterSecondDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->timeCounterSecondDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->timeCounterSecondDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->timeCounterSecondDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->timeCounterSecondDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->timeCounterSecondDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->timeCounterSecondDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->timeCounterSecondDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->timeCounterSecondDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->timeCounterSecondDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }

    switch (thirdDigit)
    {
    case 0:
    {
        ui->timeCounterThirdDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->timeCounterThirdDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->timeCounterThirdDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->timeCounterThirdDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->timeCounterThirdDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->timeCounterThirdDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->timeCounterThirdDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->timeCounterThirdDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->timeCounterThirdDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->timeCounterThirdDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }
}

void MineSweeperWidgetCls::updateMineCounter()
{
    const QPixmap zero(COUNTER_ZERO);
    const QPixmap one(COUNTER_ONE);
    const QPixmap two(COUNTER_TWO);
    const QPixmap three(COUNTER_THREE);
    const QPixmap four(COUNTER_FOUR);
    const QPixmap five(COUNTER_FIVE);
    const QPixmap six(COUNTER_SIX);
    const QPixmap seven(COUNTER_SEVEN);
    const QPixmap eight(COUNTER_EIGHT);
    const QPixmap nine(COUNTER_NINE);

    quint32 flag = mineSweeperObj->CalculateFlagCount();

    if (flag > mineCount)
    {
        ui->mineCounterFirstDigit->setPixmap(zero);
        ui->mineCounterSecondDigit->setPixmap(zero);
        ui->mineCounterThirdDigit->setPixmap(zero);
        return;
    }

    quint32 remainingMine = 0;
    remainingMine = mineCount - flag;

    qint32 firstDigit = remainingMine % 10;
    qint32 secondDigit = (remainingMine / 10) % 10;
    qint32 thirdDigit = remainingMine / 100;


    switch (firstDigit)
    {
    case 0:
    {
        ui->mineCounterFirstDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->mineCounterFirstDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->mineCounterFirstDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->mineCounterFirstDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->mineCounterFirstDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->mineCounterFirstDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->mineCounterFirstDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->mineCounterFirstDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->mineCounterFirstDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->mineCounterFirstDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }

    switch (secondDigit)
    {
    case 0:
    {
        ui->mineCounterSecondDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->mineCounterSecondDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->mineCounterSecondDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->mineCounterSecondDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->mineCounterSecondDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->mineCounterSecondDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->mineCounterSecondDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->mineCounterSecondDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->mineCounterSecondDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->mineCounterSecondDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }

    switch (thirdDigit)
    {
    case 0:
    {
        ui->mineCounterThirdDigit->setPixmap(zero);
        break;
    }
    case 1:
    {
        ui->mineCounterThirdDigit->setPixmap(one);
        break;
    }
    case 2:
    {
        ui->mineCounterThirdDigit->setPixmap(two);
        break;
    }
    case 3:
    {
        ui->mineCounterThirdDigit->setPixmap(three);
        break;
    }
    case 4:
    {
        ui->mineCounterThirdDigit->setPixmap(four);
        break;
    }
    case 5:
    {
        ui->mineCounterThirdDigit->setPixmap(five);
        break;
    }
    case 6:
    {
        ui->mineCounterThirdDigit->setPixmap(six);
        break;
    }
    case 7:
    {
        ui->mineCounterThirdDigit->setPixmap(seven);
        break;
    }
    case 8:
    {
        ui->mineCounterThirdDigit->setPixmap(eight);
        break;
    }
    case 9:
    {
        ui->mineCounterThirdDigit->setPixmap(nine);
        break;
    }
    default:
    {
        break;
    }
    }
}

void MineSweeperWidgetCls::handleCellLeftClicked()
{
    const QIcon win = QIcon(FACE_WIN);
    const QIcon lose = QIcon(FACE_LOSE);

    GameStatusEnum gameStatus = mineSweeperObj->CheckGameStatus();
    if (gameStatus == GameStatus_Lose)
    {
        ui->startButton->setIcon(lose);
        timer->stop();
        updateMineCounter();
    }
    else if (gameStatus == GameStatus_Win)
    {
        ui->startButton->setIcon(win);
        timer->stop();
        updateMineCounter();
    }
    else if (gameStatus == GameStatus_InProgress)
    {
        ClickableLabel* cell = qobject_cast<ClickableLabel*>(sender());
        mineSweeperObj->ProcessUserInput(cell->row, cell->col, UserAction_Open);
        printMineField();

        gameStatus = mineSweeperObj->CheckGameStatus();
        if (gameStatus == GameStatus_Lose)
        {
            ui->startButton->setIcon(lose);
            timer->stop();
        }
        else if (gameStatus == GameStatus_Win)
        {
            ui->startButton->setIcon(win);
            timer->stop();
        }
        updateMineCounter();
    }

    if (isFirstClick == true)
    {
        timer->start();
        isFirstClick = false;
    }
}

void MineSweeperWidgetCls::handleCellRightClicked()
{
    const QIcon win = QIcon(FACE_WIN);
    const QIcon lose = QIcon(FACE_LOSE);

    GameStatusEnum gameStatus = mineSweeperObj->CheckGameStatus();
    if (gameStatus == GameStatus_Lose)
    {
        ui->startButton->setIcon(lose);
        timer->stop();
    }
    else if (gameStatus == GameStatus_Win)
    {
        ui->startButton->setIcon(win);
        timer->stop();
    }
    else if (gameStatus == GameStatus_InProgress)
    {
        ClickableLabel* cell = qobject_cast<ClickableLabel*>(sender());
        mineSweeperObj->ProcessUserInput(cell->row, cell->col, UserAction_Flag);
        printMineField();
    }
    updateMineCounter();
}

void MineSweeperWidgetCls::destroyCells()
{
    for (quint32 i = 0; i < cellCount; i++)
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

            if (selectedDifficulty == Difficulty_Easy)
            {
                mineSweeperObj->SetOptions(EASY_ROW, EASY_COL, EASY_MINE_COUNT);
                mineCount = EASY_MINE_COUNT;
            }
            else if (selectedDifficulty == Difficulty_Medium)
            {
                mineSweeperObj->SetOptions(MEDIUM_ROW, MEDIUM_COL, MEDIUM_MINE_COUNT);
                mineCount = MEDIUM_MINE_COUNT;
            }
            else if (selectedDifficulty == Difficulty_Hard)
            {
                mineSweeperObj->SetOptions(HARD_ROW, HARD_COL, HARD_MINE_COUNT);
                mineCount = HARD_MINE_COUNT;
            }

            createCells();

            isFirstClick = true;
            secondsSinceStart = 0;
            timer->stop();

            updateTimeCounter();
            updateMineCounter();
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
