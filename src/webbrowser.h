#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWidget>
#include <QWebSettings>

namespace Ui {
class WebBrowser;
}

class WebBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit WebBrowser(QWidget *parent = 0);
    ~WebBrowser();

private:
    Ui::WebBrowser *ui;
};

#endif // WEBBROWSER_H
