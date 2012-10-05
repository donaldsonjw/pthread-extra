#TOOLS
BIGLOO = bigloo
BGLAFILE = bglafile
BGLTAGS = bgltags
LD = ld
AR = ar 
RANLIB = ranlib
INSTALL = install
LINK = ln

BIGLOO_VERSION := $(shell $(BIGLOO) -eval "(print *bigloo-version*) (exit 0)" -q)
BIGLOOLIBDIR := $(shell $(BIGLOO) -eval "(print *default-lib-dir*) (exit 0)" -q)

#install related variables
DESTDIR = /usr
INSTLIBDIR = $(DESTDIR)/lib
INSTBIGLOOLIBDIR = $(INSTLIBDIR)/bigloo/$(BIGLOO_VERSION)


VERSION = 0.2

#Bigloo Flags
BHEAPFLAGS = -unsafe -q -mkaddheap -mkaddlib -v2 -heap-library pthread-extra

BCOMMONFLAGS = -mkaddlib -fsharing -q \
               -copt '$(CCOMMONFLAGS)'

BSAFEFLAGS = $(BCOMMONFLAGS) -cg -O3 -g 

BUNSAFEFLAGS = $(BCOMMONFLAGS) -O4 -unsafe

#C Flags
CCOMMONFLAGS = -fPIC

# directory variables
OBJDIR = objs
DISTDIR = dist

# sources
BIGLOOSRCS = src/Llib/work-queue.scm src/Llib/rw-lock.scm \
	     src/Llib/semaphore.scm src/Llib/future.scm \
             src/Llib/concurrent_queue.scm src/Llib/actor.scm \
	     src/Llib/barrier.scm src/Llib/threadless_actor.scm \
	     src/Llib/atomics.scm
HEAPSRC = src/Misc/make_lib.scm


# object files

_SRCSWOUTDIR = $(foreach src, $(BIGLOOSRCS), $(notdir $(src)))
_BASEOBJSWOUTDIR = $(_SRCSWOUTDIR:%.scm=%)

SAFEOBJECTS = $(_BASEOBJSWOUTDIR:%=$(OBJDIR)/%_s.o)

UNSAFEOBJECTS = $(_BASEOBJSWOUTDIR:%=$(OBJDIR)/%_u.o)

_ESRCSWOUTDIR = $(foreach src, $(HEAPSRC), $(notdir $(src)))
_EBASEOBJSWOUTDIR = $(_ESRCSWOUTDIR:%.scm=%)

ESAFEOBJECTS = $(_EBASEOBJSWOUTDIR:%=$(OBJDIR)/%_s.o)

EUNSAFEOBJECTS = $(_EBASEOBJSWOUTDIR:%=$(OBJDIR)/%_u.o)


.SUFFIXES:

$(OBJDIR)/%_s.o:src/Llib/%.scm
	$(BIGLOO) -c $(BSAFEFLAGS) -o $@ $^

$(OBJDIR)/%_u.o:src/Llib/%.scm
	$(BIGLOO) -c $(BUNSAFEFLAGS) -o $@ $^



#targets

all: .afile .etags lib recette/testpthreadextra


.afile: $(BIGLOOSRCS)
	$(BGLAFILE) -o $@  $^

.etags: $(BIGLOOSRCS)
	$(BGLTAGS) -o $@ $^

heap: $(DISTDIR)/pthread-extra.heap

$(DISTDIR)/pthread-extra.heap: $(DISTDIR) $(HEAPSRC)
	$(BIGLOO) $(BHEAPFLAGS) $(HEAPSRC)  -addheap $@

$(OBJDIR)/make_lib_s.o:src/Misc/make_lib.scm
	$(BIGLOO) -c $(BSAFEFLAGS) -o $@ $^

$(OBJDIR)/make_lib_u.o:src/Misc/make_lib.scm
	$(BIGLOO) -c $(BUNSAFEFLAGS) -o $@ $^


lib: init heap lib_s lib_u lib_s.a lib_u.a lib_es lib_eu

init: $(DISTDIR)/pthread-extra.init

$(DISTDIR)/pthread-extra.init : src/Misc/pthread-extra.init $(DISTDIR)
	cp $< $(DISTDIR)/


lib_s: $(OBJDIR) $(DISTDIR) $(SAFEOBJECTS)
	$(LD) -G -o $(DISTDIR)/libpthread-extra_s-$(VERSION).so $(SAFEOBJECTS) -lc -lm

lib_s.a : $(OBJDIR) $(DISTDIR) $(SAFEOBJECTS)
	$(AR) rcv $(DISTDIR)/libpthread-extra_s-$(VERSION).a $(SAFEOBJECTS);\
	$(RANLIB) $(DISTDIR)/libpthread-extra_s-$(VERSION).a

lib_es : $(OBJDIR) $(DISTDIR) $(ESAFEOBJECTS)
	$(LD) -G -o $(DISTDIR)/libpthread-extra_es-$(VERSION).so $(ESAFEOBJECTS) -lc -lm

lib_u : $(OBJDIR) $(DISTDIR) $(UNSAFEOBJECTS)
	$(LD) -G -o $(DISTDIR)/libpthread-extra_u-$(VERSION).so $(UNSAFEOBJECTS) -lc -lm

lib_u.a : $(OBJDIR) $(DISTDIR) $(UNSAFEOBJECTS)
	$(AR) qcv $(DISTDIR)/libpthread-extra_u-$(VERSION).a $(SAFEOBJECTS);\
	$(RANLIB) $(DISTDIR)/libpthread-extra_u-$(VERSION).a

lib_eu : $(OBJDIR) $(DISTDIR) $(EUNSAFEOBJECTS)
	$(LD) -G -o $(DISTDIR)/libpthread-extra_eu-$(VERSION).so $(EUNSAFEOBJECTS) -lc -lm


recette/testpthreadextra : recette/testpthreadextra.scm lib 
	$(BIGLOO) -static-all-bigloo $(BUNSAFEFLAGS) -L $(DISTDIR) -o $@ $< 


$(OBJDIR):
	mkdir $@

$(DISTDIR):
	mkdir $@

install: all
	for file in $(DISTDIR)/*; do \
	  $(INSTALL) $$file $(INSTBIGLOOLIBDIR)/`basename $$file`; \
	done; \
	for file in $(DISTDIR)/*.so; do \
	  $(LINK) -s $(INSTBIGLOOLIBDIR)/`basename $$file` $(INSTLIBDIR)/`basename $$file`; \
	done

clean:
	rm -f -r $(OBJDIR);\
	rm -f -r $(DISTDIR);\
	rm -f pthread-extra.heap;\
	rm -f pthread-extra.init;\
	rm -f recette/testpthreadextra



