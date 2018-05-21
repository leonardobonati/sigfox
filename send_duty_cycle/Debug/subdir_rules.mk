################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
CC2650_LAUNCHXL.obj: ../CC2650_LAUNCHXL.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="CC2650_LAUNCHXL.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ccfg.obj: ../ccfg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="ccfg.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sigfox.obj: ../sigfox.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI" --include_path="/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="sigfox.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1517723599:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1517723599-inproc

build-1517723599-inproc: ../sigfox.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/Users/Leonardo/ti/xdctools_3_32_00_06_core/xs" --xdcpath="/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/packages;/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC2650F128 -r release -c "/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS" --compileOptions "-mv7M3 --code_state=16 --float_support=vfplib -me --include_path=\"/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI\" --include_path=\"/Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI\" --include_path=\"/Users/Leonardo/ti/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc26xxware_2_24_03_17272\" --include_path=\"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include\" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1517723599 ../sigfox.cfg
configPkg/compiler.opt: build-1517723599
configPkg/: build-1517723599


