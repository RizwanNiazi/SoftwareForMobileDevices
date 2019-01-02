#include "mainwindow.h"
#include <QApplication>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPalette p = QApplication::palette();
    p.setColor( QPalette::Text, Qt::red );
    p.setColor( QPalette::WindowText, Qt::red );
    p.setColor( QPalette::ButtonText, Qt::red );
    p.setColor( QPalette::BrightText, Qt::red );
    QApplication::setPalette( p );
    w.show();

    return a.exec();
}
