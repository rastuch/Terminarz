#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>
class Task
{
private:
    int id;
    QString title;
    QString description;
    QString date;
    QString time;
    QString type;

public:
    Task();
    Task(int id, QString title, QString description, QString date, QString time, QString type);
    void setTask(int id, QString title, QString description, QString date, QString time, QString type);
    int getId() {return id;}
    QString getTitle() {return title;}
    QString getDescription() {return description;}
    QString getDate() {return this->date;}
    QString getTime() {return time;}
    QString getType() {return type;}
    void setId(int id) { this->id = id; }
    void setTitle(QString title) { this->title = title; }
    void setDescription(QString description) { this->description = description; }
    void setDate(QString date) { this->date = date; }
    void setTime(QString time) { this->time = time; }
    void setType(QString type) { this->type = type; }
    QDate getQDate(){
        QDate Date = QDate::fromString(date,"yyyy-MM-dd");
        return Date;
    }
};

#endif // TASK_H
