#include "MineSweeperCls.h"
#include <new>
#include <QRandomGenerator>

// TL  T  TR
//  \  |  /
//   \ | /
// L--Cell--R
//   / | \
//  /  |  \
// BL  B  BR
//
// TL   -> Top Left     (row - 1, column - 1)
// T    -> Top          (row - 1, column)
// TR   -> Top Right    (row - 1, column + 1)
// L    -> Left         (row, column - 1)
// Cell -> Current Cell (row, column)
// R    -> Right        (row, column + 1)
// BL   -> Bottom Left  (row + 1, column - 1)
// B    -> Bottom       (row + 1, column)
// BR   -> Bottom Right (row + 1, column + 1)

unsigned int MineSweeperCls::FindAdjacentMineCount(unsigned int row, unsigned int column)
{
    unsigned int mineCount = 0;
    unsigned int index = 0;
    // Top left corner
    // Only check R, BR, B
    if ((row == 0) && (column == 0))
    {
        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Top right corner
    // Only check L, BL, B
    else if ((row == 0) && (column == MaxColumn - 1))
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Bottom left corner
    // Only check R, TR, T
    else if ((row == MaxRow - 1) && (column == 0))
    {
        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Bottom right corner
    // Only check L, TL, T
    else if ((row == MaxRow - 1) && (column == MaxColumn - 1))
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Left but not corner
    // Only check T, TR, R, BR, B
    else if (column == 0)
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Right but not corner
    // Only check T, TL, L, BL, B
    else if (column == MaxColumn - 1)
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

    }
    // Top but not corner
    // Only check L, BL, B, BR, R
    else if (row == 0)
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Bottom but not corner
    // Only check L, TL, T, TR, R
    else if (row == MaxRow - 1)
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }
    // Not in any border
    // Check every neighbor
    // T, TR, R, BR, B, BL, L, TL
    else
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            mineCount = mineCount + 1;
        }
    }

    return mineCount;
};

unsigned int MineSweeperCls::FindAdjacentFlagCount(unsigned int row, unsigned int column)
{
    unsigned int flagCount = 0;
    unsigned int index = 0;
    // Top left corner
    // Only check R, BR, B
    if ((row == 0) && (column == 0))
    {
        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Top right corner
    // Only check L, BL, B
    else if ((row == 0) && (column == MaxColumn - 1))
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Bottom left corner
    // Only check R, TR, T
    else if ((row == MaxRow - 1) && (column == 0))
    {
        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Bottom right corner
    // Only check L, TL, T
    else if ((row == MaxRow - 1) && (column == MaxColumn - 1))
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Left but not corner
    // Only check T, TR, R, BR, B
    else if (column == 0)
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Right but not corner
    // Only check T, TL, L, BL, B
    else if (column == MaxColumn - 1)
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

    }
    // Top but not corner
    // Only check L, BL, B, BR, R
    else if (row == 0)
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Bottom but not corner
    // Only check L, TL, T, TR, R
    else if (row == MaxRow - 1)
    {
        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }
    // Not in any border
    // Check every neighbor
    // T, TR, R, BR, B, BL, L, TL
    else
    {
        // Checking Top cell
        index = CalculateIndex(row - 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Right cell
        index = CalculateIndex(row - 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Right cell
        index = CalculateIndex(row, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Right cell
        index = CalculateIndex(row + 1, column + 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom cell
        index = CalculateIndex(row + 1, column);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Bottom Left cell
        index = CalculateIndex(row + 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Left cell
        index = CalculateIndex(row, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }

        // Checking Top Left cell
        index = CalculateIndex(row - 1, column - 1);
        if (MineField[index].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }

    return flagCount;
};

unsigned int MineSweeperCls::CalculateFlagCount()
{
    unsigned int flagCount = 0;
    unsigned int size = MaxColumn * MaxRow;

    for (unsigned int i = 0; i < size; i++)
    {
        if (MineField[i].TileStatus == TileStatus_Flagged)
        {
            flagCount = flagCount + 1;
        }
    }

    return flagCount;
}

MineSweeperCls::MineSweeperCls()
{
    // Initialize data
    GameState = GameStatus_InProgress;
    MaxRow = 0;
    MaxColumn = 0;
    MineCount = 0;
    FirstInput = true;
    MineField = nullptr;

    QRandomGenerator::securelySeeded();
};

MineSweeperCls::~MineSweeperCls()
{
    DestroyMineField();
}

ResultEnum MineSweeperCls::SetOptions(unsigned int row, unsigned int column, unsigned int mineCount)
{
    MaxRow = row;
    MaxColumn = column;
    MineCount = mineCount;
    FirstInput = true;
    GameState = GameStatus_InProgress;

    ResultEnum result = CreateMineField();

    if (result == Result_MemoryAllocationError)
    {
        MaxRow = 0;
        MaxColumn = 0;
        MineCount = 0;
    }

    return result;
};

unsigned int MineSweeperCls::CalculateIndex(unsigned int row, unsigned int column)
{
    unsigned int index = (MaxColumn * row) + column;
    return index;
};

ResultEnum MineSweeperCls::CreateMineField()
{
    const unsigned int mineFieldSize = MaxRow * MaxColumn;
    ResultEnum result = Result_Success;

    DestroyMineField();

    TileStc* tileStc = new (std::nothrow) TileStc[mineFieldSize];

    if (tileStc != nullptr)
    {
        for (unsigned int row = 0; row < MaxRow; row++)
        {
            for (unsigned int column = 0; column < MaxColumn; column++)
            {
                unsigned int index = CalculateIndex(row, column);

                tileStc[index].MineStatus = MineStatus_NotExist;
                tileStc[index].TileStatus = TileStatus_Unopened;
            }
        }

        MineField = tileStc;
    }
    else
    {
        result = Result_MemoryAllocationError;
    }

    return result;
};

void MineSweeperCls::DestroyMineField()
{
    if (MineField != nullptr)
    {
        delete[] MineField;
        MineField = nullptr;
    }
}

void MineSweeperCls::ProcessUserInput(unsigned int row, unsigned int column, UserActionEnum userAction)
{
    if (userAction == UserAction_Flag)
    {
        FlagCell(row, column);
    }
    else if (userAction == UserAction_Open)
    {
        if (FirstInput == true)
        {
            FirstInput = false;
            PlaceMines(row, column);
        }

        OpenCell(row, column, true, false);
    }

    GameState = CheckGameStatus();
};

void MineSweeperCls::FlagCell(unsigned int row, unsigned int column)
{
    unsigned int index = CalculateIndex(row, column);

    if (MineField[index].TileStatus == TileStatus_Unopened)
    {
        MineField[index].TileStatus = TileStatus_Flagged;
    }
    else if (MineField[index].TileStatus == TileStatus_Flagged)
    {
        MineField[index].TileStatus = TileStatus_Unopened;
    }
};

void MineSweeperCls::PlaceMines(unsigned int row, unsigned int column)
{
    unsigned int index = CalculateIndex(row, column);

    unsigned int size = MaxRow * MaxColumn;

    // Top Left corner
    // Only R, BR, B valid
    if ((row == 0) && (column == 0))
    {
        unsigned int rightIndex = CalculateIndex(row, column + 1);
        unsigned int bottomRightIndex = CalculateIndex(row + 1, column + 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == rightIndex) ||
                (randomMineLocation == bottomRightIndex) ||
                (randomMineLocation == bottomIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Top right corner
    // Only L, BL, B valid
    else if ((row == 0) && (column == MaxColumn - 1))
    {
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int bottomLeftIndex = CalculateIndex(row + 1, column - 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == bottomLeftIndex) ||
                (randomMineLocation == bottomIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Bottom left corner
    // Only R, TR, T valid
    else if ((row == MaxRow - 1) && (column == 0))
    {
        unsigned int rightIndex = CalculateIndex(row, column + 1);
        unsigned int topRightIndex = CalculateIndex(row - 1, column + 1);
        unsigned int topIndex = CalculateIndex(row - 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == rightIndex) ||
                (randomMineLocation == topRightIndex) ||
                (randomMineLocation == topIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Bottom right corner
    // Only check L, TL, T
    else if ((row == MaxRow - 1) && (column == MaxColumn - 1))
    {
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int topleftIndex = CalculateIndex(row - 1, column - 1);
        unsigned int topIndex = CalculateIndex(row - 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == topleftIndex) ||
                (randomMineLocation == topIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Left but not corner
    // Only check T, TR, R, BR, B
    else if (column == 0)
    {
        unsigned int topIndex = CalculateIndex(row - 1, column);
        unsigned int topRightIndex = CalculateIndex(row - 1, column + 1);
        unsigned int rightIndex = CalculateIndex(row, column + 1);
        unsigned int bottomRightIndex = CalculateIndex(row + 1, column + 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == topIndex) ||
                (randomMineLocation == topRightIndex) ||
                (randomMineLocation == rightIndex) ||
                (randomMineLocation == bottomRightIndex) ||
                (randomMineLocation == bottomIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Right but not corner
    // Only T, TL, L, BL, B valid
    else if (column == MaxColumn - 1)
    {
        unsigned int topIndex = CalculateIndex(row - 1, column);
        unsigned int topLeftIndex = CalculateIndex(row - 1, column - 1);
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int bottomLeftIndex = CalculateIndex(row + 1, column - 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == topIndex) ||
                (randomMineLocation == topLeftIndex) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == bottomLeftIndex) ||
                (randomMineLocation == bottomIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Top but not corner
    // Only check L, BL, B, BR, R
    else if (row == 0)
    {
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int bottomLeftIndex = CalculateIndex(row + 1, column - 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);
        unsigned int bottomRightIndex = CalculateIndex(row + 1, column + 1);
        unsigned int rightIndex = CalculateIndex(row, column + 1);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == bottomLeftIndex) ||
                (randomMineLocation == bottomIndex) ||
                (randomMineLocation == bottomRightIndex) ||
                (randomMineLocation == rightIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Bottom but not corner
    // Only check L, TL, T, TR, R
    else if (row == MaxRow - 1)
    {
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int topLeftIndex = CalculateIndex(row - 1, column - 1);
        unsigned int topIndex = CalculateIndex(row - 1, column);
        unsigned int topRightIndex = CalculateIndex(row - 1, column + 1);
        unsigned int rightIndex = CalculateIndex(row, column + 1);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == topLeftIndex) ||
                (randomMineLocation == topIndex) ||
                (randomMineLocation == topRightIndex) ||
                (randomMineLocation == rightIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }

    // Not in any border
    // Every neighbor is valid
    else
    {
        unsigned int leftIndex = CalculateIndex(row, column - 1);
        unsigned int topLeftIndex = CalculateIndex(row - 1, column - 1);
        unsigned int topIndex = CalculateIndex(row - 1, column);
        unsigned int topRightIndex = CalculateIndex(row - 1, column + 1);
        unsigned int rightIndex = CalculateIndex(row, column + 1);
        unsigned int bottomRightIndex = CalculateIndex(row + 1, column + 1);
        unsigned int bottomIndex = CalculateIndex(row + 1, column);
        unsigned int bottomLeftIndex = CalculateIndex(row + 1, column - 1);

        for (unsigned int i = 0; i < MineCount; i++)
        {
            unsigned int randomMineLocation = QRandomGenerator::global()->generate() % size;

            if ((randomMineLocation == index) ||
                (randomMineLocation == leftIndex) ||
                (randomMineLocation == topLeftIndex) ||
                (randomMineLocation == topIndex) ||
                (randomMineLocation == topRightIndex) ||
                (randomMineLocation == rightIndex) ||
                (randomMineLocation == bottomRightIndex) ||
                (randomMineLocation == bottomIndex) ||
                (randomMineLocation == bottomLeftIndex))
            {
                i = i - 1;
            }
            else if (MineField[randomMineLocation].MineStatus == MineStatus_Exist)
            {
                i = i - 1;
            }
            else
            {
                MineField[randomMineLocation].MineStatus = MineStatus_Exist;
            }
        }
    }
};

void MineSweeperCls::OpenCell(unsigned int row, unsigned int column, bool userClickedCell, bool openedClicked)
{
    unsigned int index = CalculateIndex(row, column);

    if (MineField[index].TileStatus == TileStatus_Unopened)
    {
        if (MineField[index].MineStatus == MineStatus_Exist)
        {
            // Only open mined cell if user is clicked on it
            if (userClickedCell == true || openedClicked == true)
            {
                MineField[index].TileStatus = TileStatus_Opened;
            }
        }
        else if (MineField[index].MineStatus == MineStatus_NotExist)
        {
            MineField[index].TileStatus = TileStatus_Opened;

            unsigned int adjacentMineCount = FindAdjacentMineCount(row, column);

            // All adjacent cells do not contain mine. Recursively open them as well
            if (adjacentMineCount == 0)
            {
                if ((row > 0) && (column > 0))
                {
                    OpenCell(row - 1, column - 1, false, false);
                }
                if (row > 0)
                {
                    OpenCell(row - 1, column, false, false);
                }
                if ((row > 0) && (column < MaxColumn - 1))
                {
                    OpenCell(row - 1, column + 1, false, false);
                }
                if (column > 0)
                {
                    OpenCell(row, column - 1, false, false);
                }
                if (column < MaxColumn - 1)
                {
                    OpenCell(row, column + 1, false, false);
                }
                if ((row < MaxRow - 1) && (column > 0))
                {
                    OpenCell(row + 1, column - 1, false, false);
                }
                if (row < MaxRow - 1)
                {
                    OpenCell(row + 1, column, false, false);
                }
                if ((row < MaxRow - 1) && (column < MaxColumn - 1))
                {
                    OpenCell(row + 1, column + 1, false, false);
                }
            }
        }
    }
    else if ((MineField[index].TileStatus == TileStatus_Opened) && (userClickedCell == true))
    {
        unsigned int adjacentMineCount = FindAdjacentMineCount(row, column);
        unsigned int adjacentFlagCount = FindAdjacentFlagCount(row, column);

        if ((adjacentMineCount == adjacentFlagCount) && (adjacentMineCount > 0))
        {
            if ((row > 0) && (column > 0))
            {
                OpenCell(row - 1, column - 1, false, true);
            }
            if (row > 0)
            {
                OpenCell(row - 1, column, false, true);
            }
            if ((row > 0) && (column < MaxColumn - 1))
            {
                OpenCell(row - 1, column + 1, false, true);
            }
            if (column > 0)
            {
                OpenCell(row, column - 1, false, true);
            }
            if (column < MaxColumn - 1)
            {
                OpenCell(row, column + 1, false, true);
            }
            if ((row < MaxRow - 1) && (column > 0))
            {
                OpenCell(row + 1, column - 1, false, true);
            }
            if (row < MaxRow - 1)
            {
                OpenCell(row + 1, column, false, true);
            }
            if ((row < MaxRow - 1) && (column < MaxColumn - 1))
            {
                OpenCell(row + 1, column + 1, false, true);
            }
        }
    }
};

GameStatusEnum MineSweeperCls::CheckGameStatus()
{
    GameStatusEnum result = GameStatus_InProgress;

    unsigned int size = MaxColumn * MaxRow;
    unsigned int counter = 0;

    for (unsigned int i = 0; i < size; i++)
    {
        if ((MineField[i].TileStatus == TileStatus_Opened) &&
            (MineField[i].MineStatus == MineStatus_Exist))
        {
            result = GameStatus_Lose;
            break;
        }

        if (((MineField[i].TileStatus == TileStatus_Opened) &&
            (MineField[i].MineStatus == MineStatus_NotExist)) ||
            ((MineField[i].MineStatus == MineStatus_Exist) &&
                ((MineField[i].TileStatus == TileStatus_Unopened) ||
                    (MineField[i].TileStatus == TileStatus_Flagged))))
        {
            counter = counter + 1;
        }
    }

    if (counter == size)
    {
        result = GameStatus_Win;
    }

    return result;
};
