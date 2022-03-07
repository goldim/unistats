#pragma once

#include <string>
#include <map>

// Qt
#include <QtQml>
#include <QVariantMap>

// unistatscore
#include <unistatscore/Config.h>
#include <unistatscore/System.h>

class CategoryState
{
public:
    virtual Criterion *getCriterion() = 0;

    virtual ~CategoryState() = default;
};

class TermState : public CategoryState
{
public:
    TermState() = default;

    virtual Criterion *getCriterion() { return new TermCriterion(); }

    virtual ~TermState(){}
};

class YearState : public CategoryState
{
public:
    YearState() = default;

    virtual Criterion *getCriterion() { return new YearCriterion(); }

    virtual ~YearState(){}
};

class SubjectState : public CategoryState
{
public:
    SubjectState() = default;

    virtual Criterion *getCriterion() { return new SubjectCriterion(); }

    virtual ~SubjectState(){}
};

class TeacherState : public CategoryState
{
public:
    TeacherState() = default;

    virtual Criterion *getCriterion() { return new TeacherCriterion(); }

    virtual ~TeacherState(){}
};

class GroupState : public CategoryState
{
public:
    GroupState() = default;

    virtual Criterion *getCriterion() { return new GroupCriterion(); }

    virtual ~GroupState(){}
};

class KursState : public CategoryState
{
public:
    KursState() = default;

    virtual Criterion *getCriterion() { return new KursCriterion(); }

    virtual ~KursState(){}
};

class FacultyState : public CategoryState
{
public:
    FacultyState() = default;

    virtual Criterion *getCriterion() { return new FacultyCriterion(); }

    virtual ~FacultyState(){}
};

class SpecialtyState : public CategoryState
{
public:
    SpecialtyState() = default;

    virtual Criterion *getCriterion() { return new SpecialtyCriterion(); }

    virtual ~SpecialtyState(){}
};

class SpecializationState : public CategoryState
{
public:
    SpecializationState() = default;

    virtual Criterion *getCriterion() { return new SpecializationCriterion(); }

    virtual ~SpecializationState(){}
};

class YearStartState : public CategoryState
{
public:
    YearStartState() = default;

    virtual Criterion *getCriterion() { return new YearStartCriterion(); }

    virtual ~YearStartState(){}
};

class ExamOrderGroupState : public CategoryState
{
public:
    ExamOrderGroupState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderGroupCriterion(_order); }

    virtual ~ExamOrderGroupState(){}
private:
    int _order;
};

class ExamOrderYearState : public CategoryState
{
public:
    ExamOrderYearState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderYearCriterion(_order); }

    virtual ~ExamOrderYearState(){}
private:
    int _order;
};

class ExamOrderTermState : public CategoryState
{
public:
    ExamOrderTermState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderTermCriterion(_order); }

    virtual ~ExamOrderTermState(){}
private:
    int _order;
};

class ExamOrderKursState : public CategoryState
{
public:
    ExamOrderKursState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderKursCriterion(_order); }

    virtual ~ExamOrderKursState(){}
private:
    int _order;
};

class ExamOrderFacultyState : public CategoryState
{
public:
    ExamOrderFacultyState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderFacultyCriterion(_order); }

    virtual ~ExamOrderFacultyState(){}
private:
    int _order;
};

class ExamOrderSpecialtyState : public CategoryState
{
public:
    ExamOrderSpecialtyState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderSpeacialtyCriterion(_order); }

    virtual ~ExamOrderSpecialtyState(){}
private:
    int _order;
};

class ExamOrderSpecializationState : public CategoryState
{
public:
    ExamOrderSpecializationState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderSpecializationCriterion(_order); }

    virtual ~ExamOrderSpecializationState(){}
private:
    int _order;
};

class ExamOrderYearStartState : public CategoryState
{
public:
    ExamOrderYearStartState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderYearStartCriterion(_order); }

    virtual ~ExamOrderYearStartState(){}
private:
    int _order;
};

class ExamOrderSubjectState : public CategoryState
{
public:
    ExamOrderSubjectState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderSubjectCriterion(_order); }

    virtual ~ExamOrderSubjectState(){}
private:
    int _order;
};

class ExamOrderTeacherState : public CategoryState
{
public:
    ExamOrderTeacherState(int order):_order(order){}

    virtual Criterion *getCriterion() { return new ExamOrderTeacherCriterion(_order); }

    virtual ~ExamOrderTeacherState(){}
private:
    int _order;
};



