#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tools/utils.h"

#include <QMainWindow>

#include "authorizer.h"
#include "start_page.h"
#include "url_configuration.h"
#include "user_settings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 public slots:
    void drawWidget();
    void closeWindow();
    void cleanWindow();
    void drawUser();

 private slots:
    void on_BtnUser_clicked();

 private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
