#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QtXml>
#include <QFile>
#include <QDir>

/*!
 * Tags de la estrucura de datos XML
 */
#define USUARIO        "usuario"
#define CUSTOMSERIAL   "customserial"

#define GENERAL         "general"
    #define NOMBRE          "nombre"
    #define APELLIDO        "apellido"
    #define NOMBRE_USUARIO  "nombreUsuario"
    #define IMAGEN          "imagen"
    #define CARPETA         "carpeta"

#define CONFIG          "config"
    #define MODO_ENTRADA    "modoEntrada"
    #define TIEMPO_BARRIDO  "tiempoBarrido"

#define SERIALCFG       "serialcfg"
    #define BAUDRATE    "baudrate"
    #define DATABITS    "databits"
    #define STOPBITS    "stopbits"
    #define PARITY      "parity"
    #define FLOWCONTROL "flowcontrol"

#define SOCKETCFG       "socketcfg"
    #define ADDR_SERVER "addrserver"
    #define PORT_SERVER "portserver"

#define MYOCFG  "myocfg"
    #define GESTURE_REST_STATE          "rest"
    #define GESTURE_FIST_STATE          "fist"
    #define GESTURE_FINGERSPREAD_STATE  "fingerspread"
    #define GESTURE_WAVEOUT_STATE       "waveout"
    #define GESTURE_WAVEIN_STATE        "wavein"
    #define GESTURE_DOUBLETAP_STATE     "doubletap"


#define APPS        "apps"

#define DEFAULT_INDENT  4

enum XmlType {NUEVO_XML_USUARIO, ABRIR_XML_USUARIO};

class XmlHandler
{
public:
    XmlHandler();
    XmlHandler(const QString &nombreArchivo, XmlType modo);

    bool save();                    // escribe los datos en el archivo XML
    bool save_comcfg();          // Guardo la configuración del puerto serial.
    bool load (QFileDevice &file);  // recupera los datos del archivo XML

    // Getters
    QString getContenidoGeneral(const QString &tagName);
    QString getContenidoConfig(const QString &tagName);
    QString getContenidoApps(const QString &tagName);
    QString getContenidoSerialCfg(const QString &tagName);
    QString getContenidoSocketsCfg(const QString &tagName);
    QString getContenidoMyoCfg(const QString &tagName);

    // Setters
    bool setContenidoGeneral(const QString &tagName, const QString &contenido);    
    bool setContenidoConfig(const QString &tagName, const QString &contenido);    
    bool setContenidoApps(const QString &tagName, const QString &contenido);    
    bool setContenidoSerialCfg(const QString &tagName, const QString &contenido);
    bool setContenidoSocketsCfg(const QString &tagName, const QString &contenido);
    bool setContenidoMyoCfg(const QString &tagName, const QString &contenido);

private:
    void crearEstructuraUsuario();
    void crearEstructuraSerial();
    void addElemento(const QString &parentNode, const QString &tagName,
                     const QString &contenido = QString());

    QDomDocument m_doc;
    QFile m_file;
    QDir m_dir;
};

#endif // XMLHANDLER_H
