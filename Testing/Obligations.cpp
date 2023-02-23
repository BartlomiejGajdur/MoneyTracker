#include "gtest/gtest.h"

#include <vector>

#include "../Include/User.hpp"
#include "../Include/Bills.hpp"
#include "../Include/Loan.hpp"

struct ObligationsUnderTests : public ::testing::Test{
    User person{};
    
    void addObligations(){
        person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,Date{24,02,2023}));
        person.addObligation(std::make_shared<Bills>(BillType::Water, 33,Date{28,02,2023}));
        person.addObligation(std::make_shared<Bills>(BillType::Gas, 33,Date{31,01,2023}));
        person.addObligation(std::make_shared<Bills>(BillType::Internet, 33,Date{25,04,2023}));
        person.addObligation(std::make_shared<Loan>("Iphone 12", 2000,Date{24,02,2023}, 11));
    }
    
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
    addObligations();
    std::cout<<person.printAllObligations();
}
