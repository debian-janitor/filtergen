/* iptables-save syntax tree data structure definitions
 *
 * Copyright (c) 2003,2004 Jamie Wilkinson <jaq@spacepants.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __IPTABLES_AST_H__
#define __IPTABLES_AST_H__

struct pkt_count_s {
    char * in;
    char * out;
};

struct not_identifier_s {
    int neg;
    struct identifier_s * identifier;
};

struct option_s {
    char * option;
    struct not_identifier_s * not_identifier;
};

struct not_option_s {
    int neg;
    struct option_s * option;
};
    
struct option_list_s {
    struct option_list_s * option_list;
    struct not_option_s * not_option;
};

struct rule_s {
    int type;
    char * identifier;
    struct pkt_count_s * pkt_count;
    struct option_list_s * option_list;
};

struct rule_list_s {
    struct rule_list_s * list;
    struct rule_s * rule;
};

struct ast_s {
    struct rule_list_s * list;
};

#endif /* __IPTABLES_AST_H__ */
