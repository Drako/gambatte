
find_package(ZLIB)

set(libgambatte_SOURCES
        src/bitmap_font.cpp src/bitmap_font.h
        src/counterdef.h
        src/cpu.cpp src/cpu.h
        src/gambatte.cpp
        src/initstate.cpp src/initstate.h
        src/insertion_sort.h
        src/interrupter.cpp src/interrupter.h
        src/interruptrequester.cpp src/interruptrequester.h
        src/loadres.cpp
        src/memory.cpp src/memory.h
        src/minkeeper.h
        src/osd_element.h
        src/savestate.h
        src/sound.cpp src/sound.h
        src/state_osd_elements.cpp src/state_osd_elements.h
        src/statesaver.cpp src/statesaver.h
        src/tima.cpp src/tima.h
        src/video.cpp src/video.h
        src/mem/cartridge.cpp src/mem/cartridge.h
        src/mem/memptrs.cpp src/mem/memptrs.h
        src/mem/pakinfo.cpp src/mem/pakinfo_internal.h
        src/mem/rtc.cpp src/mem/rtc.h
        src/sound/channel1.cpp src/sound/channel1.h
        src/sound/channel2.cpp src/sound/channel2.h
        src/sound/channel3.cpp src/sound/channel3.h
        src/sound/channel4.cpp src/sound/channel4.h
        src/sound/duty_unit.cpp src/sound/duty_unit.h
        src/sound/envelope_unit.cpp src/sound/envelope_unit.h
        src/sound/length_counter.cpp src/sound/length_counter.h
        src/sound/master_disabler.h
        src/sound/psgdef.h
        src/sound/sound_unit.h
        src/sound/static_output_tester.h
        src/video/lcddef.h
        src/video/ly_counter.cpp src/video/ly_counter.h
        src/video/lyc_irq.cpp src/video/lyc_irq.h
        src/video/mstat_irq.h
        src/video/next_m0_time.cpp src/video/next_m0_time.h
        src/video/ppu.cpp src/video/ppu.h
        src/video/sprite_mapper.cpp src/video/sprite_mapper.h
        src/file/file.h
        src/file/stdfile.h

        include/gambatte.h
        include/gbint.h
        include/inputgetter.h
        include/loadres.h
        include/pakinfo.h
        )


if (ZLIB_FOUND)
    list(APPEND libgambatte_SOURCES
            src/file/unzip/crypt.h
            src/file/unzip/unzip.c src/file/unzip/unzip.h
            src/file/unzip/ioapi.c src/file/unzip/ioapi.h
            src/file/file_zip.cpp
            )
else ()
    list(APPEND libgambatte_SOURCES src/file/file.cpp)
endif ()

add_library(gambatte STATIC ${libgambatte_SOURCES})
target_include_directories(gambatte PRIVATE src ../common PUBLIC include)
target_compile_definitions(gambatte PUBLIC -DHAVE_STDINT_H)

if (ZLIB_FOUND)
    target_include_directories(gambatte PUBLIC ${ZLIB_INCLUDE_DIRS})
    target_link_libraries(gambatte PUBLIC ${ZLIB_LIBRARIES})
endif ()
