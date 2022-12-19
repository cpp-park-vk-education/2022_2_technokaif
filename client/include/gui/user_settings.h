#ifndef _USERSETTINGS_H_
#define _USERSETTINGS_H_

#include "../user.h"
#include "../tools/utils.h"

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
    virtual void saveClicked() = 0;
    virtual void logoutClicked() = 0;
    virtual void backClicked() = 0;
};

class UserSettings : public QWidget, public IUserSettings {
    Q_OBJECT

 public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

 private slots:
    void saveClicked() override;
    void logoutClicked() override;
    void backClicked() const override;

 private:
    void changeSettings() override;

    Ui::Widget *ui;
    IUser* user = nullptr;
    VPNContext* context;
    std::vector<std::string> urlList;
};
#endif  // _USERSETTINGS_H_
