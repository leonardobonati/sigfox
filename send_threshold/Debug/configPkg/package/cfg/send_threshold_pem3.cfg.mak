# invoke SourceDir generated makefile for send_threshold.pem3
send_threshold.pem3: .libraries,send_threshold.pem3
.libraries,send_threshold.pem3: package/cfg/send_threshold_pem3.xdl
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/send_threshold_CC2650_LAUNCHXL_TI/src/makefile.libs

clean::
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/send_threshold_CC2650_LAUNCHXL_TI/src/makefile.libs clean

