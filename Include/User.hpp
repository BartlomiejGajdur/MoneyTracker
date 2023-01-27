#include <memory>
#include <string>
#include <vector>

#include "Tranzaction.hpp"

enum class UserErrorCode {Ok, NoTranzactionFound};

class User{

public:
    void addTranzaction(const std::shared_ptr<Tranzaction> tranzaction);
    UserErrorCode removeTranzactionById(size_t ID);

private:
    std::vector<std::shared_ptr<Tranzaction>> tranzactions_;
    
};