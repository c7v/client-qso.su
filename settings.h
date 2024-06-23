#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QFileInfo>
#include <QFile>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    QString accessToken;
    bool udpServerEnable;
    uint16_t udpServerPort;

private:
    Ui::Settings *ui;
    QSettings *qs;
    QString path;

    void openPath(QString path);
    void read();
    void createDefaultFile();
    void display();

private slots:
    void save();

signals:
    void saved();

};

#endif // SETTINGS_H
