/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/02/17 02:28:46 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*t_op	g_op_tab[17] =
{
	name	nb_arg		args				  op_code	cycles				 cod_byte	index

O1	{"live",	1, ( D )     , 						1,	10,		"alive",			0,	0},
O2	{"ld",		2, ( D|I )   , ( R )     , 			2,	5,		"load",				1,	0},c
O3	{"st",		2, ( R )     , ( R|I )   , 			3,	5,		"store",			1,	0},
O4	{"add", 	3, ( R )     , ( R )     , ( R )  , 4,	10,		"addition", 		1,	0},c
O5	{"sub", 	3, ( R )     , ( R )     , ( R )  ,	5,	10,		"soustraction", 	1,	0},c
O6	{"and", 	3, ( R|D|I ) , ( R|D|I ) , ( R )  , 6,	6,		"and", 				1,	0},c
O7	{"or", 		3, ( R|D|I ) , ( R|D|I ) , ( R )  , 7,	6,		"or",				1,	0},c
O8	{"xor", 	3, ( R|D|I ) , ( R|D|I ) , ( R )  , 8,	6,		"xor",				1,	0},c
O9	{"zjmp", 	1, ( D )     , 						9,	20, 	"jump if carry",	0,	1},
Oa	{"ldi", 	3, ( R|D|I ) , ( R|D )   , ( R )  , 10,	25, 	"load index",		1,	1},
ob	{"sti", 	3, ( R )     , ( R|D|I ) , ( R|D ), 11,	25,		"store index",		1,	1},
Oc	{"fork", 	1, ( D )     , 						12,	800,	"fork",				0,	1},
Od	{"lld", 	2, ( D|I )   , ( R )     , 			13,	10,		"long load",		1,	0},c
Oe	{"lldi", 	3, ( R|D|I ) , ( R|D )   , ( R )  , 14,	50,		"lg load index",	1,	1},c
Of	{"lfork", 	1, ( D )     , 						15,	1000,	"long fork",		0,	1},
1O	{"aff", 	1, ( R )     , 						16,	2,		"aff",				1,	0},
	{0, 		0, {0}, 							0, 	0, 		0, 					0, 	0}
};*/
