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
    virtual void nlClicked() = 0;
    virtual void rusClicked() = 0;
};

class CountryWindow : public QWidget, public ICountryWindow {
    Q_OBJECT

 public:
    explicit CountryWindow(QWidget *parent = nullptr);
    ~CountryWindow();

    QPushButton* nlBtn;
    QPushButton* rusBtn;

 private slots:
    void nlClicked() override;
    void rusClicked() override;

 private:
    VPNServer server = VPNServer::NETHERLANDS;

    QVBoxLayout* layout;

    QLabel* header;

    QLabel* amsterdamLabel;
    QLabel* moscowLabel;

    QLabel* soon;
};
#endif  // _COUNTRYWINDOW_H_
