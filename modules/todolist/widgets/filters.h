#include <QMouseEvent>
#include <QResizeEvent>

class ClicFilter : public QObject
{
    Q_OBJECT
public:
    ClicFilter(std::function<void(QMouseEvent *)> m_handler) : handler(m_handler) {};

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *e = static_cast<QMouseEvent *>(event);
            if (e->button() == Qt::LeftButton) {
                handler(e);
                return true;
            } else
                return false;
        }
        return false;
    }

    std::function<void(QMouseEvent *)> handler;
};

class ResizeFilter : public QObject
{
    Q_OBJECT
public:
    ResizeFilter(std::function<void(QResizeEvent *)> m_handler) : handler(m_handler) {};

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::Resize) {
            QResizeEvent *e = static_cast<QResizeEvent *>(event);
            handler(e);
            return true;
        } else {
            return false;
        }
    }

    std::function<void(QResizeEvent *)> handler;
};

class HoverFilter : public QObject
{
    Q_OBJECT
public:
    HoverFilter(std::function<void(QEnterEvent *)> m_enterHandler, std::function<void(QEnterEvent *)> m_leaveHandler)
        : enterHandler(m_enterHandler), leaveHandler(m_leaveHandler) {};

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::Enter) {
            QEnterEvent *e = static_cast<QEnterEvent *>(event);
            enterHandler(e);
            return true;
        } else if (event->type() == QEvent::Leave) {
            QEnterEvent *e = static_cast<QEnterEvent *>(event);
            leaveHandler(e);
            return true;
        } else {
            return false;
        }
    }

    std::function<void(QEnterEvent *)> enterHandler;
    std::function<void(QEnterEvent *)> leaveHandler;
};