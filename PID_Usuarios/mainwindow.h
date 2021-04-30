#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"usuarios.h"
#include"xmlhandler.h"
#include"userwindow.h"
#include"adminwindow.h"
#include"check_dialog.h"
#include <signal.h>
#include <QTime>
#include <QTimer>
#include <QList>
#include <QThread>
#include <qlayout.h>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <QCursor>
#define NRO_ITEMS 4
#define OFF 0
#define ON 1
#define CARD1 1
#define CARD2 2
#define CARD3 3
#define CARD4 4
#define SIG 5
//#include<usuario.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void crear_lista_de_usuarios();
    int Obtener_usuarios();
    class usuarios* cargar_usuario(QString path);
    void Crear_pagina_usuarios(QList<class usuarios *> aux);
    QList<class usuarios*> rellenar_pagina(QList<class usuarios *> aux);
    void Mostrar_pagina(QList<class usuarios *> aux);
    void actualizar_usernames(QList<class usuarios*> aux);
    void actualizar_names(QList<class usuarios*> aux);
    void actualizar_icons(QList<class usuarios*> aux);
    int verificar_password(usuarios admin);

    void iniciar_conecciones();
    int posicion();

    void seleccionar(int x);
    void delay(int sec);
    void barrido( );
    void resetear_barrido();


public slots:
    void abrir_ventana(int i);
    void start_barrido();
    void stop_barrido();
    void s_delay();





private slots:

    void on_boton_atras_clicked();

    void on_boton_adelante_clicked();

private:
    Ui::MainWindow *ui;
    static unsigned int indice;
    static unsigned int max;
    static unsigned int boton_barrido;


    QList<class usuarios*>  users;
    QList<class usuarios*>  lista_pagina;


    QString path;
    QStringList filters;

    XmlHandler *m_datosXml;

    adminwindow *ventana_admin;
    UserWindow  *ventana_user;
    check_Dialog *check;
    static int estado;
protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void rightclicked();
    void leftclicked();


};
#endif // MAINWINDOW_H
