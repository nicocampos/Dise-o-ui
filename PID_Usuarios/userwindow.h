#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "usuarios.h"
#include "usuarioconfig.h"
namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);

    ~UserWindow();
    void iniciar_usuario(usuarios u);
    void actualizar_ventana();
private slots:
    void on_pushButton_clicked();

    void on_boton_atras_clicked();

    void on_boton_perfil_clicked();

private:
    Ui::UserWindow *ui;
    usuarios nu;
    Usuarioconfig *windowPerfil;
};

#endif // USERWINDOW_H
