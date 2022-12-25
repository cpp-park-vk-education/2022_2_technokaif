#include "../../include/gui/base.h"


Base::Base(QWidget *parent) :
    QWidget(parent),
    context(),
    client(context, ip, port) {

    // Window size
    setFixedHeight(600);
    setFixedWidth(350);

    // Common style
    setStyleSheet("background-image: url(\"../img/star-sky.jpg\"); color: white;");

    // Common layout
    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    setLayout(layout);


    header = new QHBoxLayout(this);
    header->setAlignment(Qt::AlignLeft);

    logo = new QLabel(this);
    logo->setStyleSheet("image: url(\"../img/rabbit.png\");");
    logo->setFixedWidth(40);
    header->addWidget(logo);

    appName = new QLabel("Rabbit Hole", this);
    appName->setStyleSheet("font-size: 24px;");
    appName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    header->addWidget(appName);

    layout->addItem(header);

    pages = new QStackedWidget(this);
    pages->setFixedSize(330, 480);
    homePage = new HomeWindow(this);
    configPage = new ConfigWindow(this);
    countryPage = new CountryWindow(this);

    pages->insertWidget(0, homePage);
    pages->insertWidget(1, configPage);
    pages->insertWidget(2, countryPage);

    layout->addWidget(pages);

    footerBar = new QHBoxLayout(this);

    configBtn = new QPushButton("Config", this);
    configBtn->setStyleSheet("height: 40px; font-size: 20px;");
    configBtn->setCursor(Qt::PointingHandCursor);
    footerBar->addWidget(configBtn);

    mainBtn = new QPushButton("Main", this);
    mainBtn->setStyleSheet("height: 40px; font-size: 20px;");
    mainBtn->setCursor(Qt::PointingHandCursor);
    footerBar->addWidget(mainBtn);

    countryBtn = new QPushButton(this);
    countryBtn->setStyleSheet("height: 40px; font-size: 20px; image: url(\"../img/russia.png\");");
    countryBtn->setCursor(Qt::PointingHandCursor);
    footerBar->addWidget(countryBtn);

    layout->addItem(footerBar);

    connect(configBtn, &QPushButton::clicked, this, &Base::configClicked);
    connect(mainBtn, &QPushButton::clicked, this, &Base::mainClicked);
    connect(countryBtn, &QPushButton::clicked, this, &Base::countryClicked);

    connect(countryPage->rusBtn, &QPushButton::clicked, this, &Base::rusClicked);
    connect(countryPage->nlBtn, &QPushButton::clicked, this, &Base::nlClicked);

    connect(homePage->runBtn, &QCheckBox::toggled, this, &Base::runChanged);
    connect(homePage->modeBtn, &QCheckBox::toggled, this, &Base::modeChanged);

}

Base::~Base() {
   delete countryBtn;
   delete mainBtn;
   delete configBtn;
   delete footerBar;

   delete countryPage;
   delete configPage;
   delete homePage;
   delete pages;

   delete appName;
   delete logo;
   delete header;

   delete layout;
}

void Base::mainClicked() {
    pages->setCurrentIndex(0);
}

void Base::configClicked() {
    pages->setCurrentIndex(1);
}

void Base::countryClicked() {
    pages->setCurrentIndex(2);
}

void Base::rusClicked() {
    countryBtn->setStyleSheet("height: 40px; font-size: 20px; image: url(\"../img/russia.png\");");

    ip = "51.250.84.126";
    port = 2020;

    client.setEndpoint(ip, port);
}

void Base::nlClicked() {
    countryBtn->setStyleSheet("height: 40px; font-size: 20px; image: url(\"../img/netherlands.png\");");

    ip = "188.227.84.52";
    port = 2020;

    client.setEndpoint(ip, port);
}

void Base::runChanged(bool checked) {
    if (!checked) {
        state = RunStatus::STOPPED;

        client.setVPNContext(state, mode, std::vector<std::string>());
        client.sendData();
        client.stopConnection();

        homePage->setUserIp("Non-private");
    } else {
        state = RunStatus::RUNNING;

        std::vector<std::string> urlList;
        if (mode == VPNMode::OPTIONAL) {
            urlList = getUrlList();
        }
        client.setVPNContext(state, mode, urlList);

        client.connect();
        client.sendData();
        client.getData();

        homePage->setUserIp(ip);
    }
}

void Base::modeChanged(bool checked) {
    if (checked) {
        mode = VPNMode::OPTIONAL;
    } else {
        mode = VPNMode::TOTAL;
    }
}

std::vector<std::string> Base::getUrlList() {
    std::vector<std::string> urlList;

    for (uint i = 0; i < configPage->domainList->count(); ++i) {
        QListWidgetItem* item = configPage->domainList->item(i);

        urlList.push_back(item->text().toStdString());
    }

    return urlList;
}
