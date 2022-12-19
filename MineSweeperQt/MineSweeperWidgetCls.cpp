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
    mineCount = 0;


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
    if (selectedDifficulty == Difficulty_Easy)
    {
        mineCount = 9 * 9;

        cellArr = new ClickableLabel * [mineCount];

        QPixmap pix = QPixmap(":/tiles/tiles/unopened.png");


        for (qint32 i = 0; i < mineCount; i++)
        {
            // Create new cell
            ClickableLabel* cell = new ClickableLabel(this);

            // Set unopened cell picture
            cell->setPixmap(pix);

            // Set coordinate
            QPoint point((i % 9) * CELL_SIZE_X, (i / 9) * CELL_SIZE_Y + 30);
            cell->setGeometry(QRect(point, QSize(CELL_SIZE_X, CELL_SIZE_Y)));

            // Set visibility
            cell->setVisible(true);

            // Save cell address
            cellArr[i] = cell;
        }

        this->setFixedSize(QSize(9 * CELL_SIZE_X, 10 * CELL_SIZE_Y));

        // Set up event handlers for cells
        for (qint32 i = 0; i < mineCount; i++)
        {
            connect(cellArr[i], SIGNAL(leftClicked()), this, SLOT(handleCellLeftClicked()));
            connect(cellArr[i], SIGNAL(rightClicked()), this, SLOT(handleCellRightClicked()));
        }
    }
}

void MineSweeperWidgetCls::handleCellLeftClicked()
{
    QPixmap pix = QPixmap(":/tiles/tiles/openedEmpty.png");

    ClickableLabel *cell = qobject_cast<ClickableLabel*>(sender());

    cell->setPixmap(pix);
}

void MineSweeperWidgetCls::handleCellRightClicked()
{
    QPixmap pix = QPixmap(":/tiles/tiles/flagged.png");

    ClickableLabel* cell = qobject_cast<ClickableLabel*>(sender());

    cell->setPixmap(pix);
}

void MineSweeperWidgetCls::destroyCells()
{
    for (qint32 i = 0; i < mineCount; i++)
    {
        QLabel* cell = cellArr[i];
        delete cell;
    }

    delete[] cellArr;

    cellArr = Q_NULLPTR;

    mineCount = 0;
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
            }

            createCells();
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
    QIcon icon = QIcon(":/faces/faces/onClicked.png");
    ui->startButton->setIcon(icon);
}

void MineSweeperWidgetCls::handleStartButtonReleased()
{
    QIcon icon = QIcon(":/faces/faces/main.png");
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
