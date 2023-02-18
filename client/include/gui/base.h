#ifndef _BASE_H_
#define _BASE_H_

#include "../tools/utils.h"
#include "../network/client.h"

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "homewindow.h"
#include "configwindow.h"
#include "countrywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

// Base app window
class Base : public QWidget {
    Q_OBJECT

 public:
    Base(QWidget *parent = nullptr);
    ~Base();

 private slots:
    // Switch page
    void mainClicked();
    void configClicked();
    void countryClicked();

    void runChanged(bool checked);
    void modeChanged(bool checked);

    void rusClicked();
    void nlClicked();

 private:
    boost::asio::io_context context;
    std::string ip = "51.250.1.154";
    uint port = 2020;

    Client client;

    VPNMode mode = VPNMode::TOTAL;
    RunStatus state = RunStatus::STOPPED;

    std::vector<std::string> getUrlList();

    QVBoxLayout* layout;

    QHBoxLayout* header;
    QLabel* logo;
    QLabel* appName;

    QStackedWidget* pages;
    HomeWindow* homePage;
    ConfigWindow* configPage;
    CountryWindow* countryPage;

    QHBoxLayout* footerBar;
    QPushButton* configBtn;
    QPushButton* mainBtn;
    QPushButton* countryBtn;
};

#endif  // _BASE_H_
