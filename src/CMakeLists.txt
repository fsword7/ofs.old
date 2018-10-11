set(ofs_cpp_SRCS
	main/qt/qtmain.cpp
	main/qt/ofswinapp.cpp
	main/qt/ofscoreapp.cpp
	main/qt/ofswidget.cpp
	main/coreapp.cpp
	engine/object.cpp
	engine/engine.cpp
	engine/player.cpp
	engine/render/glrender.cpp
	engine/universe/universe.cpp
)

set(ofs_h_SRCS
	main/qt/ofswinapp.h
	main/qt/ofscoreapp.h
	main/qt/ofswidget.h
	main/coreapp.h
	main/main.h
	main/math.h
	engine/object.h
	engine/engine.h
	engine/player.h
	engine/render/render.h
	engine/universe/astro.h
	engine/universe/universe.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_h_SRCS})
qt5_use_modules(ofs Widgets OpenGL)
target_link_libraries(ofs ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
