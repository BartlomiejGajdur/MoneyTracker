#include <algorithm>

#include "../Include/User.hpp"

void User::addTranzaction(const std::shared_ptr<Tranzaction> tranzaction){
    tranzactions_.push_back(tranzaction);
}

UserErrorCode User::removeTranzactionById(size_t ID){
    auto temp = tranzactions_.size();
    tranzactions_.erase(std::remove_if(tranzactions_.begin(), tranzactions_.end(),[&ID](std::shared_ptr<Tranzaction> tranzaction)
                                                                                                                            {
                                                                                                                               return tranzaction->getID() == ID;
                                                                                                                            }));
    return temp>tranzactions_.size() ? UserErrorCode::Ok : UserErrorCode::NoTranzactionFound;
}