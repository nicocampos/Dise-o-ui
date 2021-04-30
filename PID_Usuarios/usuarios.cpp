#include "usuarios.h"

#define DIRUSUARIOS     QDir::currentPath()+"/sci/usuarios/"

usuarios::usuarios()
{
}
usuarios::usuarios(const usuarios &other):name(other.name),lastname(other.lastname),username(other.username),iconpath(other.iconpath){

}

usuarios &usuarios::operator=(const usuarios &other)
{
    this->set_name(other.name);
    this->set_lastname(other.lastname);
    this->set_iconpath(other.iconpath);
    this->set_password(other.password);
    this->set_username(other.username);
    this->set_permisos(other.permisos);

    return (*this);
}
usuarios::~usuarios()
{
    delete m_datosXml;
}
void usuarios::set_permisos(int i){
    permisos=i;
}
void usuarios::set_name(QString nombre)
{
    name = nombre;
}
void usuarios::set_lastname(QString apellido)
{
    lastname = apellido;
}
void usuarios::set_username(QString user_name)
{
    username = user_name;
}
void usuarios::set_iconpath(QString path)
{
    iconpath = path;
}
void usuarios::set_password(QString pw){
    password=pw;
}

void usuarios::loadUsers(QString path)
{

}

void usuarios::refreshUsers()
{

}

bool usuarios::saveUsers()
{
    m_datosXml = new XmlHandler(username, NUEVO_XML_USUARIO);
    // Estos métodos cargan los datos a la estructura XML
    m_datosXml->setContenidoGeneral(NOMBRE, name);
    m_datosXml->setContenidoGeneral(APELLIDO, lastname);
    m_datosXml->setContenidoGeneral(NOMBRE_USUARIO, username);
    m_datosXml->setContenidoGeneral(IMAGEN, iconpath);
    m_datosXml->setContenidoGeneral(CARPETA, DIRUSUARIOS);

    return m_datosXml->save();
}
int usuarios::get_permisos(){
    return permisos;
}
QString usuarios::get_name()
{
    return name;
}
QString usuarios::get_lastname()
{
    return lastname;
}
QString usuarios::get_username()
{
    return username;
}
QString usuarios::get_iconpath()
{
    return iconpath;
}
QString usuarios::get_password(){
    return password;
}
