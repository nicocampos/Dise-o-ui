#include "usercard.h"
#include "ui_usercard.h"

usercard::usercard(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::usercard)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_Hover, true);
    this->setCursor(Qt::BlankCursor);
}

usercard::~usercard()
{
    delete ui;
}
void usercard::set_min_size(int height, int width)
{

    this->setMinimumSize(width, height);
}
void usercard::set_name(QString name)
{

    ui->name_label->setText(name);
}

void usercard::set_username(QString username)
{

    ui->username_label->setText(username);
}
void usercard::set_icon(QString iconpath)
{

    QPixmap icon(iconpath);
    QIcon user_icon(icon);
    ui->iconboton->setIcon(user_icon);
    ui->iconboton->setIconSize(QSize(600,400));

}

void usercard::expand(float porcent)
{
    set_min_size(this->height(), this->width());
    porcent = ((porcent + 100) / 100);
    this->resize(((this->width()) * porcent), ((this->height()) * porcent));
}
void usercard::decrease(float porcent)
{

    porcent = ((100 - porcent) / 100);
    this->resize(((this->width()) * porcent), ((this->height()) * porcent));
}

void usercard::remark(bool a)
{

    if (a)
    {
        ui->card->setStyleSheet(
            "background-color: rgb(255, 255, 255);"
            "border-width: 12px;"
            "border-style:solid;"
            "border-right-color: qlineargradient(spread:repeat, x1:0, y1:0, x2:1, y2:0, stop:0.144231 rgba(91, 42, 134, 255), stop:0.427885 rgba(131, 94, 164, 255), stop:0.740385 rgba(207, 193, 220, 255), stop:0.860577 rgba(255, 255, 255, 255));"
            "border-top-color: qlineargradient(spread:repeat, x1:0, y1:1, x2:0, y2:0, stop:0.144231 rgba(91, 42, 134, 255), stop:0.427885 rgba(131, 94, 164, 255), stop:0.740385 rgba(207, 193, 220, 255), stop:0.860577 rgba(255, 255, 255, 255));"
            "border-bottom-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:1, y2:1, stop:0.144231 rgba(91, 42, 134, 255), stop:0.427885 rgba(131, 94, 164, 255), stop:0.740385 rgba(207, 193, 220, 255), stop:0.860577 rgba(255, 255, 255, 255));"
            "border-left-color: qlineargradient(spread:repeat, x1:1, y1:0, x2:0, y2:0, stop:0.144231 rgba(91, 42, 134, 255), stop:0.427885 rgba(131, 94, 164, 255), stop:0.740385 rgba(207, 193, 220, 255), stop:0.860577 rgba(255, 255, 255, 255));  ");
    }
    else
    {
        ui->card->setStyleSheet(
            "background-color: rgb(255, 255, 255);"
            "border-width: 10px;"
            "border-style:solid;"
            "border-top-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(95, 95, 95, 255), stop:0.990385 rgba(255, 255, 255, 255), stop:1 rgba(171, 171, 171, 255));"
            "border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(95, 95, 95, 255), stop:0.990385 rgba(255, 255, 255, 255), stop:1 rgba(171, 171, 171, 255));"
            "border-bottom-color: qlineargradient(spread:pad, x1:1, y1:0, x2:1, y2:1, stop:0 rgba(95, 95, 95, 255), stop:0.990385 rgba(255, 255, 255, 255), stop:1 rgba(171, 171, 171, 255));"
            "border-left-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:1, stop:0 rgba(95, 95, 95, 255), stop:0.990385 rgba(255, 255, 255, 255), stop:1 rgba(171, 171, 171, 255));");
    }
}

void usercard::select(bool x)
{
    if(x){
        this->remark(true);
        this->expand(PORCENT);
    }else{
        this->remark(false);
        this->decrease(PORCENT);
    }

}
void usercard::mouseMoveEvent(QMouseEvent *event)
{

    switch (event->type())
    {

    case QEvent::HoverEnter:
        enterEvent(event);
        break;
    case QEvent::HoverLeave:
        leaveEvent(event);
        break;
    default:
        break;
    }
}
void usercard::leaveEvent(QEvent *)
{
    decrease(PORCENT);
    remark(false);
}
void usercard::enterEvent(QEvent *)
{
    expand(PORCENT);
    remark(true);
}
void usercard::on_iconboton_clicked()
{
        emit clicked();
}
QPoint usercard::posicion(){
    return ui->iconboton->pos();

}
