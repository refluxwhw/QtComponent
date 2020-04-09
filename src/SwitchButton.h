#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>
#include <QBitmap>
#include <QPropertyAnimation>

class SwitchButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QBrush onGrooveBrush      READ onGrooveBrush      WRITE setOnGrooveBrush     )
    Q_PROPERTY(QBrush onHandleBrush      READ onHandleBrush      WRITE setOnHandleBrush     )
    Q_PROPERTY(QBrush offGrooveBrush     READ offGrooveBrush     WRITE setOffGrooveBrush    )
    Q_PROPERTY(QBrush offHandleBrush     READ offHandleBrush     WRITE setOffHandleBrush    )
    Q_PROPERTY(QBrush disableGrooveBrush READ disableGrooveBrush WRITE setDisableGrooveBrush)
    Q_PROPERTY(QBrush disableHandleBrush READ disableHandleBrush WRITE setDisableHandleBrush)
    Q_PROPERTY(int    margin             READ margin             WRITE setMargin            )
    Q_PROPERTY(bool   handleIn           READ handleIn           WRITE setHandleIn          )
    Q_PROPERTY(qreal  offset             READ offset             WRITE setOffset            )

public:
    explicit SwitchButton(QWidget *parent = nullptr);

    void setOnGrooveBrush(const QBrush &onGrooveBrush);
    void setOnHandleBrush(const QBrush &onHandleBrush);
    void setOffGrooveBrush(const QBrush &offGrooveBrush);
    void setOffHandleBrush(const QBrush &offHandleBrush);
    void setDisableGrooveBrush(const QBrush &disableGrooveBrush);
    void setDisableHandleBrush(const QBrush &disableHandleBrush);
    void setMargin(int margin);

    QBrush onGrooveBrush() const;
    QBrush onHandleBrush() const;
    QBrush offGrooveBrush() const;
    QBrush offHandleBrush() const;
    QBrush disableGrooveBrush() const;
    QBrush disableHandleBrush() const;
    int margin() const;

    bool handleIn() const;
    void setHandleIn(bool handleIn);

    qreal offset() const;
    void setOffset(const qreal &offset);

    void setChecked(bool c);

private:
    void init();

private slots:
    void onThisBtnClicked();

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QBrush m_onGrooveBrush     ;
    QBrush m_onHandleBrush     ;
    QBrush m_offGrooveBrush    ;
    QBrush m_offHandleBrush    ;
    QBrush m_disableGrooveBrush;
    QBrush m_disableHandleBrush;
    int    m_margin = 4;
    bool   m_handleIn = true; // true-圆点比滑槽小，在滑槽内，false-圆点比滑槽大，在滑槽外

    qreal  m_offset = 0.0;
    QPropertyAnimation m_animation;
};

#endif // SWITCHBUTTON_H
