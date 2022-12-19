#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

    qint32 row;
    qint32 col;

signals:
    void leftClicked();
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif

