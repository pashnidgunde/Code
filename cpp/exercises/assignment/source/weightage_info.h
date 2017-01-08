#ifndef __weightage_config_h
#define __weightage_config_h

#include <string>
namespace Config
{
    class WeightageInfo
    {
        public:

            WeightageInfo(const std::string& teacher
                          , const float& assignment_weightage
                          , const float& exam_weightage
                          , const float& extra_credit_points)
                        :_teacher_name(teacher)
                         , _assigment_weightage(assignment_weightage)
                         , _exam_weightage(exam_weightage)
                         , _extra_credit_points(extra_credit_points)
            {
            }

            WeightageInfo() :_assigment_weightage(0.0)
                            ,_exam_weightage(0.0)
                            ,_extra_credit_points(0.0)
            {
            }

            float getAssignmentWeightage() const
            {
                return _assigment_weightage;
            }
            
            float getExamWeightage() const
            {
                return _exam_weightage;
            }

            float getExtraCreditPoints() const
            {
                return _extra_credit_points;
            }
            void setAssignmentWeightage(const float& assigment_weightage)
            {
                _assigment_weightage = assigment_weightage;
            }
            void setExamWeightage(const float& exam_weightage)
            {
                _exam_weightage = exam_weightage;
            }
            void setExtraCreditPoints(const float& extra_credits)
            {
                _extra_credit_points = extra_credits;
            }
            void setTeacherName(const std::string& teacher_name)
            {
                _teacher_name = teacher_name;
            }
            std::string getTeacherName() const
            {
                return _teacher_name;
            }
            
        private:
            std::string _teacher_name;
            float _assigment_weightage;
            float _exam_weightage;
            float _extra_credit_points;

    };

}
#endif

