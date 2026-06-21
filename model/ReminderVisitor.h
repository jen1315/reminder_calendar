#ifndef REMINDERVISITOR_H
#define REMINDERVISITOR_H

class Event;
class Deadline;
class Memo;

class ReminderVisitor {
public:
    virtual void visit(Event *event) = 0;
    virtual void visit(Deadline *deadline) = 0;
    virtual void visit(Memo *memo) = 0;
};

#endif
