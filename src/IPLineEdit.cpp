/**
 * @author  wanghaowen_1988@163.com
 * @date    2020.04.01
 * @file    IPLineEdit.cpp
 * @version 1.0
 * @brief   实现IP编辑框
 *          基于 https://blog.csdn.net/u011417605/article/details/51353337 修改而成
 */

#include "IPLineEdit.h"
#include <QRegExpValidator>
#include <QPainter>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>

IPLineEdit::IPLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    QRegExp rx("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
    QHBoxLayout *pHBox = new QHBoxLayout(this);
    pHBox->setSpacing(0);
    pHBox->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < 4; i++)
    {
        QLineEdit* e = new QLineEdit();
        m_lineEidt[i] = e;
        e->setObjectName("SubIPLineEdit");
        e->setFrame(false);
        e->setMaxLength(3);
        e->setAlignment(Qt::AlignCenter);
        e->installEventFilter(this);
        e->setValidator(new QRegExpValidator(rx, this));
        e->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        e->setContentsMargins(1,1,1,1);
        pHBox->addWidget(e, 1);

        if (3 != i) {
            QLabel *l = new QLabel(QStringLiteral("·"));
            l->setFixedWidth(8);
            l->setContentsMargins(0,0,0,0);
            l->setAlignment(Qt::AlignCenter);
            pHBox->addWidget(l);
        }
    }

    this->setReadOnly(true);
    //this->setFixedWidth(142);
}

IPLineEdit::~IPLineEdit()
{

}

bool IPLineEdit::eventFilter(QObject *obj, QEvent *ev)
{
    if (!children().contains(obj) ||  QEvent::KeyPress != ev->type()) {
        return false;
    }

    QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(ev);
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(obj);

    QString strText = pEdit->text();
    QString strSelected = pEdit->selectedText();
    int     posCursor = pEdit->cursorPosition();
    int     posSelectionStart = pEdit->selectionStart();

    switch (keyEvent->key()) {
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9: {
            QChar ch(keyEvent->key());

            if (strSelected.length() != 0) {
                strText = strText.replace(posSelectionStart, strSelected.length(), ch);
                posCursor = posSelectionStart+1;
            } else if (strText.toInt() * 10 < 255) {
                if (strText.toInt() == 0) {
                    strText = ch;
                    posCursor = 1;
                } else {
                    strText = strText.insert(posCursor, ch);
                    posCursor++;
                }
            }

            pEdit->setText(strText);
            pEdit->setCursorPosition(posCursor);

            if (strText.toInt() * 10 > 255) {
                if (pEdit->cursorPosition() == strText.length()) {
                    jumpToNext(pEdit);
                }
            }

            break;
        }

        case Qt::Key_Period:
            if (!strText.isEmpty()) {
                jumpToNext(pEdit);
            }
            break;

        case Qt::Key_Backspace: {
            if (!strSelected.isEmpty()) {
                strText = strText.remove(posSelectionStart, strSelected.length());
                posCursor = posSelectionStart;
            } else if (!strText.isEmpty()) {
                if (posCursor > 0) {
                    posCursor--;
                    strText = strText.remove(posCursor, 1);
                }
            }

            pEdit->setText(strText);
            pEdit->setCursorPosition(posCursor);

            if (0 == posCursor) {
                jumpToPre(pEdit);
            }

            break;
        }

        case Qt::Key_Left: {
            if (!strSelected.isEmpty()) {
                pEdit->setCursorPosition(posSelectionStart);
            } else if (posCursor > 0) {
                pEdit->setCursorPosition(posCursor-1);
            } else {
                jumpToPre(pEdit);
            }
            break;
        }

        case Qt::Key_Right: {
            if (!strSelected.isEmpty()) {
                pEdit->setCursorPosition(posSelectionStart+strSelected.length());
            } else if (posCursor < strText.length()) {
                pEdit->setCursorPosition(posCursor+1);
            } else {
                jumpToNext(pEdit, false);
            }
            break;
        }

        default:
            return false;
    }

    return true;
}

void IPLineEdit::setText(const QString &strIP)
{
    if (!isTextValid(strIP)) {
        return;
    } else {
        int i = 0;
        QStringList ipList = strIP.split(".");
        foreach (QString ip, ipList) {
            m_lineEidt[i++]->setText(ip);
        }
    }
}

bool IPLineEdit::isTextValid(const QString &strIP)
{
    QRegExp rx2("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    if (!rx2.exactMatch(strIP)) {
        return false;
    }
    return true;
}

int IPLineEdit::getIndex(QLineEdit *pEdit)
{
    for (int i = 0; i < 4; i++) {
        if (pEdit == m_lineEidt[i]) {
            return i;
        }
    }
    return -1;
}

void IPLineEdit::jumpToNext(QLineEdit *obj, bool selectAll)
{
    int index = getIndex(obj);
    if (index != -1 && index != 3) {
        QLineEdit* e = m_lineEidt[index + 1];
        e->setFocus();
        if (selectAll) {
            e->selectAll();
        } else {
            e->setCursorPosition(0);
        }
    }
}

void IPLineEdit::jumpToPre(QLineEdit *obj)
{
    int index = getIndex(obj);
    if (index > 0) {
        QLineEdit* e = m_lineEidt[index - 1];
        e->setFocus();
        e->setCursorPosition(e->text().length());
    }
}

QString IPLineEdit::text() const
{
    QStringList ipList;
    for (int i = 0; i < 4; i++) {
        QString ip = m_lineEidt[i]->text();
        if (ip.isEmpty()) { ip = "0"; }
        ipList << ip;
    }
    return ipList.join('.');
}
