# Code naming convention:
* `.h`   - header for .cpp files
* `.cpp` - files containing algorithms to be ported into whatever is handling the hits etc.
* `.cc`  - files for actual implementation (further described below)

# Build instructions:
From the root directory: 
* `make`      - compiles only the src/ code
* `make test` - compiles only the test/ code
* `make all`  - both

# The following is relevant:
* APA 1 and 3 are those currently instrumented with Felix.
* The APA-collection-channel (mod 2560-1600) counts down towards the upstream end and is between 0 and 479 for the above-specified APAs.
* The Scripts starting with "Test" are those which are a ROOT-dependent version of taking in some set of hits and then passing it t the algorithms and making a decision.

# Known Bugs:
* Sometimes, a candidate is issued for a higher hit threshold but not a lower... this is rare but odd...
This is likely a component of the first problem, but cannot account for all of the issues... These issues will likely be manifestly different in the protoDUNE tests/DUNE system since they are live-time, and the aggregation of these things will be different. Have yet to decide exactly how we plan to pass the Candidates to the Module-Level...

# TODOs:
* Focus on the actual nitty-gritty of the BR first though... Therefore the above is being put on hold...
