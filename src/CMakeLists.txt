# Add implementations for CNG interfaces here.
set(${CNG_SOURCES} "")

# Configure the code for main loop subsystem.
set(CNG_SOURCES ${CNG_SOURCES} 
	defaultMainLoop.cpp)

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

# Configure the code for box.h implementation.
set(CNG_SOURCES ${CNG_SOURCES} util.cpp)

# Assemble the code together.
if(_CNG_SHARED_LIB_)
	add_library(CNG SHARED ${CNG_SOURCES})
else()
	add_library(CNG ${CNG_SOURCES})
endif()
target_link_libraries(CNG curses pthread)
