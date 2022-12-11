#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

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

class HomeWindow : public QWidget, public IHomeWidget
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

    QCheckBox* runBtn;
    QCheckBox* modeBtn;

private slots:
    void runToggled(bool checked) override;
    void modeToggled(bool checked) override;

private:
    QVBoxLayout* layout;

    QHBoxLayout* runLayout;
    QHBoxLayout* statusLayout;
    QLabel* vpnStatus;

    QHBoxLayout* modeLayout;
    QLabel* lazyMode;
    QLabel* fullMode;

    QHBoxLayout* ipLayout;
    QLabel* ipLabel;
    QLabel* userIp;
};

#endif // HOMEWINDOW_H
