#ifndef CAMERA_H
#define CAMERA_H

#include <QDialog>

namespace Ui {
class Camera;
}
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class Camera : public QDialog
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

    void setRutaImagen(const QString &path);
    void setNombreImagen(const QString &name);

public slots:
    void Capturar();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Camera *ui;

    QCamera *mCamera;
    QCameraViewfinder *mCameraViewFinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;

    QMenu *mOpcionesMenu;
    QAction *mSalir;
    QAction *mCapturar;

    QString *username;
    QString *pathPhoto;
};

#endif // CAMERA_H
