# Add implementations for CNG interfaces here.

if(_CNG_NODEFAULT_GS_)
	set(DEFAULT_GS_SOURCES "")
else()
	set(DEFAULT_GS_SOURCES 
		nullGs.h 
		nullGs.cpp
		defaultGs.h
		defaultGs.cpp)
endif()

add_library(CNG mainloop.cpp ${DEFAULT_GS_SOURCES})
target_link_libraries(CNG curses)
