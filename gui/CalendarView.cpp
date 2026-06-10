#include "CalendarView.h"

#include <QHBoxLayout>
#include <QTextCharFormat>
#include "../model/Event.h"
#include "../model/Deadline.h"

CalendarView::CalendarView(QWidget *parent) : QWidget(parent) {
    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, SIGNAL(activated(QDate)), this, SIGNAL(dateSelected(QDate)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(calendar);
    setLayout(layout);
}

void CalendarView::highlight(AbstractReminder& reminder) {
    QTextCharFormat eventFormat, deadlineFormat, eventDeadlineFormat;
    eventFormat.setBackground(Qt::blue);
    deadlineFormat.setForeground(Qt::black);
    deadlineFormat.setBackground(Qt::yellow);
    eventDeadlineFormat.setBackground(Qt::green);
    if(dynamic_cast<Event*>(&reminder)) {
            QDate eDate = static_cast<Event*>(&reminder)->getStartDate().date();
            while (eDate<=static_cast<Event*>(&reminder)->getEndDate().date()) {
                calendar->setDateTextFormat(eDate, eventFormat);
                eDate = eDate.addDays(1);
            }
    }
    if(dynamic_cast<Deadline*>(&reminder)) {
        QDate dDate = static_cast<Deadline*>(&reminder)->getDate().date();
        if(calendar->dateTextFormat(dDate).background().color() == Qt::blue)
            calendar->setDateTextFormat(dDate, eventDeadlineFormat);
        else
            calendar->setDateTextFormat(dDate, deadlineFormat);
    } 
}

void CalendarView::removeHighlight(const QDate& date) {
    calendar->setDateTextFormat(date, QTextCharFormat());
}

void CalendarView::highlightReminders(const ReminderList& list) {
    calendar->setDateTextFormat(QDate(), QTextCharFormat() );
    for(auto it=list.begin(); it!=list.end(); ++it) {
        highlight(**it);
    }
}