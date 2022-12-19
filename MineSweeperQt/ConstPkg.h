#ifndef CONSTPKG_H
#define CONSTPKG_H

#include <QString>

// UI Texts
const QString APPLY_BUTTON_TEXT = "Apply";
const QString EASY_CHECKBOX_TEXT = "9x9, 10";
const QString MEDIUM_CHECKBOX_TEXT = "16x16, 40";
const QString HARD_CHECKBOX_TEXT = "30x16, 99";

// UI Sizes
const qint32 CELL_SIZE_X = 30;
const qint32 CELL_SIZE_Y = 30;

// Game settings
// Easy
const qint32 EASY_ROW = 9;
const qint32 EASY_COL = 9;
const qint32 EASY_MINE_COUNT = 10;

// Medium
const qint32 MEDIUM_ROW = 16;
const qint32 MEDIUM_COL = 16;
const qint32 MEDIUM_MINE_COUNT = 40;

// Hard
const qint32 HARD_ROW = 16;
const qint32 HARD_COL = 16;
const qint32 HARD_MINE_COUNT = 99;

// Assets
// Faces
const QString FACE_ON_CLICKED = ":/faces/faces/onClicked.png";
const QString FACE_WIN = ":/faces/faces/win.png";
const QString FACE_LOSE = ":/faces/faces/lose.png";
const QString FACE_MAIN = ":/faces/faces/main.png";

// Tiles
const QString TILE_FLAGGED = ":/tiles/tiles/flagged.png";
const QString TILE_UNOPENED = ":/tiles/tiles/unopened.png";
const QString TILE_OPENED_EMPTY = ":/tiles/tiles/openedEmpty.png";
const QString TILE_BOMB = ":/tiles/tiles/bomb.png";
const QString TILE_ONE = ":/tiles/tiles/1.png";
const QString TILE_TWO = ":/tiles/tiles/2.png";
const QString TILE_THREE = ":/tiles/tiles/3.png";
const QString TILE_FOUR = ":/tiles/tiles/4.png";
const QString TILE_FIVE = ":/tiles/tiles/5.png";
const QString TILE_SIX = ":/tiles/tiles/6.png";
const QString TILE_SEVEN = ":/tiles/tiles/7.png";
const QString TILE_EIGHT = ":/tiles/tiles/8.png";

// Counter numbers
const QString COUNTER_ZERO = ":/numbers/numbers/0.png";
const QString COUNTER_ONE = ":/numbers/numbers/1.png";
const QString COUNTER_TWO = ":/numbers/numbers/2.png";
const QString COUNTER_THREE = ":/numbers/numbers/3.png";
const QString COUNTER_FOUR = ":/numbers/numbers/4.png";
const QString COUNTER_FIVE = ":/numbers/numbers/5.png";
const QString COUNTER_SIX = ":/numbers/numbers/6.png";
const QString COUNTER_SEVEN = ":/numbers/numbers/7.png";
const QString COUNTER_EIGHT = ":/numbers/numbers/8.png";
const QString COUNTER_NINE = ":/numbers/numbers/9.png";


#endif // CONSTPKG_H
