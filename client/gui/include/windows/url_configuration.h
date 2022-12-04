#ifndef CONFIG_H
#define CONFIG_H

#include "tools/utils.h"
#include "include/user.h"
#include "include/tools/vpncontext.h"

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
    class URLConfiguration;
}
QT_END_NAMESPACE

class IURLConfiguration {
    virtual void on_BtnAdd_clicked() = 0;
    virtual void on_BtnDelete_clicked() = 0;
    virtual void on_BtnSave_clicked() = 0;
    virtual void on_BtnBack_clicked() = 0;
};

class URLConfiguration : public QWidget, public IURLConfiguration {
    Q_OBJECT

 public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

 private slots:
    void on_BtnAdd_clicked() const override;
    void on_BtnDelete_clicked() const override;
    void on_BtnSave_clicked() const override;
    void on_BtnBack_clicked() const override;

 private:
    Ui::Widget *ui;
    IUser* user = nullptr;
    VPNContext* context;
    std::vector<std::string> urlList;
};
#endif  // CONFIG_H
