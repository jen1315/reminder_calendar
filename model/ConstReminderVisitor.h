#ifndef CONSTREMINDERVISITOR_H
#define CONSTREMINDERVISITOR_H

class Event;
class Deadline;
class Memo;

class ConstReminderVisitor {
public:
    virtual void visit(const Event *event) = 0;
    virtual void visit(const Deadline *deadline) = 0;
    virtual void visit(const Memo *memo) = 0;
};

#endif