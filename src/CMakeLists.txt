# Create ListNode module
add_library(ListNode)
target_sources(ListNode
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Util/ListNode.cppm
)

# Add executables for LeetCode solutions
add_executable(88_MergeSortedArray 88_MergeSortedArray.cpp)
add_executable(27_RemoveElement 27_RemoveElement.cpp)

# Add LinkedListCycle executable with module dependency
add_executable(141_LinkedListCycle 141_LinkedListCycle.cpp)
target_link_libraries(141_LinkedListCycle PRIVATE ListNode)