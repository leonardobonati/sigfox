# invoke SourceDir generated makefile for send_temperature.pem3
send_temperature.pem3: .libraries,send_temperature.pem3
.libraries,send_temperature.pem3: package/cfg/send_temperature_pem3.xdl
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/send_temperature_CC2650_LAUNCHXL_TI/src/makefile.libs

clean::
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/send_temperature_CC2650_LAUNCHXL_TI/src/makefile.libs clean

