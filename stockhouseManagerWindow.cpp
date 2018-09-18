#include "stockhouseManagerWindow.h"
#include "ui_stockhousemanager.h"


StockhouseManager::StockhouseManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StockhouseManager)
{
    ui->setupUi(this);

    // Connect button signal to appropriate slot
    connect(ui->btnAvvia, SIGNAL (released()), this, SLOT (on_btnAvvia_clicked()));

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

}

void StockhouseManager::closeEvent(QCloseEvent *event)
{
    if(video.isOpened()) {
        QMessageBox::warning(this,
        "Warning",
        "Stop the video before closing the application!");
        event->ignore();
    }
    else {
        event->accept();
    }
}

StockhouseManager::~StockhouseManager()
{
    delete ui;
}

void StockhouseManager::on_btnAvvia_clicked()
{
    using namespace cv;

    if(video.isOpened())
    {
        ui->btnAvvia->setText("Start");
        video.release();
        return;
    }

    bool isCamera;
    int cameraIndex = ui->lineEdit->text().toInt(&isCamera);
    if(isCamera) {
        if(!video.open(cameraIndex))
        {
            QMessageBox::critical(this,
            "Camera Error",
            "Make sure you entered a correct camera index,"
            "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }
    else
    {
    if(!video.open(ui->lineEdit->text().trimmed().toStdString())) {
        QMessageBox::critical(this,
        "Video Error",
        "Make sure you entered a correct and supported video file path,"
        "<br>or a correct RTSP feed URL!");
        return;
        }
    }

    this->ui->btnAvvia->setText("Stop");

    Mat frame;
    while(video.isOpened())
    {
        video >> frame;
        if(!frame.empty())
        {
            copyMakeBorder(frame,
                           frame,
                           frame.rows/2,
                           frame.rows/2,
                           frame.cols/2,
                           frame.cols/2,
                           BORDER_REFLECT);

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }


}
