#ifndef USERCARD_H
#define USERCARD_H

#include <QWidget>
#include <QHoverEvent>
#include <QEvent>
#include <QPoint>
#define PORCENT 10
namespace Ui {
class usercard;
}

class usercard : public QWidget
{
    Q_OBJECT

public:
    explicit usercard(QWidget *parent = nullptr);
    ~usercard();
    void set_min_size(int height,int width);
    void set_username(QString username);
    void set_name(QString name);
    void set_icon(QString iconpath);
    void expand(float porcent);
    void decrease(float porcent);
    void remark(bool a);
    void select(bool x);
    QPoint posicion();
private slots:
    void on_iconboton_clicked();
signals:
    void clicked();

private:
    Ui::usercard *ui;
protected:

    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;




};

#endif // USERCARD_H
