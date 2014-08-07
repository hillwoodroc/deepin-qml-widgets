#include "plugins/dwindow.h"
#include <QCursor>
#include <QGuiApplication>
#include <QX11Info>

#include <cstdio>
#include <cstring>

DOverrideWindow::DOverrideWindow(DWindow *parent)
    :DWindow(parent)
{
    QSurfaceFormat sformat;
    sformat.setAlphaBufferSize(8);
    this->setFormat(sformat);
    this->setClearBeforeRendering(true);

    this->setFlags(Qt::Popup|Qt::FramelessWindowHint);
}

DOverrideWindow::~DOverrideWindow()
{
}

DWindow::DWindow(QQuickWindow *parent)
    :QQuickWindow(parent)
{
    _conn = QX11Info::connection();

    QSurfaceFormat sformat;
    sformat.setAlphaBufferSize(8);
    this->setFormat(sformat);
    this->setClearBeforeRendering(true);
    QObject::connect(qApp, SIGNAL(focusWindowChanged(QWindow*)), this, SLOT(focusChanged(QWindow *)));
}

DWindow::~DWindow()
{
}

int DWindow::shadowWidth()
{
    return _shadowWidth;
}

void DWindow::setShadowWidth(int shadowWidth)
{
    _shadowWidth = shadowWidth;
    char shadowWidthStr[8];
    sprintf(shadowWidthStr, "%d", shadowWidth);

    xcb_intern_atom_cookie_t cookie;
    xcb_intern_atom_reply_t *reply;

    cookie = xcb_intern_atom(_conn, false, strlen("DEEPIN_WINDOW_SHADOW"),
                             "DEEPIN_WINDOW_SHADOW");
    if ((reply = xcb_intern_atom_reply(_conn, cookie, NULL))) {

        xcb_change_property_checked(_conn, XCB_PROP_MODE_REPLACE, this->winId(),
                                    reply->atom, XCB_ATOM_STRING, 8, strlen(shadowWidthStr),
                                    shadowWidthStr);

        free(reply);
    }
}

QPoint DWindow::getCursorPos()
{
    return QCursor::pos();
}

void DWindow::focusChanged(QWindow *win)
{
    Q_EMIT windowFocusChanged(win);
}

void DWindow::mousePressEvent(QMouseEvent *ev){
    //qDebug() << "Event:" << ev->x() << "," << ev->y();
    QPointF p = QPointF(ev->x(), ev->y());
    DWindow::mousePressed(p);
    QQuickWindow::mousePressEvent(ev);
}
