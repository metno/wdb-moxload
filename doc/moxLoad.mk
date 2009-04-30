man_MANS = moxLoad.1

moxLoad.1:	doc/moxLoad.man.xml
	$(DOCBOOK) man $<
	
EXTRA_DIST += doc/moxLoad.man.xml
CLEANFILES += moxLoad.1