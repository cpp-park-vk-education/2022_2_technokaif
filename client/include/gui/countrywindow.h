#ifndef _COUNTRYWINDOW_H_
#define _COUNTRYWINDOW_H_

#include "../tools/utils.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


namespace Ui {
class CountryWindow;
}

class ICountryWindow {
 public:
    virtual void netherlandsClicked() = 0;
    virtual void russiaClicked() = 0;
};

class CountryWindow : public QWidget, public ICountryWindow {
    Q_OBJECT

 public:
    explicit CountryWindow(QWidget *parent = nullptr);
    ~CountryWindow();


 private slots:
    void netherlandsClicked() override;
    void russiaClicked() override;

 private:
    VPNServer server = VPNServer::NETHERLANDS;

    QVBoxLayout* layout;

    QLabel* header;

    QPushButton* netherlandsBtn;
    QLabel* amsterdamLabel;
    QPushButton* russiaBtn;
    QLabel* moscowLabel;

    QLabel* soon;
};
#endif  // _COUNTRYWINDOW_H_
