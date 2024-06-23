#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QFileInfo>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

    bool udpServerEnable;
    uint16_t udpServerPort;

private:
    Ui::Settings *ui;
    QSettings *qs;

    void openPath(QString path);
    void read();
    void createDefaultFile();

};

#endif // SETTINGS_H
