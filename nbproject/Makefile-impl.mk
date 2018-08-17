#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a pre- and a post- target defined where you can add customization code.
#
# This makefile implements macros and targets common to all configurations.
#
# NOCDDL


# Building and Cleaning subprojects are done by default, but can be controlled with the SUB
# macro. If SUB=no, subprojects will not be built or cleaned. The following macro
# statements set BUILD_SUB-CONF and CLEAN_SUB-CONF to .build-reqprojects-conf
# and .clean-reqprojects-conf unless SUB has the value 'no'
SUB_no=NO
SUBPROJECTS=${SUB_${SUB}}
BUILD_SUBPROJECTS_=.build-subprojects
BUILD_SUBPROJECTS_NO=
BUILD_SUBPROJECTS=${BUILD_SUBPROJECTS_${SUBPROJECTS}}
CLEAN_SUBPROJECTS_=.clean-subprojects
CLEAN_SUBPROJECTS_NO=
CLEAN_SUBPROJECTS=${CLEAN_SUBPROJECTS_${SUBPROJECTS}}


# Project Name
PROJECTNAME=FluvalBLE_Pro.X

# Active Configuration
DEFAULTCONF=BootApp_Blue1100
CONF=${DEFAULTCONF}

# All Configurations
ALLCONFS=default BootApp_Plant500 BootApp_Plant800 BootApp_Plant1000 BootApp_Plant1100 BootApp_Marine500 BootApp_Marine800 BootApp_Marine1000 BootApp_Marine1100 BootApp_NanoMarine BootApp_NanoPlant BootApp_Blue500 BootApp_Blue800 BootApp_Blue1000 BootApp_Blue1100 BootApp_Aquasky600 BootApp_Aquasky900 BootApp_Aquasky1200 BootApp_Aquasky380 BootApp_Aquasky530 BootApp_Aquasky835 BootApp_Aquasky990 BootApp_Aquasky750 BootApp_Aquasky1150 BootApp_Aquasky910 UpgradeApp_Plant500 UpgradeApp_Plant800 UpgradeApp_Plant1000 UpgradeApp_Plant1100 UpgradeApp_Marine500 UpgradeApp_Marine800 UpgradeApp_Marine1000 UpgradeApp_Marine1100 UpgradeApp_Blue500 UpgradeApp_Blue800 UpgradeApp_Blue1000 UpgradeApp_Blue1100 UpgradeApp_NanoMarine UpgradeApp_NanoPlant UpgradeApp_Aquasky600 UpgradeApp_Aquasky900 UpgradeApp_Aquasky1200 UpgradeApp_Aquasky380 UpgradeApp_Aquasky530 UpgradeApp_Aquasky835 UpgradeApp_Aquasky990 UpgradeApp_Aquasky750 UpgradeApp_Aquasky1150 UpgradeApp_Aquasky910 


# build
.build-impl: .build-pre
	${MAKE} -f nbproject/Makefile-${CONF}.mk SUBPROJECTS=${SUBPROJECTS} .build-conf


# clean
.clean-impl: .clean-pre
	${MAKE} -f nbproject/Makefile-${CONF}.mk SUBPROJECTS=${SUBPROJECTS} .clean-conf

# clobber
.clobber-impl: .clobber-pre .depcheck-impl
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=default clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_NanoMarine clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_NanoPlant clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky600 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky900 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky1200 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky380 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky530 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky835 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky990 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky750 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky1150 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky910 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue500 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue800 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue1000 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue1100 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_NanoMarine clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_NanoPlant clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky600 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky900 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky1200 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky380 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky530 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky835 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky990 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky750 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky1150 clean
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky910 clean



# all
.all-impl: .all-pre .depcheck-impl
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=default build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Plant1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Marine1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_NanoMarine build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_NanoPlant build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Blue1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky600 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky900 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky1200 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky380 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky530 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky835 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky990 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky750 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky1150 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=BootApp_Aquasky910 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Plant1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Marine1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue500 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue800 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue1000 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Blue1100 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_NanoMarine build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_NanoPlant build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky600 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky900 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky1200 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky380 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky530 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky835 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky990 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky750 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky1150 build
	    ${MAKE} SUBPROJECTS=${SUBPROJECTS} CONF=UpgradeApp_Aquasky910 build



# dependency checking support
.depcheck-impl:
#	@echo "# This code depends on make tool being used" >.dep.inc
#	@if [ -n "${MAKE_VERSION}" ]; then \
#	    echo "DEPFILES=\$$(wildcard \$$(addsuffix .d, \$${OBJECTFILES}))" >>.dep.inc; \
#	    echo "ifneq (\$${DEPFILES},)" >>.dep.inc; \
#	    echo "include \$${DEPFILES}" >>.dep.inc; \
#	    echo "endif" >>.dep.inc; \
#	else \
#	    echo ".KEEP_STATE:" >>.dep.inc; \
#	    echo ".KEEP_STATE_FILE:.make.state.\$${CONF}" >>.dep.inc; \
#	fi
