#ifndef CHECK_DIALOG_H
#define CHECK_DIALOG_H

#include <QDialog>

namespace Ui {
class check_Dialog;
}

class check_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit check_Dialog(QWidget *parent = nullptr);
    ~check_Dialog();
    int verificar_password();
    void set_user();
    void set_password(QString pw);
    QString get_password();
    void cargar_datos(QString user,QString pw);


private slots:
    void on_boton_ok_clicked();

private:
    Ui::check_Dialog *ui;
    QString user;
    QString password;
};

#endif // CHECK_DIALOG_H
