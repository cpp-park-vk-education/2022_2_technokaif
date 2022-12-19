#include "../../include/gui/countrywindow.h"


CountryWindow::CountryWindow(QWidget *parent) : QWidget(parent) {
    
    setFixedHeight(480);
    setFixedWidth(330);

    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    setLayout(layout);

    header = new QLabel("Choose VPN Server:", this);
    header->setStyleSheet("font-size: 20px; background: transparent;");
    header->setFixedHeight(50);
    header->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);;
    layout->addWidget(header);

    netherlandsBtn = new QPushButton(this);
    netherlandsBtn->setCursor(Qt::PointingHandCursor);
    netherlandsBtn->setFixedWidth(73);
    netherlandsBtn->setFixedHeight(50);
    netherlandsBtn->setStyleSheet("image: url(\"../img/netherlands.png\");");
    netherlandsBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(netherlandsBtn);

    amsterdamLabel = new QLabel("Amsterdam", this);
    amsterdamLabel->setStyleSheet("font-size: 16px; background: transparent;");
    amsterdamLabel->setFixedHeight(30);
    amsterdamLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(amsterdamLabel);

    russiaBtn = new QPushButton(this);
    russiaBtn->setCursor(Qt::PointingHandCursor);
    russiaBtn->setFixedWidth(73);
    russiaBtn->setFixedHeight(50);
    russiaBtn->setStyleSheet("image: url(\"../img/russia.png\");");
    russiaBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(russiaBtn);

    moscowLabel = new QLabel("Moscow", this);
    moscowLabel->setStyleSheet("font-size: 16px; background: transparent;");
    moscowLabel->setFixedHeight(30);
    moscowLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(moscowLabel);

    soon = new QLabel("More servers soon", this);
    soon->setStyleSheet("font-size: 16px; background: transparent;");
    layout->addWidget(soon);


    connect(netherlandsBtn, &QPushButton::clicked, this, &CountryWindow::netherlandsClicked);
    connect(russiaBtn, &QPushButton::clicked, this, &CountryWindow::russiaClicked);
}

CountryWindow::~CountryWindow() {
    delete soon;

    delete moscowLabel;
    delete russiaBtn;
    delete amsterdamLabel;
    delete netherlandsBtn;

    delete header;

    delete layout;
}

void CountryWindow::netherlandsClicked() {
    server = VPNServer::NETHERLANDS;
}

void CountryWindow::russiaClicked() {
    server = VPNServer::RUSSIA;
}
