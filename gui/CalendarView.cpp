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
    reminder.accept(this);
}

void CalendarView::visit(const Event* event) {
    QTextCharFormat eventFormat, eventDeadlineFormat;
    eventFormat.setForeground(Qt::white);
    eventFormat.setBackground(Qt::blue);
    eventDeadlineFormat.setForeground(Qt::black);
    eventDeadlineFormat.setBackground(Qt::green);

    QDate eDate = event->getStartDate().date();
    while (eDate <= event->getEndDate().date()) {
        if(calendar->dateTextFormat(eDate).background().color() == Qt::yellow)
            calendar->setDateTextFormat(eDate, eventDeadlineFormat);
        else
            calendar->setDateTextFormat(eDate, eventFormat);
        eDate = eDate.addDays(1);
    }
}

void CalendarView::visit(const Deadline* deadline) {
    QTextCharFormat deadlineFormat, eventDeadlineFormat;
    deadlineFormat.setForeground(Qt::black);
    deadlineFormat.setBackground(Qt::yellow);
    eventDeadlineFormat.setForeground(Qt::black);
    eventDeadlineFormat.setBackground(Qt::green);

    QDate dDate = deadline->getDate().date();
    if(calendar->dateTextFormat(dDate).background().color() == Qt::blue)
        calendar->setDateTextFormat(dDate, eventDeadlineFormat);
    else
        calendar->setDateTextFormat(dDate, deadlineFormat);
}

void CalendarView::visit(const Memo* memo) {}

void CalendarView::highlightReminders(const ReminderList& list) {
    calendar->setDateTextFormat(QDate(), QTextCharFormat() );
    for(auto it=list.begin(); it!=list.end(); ++it) {
        highlight(**it);
    }
}

void CalendarView::removeHighlight(const QDate& date) {
    calendar->setDateTextFormat(date, QTextCharFormat());
}