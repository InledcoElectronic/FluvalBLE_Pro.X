#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-BootApp_Marine1000.mk)" "nbproject/Makefile-local-BootApp_Marine1000.mk"
include nbproject/Makefile-local-BootApp_Marine1000.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=BootApp_Marine1000
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/drv_tmr.c src/drv_pwm.c src/drv_eeprom.c src/drv_eusart.c src/app_key.c src/app_rtc.c src/app_util.c src/app_ble.c src/app_led.c src/app_main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/drv_tmr.p1 ${OBJECTDIR}/src/drv_pwm.p1 ${OBJECTDIR}/src/drv_eeprom.p1 ${OBJECTDIR}/src/drv_eusart.p1 ${OBJECTDIR}/src/app_key.p1 ${OBJECTDIR}/src/app_rtc.p1 ${OBJECTDIR}/src/app_util.p1 ${OBJECTDIR}/src/app_ble.p1 ${OBJECTDIR}/src/app_led.p1 ${OBJECTDIR}/src/app_main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/drv_tmr.p1.d ${OBJECTDIR}/src/drv_pwm.p1.d ${OBJECTDIR}/src/drv_eeprom.p1.d ${OBJECTDIR}/src/drv_eusart.p1.d ${OBJECTDIR}/src/app_key.p1.d ${OBJECTDIR}/src/app_rtc.p1.d ${OBJECTDIR}/src/app_util.p1.d ${OBJECTDIR}/src/app_ble.p1.d ${OBJECTDIR}/src/app_led.p1.d ${OBJECTDIR}/src/app_main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/drv_tmr.p1 ${OBJECTDIR}/src/drv_pwm.p1 ${OBJECTDIR}/src/drv_eeprom.p1 ${OBJECTDIR}/src/drv_eusart.p1 ${OBJECTDIR}/src/app_key.p1 ${OBJECTDIR}/src/app_rtc.p1 ${OBJECTDIR}/src/app_util.p1 ${OBJECTDIR}/src/app_ble.p1 ${OBJECTDIR}/src/app_led.p1 ${OBJECTDIR}/src/app_main.p1

# Source Files
SOURCEFILES=src/drv_tmr.c src/drv_pwm.c src/drv_eeprom.c src/drv_eusart.c src/app_key.c src/app_rtc.c src/app_util.c src/app_ble.c src/app_led.c src/app_main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-BootApp_Marine1000.mk dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F18345
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/drv_tmr.p1: src/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_tmr.p1  src/drv_tmr.c 
	@-${MV} ${OBJECTDIR}/src/drv_tmr.d ${OBJECTDIR}/src/drv_tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_pwm.p1: src/drv_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_pwm.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_pwm.p1  src/drv_pwm.c 
	@-${MV} ${OBJECTDIR}/src/drv_pwm.d ${OBJECTDIR}/src/drv_pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_eeprom.p1: src/drv_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_eeprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_eeprom.p1  src/drv_eeprom.c 
	@-${MV} ${OBJECTDIR}/src/drv_eeprom.d ${OBJECTDIR}/src/drv_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_eusart.p1: src/drv_eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_eusart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_eusart.p1  src/drv_eusart.c 
	@-${MV} ${OBJECTDIR}/src/drv_eusart.d ${OBJECTDIR}/src/drv_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_key.p1: src/app_key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_key.p1.d 
	@${RM} ${OBJECTDIR}/src/app_key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_key.p1  src/app_key.c 
	@-${MV} ${OBJECTDIR}/src/app_key.d ${OBJECTDIR}/src/app_key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_rtc.p1: src/app_rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_rtc.p1.d 
	@${RM} ${OBJECTDIR}/src/app_rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_rtc.p1  src/app_rtc.c 
	@-${MV} ${OBJECTDIR}/src/app_rtc.d ${OBJECTDIR}/src/app_rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_util.p1: src/app_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_util.p1.d 
	@${RM} ${OBJECTDIR}/src/app_util.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_util.p1  src/app_util.c 
	@-${MV} ${OBJECTDIR}/src/app_util.d ${OBJECTDIR}/src/app_util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_ble.p1: src/app_ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_ble.p1.d 
	@${RM} ${OBJECTDIR}/src/app_ble.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_ble.p1  src/app_ble.c 
	@-${MV} ${OBJECTDIR}/src/app_ble.d ${OBJECTDIR}/src/app_ble.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_ble.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_led.p1: src/app_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_led.p1.d 
	@${RM} ${OBJECTDIR}/src/app_led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_led.p1  src/app_led.c 
	@-${MV} ${OBJECTDIR}/src/app_led.d ${OBJECTDIR}/src/app_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_main.p1: src/app_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_main.p1.d 
	@${RM} ${OBJECTDIR}/src/app_main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_main.p1  src/app_main.c 
	@-${MV} ${OBJECTDIR}/src/app_main.d ${OBJECTDIR}/src/app_main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/drv_tmr.p1: src/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_tmr.p1  src/drv_tmr.c 
	@-${MV} ${OBJECTDIR}/src/drv_tmr.d ${OBJECTDIR}/src/drv_tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_pwm.p1: src/drv_pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_pwm.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_pwm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_pwm.p1  src/drv_pwm.c 
	@-${MV} ${OBJECTDIR}/src/drv_pwm.d ${OBJECTDIR}/src/drv_pwm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_pwm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_eeprom.p1: src/drv_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_eeprom.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_eeprom.p1  src/drv_eeprom.c 
	@-${MV} ${OBJECTDIR}/src/drv_eeprom.d ${OBJECTDIR}/src/drv_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/drv_eusart.p1: src/drv_eusart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/drv_eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/drv_eusart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/drv_eusart.p1  src/drv_eusart.c 
	@-${MV} ${OBJECTDIR}/src/drv_eusart.d ${OBJECTDIR}/src/drv_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/drv_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_key.p1: src/app_key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_key.p1.d 
	@${RM} ${OBJECTDIR}/src/app_key.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_key.p1  src/app_key.c 
	@-${MV} ${OBJECTDIR}/src/app_key.d ${OBJECTDIR}/src/app_key.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_key.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_rtc.p1: src/app_rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_rtc.p1.d 
	@${RM} ${OBJECTDIR}/src/app_rtc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_rtc.p1  src/app_rtc.c 
	@-${MV} ${OBJECTDIR}/src/app_rtc.d ${OBJECTDIR}/src/app_rtc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_rtc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_util.p1: src/app_util.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_util.p1.d 
	@${RM} ${OBJECTDIR}/src/app_util.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_util.p1  src/app_util.c 
	@-${MV} ${OBJECTDIR}/src/app_util.d ${OBJECTDIR}/src/app_util.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_util.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_ble.p1: src/app_ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_ble.p1.d 
	@${RM} ${OBJECTDIR}/src/app_ble.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_ble.p1  src/app_ble.c 
	@-${MV} ${OBJECTDIR}/src/app_ble.d ${OBJECTDIR}/src/app_ble.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_ble.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_led.p1: src/app_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_led.p1.d 
	@${RM} ${OBJECTDIR}/src/app_led.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_led.p1  src/app_led.c 
	@-${MV} ${OBJECTDIR}/src/app_led.d ${OBJECTDIR}/src/app_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/app_main.p1: src/app_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_main.p1.d 
	@${RM} ${OBJECTDIR}/src/app_main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/app_main.p1  src/app_main.c 
	@-${MV} ${OBJECTDIR}/src/app_main.d ${OBJECTDIR}/src/app_main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/app_main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../BleBootloader.X/dist/default/production/BleBootloader.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.map  --double=24 --float=24 --rom=default,-1FE0-1FFF --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=pro -DLIGHT_TYPE=LIGHT_TYPE_MARINE_REEF_1000 -DLIGHT_ID=LIGHT_ID_MARINE_REEF_1000 -P -N255 --warn=-3 --asmlist -DXPRJ_BootApp_Marine1000=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --fill=0x3F55@8191:8191 --codeoffset=400 --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,+download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	@echo "Creating unified hex file"
	@"D:/Program Files/Microchip/MPLABX/v4.15/mplab_ide/platform/../mplab_ide/modules/../../bin/hexmate" --edf="D:/Program Files/Microchip/MPLABX/v4.15/mplab_ide/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/FluvalBLE_Pro.X.${IMAGE_TYPE}.hex ../BleBootloader.X/dist/default/production/BleBootloader.X.production.hex -odist/${CND_CONF}/production/FluvalBLE_Pro.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd /D ../BleBootloader.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd /D ../BleBootloader.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd /D ../BleBootloader.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/BootApp_Marine1000
	${RM} -r dist/BootApp_Marine1000

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
