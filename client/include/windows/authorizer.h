#ifndef AUTH_H
#define AUTH_H

#include "tools/utils.h"
#include "include/user.h"

#include <QWidget>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui {
    class Authorizer;
}
QT_END_NAMESPACE

class IAuthorizer {
    virtual void on_BtnAuth_clicked() = 0;
    virtual void on_BtnCheckForm_clicked() = 0;
    virtual void on_BtnBack_clicked() = 0;
};

class Authorizer : public QWidget, public IAuthorizer {
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
#endif  // AUTH_H
