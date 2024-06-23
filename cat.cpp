#include "cat.h"

Cat::Cat(QObject *parent)
    : QObject{parent}
{
}

QList<QPair<int, QString>> Cat::getAvailableRigs() {
    QList<QPair<int, QString>> riglist;
    rig_load_all_backends();
    rig_list_foreach(addRig, &riglist);
    return riglist;
}

//int Cat::addRig(rig_caps *caps, void* data) {
int Cat::addRig(const rig_caps *caps, void* data) {
    QList<QPair<int, QString>> *list = static_cast<QList<QPair<int, QString>>*>(data);
    QString name = QString("%1 %2").arg(caps->mfg_name, caps->model_name);
    list->append(QPair<int, QString>(caps->rig_model, name));
    return -1;
}
