#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QSO.su desktop app");

    settings = new Settings(this);
    connect(settings, &Settings::saved, this, &MainWindow::onSettingsSaved);

    udpReceiver = new UdpReceiver(this);
    if (settings->udpServerEnable) {
        if (udpReceiver->start(settings->udpServerPort)) {
            connect(udpReceiver, &UdpReceiver::heartbeat, this, [=]() {
                ui->statusbar->showMessage(QString("UDP: получен HEARTBEAT - %1 %2").arg(QString::fromUtf8(udpReceiver->version), QString::fromUtf8(udpReceiver->revision)), 1000);
            });

            ui->statusbar->showMessage("UDP сервер запущен на порту " + QString::number(settings->udpServerPort), 3000);
        } else {
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка запуска UDP сервера");
        }
    }

    initUI();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initUI() {
    connect(ui->actionSettings, &QAction::triggered, settings, &Settings::show);
}

void MainWindow::onSettingsSaved() {
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Сохранение настроек", "Для применения настроек необходим перезапуск программы. Выполнить?", QMessageBox::Yes|QMessageBox::No);

    if (confirm == QMessageBox::Yes) {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}

