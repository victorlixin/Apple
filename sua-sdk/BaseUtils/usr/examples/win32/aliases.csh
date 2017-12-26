#
# Copyright (c) Microsoft Corporation. All rights reserved.
# 
# srcId = $Id: aliases.csh#2 2006/10/31 00:16:38 FAREAST\\rkohad $
#
# Sample aliases file which includes contents of the stock
# WINNT40/system32 directory.

# If WINSYS is already defined, don't change it.
if (!($?WINSYS)) then
	set WINSYS=`ntpath2posix -c $SYSTEMROOT/system32`
endif

alias append `ntpath2posix -c ${WINSYS}/append.exe`
alias arp `ntpath2posix -c ${WINSYS}/ARP.EXE`
alias at `ntpath2posix -c ${WINSYS}/at.exe`
alias attrib `ntpath2posix -c ${WINSYS}/attrib.exe`
alias autochk `ntpath2posix -c ${WINSYS}/autochk.exe`
alias autoconv `ntpath2posix -c ${WINSYS}/autoconv.exe`
alias cacls `ntpath2posix -c ${WINSYS}/cacls.exe`
alias calc `ntpath2posix -c ${WINSYS}/calc.exe`
alias charmap `ntpath2posix -c ${WINSYS}/charmap.exe`
alias chkdsk `ntpath2posix -c ${WINSYS}/chkdsk.exe`
alias cmd `ntpath2posix -c ${WINSYS}/cmd.exe`
alias comp `ntpath2posix -c ${WINSYS}/comp.exe`
alias compact `ntpath2posix -c ${WINSYS}/compact.exe`
alias control `ntpath2posix -c ${WINSYS}/control.exe`
alias convert `ntpath2posix -c ${WINSYS}/convert.exe`
alias dcomcnfg `ntpath2posix -c ${WINSYS}/dcomcnfg.exe`
alias debug `ntpath2posix -c ${WINSYS}/debug.exe`
alias diskperf `ntpath2posix -c ${WINSYS}/diskperf.exe`
alias doskey `ntpath2posix -c ${WINSYS}/doskey.exe`
alias dosx `ntpath2posix -c ${WINSYS}/dosx.exe`
alias drwatson `ntpath2posix -c ${WINSYS}/drwatson.exe`
alias edlin `ntpath2posix -c ${WINSYS}/edlin.exe`
alias eventvwr `ntpath2posix -c ${WINSYS}/eventvwr.exe`
alias exe2bin `ntpath2posix -c ${WINSYS}/exe2bin.exe`
alias fastopen `ntpath2posix -c ${WINSYS}/fastopen.exe`
alias findstr `ntpath2posix -c ${WINSYS}/findstr.exe`
alias finger `ntpath2posix -c ${WINSYS}/finger.exe`
alias fontview `ntpath2posix -c ${WINSYS}/fontview.exe`
alias gdi `ntpath2posix -c ${WINSYS}/gdi.exe`
alias grpconv `ntpath2posix -c ${WINSYS}/grpconv.exe`
alias help `ntpath2posix -c ${WINSYS}/help.exe`
alias hostname `ntpath2posix -c ${WINSYS}/HOSTNAME.EXE`
alias ipconfig `ntpath2posix -c ${WINSYS}/IPCONFIG.EXE`
alias label `ntpath2posix -c ${WINSYS}/label.exe`
alias locator `ntpath2posix -c ${WINSYS}/LOCATOR.EXE`
alias lodctr `ntpath2posix -c ${WINSYS}/lodctr.exe`
alias mem `ntpath2posix -c ${WINSYS}/mem.exe`
alias mscdexnt `ntpath2posix -c ${WINSYS}/mscdexnt.exe`
alias mspaint `ntpath2posix -c ${WINSYS}/mspaint.exe`
alias nbtstat `ntpath2posix -c ${WINSYS}/NBTSTAT.EXE`
alias net1 `ntpath2posix -c ${WINSYS}/net1.exe`
alias net `ntpath2posix -c ${WINSYS}/net.exe`
alias netstat `ntpath2posix -c ${WINSYS}/NETSTAT.EXE`
alias nlsfunc `ntpath2posix -c ${WINSYS}/nlsfunc.exe`
alias notepad `ntpath2posix -c ${WINSYS}/notepad.exe`
alias nslookup `ntpath2posix -c ${WINSYS}/NSLOOKUP.EXE`
alias packager `ntpath2posix -c ${WINSYS}/packager.exe`
alias perfmon `ntpath2posix -c ${WINSYS}/perfmon.exe`
alias rasmon `ntpath2posix -c ${WINSYS}/rasmon.exe`
alias rasphone `ntpath2posix -c ${WINSYS}/rasphone.exe`
alias recover `ntpath2posix -c ${WINSYS}/recover.exe`
alias redir `ntpath2posix -c ${WINSYS}/redir.exe`
alias regedt32 `ntpath2posix -c ${WINSYS}/regedt32.exe`
alias replace `ntpath2posix -c ${WINSYS}/replace.exe`
alias restore `ntpath2posix -c ${WINSYS}/restore.exe`
alias route `ntpath2posix -c ${WINSYS}/ROUTE.EXE`
alias rundll32 `ntpath2posix -c ${WINSYS}/rundll32.exe`
alias runonce `ntpath2posix -c ${WINSYS}/runonce.exe`
alias savedump `ntpath2posix -c ${WINSYS}/savedump.exe`
alias services `ntpath2posix -c ${WINSYS}/services.exe`
alias setver `ntpath2posix -c ${WINSYS}/setver.exe`
alias share `ntpath2posix -c ${WINSYS}/share.exe`
alias subst `ntpath2posix -c ${WINSYS}/subst.exe`
alias sysedit `ntpath2posix -c ${WINSYS}/sysedit.exe`
alias systray `ntpath2posix -c ${WINSYS}/systray.exe`
alias taskman `ntpath2posix -c ${WINSYS}/taskman.exe`
alias taskmgr `ntpath2posix -c ${WINSYS}/taskmgr.exe`
alias tracert `ntpath2posix -c ${WINSYS}/TRACERT.EXE`
alias unlodctr `ntpath2posix -c ${WINSYS}/unlodctr.exe`
alias user `ntpath2posix -c ${WINSYS}/user.exe`
alias userinit `ntpath2posix -c ${WINSYS}/userinit.exe`
alias wexpand `ntpath2posix -c ${WINSYS}/expand.exe`
alias wfc `ntpath2posix -c ${WINSYS}/fc.exe`
alias wfind `ntpath2posix -c ${WINSYS}/find.exe`
alias wftp `ntpath2posix -c ${WINSYS}/FTP.EXE`
alias winspool `ntpath2posix -c ${WINSYS}/winspool.exe`
alias winver `ntpath2posix -c ${WINSYS}/winver.exe`
alias wowdeb `ntpath2posix -c ${WINSYS}/wowdeb.exe`
alias wowexec `ntpath2posix -c ${WINSYS}/wowexec.exe`
alias wping `ntpath2posix -c ${WINSYS}/PING.EXE`
alias wprint `ntpath2posix -c ${WINSYS}/print.exe`
alias wwrite `ntpath2posix -c ${WINSYS}/write.exe`
alias wsort `ntpath2posix -c ${WINSYS}/sort.exe`
alias wtelnet `ntpath2posix -c ${WINSYS}/telnet.exe`
alias xcopy `ntpath2posix -c ${WINSYS}/xcopy.exe`
