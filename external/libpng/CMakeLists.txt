set( target_name "libpng" )
message( STATUS "generate library: " ${target_name} )

set( inc_list 
	png.h
	)

set( src_list
	pngdebug.h
	pnginfo.h
	pngpriv.h
	pngstruct.h
	png.c
	pngerror.c
	pngget.c
	pngmem.c
	pngpread.c
	pngread.c
	pngrio.c
	pngrtran.c
	pngrutil.c
	pngset.c
	pngtrans.c
	pngwio.c
	pngwrite.c
	pngwtran.c
	pngwutil.c
	)



if( BUILD_PLATFORM_WIN32)
	include_directories( "${PROJECT_SOURCE_DIR}/external/zlib" )
endif()

add_library( ${target_name} STATIC ${src_list} ${inc_list}  )
set_target_properties(${target_name} PROPERTIES FOLDER external)

