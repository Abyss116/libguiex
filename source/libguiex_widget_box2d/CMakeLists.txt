set( target_name "libguiex_widget_box2d" )
message( STATUS "generate library: " ${target_name} )

#box2d widget
set( ${target_name}_box2d_SRCS 
        guiwgtbox2dbase.cpp
        guiwgtbox2dbase.h
        guiwgtbox2dbodybase.cpp
        guiwgtbox2dbodybase.h
        guiwgtbox2dstaticbody.cpp
        guiwgtbox2dstaticbody.h
        guiwgtbox2ddynamicbody.cpp
        guiwgtbox2ddynamicbody.h
        guiwgtbox2djoint.cpp
        guiwgtbox2djoint.h 
	)
source_group( box2d FILES ${${target_name}_box2d_SRCS} )

#utility
set( ${target_name}_utility_SRCS 
		guiwgt_box2d.h
        guiwgtgeneratewidgets_box2d.cpp
        guiwgtgeneratewidgets_box2d.h
	)
source_group( utility FILES ${${target_name}_utility_SRCS} )

set( ${target_name}_SRCS 
	${${target_name}_box2d_SRCS}
	${${target_name}_utility_SRCS}
	)

#include directory
include_directories( "${PROJECT_SOURCE_DIR}/external/Box2D" )
    
add_library( ${target_name} STATIC ${${target_name}_SRCS} )
set_target_properties(${target_name} PROPERTIES FOLDER library)

