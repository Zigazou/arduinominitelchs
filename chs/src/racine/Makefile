COMPILEVDT=../../../compiler/compilevdt
COMPILECMD=../../../compiler/compilecmd
SRC=$(wildcard *.xml)
VDT=$(SRC:.xml=.vdt)
CMD=$(SRC:.xml=.cmd)

all: $(VDT) $(CMD)

%.vdt: %.xml
	$(COMPILEVDT) $< $@

%.cmd: %.xml
	$(COMPILECMD) $< $@

install:
	cp $(VDT) $(CMD) ../../bin/racine

clean:
	rm -rf *.cmd *.vdt

