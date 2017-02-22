# This demo is a snake game.
# We tend to implement two versions of them.

set(SNAKE_COMMON_SOURCES snakepair.cpp snakepair.h
			 snakelogic.cpp snakelogic.h
			 snakerender.h snake.cpp)

# One use just main loop.
add_executable(snake ${SNAKE_COMMON_SOURCES} nongsrender.cpp)
target_link_libraries(snake CNG curses)

if(_CNG_NODEFAULT_GS_)
	# You should compile default Graphics if you want this demo.
else()
	# Another use main loop and graphics.
	add_executable(snakeGs ${SNAKE_COMMON_SOURCES} gsrender.cpp)
	target_link_libraries(snakeGs CNG curses)
endif()
