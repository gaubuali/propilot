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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/monitor.o ${OBJECTDIR}/_ext/925799516/ccsbcs.o ${OBJECTDIR}/_ext/1472/mmc.o ${OBJECTDIR}/_ext/1472/uart.o ${OBJECTDIR}/_ext/1472/ff.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/main.o.d -o ${OBJECTDIR}/_ext/1472/main.o ../main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
endif
${OBJECTDIR}/_ext/1472/monitor.o: ../monitor.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/monitor.o.d -o ${OBJECTDIR}/_ext/1472/monitor.o ../monitor.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/monitor.o.d > ${OBJECTDIR}/_ext/1472/monitor.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/monitor.o.tmp ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/monitor.o.d > ${OBJECTDIR}/_ext/1472/monitor.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/monitor.o.tmp ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.tmp}
endif
${OBJECTDIR}/_ext/925799516/ccsbcs.o: ../option/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/925799516 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d -o ${OBJECTDIR}/_ext/925799516/ccsbcs.o ../option/ccsbcs.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d > ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${CP} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d > ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${CP} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp}
endif
${OBJECTDIR}/_ext/1472/mmc.o: ../mmc.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/mmc.o.d -o ${OBJECTDIR}/_ext/1472/mmc.o ../mmc.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/mmc.o.d > ${OBJECTDIR}/_ext/1472/mmc.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mmc.o.tmp ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/mmc.o.d > ${OBJECTDIR}/_ext/1472/mmc.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mmc.o.tmp ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.tmp}
endif
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/uart.o.d -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/uart.o.d > ${OBJECTDIR}/_ext/1472/uart.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/uart.o.tmp ${OBJECTDIR}/_ext/1472/uart.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/uart.o.d > ${OBJECTDIR}/_ext/1472/uart.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/uart.o.tmp ${OBJECTDIR}/_ext/1472/uart.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.tmp}
endif
${OBJECTDIR}/_ext/1472/ff.o: ../ff.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${MP_CC} -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/ff.o.d -o ${OBJECTDIR}/_ext/1472/ff.o ../ff.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/ff.o.d > ${OBJECTDIR}/_ext/1472/ff.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/ff.o.tmp ${OBJECTDIR}/_ext/1472/ff.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/ff.o.d > ${OBJECTDIR}/_ext/1472/ff.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/ff.o.tmp ${OBJECTDIR}/_ext/1472/ff.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.tmp}
endif
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/main.o.d -o ${OBJECTDIR}/_ext/1472/main.o ../main.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/main.o.d > ${OBJECTDIR}/_ext/1472/main.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/main.o.tmp ${OBJECTDIR}/_ext/1472/main.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/main.o.tmp}
endif
${OBJECTDIR}/_ext/1472/monitor.o: ../monitor.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/monitor.o.d -o ${OBJECTDIR}/_ext/1472/monitor.o ../monitor.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/monitor.o.d > ${OBJECTDIR}/_ext/1472/monitor.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/monitor.o.tmp ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/monitor.o.d > ${OBJECTDIR}/_ext/1472/monitor.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/monitor.o.tmp ${OBJECTDIR}/_ext/1472/monitor.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/monitor.o.tmp}
endif
${OBJECTDIR}/_ext/925799516/ccsbcs.o: ../option/ccsbcs.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/925799516 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d -o ${OBJECTDIR}/_ext/925799516/ccsbcs.o ../option/ccsbcs.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d > ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${CP} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d > ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${CP} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp ${OBJECTDIR}/_ext/925799516/ccsbcs.o.d 
	${RM} ${OBJECTDIR}/_ext/925799516/ccsbcs.o.tmp}
endif
${OBJECTDIR}/_ext/1472/mmc.o: ../mmc.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/mmc.o.d -o ${OBJECTDIR}/_ext/1472/mmc.o ../mmc.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/mmc.o.d > ${OBJECTDIR}/_ext/1472/mmc.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mmc.o.tmp ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/mmc.o.d > ${OBJECTDIR}/_ext/1472/mmc.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/mmc.o.tmp ${OBJECTDIR}/_ext/1472/mmc.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/mmc.o.tmp}
endif
${OBJECTDIR}/_ext/1472/uart.o: ../uart.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/uart.o.d -o ${OBJECTDIR}/_ext/1472/uart.o ../uart.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/uart.o.d > ${OBJECTDIR}/_ext/1472/uart.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/uart.o.tmp ${OBJECTDIR}/_ext/1472/uart.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/uart.o.d > ${OBJECTDIR}/_ext/1472/uart.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/uart.o.tmp ${OBJECTDIR}/_ext/1472/uart.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/uart.o.tmp}
endif
${OBJECTDIR}/_ext/1472/ff.o: ../ff.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${MP_CC}  -omf=elf -x c -c -mcpu=33FJ128GP802 -Wall -I"/C/Program Files/Microchip/MPLAB C30/support/dsPIC33F/h" -I".." -Os -MMD -MF ${OBJECTDIR}/_ext/1472/ff.o.d -o ${OBJECTDIR}/_ext/1472/ff.o ../ff.c 
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	 sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/ff.o.d > ${OBJECTDIR}/_ext/1472/ff.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/ff.o.tmp ${OBJECTDIR}/_ext/1472/ff.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.tmp}
else 
	 sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/ff.o.d > ${OBJECTDIR}/_ext/1472/ff.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/ff.o.tmp ${OBJECTDIR}/_ext/1472/ff.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/ff.o.tmp}
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ128GP802  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf ${OBJECTFILES}      -Wl,--defsym=__MPLAB_BUILD=1,-Tp33FJ128GP802.gld,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-L"/C/Program Files/Microchip/MPLAB C30/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem
else
dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  -omf=elf  -mcpu=33FJ128GP802  -o dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf ${OBJECTFILES}      -Wl,--defsym=__MPLAB_BUILD=1,-Tp33FJ128GP802.gld,-L"/C/Program Files/Microchip/MPLAB C30/lib",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/picmmc.X.${IMAGE_TYPE}.elf -omf=elf
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
