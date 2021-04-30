#include "xmlhandler.h"

/*!
 * \brief XmlHandler::XmlHandler
 */
XmlHandler::XmlHandler()
{
    // Defino el nombre del archivo por default (vacío)
    m_file.setFileName(QString());
}

/*!
 * \brief XmlHandler::XmlHandler
 * \param nombreArchivo
 * \param modo
 */
XmlHandler::XmlHandler(const QString &nombreArchivo, XmlType modo)
{
    switch (modo) {
        case NUEVO_XML_USUARIO:
            m_file.setFileName(nombreArchivo+".sci");
            crearEstructuraUsuario();
            break;

        case ABRIR_XML_USUARIO:
            m_file.setFileName(nombreArchivo);
            break;

    }
}

/*!
 * \brief XmlHandler::save
 * \return
 */
bool XmlHandler::save()
{
    QFile file(getContenidoGeneral(CARPETA)+"/"+getContenidoGeneral(NOMBRE_USUARIO)+".sci");

    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) == true ) {
        // Escribe los datos en el archivo XML
        QTextStream stream(&file);
        m_doc.save(stream, DEFAULT_INDENT, QDomNode::EncodingFromDocument);
        file.close();
        return true;
    }
    else
        return false;
}

/*!
 * \brief XmlHandler::save_serialcfg
 * \return
 */
bool XmlHandler::save_comcfg()
{
    QFile file(getContenidoGeneral(CARPETA)+"/"+"comcfg"+".sci");

    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) == true ) {
        // Escribe los datos en el archivo XML
        QTextStream stream(&file);
        m_doc.save(stream, DEFAULT_INDENT, QDomNode::EncodingFromDocument);
        file.close();
        return true;
    }
    else
        return false;
}

/*!
 * \brief XmlHandler::load
 * \param file
 * \return
 */
bool XmlHandler::load(QFileDevice &file)
{
    return (m_doc.setContent(&file));
}

bool XmlHandler::setContenidoGeneral(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(GENERAL).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true)
            element.firstChild().setNodeValue(contenido);
        else
            element.appendChild(m_doc.createTextNode(contenido));

        return true;
    } else
        return false;
}

QString XmlHandler::getContenidoGeneral(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(GENERAL).firstChildElement(tagName);
    if(!element.isNull())
        return (element.text());
    else
        return (QString::number(-1));
}

QString XmlHandler::getContenidoSerialCfg(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(SERIALCFG).firstChildElement(tagName);
    if(!element.isNull()) return (element.text());
    else return (QString::number(-1));
}

bool XmlHandler::setContenidoSerialCfg(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(SERIALCFG).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true) element.firstChild().setNodeValue(contenido);
        else element.appendChild(m_doc.createTextNode(contenido));
        return true;
    }
    else return false;
}



bool XmlHandler::setContenidoSocketsCfg(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(SOCKETCFG).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true) element.firstChild().setNodeValue(contenido);
        else element.appendChild(m_doc.createTextNode(contenido));
        return true;
    }
    else return false;
}

QString XmlHandler::getContenidoSocketsCfg(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(SOCKETCFG).firstChildElement(tagName);
    if(!element.isNull()) return (element.text());
    else return (QString::number(-1));
}

QString XmlHandler::getContenidoMyoCfg(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(MYOCFG).firstChildElement(tagName);
    if(!element.isNull()) return (element.text());
    else return (QString::number(-1));
}

bool XmlHandler::setContenidoMyoCfg(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(MYOCFG).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true) element.firstChild().setNodeValue(contenido);
        else element.appendChild(m_doc.createTextNode(contenido));
        return true;
    }
    else return false;
}

bool XmlHandler::setContenidoConfig(const QString &tagName, const QString &contenido)
{
    QDomElement element = m_doc.documentElement().firstChildElement(CONFIG).firstChildElement(tagName);

    if(!element.isNull()) {
        if (element.hasChildNodes() == true)
            element.firstChild().setNodeValue(contenido);
        else
            element.appendChild(m_doc.createTextNode(contenido));

        return true;
    } else
        return false;
}

QString XmlHandler::getContenidoConfig(const QString &tagName)
{
    QDomElement element = m_doc.documentElement().firstChildElement(CONFIG).firstChildElement(tagName);
    if(!element.isNull())
        return (element.text());
    else
        return (QString::number(-1));
}

bool XmlHandler::setContenidoApps(const QString &tagName, const QString &contenido)
{
    // Falta implementar
    // Este codigo no hace nada, es para evitar que salgan warning
    tagName.at(0);
    contenido.at(0);

    // return false; evita errores/warnings
    return false;
}

QString XmlHandler::getContenidoApps(const QString &tagName)
{
    // Falta implemntar
    // Este codigo no hace nada, es para evitar que salgan warning
    tagName.at(0);
    // return 0; evita errores/warnings
    return 0;
}

/*!
 * \brief XmlHandler::crearEstructuraUsuario
 */
void XmlHandler::crearEstructuraUsuario()
{
    // Crea el encabezado del archivo XML y lo agrega al documento
    QDomProcessingInstruction instr = m_doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    m_doc.appendChild(instr);

    // Crea el elemento 'raiz' (usuario) y lo agrega al documento
    QDomElement root = m_doc.createElement(USUARIO);
    m_doc.appendChild(root);

    // Crea los elementos principales
    root.appendChild(m_doc.createElement(GENERAL));
    root.appendChild(m_doc.createElement(CONFIG));
    root.appendChild(m_doc.createElement(SERIALCFG));
    root.appendChild(m_doc.createElement(SOCKETCFG));
    root.appendChild(m_doc.createElement(MYOCFG));
    root.appendChild(m_doc.createElement(APPS));

    // Crea los sub-elementos dentro de 'general'
    addElemento(GENERAL, NOMBRE);
    addElemento(GENERAL, APELLIDO);
    addElemento(GENERAL, NOMBRE_USUARIO);
    addElemento(GENERAL, IMAGEN);
    addElemento(GENERAL, CARPETA);

    // Crea los sub-elementos dentro de 'config'
    addElemento(CONFIG, MODO_ENTRADA);
    addElemento(CONFIG, TIEMPO_BARRIDO);

    // Crea los sub-elementos dentro de 'serialcfg'
    addElemento(SERIALCFG,BAUDRATE);
    addElemento(SERIALCFG,STOPBITS);
    addElemento(SERIALCFG,DATABITS);
    addElemento(SERIALCFG,PARITY);
    addElemento(SERIALCFG,FLOWCONTROL);

    // Crea los sub-elementos dentro de 'socketcfg'
    addElemento(SOCKETCFG, ADDR_SERVER);
    addElemento(SOCKETCFG, PORT_SERVER);

    // Crea los sub-elementos dentro de 'myocfg'
    addElemento(MYOCFG,GESTURE_REST_STATE);
    addElemento(MYOCFG,GESTURE_FIST_STATE);
    addElemento(MYOCFG,GESTURE_FINGERSPREAD_STATE);
    addElemento(MYOCFG,GESTURE_WAVEIN_STATE);
    addElemento(MYOCFG,GESTURE_WAVEOUT_STATE);
    addElemento(MYOCFG,GESTURE_DOUBLETAP_STATE);

    // Crea los sub-elementos dentro de 'apps'
    //addElemento(APPS, ); Falta definir!
}

/*!
 * \brief XmlHandler::crearEstructuraSerial
 */
void XmlHandler::crearEstructuraSerial(void)
{
    // Crea el encabezado del archivo XML y lo agrega al documento
    QDomProcessingInstruction instr = m_doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    m_doc.appendChild(instr);

    // Crea el elemento 'raiz' (usuario) y lo agrega al documento
    QDomElement root = m_doc.createElement(CUSTOMSERIAL);
    m_doc.appendChild(root);

    // Crea los elementos principales
    root.appendChild(m_doc.createElement(SERIALCFG));

    // Crea los sub-elementos dentro de 'serialcfg"
    addElemento(SERIALCFG,BAUDRATE);
    addElemento(SERIALCFG,STOPBITS);
    addElemento(SERIALCFG,DATABITS);
    addElemento(SERIALCFG,PARITY);
    addElemento(SERIALCFG,FLOWCONTROL);
}

/*!
 * \brief XmlHandler::addElemento
 * \param parentNode
 * \param tagName
 * \param contenido
 * Crea un nuevo 'tag' en un determinado 'parent node' ( puede o no incluir un 'contenido' )
 */
void XmlHandler::addElemento(const QString &parentNode, const QString &tagName, const QString &contenido)
{
    if( m_doc.documentElement().firstChildElement(parentNode).firstChildElement(tagName).isNull() )
    {
        QDomElement newElement = m_doc.createElement(tagName);

        m_doc.documentElement().firstChildElement(parentNode).appendChild(newElement);

        if( !contenido.isNull() )
            newElement.appendChild(m_doc.createTextNode(contenido));
    }
}
