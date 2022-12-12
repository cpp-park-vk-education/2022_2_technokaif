#include "../../include/gui/homewindow.h"


HomeWindow::HomeWindow(QWidget *parent) :
                        QWidget(parent) {

    setFixedHeight(480);
    setFixedWidth(330);

    layout = new QVBoxLayout(this);
    setLayout(layout);

    runLayout = new QHBoxLayout(this);

    runBtn = new QCheckBox(this);
    runBtn->setStyleSheet("QCheckBox {background: transparent;}"
                "QCheckBox::indicator {width: 100px; height: 100px; border: 0px solid black; border-radius: 50%;}"
                "QCheckBox::indicator::checked {image: url(\"../img/power-off.png\");}"
                "QCheckBox::indicator::unchecked {image: url(\"../img/power-on.png\");}");
    runBtn->setCursor(Qt::PointingHandCursor);
    runBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    runLayout->addWidget(runBtn);
    layout->addItem(runLayout);

    statusLayout = new QHBoxLayout(this);

    vpnStatus = new QLabel("VPN OFF", this);
    vpnStatus->setStyleSheet("font-weight: 700; font-size: 14px; background: transparent;");
    vpnStatus->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    statusLayout->addWidget(vpnStatus);

    layout->addItem(statusLayout);

    modeLayout = new QHBoxLayout(this);

    fullMode = new QLabel("Full mode", this);
    fullMode->setStyleSheet("background: transparent; font-size: 18px;");

    modeBtn = new QCheckBox(this);
    modeBtn->setStyleSheet("QCheckBox {color: white; background: transparent;}"
                "QCheckBox::indicator {width: 110px; height: 60px;}"
                "QCheckBox::indicator::unchecked {image: url(\"../img/toggle_off.png\");}"
                "QCheckBox::indicator::checked {image: url(\"../img/toggle_on.png\");}");
    modeBtn->setCursor(Qt::PointingHandCursor);

    lazyMode = new QLabel("Lazy mode", this);
    lazyMode->setStyleSheet("background: transparent; font-size: 18px;");

    modeLayout->addWidget(fullMode);
    modeLayout->addWidget(modeBtn);
    modeLayout->addWidget(lazyMode);

    layout->addItem(modeLayout);

    ipLayout = new QHBoxLayout(this);
    ipLabel = new QLabel("Your IP:", this);
    ipLabel->setStyleSheet("font-size: 22px; background: transparent;");
    userIp = new QLabel(this);
    userIp->setStyleSheet("font-size: 18px; font-weight: 600; background: transparent;");

    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(userIp);
    layout->addItem(ipLayout);

    connect(runBtn, &QCheckBox::toggled, this, &HomeWindow::runToggled);
    connect(modeBtn, &QCheckBox::toggled, this, &HomeWindow::modeToggled);
}

HomeWindow::~HomeWindow() {
   delete userIp;
   delete ipLabel;
   delete ipLayout;

   delete lazyMode;
   delete modeBtn;
   delete fullMode;
   delete modeLayout;

   delete vpnStatus;
   delete statusLayout;
   delete runBtn;


   delete runLayout;
   delete layout;
}

void HomeWindow::runToggled(bool checked) {
    if (checked) {
        vpnStatus->setText("VPN ON");
    } else {
        vpnStatus->setText("VPN OFF");
    }
}

void HomeWindow::modeToggled(bool checked) {
    return;
}
