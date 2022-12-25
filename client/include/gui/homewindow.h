#ifndef _HOMEWINDOW_H_
#define _HOMEWINDOW_H_

#include "../tools/utils.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>


namespace Ui {
class homeWindow;
}

class IHomeWidget {
    virtual void runToggled(bool checked) = 0;
    virtual void modeToggled(bool checked) = 0;
};

class HomeWindow : public QWidget, public IHomeWidget {
    Q_OBJECT

 public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

    QCheckBox* runBtn;
    QCheckBox* modeBtn;
    QLabel* vpnStatus;

    void setUserIp(std::string ip);

 private slots:
    void runToggled(bool checked) override;
    void modeToggled(bool checked) override;

 private:
    QVBoxLayout* layout;

    QHBoxLayout* runLayout;
    QHBoxLayout* statusLayout;

    QHBoxLayout* modeLayout;
    QLabel* lazyMode;
    QLabel* fullMode;

    QHBoxLayout* ipLayout;
    QLabel* ipLabel;
    QLabel* userIp;
};

#endif  // _HOMEWINDOW_H_
