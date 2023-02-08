#include <string>
#include <vector>

enum class Color {Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White,
                  Bright_Black = 90, Bright_Red, Bright_Green, Bright_Yellow, Bright_Blue, 
                  Bright_Magenta, Bright_Cyan, Bright_White};

namespace MenuFunctions{

    void ClearTerminal();
    void WaitForAction();
    std::string insertPassword();
    int insertNumber(const int& zakresL, const int& zakresP);
    std::string SetTextColor(const Color& color, const std::string& text);
    std::string SetBackgroundColor(const Color& color, const std::string& text);
    std::string SetBoldText(const std::string& text);
    int arrowMenu(const std::vector<std::string>& Options);

}