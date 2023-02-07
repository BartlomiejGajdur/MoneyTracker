#include <string>

enum class Color {Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White,
                  Bright_Black = 90, Bright_Red, Bright_Green, Bright_Yellow, Bright_Blue, 
                  Bright_Magenta, Bright_Cyan, Bright_White};

namespace MenuFunctions{

    void ClearTerminal();
    void WaitForAction();
    std::string insertPassword();
    size_t insertNumber(const size_t& zakresL, const size_t& zakresP);
    std::string SetTextColor(const Color& color, const std::string& text);
    std::string SetBackgroundColor(const Color& color, const std::string& text);
}