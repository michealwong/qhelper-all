.PHONY: all altova altoavxml dsap dsapTest clean

all: dsapTest
	
altova:
	cd Altova && $(MAKE)
	
altovaxml:
	cd AltovaXML && $(MAKE)
	
dsap: altova altovaxml
	cd sap && $(MAKE)
	
dsapTest: dsap
	cd sapTest && $(MAKE)

clean:
	cd Altova && $(MAKE) clean
	cd AltovaXML && $(MAKE) clean
	cd sap && $(MAKE) clean
	cd sapTest && $(MAKE) clean
