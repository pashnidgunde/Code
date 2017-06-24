#include "UnitTest++/UnitTest++.h"

#include "../source/grade_calculator.h"

SUITE(GradeCalculatorSuite)
{
    TEST(TestSally)
    {
        Config::WeightageInfo weightages;
        weightages.setAssignmentWeightage(10.1);
        weightages.setExamWeightage(89.9);
        weightages.setExtraCreditPoints(2);

        Calculator::GradeCalculator calculator(weightages);
        std::vector<float> assignments = { 85,88,92 };
        std::vector<float> exams = {91};
        int extra_credits = 1;

        CHECK_CLOSE(90.9327f,calculator.calculate_grade(assignments,exams,extra_credits),0.01);

    }


    TEST(TestSallyNoExams)
    {
        Config::WeightageInfo weightages("Prashant",10.1,89.9,2);
        Calculator::GradeCalculator calculator(weightages);
        std::vector<float> assignments = { 85,88,92 };
        std::vector<float> exams;
        int extra_credits = 1;

        CHECK_CLOSE(90.33f,calculator.calculate_grade(assignments,exams,extra_credits),0.01);

    }

    TEST(TestSallyNoExtraCredits)
    {
        Config::WeightageInfo weightages("Prashant",10.1,89.9,2);
        Calculator::GradeCalculator calculator(weightages);
        std::vector<float> assignments = { 85,88,92 };
        std::vector<float> exams = {91};
        int extra_credits = 0;

        CHECK_CLOSE(90.73f,calculator.calculate_grade(assignments,exams,extra_credits),0.01);

    }
}


int main(int,const char*[])
{
    return UnitTest::RunAllTests();
}



