#include "webbrowser.h"
#include "ui_webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebBrowser)
{
    ui->setupUi(this);
}

WebBrowser::~WebBrowser()
{
    delete ui;
}
