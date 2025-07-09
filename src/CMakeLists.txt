# Create ListNode module
add_library(ListNode)
target_sources(ListNode
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Util/ListNode.cppm
)
add_library(TreeNode)
target_sources(TreeNode
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Util/TreeNode.cppm
)

enable_testing()

include(GoogleTest)
macro(add_solution_executable exe src)
    add_executable(${exe} ${src})
    target_link_libraries(${exe} PRIVATE ListNode TreeNode GTest::gtest_main)
    gtest_discover_tests(${exe})
endmacro()

# Find all .cpp files in the current directory
file(GLOB CPP_FILES *.cpp)

# Create an executable for each .cpp file
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_solution_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()
