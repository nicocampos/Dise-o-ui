#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DIRUSUARIOS     QDir::currentPath()+"/sci/usuarios/"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->boton_atras->hide();

    ui->boton_adelante->hide();
    ui->botonbarrido->setText("barrido:OFF");
    m_datosXml = nullptr;

    crear_lista_de_usuarios();
    iniciar_conecciones();




    connect (this, SIGNAL(rightclicked()), this, SLOT(start_barrido())) ;
    connect (this, SIGNAL(leftclicked()), this, SLOT(stop_barrido())) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned int MainWindow::indice = 0;
unsigned int MainWindow::max = 0;
unsigned int MainWindow::boton_barrido = OFF;
int MainWindow::estado=CARD1;
/*static, but non-const data members should be defined outside of the class
 * definition and inside the namespace enclosing the class.
 * The usual practice is to define it in the translation unit (*.cpp) because it is considered to be an implementation detail.
 * Only static and const integral types can be declared and defined at the same time*/

void MainWindow::crear_lista_de_usuarios()
{
    //configura el path y añade los filtros
//    path="C:/Users/Usuario/Desktop/tecnologias/launcher/users";
    path = DIRUSUARIOS;    
    filters << "*.sci";
    QDir dir(path);

    // Si no existe el directorio, lo creo
    if(!dir.exists()){
        dir.mkpath(DIRUSUARIOS);
    }


    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dir.setNameFilters(filters);

    QDirIterator it(path, filters);
    //si la lista "users" esta vacia" añade el elemento administrador
    if(users.empty()){
        class usuarios *ptr = new usuarios();
        ptr->set_name("administrador");
        ptr->set_iconpath(":/resource/resources/e.png");
        ptr->set_username("admin");
        ptr->set_permisos(ADMIN);
        users.append(ptr);
    }
    //mientras exista otro archivo dentro del path
    //carga el nuevo  usuario
    while (it.hasNext())
    {

        users.append(cargar_usuario(it.next()));
    }

    if (users.size() > NRO_ITEMS)
    {
        ui->boton_adelante->show();
    }
    max = users.size();

    Crear_pagina_usuarios(users);
}
class usuarios *MainWindow::cargar_usuario(QString path)
{
    class usuarios *ptr = new usuarios();

    // abre el archivo en modo lectura
    //si se pudo abrir crea un objeto "usuario" con los datos del archivo .sci
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error al Abrir Archivo"),
                             tr("No se pudo abrir el archivo \n%1").arg(path));
    }
    if (m_datosXml != nullptr)
        delete m_datosXml;
    m_datosXml = new XmlHandler();
    if (!m_datosXml->load(file))
    {
        QMessageBox::warning(this, tr("Error al Abrir Archivo"),
                             tr("No se pudo procesar el archivo \n%1").arg(path));
    }
    file.close();

    ptr->set_name(m_datosXml->getContenidoGeneral(NOMBRE));// + " " + m_datosXml->getContenidoGeneral(APELLIDO));
    ptr->set_lastname(m_datosXml->getContenidoGeneral(APELLIDO));
    ptr->set_username(m_datosXml->getContenidoGeneral(NOMBRE_USUARIO));
    ptr->set_iconpath(m_datosXml->getContenidoGeneral(IMAGEN));
    ptr->set_permisos(USER);

    return ptr;
}
void MainWindow::Crear_pagina_usuarios(QList<class usuarios *> list)
{
    //crea una lista de 4 elementos a partir del indice actual
    lista_pagina = list.mid(indice, NRO_ITEMS);
    //si la nueva lista tiene menos de 4 elementos
    //rellena la lista con usuarios genericos
    if (lista_pagina.size() < NRO_ITEMS)
    {
        lista_pagina = rellenar_pagina(lista_pagina);
    }
    //actualiza los widgets con los elementos de la lista
    Mostrar_pagina(lista_pagina);
}
QList<class usuarios *> MainWindow::rellenar_pagina(QList<class usuarios *> list)
{
    class usuarios *ptr = new class usuarios();
    ptr->set_name("nombre gen");
    ptr->set_iconpath(":/resource/resources/e.png");
    ptr->set_username("username gen");
    ptr->set_permisos(GEN);
    while (list.size() < 4)
    {
        list.append(ptr);
    }

    return list;
}
void MainWindow::Mostrar_pagina(QList<class usuarios *> aux)
{
    actualizar_usernames(aux);
    actualizar_names(aux);
    actualizar_icons(aux);
}
void MainWindow::actualizar_icons(QList<class usuarios *> aux)
{

    ui->card1->set_icon(aux[0]->get_iconpath());
    ui->card2->set_icon(aux[1]->get_iconpath());
    ui->card3->set_icon(aux[2]->get_iconpath());
    ui->card4->set_icon(aux[3]->get_iconpath());
}
void MainWindow::actualizar_names(QList<class usuarios *> aux)
{

    ui->card1->set_name(aux[0]->get_name()+" "+aux[0]->get_lastname());
    ui->card2->set_name(aux[1]->get_name()+" "+aux[1]->get_lastname());
    ui->card3->set_name(aux[2]->get_name()+" "+aux[2]->get_lastname());
    ui->card4->set_name(aux[3]->get_name()+" "+aux[3]->get_lastname());
}
void MainWindow::actualizar_usernames(QList<class usuarios *> aux)
{
    ui->card1->set_username(aux[0]->get_username());
    ui->card2->set_username(aux[1]->get_username());
    ui->card3->set_username(aux[2]->get_username());
    ui->card4->set_username(aux[3]->get_username());
}

//----------------------SLOTS-------------------------------------------------------------------
void MainWindow::on_boton_atras_clicked()
{
    indice = indice - NRO_ITEMS;
    ui->boton_adelante->show();
    if (indice < 1)
    {
        ui->boton_atras->hide();
    }

    Crear_pagina_usuarios(users);
}
void MainWindow::on_boton_adelante_clicked()
{
    indice = indice + NRO_ITEMS;
    ui->boton_atras->show();

    if (indice >= unsigned((users.size() - NRO_ITEMS)))
    {
        ui->boton_adelante->hide();
    }

    Crear_pagina_usuarios(users);
}


void MainWindow::iniciar_conecciones(){
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    connect (ui->card1, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    connect (ui->card2, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    connect (ui->card3, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    connect (ui->card4, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
    signalMapper->setMapping(ui->card1,0);
    signalMapper->setMapping(ui->card2,1);
    signalMapper->setMapping(ui->card3,2);
    signalMapper->setMapping(ui->card4,3);
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(abrir_ventana(int))) ;
}
void MainWindow::abrir_ventana(int i){
    if(boton_barrido==ON){
        emit rightclicked();
    }
    switch (lista_pagina.at(i)->get_permisos()) {

    case ADMIN://cambiar por ventana admin

        if(verificar_password(*lista_pagina.at(i))){
            ventana_admin=new adminwindow(this);
            ventana_admin->iniciar_administrador(users,*lista_pagina.at(i));
            ventana_admin->show();
            this->hide();

        }

        break;
    case USER:
        ventana_user= new UserWindow(this);
        ventana_user->iniciar_usuario(*lista_pagina.at(i));
        ventana_user->actualizar_ventana();
        ventana_user->show();
        this->hide();
        break;
    case GEN:
        break;
    default:
        break;
    }


}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton)
    {
        emit rightclicked();
    }
    if (event->button() == Qt::LeftButton)
    {
        if (boton_barrido == ON)
        {
            emit leftclicked();//emitir click izquierdo
        }
    }

}
void MainWindow::start_barrido(){

    if(boton_barrido==OFF){
       boton_barrido=ON;
       ui->botonbarrido->setEnabled(true);
       ui->botonbarrido->setText("barrido:ON");

       resetear_barrido();
       //Crear_pagina_usuarios(users);

       // Nico
       //actualiza los widgets con los elementos de la lista
       Mostrar_pagina(lista_pagina);

       ui->boton_atras->hide();
       if(users.length() >= NRO_ITEMS)
        ui->boton_adelante->show();

       barrido();

    }else{

       boton_barrido=OFF;

       ui->botonbarrido->setEnabled(false);
       ui->botonbarrido->setText("barrido:OFF");
       resetear_barrido();

    }
}

void MainWindow::stop_barrido(){
    boton_barrido=OFF;
}
void MainWindow::barrido(){


    static unsigned int i = 1;
    QCursor *cursor=new QCursor();
    QPoint  pos;
    QPoint q(50,50);


    if(i<=max && boton_barrido==unsigned(ON)){


        switch (estado)
        {
        case CARD1:
            pos = mapToGlobal(ui->card1->pos());
            pos += q;
            cursor->setPos(pos);
            estado = CARD2;
            break;
        case CARD2:
            pos = mapToGlobal(ui->card2->pos());
            pos += q;
            cursor->setPos(pos);
            estado = CARD3;
            break;
        case CARD3:
            pos = mapToGlobal(ui->card3->pos());
            pos += q;
            cursor->setPos(pos);
            estado = CARD4;
            break;
        case CARD4:
            pos = mapToGlobal(ui->card4->pos());
            pos += q;
            cursor->setPos(pos);

            if(users.length() > (i*NRO_ITEMS)){// Si hay mas de NRO_ITEMS usuarios, paso a la siguiente pagina - Nico
                estado = SIG;
                i++;
            }
            else{
                estado = CARD1;
                qDebug() << "valor de i= " <<i;
                for(;i > 1; i--){
                    on_boton_atras_clicked();
                }
                qDebug() << "valor de i= " <<i;
            }


            break;
        case SIG:
            pos = mapToGlobal(ui->card1->pos());
            pos += q;
            cursor->setPos(pos);
            on_boton_adelante_clicked();
            estado = CARD1;
        default:
            estado = CARD1;
        }

        delay(1000);

        //i++;
    }else {
        boton_barrido=OFF;
        ui->botonbarrido->setText("barrido:OFF");
        i=0;
    }


}

void MainWindow::delay(int msec){

      QTimer::singleShot(msec,this,SLOT(s_delay()));

}
void MainWindow::s_delay(){
    barrido();

}
void MainWindow::resetear_barrido(){
    indice=0;
    estado=CARD1;
}
int MainWindow::verificar_password(usuarios admin){
    check=new check_Dialog(this);
    admin.set_password("12345678");
    check->cargar_datos(admin.get_name(),admin.get_password());
    check->exec();



    return check->result();
}
