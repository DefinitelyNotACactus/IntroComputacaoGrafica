#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/loader.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/objTester/list.o \
	${OBJECTDIR}/objTester/objLoader.o \
	${OBJECTDIR}/objTester/objTester.o \
	${OBJECTDIR}/objTester/obj_parser.o \
	${OBJECTDIR}/objTester/string_extra.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/introcomputacaografica.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/introcomputacaografica.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/introcomputacaografica ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/loader.o: loader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/loader.o loader.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/objTester/list.o: objTester/list.cpp
	${MKDIR} -p ${OBJECTDIR}/objTester
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/objTester/list.o objTester/list.cpp

${OBJECTDIR}/objTester/objLoader.o: objTester/objLoader.cpp
	${MKDIR} -p ${OBJECTDIR}/objTester
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/objTester/objLoader.o objTester/objLoader.cpp

${OBJECTDIR}/objTester/objTester.o: objTester/objTester.cpp
	${MKDIR} -p ${OBJECTDIR}/objTester
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/objTester/objTester.o objTester/objTester.cpp

${OBJECTDIR}/objTester/obj_parser.o: objTester/obj_parser.cpp
	${MKDIR} -p ${OBJECTDIR}/objTester
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/objTester/obj_parser.o objTester/obj_parser.cpp

${OBJECTDIR}/objTester/string_extra.o: objTester/string_extra.cpp
	${MKDIR} -p ${OBJECTDIR}/objTester
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/objTester/string_extra.o objTester/string_extra.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
