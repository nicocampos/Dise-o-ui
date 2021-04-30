#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "usuarios.h"
#include "usuarioconfig.h"

namespace Ui {
class adminwindow;
}

class adminwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();

    void cargar_usuarios(QList<class usuarios*>  s);
    void iniciar_administrador(QList<class usuarios*> s,usuarios admin);
    void actualizar_lista();
    void actualizar_ventana();
    void cargar_datos_admin(usuarios admin);


private slots:
    void on_boton_atras_clicked();

    void on_boton_config_clicked();

private:
    Ui::adminwindow *ui;
    QList<class usuarios*>  users;
    usuarios administrador;
    Usuarioconfig *windowConfig;

};

#endif // ADMINWINDOW_H
