enum class ErrorCode { Ok };

class Date{
public:
    Date() = default;
    Date(int day, int month, int year): day_(day) , month_(month), year_(year) {};

private:
    int month_{};
    int year_{};
    int day_{};
};