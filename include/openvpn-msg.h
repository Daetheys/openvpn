/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single TCP/UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2013 Heiko Hund <heiko.hund@sophos.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING included with this
 *  distribution); if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef OPENVPN_MSG_H_
#define OPENVPN_MSG_H_

typedef enum {
  msg_acknowledgement,
  msg_add_address,
  msg_del_address,
  msg_add_route,
  msg_del_route,
  msg_add_dns_cfg,
  msg_del_dns_cfg,
  msg_add_nbt_cfg,
  msg_del_nbt_cfg,
  msg_flush_neighbors
} message_type_t;

typedef struct {
  message_type_t type;
  size_t size;
  int message_id;
} message_header_t;

typedef union {
  struct in_addr ipv4;
  struct in6_addr ipv6;
} inet_address_t;

typedef struct {
  int index;
  char name[256];
} interface_t;

typedef struct {
  message_header_t header;
  short family;
  inet_address_t address;
  int prefix_len;
  interface_t iface;
} address_message_t;

typedef struct {
  message_header_t header;
  short family;
  inet_address_t prefix;
  int prefix_len;
  inet_address_t gateway;
  interface_t iface;
  int metric;
} route_message_t;

typedef struct {
  message_header_t header;
  interface_t iface;
  char domains[512];
  struct in_addr primary_ipv4;
  struct in_addr secondary_ipv4;
  struct in_addr6 primary_ipv6;
  struct in_addr6 secondary_ipv6;
} dns_cfg_message_t;

typedef struct {
  message_header_t header;
  interface_t iface;
  int disable_nbt;
  int nbt_type;
  char scope_id[256];
  struct in_addr primary_nbns;
  struct in_addr secondary_nbns;
} nbt_cfg_message_t;

// TODO: NTP

typedef struct {
  message_header_t header;
  short family;
  interface_t iface;
} flush_neighbors_message_t;

typedef struct {
  message_header_t header;
  int error_number;
} ack_message_t;

#endif
