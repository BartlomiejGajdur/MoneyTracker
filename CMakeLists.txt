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


FetchContent_Declare(

    libxlsxwriter

    GIT_REPOSITORY

    https://github.com/jmcnamara/libxlsxwriter.git

    GIT_TAG main

)

FetchContent_MakeAvailable(libxlsxwriter)

FetchContent_GetProperties(libxlsxwriter)

if(NOT libxlsxwriter_POPULATED)

    FetchContent_Populate(libxlsxwriter)

    message(STATUS "libxlsxwriter source dir: ${libxlsxwriter_SOURCE_DIR}")

    message(STATUS "libxlsxwriter binary dir: ${libxlsxwriter_BINARY_DIR}")

    add_subdirectory(${libxlsxwriter_SOURCE_DIR} ${libxlsxwriter_BINARY_DIR})

endif()

# Now simply link against gtest or gtest_main as needed. Eg

project(MONEYTRACKER)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp Src/Transaction.cpp Src/Date.cpp Src/User.cpp Src/ValidatePassword.cpp Src/Menu_LOG.cpp Src/MenuFunctions.cpp Src/Menu_Main.cpp Src/ExcelGenerator.cpp)
add_executable(${PROJECT_NAME}-ut Testing/DateTests.cpp Testing/UserTests.cpp Testing/ValidatePasswordTests.cpp Src/Transaction.cpp Src/Date.cpp Src/User.cpp Src/ValidatePassword.cpp Src/Menu_LOG.cpp Src/MenuFunctions.cpp Src/Menu_Main.cpp Src/ExcelGenerator.cpp)

target_link_libraries(${PROJECT_NAME}-ut gtest_main bcrypt xlsxwriter)
target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt xlsxwriter)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)