#ifndef STARTPAGE_H
#define STARTPAGE_H

#include "../tools/utils.h"
#include "include/user.h"

#include <QWidget>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui {
    class StartPage;
}
QT_END_NAMESPACE

class IStartPage {
    virtual void on_BtnRun_clicked() = 0;
    virtual void on_BtnConfig_clicked() = 0;
    virtual void on_BtnChangeMode_clicked() = 0;
};

class StartPage : public QWidget, public IStartPage {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_BtnRun_clicked() const override;
    void on_BtnConfig_clicked() const override;
    void on_BtnChangeMode_clicked() const override;

private:
    Ui::Widget *ui;
};
#endif  // STARTPAGE_H
