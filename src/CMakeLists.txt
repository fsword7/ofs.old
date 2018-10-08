set(ofs_cpp_SRCS
	main/qt/qtmain.cpp
	main/qt/ofswinapp.cpp
	main/qt/ofscoreapp.cpp
	main/qt/ofswidget.cpp
	main/coreapp.cpp
	engine/universe/universe.cpp
)

set(ofs_h_SRCS
	main/qt/ofswinapp.h
	main/qt/ofscoreapp.h
	main/qt/ofswidget.h
	main/coreapp.h
	main/main.h
	main/math.h
	engine/universe/astro.h
	engine/universe/universe.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)
#include_directories(${SDL2_INCLUDE_DIRS} ${VULKAN_INCLUDE_DIRS})
#include_directories(${QT_INCLUDES} ${OPENGL_INCLUDE_DIRS})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_h_SRCS})
#target_link_libraries(ofs ${VULKAN_LIBRARIES} ${SDL2_LIBRARIES})
#target_link_libraries(ofs ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(ofs Qt5::Widgets)
