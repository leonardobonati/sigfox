# invoke SourceDir generated makefile for sigfox.pem3
sigfox.pem3: .libraries,sigfox.pem3
.libraries,sigfox.pem3: package/cfg/sigfox_pem3.xdl
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI/src/makefile.libs

clean::
	$(MAKE) -f /Users/Leonardo/TI_workspace_v8/sigfox_CC2650_LAUNCHXL_TI/src/makefile.libs clean

