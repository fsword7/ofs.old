set(ofs_cpp_SRCS
	main/coreapp.cpp
	main/date.cpp
	engine/object.cpp
	engine/engine.cpp
	engine/player.cpp
	render/image.cpp
	render/terrainmgr.cpp
	render/vobject.cpp
	render/vplanet.cpp
	render/ztreemgr.cpp
	render/gl/mesh.cpp
	render/gl/scene.cpp
	render/gl/shader.cpp
	render/gl/shadermgr.cpp
	universe/universe.cpp
	universe/stardb.cpp
	universe/body.cpp
	universe/star.cpp
	util/tree.cpp
)

set(ofs_qt_cpp_SECS
	main/qt/qtmain.cpp
	main/qt/ofswinapp.cpp
	main/qt/ofscoreapp.cpp
	main/qt/ofswidget.cpp
)

set(ofs_sdl2_cpp_SRCS
	main/sdl2/coreapp.cpp
	main/sdl2/glmain.cpp
)

set(ofs_h_SRCS
	main/coreapp.h
	main/main.h
	main/math.h
	main/date.h
	engine/object.h
	engine/engine.h
	engine/player.h
	render/image.h
	render/scene.h
	render/shader.h
	render/terrainmgr.h
	render/vobject.h
	render/ztreemgr.h
	render/gl/funcs.h
	render/gl/mesh.h
	render/gl/scene.h
	render/gl/shader.h
	render/gl/shadermgr.h
	universe/astro.h
	universe/universe.h
	universe/stardb.h
	universe/body.h
	universe/star.h
	util/tree.h
)

set(ofs_qt_h_SRCS
	main/qt/ofswinapp.h
	main/qt/ofscoreapp.h
	main/qt/ofswidget.h
)

set(ofs_sdl2_h_SRCS
	main/sdl2/coreapp.h
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

#add_executable(ofs ${ofs_cpp_SRCS} ${ofs_qt_cpp_SRCS} ${ofs_h_SRCS} ${ofs_qt_h_SRCS})
#qt5_use_modules(ofs Widgets OpenGL)
#target_link_libraries(ofs ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_sdl2_cpp_SRCS} ${ofs_h_SRCS} ${ofs_sdl2_h_SRCS})
target_link_libraries(ofs
	${SDL2_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${ZLIB_LIBRARIES}
)
