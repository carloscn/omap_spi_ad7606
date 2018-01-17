/**
 * @file - sitaraif.c
 * lwIP Ethernet interface for Sitara Devices
 *
 */

/**
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/**
 * Copyright (c) 2010 Texas Instruments Incorporated
 *
 * This file is dervied from the "ethernetif.c" skeleton Ethernet network
 * interface driver for lwIP.
 *
 */
#include "src/include/lwip/opt.h"
#include "src/include/lwip/def.h"
#include "src/include/lwip/mem.h"
#include "src/include/lwip/pbuf.h"
#include "src/include/lwip/sys.h"
#include "src/include/lwip/stats.h"
#include "src/include/lwip/snmp.h"
#include "src/include/netif/etharp.h"
#include "src/include/netif/ppp_oe.h"
#include "src/include/lwip/err.h"
#include "ports/am1808/include/netif/sitaraif.h"
#include "ports/am1808/include/arch/cc.h"

/* Sitara DriverLib Header Files required for this interface driver. */
#include "hw_types.h"
#include "emac.h"
#include "mdio.h"
#include "interrupt.h"
#include "lan8710a.h"

/* EMAC Control RAM size in bytes */
#ifndef SIZE_EMAC_CTRL_RAM
#define SIZE_EMAC_CTRL_RAM        0x2000
#endif

/* MDIO input and output frequencies in Hz */
#define MDIO_FREQ_INPUT           75000000
#define MDIO_FREQ_OUTPUT          1000000

#define EMAC_BUF_DESC_OWNER       0x20000000
#define EMAC_BUF_DESC_SOP         0x80000000
#define EMAC_BUF_DESC_EOP         0x40000000
#define EMAC_BUF_DESC_EOQ         0x10000000

#define MAX_TRANSFER_UNIT         1500
#define PBUF_LEN_MAX              MAX_TRANSFER_UNIT

/* Base Addresses */
#define EMAC_CTRL_RAM_0_BASE      0x01E20000
#define EMAC_0_BASE               0x01E23000
#define EMAC_CTRL_0_BASE          0x01E22000
#define MDIO_0_BASE               0x01E24000

#define MAX_RX_PBUF_ALLOC         10
#define MIN_PKT_LEN               60

/* Define those to better describe the network interface. */
#define IFNAME0                  'e'
#define IFNAME1                  'n'

/* EMAC TX Buffer descriptor data structure */
struct emac_tx_bd {
  volatile struct emac_tx_bd *next;
  volatile u32_t bufptr;
  volatile u32_t bufoff_len;
  volatile u32_t flags_pktlen;
  
  /* helper to know which pbuf this tx bd corresponds to */
  volatile struct pbuf *pbuf;
}emac_tx_bd;

/* EMAC RX Buffer descriptor data structure */
struct emac_rx_bd {
  volatile struct emac_rx_bd *next;
  volatile u32_t bufptr;
  volatile u32_t bufoff_len;
  volatile u32_t flags_pktlen;

  /* helper to know which pbuf this rx bd corresponds to */
  volatile struct pbuf *pbuf;
}emac_rx_bd;

/**
 * Helper struct to hold the data used to operate on a particular 
 * receive channel 
 */
struct rxch {
  volatile struct emac_rx_bd *free_head;
  volatile struct emac_rx_bd *active_head;
  volatile struct emac_rx_bd *active_tail;
  u32_t freed_pbuf_len;
}rxch;

/**
 * Helper struct to hold the data used to operate on a particular 
 * transmit channel 
 */
struct txch {
  volatile struct emac_tx_bd *free_head;
  volatile struct emac_tx_bd *active_tail;
  volatile struct emac_tx_bd *next_bd_to_process;
}txch;
 
/**
 * Helper struct to hold private data used to operate the ethernet interface.
 */
struct sitaraif {
  /* emac instance number */
  u32_t inst_num;

  u8_t mac_addr[6];

  /* emac base address */
  u32_t emac_base;

  /* emac controller base address */
  volatile u32_t emac_ctrl_base;
  volatile u32_t emac_ctrl_ram;

  /* mdio base address */
  volatile u32_t mdio_base;

  /* phy parameters for this instance - for future use */
  u32_t phy_addr;
  u32_t (*phy_autoneg)(u32_t, u32_t, u16_t);
  u32_t (*phy_partnerability)(u32_t, u32_t, u16_t*);
 
  /* The tx/rx channels for the interface */
  struct txch txch;
  struct rxch rxch;
}sitaraif;


/* Defining interface for all the emac instances */
static struct sitaraif sitaraif_data[MAX_EMAC_INSTANCE];

/**
* Function to set the MAC address to the interface
* @param   inst_num the instance number 
* @return  none. 
*/
void 
sitaraif_macaddrset(u32_t inst_num, u8_t *mac_addr) {
  struct sitaraif *sitaraif;
  u32_t temp;

  sitaraif = &sitaraif_data[inst_num];
  
  /* set MAC hardware address */
  for(temp = 0; temp < ETHARP_HWADDR_LEN; temp++) {
    sitaraif->mac_addr[temp] = mac_addr[(ETHARP_HWADDR_LEN - 1) - temp];
  }
}

/**
* Function to setup the instance parameters inside the interface
* @param   sitaraif
* @return  none. 
*/
static void 
sitaraif_inst_config(struct sitaraif *sitaraif) {
  if(sitaraif->inst_num == 0) {
    sitaraif->emac_base = EMAC_0_BASE;
    sitaraif->emac_ctrl_base = EMAC_CTRL_0_BASE;
    sitaraif->emac_ctrl_ram = EMAC_CTRL_RAM_0_BASE;
    sitaraif->mdio_base = MDIO_0_BASE;
#if defined(lcdkOMAPL138) || defined(lcdkC6748)
    sitaraif->phy_addr = 7;
#else
    sitaraif->phy_addr = 0;
#endif
    sitaraif->phy_autoneg = Lan8710aAutoNegotiate;
    sitaraif->phy_partnerability = Lan8710aPartnerAbilityGet;
  }
}

/**
* Function to setup the link. AutoNegotiates with the phy for link
* setup and set the EMAC with the result of autonegotiation. 
* @param  sitaraif
* @return ERR_OK if everything passed
*         others if not passed
*/
static err_t 
sitaraif_link_setup(struct sitaraif *sitaraif) {
  err_t linkstat = ERR_CONN;
  u16_t partnr_ablty;
  u32_t phyduplex = EMAC_DUPLEX_HALF;
  volatile unsigned int delay = 0xFFFFF;

  if(sitaraif->inst_num == 0) {
    if(Lan8710aAutoNegotiate(sitaraif->mdio_base, sitaraif->phy_addr,
                             (LAN8710A_100BTX | LAN8710A_100BTX_FD
                              | LAN8710A_10BT | LAN8710A_10BT_FD)) == TRUE) {
      linkstat = ERR_OK;
      Lan8710aPartnerAbilityGet(sitaraif->mdio_base, sitaraif->phy_addr,
                                &partnr_ablty);
      
      /* Check for 100 Mbps and duplex capability */
      if(partnr_ablty & LAN8710A_100BTX_FD) {
        phyduplex = EMAC_DUPLEX_FULL;
      }
    }
    else {
      linkstat = ERR_CONN;
    }
  }

  else {
    linkstat = ERR_CONN;
  }
 
  /* Set the EMAC with the negotiation results if it is successful */ 
  if(linkstat == ERR_OK) {
    EMACDuplexSet(sitaraif->emac_base, phyduplex); 
  }

  /* Wait for the MII to settle down */
  while(delay--);

  return linkstat;
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf might be
 * chained. That is, one pbuf can span more than one tx buffer descriptors
 *
 * @param sitaraif the network interface state for this ethernetif
 * @param pbuf  the pbuf which is to be sent over EMAC
 * @return None
 */
static void
sitaraif_transmit(struct sitaraif *sitaraif, struct pbuf *pbuf) {
  struct pbuf *q;
  struct txch *txch;
  volatile struct emac_tx_bd *curr_bd, *active_head, *bd_end;

  txch = &(sitaraif->txch);
 
  /* Get the buffer descriptor which is free to transmit */
  curr_bd = txch->free_head;
  
  active_head = curr_bd;
 
  /* Update the total packet length */
  curr_bd->flags_pktlen &= ~0xFFFF;
  curr_bd->flags_pktlen |= pbuf->tot_len;

  /* Indicate the start of the packet */
  curr_bd->flags_pktlen |= (EMAC_BUF_DESC_SOP | EMAC_BUF_DESC_OWNER);

  /* Copy pbuf information into TX buffer descriptors */
  for(q = pbuf; q != NULL; q = q->next) {

    /* Intialize the buffer pointer and length */
    curr_bd->bufptr = (u32_t)(q->payload);
    curr_bd->bufoff_len = (q->len) & 0xFFFF;
    bd_end = curr_bd;
    curr_bd->pbuf = pbuf;
    curr_bd = curr_bd->next;
  }

  /* Indicate the end of the packet */
  bd_end->next = NULL;
  bd_end->flags_pktlen |= EMAC_BUF_DESC_EOP;
 
  txch->free_head = curr_bd;
 
  /* For the first time, write the HDP with the filled bd */
  if(txch->active_tail == NULL) {
    EMACTxHdrDescPtrWrite(sitaraif->emac_base, (unsigned int)(active_head), 0);
  }
 
  /*
   * Chain the bd's. If the DMA engine, already reached the end of the chain, 
   * the EOQ will be set. In that case, the HDP shall be written again.
   */
  else {
    curr_bd = txch->active_tail;
    curr_bd->next = active_head;
    if(curr_bd->flags_pktlen & EMAC_BUF_DESC_EOQ) {
      /* Write the Header Descriptor Pointer and start DMA */
      EMACTxHdrDescPtrWrite(sitaraif->emac_base, (unsigned int)(active_head), 0);
    }
  }

  txch->active_tail = bd_end;
}

/**
 * This function will send a packet through the emac if the channel is 
 * available. Otherwise, the packet will be queued in a pbuf queue.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 */
static err_t
sitaraif_output(struct netif *netif, struct pbuf *p) {
  SYS_ARCH_DECL_PROTECT(lev);

  /**
   * This entire function must run within a "critical section" to preserve
   * the integrity of the transmit pbuf queue.
   *
   */
  SYS_ARCH_PROTECT(lev);

  /* adjust the packet length if less than minimum required */
  if(p->tot_len < MIN_PKT_LEN) {
     p->tot_len = MIN_PKT_LEN;
     p->len = MIN_PKT_LEN;
  }

  /**
   * Bump the reference count on the pbuf to prevent it from being
   * freed till we are done with it.
   *
   */
  pbuf_ref(p);
   
  /* call the actual transmit function */
  sitaraif_transmit(netif->state, p);

  /* Return to prior interrupt state and return. */
  SYS_ARCH_UNPROTECT(lev);
  
  return ERR_OK;
}

/**
 * In this function, the hardware should be initialized.
 * Called from sitaraif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static err_t
sitaraif_hw_init(struct netif *netif)
{
  u32_t temp, channel;
  u32_t num_bd, pbuf_cnt = 0;
#if defined(lcdkOMAPL138) || defined(lcdkC6748)
  volatile u32_t delay = 0xfffff;
#else
  volatile u32_t delay = 0xfff;
#endif
  volatile struct emac_tx_bd *curr_txbd, *last_txbd;
  volatile struct emac_rx_bd *curr_bd, *last_bd;
  struct sitaraif *sitaraif;
  struct txch *txch;
  struct rxch *rxch;
  struct pbuf *p, *q;

  sitaraif = netif->state;

  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  for(temp = 0; temp < ETHARP_HWADDR_LEN; temp++) {
    netif->hwaddr[temp] = sitaraif->mac_addr[(ETHARP_HWADDR_LEN - 1) - temp];
  }

  /* maximum transfer unit */
  netif->mtu = MAX_TRANSFER_UNIT;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

  EMACInit(sitaraif->emac_ctrl_base, sitaraif->emac_base);

  MDIOInit(sitaraif->mdio_base, MDIO_FREQ_INPUT, MDIO_FREQ_OUTPUT);
  while(delay--);
  
  EMACRxBroadCastEnable(sitaraif->emac_base, 0);

  /* Set the MAC Addresses in EMAC hardware */
  EMACMACSrcAddrSet(sitaraif->emac_base, sitaraif->mac_addr);
  
  for(channel = 0; channel < 8; channel++) {
       EMACMACAddrSet(sitaraif->emac_base, channel, sitaraif->mac_addr, EMAC_MACADDR_MATCH);
  }

  if(!((MDIOPhyAliveStatusGet(sitaraif->mdio_base) 
        >> sitaraif->phy_addr) & 0x01 )) {
    return ERR_CONN;
  }

  if(!Lan8710aLinkStatusGet(sitaraif->mdio_base, sitaraif->phy_addr, 10000)) {
      return ERR_CONN;
  }

  if(sitaraif_link_setup(sitaraif) != ERR_OK) {
    return ERR_CONN;
  }  

  txch = &(sitaraif->txch);  

  /**
  * Initialize the Descriptor Memory For TX and RX 
  * Only Channel 0 is supported for both TX and RX
  */
  txch->free_head = (volatile struct emac_tx_bd*)(sitaraif->emac_ctrl_ram);
  txch->next_bd_to_process = txch->free_head;
  txch->active_tail = NULL;
 
  /* Set the number of descriptors for the channel */ 
  num_bd = (SIZE_EMAC_CTRL_RAM >> 1) / sizeof(emac_tx_bd);
  
  curr_txbd = txch->free_head;

  /* Initialize all the TX buffer Descriptors */
  while(num_bd--) {
    curr_txbd->next = curr_txbd + 1;
    curr_txbd->flags_pktlen = 0;
    last_txbd = curr_txbd;
    curr_txbd = curr_txbd->next;
  } 
  last_txbd->next = txch->free_head;
  
  /* Initialize the descriptors for the RX channel */
  rxch = &(sitaraif->rxch);
  rxch->active_head = (volatile struct emac_rx_bd*)(curr_txbd + 1);
  
  rxch->free_head = NULL;
  rxch->freed_pbuf_len = 0;
  num_bd = ((SIZE_EMAC_CTRL_RAM >> 1) / sizeof(emac_rx_bd) - 1);
  curr_bd = rxch->active_head;
  last_bd = curr_bd;

  /*
  ** Allocate the pbufs for the maximum count permitted or till the
  ** number of buffer desceriptors expire, which ever is earlier.
  */
  while(pbuf_cnt < MAX_RX_PBUF_ALLOC) {
    p = pbuf_alloc(PBUF_RAW, PBUF_LEN_MAX, PBUF_POOL);
    pbuf_cnt++;
    
    if(p != NULL) {
      /* write the descriptors if there are enough numbers to hold the pbuf*/
      if(((u32_t)pbuf_clen(p)) <= num_bd) {
        for(q = p; q != NULL; q = q->next) {
          curr_bd->bufptr = (u32_t)(q->payload);
          curr_bd->bufoff_len = q->len;
          curr_bd->next = curr_bd + 1;
          curr_bd->flags_pktlen = EMAC_BUF_DESC_OWNER;
          
          /* Save the pbuf */
          curr_bd->pbuf = q;
          last_bd = curr_bd;
          curr_bd = curr_bd->next;
          num_bd--;
        }
      }
    
      /* free the allocated pbuf if no free descriptors are left */
      else {
        pbuf_free(p);
        break;
      }
    }
    else {
      break;
    }
  }

  last_bd->next = NULL;
  rxch->active_tail = last_bd;

  /* Acknowledge receive and transmit interrupts for proper interrupt pulsing*/
  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_RX);
  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_TX);
  
  EMACRxUnicastSet(sitaraif->emac_base, 0);
  EMACNumFreeBufSet(sitaraif->emac_base, 0, 10);
  EMACTxEnable(sitaraif->emac_base);
  EMACRxEnable(sitaraif->emac_base);

  /* Write the RX HDP for channel 0 */
  EMACRxHdrDescPtrWrite(sitaraif->emac_base, (u32_t)rxch->active_head, 0);
  EMACRMIISpeedSet(sitaraif->emac_base, EMAC_RMIISPEED_100MBPS);
  EMACMIIEnable(sitaraif->emac_base); 

  
  /**
  * Enable the Transmission and reception, enable the interrupts for
  * channel 0 and for control core 0
  */
  EMACTxIntPulseEnable(sitaraif->emac_base, sitaraif->emac_ctrl_base, 0, 0);
  EMACRxIntPulseEnable(sitaraif->emac_base, sitaraif->emac_ctrl_base, 0, 0);

  return ERR_OK;
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function sitaraif_hw_init() to do the
 * low level initializations.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
sitaraif_init(struct netif *netif)
{
  /* Get the instance number first */
  unsigned int inst_num = *(unsigned int*)(netif->state);
  struct sitaraif *sitaraif;

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  sitaraif = &sitaraif_data[inst_num];
 
  netif->state = sitaraif;
  
  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
  */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 10000000);


  sitaraif->inst_num = inst_num;

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;

  netif->num = (u8_t)inst_num;

  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) 
   */
  netif->output = etharp_output;
  netif->linkoutput = sitaraif_output;

  /* initialize the hardware */
  sitaraif_inst_config(sitaraif);

  return (sitaraif_hw_init(netif));
}

/**
 * Handler for Receive interrupt. Packet processing is done in this
 * interrupt handler itself. 
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return none
 */
void
sitaraif_rx_inthandler(struct netif *netif) {
  struct sitaraif *sitaraif;
  struct rxch *rxch;
  volatile struct emac_rx_bd *curr_bd, *processed_bd, *curr_tail, *last_bd;
  volatile struct pbuf *pbuf, *q, *new_pbuf;
  u32_t ex_len = 0, len_to_alloc = 0;
  u16_t tot_len; 
 
  sitaraif = netif->state;
  rxch = &(sitaraif->rxch);

  /* Get the bd which contains the earliest filled data */ 
  curr_bd = rxch->active_head;
  last_bd = rxch->active_tail;
  
  /**
   * Process the descriptors as long as data is available
   * when the DMA is receiving data, SOP flag will be set
  */
  while(curr_bd->flags_pktlen & EMAC_BUF_DESC_SOP) {
    ex_len = 0;
    len_to_alloc = 0;

    /* Start processing once the packet is loaded */
    if((curr_bd->flags_pktlen & EMAC_BUF_DESC_OWNER)
       != EMAC_BUF_DESC_OWNER) {
 
      if(rxch->free_head == NULL) {
        /* this bd chain will be freed after processing */
        rxch->free_head = curr_bd;     
      }
     
      /* Get the total length of the packet. curr_bd points to the start
       * of the packet.
       */ 
      tot_len = (curr_bd->flags_pktlen) & 0xFFFF;

      /* Get the start of the pbuf queue */
      q = curr_bd->pbuf;
 
      do { 
        /* Get the pbuf pointer which is associated with the current bd */
        pbuf = curr_bd->pbuf;
        
        /* If the earlier pbuf ended, update the chain */ 
        if(pbuf->next == NULL) {
          pbuf->next = (struct pbuf*)(curr_bd->next)->pbuf; 
        }  
       
        len_to_alloc += pbuf->len;
        /* Update the len and tot_len fields for the pbuf in the chain*/
        pbuf->len = (curr_bd->bufoff_len) & 0xFFFF;
        pbuf->tot_len = tot_len - ex_len ;
        processed_bd = curr_bd;
        ex_len += pbuf->len;
        curr_bd = curr_bd->next;
      } while((processed_bd->flags_pktlen & EMAC_BUF_DESC_EOP)
              != EMAC_BUF_DESC_EOP);

      /**
       * Close the chain for this pbuf. A full packet is received in 
       * this pbuf chain. Now this pbuf can be given to upper layers for 
       * processing. The start of the pbuf chain is now 'q'.
      */
      pbuf->next = NULL;
  
      /* Adjust the link statistics */
      LINK_STATS_INC(link.recv);

      /* Process the packet */
      if(ethernet_input((struct pbuf *)q, netif) != ERR_OK) {
        /* Adjust the link statistics */
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
      }

      /* Acknowledge that this packet is processed */
      EMACRxCPWrite(sitaraif->emac_base, 0, (unsigned int)processed_bd);

      rxch->active_head = curr_bd;
   
      /**
       * The earlier pbuf chain is freed from the upper layer. So, we need to
       * allocate a new pbuf chain and update the descriptors with the pbuf info.
       * To support chaining, the total length freed by the upper layer is tracked.
       * Care should be taken even if the allocation fails.
       */   
      /**
       * now len_to_alloc will contain the length of the pbuf which was freed
       * from the upper layer
       */
      rxch->freed_pbuf_len += len_to_alloc;  
      new_pbuf = pbuf_alloc(PBUF_RAW, (rxch->freed_pbuf_len), PBUF_POOL);

      /* Write the descriptors with the pbuf info till either of them expires */
      if(new_pbuf != NULL) {
        curr_bd = rxch->free_head;

        for(q = new_pbuf; (q != NULL) && (curr_bd != rxch->active_head); q = q->next) {
          curr_bd->bufptr = (u32_t)(q->payload);
          
          /* no support for buf_offset. RXBUFFEROFFEST register is 0 */
          curr_bd->bufoff_len = (q->len) & 0xFFFF;
          curr_bd->flags_pktlen = EMAC_BUF_DESC_OWNER;
          
          rxch->freed_pbuf_len -= q->len;
         
          /* Save the pbuf */
          curr_bd->pbuf = q;
          last_bd = curr_bd;
          curr_bd = curr_bd->next;
        }
         
        /**
         * At this point either pbuf expired or no rxbd to allocate. If 
         * there are no, enough rx bds to allocate all pbufs in the chain,
         * free the rest of the pbuf
         */
        if(q != NULL) {
          pbuf_free((struct pbuf *)q);
        }
       
        curr_tail = rxch->active_tail; 
        last_bd->next = NULL;
       
        curr_tail->next = rxch->free_head; 
        
        /**
         * Check if the reception has ended. If the EOQ flag is set, the NULL
         * Pointer is taken by the DMA engine. So we need to write the RX HDP
         * with the next descriptor.
         */
        if(curr_tail->flags_pktlen & EMAC_BUF_DESC_EOQ) {
          EMACRxHdrDescPtrWrite(sitaraif->emac_base, (u32_t)(rxch->free_head), 0);
        }

        rxch->free_head  = curr_bd;
        rxch->active_tail = last_bd;
      }
    }
    curr_bd = rxch->active_head;
  }

  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_RX);
  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_TX);
}

/**
 * Handler for EMAC Transmit interrupt
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return none
 */
void
sitaraif_tx_inthandler(struct netif *netif) {
  struct txch *txch;
  struct sitaraif *sitaraif; 
  volatile struct emac_tx_bd *curr_bd, *next_bd_to_process;  
  
  sitaraif = netif->state; 
  txch = &(sitaraif->txch);
    
  next_bd_to_process = txch->next_bd_to_process;
  
  curr_bd = next_bd_to_process;
  
  /* Check for correct start of packet */
  while((curr_bd->flags_pktlen) & EMAC_BUF_DESC_SOP) {
    
    /* Make sure that the transmission is over */
    while((curr_bd->flags_pktlen & EMAC_BUF_DESC_OWNER)
          == EMAC_BUF_DESC_OWNER);
   
    /* Traverse till the end of packet is reached */ 
    while(((curr_bd->flags_pktlen) & EMAC_BUF_DESC_EOP) != EMAC_BUF_DESC_EOP) {
       curr_bd = curr_bd->next;
    }
 
    next_bd_to_process->flags_pktlen &= ~(EMAC_BUF_DESC_SOP);
    curr_bd->flags_pktlen &= ~(EMAC_BUF_DESC_EOP);

    /**
     * If there are no more data transmitted, the next interrupt 
     * shall happen with the pbuf associated with the free_head
     */
    if(curr_bd->next == NULL) {
      txch->next_bd_to_process = txch->free_head;
    }
  
    else {
      txch->next_bd_to_process = curr_bd->next;
    }
    
    /* Acknowledge the EMAC and free the corresponding pbuf */
    EMACTxCPWrite(sitaraif->emac_base, 0, (u32_t)curr_bd);

    pbuf_free((struct pbuf *)curr_bd->pbuf);

    LINK_STATS_INC(link.xmit);
   
    next_bd_to_process = txch->next_bd_to_process;
    curr_bd = next_bd_to_process;
  }

  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_RX);
  EMACCoreIntAck(sitaraif->emac_base, EMAC_INT_CORE0_TX);
}

/**
 * Gets the netif status
 *
 * @param   the netif whoes status to be checked 
 * @return  the status
 */
u32_t
sitaraif_netif_status(struct netif *netif) {
  return (netif_is_up(netif));
}

/**
 * returns the link status
 *
 * @param   the netif whoes link to be checked 
 * @return  the status
 */
u32_t
sitaraif_link_status(struct netif *netif) {

  struct sitaraif *sitaraif = netif->state;

  return (Lan8710aLinkStatusGet(sitaraif->mdio_base,
                                sitaraif->phy_addr,
                                10000));
}


