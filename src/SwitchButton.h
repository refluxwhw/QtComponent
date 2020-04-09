#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QPainter>

class SwitchButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColorOn  READ getBackgroundColorOn  WRITE setBackgroundColorOn )
    Q_PROPERTY(QColor backgroundColorOff READ getBackgroundColorOff WRITE setBackgroundColorOff)
    Q_PROPERTY(QColor backgroundColorDis READ getBackgroundColorDis WRITE setBackgroundColorDis)
    Q_PROPERTY(QColor sliderColorOn      READ getSliderColorOn      WRITE setSliderColorOn     )
    Q_PROPERTY(QColor sliderColorOff     READ getSliderColorOff     WRITE setSliderColorOff    )
    Q_PROPERTY(QColor sliderColorDis     READ getSliderColorDis     WRITE setSliderColorDis    )

    Q_PROPERTY(int    sliderType         READ getSliderType         WRITE setSliderType        )
    Q_PROPERTY(int    margin             READ getMargin             WRITE setMargin            )
    Q_PROPERTY(int    radius             READ getRadius             WRITE setRadius            )
    Q_PROPERTY(qreal  offset             READ getOffset             WRITE setOffset            )

public:
    enum class SliderType {
        kRect = 0,
        kCircleIn,
        kCircleOut
    };

    explicit SwitchButton(QWidget *parent = nullptr);

    qreal getOffset() const;
    void setOffset(const qreal &offset);
    int getSliderType() const;
    void setSliderType(int type);
    int getMargin() const;
    void setMargin(int margin);
    int getRadius() const;
    void setRadius(int radius);

    QColor getBackgroundColorOn() const;
    void setBackgroundColorOn(const QColor &backgroundColorOn);
    QColor getBackgroundColorOff() const;
    void setBackgroundColorOff(const QColor &backgroundColorOff);
    QColor getBackgroundColorDis() const;
    void setBackgroundColorDis(const QColor &backgroundColorDis);
    QColor getSliderColorOn() const;
    void setSliderColorOn(const QColor &sliderColorOn);
    QColor getSliderColorOff() const;
    void setSliderColorOff(const QColor &sliderColorOff);
    QColor getSliderColorDis() const;
    void setSliderColorDis(const QColor &sliderColorDis);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void init();
    void drawBackground(QPainter& p);
    void drawSlider(QPainter& p);
    void drawText(QPainter& p, QRectF& rect);

private slots:
    void onThisBtnClicked();

private:
    QColor m_backgroundColorOn ;
    QColor m_backgroundColorOff;
    QColor m_backgroundColorDis;    // 禁用颜色
    QColor m_sliderColorOn     ;
    QColor m_sliderColorOff    ;
    QColor m_sliderColorDis    ;

    SliderType m_sliderType = SliderType::kRect;
    int        m_margin = 3;
    qreal      m_offset = 1.0;
    int        m_radius = 9;

    QPropertyAnimation m_animation;
};

#endif // SWITCHBUTTON_H
