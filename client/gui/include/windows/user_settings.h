#ifndef CONFIG_H
#define CONFIG_H

#include "include/user.h"

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserSettings;
}
QT_END_NAMESPACE

class IUserSettings {
 public:
    virtual void changeSettings() = 0;
    virtual void on_BtnSave_clicked() = 0;
    virtual void on_BtnLogout_clicked() = 0;
    virtual void on_BtnBack_clicked() = 0;
};

class UserSettings : public QWidget, public IUserSettings {
    Q_OBJECT

 public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

 private slots:
    void on_BtnSave_clicked() override;
    void on_BtnLogout_clicked() override;
    void on_BtnBack_clicked() const override;

 private:
    void changeSettings() override;

    Ui::Widget *ui;
    IUser* user = nullptr;
    VPNContext* context;
    std::vector<std::string> urlList;
};
#endif  // CONFIG_H
