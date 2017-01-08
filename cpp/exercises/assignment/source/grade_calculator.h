#ifndef __grade_calculator_h__
#define __grade_calculator_h__

#include "weightage_info.h"
#include <vector>

namespace Calculator
{
    class GradeCalculator
    {
        public:

            GradeCalculator(const Config::WeightageInfo& config) : _config(config)
            {
            	
			}
            
            float calculate_grade(const std::vector<float> & assignments,
								  const std::vector<float>& exams,
								  const int& extra_credits)
            {
                float weight = 0.0;
                float assignment_grade = 0.0;
                float exam_grade = 0.0;

                for(float assignment : assignments )
                {
                    assignment_grade+= assignment;
                    weight++;
                }

                assignment_grade = assignment_grade / weight;
                assignment_grade += _config.getExtraCreditPoints() * extra_credits;

                if (exams.size())
                {
                    assignment_grade = ( assignment_grade * _config.getAssignmentWeightage() / 100 );	
                }


                for(float exam : exams)
                {
                    exam_grade +=  exam * _config.getExamWeightage()/100 ; 
                }

                return assignment_grade + exam_grade;

            }
            
         private:
                const Config::WeightageInfo& _config;
    };

} // end of namespace

#endif
