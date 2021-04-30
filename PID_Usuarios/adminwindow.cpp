#include "adminwindow.h"
#include "ui_adminwindow.h"

adminwindow::adminwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);
    actualizar_ventana();
}

adminwindow::~adminwindow()
{
    delete ui;
}
//copia la lista de usurios para ser usado dentro de la ventana de administrador

void adminwindow::cargar_usuarios(QList<class usuarios*> s){
    users=s;

}
void adminwindow::iniciar_administrador(QList<class usuarios*> s,usuarios admin){
    cargar_usuarios(s);
    cargar_datos_admin(admin);
    actualizar_ventana();

}
void adminwindow::actualizar_ventana(){
    QPixmap img(administrador.get_iconpath());
    ui->name_label_3->setText(administrador.get_name());
    ui->username_label_3->setText(administrador.get_username());
    ui->icon_label_3->setPixmap(img);
    actualizar_lista();
}
void adminwindow::cargar_datos_admin(usuarios admin){

    administrador.set_name(admin.get_name());
    administrador.set_username(admin.get_username());
    administrador.set_iconpath(admin.get_iconpath());

}

void adminwindow::on_boton_atras_clicked()
{
    this->parentWidget()->show();
    this->close();
}
void adminwindow::actualizar_lista(){
    int i=0;
    for (i=0;i<users.length();i++) {
        ui->listWidget->addItem(users.at(i)->get_name());

    }
}

void adminwindow::on_boton_config_clicked()
{
    windowConfig = new Usuarioconfig(this, users);
    windowConfig->exec();
    this->parentWidget()->show();
    delete windowConfig;
}
