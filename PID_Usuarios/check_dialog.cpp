#include "check_dialog.h"
#include "ui_check_dialog.h"

check_Dialog::check_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_Dialog)
{
    ui->setupUi(this);
    ui->password_label->setEchoMode(QLineEdit::Password);
}

check_Dialog::~check_Dialog()
{
    delete ui;
}
void check_Dialog::cargar_datos(QString user, QString pw){
    ui->user_label->setPlainText(user);
    set_password(pw);
}
void check_Dialog::on_boton_ok_clicked()
{
    if(verificar_password()){
        this->accept();
    }else{
        this->reject();
    }
    this->done(this->result());
}
void check_Dialog::set_password(QString pw){
    password=pw;

}
QString check_Dialog::get_password(){
    return  password;
}
int check_Dialog::verificar_password(){
    QString s=ui->password_label->text();
    return !(QString::compare(s,get_password()));

}
