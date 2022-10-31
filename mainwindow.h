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

private slots:
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void on_tabWidget_tabBarClicked(int index);

    void on_dateEdit_dateChanged(const QDate &date);


    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
