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
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date));
    person.addObligation(std::make_shared<Bills>(BillType::Electricity, 33,date));
    person.addObligation(std::make_shared<Loan>("dasdasdas", 2000,date, 11));

    std::cout<<person.printIncomingObligations(10);

    ASSERT_EQ(before+1, person.getObligations().size());
}