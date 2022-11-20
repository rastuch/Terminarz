#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void receiveSignal();
    void receiveRefreshSingal();

private slots:
    void on_calendarWidget_selectionChanged();

   void showTime();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
