#include "photoedit.h"
#include "ui_photoedit.h"
#include <QDesktopWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QPen>
#include <QDir>
#include <QMessageBox>

#define OFFSETY         50
#define NOMBREVENTANA   "Editor de fotos"
#define DIRUSUARIOS     QDir::currentPath()+"/sci/usuarios/"



Photoedit::Photoedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Photoedit)
{
    ui->setupUi(this);
    mImage = nullptr;
    mPainter = nullptr;
    mEnabled = false;
    mCutImage = nullptr;
    mImagePrev = nullptr;
    pathImage = nullptr;
}

Photoedit::Photoedit(QWidget *parent, const QString &pathImage, const QString &nameImg):
    QDialog(parent),
    ui(new Ui::Photoedit)
{
    ui->setupUi(this);
    mMouse = new QCursor(cursor());
    this->pathImage = new QString(pathImage);
    nameImage = new QString(nameImg);
    mImg = new QImageReader(pathImage);
    mSizeImg = new QSize(1080,720);
    mSizeImgBegin = new QSize(mImg->size());
    mImg->setScaledSize(*mSizeImg);
    qDebug() << "ancho: " << mImg->size().width();
    mImage = new QImage(mImg->read());
    qDebug() << "ancho: " << mImg->size().width();
    this->setWindowTitle(NOMBREVENTANA);
    this->setFixedSize(1080,740);
    mPainter = new QPainter(mImage);
    pen = new QPen(Qt::black);
    pen->setCapStyle(Qt::RoundCap);
    mEnabled = false;
    mCutImage = nullptr;
    mImagePrev = nullptr;
    cutEnabled = true;
    refreshOffset();
    centerImage();
    drawRect();
    paintRect();

    connect(ui->PB_retroceder, SIGNAL(clicked()), this, SLOT(backImage()));
    connect(ui->PB_recortar, SIGNAL(clicked()), this, SLOT(cut()));
    connect(ui->PB_aceptar, SIGNAL(clicked()), this, SLOT(Save()));
    connect(ui->PB_salir, SIGNAL(clicked()), this, SLOT(close()));

    qDebug()<<"mBegin_X: " << mBegin.x() << "mBegin_Y: " << mBegin.y();
}

Photoedit::~Photoedit()
{
    delete ui;
    delete mPainter;
    delete mImage;
    delete mImagePrev;
}

void Photoedit::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.drawImage(offset.x(), offset.y(), *mImage);
    ev->accept();
}

void Photoedit::mousePressEvent(QMouseEvent *ev)
{
    if(!ui->PB_recortar->isEnabled()){
        ev->accept();
        return;
    }
    if(rectPress(ev->pos())){
        mEnabled = true;
        mMouse->setPos(mapToGlobal(mBegin+offset));
        mMouse->setShape(Qt::SizeAllCursor);
        setCursor(*mMouse);
    }
    ev->accept();
}

void Photoedit::mouseMoveEvent(QMouseEvent *ev)
{
    if(!mEnabled){
        ev->accept();
        return;
    }
    cleanWindow();
    mBegin = ev->pos();
    checkOffset(mBegin);
    qDebug()<<"move mBegin_X: " << mBegin.x() << "mBegin_Y: " << mBegin.y();
    checkEndPoint();
    drawRect();
    paintRect();
//    mEnd = ev->pos();
//    checkOffset(mEnd);
//    checkEndPoint(mEnd);
//    mPainter->drawRect(mBegin.x(),mBegin.y(),mEnd.x()-mBegin.x(),mEnd.y()-mBegin.y());
    update();
    ev->accept();
}

void Photoedit::mouseReleaseEvent(QMouseEvent *ev)
{
//    QBrush aux;
//    aux.setStyle(Qt::Dense2Pattern);
    mEnabled = false;
//    mPainter->setPen(*pen);
//    mEnd = ev->pos();
//    checkOffset(mEnd);
//    checkEndPoint(mEnd);
//    mPainter->setBrush(aux);
//    mPainter->drawRect(mBegin.x(),mBegin.y(),mEnd.x()-mBegin.x(),mEnd.y()-mBegin.y());
    mMouse->setShape(Qt::ArrowCursor);
    setCursor(*mMouse);
    update();
    ev->accept();
}

void Photoedit::wheelEvent(QWheelEvent *ev)
{
    if(!cutEnabled)
        return;

    if(ev->angleDelta().y() > 0)
        ZOOMIN;
    else
        ZOOMOUT;

    cleanWindow();
    refreshOffset();
    refreshForZoom();
    drawRect();
    paintRect();

    update();
    ev->accept();

}

//Limpia el dibujo previo
void Photoedit::cleanWindow()
{
    refreshImageReader();

    delete mPainter;
    delete mImage;
    if(mCutImage == nullptr){
        mImage = new QImage(mImg->read());
    }
    else{
        mImage = new QImage(*mCutImage);
    }
    mPainter = new QPainter(mImage);
}

// Pinta alrededor del rectangulo de corte
void Photoedit::paintRect()
{
    int x, y, w, h;
    QBrush fill;
    fill.setStyle(Qt::Dense2Pattern);
    pen->setStyle(Qt::DotLine);
    pen->setWidth(1);
    mPainter->setPen(*pen);
    mPainter->setBrush(fill);

    // Primer rectangulo (izquierda)
    x = 0;
    y = 0;
    w = mBegin.x();
    h = mSizeImg->height();
    mPainter->drawRect(x, y, w, h);

    // Segundo rectangulo (centro arriba)
    x = mBegin.x();
    y = 0;
    w = mCut.x();
    h = mBegin.y();
    mPainter->drawRect(x, y, w, h);

    // Tercer rectangulo (centro abajo)
    x = mBegin.x();
    y = mBegin.y()+mCut.y();
    w = mCut.x();
    h = mSizeImg->height()-y;
    mPainter->drawRect(x, y, w, h);

    // Cuarto rectangulo (derecha)
    x = mBegin.x()+mCut.x();
    y = 0;
    w = mSizeImg->width()-x;
    h = mSizeImg->height();
    mPainter->drawRect(x, y, w, h);

    update();
}

// Chequea si se hizo click dentro del rectangulo
// que selecciona que parte cortar de la imagen
bool Photoedit::rectPress(const QPoint &po)
{
    bool res = false;
    QPoint p = po;

    checkOffset(p);
    if(p.x() > mBegin.x() && p.x() < (mBegin.x()+mCut.x()) && p.y() > mBegin.y() && p.y() < (mBegin.y()+mCut.y()))
        res = true;

    return res;
}

// Chequea el tamaño de la ventana
// para evitar recortar por fuera
void Photoedit::checkEndPoint()
{
    QSize sizeWindow(this->size());
    int maxX, maxY, minX, minY;


    if(mSizeImg->width() > sizeWindow.width()){
        maxX = sizeWindow.width() + ((mSizeImg->width() - sizeWindow.width())/2);
        minX = (mSizeImg->width() - sizeWindow.width())/2;
    }
    else{
        maxX = mSizeImg->width();
        minX = 0;
    }

    if(mSizeImg->height() > sizeWindow.height()){
        maxY = sizeWindow.height() + ((mSizeImg->height() - sizeWindow.height())/2);
        minY = (mSizeImg->height() - sizeWindow.height())/2;
    }
    else{
        maxY = mSizeImg->height();
        minY = 0;
    }

    // Control de maximo
    if((mBegin.x()+mCut.x()) > maxX){
        mBegin.setX(maxX-mCut.x()-1);
    }

    if((mBegin.y()+mCut.y()) > maxY){
        mBegin.setY(maxY-mCut.y()-1);
    }


    // Control de minimo
    if(mBegin.x() < minX){
        mBegin.setX(minX);
    }

    if(mBegin.y() < minY){
        mBegin.setY(minY);
    }

}

void Photoedit::checkOffset(QPoint &point)
{
    point.setX(point.x() - offset.x());
    point.setY(point.y() - offset.y());
}

int Photoedit::deltaX(int xf, int xi)
{
    int dx;
    dx = xf - xi;

    if(dx < 0) dx = -dx;

    if(dx < VARX){
        dx = VARX;
    }

    return dx;
}

int Photoedit::deltaY(int yf, int yi)
{
    int dy;
    dy = yf - yi;

    if(dy < 0) dy = -dy;

    if(dy < VARY){
        dy = VARY;
    }

    return dy;
}

void Photoedit::refreshOffset()
{
    // Centro la imagen
    offset.setX((this->size().width()/2)-(mImage->width()/2));    // Tamaño ventana/2 - tamaño imagen/2
    offset.setY(((this->size().height()/2)-(mImage->height()/2))+(OFFSETY/2));    // Tamaño ventana/2 - tamaño imagen/2

//    offset.setX((this->size().width()/2)-(mSizeImg->width()/2));    // Tamaño ventana/2 - tamaño imagen/2
//    offset.setY(((this->size().height()/2)-(mSizeImg->height()/2))+(OFFSETY/2));    // Tamaño ventana/2 - tamaño imagen/2

}

// Recargo la imagen porque luego de un read
// se pierde o se borra la imagen
void Photoedit::refreshImageReader()
{
    delete mImg;
    mImg = new QImageReader(*pathImage);
    mImg->setScaledSize(*mSizeImg);
}

void Photoedit::centerImage()
{
    mCut.setX(mSizeImg->width()*(float(VARX)/mSizeImgBegin->width())); // tamaño_escala * (valor_ancho/tamaño_original)
    mBegin.setX((this->width()/2)-(mCut.x()/2));   // punto inicial en x

    mCut.setY(mSizeImg->height()*(float(VARY)/mSizeImgBegin->height())); // tamaño_escala * (valor_ancho/tamaño_original)
    mBegin.setY((this->height()/2)-(mCut.y()/2));  // punto inicial en y
}

void Photoedit::drawRect()
{
    pen->setWidth(3);
    pen->setStyle(Qt::SolidLine);
    mPainter->setPen(*pen);

    mPainter->drawRect(mBegin.x(), mBegin.y(), mCut.x(), mCut.y());
    update();
}

void Photoedit::imgZoom(bool zoom)
{
//    static int c = 0;
    delete mImg;
    mImg = new QImageReader(*pathImage);
//    qDebug() << "ancho: " << this->size().width();
    if(zoom){
        if(!(mSizeImg->width() + 60 > SIZEMAX_X || mSizeImg->height() + 60 > SIZEMAX_Y)){
            mSizeImg->setWidth(mSizeImg->width() + 60);
            mSizeImg->setHeight(mSizeImg->height() + 60);
        }
    }
    else{
        if(!(mSizeImg->width() - 60 < mCut.x() || mSizeImg->height() - 60 < mCut.y())){ // Si no superan el tamaño minino, puedo seguir alejando la imagen
            mSizeImg->setWidth(mSizeImg->width() - 60);
            mSizeImg->setHeight(mSizeImg->height() - 60);
        }
    }
    mImg->setScaledSize(*mSizeImg);
//    qDebug() << "x: "<< mSizeImg->width() << "y: "<< mSizeImg->height();

}

// Se encarga de centrar el punto inicial
// luego de haber hecho zoom a la imagen
void Photoedit::refreshForZoom()
{
    mBegin.setX((mSizeImg->width()/2)-(mCut.x()/2));   // punto inicial en x
    mBegin.setY((mSizeImg->height()/2)-(mCut.y()/2));  // punto inicial en y

//    if(mSizeImg->width() > this->size().width())
//        mBegin.setX(mBegin.x() + ((mSizeImg->width() - this->size().width())/2));

//    if(mSizeImg->height() > this->size().height())
//        mBegin.setY(mBegin.y() + ((mSizeImg->height() - this->size().height())/2) );

//    qDebug()<<"mBegin_X: " << mBegin.x() << "mBegin_Y: " << mBegin.y();
}

void Photoedit::Save()
{
    if(mCutImage != nullptr){
        mCutImage->save(DIRUSUARIOS+nameImage);
        accept();
    }
    else
        QMessageBox::warning(this,"Advertencia","No se encuentra un recorte de la imagen. Asegurese de hacer el recorte e intente nuevamente.");
}

void Photoedit::cut()
{
    if(mCutImage == nullptr){
        refreshImageReader();
        mImagePrev = new QImage(mImg->read());
    }
    else
        mImagePrev = new QImage(*mCutImage);

    mCutImage = new QImage(mImage->copy(mBegin.x(), mBegin.y(), mCut.x(), mCut.y()));
    delete mPainter;
    delete mImage;
    mImage = new QImage(*mCutImage);
    mPainter = new QPainter(mImage);

    refreshOffset();
    centerImage();
    update();

    ui->PB_recortar->setEnabled(false);
    cutEnabled = false;
}

void Photoedit::backImage()
{
    if(mImagePrev == nullptr)
        return;
    delete mPainter;
    delete mImage;
    delete mCutImage;
    mImage = new QImage(*mImagePrev);
    mCutImage = nullptr;//new QImage(*mImagePrev);
    mPainter = new QPainter(mImage);

    mSizeImg->setWidth(1080);
    mSizeImg->setHeight(720);
    mSizeImgBegin->setWidth(mImg->size().width());
    mSizeImgBegin->setHeight(mImg->size().height());

    cleanWindow();
    refreshOffset();
    centerImage();
    drawRect();
    paintRect();
    update();

    ui->PB_recortar->setEnabled(true);
    cutEnabled = true;
}
