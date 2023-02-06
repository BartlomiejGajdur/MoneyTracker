cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main # release-1.10.0
)

include(FetchContent)
FetchContent_Declare(
        Bcrypt
        GIT_REPOSITORY https://github.com/BartlomiejGajdur/Bcrypt.cpp
        GIT_TAG master
)
FetchContent_MakeAvailable(Bcrypt)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg

project(MONEYTRACKER)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp Src/Transaction.cpp Src/Date.cpp Src/User.cpp Src/ValidatePassword.cpp Src/Menu_LOG.cpp Src/MenuFunctions.cpp)
add_executable(${PROJECT_NAME}-ut Testing/DateTests.cpp Testing/UserTests.cpp Testing/ValidatePasswordTests.cpp Src/Transaction.cpp Src/Date.cpp Src/User.cpp Src/ValidatePassword.cpp Src/Menu_LOG.cpp Src/MenuFunctions.cpp)

target_link_libraries(${PROJECT_NAME}-ut gtest_main bcrypt)
target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)