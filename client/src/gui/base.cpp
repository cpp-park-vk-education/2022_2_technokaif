#include "../../include/gui/base.h"


Base::Base(QWidget *parent)
    : QWidget(parent), context(), client(context, ip, port) {

    setFixedHeight(600);
    setFixedWidth(350);

    setStyleSheet("background-image: url(\"../img/star-sky.jpg\"); color: white;");

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

    pages->insertWidget(0, homePage);
    pages->insertWidget(1, configPage);

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

    profileBtn = new QPushButton("User", this);
    profileBtn->setStyleSheet("height: 40px; font-size: 20px;");
    profileBtn->setCursor(Qt::PointingHandCursor);
    footerBar->addWidget(profileBtn);

    layout->addItem(footerBar);

    connect(configBtn, &QPushButton::clicked, this, &Base::configClicked);
    connect(mainBtn, &QPushButton::clicked, this, &Base::mainClicked);
    connect(profileBtn, &QPushButton::clicked, this, &Base::profileClicked);

    connect(homePage->runBtn, &QCheckBox::toggled, this, &Base::runChanged);
    connect(homePage->modeBtn, &QCheckBox::toggled, this, &Base::modeChanged);
}

Base::~Base() {
    delete layout;

    delete header;
    delete logo;
    delete appName;

    delete pages;
    delete homePage;
    delete configPage;

    delete footerBar;
    delete configBtn;
    delete mainBtn;
    delete profileBtn;
}

void Base::mainClicked() {
    pages->setCurrentIndex(0);
}

void Base::configClicked() {
    pages->setCurrentIndex(1);
}

void Base::profileClicked() {
    pages->setCurrentIndex(2);
}

void Base::runChanged(bool checked) {
    if (checked) {
        state = RunStatus::RUNNING;
        
        std::vector<std::string> urlList;
        if (mode == VPNMode::OPTIONAL) {
            urlList = getUrlList();
        }
        client.setVPNContext(state, mode, urlList);

        client.connect();
        client.sendData();
        client.getData();

    } else {
        client.stopConnection();
        state = RunStatus::STOPPED;
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
