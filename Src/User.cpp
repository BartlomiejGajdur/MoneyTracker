#include "../Include/User.hpp"

void User::addTranzaction(const std::shared_ptr<Tranzaction> tranzaction){
    tranzactions_.push_back(tranzaction);
}