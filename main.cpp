#include "includes/widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    task_manager::Widget w;
    w.show();
    return a.exec();
}