    #ifndef STOCKHOUSEMANAGER_H
#define STOCKHOUSEMANAGER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QCloseEvent>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace Ui {
class StockhouseManager;
}

class StockhouseManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit StockhouseManager(QWidget *parent = nullptr);
    ~StockhouseManager();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_btnAvvia_clicked();

private:
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
    Ui::StockhouseManager *ui;
};

#endif // STOCKHOUSEMANAGER_H
