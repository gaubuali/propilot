#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 
# Macros
CND_CONF=default

ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o ${OBJECTDIR}/_ext/680170088/servoMix.o ${OBJECTDIR}/_ext/1344113738/estYawDrift.o ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o ${OBJECTDIR}/_ext/1344097381/libUDB.o ${OBJECTDIR}/_ext/680170088/navigate.o ${OBJECTDIR}/_ext/680170088/servoPrepare.o ${OBJECTDIR}/_ext/680170088/mp_osd.o ${OBJECTDIR}/_ext/1344113738/rmat.o ${OBJECTDIR}/_ext/1344113738/estWind.o ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o ${OBJECTDIR}/_ext/1344097381/osd.o ${OBJECTDIR}/_ext/680170088/states.o ${OBJECTDIR}/_ext/680170088/main.o ${OBJECTDIR}/_ext/680170088/telemetry.o ${OBJECTDIR}/_ext/1344113738/deadReckoning.o ${OBJECTDIR}/_ext/1344097381/background.o ${OBJECTDIR}/_ext/680170088/cameraCntrl.o ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o ${OBJECTDIR}/_ext/680170088/behavior.o ${OBJECTDIR}/_ext/680170088/rollCntrl.o ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o ${OBJECTDIR}/_ext/1344113738/libDCM.o ${OBJECTDIR}/_ext/680170088/pitchCntrl.o ${OBJECTDIR}/_ext/1344097381/SuperSample.o ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o ${OBJECTDIR}/_ext/680170088/flightplan-logo.o ${OBJECTDIR}/_ext/680170088/yawCntrl.o ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

OS_ORIGINAL="MINGW32_NT-5.1"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-gcc.exe
MP_AS=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-as.exe
MP_LD=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-ld.exe
MP_AR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-ar.exe
MP_CC_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
MP_AS_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
MP_LD_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
MP_AR_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
.PHONY: ${OBJECTDIR}/_ext/1344097381/SuperSample.o
${OBJECTDIR}/_ext/1344097381/SuperSample.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/SuperSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1344097381/SuperSample.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/SuperSample.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,-g
else
.PHONY: ${OBJECTDIR}/_ext/1344097381/SuperSample.o
${OBJECTDIR}/_ext/1344097381/SuperSample.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/SuperSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1344097381/SuperSample.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/SuperSample.s  -Wa,--defsym=__MPLAB_BUILD=1
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseUBX.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/mathlibNAV.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/mathlibNAV.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/altitudeCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/altitudeCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseCommon.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/servoMix.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/servoMix.o.d -o ${OBJECTDIR}/_ext/680170088/servoMix.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoMix.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/servoMix.o.d > ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/servoMix.o.d > ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/estYawDrift.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1344113738/estYawDrift.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estYawDrift.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d > ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d > ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseSTD.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/libUDB.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/libUDB.o.d -o ${OBJECTDIR}/_ext/1344097381/libUDB.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/libUDB.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/libUDB.o.d > ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/libUDB.o.d > ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/navigate.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/navigate.o.d -o ${OBJECTDIR}/_ext/680170088/navigate.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/navigate.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/navigate.o.d > ${OBJECTDIR}/_ext/680170088/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/navigate.o.d > ${OBJECTDIR}/_ext/680170088/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/servoPrepare.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d -o ${OBJECTDIR}/_ext/680170088/servoPrepare.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoPrepare.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d > ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d > ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/mp_osd.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/mp_osd.o.d -o ${OBJECTDIR}/_ext/680170088/mp_osd.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/mp_osd.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/mp_osd.o.d > ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/mp_osd.o.d > ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/rmat.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/rmat.o.d -o ${OBJECTDIR}/_ext/1344113738/rmat.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/rmat.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/rmat.o.d > ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/rmat.o.d > ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/estWind.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/estWind.o.d -o ${OBJECTDIR}/_ext/1344113738/estWind.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estWind.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/estWind.o.d > ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/estWind.o.d > ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/analog2digital_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/analog2digital_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/servoOut_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/servoOut_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/magneto_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/magneto_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/magneto_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/osd.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/osd.o.d -o ${OBJECTDIR}/_ext/1344097381/osd.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/osd.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/osd.o.d > ${OBJECTDIR}/_ext/1344097381/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/osd.o.d > ${OBJECTDIR}/_ext/1344097381/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/states.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/states.o.d -o ${OBJECTDIR}/_ext/680170088/states.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/states.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/states.o.d > ${OBJECTDIR}/_ext/680170088/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/states.o.tmp ${OBJECTDIR}/_ext/680170088/states.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/states.o.d > ${OBJECTDIR}/_ext/680170088/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/states.o.tmp ${OBJECTDIR}/_ext/680170088/states.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/main.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/main.o.d -o ${OBJECTDIR}/_ext/680170088/main.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/main.o.d > ${OBJECTDIR}/_ext/680170088/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/main.o.tmp ${OBJECTDIR}/_ext/680170088/main.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/main.o.d > ${OBJECTDIR}/_ext/680170088/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/main.o.tmp ${OBJECTDIR}/_ext/680170088/main.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/telemetry.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/telemetry.o.d -o ${OBJECTDIR}/_ext/680170088/telemetry.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/telemetry.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/telemetry.o.d > ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/telemetry.o.d > ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/deadReckoning.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1344113738/deadReckoning.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/deadReckoning.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d > ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d > ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/background.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/background.o.d -o ${OBJECTDIR}/_ext/1344097381/background.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/background.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/background.o.d > ${OBJECTDIR}/_ext/1344097381/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/background.o.tmp ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/background.o.d > ${OBJECTDIR}/_ext/1344097381/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/background.o.tmp ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/cameraCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/cameraCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/cameraCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d > ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d > ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-waypoints.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/behavior.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/behavior.o.d -o ${OBJECTDIR}/_ext/680170088/behavior.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/behavior.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/behavior.o.d > ${OBJECTDIR}/_ext/680170088/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/behavior.o.d > ${OBJECTDIR}/_ext/680170088/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/rollCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/rollCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/rollCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d > ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d > ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/serialIO_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/serialIO_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/libDCM.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/libDCM.o.d -o ${OBJECTDIR}/_ext/1344113738/libDCM.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/libDCM.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/libDCM.o.d > ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/libDCM.o.d > ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/pitchCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/pitchCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/pitchCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d > ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d > ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/radioIn_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/radioIn_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/flightplan-logo.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/680170088/flightplan-logo.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-logo.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/yawCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/yawCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/yawCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d > ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d > ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/I2C_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/I2C_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/I2C_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp}
endif
else
${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseUBX.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/mathlibNAV.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/mathlibNAV.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/altitudeCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/altitudeCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseCommon.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/servoMix.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/servoMix.o.d -o ${OBJECTDIR}/_ext/680170088/servoMix.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoMix.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/servoMix.o.d > ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/servoMix.o.d > ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp ${OBJECTDIR}/_ext/680170088/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/estYawDrift.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1344113738/estYawDrift.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estYawDrift.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d > ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d > ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/gpsParseSTD.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/libUDB.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/libUDB.o.d -o ${OBJECTDIR}/_ext/1344097381/libUDB.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/libUDB.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/libUDB.o.d > ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/libUDB.o.d > ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp ${OBJECTDIR}/_ext/1344097381/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/libUDB.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/navigate.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/navigate.o.d -o ${OBJECTDIR}/_ext/680170088/navigate.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/navigate.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/navigate.o.d > ${OBJECTDIR}/_ext/680170088/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/navigate.o.d > ${OBJECTDIR}/_ext/680170088/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp ${OBJECTDIR}/_ext/680170088/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/servoPrepare.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d -o ${OBJECTDIR}/_ext/680170088/servoPrepare.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/servoPrepare.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d > ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d > ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp ${OBJECTDIR}/_ext/680170088/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/mp_osd.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/mp_osd.o.d -o ${OBJECTDIR}/_ext/680170088/mp_osd.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/mp_osd.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/mp_osd.o.d > ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/mp_osd.o.d > ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp ${OBJECTDIR}/_ext/680170088/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/rmat.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/rmat.o.d -o ${OBJECTDIR}/_ext/1344113738/rmat.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/rmat.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/rmat.o.d > ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/rmat.o.d > ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp ${OBJECTDIR}/_ext/1344113738/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/estWind.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/estWind.o.d -o ${OBJECTDIR}/_ext/1344113738/estWind.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/estWind.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/estWind.o.d > ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/estWind.o.d > ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp ${OBJECTDIR}/_ext/1344113738/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/analog2digital_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/analog2digital_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/analog2digital_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/servoOut_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/servoOut_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/servoOut_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/magneto_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/magneto_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/magneto_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/magneto_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/osd.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/osd.o.d -o ${OBJECTDIR}/_ext/1344097381/osd.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/osd.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/osd.o.d > ${OBJECTDIR}/_ext/1344097381/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/osd.o.d > ${OBJECTDIR}/_ext/1344097381/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp ${OBJECTDIR}/_ext/1344097381/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/osd.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/states.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/states.o.d -o ${OBJECTDIR}/_ext/680170088/states.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/states.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/states.o.d > ${OBJECTDIR}/_ext/680170088/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/states.o.tmp ${OBJECTDIR}/_ext/680170088/states.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/states.o.d > ${OBJECTDIR}/_ext/680170088/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/states.o.tmp ${OBJECTDIR}/_ext/680170088/states.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/states.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/main.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/main.o.d -o ${OBJECTDIR}/_ext/680170088/main.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/main.o.d > ${OBJECTDIR}/_ext/680170088/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/main.o.tmp ${OBJECTDIR}/_ext/680170088/main.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/main.o.d > ${OBJECTDIR}/_ext/680170088/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/main.o.tmp ${OBJECTDIR}/_ext/680170088/main.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/main.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/telemetry.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/telemetry.o.d -o ${OBJECTDIR}/_ext/680170088/telemetry.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/telemetry.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/telemetry.o.d > ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/telemetry.o.d > ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp ${OBJECTDIR}/_ext/680170088/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/deadReckoning.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1344113738/deadReckoning.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/deadReckoning.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d > ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d > ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/deadReckoning.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/background.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/background.o.d -o ${OBJECTDIR}/_ext/1344097381/background.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/background.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/background.o.d > ${OBJECTDIR}/_ext/1344097381/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/background.o.tmp ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/background.o.d > ${OBJECTDIR}/_ext/1344097381/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/background.o.tmp ${OBJECTDIR}/_ext/1344097381/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/background.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/cameraCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/cameraCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/cameraCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d > ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d > ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-waypoints.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/behavior.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/behavior.o.d -o ${OBJECTDIR}/_ext/680170088/behavior.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/behavior.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/behavior.o.d > ${OBJECTDIR}/_ext/680170088/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/behavior.o.d > ${OBJECTDIR}/_ext/680170088/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp ${OBJECTDIR}/_ext/680170088/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/rollCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/rollCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/rollCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d > ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d > ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/serialIO_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/serialIO_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/serialIO_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1344113738/libDCM.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344113738 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344113738/libDCM.o.d -o ${OBJECTDIR}/_ext/1344113738/libDCM.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libDCM/libDCM.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344113738/libDCM.o.d > ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344113738/libDCM.o.d > ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp ${OBJECTDIR}/_ext/1344113738/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1344113738/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/pitchCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/pitchCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/pitchCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d > ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d > ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/radioIn_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/radioIn_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/radioIn_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/flightplan-logo.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/680170088/flightplan-logo.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/flightplan-logo.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d > ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/680170088/yawCntrl.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/680170088 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d -o ${OBJECTDIR}/_ext/680170088/yawCntrl.o /E/Projects/ProPilot/Nav10\ Board/Nav10/ProPilot/yawCntrl.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d > ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d > ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp ${OBJECTDIR}/_ext/680170088/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/680170088/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1344097381/I2C_aspg.o: /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/I2C_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1344097381 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -I"E:/Projects/ProPilot/Nav10 Board/Nav10/ProPilot" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libUDB" -I"E:/Projects/ProPilot/Nav10 Board/Nav10/libDCM" -MMD -MF ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d -o ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o /E/Projects/ProPilot/Nav10\ Board/Nav10/libUDB/I2C_aspg.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1344097381/I2C_aspg.o.tmp}
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ256GP710A  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf ${OBJECTFILES} C:/Program\ Files/Microchip/MPLAB\ C30/lib/libdsp-elf.a     -Wl,--defsym=__MPLAB_BUILD=1,-Tp33FJ256GP710A.gld,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ256GP710A  -o dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf ${OBJECTFILES} C:/Program\ Files/Microchip/MPLAB\ C30/lib/libdsp-elf.a     -Wl,--defsym=__MPLAB_BUILD=1,-Tp33FJ256GP710A.gld
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist
# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
