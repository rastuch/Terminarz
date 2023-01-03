#ifndef TASK_H
#define TASK_H
#include <QDate>
#include <QString>

/*!
 * @class Task
 * @brief Klasa odpowiadająca za zadanie.
 *
 * W tej klasie zaimplementowano obiekt zadania, który zawiera pola takie jak identyfikator, tytuł, opis, data, czas i rodzaj.
 * Zawiera także metody do ustawiania i pobierania wartości tych pól oraz konwersję formatu daty.
 */

class Task
{
private:
    int id; /**< Identyfikator */
    QString title; /**< Tytuł */
    QString description; /**< Opis */
    QString date; /**< Data */
    QString time; /**< Czas */
    QString type; /**< Rodzaj */

public:
    Task();
    Task(int id, QString title, QString description, QString date, QString time, QString type);
    void setTask(int id, QString title, QString description, QString date, QString time, QString type);
    int getId() {return id;} /**@return zwraca identyfikator*/
    QString getTitle() {return title;} /**@return zwraca tytuł*/
    QString getDescription() {return description;} /**@return zwraca opis*/
    QString getDate() {return this->date;} /**@return zwraca date*/
    QString getTime() {return time;} /**@return zwraca czas*/
    QString getType() {return type;} /*! @return zwraca rodzaj*/
    void setId(int id) { this->id = id; } /**@brief Konwersja formatu daty */
    void setTitle(QString title) { this->title = title; } /**@brief wartość argumentu id przypisywana jest do pola id w obiekcie */
    void setDescription(QString description) { this->description = description; }
    void setDate(QString date) { this->date = date; }
    void setTime(QString time) { this->time = time; }
    void setType(QString type) { this->type = type; }
    QDate getQDate(){
        QDate Date = QDate::fromString(date,"yyyy-MM-dd"); /**@brief Konwersja formatu daty */
        return Date;
    }
};

#endif // TASK_H
