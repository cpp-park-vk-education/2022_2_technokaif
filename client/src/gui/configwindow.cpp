#include "../../include/gui/configwindow.h"


ConfigWindow::ConfigWindow(QWidget *parent) :
                            QWidget(parent) {

    setFixedHeight(480);
    setFixedWidth(330);

    layout = new QVBoxLayout;
    setLayout(layout);

    header = new QLabel("Your domains for lazy mode:", this);
    header->setStyleSheet("font-size: 20px; background: transparent;");
    layout->addWidget(header);

    domainList = new QListWidget(this);
    domainList->setStyleSheet("background: transparent; font-size: 14px; border: 0px solid black;");
    layout->addWidget(domainList);

    buttons = new QHBoxLayout(this);
    buttons->setAlignment(Qt::AlignLeft);

    deleteBtn = new QPushButton("Delete", this);
    deleteBtn->setStyleSheet("font-size: 16px;");
    deleteBtn->setCursor(Qt::PointingHandCursor);
    deleteBtn->setFixedWidth(80);
    buttons->addWidget(deleteBtn);

    clearBtn = new QPushButton("Clear", this);
    clearBtn->setStyleSheet("font-size: 16px;");
    clearBtn->setCursor(Qt::PointingHandCursor);
    clearBtn->setFixedWidth(80);

    buttons->addWidget(clearBtn);

    layout->addItem(buttons);

    inputLayout = new QHBoxLayout(this);

    domainInput = new QLineEdit(this);
    inputLayout->addWidget(domainInput);

    addBtn = new QPushButton("Add", this);
    addBtn->setStyleSheet("font-size: 16px;");
    addBtn->setCursor(Qt::PointingHandCursor);
    addBtn->setFixedWidth(80);
    inputLayout->addWidget(addBtn);

    layout->addItem(inputLayout);

    errorField = new QLabel(this);
    errorField->setStyleSheet("color: red; font-size: 16px;");
    layout->addWidget(errorField);

    connect(addBtn, &QPushButton::clicked, this, &ConfigWindow::addClicked);
    connect(clearBtn, &QPushButton::clicked, this, &ConfigWindow::clearClicked);
    connect(deleteBtn, &QPushButton::clicked, this, &ConfigWindow::deleteClicked);
}

ConfigWindow::~ConfigWindow() {
   delete errorField;
    
   delete addBtn;
   delete domainInput;
   delete inputLayout;
    
   delete clearBtn;
   delete deleteBtn;
   delete buttons;

   delete domainList;

   delete header;
   delete layout;
}

void ConfigWindow::addClicked() {
    QString domain = domainInput->text();

    errorField->setText("");

    if (domain.size() == 0) {
        errorField->setText("Enter a domain");
        return;
    }

    for (uint i = 0; i < domainList->count(); ++i) {
        QListWidgetItem* item = domainList->item(i);

        if (domain == item->text()) {
            errorField->setText("Domain already added");
            return;
        }
    }

    domainList->addItem(domain);

    domainInput->setText("");
}

void ConfigWindow::clearClicked() {
    domainList->clear();
}

void ConfigWindow::deleteClicked() {
    QListWidgetItem *item = domainList->item(domainList->currentRow());

    errorField->setText("");

    if (!item) {
        errorField->setText("Choose a domain");
        return;
    }

    domainList->takeItem(domainList->currentRow());
}
