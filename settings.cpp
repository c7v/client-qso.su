#include "settings.h"
#include "ui_settings.h"
#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Настройки программы");

    connect(ui->saveButton, &QPushButton::clicked, this, &Settings::save);
    connect(ui->closeButton, &QPushButton::clicked, this, &Settings::hide);

    openPath(QCoreApplication::applicationDirPath() + "/settings.ini");
}

Settings::~Settings() {
    delete ui;
}

void Settings::openPath(QString path) {
    this->path = path;
    QFileInfo info(path);
    if (!info.exists()) {
        createDefaultFile();
    }

    qs = new QSettings(path, QSettings::IniFormat);
    read();
}

void Settings::read() {
    qs->beginGroup("API");
    accessToken = qs->value("token", "").toString();
    qs->endGroup();

    qs->beginGroup("UDP");
    udpServerEnable = qs->value("enable", true).toBool();
    udpServerPort = qs->value("port", 2237).toInt();
    qs->endGroup();

    display();
}

void Settings::display() {
    ui->accessToken->setText(accessToken);
    ui->udpServerEnableCheckbox->setChecked(udpServerEnable);
    ui->udpServerPort->setValue(udpServerPort);
}

void Settings::createDefaultFile() {
    QFile newFile(path);
    newFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&newFile);
    stream << "[API]" << Qt::endl;
    stream << "token =" << Qt::endl;
    stream << Qt::endl;
    stream << "[UDP]" << Qt::endl;
    stream << "enable = 1" << Qt::endl;
    stream << "port = 2237" << Qt::endl;

    newFile.close();
}

void Settings::save() {
    qs->beginGroup("API");
    qs->setValue("token", ui->accessToken->text());
    qs->endGroup();

    qs->beginGroup("UDP");
    qs->setValue("enable", ui->udpServerEnableCheckbox->isChecked() ? 1 : 0);
    qs->setValue("port", ui->udpServerPort->value());
    qs->endGroup();

    qs->sync();
    emit saved();
}
