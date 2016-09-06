#############################################################################
# Makefile for building: Messenger
# Generated by qmake (2.01a) (Qt 4.8.1) on: Tue Aug 30 12:10:32 2016
# Project:  Messenger.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile Messenger.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -std=c++0x -O2 -D_REENTRANT $(DEFINES) -Wno-unused-result
CXXFLAGS      = -pipe -std=c++0x -O2 -D_REENTRANT $(DEFINES) -Wno-unused-result
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Icore -Igui -Imain -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = core/client.cpp \
		core/dispatcher.cpp \
		core/main_client.cpp \
		core/server.cpp \
		gui/log_in_window.cpp \
		gui/messenger_window.cpp \
		main/main.cpp \
		main/messenger.cpp \
		main/myThread.cpp moc_dispatcher.cpp \
		moc_server.cpp \
		moc_log_in_window.cpp \
		moc_messenger_window.cpp \
		moc_messenger.cpp \
		moc_myThread.cpp
OBJECTS       = client.o \
		dispatcher.o \
		main_client.o \
		server.o \
		log_in_window.o \
		messenger_window.o \
		main.o \
		messenger.o \
		myThread.o \
		moc_dispatcher.o \
		moc_server.o \
		moc_log_in_window.o \
		moc_messenger_window.o \
		moc_messenger.o \
		moc_myThread.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Messenger.pro
QMAKE_TARGET  = Messenger
DESTDIR       = 
TARGET        = Messenger

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Messenger.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile Messenger.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile Messenger.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Messenger1.0.0 || $(MKDIR) .tmp/Messenger1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Messenger1.0.0/ && $(COPY_FILE) --parents core/client.hpp core/dispatcher.hpp core/main_client.hpp core/server.hpp core/user.hpp gui/log_in_window.h gui/messenger_window.h main/messenger.h main/myThread.h .tmp/Messenger1.0.0/ && $(COPY_FILE) --parents core/client.cpp core/dispatcher.cpp core/main_client.cpp core/server.cpp gui/log_in_window.cpp gui/messenger_window.cpp main/main.cpp main/messenger.cpp main/myThread.cpp .tmp/Messenger1.0.0/ && (cd `dirname .tmp/Messenger1.0.0` && $(TAR) Messenger1.0.0.tar Messenger1.0.0 && $(COMPRESS) Messenger1.0.0.tar) && $(MOVE) `dirname .tmp/Messenger1.0.0`/Messenger1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Messenger1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) server 


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_dispatcher.cpp moc_server.cpp moc_log_in_window.cpp moc_messenger_window.cpp moc_messenger.cpp moc_myThread.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_dispatcher.cpp moc_server.cpp moc_log_in_window.cpp moc_messenger_window.cpp moc_messenger.cpp moc_myThread.cpp
moc_dispatcher.cpp: core/client.hpp \
		core/user.hpp \
		core/server.hpp \
		core/main_client.hpp \
		core/dispatcher.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) core/dispatcher.hpp -o moc_dispatcher.cpp

moc_server.cpp: core/user.hpp \
		core/server.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) core/server.hpp -o moc_server.cpp

moc_log_in_window.cpp: gui/log_in_window.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gui/log_in_window.h -o moc_log_in_window.cpp

moc_messenger_window.cpp: gui/messenger_window.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gui/messenger_window.h -o moc_messenger_window.cpp

moc_messenger.cpp: main/myThread.h \
		main/messenger.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) main/messenger.h -o moc_messenger.cpp

moc_myThread.cpp: main/myThread.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) main/myThread.h -o moc_myThread.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

client.o: core/client.cpp core/client.hpp \
		core/user.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o client.o core/client.cpp

dispatcher.o: core/dispatcher.cpp core/dispatcher.hpp \
		core/client.hpp \
		core/user.hpp \
		core/server.hpp \
		core/main_client.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dispatcher.o core/dispatcher.cpp

main_client.o: core/main_client.cpp core/main_client.hpp \
		core/user.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main_client.o core/main_client.cpp

server.o: core/server.cpp core/server.hpp \
		core/user.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o server.o core/server.cpp

log_in_window.o: gui/log_in_window.cpp gui/log_in_window.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log_in_window.o gui/log_in_window.cpp

messenger_window.o: gui/messenger_window.cpp gui/messenger_window.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o messenger_window.o gui/messenger_window.cpp

main.o: main/main.cpp main/messenger.h \
		main/myThread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main/main.cpp

messenger.o: main/messenger.cpp main/messenger.h \
		main/myThread.h \
		gui/messenger_window.h \
		gui/log_in_window.h \
		core/dispatcher.hpp \
		core/client.hpp \
		core/user.hpp \
		core/server.hpp \
		core/main_client.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o messenger.o main/messenger.cpp

myThread.o: main/myThread.cpp main/myThread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myThread.o main/myThread.cpp

moc_dispatcher.o: moc_dispatcher.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dispatcher.o moc_dispatcher.cpp

moc_server.o: moc_server.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_server.o moc_server.cpp

moc_log_in_window.o: moc_log_in_window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_log_in_window.o moc_log_in_window.cpp

moc_messenger_window.o: moc_messenger_window.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_messenger_window.o moc_messenger_window.cpp

moc_messenger.o: moc_messenger.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_messenger.o moc_messenger.cpp

moc_myThread.o: moc_myThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myThread.o moc_myThread.cpp

####### Install

install:   FORCE

uninstall:   FORCE

main_server_sources := \
    ./main_server/main.cpp \
    ./main_server/server.cpp \
    ./main_server/user_info.cpp \

main_server_headers := \
    ./main_server/server.hpp \
    ./main_server/user_info.hpp \
    
server: $(main_server_sources) $(main_server_headers)
	$(CXX) $(CXXFLAGS) $(main_server_sources) $(LIBS) -o $@


FORCE:
