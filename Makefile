# a Unix based makefile
NAME=te13-DemonSteele
JUKEBOX_NAME=te13-metal-jukebox
SRC=pk3/acs
OBJ=pk3/acs
.PHONY: help pk3 pk7 clean jukebox-pk3 jukebox-pk3

help:
	@echo "Available options:"
	@echo "  help    - prints this dialog and exits"
	@echo "  pk3     - builds a pk3 archive of the target sources"
	@echo "  pk7     - builds a pk7 archive of the target sources"
	@echo "  pk3     - builds a pk3 archive of the jukebox"
	@echo "  pk7     - builds a pk7 archive of the jukebox"
	@echo "  compile - equivalent to the commands in _compile.bat (assumes that acc is on the path)!"

jukebox-pk3:
	@echo -n "Building ${JUKEBOX_NAME}.pk3 ......"
	@cd metal-jukebox-pk3 && 7z a -tzip ../${JUKEBOX_NAME}.pk3 *
	@echo "done"

jukebox-pk7:
	@echo -n "Building ${JUKEBOX_NAME}.pk7 ......"
	@cd metal-jukebox-pk3 && 7z a ../${JUKEBOX_NAME}.pk7 *
	@echo "done"

pk3:
	@echo -n "Building ${NAME}.pk3 ......"
	@cd pk3 && 7z a -tzip ../${NAME}.pk3 *
	@echo "done"

pk7:
	@echo -n "Building ${NAME}.pk7 ......"
	@cd pk3 && 7z a ../${NAME}.pk7 *
	@echo "done"

clean:
	@echo -n "Removing archives....."
	@rm -f ${NAME}.pk7 ${NAME}.pk3 ${JUKEBOX_NAME}.pk7 ${JUKEBOX_NAME}.pk3
	@echo "done"

# assume that acc is on the path
compile:
	@echo -n "Compiling Weeaboo"
	@acc ${SRC}/weeaboo.c ${OBJ}/weeaboo.o
	@echo "done"
