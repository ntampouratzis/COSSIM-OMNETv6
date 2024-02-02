/* ----------------------------------------------------------------------------
 * COSSIM - HLANode
 * Copyright (c) 2018, H2020 COSSIM.
 * Copyright (c) 2018, Telecommunications Systems Institute.
 * 
 * Author: Nikolaos Tampouratzis, ntampouratzis@isc.tuc.gr
 * ----------------------------------------------------------------------------
 *
*/

#ifndef __HLA_NODE_TCX_H
#define __HLA_NODE_TCX_H
#define DEBUG_MSG
//#define NO_HLA


#include <typeinfo>
#include <omnetpp.h>
#include <inttypes.h>


#include <inet/common/Units.h>
#include <inet/linklayer/ethernet/basic/EthernetEncapsulation.h>
#include <inet/linklayer/ethernet/common/EthernetMacHeader_m.h>
#include <inet/linklayer/ethernet/common/Ethernet.h>
#include <inet/linklayer/common/Ieee802Ctrl.h>

#include <inet/common/packet/chunk/Chunk.h>


#include <inet/transportlayer/udp/UdpHeader_m.h>

#include <inet/networklayer/common/IpProtocolId_m.h>

#include <inet/networklayer/ipv4/IcmpHeader.h>
#include <inet/networklayer/ipv4/Ipv4Header_m.h>
#include <inet/networklayer/contract/ipv4/Ipv4Address.h>
#include <inet/networklayer/ipv4/Ipv4.h>
#include <inet/networklayer/arp/ipv4/Arp.h>
#include <inet/networklayer/arp/ipv4/ArpPacket_m.h>
#include<inet/linklayer/ethernet/basic/EthernetMac.h>
#include <inet/linklayer/common/MacAddressTag_m.h>
#include <inet/linklayer/common/FcsMode_m.h>
#include <inet/physicallayer/wired/ethernet/EthernetPhyHeader_m.h>
#include <inet/physicallayer/wired/ethernet/EthernetSignal_m.h>
#include "inet/common/TimeTag_m.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"

#include "inet/physicallayer/wireless/common/signal/WirelessSignal.h"

#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"

#include "inet/protocolelement/checksum/header/CrcHeader_m.h"


#include "inet/linklayer/ieee8022/Ieee8022SnapHeader_m.h"

#include "inet/networklayer/ipv4/IcmpHeader_m.h"

#include "inet/common/Protocol.h"
#include "inet/networklayer/common/L3AddressTag_m.h"

#include "inet/networklayer/common/NetworkInterface.h"


#ifndef NO_HLA
    #include "HLA_OMNET.hh"
#endif

#define MAX_PACKET_LENGTH 2048


#include "myPacket_m.h"

#include <dlfcn.h> //dynamic linking
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

using std::string ;
using std::cout ;
using std::endl ;

#ifdef NO_HLA
class EtherTestPacket{

public:

    uint8_t *data;
    unsigned int length ;

    EtherTestPacket();
};
#endif


namespace HLANode {


class SyncNode : public inet::cSimpleModule
{
public:
  int NUMBER_OF_HLA_NODES;
  int NODE_NO;

  double SYNCH_TIME;

  string federate = "SYNCH_OMNET" ;

#ifndef NO_HLA
  HLA_OMNET * HLAGlobalSynch=0;
#endif

  bool TerminateNormal; //! Terminate from GEM5 !//

    virtual void initialize();
    virtual void HLA_initialization(void);
    virtual void handleMessage(inet::cMessage *msg);

    virtual void HLANodesInitialization(cModule *parent);
    virtual void HLANodesFinalization(cModule *parent);


};


class Txc0 : public inet::cSimpleModule
{
public:
    int NUMBER_OF_HLA_NODES;
    int NODE_NO;

    double RX_PACKET_TIME;

    string federationName;

    string federate = "OMNET" ;

#ifndef NO_HLA
  HLA_OMNET * NODEHLA=0;
#endif

    bool TerminateNormal; //! Terminate from GEM5 !//
    bool L2_Routing= false;
    bool send_packet= false;
    bool TOGGLE= true;

#ifdef DEBUG_MSG
    //----CRC stuff
    #define POLYNOMIAL 0x8408
    unsigned short  crcTable[256];

    virtual void  CRC_Init();
    virtual unsigned short CRC_Calculate(const uint8_t *message, int nBytes);
#endif
    virtual void HLA_initialization(int);
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(inet::cMessage *msg);
    void  setPayloadArray(inet::Ptr<inet::myPacket> msg, uint8_t *payload, int length);
    void  getPayloadArray(const inet::Ptr<const inet::myPacket>  msg, uint8_t *payload, int length);   //const inet::Ptr<const inet::testPacket>
    void sendCopyOf(inet::myPacket* msg);

private:
    inet::Ptr<inet::Ipv4Header> datagram;
    inet::Ptr<inet::IcmpHeader> icmp;


    bool  isSwitch = false;
    inet::b sizeData,sizeIpv4Header , sizeArpHeader, sizeEthHeader , sizePhyHeader;

    long total_bytes_sent=0;
    long total_bytes_received=0;

    unsigned char tmp_src[6];
    unsigned char tmp_dst[6];

    uint8_t  ethertype_dec[2];
    int ethertype=0;
    int snap_local_code=0;
    int tmp_ethertype;

    uint8_t tmp_payload[MAX_PACKET_LENGTH];
    uint8_t total_payload[MAX_PACKET_LENGTH];
    uint8_t from_eth_payload[MAX_PACKET_LENGTH];
    //-----------------------------

    //http://www.tcpipguide.com/free/t_IPDatagramGeneralFormat.htm

    short my_Version; //15 1/2
    inet::B my_IHL; //15 2/2 (Internet Header Length)

    short my_TOS; //16  (Type Of Service)
    inet::B my_Total_Length; //17-18
    uint16_t my_Identification; //19-20

    bool my_Flags_DF;//21: 2/8
    bool my_Flags_MF;//21: 3/8
    uint16_t my_Fragment_Offset; //21: 5/8 -22

    short my_Time_to_Live; //23
    inet::IpProtocolId my_Protocol; //24
    unsigned char my_Header_Checksum[2]; //25-26
    int my_source_ip[4];//27-30
    int my_dest_ip[4];//31-34

};

}; // namespace



#endif
