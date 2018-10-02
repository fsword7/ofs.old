set(ofs_cpp_SRCS
	osd/sdl2/main.cpp
	main/core.cpp
	engine/universe/universe.cpp
)

set(ofs_h_SRCS
	main/core.h
	main/main.h
	main/math.h
	engine/universe/astro.h
	engine/universe/universe.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_h_SRCS})
target_link_libraries(ofs ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
