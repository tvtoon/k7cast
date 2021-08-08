PROJECT = k7cast
MAJVER = 1.0
MINVER = 2
LIBS = ${PROJECT}
PROGS = ${PROJECT}

include make/conf
include make/cpplib
include make/alsa.mk
include make/flac.mk
include make/gl.mk
include make/libpng.mk
include make/libX11.mk
#include make/libXext.mk
#include make/libdl.mk
include make/openmp.mk
#include make/sdl2.mk
include make/zlib.mk

ELIBFLAGS += -lEGL -lutil -lzip
# -levdev -ludev
# -DUSE_LUA
#CFLAGS = -DBUILD_COMPILER=0x30000002 -DCHD5_LZMA -DCMAKE_BUILD -DDEF_CONSOLE -DFEAT_AREC=0x40000001 -DFEAT_DSPREC=0x40000001 -DFEAT_HAS_SOFTREND=1 -DFEAT_SHREC=0x40000002 -DFEAT_TA=0x60000001 -DHOST_CPU=0x20000004 -DHOST_OS=0x10000002 -DSUPPORT_EGL -DTARGET_NO_WEBUI
CFLAGS = -DNDEBUG -DUSE_ALSA -D_7ZIP_ST -DSUPPORT_X11
# -DUSE_JOYSTICK
#-DUSE_LIBAO -DUSE_SDL -DUSE_SDL_AUDIO -DUSE_VULKAN
# -DUSE_EVDEV -DUSE_UDEV
#CFLAGS += -DTEST_DC1
CFLAGS += -I. -Icore -Ideps
CFLAGS += -D_VERSION_=\"${VERSION}\" -O2 -Wall -Wextra -o
#CFLAGS += -msse4 --std=c++17
#
#C_FLAGS = -fno-strict-aliasing
#CXX_FLAGS = -fno-rtti -fno-strict-aliasing -fopenmp
# NOT USED: -DEGL_NO_X11 -DGL_SILENCE_DEPRECATION
# NOMINMAX: only once in "rend/vulkan/vk_mem_alloc.h".
# Windows: -D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES

DATA =
DOCS =
INFOS =
INCLUDES =

#For all source needs, that is almost what the build system do...
# ls */*.cpp */*/*.cpp */*/*/*.cpp */*/*.c */*/*/*.c
# EXTERNALS
SRC = deps/cdipsr.cpp
SRC += deps/imgui/imgui.cpp deps/imgui/imgui_demo.cpp deps/imgui/imgui_draw.cpp deps/imgui/imgui_widgets.cpp
SRC += deps/libelf/elf32.cpp deps/libelf/elf64.cpp deps/libelf/elf.cpp
SRC += deps/libchdr/bitstream.c deps/libchdr/cdrom.c deps/libchdr/chd.c deps/libchdr/flac.c deps/libchdr/huffman.c deps/libchdr/md5.c deps/libchdr/sha1.c
# deps/coreio/coreio.cpp deps/crypto/sha256.cpp

SRC += deps/lzma/7zArcIn.c deps/lzma/7zBuf.c deps/lzma/7zCrc.c deps/lzma/7zCrcOpt.c deps/lzma/7zDec.c deps/lzma/7zFile.c deps/lzma/7zStream.c deps/lzma/Alloc.c deps/lzma/Bcj2.c deps/lzma/Bra86.c deps/lzma/Bra.c deps/lzma/BraIA64.c deps/lzma/CpuArch.c deps/lzma/Delta.c deps/lzma/LzFind.c deps/lzma/Lzma2Dec.c deps/lzma/Lzma86Dec.c deps/lzma/Lzma86Enc.c deps/lzma/LzmaDec.c deps/lzma/LzmaEnc.c deps/lzma/LzmaLib.c deps/lzma/Sort.c

#SRC += deps/picotcp/pico_arp.c deps/picotcp/pico_dev_ppp.c deps/picotcp/pico_dns_client.c deps/picotcp/pico_dns_common.c deps/picotcp/pico_ethernet.c deps/picotcp/pico_fragments.c deps/picotcp/pico_ipv4.c deps/picotcp/pico_socket_tcp.c deps/picotcp/pico_socket_udp.c deps/picotcp/pico_strings.c deps/picotcp/pico_tcp.c deps/picotcp/pico_udp.c
#SRC += deps/picotcp/pico_device.c deps/picotcp/pico_frame.c deps/picotcp/pico_md5.c deps/picotcp/pico_protocol.c deps/picotcp/pico_socket.c deps/picotcp/pico_socket_multicast.c deps/picotcp/pico_stack.c deps/picotcp/pico_tree.c
#SRC += core/deps/picotcp/modules/pico_dhcp_common.c.o core/deps/picotcp/modules/pico_dhcp_server.c.o core/deps/picotcp/modules/pico_icmp4.c.o

SRC += deps/xbrz/xbrz.cpp deps/xxhash/xxhash.c

# MAIN
# Tools and whatever...
#aica-dsp-asm/main.cpp
#deps/khronos/GL3/gl3w.c
#gdtool/src/cdromfs.cpp
#gdtool/src/main.cpp
# Windows
#deps/dirent/dirent.c
# Not used?
#libswirl/android/Android.cpp
#libswirl/android/utils.cpp

# Others...
#libswirl/jit/rec_cpp.cpp
#libswirl/jit/rec_x86_asm.cpp
#libswirl/jit/rec_x86_driver.cpp
#libswirl/jit/x86_emitter.cpp
#libswirl/linux-dist/dispmanx.cpp
#libswirl/linux-dist/emscripten.cpp
#libswirl/linux-dist/evdev.cpp
#libswirl/linux-dist/joystick.cpp
#libswirl/oslib/audiobackend_coreaudio.cpp
#libswirl/oslib/audiobackend_directsound.cpp
#libswirl/oslib/audiobackend_libao.cpp
#libswirl/oslib/audiobackend_omx.cpp
#libswirl/oslib/audiobackend_pulseaudio.cpp
#libswirl/oslib/audiobackend_xaudio.cpp
#libswirl/oslib/windows_threading.cpp
#libswirl/rend/d3d11.cpp
#libswirl/utils/gl3w.cpp
#libswirl/utils/gl3w-es.cpp
#libswirl/utils/wgl.cpp
#libswirl/windows/winmain.cpp
#libswirl/windows/win_vmem.cpp

SRC += core/archive/7zArchive.cpp core/archive/ZipArchive.cpp core/archive/archive.cpp core/archive/rzip.cpp core/cfg/cfg.cpp core/cfg/cl.cpp core/cfg/ini.cpp core/cfg/option.cpp
#core/dispframe.cpp

SRC += core/hw/aica.cpp core/hw/aica_if.cpp core/hw/aica_mem.cpp core/hw/dsp.cpp core/hw/dsp_interp.cpp core/hw/dsp_x64.cpp core/hw/sgc_if.cpp
# core/hw/dsp_arm64.cpp core/hw/dsp_x86.cpp
# core/hw/aica_mmio.cpp
# core/hw/dsp_helpers.cpp

SRC += core/hw/arm7.cpp core/hw/arm7_rec.cpp core/hw/arm7_rec_x64.cpp core/hw/arm_mem.cpp core/hw/vbaARM.cpp
# core/hw/arm7_rec_arm32.cpp core/hw/arm7_rec_arm64.cpp
# core/hw/arm7_rec_x86.cpp
# core/hw/virt_arm.cpp

#core/hw/disc_common.cpp
SRC += core/hw/gdrom_response.cpp core/hw/gdromv3.cpp

SRC += core/hw/maple_cfg.cpp core/hw/maple_devs.cpp core/hw/maple_helper.cpp core/hw/maple_if.cpp core/hw/maple_jvs.cpp

SRC += core/hw/naomi/awcartridge.cpp core/hw/naomi/decrypt.cpp core/hw/naomi/gdcartridge.cpp core/hw/naomi/m1cartridge.cpp core/hw/naomi/m4cartridge.cpp core/hw/naomi/naomi_cart.cpp core/hw/naomi/naomi_flashrom.cpp core/hw/naomi/naomi_m3comm.cpp core/hw/naomi/naomi.cpp core/hw/naomi/naomi_roms.cpp

SRC += core/hw/pvr/drkPvr.cpp core/hw/pvr/pvr_mem.cpp core/hw/pvr/pvr_regs.cpp core/hw/pvr/pvr_sb_regs.cpp core/hw/pvr/Renderer_if.cpp core/hw/pvr/spg.cpp core/hw/pvr/ta.cpp core/hw/pvr/ta_ctx.cpp core/hw/pvr/ta_vtx.cpp
# core/hw/pvr/pvr_yuv.cpp

SRC += core/hw/sh4/blockmanager.cpp core/hw/sh4/bsc.cpp core/hw/sh4/ccn.cpp core/hw/sh4/cpg.cpp core/hw/sh4/decoder.cpp core/hw/sh4/dmac.cpp core/hw/sh4/driver.cpp core/hw/sh4/fastmmu.cpp core/hw/sh4/intc.cpp core/hw/sh4/mmu.cpp core/hw/sh4/rtc.cpp core/hw/sh4/serial.cpp core/hw/sh4/sh4_core_regs.cpp core/hw/sh4/sh4_fpu.cpp core/hw/sh4/sh4_interpreter.cpp core/hw/sh4/sh4_interrupts.cpp core/hw/sh4/sh4_mem.cpp core/hw/sh4/sh4_mmr.cpp core/hw/sh4/sh4_opcode_list.cpp core/hw/sh4/sh4_opcodes.cpp core/hw/sh4/sh4_rom.cpp core/hw/sh4/sh4_sched.cpp core/hw/sh4/shil.cpp core/hw/sh4/ssa.cpp core/hw/sh4/tmu.cpp core/hw/sh4/ubc.cpp
# core/hw/sh4/sci.cpp core/hw/sh4/scif.cpp
# core/hw/sh4/SuperH4_impl.cpp
# core/hw/sh4/blockmanager-extras.cpp

SRC += core/hw/holly_intc.cpp core/hw/sb.cpp core/hw/sb_mem.cpp core/hw/_vmem.cpp

#SRC += core/hw/dns.cpp core/hw/modem.cpp core/hw/picoppp.cpp

SRC += core/imgread/ImgReader.cpp core/imgread/cdi.cpp core/imgread/chd.cpp  core/imgread/common.cpp core/imgread/cue.cpp core/imgread/gdi.cpp core/imgread/ioctl.cpp

SRC += core/reios/descrambl.cpp core/reios/gdrom_hle.cpp core/reios/reios.cpp core/reios/reios_elf.cpp

SRC += core/cheats.cpp core/dispframe.cpp core/nullDC.cpp core/profiler.cpp core/rec_cpp.cpp core/rec_x64.cpp core/serialize.cpp core/stdclass.cpp
# core/sdl.cpp
#SRC += lxdream/tacore.cpp

#core/hw/bba/bba.cpp core/hw/bba/rtl8139c.cpp

#core/hw/modem/modem.cpp

LIBSRC = ${SRC}

#PROGSRC = core/gui/gui_android.cpp core/gui/gui.cpp core/gui/gui_renderer.cpp core/gui/gui_settings_about.cpp core/gui/gui_settings_advanced.cpp core/gui/gui_settings_audio.cpp core/gui/gui_settings_controls.cpp core/gui/gui_settings.cpp core/gui/gui_settings_general.cpp core/gui/gui_settings_social.cpp core/gui/gui_settings_video.cpp core/gui/gui_util.cpp core/gui/gui_welcome.cpp

PROGSRC += core/input/gamepad_device.cpp core/input/keyboard_device.cpp core/input/mapping.cpp

#OUTA: core/linux/nixprof.cpp
PROGSRC += core/linux/common.cpp core/linux/context.cpp core/linux/posix_vmem.cpp
PROGSRC += core/linux-dist/dispmanx.cpp core/linux-dist/joystick.cpp core/linux-dist/main.cpp core/linux-dist/x11.cpp
#core/linux-dist/evdev.cpp

PROGSRC += core/log/ConsoleListenerDroid.cpp core/log/ConsoleListenerNix.cpp core/log/ConsoleListenerWin.cpp core/log/LogManager.cpp

# core/network/dns.cpp core/network/miniupnp.cpp core/network/naomi_network.cpp core/network/picoppp.cpp

# core/oslib/audiobackend_coreaudio.cpp core/oslib/audiobackend_directsound.cpp core/oslib/audiobackend_libao.cpp core/oslib/audiobackend_oboe.cpp core/oslib/audiobackend_omx.cpp core/oslib/audiobackend_pulseaudio.cpp core/oslib/audiobackend_sdl2.cpp core/oslib/audiostream.cpp
PROGSRC += core/oslib/audiobackend_alsa.cpp core/oslib/audiobackend_null.cpp core/oslib/audiobackend_oss.cpp core/oslib/audiobackend_sdl2.cpp core/oslib/audiostream.cpp
# core/oslib/posix_threading.cpp

PROGSRC += core/rend/CustomTexture.cpp core/rend/norend.cpp core/rend/TexCache.cpp
PROGSRC += core/rend/gui.cpp core/rend/gui_android.cpp core/rend/gui_cheats.cpp core/rend/gui_util.cpp core/rend/mainui.cpp core/rend/osd.cpp core/rend/sorter.cpp
PROGSRC += core/rend/gl4abuffer.cpp core/rend/gl4draw.cpp core/rend/gl4es.cpp

# OLD:  core/rend/refrend_base.cpp core/rend/refrend_debug.cpp core/rend/refsw.cpp core/rend/refsw_pixel.cpp core/rend/slowsoftrend.cpp core/rend/softrend.cpp
PROGSRC += core/rend/glesdraw.cpp core/rend/gles.cpp core/rend/glestex.cpp core/rend/gles_imgui_opengl.cpp core/rend/glesquad.cpp
PROGSRC += core/rend/transform_matrix.cpp

#PROGSRC += core/rend/vulkan/oit/oit_drawer.cpp core/rend/vulkan/oit/oit_pipeline.cpp core/rend/vulkan/oit/oit_renderer.cpp core/rend/vulkan/oit/oit_renderpass.cpp core/rend/vulkan/oit/oit_shaders.cpp core/rend/vulkan/buffer.cpp core/rend/vulkan/compiler.cpp core/rend/vulkan/drawer.cpp core/rend/vulkan/imgui_impl_vulkan.cpp core/rend/vulkan/pipeline.cpp core/rend/vulkan/quad.cpp core/rend/vulkan/shaders.cpp core/rend/vulkan/texture.cpp core/rend/vulkan/vmallocator.cpp core/rend/vulkan/overlay.cpp core/rend/vulkan/vulkan_context.cpp core/rend/vulkan/vulkan_renderer.cpp

# core/wsi/egl.cpp
PROGSRC += core/wsi/gl32funcs.c core/wsi/gl4funcs.cpp core/wsi/gl_context.cpp core/wsi/switcher.cpp core/wsi/xgl.cpp
# OLD: core/utils/gl3w.cpp core/utils/gl3w-es.cpp core/utils/glx.cpp core/utils/http.cpp core/utils/cloudrom.cpp
#core/utils/sdl.cpp
# core/wsi/osx.cpp core/wsi/sdl.cpp core/wsi/wgl.cpp

#PROGOBJ = core/gui/gui_android.o core/gui/gui.o core/gui/gui_renderer.o core/gui/gui_settings_about.o core/gui/gui_settings_advanced.o core/gui/gui_settings_audio.o core/gui/gui_settings_controls.o core/gui/gui_settings.o core/gui/gui_settings_general.o core/gui/gui_settings_social.o core/gui/gui_settings_video.o core/gui/gui_util.o core/gui/gui_welcome.o

PROGOBJ += core/input/gamepad_device.o core/input/keyboard_device.o core/input/mapping.o

PROGOBJ += core/linux/common.o core/linux/context.o core/linux/posix_vmem.o
PROGOBJ += core/linux-dist/dispmanx.o core/linux-dist/joystick.o core/linux-dist/main.o core/linux-dist/x11.o
#core/linux-dist/evdev.o
# core/linux/nixprof.o

PROGOBJ += core/log/ConsoleListenerDroid.o core/log/ConsoleListenerNix.o core/log/ConsoleListenerWin.o core/log/LogManager.o

PROGOBJ += core/oslib/audiobackend_alsa.o core/oslib/audiobackend_null.o core/oslib/audiobackend_oss.o core/oslib/audiobackend_sdl2.o core/oslib/audiostream.o

PROGOBJ += core/rend/CustomTexture.o core/rend/norend.o core/rend/TexCache.o
PROGOBJ += core/rend/gui.o core/rend/gui_android.o core/rend/gui_cheats.o core/rend/gui_util.o core/rend/mainui.o core/rend/osd.o core/rend/sorter.o
PROGOBJ += core/rend/gl4abuffer.o core/rend/gl4draw.o core/rend/gl4es.o
# Needed by GL4
PROGOBJ += core/rend/glesdraw.o core/rend/gles.o core/rend/glestex.o core/rend/gles_imgui_opengl.o core/rend/glesquad.o
PROGOBJ += core/rend/transform_matrix.o

PROGOBJ += core/wsi/gl32funcs.o core/wsi/gl4funcs.o core/wsi/gl_context.o core/wsi/switcher.o core/wsi/xgl.o

include make/exconf.noasm
include make/build

dist-clean: clean

clean-core:
	rm -f core/*.o core/*/*.o core/*/*/*.o
#clean-ext:
#	rm -f 
#clean-test:
#	rm -f 

${PROGS}: ${PROGOBJ}

include make/pack
include make/rules
#include make/thedep
