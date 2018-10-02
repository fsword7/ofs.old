set(ofs_cpp_SRCS
	osd/sdl2/main.cpp
	main/core.cpp
)

set(ofs_h_SRCS
	main/core.h
	main/main.h
	main/math.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_h_SRCS})
