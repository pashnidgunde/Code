#include "student_information.h"

namespace Config
{
    const std::vector<float>& StudentInformation::getAssignments() const
    {
        return _assignments;
    }

    const std::vector<float>& StudentInformation::getExams() const
    {
        return _exams;
    }

    const float& StudentInformation::getExtraCredits() const
    {
        return _extra_credits;
    }

    const std::string& StudentInformation::getStudentName() const
    {
        return _student_name;
    }    

    void StudentInformation::addAssignmentMarks(const float& assignment_marks)
    {
        _assignments.push_back(assignment_marks);
    }

    void StudentInformation::addExamMarks(const float& exam_marks)
    {
        _exams.push_back(exam_marks);
    }

    void StudentInformation::addExtraCredits()
    {
        _extra_credits++;
    }

    void StudentInformation::setStudentName(const std::string& student_name)
    {
        _student_name = student_name;
    }

    void StudentInformation::setGrade(const float& grade)
    {
        _grade = (grade > 100) ? 100.00 : grade;
    }

    const float& StudentInformation::getGrade() const
    {
        return _grade;
    }
}

