#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QCalendarWidget>
#include "../model/ReminderList.h"
#include "../model/ConstReminderVisitor.h"

class CalendarView : public QWidget, public ConstReminderVisitor {
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent=nullptr);
    void highlight(AbstractReminder& reminder);
    void removeHighlight(const QDate& date);
    void highlightReminders(const ReminderList& list);

    void visit(const Event* event);
    void visit(const Deadline* deadline);
    void visit(const Memo* memo);

private:
    QCalendarWidget *calendar;
    
signals:
    void dateSelected(QDate date);
};

#endif
