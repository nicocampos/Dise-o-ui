#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    actualizar_ventana();
}

UserWindow::~UserWindow()
{
    delete ui;
}
void UserWindow::iniciar_usuario(usuarios u){
  nu.set_name(u.get_name());
  nu.set_lastname(u.get_lastname());
  nu.set_username(u.get_username());
  nu.set_iconpath(u.get_iconpath());
}
void UserWindow::actualizar_ventana(){
    QPixmap img(nu.get_iconpath());
    ui->name_label->setText(nu.get_name()+" "+nu.get_lastname());
    ui->username_label->setText(nu.get_username());
    ui->icon_label->setPixmap(img);
}
void UserWindow::on_pushButton_clicked()
{
    QPixmap img(nu.get_iconpath());
    ui->name_label->setText(nu.get_name()+" "+nu.get_lastname());
    ui->username_label->setText(nu.get_username());
    ui->icon_label->setPixmap(img);

}

void UserWindow::on_boton_atras_clicked()
{

    this->parentWidget()->show();
    this->close();
}

void UserWindow::on_boton_perfil_clicked()
{
    windowPerfil = new Usuarioconfig(this, nu);
    windowPerfil->exec();
    this->parentWidget()->show();
    delete windowPerfil;
}
