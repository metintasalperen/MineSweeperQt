#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    row = 0;
    col = 0;
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
    {
        emit leftClicked();
    }
    else if (event->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
}
