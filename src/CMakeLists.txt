set(ofs_cpp_SRCS
	main/coreapp.cpp
	main/date.cpp
	main/plane.cpp
	engine/object.cpp
	engine/engine.cpp
	engine/player.cpp
	render/image.cpp
	render/shader.cpp
	render/shadermgr.cpp
	render/stars.cpp
	render/terrainmgr.cpp
	render/vobject.cpp
	render/vplanet.cpp
	render/ztreemgr.cpp
	render/gl/mesh.cpp
	render/gl/scene.cpp
	render/gl/shader.cpp
	render/gl/shadermgr.cpp
	render/gl/stars.cpp
	universe/astro.cpp
	universe/universe.cpp
	universe/stardb.cpp
	universe/startree.cpp
	universe/body.cpp
	universe/star.cpp
	util/color.cpp
	util/dds.cpp
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
	main/core.h
	main/coreapp.h
	main/main.h
	main/math.h
	main/date.h
	main/plane.h
	engine/object.h
	engine/engine.h
	engine/player.h
	render/image.h
	render/scene.h
	render/shader.h
	render/shadermgr.h
	render/stars.h
	render/terrainmgr.h
	render/vobject.h
	render/ztreemgr.h
	render/gl/funcs.h
	render/gl/mesh.h
	render/gl/scene.h
	render/gl/shader.h
	render/gl/shadermgr.h
	render/gl/stars.h
	universe/astro.h
	universe/universe.h
	universe/stardb.h
	universe/startree.h
	universe/body.h
	universe/star.h
	util/color.h
	util/dds.h
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
include_directories(
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
)

#add_executable(ofs ${ofs_cpp_SRCS} ${ofs_qt_cpp_SRCS} ${ofs_h_SRCS} ${ofs_qt_h_SRCS})
#qt5_use_modules(ofs Widgets OpenGL)
#target_link_libraries(ofs ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(ofs ${ofs_cpp_SRCS} ${ofs_sdl2_cpp_SRCS} ${ofs_h_SRCS} ${ofs_sdl2_h_SRCS})
target_link_libraries(ofs
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${ZLIB_LIBRARIES}
)
