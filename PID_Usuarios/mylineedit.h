#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *);

signals:
    void MousePressed(void);
};

#endif // MYLINEEDIT_H
