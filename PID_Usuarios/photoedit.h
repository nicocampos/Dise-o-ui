#ifndef PHOTOEDIT_H
#define PHOTOEDIT_H

#include <QDialog>
#include <QImageReader>
#include <QWheelEvent>

#define VARX            180 // ancho del recorte
#define VARY            210 // altura del recorte

#define SIZEMAX_X       3840
#define SIZEMAX_Y       2160

#define ZOOMIN          imgZoom(true)
#define ZOOMOUT         imgZoom(false)

namespace Ui {
class Photoedit;
}

class Photoedit : public QDialog
{
    Q_OBJECT

public:
    explicit Photoedit(QWidget *parent = nullptr);
    Photoedit(QWidget *parent, const QString &pathImage, const QString &nameImg);
    ~Photoedit();

public slots:
    void Save();
    void cut();
    void backImage();

protected:
    void paintEvent(QPaintEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;

private:
    Ui::Photoedit *ui;

    QPainter *mPainter;
    QImageReader *mImg;         // Contiene la imagen cargada y permite escalar bien
    QImage *mImage;             // Contiene la imagen cargada
    QImage *mCutImage;          // Contiene la imagen cortada
    QImage *mImagePrev;         // Contiene un copia de la imagen anterior al ultimo corte
    QSize *mSizeImg;            // Contiene el tamaño de la imagen luego de escalar
    QSize *mSizeImgBegin;       // Contiene el tamaño de la imagen original

    QCursor *mMouse;            // Sirve para posicionar el mouse al mover el cuadro de recorte
    QPoint mBegin;              // Contiene la posicion de inicio del cuadro de recorte
//    QPoint mEnd;
    QPoint offset;              // Offset respecto de la ventana
    QPoint mCut;                // Contiene los valores de alto(y) y ancho(x) del cuadro de recorte
    QPoint mScroll;             // Contiene un delta del angulo que giro el scroll del mouse, 1 paso = 120
    bool cutEnabled;

    QPen *pen;
    QString *pathImage;
    QString *nameImage;
    bool mEnabled;

    void cleanWindow();
    void paintRect();

    bool rectPress(const QPoint &p);
    void checkEndPoint();
    void checkOffset(QPoint &point);
    int deltaX(int xf, int xi);
    int deltaY(int yf, int yi);

    void refreshOffset();
    void refreshImageReader();
    void centerImage();
    void drawRect();
    void imgZoom(bool);
    void refreshForZoom();
};
#endif // PHOTOEDIT_H
