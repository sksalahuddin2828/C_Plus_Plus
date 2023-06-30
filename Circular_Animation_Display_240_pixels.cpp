#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTimer>

class RotatingPatternWidget : public QWidget {
public:
    RotatingPatternWidget(QWidget *parent = nullptr) : QWidget(parent) {
        pi = 3.14159265358979323846;
        circle = pi * 2;
        length = 12;
        halfLength = length / 2;
        cx = 115;
        cy = 115;
        w = 90.0;
        h = 90.0;
        step = 0.0;

        setWindowTitle("Rotating Pattern");
        resize(240, 240);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &RotatingPatternWidget::updateAnimation);
        timer->start(100);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Clear the background
        painter.fillRect(rect(), Qt::black);

        for (int i = 0; i < length; i++) {
            double a = (i / static_cast<double>(length)) * circle;
            double x = cx + qRound(cos(a) * w);
            double y = cy + qRound(sin(a) * h);
            drawCircle(painter, x, y, Qt::white);

            if (i < halfLength) {
                continue;
            }

            double rangeVal = cos(a + step);
            x = cx + qRound(cos(a) * (w - 1) * rangeVal);
            y = cy + qRound(sin(a) * (h - 1) * rangeVal);
            drawCircle(painter, x, y, Qt::white);
        }
    }

private:
    void updateAnimation() {
        step -= 0.09;
        update();
    }

    void drawCircle(QPainter &painter, int x, int y, const QColor &color) {
        painter.setPen(color);
        painter.setBrush(color);
        painter.drawEllipse(x - 5, y - 5, 10, 10);
    }

private:
    double pi;
    double circle;
    int length;
    int halfLength;
    double cx;
    double cy;
    double w;
    double h;
    double step;
    QTimer *timer;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    RotatingPatternWidget widget;
    widget.show();

    return app.exec();
}
