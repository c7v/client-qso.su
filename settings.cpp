#include "settings.h"
#include "ui_settings.h"
#include <QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setWindowTitle("Настройки программы");
    openPath(QCoreApplication::applicationDirPath() + "/settings.ini");
}

Settings::~Settings() {
    delete ui;
}

void Settings::openPath(QString path) {
    QFileInfo info(path);
    if (!info.exists()) {
        createDefaultFile();
    }

    qs = new QSettings(path, QSettings::IniFormat);
    read();
}

void Settings::read() {
    qs->beginGroup("UDP");
    udpServerEnable = qs->value("enable", true).toBool();
    udpServerPort = qs->value("port", 2237).toInt();
    qs->endGroup();
}

void Settings::createDefaultFile() {

}
