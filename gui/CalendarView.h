#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

public CalendarView : public QWidget {
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent=nullptr);

private:
    QCalendarWidget *calendar;
    
};

#endif
