#ifndef REMINDERVISITOR_H
#define REMINDERVISITOR_H

class Event;
class Deadline;
class Memo;

class ReminderVisitor {
public:
    virtual void visit(const Event *event) = 0;
    virtual void visit(const Deadline *deadline) = 0;
    virtual void visit(const Memo *memo) = 0;

    virtual void visitEdit(const Event *event) = 0;
    virtual void visitEdit(const Deadline *deadline) = 0;
    virtual void visitEdit(const Memo *memo) = 0;
};

#endif
