# Add implementations for CNG interfaces here.

#add_library(CNG pane.cpp)
add_library(CNG mainloop.cpp)
target_link_libraries(CNG curses)
