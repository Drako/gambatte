
find_package(SDL2 REQUIRED)

set(gambatte_sdl_SOURCES
        src/audiosink.cpp src/audiosink.h
        src/blitterwrapper.cpp src/blitterwrapper.h
        src/gambatte_sdl.cpp
        src/parser.cpp src/parser.h
        src/sdlblitter.cpp src/sdlblitter.h
        src/str_to_sdlkey.cpp src/str_to_sdlkey.h
        src/usec.cpp
        ../common/adaptivesleep.cpp
        ../common/resample/src/chainresampler.cpp
        ../common/resample/src/i0.cpp
        ../common/resample/src/kaiser50sinc.cpp
        ../common/resample/src/kaiser70sinc.cpp
        ../common/resample/src/makesinckernel.cpp
        ../common/resample/src/resamplerinfo.cpp
        ../common/resample/src/u48div.cpp
        ../common/rateest.cpp
        ../common/skipsched.cpp
        ../common/videolink/rgb32conv.cpp
        ../common/videolink/vfilterinfo.cpp
        ../common/videolink/vfilters/catrom2x.cpp
        ../common/videolink/vfilters/catrom3x.cpp
        ../common/videolink/vfilters/kreed2xsai.cpp
        ../common/videolink/vfilters/maxsthq2x.cpp
        ../common/videolink/vfilters/maxsthq3x.cpp
        )

add_executable(gambatte_sdl WIN32 ${gambatte_sdl_SOURCES})
target_include_directories(gambatte_sdl PRIVATE ${SDL2_INCLUDE_DIRS} ../common ../libgambatte/include)
target_link_libraries(gambatte_sdl PRIVATE gambatte ${SDL2_LIBRARIES})
