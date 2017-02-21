# Add implementations for CNG interfaces here.
set(${CNG_SOURCES} "")

# Configure the code for main loop subsystem.
set(CNG_SOURCES ${CNG_SOURCES} mainloop.cpp)

# Configure the code for default graphics subsystem.
if(_CNG_NODEFAULT_GS_)
	# Do not add default Gs sources.
else()
	set(CNG_SOURCES ${CNG_SOURCES}
		defaultGs.cpp
		nullGs.cpp
		nullGs.h 
		defaultGs.h)
endif()

# Assemble the code together.
add_library(CNG ${CNG_SOURCES})
target_link_libraries(CNG curses)
