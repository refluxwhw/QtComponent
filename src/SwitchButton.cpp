#include "SwitchButton.h"
#include <QPainter>
#include <QDebug>

SwitchButton::SwitchButton(QWidget *parent)
    : QPushButton(parent)
{
    init();
}

void SwitchButton::init()
{
    m_onGrooveBrush      = QBrush(Qt::green);
    m_onHandleBrush      = QBrush(Qt::white);
    m_offGrooveBrush     = QBrush(Qt::gray);
    m_offHandleBrush     = QBrush(Qt::white);
    m_disableGrooveBrush = QBrush(Qt::lightGray);
    m_disableHandleBrush = QBrush(QColor(220,220,220));
    setCheckable(true);

    m_animation.setTargetObject(this);
    m_animation.setPropertyName("offset");
    m_animation.setDuration(200);
    connect(this, &SwitchButton::clicked, this, &SwitchButton::onThisBtnClicked);

    m_offset = isChecked() ? 1.0 : 0.0;
}

void SwitchButton::onThisBtnClicked()
{
    m_animation.stop();
    if (isChecked()) {
        m_animation.setStartValue(0.0);
        m_animation.setEndValue(1.0);
    } else {
        m_animation.setStartValue(1.0);
        m_animation.setEndValue(0.0);
    }
    m_animation.start();
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int w = width();
    int h = height();
    int s = qMin(w, h); // 短边
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing, true);

    QBrush groove;
    QBrush handle;
    if (isEnabled()) {
        if (isChecked()) {
            groove = m_onGrooveBrush;
            handle = m_onHandleBrush;
        } else {
            groove = m_offGrooveBrush;
            handle = m_offHandleBrush;
        }
    } else {
        groove = m_disableGrooveBrush;
        handle = m_disableHandleBrush;
    }

    QRectF rect;
    if (m_handleIn) {
        rect = this->rect();
    } else {
        rect = QRectF(m_margin, m_margin, w-2*m_margin, h-2*m_margin);
    }
    qreal r = qMin(rect.width(), rect.height())/2.0; // 滑槽圆角半径
    p.setBrush(groove);
    p.drawRoundedRect(rect, r, r);

    QPointF startPos(s/2.0, s/2.0);
    QPointF endPos(w-s/2.0, h-s/2.0);
    // 滑块中点
    QPointF pos(startPos.rx()+m_offset*(endPos.rx()-startPos.rx()),
                startPos.ry()+m_offset*(endPos.ry()-startPos.ry()));
    r = qMin(w, h)/2.0; // 滑块半径
    if (m_handleIn) {
        r -= m_margin;
    }

    p.setBrush(handle);
    p.drawEllipse(pos, r, r);

    QFont font = this->font();
    font.setPixelSize((int)(r*1.2));
    p.setFont(font);
    p.setPen(groove.color());
    p.drawText(QRectF(pos.rx()-r, pos.ry()-r, 2*r, 2*r), Qt::AlignCenter,
               isChecked() ? QStringLiteral("开") : QStringLiteral("关"));
}

qreal SwitchButton::offset() const
{
    return m_offset;
}

void SwitchButton::setOffset(const qreal &offset)
{
    m_offset = offset;
    update();
}

void SwitchButton::setChecked(bool c)
{
    m_offset = c ? 1.0 : 0.0;
    QPushButton::setChecked(c);
}

bool SwitchButton::handleIn() const
{
    return m_handleIn;
}

void SwitchButton::setHandleIn(bool handleIn)
{
    m_handleIn = handleIn;
    update();
}

int SwitchButton::margin() const
{
    return m_margin;
}

QBrush SwitchButton::disableHandleBrush() const
{
    return m_disableHandleBrush;
}

QBrush SwitchButton::disableGrooveBrush() const
{
    return m_disableGrooveBrush;
}

QBrush SwitchButton::offHandleBrush() const
{
    return m_offHandleBrush;
}

QBrush SwitchButton::offGrooveBrush() const
{
    return m_offGrooveBrush;
}

QBrush SwitchButton::onHandleBrush() const
{
    return m_onHandleBrush;
}

QBrush SwitchButton::onGrooveBrush() const
{
    return m_onGrooveBrush;
}

void SwitchButton::setMargin(int margin)
{
    m_margin = margin;
    update();
}

void SwitchButton::setDisableHandleBrush(const QBrush &disableHandleBrush)
{
    m_disableHandleBrush = disableHandleBrush;
    update();
}

void SwitchButton::setDisableGrooveBrush(const QBrush &disableGrooveBrush)
{
    m_disableGrooveBrush = disableGrooveBrush;
    update();
}

void SwitchButton::setOffHandleBrush(const QBrush &offHandleBrush)
{
    m_offHandleBrush = offHandleBrush;
    update();
}

void SwitchButton::setOffGrooveBrush(const QBrush &offGrooveBrush)
{
    m_offGrooveBrush = offGrooveBrush;
    update();
}

void SwitchButton::setOnHandleBrush(const QBrush &onHandleBrush)
{
    m_onHandleBrush = onHandleBrush;
    update();
}

void SwitchButton::setOnGrooveBrush(const QBrush &onGrooveBrush)
{
    m_onGrooveBrush = onGrooveBrush;
    update();
}
