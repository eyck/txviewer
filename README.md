SCViewer
========

Note: Please be aware that the development has moved to https://github.com/Minres/SCViewer

SCViewer is composed of a set of eclipse plugins to display VCD and transaction streams 
created by the SystemC VCD trace implementation and the SystemC Verification Library (SCV).
For further description of the SCV please refer to 
http://www.accellera.org/activities/committees/systemc-verification.

The viewer is in early alpha stage and not yet ready for production use!

The plugins are structured as follows:
- com.minres.scviewer.database
	the interface defining the API to access the database and the implementation for VCD
- com.minres.scviewer.database.text
	an implementation of the API to read the text files generated by the SCV
	sc_tr_text database
- com.minres.scviewer.database.sqlite
	an implementation of the API to read the files generated by implementation in the
	sc_tr_sqlite project using a SQLite based database
- com.minres.scviewer.database.test
	a some JUnit tests of the 3 back ends
- com.minres.scviewer.ui
	the viewer it self to diplay the transactions and associated views like the
	outline of the DB and the properties of the transaction
- com.minres.scviewer.feature
	the feature combining the plugins above into a somhow usable form
- scv_tr_sqlite
	a C++ project containing the SQLite based SCV database implementation and the scv4tlm 
	socket implementations.
	A simple example (scv_tr_recording_example.cpp) for testig purposes of the database is
	provided. 
	
To build the plugins the Eclipse SDK or PDE can be used. In both cases the Groovy
eclipse plugin (http://groovy.codehaus.org/Eclipse+Plugin or Market) has to be
installed.

TODO
====
- add more tests
- move to feature based product to allow automatic updates
- improve graphics
- catch-up e3 plugin to functionality of e4 product
