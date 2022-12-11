#ifndef RABBITHOLEGUI_H
#define RABBITHOLEGUI_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../tools/utils.h"

#include "homewindow.h"
#include "configwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Base; }
QT_END_NAMESPACE

class Base : public QWidget
{
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

    QHBoxLayout* footerBar;
    QPushButton* configBtn;
    QPushButton* mainBtn;
    QPushButton* profileBtn;
};

#endif // RABBITHOLEGUI_H
