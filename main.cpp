#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); /*! @brief tworzy obiekt „aplikacja” */
    MainWindow w; /*! @brief tworzy główny obiekt okna */
    w.show(); /*! @brief pokazuje główne okno */
    return a.exec(); /*! @brief uruchamia pętlę zdarzeń aplikacji */
}
