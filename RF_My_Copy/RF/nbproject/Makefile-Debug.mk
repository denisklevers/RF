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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/92f1562c/analyzer.o \
	${OBJECTDIR}/_ext/92f1562c/main.o \
	${OBJECTDIR}/_ext/92f1562c/simu.o \
	${OBJECTDIR}/_ext/92f1562c/tools.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/disttests.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/92f1562c/analyzer.o: ../../RF_MyCopy/analyzer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/analyzer.o ../../RF_MyCopy/analyzer.cpp

${OBJECTDIR}/_ext/92f1562c/main.o: ../../RF_MyCopy/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/main.o ../../RF_MyCopy/main.cpp

${OBJECTDIR}/_ext/92f1562c/simu.o: ../../RF_MyCopy/simu.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/simu.o ../../RF_MyCopy/simu.cpp

${OBJECTDIR}/_ext/92f1562c/tools.o: ../../RF_MyCopy/tools.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/tools.o ../../RF_MyCopy/tools.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/disttests.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/tests/disttests.o: tests/disttests.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/disttests.o tests/disttests.cpp


${OBJECTDIR}/_ext/92f1562c/analyzer_nomain.o: ${OBJECTDIR}/_ext/92f1562c/analyzer.o ../../RF_MyCopy/analyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/92f1562c/analyzer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/analyzer_nomain.o ../../RF_MyCopy/analyzer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/92f1562c/analyzer.o ${OBJECTDIR}/_ext/92f1562c/analyzer_nomain.o;\
	fi

${OBJECTDIR}/_ext/92f1562c/main_nomain.o: ${OBJECTDIR}/_ext/92f1562c/main.o ../../RF_MyCopy/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/92f1562c/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/main_nomain.o ../../RF_MyCopy/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/92f1562c/main.o ${OBJECTDIR}/_ext/92f1562c/main_nomain.o;\
	fi

${OBJECTDIR}/_ext/92f1562c/simu_nomain.o: ${OBJECTDIR}/_ext/92f1562c/simu.o ../../RF_MyCopy/simu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/92f1562c/simu.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/simu_nomain.o ../../RF_MyCopy/simu.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/92f1562c/simu.o ${OBJECTDIR}/_ext/92f1562c/simu_nomain.o;\
	fi

${OBJECTDIR}/_ext/92f1562c/tools_nomain.o: ${OBJECTDIR}/_ext/92f1562c/tools.o ../../RF_MyCopy/tools.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/92f1562c
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/92f1562c/tools.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/92f1562c/tools_nomain.o ../../RF_MyCopy/tools.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/92f1562c/tools.o ${OBJECTDIR}/_ext/92f1562c/tools_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
