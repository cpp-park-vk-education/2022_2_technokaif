#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include "../tools/utils.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class ConfigWindow;
}

class IConfigWidget {
    virtual void addClicked() = 0;
    virtual void clearClicked() = 0;
    virtual void deleteClicked() = 0;
};

class ConfigWindow : public QWidget, public IConfigWidget
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = nullptr);
    ~ConfigWindow();

private slots:
    void addClicked() override;
    void clearClicked() override;
    void deleteClicked() override;

private:
    QVBoxLayout* layout;
    QLabel* header;

    QListWidget* domainList;

    QHBoxLayout* buttons;
    QPushButton* deleteBtn;
    QPushButton* clearBtn;

    QHBoxLayout* inputLayout;
    QLineEdit* domainInput;
    QPushButton* addBtn;

    QLabel* errorField;
};

#endif // CONFIGWINDOW_H
