#ifndef __student_information_h
#define __student_information_h

#include<vector>
#include<string>

namespace Config
{
    class StudentInformation
    {

        public:

            StudentInformation() : _extra_credits(0.0),_grade(0.0)
            {
            }

            const std::vector<float>& getAssignments() const;
            const std::vector<float>& getExams() const;
            const float& getExtraCredits() const;
            const std::string& getStudentName() const;
            const float& getGrade() const;    

            void addAssignmentMarks(const float& assignment_marks);
            void addExamMarks(const float& exam_marks);
            void addExtraCredits();
            void setStudentName(const std::string& student_name);
            void setGrade(const float& grade);
            
	    private:
           std::vector<float> _assignments;
           std::vector<float> _exams;
           float _extra_credits;
           std::string _student_name;
           float _grade;
	};
}

#endif
