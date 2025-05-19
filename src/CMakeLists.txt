# Create ListNode module
add_library(ListNode)
target_sources(ListNode
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Util/ListNode.cppm
)

enable_testing()

include(GoogleTest)
macro(add_listnode_executable exe src)
    add_executable(${exe} ${src})
    target_link_libraries(${exe} PRIVATE ListNode GTest::gtest_main)
    gtest_discover_tests(${exe})
endmacro()

# Find all .cpp files in the current directory
file(GLOB CPP_FILES *.cpp)

# Create an executable for each .cpp file
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
    add_listnode_executable(${EXECUTABLE_NAME} ${CPP_FILE})
endforeach()
