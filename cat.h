#ifndef CAT_H
#define CAT_H

#include <QObject>
#include <hamlib/rig.h>

class Cat : public QObject
{
    Q_OBJECT
public:
    explicit Cat(QObject *parent = nullptr);
    static QList<QPair<int, QString>> getAvailableRigs();

private:
    //static int addRig(rig_caps *caps, void* data);
    static int addRig(const rig_caps *caps, void* data);

signals:

};

#endif // CAT_H
