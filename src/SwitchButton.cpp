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
    m_backgroundColorOn  = Qt::white;
    m_sliderColorOn      = Qt::darkGreen;
    m_backgroundColorOff = Qt::lightGray;
    m_sliderColorOff     = QColor(100,100,100);
    m_backgroundColorDis = Qt::lightGray;
    m_sliderColorDis     = QColor(220,220,220);
    setCheckable(true);

    m_animation.setTargetObject(this);
    m_animation.setPropertyName("offset");
    m_animation.setDuration(200);
    connect(this, &SwitchButton::clicked, this, &SwitchButton::onThisBtnClicked);
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawBackground(p);
    drawSlider(p);
}

void SwitchButton::drawBackground(QPainter &p)
{
    p.save();
    p.setPen(Qt::NoPen);

    if (isEnabled()) {
        if (isChecked()) {
            p.setBrush(m_backgroundColorOn);
        } else {
            p.setBrush(m_backgroundColorOff);
        }
    } else {
        p.setBrush(m_backgroundColorDis);
    }

    QRectF rect = this->rect();
    qreal r = 0.0;
    switch (m_sliderType) {
        case SliderType::kRect:
            r = m_radius;
            break;

        case SliderType::kCircleOut:
            rect = QRectF(m_margin, m_margin,
                          rect.width() - 2*m_margin,
                          rect.height() - 2*m_margin);
            r = qMin(rect.width(), rect.height()) / 2.0;
            break;

        case SliderType::kCircleIn:
            r = qMin(rect.width(), rect.height()) / 2.0;
            break;
    }

    p.drawRoundedRect(rect, r, r);
    p.restore();
}

void SwitchButton::drawSlider(QPainter &p)
{
    p.save();

    p.setPen(Qt::NoPen);
    if (isEnabled()) {
        if (isChecked()) {
            p.setBrush(m_sliderColorOn);
        } else {
            p.setBrush(m_sliderColorOff);
        }
    } else {
        p.setBrush(m_sliderColorDis);
    }

    qreal  w = width();
    qreal  h = height();
    qreal  s = qMin(w, h);
    QPointF startPos(s/2.0, s/2.0);
    QPointF endPos(w-s/2.0, h-s/2.0);
    qreal dtaX = endPos.x() - startPos.x();
    qreal dtaY = endPos.y() - startPos.y();

    QPointF center;
    if (isChecked()) {
        center = QPointF(startPos.x() + m_offset * dtaX,
                         startPos.y() + m_offset * dtaY);
    } else {
        center = QPointF(endPos.x() - m_offset * dtaX,
                         endPos.y() - m_offset * dtaY);
    }

    qreal r = 0.0;
    QRectF rect;
    switch (m_sliderType) {
        case SliderType::kRect:
            s -= 2*m_margin;
            r = m_radius;
            break;

        case SliderType::kCircleOut:
            r = s / 2.0;
            break;

        case SliderType::kCircleIn: {
            s -= 2*m_margin;
            r = s / 2.0;
            break;
        }
    }
    rect = QRectF(center.x()-s/2.0, center.y()-s/2.0, s, s);
    p.drawRoundedRect(rect, r, r);
    p.restore();

    drawText(p, rect);
}

void SwitchButton::drawText(QPainter &p, QRectF &rect)
{
    p.save();
    QFont font = this->font();
    font.setPixelSize((int)(rect.height()/1.5));
    p.setFont(font);
    p.setPen(isChecked() ? m_backgroundColorOn : m_backgroundColorOff);
    p.drawText(rect, Qt::AlignCenter,
               isChecked() ? QStringLiteral("开") : QStringLiteral("关"));
    p.restore();
}

void SwitchButton::onThisBtnClicked()
{
    m_animation.stop();
    m_animation.setStartValue(0.0);
    m_animation.setEndValue(1.0);
    m_animation.start();
}

QColor SwitchButton::getSliderColorDis() const
{
    return m_sliderColorDis;
}

void SwitchButton::setSliderColorDis(const QColor &sliderColorDis)
{
    m_sliderColorDis = sliderColorDis;
    update();
}

QColor SwitchButton::getSliderColorOff() const
{
    return m_sliderColorOff;
}

void SwitchButton::setSliderColorOff(const QColor &sliderColorOff)
{
    m_sliderColorOff = sliderColorOff;
    update();
}

QColor SwitchButton::getSliderColorOn() const
{
    return m_sliderColorOn;
}

void SwitchButton::setSliderColorOn(const QColor &sliderColorOn)
{
    m_sliderColorOn = sliderColorOn;
    update();
}

QColor SwitchButton::getBackgroundColorDis() const
{
    return m_backgroundColorDis;
}

void SwitchButton::setBackgroundColorDis(const QColor &backgroundColorDis)
{
    m_backgroundColorDis = backgroundColorDis;
    update();
}

QColor SwitchButton::getBackgroundColorOff() const
{
    return m_backgroundColorOff;
}

void SwitchButton::setBackgroundColorOff(const QColor &backgroundColorOff)
{
    m_backgroundColorOff = backgroundColorOff;
    update();
}

QColor SwitchButton::getBackgroundColorOn() const
{
    return m_backgroundColorOn;
}

void SwitchButton::setBackgroundColorOn(const QColor &backgroundColorOn)
{
    m_backgroundColorOn = backgroundColorOn;
    update();
}

int SwitchButton::getRadius() const
{
    return m_radius;
}

void SwitchButton::setRadius(int radius)
{
    m_radius = radius;
    update();
}

int SwitchButton::getMargin() const
{
    return m_margin;
}

void SwitchButton::setMargin(int margin)
{
    m_margin = margin;
    update();
}

qreal SwitchButton::getOffset() const
{
    return m_offset;
}

void SwitchButton::setOffset(const qreal &offset)
{
    m_offset = offset;
    update();
}

int SwitchButton::getSliderType() const
{
    return (int)m_sliderType;
}

void SwitchButton::setSliderType(int type)
{
    m_sliderType = (SliderType)type;
    update();
}
