#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QImage"
#include "QPixmap"
#include "QLabel"
#include "iostream"
#include "string"

using namespace QtCharts;

using namespace std ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayWindown(QImage &image,QString title) {
    QLabel *label = new QLabel ();
    label->setPixmap(QPixmap::fromImage(image));
    label->setWindowTitle(title);
    label->show();
}

void MainWindow::on_bt_find_clicked()
{
//    D:/trung/hinh
    QString filename = QFileDialog::getOpenFileName(this,"Open File",
                                                    "/home/banhtrung/Pictures",
                                                    "*.* All File;; *.bmp;; *.jpeg;; *.jpg;; *.png;;");
    if (filename.isEmpty() ) {
        return ;
    }
    ui->il_Path->setText(filename);
    QImage img(filename);
    DisplayWindown(img,"meo meo");
}

void MainWindow::on_bt_hisSlide_gray_clicked()
{
    QString file = ui->il_Path->text();
    QImage imgin (file);
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    int c = ui->il_num->text().toInt();
    for (int x=0 ; x<imgin.width();x++) {
        for (int y =0 ;y < imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray_in = qGray(color);
            int gray_out = gray_in +c ;
            if (gray_out>255)
                gray_out = 255 ;
            if (gray_out<0)
                gray_out=0 ;
            QRgb color_out = qRgb(gray_out,gray_out,gray_out);
            imgout.setPixel(x,y,color_out);
        }
    }
    DisplayWindown(imgout,"meo meo");
}

void MainWindow::on_bt_hisSlide_color_clicked()
{
    QString file = ui->il_Path->text();
    QImage imgin (file);
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    int c = ui->il_num->text().toInt();
    for (int x=0 ; x<imgin.width();x++) {
        for (int y =0 ;y < imgin.height();y++) {
            QRgb rgb = imgin.pixel(x,y);
            QColor color(rgb) ;
            int h,s,v;
            color.getHsv(&h,&s,&v);
            int v_out = v+c ;
            if (v_out>255 )
                v_out =255 ;
            if (v_out < 0)
                v_out = 0 ;
            QColor color_out = QColor::fromHsv(h,s,v_out);
            imgout.setPixel(x,y,color_out.rgb());
        }
    }
    DisplayWindown(imgout,"meo meo");
}

void MainWindow::on_bt_segmenttion_clicked()
{
    QString file = ui->il_Path->text();
    QImage imgin (file);
    QImage imgout (imgin.width(),imgin.height(),QImage::Format_ARGB32);
    int c = ui->il_num->text().toInt();
    for (int x=0 ; x<imgin.width();x++) {
        for (int y =0 ;y < imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray_in = qGray(color);
            int gray_out = gray_in +c ;
            if (gray_out>127)
                gray_out = 255 ;
            if (gray_out<= 127)
                gray_out=0 ;
            QRgb color_out = qRgb(gray_out,gray_out,gray_out);
            imgout.setPixel(x,y,color_out);
        }
    }
    DisplayWindown(imgout,"meo meo");
}
int MainWindow::max(int cols[]) {
    int max =0 ;
    for (int i =0 ;i<255 ;i++) {
        if (cols[i]>= max){
            max = cols[i];
        }
    }
    return max;
}

void MainWindow::on_bt_graph_gray_clicked()
{
    int cols [255] ;
    for (int i=0 ; i<255 ; i++) {
       cols[i] = 0;
    }
    QString file = ui->il_Path->text();
    QImage imgin (file);

    for (int x=0 ; x<imgin.width();x++) {
        for (int y =0 ;y < imgin.height();y++) {
            QRgb color = imgin.pixel(x,y);
            int gray_in = qGray(color);
            QRgb color_out = qRgb(gray_in,gray_in,gray_in);
            cols[gray_in] = cols[gray_in]+ 1 ;
//            cout << gray_in << " ";
        }
//        cout << endl ;
    }


    QLineSeries *line = new QLineSeries();
    line->append(0.0,0.0);
    line->append(255.0,max(cols));
    for (int i=0 ; i<255 ; i++) {
       *line << QPoint(i,cols[i]);
       cout << to_string(cols[i]) << endl;
    }

    QChart *chart = new QChart();

    chart->legend()->hide();
    chart->addSeries(line);
    chart->createDefaultAxes();
    chart->setTitle("is okey");

    QChartView *chartView = new QChartView(chart);

    QGridLayout *gridLayout = new QGridLayout(ui->centralWidget);
    gridLayout->addWidget(chartView,0,0);

}
