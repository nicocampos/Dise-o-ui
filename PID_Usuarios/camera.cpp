#include "camera.h"
#include "ui_camera.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

Camera::Camera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);
    username = nullptr;
    pathPhoto = nullptr;

    mCamera = new QCamera(this);
    mCameraViewFinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
    mLayout = new QVBoxLayout;
    mOpcionesMenu = new QMenu("Opciones",this);
    mCapturar = new QAction("Capturar",this);
    mSalir = new QAction("Salir",this);

    mOpcionesMenu->addActions({ mCapturar, mSalir});
    ui->PB_opciones->setMenu(mOpcionesMenu);
    mCamera->setViewfinder(mCameraViewFinder);
    mLayout->addWidget(mCameraViewFinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);

    connect(mSalir, SIGNAL(triggered()), this, SLOT(close()));
    connect(mCapturar, SIGNAL(triggered()), this, SLOT(Capturar()));
}

Camera::~Camera()
{
    delete ui;
    delete username;
}

void Camera::setRutaImagen(const QString &path)
{
    if(pathPhoto != nullptr)
        delete pathPhoto;
    pathPhoto = new QString(path);
}

void Camera::setNombreImagen(const QString &name)
{
    if(username != nullptr)
        delete username;
    username = new QString(name);
}

void Camera::Capturar()
{
//    auto fileName = QFileDialog::getSaveFileName(this,"Capturar", "/", "Imagen (*.jpg,*.jpeg)");
//    if(fileName.isEmpty()){
//        return;
//    }
    if(username->isEmpty() || pathPhoto->isEmpty()){
        return;
    }
    *pathPhoto += username;
    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEnconderSettings;
    imageEnconderSettings.setCodec("image/jpeg");
    imageEnconderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(imageEnconderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(*pathPhoto);
    mCamera->unlock();
}

void Camera::on_pushButton_clicked()
{

}
