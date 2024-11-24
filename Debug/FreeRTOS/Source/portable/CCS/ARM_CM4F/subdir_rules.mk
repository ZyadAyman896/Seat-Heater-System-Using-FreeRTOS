################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/Source/portable/CCS/ARM_CM4F/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/GPTM" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/Common" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/GPIO" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/UART" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/FreeRTOS/Source/include" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/Source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/Source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS/Source/portable/CCS/ARM_CM4F/%.obj: ../FreeRTOS/Source/portable/CCS/ARM_CM4F/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/GPTM" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/Common" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/GPIO" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/MCAL/UART" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/FreeRTOS/Source/include" --include_path="F:/COURSES/EMBEDDED SYSTEMS/Advanced Embedded Tarek/CODES/FreeRTOS_Project__Final/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/ccs1271/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/Source/portable/CCS/ARM_CM4F/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/Source/portable/CCS/ARM_CM4F" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


