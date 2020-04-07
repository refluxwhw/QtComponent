/**
 * @author  wanghaowen_1988@163.com
 * @date    2020.04.01
 * @file    IPLineEdit.h
 * @version 1.0
 * @brief   实现IP编辑框
 *          基于 https://blog.csdn.net/u011417605/article/details/51353337 修改而成
 */

#ifndef IPLINEEDIT_H
#define IPLINEEDIT_H

#include <QLineEdit>
#include <QEvent>

class IPLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    IPLineEdit(QWidget *parent = nullptr);
    ~IPLineEdit();

    void setText(const QString &strIP);
    QString text() const;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    bool isTextValid(const QString &strIP);
    inline int getIndex(QLineEdit *pEdit);
    inline void jumpToNext(QLineEdit *obj, bool selectAll=true);
    inline void jumpToPre(QLineEdit *obj);

private:
    QLineEdit *m_lineEidt[4];
};

#endif // IPLINEEDIT_H
