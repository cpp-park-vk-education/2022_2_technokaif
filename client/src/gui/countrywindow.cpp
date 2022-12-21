#include "../../include/gui/countrywindow.h"


CountryWindow::CountryWindow(QWidget *parent) :
    QWidget(parent) {
    
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

    nlBtn = new QPushButton(this);
    nlBtn->setCursor(Qt::PointingHandCursor);
    nlBtn->setFixedWidth(73);
    nlBtn->setFixedHeight(50);
    nlBtn->setStyleSheet("image: url(\"../img/netherlands.png\");");
    nlBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(nlBtn);

    amsterdamLabel = new QLabel("Amsterdam", this);
    amsterdamLabel->setStyleSheet("font-size: 16px; background: transparent;");
    amsterdamLabel->setFixedHeight(30);
    amsterdamLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(amsterdamLabel);

    rusBtn = new QPushButton(this);
    rusBtn->setCursor(Qt::PointingHandCursor);
    rusBtn->setFixedWidth(73);
    rusBtn->setFixedHeight(50);
    rusBtn->setStyleSheet("image: url(\"../img/russia.png\");");
    rusBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(rusBtn);

    moscowLabel = new QLabel("Moscow", this);
    moscowLabel->setStyleSheet("font-size: 16px; background: transparent;");
    moscowLabel->setFixedHeight(30);
    moscowLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    layout->addWidget(moscowLabel);

    soon = new QLabel("More servers soon", this);
    soon->setStyleSheet("font-size: 16px; background: transparent;");
    layout->addWidget(soon);

    connect(nlBtn, &QPushButton::clicked, this, &CountryWindow::nlClicked);
    connect(rusBtn, &QPushButton::clicked, this, &CountryWindow::rusClicked);
}

CountryWindow::~CountryWindow() {
    delete soon;

    delete moscowLabel;
    delete rusBtn;
    delete amsterdamLabel;
    delete nlBtn;

    delete header;

    delete layout;
}

void CountryWindow::nlClicked() {
    server = VPNServer::NETHERLANDS;
}

void CountryWindow::rusClicked() {
    server = VPNServer::RUSSIA;
}
