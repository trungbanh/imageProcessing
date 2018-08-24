#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void DisplayWindown (QImage &image ,QString title);
    int max (int cols[]);
private slots:
    void on_bt_find_clicked();

    void on_bt_hisSlide_gray_clicked();

    void on_bt_hisSlide_color_clicked();

    void on_bt_segmenttion_clicked();

    void on_bt_graph_gray_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
