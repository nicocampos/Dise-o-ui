#include "usuarioconfig.h"
#include "ui_usuarioconfig.h"
#include <QIcon>
#include <QDir>
#include <QFileDialog>
#include <QRegExpValidator>
#include <QDebug>

#define VALIUSERNAME    "/-[a-z0-9_-]{3,16}$/"

#define ADMIN           "admin"
#define DIRUSUARIOS     QDir::currentPath()+"/sci/usuarios/"
//#define CANT_USUARIOS   listaUsuarios->length()-2                   // el 2 es para no tener en cuenta el . y ..
#define CANT_USUARIOS   usuarios.length()
#define ANCHO           100
#define ALTO            120
#define SIZEDEFAULT     ANCHO,ALTO

#define USR1            0
#define USR2            1
#define USR3            2
#define USR4            3
#define USR5            4
#define USR6            5


Usuarioconfig::Usuarioconfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usuarioconfig)
{
    ui->setupUi(this);
    m_datosXml = nullptr;
    pathFoto = nullptr;
    posScroll = 0;
    editPhoto = nullptr;
    camWindow = nullptr;
    admin = true;
    hayCambios = false;

    //*****************************************************************************
    //         Connect asociados al evento del click sobre los Line Edit
    //*****************************************************************************
    connect(ui->lineEdit_Nombre,SIGNAL(MousePressed()),this,SLOT(nombreClicked()));
    connect(ui->lineEdit_Apellido,SIGNAL(MousePressed()),this,SLOT(apellidoClicked()));
    connect(ui->lineEdit_Username,SIGNAL(MousePressed()),this,SLOT(userNameClicked()));
//    connect(ui->lineEdit_Foto,SIGNAL(MousePressed()),this,SLOT(fotoClicked()));// YA NO SE USA
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los pushbutton asociados a los usuarios en una lista
    //*****************************************************************************
//    PB_usuarios[0] = ui->PB_USR1;
//    PB_usuarios[1] = ui->PB_USR2;
//    PB_usuarios[2] = ui->PB_USR3;
//    PB_usuarios[3] = ui->PB_USR4;
//    PB_usuarios[4] = ui->PB_USR5;
//    PB_usuarios[5] = ui->PB_USR6;
    //*****************************************************************************

    //*****************************************************************************
    //         Validadores para los line edit
    //*****************************************************************************
//    QRegExp userName("[0-9a-z-_ñ]+");
//    QRegExpValidator *valiUserName = new QRegExpValidator(userName, ui->lineEdit_Username);
//    ui->lineEdit_Username->setValidator(valiUserName);
    //*****************************************************************************

//    CargarUsuarios();
    MostrarUsuario();
}

Usuarioconfig::Usuarioconfig(QWidget *parent, QList<class usuarios *> list) :
QDialog(parent),
ui(new Ui::Usuarioconfig)
{
    ui->setupUi(this);
    m_datosXml = nullptr;
    pathFoto = nullptr;
    posScroll = 0;
    userSelect = 0;
    editPhoto = nullptr;
    camWindow = nullptr;
    admin = true;
    hayCambios = false;

    //*****************************************************************************
    //         Connect asociados al evento del click sobre los Line Edit
    //*****************************************************************************
    connect(ui->lineEdit_Nombre,SIGNAL(MousePressed()),this,SLOT(nombreClicked()));
    connect(ui->lineEdit_Apellido,SIGNAL(MousePressed()),this,SLOT(apellidoClicked()));
    connect(ui->lineEdit_Username,SIGNAL(MousePressed()),this,SLOT(userNameClicked()));
//    connect(ui->lineEdit_Foto,SIGNAL(MousePressed()),this,SLOT(fotoClicked()));// YA NO SE USA
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los pushbutton asociados a los usuarios en una lista
    //*****************************************************************************
//    PB_usuarios[0] = ui->PB_USR1;
//    PB_usuarios[1] = ui->PB_USR2;
//    PB_usuarios[2] = ui->PB_USR3;
//    PB_usuarios[3] = ui->PB_USR4;
//    PB_usuarios[4] = ui->PB_USR5;
//    PB_usuarios[5] = ui->PB_USR6;
    buttons.append(ui->PB_USR1);
    buttons.append(ui->PB_USR2);
    buttons.append(ui->PB_USR3);
    buttons.append(ui->PB_USR4);
    buttons.append(ui->PB_USR5);
    buttons.append(ui->PB_USR6);
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los labels asociados a los usuarios en una lista
    //*****************************************************************************
    labels.append(ui->label_usr1);
    labels.append(ui->label_usr2);
    labels.append(ui->label_usr3);
    labels.append(ui->label_usr4);
    labels.append(ui->label_usr5);
    labels.append(ui->label_usr6);
    //*****************************************************************************

    //*****************************************************************************
    //         Validadores para los line edit
    //*****************************************************************************
//    QRegExp userName("[0-9a-z-_ñ]+");
//    QRegExpValidator *valiUserName = new QRegExpValidator(userName, ui->lineEdit_Username);
//    ui->lineEdit_Username->setValidator(valiUserName);
    //*****************************************************************************

    usuarios = list;
    MostrarUsuario();
}

Usuarioconfig::Usuarioconfig(QWidget *parent, class usuarios usuario) :
    QDialog(parent),
    ui(new Ui::Usuarioconfig)
{
    ui->setupUi(this);
    m_datosXml = nullptr;
    pathFoto = nullptr;
    posScroll = 0;
    userSelect = 0;
    editPhoto = nullptr;
    camWindow = nullptr;
    admin = false;          // flag para indicar si es admin o usuario
    hayCambios = false;

    //*****************************************************************************
    //          Desactivo pushbutton que no uso en usuarios
    //*****************************************************************************
    ui->PB_USR_ADD->setEnabled(false);
    ui->PB_Anterior->setEnabled(false);
    ui->PB_Siguiente->setEnabled(false);

    //*****************************************************************************
    //          Oculto botones y labels que no uso
    //*****************************************************************************
    hideItems();

    //*****************************************************************************
    //         Connect asociados al evento del click sobre los Line Edit
    //*****************************************************************************
    connect(ui->lineEdit_Nombre,SIGNAL(MousePressed()),this,SLOT(nombreClicked()));
    connect(ui->lineEdit_Apellido,SIGNAL(MousePressed()),this,SLOT(apellidoClicked()));
    connect(ui->lineEdit_Username,SIGNAL(MousePressed()),this,SLOT(userNameClicked()));
//    connect(ui->lineEdit_Foto,SIGNAL(MousePressed()),this,SLOT(fotoClicked()));// YA NO SE USA
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los pushbutton asociados a los usuarios en una lista
    //*****************************************************************************
    buttons.append(ui->PB_USR1);
    buttons.append(ui->PB_USR2);
    buttons.append(ui->PB_USR3);
    buttons.append(ui->PB_USR4);
    buttons.append(ui->PB_USR5);
    buttons.append(ui->PB_USR6);
    //*****************************************************************************

    //*****************************************************************************
    //         Guardo los labels asociados a los usuarios en una lista
    //*****************************************************************************
    labels.append(ui->label_usr1);
    labels.append(ui->label_usr2);
    labels.append(ui->label_usr3);
    labels.append(ui->label_usr4);
    labels.append(ui->label_usr5);
    labels.append(ui->label_usr6);
    //*****************************************************************************

    usuarios.append(&usuario);
    MostrarUsuario();
    loadUser();
}

Usuarioconfig::~Usuarioconfig()
{
    delete ui;
}


void Usuarioconfig::CargarUsuarios(void)            //------> NO SE USA
{
//    QFile filename;
//    QDir dirUsuarios(DIRUSUARIOS);
//    //dirUsuarios.setFilter(QDir::NoDotAndDotDot);
//    listaUsuarios = new QStringList(dirUsuarios.entryList());

//    Miusuario aux;
//    m_datosXml = new XmlHandler();
//    for(int i = 2; i < listaUsuarios->length(); i++){
//        filename.setFileName(DIRUSUARIOS+listaUsuarios->at(i));
//        m_datosXml->load(filename);
//        aux.setNombre(m_datosXml->getContenidoGeneral(NOMBRE));
//        aux.setApellido(m_datosXml->getContenidoGeneral(APELLIDO));
//        aux.setNombreUsuario(m_datosXml->getContenidoGeneral(NOMBRE_USUARIO));
//        aux.setFoto(m_datosXml->getContenidoGeneral(IMAGEN));

//        usuarios.append(aux);
//    }
}

void Usuarioconfig::MostrarUsuario(void)
{
    if(posScroll != 0)
        LimpiarUsuariosPrevios();

    lista_usuarios = usuarios.mid(posScroll, VER_USUARIOS);

    QSize sizeDefault(SIZEDEFAULT);

    // VER_USUARIOS es por la cantidad de usuarios que puedo mostrar
    for(int i = 0; i < lista_usuarios.length(); i++){
        QIcon foto(lista_usuarios.value(i)->get_iconpath());
        buttons.at(i)->setIconSize(sizeDefault);
        buttons.at(i)->setIcon(foto);

        labels.at(i)->setText(lista_usuarios.value(i)->get_username());
        buttons.at(i)->setEnabled(true);
    }
}

void Usuarioconfig::LimpiarUsuariosPrevios()
{
    QSize sizeDefault(SIZEDEFAULT);
    for(int i = posScroll-VER_USUARIOS; i < posScroll; i++){
        QIcon foto;
        buttons.at(i)->setIconSize(sizeDefault);
        buttons.at(i)->setIcon(foto);
        labels.at(i)->setText("sin nombre");
        buttons.at(i)->setEnabled(false);
    }
}

void Usuarioconfig::loadUser(void)
{
    ui->PB_Aceptar->setText("Modificar");

    if(lista_usuarios.at(userSelect)->get_username() != ADMIN && admin){
        ui->PB_Eliminar->setEnabled(true);
    }
    else{
        ui->PB_Eliminar->setEnabled(false);
    }
    ui->lineEdit_Nombre->setText(lista_usuarios.at(userSelect)->get_name());
    ui->lineEdit_Apellido->setText(lista_usuarios.at(userSelect)->get_lastname());
    ui->lineEdit_Username->setText(lista_usuarios.at(userSelect)->get_username());
    ui->PB_VistaPrevia->setIcon(QIcon(lista_usuarios.at(userSelect)->get_iconpath()));
    pathFoto = new QString(DIRUSUARIOS +lista_usuarios.at(userSelect)->get_username() +".jpg");

    setEnabled_Add(true);
}

void Usuarioconfig::saveUser()
{
    m_datosXml = new XmlHandler(ui->lineEdit_Username->text(), NUEVO_XML_USUARIO);
    // Estos métodos cargan los datos a la estructura XML
    m_datosXml->setContenidoGeneral(NOMBRE, ui->lineEdit_Nombre->text());
    m_datosXml->setContenidoGeneral(APELLIDO, ui->lineEdit_Apellido->text());
    m_datosXml->setContenidoGeneral(NOMBRE_USUARIO, ui->lineEdit_Username->text());
    m_datosXml->setContenidoGeneral(IMAGEN, *pathFoto);
    m_datosXml->setContenidoGeneral(CARPETA, DIRUSUARIOS);
}

/**
 * \brief void Usuario::setEnabled_Add(bool opcion)
 * \param opcion Si es verdadero, habilita los lineEdit y PushBottom,
 *              caso contrario los deshabilita
 * \return Void
 */
void Usuarioconfig::setEnabled_Add(bool opcion)
{
    ui->PB_Aceptar->setEnabled(opcion);
    ui->PB_Cancelar->setEnabled(opcion);
    ui->PB_SelecFoto->setEnabled(opcion);
    ui->PB_SacarFoto->setEnabled(opcion);

    ui->lineEdit_Nombre->setEnabled(opcion);
    ui->lineEdit_Apellido->setEnabled(opcion);
    ui->lineEdit_Username->setEnabled(opcion);
//    ui->lineEdit_Foto->setEnabled(opcion);
}

// Valido que el nombre de usuario no tenga
// caracteres extraños
void Usuarioconfig::validateUserName(const QString &arg1)
{
//    QString text = arg1;
//    QString Vali_UserName(VALIUSERNAME);
//    for(int i = 0; i < text.size(); ++i)
//        foreach(const QChar &x, Vali_UserName)
//            if(text.at(i) == x)
//                text.remove(x);
//    ui->lineEdit_Username->setText(text);
}



void Usuarioconfig::on_PB_USR_ADD_clicked()
{
    // Habilito los campos a rellenar y buttons
    setEnabled_Add(true);
}

void Usuarioconfig::on_PB_Aceptar_clicked()
{
    hayCambios = true;
    if(ui->PB_Aceptar->text() == "Aceptar"){
        saveUser();

        if (m_datosXml->save() == true){
            // Deshabilito los campos a rellenar y buttons
            setEnabled_Add(false);

            // Seteo los nombres por defecto de los campos
            ui->lineEdit_Nombre->setText("Nombre");
            ui->lineEdit_Apellido->setText("Apellido");
            ui->lineEdit_Username->setText("NombreDeUsuario");

            // Borro la vista previa
            QIcon vista_previa;
            ui->PB_VistaPrevia->setIcon(vista_previa);  // Seteo un QIcon vacio

        }
    }
    else{
        // Borro el archivo previo
        QFile fileUser;
        fileUser.remove(DIRUSUARIOS+ lista_usuarios.at(userSelect)->get_username() + ".sci");

        // Guardo las modificaciones
        saveUser();

        if (m_datosXml->save() == true){
            // Deshabilito los campos a rellenar y buttons
            setEnabled_Add(false);

            // Seteo los nombres por defecto de los campos
            ui->lineEdit_Nombre->setText("Nombre");
            ui->lineEdit_Apellido->setText("Apellido");
            ui->lineEdit_Username->setText("NombreDeUsuario");

            // Borro la vista previa
            QIcon vista_previa;
            ui->PB_VistaPrevia->setIcon(vista_previa);  // Seteo un QIcon vacio

        }
    }
}

void Usuarioconfig::on_PB_Cancelar_clicked()
{
    // Vuelvo al color de fondo de la ventana
    ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: window;}");

    // Deshabilito los campos a rellenar y buttons
    setEnabled_Add(false);

    // Seteo los nombres por defecto de los campos
    ui->lineEdit_Nombre->setText("Nombre");
    ui->lineEdit_Apellido->setText("Apellido");
    ui->lineEdit_Username->setText("NombreDeUsuario");
//    ui->lineEdit_Foto->setText("Foto:");

    // Borro la vista previa
    QIcon vista_previa;
    ui->PB_VistaPrevia->setIcon(vista_previa);  // Seteo un QIcon vacio

    // Si se creo una imagen, la borro
    QFile fileFoto;

    if(fileFoto.exists(DIRUSUARIOS+userName+".jpg")){
        fileFoto.remove(DIRUSUARIOS+userName+".jpg");
    }
}

// **************************************************
// Auto-completar los campos en caso de estar vacios
// **************************************************
void Usuarioconfig::on_lineEdit_Nombre_editingFinished()
{
    if(ui->lineEdit_Nombre->text() == "")
        ui->lineEdit_Nombre->setText("Nombre");
}

void Usuarioconfig::on_lineEdit_Apellido_editingFinished()
{
    if(ui->lineEdit_Apellido->text() == "")
        ui->lineEdit_Apellido->setText("Apellido");
}

void Usuarioconfig::on_lineEdit_Username_editingFinished()
{
    if(ui->lineEdit_Username->text() == ""){
        ui->lineEdit_Username->setText("NombreDeUsuario");
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: white;}");
    }
}

// YA NO SE USA
//void Usuarioconfig::on_lineEdit_Foto_editingFinished()
//{
//    if(ui->lineEdit_Foto->text() == "")
//        ui->lineEdit_Foto->setText("Foto:");
//}
// **************************************************
// **************************************************

// **************************************************
//  Chequeo de nombre de usuarios
// **************************************************
void Usuarioconfig::on_lineEdit_Username_textEdited(const QString &new_user)
{
    QFile fileUsuario;

//    validateUserName(new_user);

    if(fileUsuario.exists(DIRUSUARIOS+"/"+new_user+".sci")){
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: rgb(255, 88, 32);}");
    }
    else{
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: rgb(157, 255, 65);}");
    }
}
// **************************************************
// **************************************************

// **************************************************
//  Acciones frente a evento del click en Line Edit
// **************************************************
void Usuarioconfig::nombreClicked()
{
    if(ui->lineEdit_Nombre->text() == "")
        ui->lineEdit_Nombre->clear();
}

void Usuarioconfig::apellidoClicked()
{
    if(ui->lineEdit_Apellido->text() == "")
        ui->lineEdit_Apellido->clear();
}

void Usuarioconfig::userNameClicked()
{
    if(ui->lineEdit_Username->text() == ""){
        ui->lineEdit_Username->clear();
        ui->lineEdit_Username->setStyleSheet("QLineEdit {background-color: white;}");
    }

}

// YA NO SE USA
//void Usuarioconfig::fotoClicked()
//{
//    // Abro la ventana para buscar la imagen
//    pathFoto = new QString(QFileDialog::getOpenFileName(this, tr("Elegir Imagen"),
//                                                    QDir::homePath(), tr("Imagenes (*.png *.jpg *.jpeg)")));

//    // Si esta vacio no hago nada
//    if(!pathFoto->isEmpty()){
//        // Seteo la imagen en vista previa
//        QIcon vista_previa(*pathFoto);
//        ui->PB_VistaPrevia->setIcon(vista_previa);
//        // Cargo el nombre de la imagen en el line edit
//        ui->lineEdit_Foto->clear();
//        ui->lineEdit_Foto->setText(pathFoto->section('/',pathFoto->count('/'),pathFoto->count('/')));
//    }

//}
// **************************************************
// **************************************************





void Usuarioconfig::on_PB_SelecFoto_clicked()
{
    // Abro la ventana para buscar la imagen
    pathFoto = new QString(QFileDialog::getOpenFileName(this, tr("Elegir Imagen"),
                                                    QDir::homePath(), tr("Imagenes (*.png *.jpg *.jpeg)")));

    // Si esta vacio no hago nada
    if(!pathFoto->isEmpty()){
        editPhoto = new Photoedit(this,*pathFoto,ui->lineEdit_Username->text()+".jpg");
        if(editPhoto->exec() == QDialog::Accepted){
            *pathFoto = DIRUSUARIOS+ui->lineEdit_Username->text()+".jpg";
            userName = ui->lineEdit_Username->text();
            QIcon *img_previa = new QIcon(*pathFoto);
            ui->PB_VistaPrevia->setIcon(*img_previa);
        }
    }
}

void Usuarioconfig::on_PB_SacarFoto_clicked()
{
    camWindow = new Camera(this);
    camWindow->setRutaImagen(DIRUSUARIOS);
    camWindow->setNombreImagen("image1.jpg");
    camWindow->exec();

}

// Boton de avanzar para ver mas usuarios
void Usuarioconfig::on_PB_Siguiente_clicked()
{
    if(2*posScroll < CANT_USUARIOS){
        posScroll += VER_USUARIOS;
        MostrarUsuario();
    }
}

void Usuarioconfig::on_PB_Anterior_clicked()
{
    if(posScroll > VER_USUARIOS-1){
        posScroll -= VER_USUARIOS;
        MostrarUsuario();
    }
}

// Botones de los usuarios (del 1 al 6)
void Usuarioconfig::on_PB_USR1_clicked()
{
    userSelect = USR1;
    loadUser();

}

void Usuarioconfig::on_PB_USR2_clicked()
{
    userSelect = USR2;
    loadUser();
}

void Usuarioconfig::on_PB_USR3_clicked()
{
    userSelect = USR3;
    loadUser();
}

void Usuarioconfig::on_PB_USR4_clicked()
{
    userSelect = USR4;
    loadUser();
}

void Usuarioconfig::on_PB_USR5_clicked()
{
    userSelect = USR5;
    loadUser();
}

void Usuarioconfig::on_PB_USR6_clicked()
{
    userSelect = USR6;
    loadUser();
}

// boton de eliminar usuario
void Usuarioconfig::on_PB_Eliminar_clicked()
{
    QFile fileUser;
    fileUser.remove(DIRUSUARIOS+ lista_usuarios.at(userSelect)->get_username() + ".sci");
}

void Usuarioconfig::hideItems()
{
    ui->PB_USR_ADD->hide();
    ui->PB_Anterior->hide();
    ui->PB_Siguiente->hide();
    ui->PB_USR2->hide();
    ui->PB_USR3->hide();
    ui->PB_USR4->hide();
    ui->PB_USR5->hide();
    ui->PB_USR6->hide();
    ui->label_usr2->hide();
    ui->label_usr3->hide();
    ui->label_usr4->hide();
    ui->label_usr5->hide();
    ui->label_usr6->hide();
}
