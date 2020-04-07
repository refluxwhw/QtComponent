#ifndef LOCALIPLINEEDIT_H
#define LOCALIPLINEEDIT_H

#include <QMenu>
#include <QListWidget>
#include "IPLineEdit.h"

class LocalIPLineEdit : public IPLineEdit
{
    Q_OBJECT
public:
    explicit LocalIPLineEdit(QWidget *parent = nullptr);
    void     addLocalIps();
    QMenu*   dropDownMenu();

private slots:
    void onMenuTriggered(QAction* act);
    void onDropDownClicked();

private:
    QMenu* m_menu=nullptr;
};

#endif // LOCALIPLINEEDIT_H
