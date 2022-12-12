#ifndef BASE_H
#define BASE_H

#include "../tools/utils.h"
#include "../network/client.h"

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "homewindow.h"
#include "configwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget {
    Q_OBJECT

public:
    Base(QWidget *parent = nullptr);
    ~Base();

private slots:
    void mainClicked();
    void configClicked();
    void profileClicked();

    void runChanged(bool checked);
    void modeChanged(bool checked);

private:
    boost::asio::io_context context;  // ?
    const std::string ip = "51.250.94.232";
    const uint port = 2020;

    Client client;

    RunStatus state = RunStatus::TOTAL;

    std::vector<std::string> getUrlList();

    QVBoxLayout* layout;

    QHBoxLayout* header;
    QLabel* logo;
    QLabel* appName;

    QStackedWidget* pages;
    HomeWindow* homePage;
    ConfigWindow* configPage;

    QHBoxLayout* footerBar;
    QPushButton* configBtn;
    QPushButton* mainBtn;
    QPushButton* profileBtn;
};

#endif // BASE_H
