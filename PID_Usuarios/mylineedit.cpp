#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent):
    QLineEdit(parent)
{

}

void MyLineEdit::mousePressEvent(QMouseEvent *)
{
    emit MousePressed();
}
