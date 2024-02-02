# COSSIM-OMNETv6
This is the OMNETWP files to work COSSIM with OMNET v6.0 and INET 4.4.1. 

<b>Warning: </b> This implementation works only with Ethernet Switches (no micro-routers).

# COSSIM OMNETPP WORKSPACE 

COSSIM OMNETPP WORKSPACE implements a basic demo with 2 simulated nodes which are connected through Ethernet. In addition, it contains all modifications required to extend the functionality of the OMNET++ v6.0 network simulator to work with the COSSIM framework based on INET (version 4.4.1).

## What is contained in the COSSIM OMNET WORKSPACE?

- `INET 4.4.1` version which is required by COSSIM to model real networks. 
- `HLANode` project which interconnects the OMNET++ with the cgem5 through HLA.
- `test` project which contains a basic demo with 2 simulated nodes using Ethernet. 

Please refer to [COSSIM _framework](https://github.com/H2020-COSSIM/COSSIM_framework) repository for more details.


## Build the COSSIM OMNET_WORKSPACE

- Replace the folder `OMNET_WORKSPACE` inside the folder `$HOME/COSSIM/OMNETPP_COSSIM_workspace`.

- Select Project -> Clean -> Clean Projects Selected Below -> Select “INET” -> Select “Start a build immediately” -> Select “Build only the selected projects” -> Press “OK”
- Select Project -> Clean -> Clean Projects Selected Below -> Select “HLANode” & “test” -> Select “Start a build immediately” -> Select “Build only the selected projects” -> Press “OK”

- Create `simulations` folder in HLANode
`mkdir $HOME/COSSIM/OMNETPP_COSSIM_workspace/OMNET_WORKSPACE/HLANode/simulations`

## Using OMNET_WORKSPACE in the context of the COSSIM simulation framework

Please refer to [COSSIM _framework](https://github.com/H2020-COSSIM/COSSIM_framework) repository for all required instructions.

## Licensing

Refer to the [LICENSE](LICENSE) files included. Individual license may be present in different files in the source codes.

## Notes 

This configuration is for 2 gem5 nodes. You may replace the following 3 gem5 script files.
1) script0.rcS (in folder cgem5/configs/boot/COSSIM/script0.rcS)
2) script1.rcS (in folder cgem5/configs/boot/COSSIM/script1.rcS)
3) run.sh      (in folder cgem5/run.sh)
