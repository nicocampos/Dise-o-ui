#ifndef USUARIO_H
#define USUARIO_H

#include "xmlhandler.h"
#include "usuarios.h"
#include "photoedit.h"
#include "camera.h"
#include <QDialog>
#include <QFile>
#include <QList>
#include <QLabel>

#define VER_USUARIOS    6

namespace Ui{
class Usuarioconfig;
}

class Usuarioconfig : public QDialog
{
    Q_OBJECT

public:
    explicit Usuarioconfig(QWidget *parent = 0);
    Usuarioconfig(QWidget *parent, QList<class usuarios *> list);
    Usuarioconfig(QWidget *parent, usuarios user);
    ~Usuarioconfig();

    inline bool checkUpdate(){return hayCambios; }


private slots:
    void on_PB_USR_ADD_clicked();

    void on_PB_Cancelar_clicked();

    void on_lineEdit_Nombre_editingFinished();

    void on_lineEdit_Apellido_editingFinished();

    void on_lineEdit_Username_editingFinished();

//    void on_lineEdit_Foto_editingFinished();

    void on_lineEdit_Username_textEdited(const QString &arg1);

    void nombreClicked(void);

    void apellidoClicked(void);

    void userNameClicked(void);

//    void fotoClicked(void);

    void on_PB_Aceptar_clicked();

    void on_PB_SelecFoto_clicked();

    void on_PB_SacarFoto_clicked();

    void on_PB_Siguiente_clicked();

    void on_PB_Anterior_clicked();

    void on_PB_USR1_clicked();

    void on_PB_USR2_clicked();

    void on_PB_USR3_clicked();

    void on_PB_USR4_clicked();

    void on_PB_USR5_clicked();

    void on_PB_USR6_clicked();

    void on_PB_Eliminar_clicked();

private:
    Ui::Usuarioconfig *ui;

//    QPushButton *PB_usuarios[6];
    QList<QPushButton *> buttons;
    QList<QLabel *> labels;
    QList<class usuarios*> usuarios;
    QList<class usuarios*> lista_usuarios;
    int posScroll;
    int userSelect;
    bool admin;
    QString *pathFoto;
    QString userName;
    XmlHandler *m_datosXml;
    bool hayCambios;

    Photoedit *editPhoto;
    Camera *camWindow;

    void hideItems(void);
    void setEnabled_Add(bool);
    void validateUserName(const QString &);
    void CargarUsuarios(void);
    void MostrarUsuario(void);
    void LimpiarUsuariosPrevios(void);
    void loadUser(void);
    void saveUser(void);
};

#endif // USUARIO_H
