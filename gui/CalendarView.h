#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QCalendarWidget>
#include "../model/ReminderList.h"

class CalendarView : public QWidget {
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent=nullptr);
    void highlight(AbstractReminder& reminder);
    void removeHighlight(const QDate& date);
    void highlightReminders(const ReminderList& list);

private:
    QCalendarWidget *calendar;
    
signals:
    void dateSelected(QDate date);
};

#endif
