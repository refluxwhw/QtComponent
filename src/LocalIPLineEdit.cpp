#include "LocalIPLineEdit.h"
#include <QLayout>
#include <QStyle>
#include <QApplication>
#include <QPushButton>
#include <QNetworkInterface>
#include <QHostAddress>

LocalIPLineEdit::LocalIPLineEdit(QWidget *parent)
    : IPLineEdit(parent)
{
    m_menu = new QMenu(this);
    m_menu->hide();
    m_menu->setObjectName("local_ip_edit_menu");
    m_menu->setStyleSheet("QMenu#local_ip_edit_menu::item{"
                          "padding:2px 5px 2px 3px;"
                          "}"
                          "QMenu#local_ip_edit_menu::item:selected{"
                          "background:rgb(230, 241, 251);"
                          "padding:2px 5px 2px 5px;"
                          "}");

    QPushButton* btn = new QPushButton();
    btn->setObjectName("local_ip_edit_dropdown");
    btn->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_TitleBarUnshadeButton));
    btn->setStyleSheet("QPushButton{background: transparent;} "
                       "QPushButton:hover{"
                       "background: rgb(230, 241, 251); "
                       "border: 1px solid rgb(11, 126, 216);"
                       "}");
    btn->setIconSize(QSize(9, 9));
    btn->setMaximumWidth(18);
    layout()->addWidget(btn);

    connect(m_menu, &QMenu::triggered,
            this, &LocalIPLineEdit::onMenuTriggered);
    connect(btn, &QPushButton::clicked,
            this, &LocalIPLineEdit::onDropDownClicked);

    setMinimumWidth(150);
}

void LocalIPLineEdit::addLocalIps()
{
    m_menu->clear();
    auto addrs = QNetworkInterface::allAddresses();
    foreach (auto addr, addrs) {
        if (QAbstractSocket::IPv4Protocol == addr.protocol()) {
            m_menu->addAction(addr.toString());
        }
    }
}

QMenu *LocalIPLineEdit::dropDownMenu()
{
    return m_menu;
}

void LocalIPLineEdit::onMenuTriggered(QAction *act)
{
    QString txt = act->text();
    setText(txt);
}

void LocalIPLineEdit::onDropDownClicked()
{
    QPoint p = mapToGlobal(QPoint(0,height()+1));
    m_menu->setFixedWidth(width());
    m_menu->exec(p);
}
