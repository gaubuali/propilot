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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1788384718/SD-SPI.o ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o ${OBJECTDIR}/_ext/1472/Files.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_descriptors.o ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o ${OBJECTDIR}/_ext/549097302/usb_device.o


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
MP_CC=C:\\MCC18\\bin\\mcc18.exe
MP_AS=C:\\MCC18\\bin\\..\\mpasm\\MPASMWIN.exe
MP_LD=C:\\MCC18\\bin\\mplink.exe
MP_AR=C:\\MCC18\\bin\\mplib.exe
MP_CC_DIR=C:\\MCC18\\bin
MP_AS_DIR=C:\\MCC18\\bin\\..\\mpasm
MP_LD_DIR=C:\\MCC18\\bin
MP_AR_DIR=C:\\MCC18\\bin
# This makefile will use a C preprocessor to generate dependency files
MP_CPP=C:/Program\ Files/Microchip/MPLAB\ X\ IDE/mplab_ide/mplab_ide/modules/../../bin/mplab-cpp
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof

# ------------------------------------------------------------------------------------
# Rules for buildStep: createRevGrep
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
__revgrep__:   nbproject/Makefile-${CND_CONF}.mk
	@echo 'grep -q $$@' > __revgrep__
	@echo 'if [ "$$?" -ne "0" ]; then' >> __revgrep__
	@echo '  exit 0' >> __revgrep__
	@echo 'else' >> __revgrep__
	@echo '  exit 1' >> __revgrep__
	@echo 'fi' >> __revgrep__
	@chmod +x __revgrep__
else
__revgrep__:   nbproject/Makefile-${CND_CONF}.mk
	@echo 'grep -q $$@' > __revgrep__
	@echo 'if [ "$$?" -ne "0" ]; then' >> __revgrep__
	@echo '  exit 0' >> __revgrep__
	@echo 'else' >> __revgrep__
	@echo '  exit 1' >> __revgrep__
	@echo 'fi' >> __revgrep__
	@chmod +x __revgrep__
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1788384718/SD-SPI.o: ../../../Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1788384718 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1788384718/SD-SPI.o ../../../Microchip/MDD\ File\ System/SD-SPI.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp ../../../Microchip/MDD\ File\ System/SD-SPI.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1788384718 > ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
else
	cat ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp >> ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1589469833/usb_function_msd.o: ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1589469833 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1589469833 > ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
else
	cat ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp >> ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/Files.o: ../Files.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/Files.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Files.o ../Files.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/Files.o.temp ../Files.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/Files.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/Files.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/Files.o.d
else
	cat ${OBJECTDIR}/_ext/1472/Files.o.temp >> ${OBJECTDIR}/_ext/1472/Files.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o ../main.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/main.o.temp ../main.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/main.o.d
else
	cat ${OBJECTDIR}/_ext/1472/main.o.temp >> ${OBJECTDIR}/_ext/1472/main.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/usb_descriptors.o ../usb_descriptors.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp ../usb_descriptors.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
else
	cat ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp >> ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/382171365/usb_function_cdc.o: ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/382171365 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/382171365 > ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
else
	cat ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp >> ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o: ../../../Microchip/MDD\ File\ System/Internal\ Flash.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1788384718 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o ../../../Microchip/MDD\ File\ System/Internal\ Flash.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp ../../../Microchip/MDD\ File\ System/Internal\ Flash.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1788384718 > ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
else
	cat ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp >> ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/549097302/usb_device.o: ../../../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/549097302/usb_device.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/549097302 
	${MP_CC}  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/549097302/usb_device.o ../../../Microchip/USB/usb_device.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/549097302/usb_device.o.temp ../../../Microchip/USB/usb_device.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/549097302 > ${OBJECTDIR}/_ext/549097302/usb_device.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/549097302/usb_device.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/549097302/usb_device.o.d
else
	cat ${OBJECTDIR}/_ext/549097302/usb_device.o.temp >> ${OBJECTDIR}/_ext/549097302/usb_device.o.d
endif
	${RM} __temp_cpp_output__
else
${OBJECTDIR}/_ext/1788384718/SD-SPI.o: ../../../Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1788384718 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1788384718/SD-SPI.o ../../../Microchip/MDD\ File\ System/SD-SPI.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp ../../../Microchip/MDD\ File\ System/SD-SPI.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1788384718 > ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
else
	cat ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.temp >> ${OBJECTDIR}/_ext/1788384718/SD-SPI.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1589469833/usb_function_msd.o: ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1589469833 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp ../../../Microchip/USB/MSD\ Device\ Driver/usb_function_msd.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1589469833 > ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
else
	cat ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.temp >> ${OBJECTDIR}/_ext/1589469833/usb_function_msd.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/Files.o: ../Files.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/Files.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/Files.o ../Files.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/Files.o.temp ../Files.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/Files.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/Files.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/Files.o.d
else
	cat ${OBJECTDIR}/_ext/1472/Files.o.temp >> ${OBJECTDIR}/_ext/1472/Files.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/main.o ../main.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/main.o.temp ../main.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/main.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/main.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/main.o.d
else
	cat ${OBJECTDIR}/_ext/1472/main.o.temp >> ${OBJECTDIR}/_ext/1472/main.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1472/usb_descriptors.o: ../usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/usb_descriptors.o ../usb_descriptors.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp ../usb_descriptors.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1472 > ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
else
	cat ${OBJECTDIR}/_ext/1472/usb_descriptors.o.temp >> ${OBJECTDIR}/_ext/1472/usb_descriptors.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/382171365/usb_function_cdc.o: ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/382171365 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp ../../../Microchip/USB/CDC\ Device\ Driver/usb_function_cdc.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/382171365 > ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
else
	cat ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.temp >> ${OBJECTDIR}/_ext/382171365/usb_function_cdc.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o: ../../../Microchip/MDD\ File\ System/Internal\ Flash.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/1788384718 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o ../../../Microchip/MDD\ File\ System/Internal\ Flash.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp ../../../Microchip/MDD\ File\ System/Internal\ Flash.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/1788384718 > ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
else
	cat ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.temp >> ${OBJECTDIR}/_ext/1788384718/Internal\ Flash.o.d
endif
	${RM} __temp_cpp_output__
${OBJECTDIR}/_ext/549097302/usb_device.o: ../../../Microchip/USB/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	${RM} ${OBJECTDIR}/_ext/549097302/usb_device.o.d 
	${MKDIR} ${OBJECTDIR}/_ext/549097302 
	${MP_CC}  -p18F26J50 -I".." -I"../../../Microchip/Include" -I"../../../Microchip/Include/MDD File System" -I"../../../Microchip/Include/USB" -I"../../../Microchip/USB" -I"C:/MCC18/h" -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/549097302/usb_device.o ../../../Microchip/USB/usb_device.c 
	${MP_CPP}  -MMD ${OBJECTDIR}/_ext/549097302/usb_device.o.temp ../../../Microchip/USB/usb_device.c __temp_cpp_output__ -D __18F26J50 -D __18CXX -I E:\\Projects\\DevPFG\\Prog10\\SD\ CDC\ Prog -I E:\\Projects\\DevPFG\\Microchip\\Include -I E:\\Projects\\DevPFG\\Microchip\\Include\\MDD\ File\ System -I E:\\Projects\\DevPFG\\Microchip\\Include\\USB -I E:\\Projects\\DevPFG\\Microchip\\USB -I C:\\MCC18\\h -I C:\\MCC18\\bin/../h  -D__18F26J50
	printf "%s/" ${OBJECTDIR}/_ext/549097302 > ${OBJECTDIR}/_ext/549097302/usb_device.o.d
ifneq (,$(findstring MINGW32,$(OS_CURRENT)))
	cat ${OBJECTDIR}/_ext/549097302/usb_device.o.temp | sed -e 's/\\\ /__SPACES__/g' -e's/\\$$/__EOL__/g' -e 's/\\/\\\\/g' -e 's/__SPACES__/\\\ /g' -e 's/__EOL__/\\/g' >> ${OBJECTDIR}/_ext/549097302/usb_device.o.d
else
	cat ${OBJECTDIR}/_ext/549097302/usb_device.o.temp >> ${OBJECTDIR}/_ext/549097302/usb_device.o.d
endif
	${RM} __temp_cpp_output__
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} ../rm18f26j50_g.lkr   -w -x -m".map" -l"/C/mcc18/lib" -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1  -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof ${OBJECTFILES}     
else
dist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} ../rm18f26j50_g.lkr   -w  -m".map" -l"/C/mcc18/lib" -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -odist/${CND_CONF}/${IMAGE_TYPE}/SD___CDC_PIC18F26J50.X.${IMAGE_TYPE}.cof ${OBJECTFILES}     
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
