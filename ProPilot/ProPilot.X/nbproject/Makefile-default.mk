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
OBJECTFILES=${OBJECTDIR}/_ext/1472/cameraCntrl.o ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o ${OBJECTDIR}/_ext/1472/servoMix.o ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o ${OBJECTDIR}/_ext/1077454706/FIR_Filter.o ${OBJECTDIR}/_ext/1077454706/libUDB.o ${OBJECTDIR}/_ext/1472/mp_osd.o ${OBJECTDIR}/_ext/1472/MAVLink.o ${OBJECTDIR}/_ext/1472/telemetry.o ${OBJECTDIR}/_ext/1472/pitchCntrl.o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o ${OBJECTDIR}/_ext/1472/servoPrepare.o ${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ${OBJECTDIR}/_ext/1077454706/osd.o ${OBJECTDIR}/_ext/1077471063/estWind.o ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o ${OBJECTDIR}/_ext/1077454706/SuperSample.o ${OBJECTDIR}/_ext/1472/yawCntrl.o ${OBJECTDIR}/_ext/1472/navigate.o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ${OBJECTDIR}/_ext/1077454706/filter_aspg.o ${OBJECTDIR}/_ext/1472/rollCntrl.o ${OBJECTDIR}/_ext/1077471063/rmat.o ${OBJECTDIR}/_ext/2104405722/protocol.o ${OBJECTDIR}/_ext/1077471063/libDCM.o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ${OBJECTDIR}/_ext/1472/states.o ${OBJECTDIR}/_ext/1472/behavior.o ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o ${OBJECTDIR}/_ext/1472/altitudeCntrl.o ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o ${OBJECTDIR}/_ext/1472/flightplan-logo.o ${OBJECTDIR}/_ext/1077454706/averageSample.o ${OBJECTDIR}/_ext/1077454706/background.o ${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o ${OBJECTDIR}/_ext/1077471063/deadReckoning.o


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
# MP_BC is not defined
MP_AS=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-as.exe
MP_LD=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-ld.exe
MP_AR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin\\pic30-ar.exe
# MP_BC is not defined
MP_CC_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
# MP_BC_DIR is not defined
MP_AS_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
MP_LD_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
MP_AR_DIR=C:\\Program\ Files\\Microchip\\MPLAB\ C30\\bin
# MP_BC_DIR is not defined
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
.PHONY: ${OBJECTDIR}/_ext/1077454706/FIR_Filter.o
${OBJECTDIR}/_ext/1077454706/FIR_Filter.o: ../../libUDB/FIR_Filter.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/FIR_Filter.o ../../libUDB/FIR_Filter.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o
${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o: ../../libUDB/filter_aspg_I2C.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o ../../libUDB/filter_aspg_I2C.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/SuperSample.o
${OBJECTDIR}/_ext/1077454706/SuperSample.o: ../../libUDB/SuperSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/SuperSample.o ../../libUDB/SuperSample.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/filter_aspg.o
${OBJECTDIR}/_ext/1077454706/filter_aspg.o: ../../libUDB/filter_aspg.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/filter_aspg.o ../../libUDB/filter_aspg.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/averageSample.o
${OBJECTDIR}/_ext/1077454706/averageSample.o: ../../libUDB/averageSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/averageSample.o ../../libUDB/averageSample.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o
${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o: ../../libUDB/traps_udb_asm.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o ../../libUDB/traps_udb_asm.s  -Wa,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
else
.PHONY: ${OBJECTDIR}/_ext/1077454706/FIR_Filter.o
${OBJECTDIR}/_ext/1077454706/FIR_Filter.o: ../../libUDB/FIR_Filter.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/FIR_Filter.o ../../libUDB/FIR_Filter.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o
${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o: ../../libUDB/filter_aspg_I2C.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/filter_aspg_I2C.o ../../libUDB/filter_aspg_I2C.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/SuperSample.o
${OBJECTDIR}/_ext/1077454706/SuperSample.o: ../../libUDB/SuperSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/SuperSample.o ../../libUDB/SuperSample.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/filter_aspg.o
${OBJECTDIR}/_ext/1077454706/filter_aspg.o: ../../libUDB/filter_aspg.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/filter_aspg.o ../../libUDB/filter_aspg.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/averageSample.o
${OBJECTDIR}/_ext/1077454706/averageSample.o: ../../libUDB/averageSample.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/averageSample.o ../../libUDB/averageSample.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
.PHONY: ${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o
${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o: ../../libUDB/traps_udb_asm.s  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${MP_CC}  -omf=elf -c -mcpu=33FJ256GP710A  -o ${OBJECTDIR}/_ext/1077454706/traps_udb_asm.o ../../libUDB/traps_udb_asm.s  -Wa,--defsym=__MPLAB_BUILD=1,-I"..",-ahlms="$(BINDIR_)$(INFILEBASE).lst"
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/cameraCntrl.o: ../cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/1472/cameraCntrl.o ../cameraCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d > ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d > ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o: ../../libUDB/serialIO_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o ../../libUDB/serialIO_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o: ../../libUDB/eeprom_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o ../../libUDB/eeprom_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/servoMix.o: ../servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/servoMix.o.d -o ${OBJECTDIR}/_ext/1472/servoMix.o ../servoMix.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/servoMix.o.d > ${OBJECTDIR}/_ext/1472/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/servoMix.o.d > ${OBJECTDIR}/_ext/1472/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1472/flightplan-waypoints.o: ../flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o ../flightplan-waypoints.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/libUDB.o: ../../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/libUDB.o.d -o ${OBJECTDIR}/_ext/1077454706/libUDB.o ../../libUDB/libUDB.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/libUDB.o.d > ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/libUDB.o.d > ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp}
endif
${OBJECTDIR}/_ext/1472/mp_osd.o: ../mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/mp_osd.o.d -o ${OBJECTDIR}/_ext/1472/mp_osd.o ../mp_osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/mp_osd.o.d > ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/mp_osd.o.d > ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/1472/MAVLink.o: ../MAVLink.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/MAVLink.o.d -o ${OBJECTDIR}/_ext/1472/MAVLink.o ../MAVLink.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/MAVLink.o.d > ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/MAVLink.o.d > ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp}
endif
${OBJECTDIR}/_ext/1472/telemetry.o: ../telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/telemetry.o.d -o ${OBJECTDIR}/_ext/1472/telemetry.o ../telemetry.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/telemetry.o.d > ${OBJECTDIR}/_ext/1472/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/telemetry.o.d > ${OBJECTDIR}/_ext/1472/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/1472/pitchCntrl.o: ../pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/1472/pitchCntrl.o ../pitchCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d > ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d > ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/mathlibNAV.o: ../../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ../../libDCM/mathlibNAV.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/magneto_aspg.o: ../../libUDB/magneto_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o ../../libUDB/magneto_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o: ../../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ../../libDCM/gpsParseCommon.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o: ../../libUDB/servoOut_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o ../../libUDB/servoOut_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/servoPrepare.o: ../servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/servoPrepare.o.d -o ${OBJECTDIR}/_ext/1472/servoPrepare.o ../servoPrepare.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/servoPrepare.o.d > ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/servoPrepare.o.d > ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/main.o.d -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o: ../../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ../../libDCM/gpsParseUBX.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/osd.o: ../../libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/osd.o.d -o ${OBJECTDIR}/_ext/1077454706/osd.o ../../libUDB/osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/osd.o.d > ${OBJECTDIR}/_ext/1077454706/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/osd.o.d > ${OBJECTDIR}/_ext/1077454706/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/estWind.o: ../../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/estWind.o.d -o ${OBJECTDIR}/_ext/1077471063/estWind.o ../../libDCM/estWind.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/estWind.o.d > ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/estWind.o.d > ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o: ../../libUDB/radioIn_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o ../../libUDB/radioIn_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/yawCntrl.o: ../yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/yawCntrl.o.d -o ${OBJECTDIR}/_ext/1472/yawCntrl.o ../yawCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/yawCntrl.o.d > ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/yawCntrl.o.d > ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1472/navigate.o: ../navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/navigate.o.d -o ${OBJECTDIR}/_ext/1472/navigate.o ../navigate.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/navigate.o.d > ${OBJECTDIR}/_ext/1472/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/navigate.o.tmp ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/navigate.o.d > ${OBJECTDIR}/_ext/1472/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/navigate.o.tmp ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o: ../../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ../../libDCM/gpsParseSTD.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1472/rollCntrl.o: ../rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/rollCntrl.o.d -o ${OBJECTDIR}/_ext/1472/rollCntrl.o ../rollCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/rollCntrl.o.d > ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/rollCntrl.o.d > ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/rmat.o: ../../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/rmat.o.d -o ${OBJECTDIR}/_ext/1077471063/rmat.o ../../libDCM/rmat.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/rmat.o.d > ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/rmat.o.d > ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/2104405722/protocol.o: ../../../Mavlink/include/protocol.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/2104405722 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/2104405722/protocol.o.d -o ${OBJECTDIR}/_ext/2104405722/protocol.o ../../../Mavlink/include/protocol.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/2104405722/protocol.o.d > ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${CP} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/2104405722/protocol.o.d > ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${CP} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/libDCM.o: ../../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/libDCM.o.d -o ${OBJECTDIR}/_ext/1077471063/libDCM.o ../../libDCM/libDCM.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/libDCM.o.d > ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/libDCM.o.d > ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/estYawDrift.o: ../../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ../../libDCM/estYawDrift.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d > ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d > ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/1472/states.o: ../states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/states.o.d -o ${OBJECTDIR}/_ext/1472/states.o ../states.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/states.o.d > ${OBJECTDIR}/_ext/1472/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/states.o.tmp ${OBJECTDIR}/_ext/1472/states.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/states.o.d > ${OBJECTDIR}/_ext/1472/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/states.o.tmp ${OBJECTDIR}/_ext/1472/states.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.tmp}
endif
${OBJECTDIR}/_ext/1472/behavior.o: ../behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/behavior.o.d -o ${OBJECTDIR}/_ext/1472/behavior.o ../behavior.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/behavior.o.d > ${OBJECTDIR}/_ext/1472/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/behavior.o.tmp ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/behavior.o.d > ${OBJECTDIR}/_ext/1472/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/behavior.o.tmp ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o: ../../libUDB/analog2digital_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o ../../libUDB/analog2digital_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/altitudeCntrl.o: ../altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/1472/altitudeCntrl.o ../altitudeCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/I2C_aspg.o: ../../libUDB/I2C_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o ../../libUDB/I2C_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/flightplan-logo.o: ../flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/1472/flightplan-logo.o ../flightplan-logo.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d > ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d > ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/background.o: ../../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/background.o.d -o ${OBJECTDIR}/_ext/1077454706/background.o ../../libUDB/background.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/background.o.d > ${OBJECTDIR}/_ext/1077454706/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/background.o.tmp ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/background.o.d > ${OBJECTDIR}/_ext/1077454706/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/background.o.tmp ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/deadReckoning.o: ../../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1077471063/deadReckoning.o ../../libDCM/deadReckoning.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d > ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d > ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp}
endif
else
${OBJECTDIR}/_ext/1472/cameraCntrl.o: ../cameraCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d -o ${OBJECTDIR}/_ext/1472/cameraCntrl.o ../cameraCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d > ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d > ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp ${OBJECTDIR}/_ext/1472/cameraCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/cameraCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o: ../../libUDB/serialIO_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o ../../libUDB/serialIO_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/serialIO_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o: ../../libUDB/eeprom_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o ../../libUDB/eeprom_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/eeprom_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/servoMix.o: ../servoMix.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/servoMix.o.d -o ${OBJECTDIR}/_ext/1472/servoMix.o ../servoMix.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/servoMix.o.d > ${OBJECTDIR}/_ext/1472/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/servoMix.o.d > ${OBJECTDIR}/_ext/1472/servoMix.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp ${OBJECTDIR}/_ext/1472/servoMix.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoMix.o.tmp}
endif
${OBJECTDIR}/_ext/1472/flightplan-waypoints.o: ../flightplan-waypoints.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d -o ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o ../flightplan-waypoints.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d > ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-waypoints.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/libUDB.o: ../../libUDB/libUDB.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/libUDB.o.d -o ${OBJECTDIR}/_ext/1077454706/libUDB.o ../../libUDB/libUDB.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/libUDB.o.d > ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/libUDB.o.d > ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp ${OBJECTDIR}/_ext/1077454706/libUDB.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/libUDB.o.tmp}
endif
${OBJECTDIR}/_ext/1472/mp_osd.o: ../mp_osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/mp_osd.o.d -o ${OBJECTDIR}/_ext/1472/mp_osd.o ../mp_osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/mp_osd.o.d > ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/mp_osd.o.d > ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp ${OBJECTDIR}/_ext/1472/mp_osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mp_osd.o.tmp}
endif
${OBJECTDIR}/_ext/1472/MAVLink.o: ../MAVLink.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/MAVLink.o.d -o ${OBJECTDIR}/_ext/1472/MAVLink.o ../MAVLink.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/MAVLink.o.d > ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/MAVLink.o.d > ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp ${OBJECTDIR}/_ext/1472/MAVLink.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/MAVLink.o.tmp}
endif
${OBJECTDIR}/_ext/1472/telemetry.o: ../telemetry.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/telemetry.o.d -o ${OBJECTDIR}/_ext/1472/telemetry.o ../telemetry.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/telemetry.o.d > ${OBJECTDIR}/_ext/1472/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/telemetry.o.d > ${OBJECTDIR}/_ext/1472/telemetry.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp ${OBJECTDIR}/_ext/1472/telemetry.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/telemetry.o.tmp}
endif
${OBJECTDIR}/_ext/1472/pitchCntrl.o: ../pitchCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d -o ${OBJECTDIR}/_ext/1472/pitchCntrl.o ../pitchCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d > ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d > ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp ${OBJECTDIR}/_ext/1472/pitchCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/pitchCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/mathlibNAV.o: ../../libDCM/mathlibNAV.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d -o ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o ../../libDCM/mathlibNAV.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d > ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/mathlibNAV.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/magneto_aspg.o: ../../libUDB/magneto_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o ../../libUDB/magneto_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/magneto_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o: ../../libDCM/gpsParseCommon.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o ../../libDCM/gpsParseCommon.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseCommon.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o: ../../libUDB/servoOut_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o ../../libUDB/servoOut_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/servoOut_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/servoPrepare.o: ../servoPrepare.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/servoPrepare.o.d -o ${OBJECTDIR}/_ext/1472/servoPrepare.o ../servoPrepare.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/servoPrepare.o.d > ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/servoPrepare.o.d > ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp ${OBJECTDIR}/_ext/1472/servoPrepare.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/servoPrepare.o.tmp}
endif
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/main.o.d -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o: ../../libDCM/gpsParseUBX.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o ../../libDCM/gpsParseUBX.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseUBX.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/osd.o: ../../libUDB/osd.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/osd.o.d -o ${OBJECTDIR}/_ext/1077454706/osd.o ../../libUDB/osd.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/osd.o.d > ${OBJECTDIR}/_ext/1077454706/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/osd.o.d > ${OBJECTDIR}/_ext/1077454706/osd.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp ${OBJECTDIR}/_ext/1077454706/osd.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/osd.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/estWind.o: ../../libDCM/estWind.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/estWind.o.d -o ${OBJECTDIR}/_ext/1077471063/estWind.o ../../libDCM/estWind.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/estWind.o.d > ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/estWind.o.d > ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp ${OBJECTDIR}/_ext/1077471063/estWind.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estWind.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o: ../../libUDB/radioIn_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o ../../libUDB/radioIn_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/radioIn_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/yawCntrl.o: ../yawCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/yawCntrl.o.d -o ${OBJECTDIR}/_ext/1472/yawCntrl.o ../yawCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/yawCntrl.o.d > ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/yawCntrl.o.d > ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp ${OBJECTDIR}/_ext/1472/yawCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/yawCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1472/navigate.o: ../navigate.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/navigate.o.d -o ${OBJECTDIR}/_ext/1472/navigate.o ../navigate.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/navigate.o.d > ${OBJECTDIR}/_ext/1472/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/navigate.o.tmp ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/navigate.o.d > ${OBJECTDIR}/_ext/1472/navigate.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/navigate.o.tmp ${OBJECTDIR}/_ext/1472/navigate.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/navigate.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o: ../../libDCM/gpsParseSTD.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d -o ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o ../../libDCM/gpsParseSTD.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d > ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/gpsParseSTD.o.tmp}
endif
${OBJECTDIR}/_ext/1472/rollCntrl.o: ../rollCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/rollCntrl.o.d -o ${OBJECTDIR}/_ext/1472/rollCntrl.o ../rollCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/rollCntrl.o.d > ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/rollCntrl.o.d > ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp ${OBJECTDIR}/_ext/1472/rollCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/rollCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/rmat.o: ../../libDCM/rmat.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/rmat.o.d -o ${OBJECTDIR}/_ext/1077471063/rmat.o ../../libDCM/rmat.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/rmat.o.d > ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/rmat.o.d > ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp ${OBJECTDIR}/_ext/1077471063/rmat.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/rmat.o.tmp}
endif
${OBJECTDIR}/_ext/2104405722/protocol.o: ../../../Mavlink/include/protocol.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/2104405722 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/2104405722/protocol.o.d -o ${OBJECTDIR}/_ext/2104405722/protocol.o ../../../Mavlink/include/protocol.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/2104405722/protocol.o.d > ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${CP} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/2104405722/protocol.o.d > ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${CP} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp ${OBJECTDIR}/_ext/2104405722/protocol.o.d 
	${RM} ${OBJECTDIR}/_ext/2104405722/protocol.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/libDCM.o: ../../libDCM/libDCM.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/libDCM.o.d -o ${OBJECTDIR}/_ext/1077471063/libDCM.o ../../libDCM/libDCM.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/libDCM.o.d > ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/libDCM.o.d > ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp ${OBJECTDIR}/_ext/1077471063/libDCM.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/libDCM.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/estYawDrift.o: ../../libDCM/estYawDrift.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d -o ${OBJECTDIR}/_ext/1077471063/estYawDrift.o ../../libDCM/estYawDrift.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d > ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d > ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/estYawDrift.o.tmp}
endif
${OBJECTDIR}/_ext/1472/states.o: ../states.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/states.o.d -o ${OBJECTDIR}/_ext/1472/states.o ../states.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/states.o.d > ${OBJECTDIR}/_ext/1472/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/states.o.tmp ${OBJECTDIR}/_ext/1472/states.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/states.o.d > ${OBJECTDIR}/_ext/1472/states.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/states.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/states.o.tmp ${OBJECTDIR}/_ext/1472/states.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/states.o.tmp}
endif
${OBJECTDIR}/_ext/1472/behavior.o: ../behavior.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/behavior.o.d -o ${OBJECTDIR}/_ext/1472/behavior.o ../behavior.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/behavior.o.d > ${OBJECTDIR}/_ext/1472/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/behavior.o.tmp ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/behavior.o.d > ${OBJECTDIR}/_ext/1472/behavior.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/behavior.o.tmp ${OBJECTDIR}/_ext/1472/behavior.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/behavior.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o: ../../libUDB/analog2digital_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o ../../libUDB/analog2digital_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/analog2digital_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/altitudeCntrl.o: ../altitudeCntrl.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d -o ${OBJECTDIR}/_ext/1472/altitudeCntrl.o ../altitudeCntrl.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d > ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/altitudeCntrl.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/I2C_aspg.o: ../../libUDB/I2C_aspg.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d -o ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o ../../libUDB/I2C_aspg.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d > ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/I2C_aspg.o.tmp}
endif
${OBJECTDIR}/_ext/1472/flightplan-logo.o: ../flightplan-logo.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d -o ${OBJECTDIR}/_ext/1472/flightplan-logo.o ../flightplan-logo.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d > ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d > ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp ${OBJECTDIR}/_ext/1472/flightplan-logo.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/flightplan-logo.o.tmp}
endif
${OBJECTDIR}/_ext/1077454706/background.o: ../../libUDB/background.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077454706 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077454706/background.o.d -o ${OBJECTDIR}/_ext/1077454706/background.o ../../libUDB/background.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077454706/background.o.d > ${OBJECTDIR}/_ext/1077454706/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/background.o.tmp ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077454706/background.o.d > ${OBJECTDIR}/_ext/1077454706/background.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${CP} ${OBJECTDIR}/_ext/1077454706/background.o.tmp ${OBJECTDIR}/_ext/1077454706/background.o.d 
	${RM} ${OBJECTDIR}/_ext/1077454706/background.o.tmp}
endif
${OBJECTDIR}/_ext/1077471063/deadReckoning.o: ../../libDCM/deadReckoning.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1077471063 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ256GP710A -Wall -I".." -I"../../../Mavlink/include" -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I"../../../Mavlink/include/common" -I"../../libUDB" -I"../../libDCM" -MMD -MF ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d -o ${OBJECTDIR}/_ext/1077471063/deadReckoning.o ../../libDCM/deadReckoning.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d > ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d > ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${CP} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.d 
	${RM} ${OBJECTDIR}/_ext/1077471063/deadReckoning.o.tmp}
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ256GP710A  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf ${OBJECTFILES}   C:/Program\ Files/Microchip/MPLAB\ C30/lib/libdsp-elf.a    -Wl,--defsym=__MPLAB_BUILD=1,-L"/C/Program Files/Microchip/MPLAB C30/lib",-L"..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--cref,--warn-section-align,--report-mem,--script=../p33FJ256GP710A.gld,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ256GP710A  -o dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf ${OBJECTFILES}   C:/Program\ Files/Microchip/MPLAB\ C30/lib/libdsp-elf.a    -Wl,--defsym=__MPLAB_BUILD=1,-L"/C/Program Files/Microchip/MPLAB C30/lib",-L"..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--cref,--warn-section-align,--report-mem,--script=../p33FJ256GP710A.gld
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ProPilot.X.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
