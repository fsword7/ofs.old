set(ofs_cpp_SRCS
	main/coreapp.cpp
	engine/object.cpp
	engine/engine.cpp
	engine/player.cpp
	engine/render/terrainmgr.cpp
	engine/render/vobject.cpp
	engine/render/vplanet.cpp
	engine/render/gl/mesh.cpp
	engine/render/gl/scene.cpp
	engine/render/gl/shader.cpp
	engine/render/gl/shadermgr.cpp
	engine/universe/universe.cpp
	engine/universe/body.cpp
	engine/universe/star.cpp
	util/tree.cpp
)

set(ofs_qt_cpp_SECS
	main/qt/qtmain.cpp
	main/qt/ofswinapp.cpp
	main/qt/ofscoreapp.cpp
	main/qt/ofswidget.cpp
)

set(ofs_sdl2_cpp_SRCS
	main/sdl2/glmain.cpp
)

set(ofs_h_SRCS
	main/coreapp.h
	main/main.h
	main/math.h
	engine/object.h
	engine/engine.h
	engine/player.h
	engine/render/scene.h
	engine/render/shader.h
	engine/render/terrainmgr.h
	engine/render/vobject.h
	engine/render/gl/funcs.h
	engine/render/gl/mesh.h
	engine/render/gl/shadermgr.h
	engine/universe/astro.h
	engine/universe/universe.h
	engine/universe/body.h
	engine/universe/star.h
	util/tree.h
)

set(ofs_qt_h_SRCS
	main/qt/ofswinapp.h
	main/qt/ofscoreapp.h
	main/qt/ofswidget.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

#add_executable(ofs ${ofs_cpp_SRCS} ${ofs_qt_cpp_SRCS} ${ofs_h_SRCS} ${ofs_qt_h_SRCS})
#qt5_use_modules(ofs Widgets OpenGL)
#target_link_libraries(ofs ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_sdl2_cpp_SRCS} ${ofs_h_SRCS})
target_link_libraries(ofs ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
