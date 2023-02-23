#include "gtest/gtest.h"

#include <vector>

#include "../Include/User.hpp"
#include "../Include/Bills.hpp"
#include "../Include/Loan.hpp"

struct ObligationsUnderTests : public ::testing::Test{
    User person{};
    

    
};

TEST_F(ObligationsUnderTests, AddingObligations)
{   
    int before = person.getObligations().size();
    Date date(11,10,2000);
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date));
    ASSERT_EQ(before+1, person.getObligations().size());
}

TEST_F(ObligationsUnderTests, PrintingObligations)
{   
    Date date1(24,02,2023);
    Date date2(28,02,2023);
    Date date3(31,01,2023);
    Date date4(25,04,2023);
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date1));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date2));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date3));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date4));
    person.addObligation(std::make_shared<Loan>("dasdasdas", 2000,date1, 11));
    std::cout<<person.printIncomingObligations(10);
}

TEST_F(ObligationsUnderTests, PrintIncomingObligations)
{   
    Date date1(24,02,2023);
    Date date2(28,02,2023);
    Date date3(31,01,2023);
    Date date4(25,04,2023);
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date1));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date2));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date3));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date4));
    person.addObligation(std::make_shared<Loan>("dasdasdas", 2000,date1, 11));
    std::cout<<person.printIncomingObligations();
}

TEST_F(ObligationsUnderTests, PrintIncomingObligations2)
{   
    Date date1(24,02,2023);
    Date date2(28,02,2023);
    Date date3(31,01,2023);
    Date date4(25,04,2023);
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date1));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date2));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date3));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date4));
    person.addObligation(std::make_shared<Loan>("dasdasdas", 2000,date1, 11));
    std::cout<<person.printOverdueObligations();
}