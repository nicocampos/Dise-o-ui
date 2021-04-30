#ifndef USUARIOS_H
#define USUARIOS_H

#include <QString>
//#include "usuariosfactory.h"
#include "xmlhandler.h"

//class usuarios :// public usuariosFactory
#define  ADMIN  1
#define  USER 2
#define  GEN  0

class usuarios
{
public:
    usuarios();
    ~usuarios();
    usuarios(const usuarios &other);

    usuarios &operator=(const usuarios &other);
    void set_permisos(int i);
    void set_name(QString nombre="nombre de usuario");
    void set_lastname(QString apellido="apellido");
    void set_username(QString user_name="Usuario");
    void set_iconpath(QString path=":/resources/resources/e.png");
    void set_password(QString pw);

    void loadUsers(QString path);

    void refreshUsers();

    bool saveUsers();

    int get_permisos();
    QString get_name();
    QString get_lastname();
    QString get_username();
    QString get_iconpath();
    QString get_password();
    usuarios *ptr;


private:
    QString name;
    QString lastname;
    QString username;
    QString iconpath;
    QString password;
    int permisos;
    XmlHandler *m_datosXml;



};


#endif // USUARIOS_H
