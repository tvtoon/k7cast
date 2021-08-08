/*
	Copyright 2021 flyinghead

	Rom information from mame (https://github.com/mamedev/mame)
	license:LGPL-2.1+
	copyright-holders: Samuele Zannoli, R. Belmont, ElSemi, David Haywood, Angelo Salese, Olivier Galibert, MetalliC

	This file is part of Flycast.

    Flycast is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Flycast is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Flycast.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "naomi_roms.h"
#include "naomi_roms_eeprom.h"
#include "naomi_roms_input.h"

BIOS_t BIOS[] =
{
	{
		"airlbios",
		{
			{ 2, "epr-21802.ic27", 0x000000, 0x200000 },
			{ 1, "epr-21801.ic27", 0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"awbios",
		{
			{ 0, "bios0.ic23", 0x000000, 0x020000 },
			//or
			//{ "bios1.ic23", 0x000000, 0x020000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"f355bios",
		{
			{ 2, "epr-22851.ic27", 0x000000, 0x200000 },
			{ 1, "epr-22850.ic27", 0x000000, 0x200000 },
			{ 0, "epr-22849.ic27", 0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"f355dlx",
		{
			// Ferrari F355 Deluxe (Export)
			{ 2, "epr-21864.ic27", 0x000000, 0x200000 },
			// Ferrari F355 Deluxe (USA)
			{ 1, "epr-21863.ic27", 0x000000, 0x200000 },
			// Ferrari F355 Deluxe (Japan)
			{ 0, "epr-21862.ic27", 0x000000, 0x200000 },
			// Ferrari F355 Deluxe (Export, prototype)
			//{ 2, "epr-21864p.ic27", 0x000000, 0x200000 },
			// Ferrari F355 Deluxe (Japan, prototype)
			//{ 0, "epr-21862p.ic27", 0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"hod2bios",
		{
            //export
            { 2, "epr-21331.ic27", 0x000000, 0x200000 },
            //usa
            { 1, "epr-21330.ic27", 0x000000, 0x200000 },
            //japan
            { 0, "epr-21329.ic27", 0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"naomi",
		{
			//ROM_SYSTEM_BIOS( 0, "bios0",   "epr-21576h (Japan)" )
			{ 0, "epr-21576h.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 1, "bios1",   "epr-21576g (Japan)" )
			//{ 0, "epr-21576g.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 2, "bios2",   "epr-21576e (Japan)" )
			//{ 0, "epr-21576e.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 3, "bios3",   "epr-21576d (Japan)" )
			//{ 0, "epr-21576d.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 4, "bios4",   "epr-21576c (Japan)" )
			//{ 0, "epr-21576c.ic27", 0x000000, 0x200000 }, // BAD DUMP
			//ROM_SYSTEM_BIOS( 5, "bios5",   "epr-21576b (Japan)" )
			//{ 0, "epr-21576b.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 6, "bios6",   "epr-21576a (Japan)" )
			//{ 0, "epr-21576a.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 7, "bios7",   "epr-21576 (Japan)" )
			//{ 0, "epr-21576.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 8, "bios8",   "epr-21578h (Export)" )
			{ 2, "epr-21578h.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 9, "bios9",   "epr-21578g (Export)" )
			//{ 2, "epr-21578g.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 10, "bios10", "epr-21578f (Export)" )
			//{ 2, "epr-21578f.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 11, "bios11", "epr-21578e (Export)" )
			//{ 2, "epr-21578e.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 12, "bios12", "epr-21578d (Export)" )
			//{ 2, "epr-21578d.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 13, "bios13", "epr-21578a (Export)" )
			//{ 2, "epr-21578a.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 14, "bios14", "epr-21577h (USA)" )
			{ 1, "epr-21577h.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 15, "bios15", "epr-21577g (USA)" )
			//{ 1, "epr-21577g.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 16, "bios16", "epr-21577e (USA)" )
			//{ 1, "epr-21577e.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 17, "bios17", "epr-21577d (USA)" )
			//{ 1, "epr-21577d.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 18, "bios18", "epr-21577a (USA)" )
			//{ 1, "epr-21577a.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 19, "bios19", "epr-21579d (Korea)" )
			{ 3, "epr-21579d.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 20, "bios20", "epr-21579 (Korea)" )
			//{ 3, "epr-21579.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 21, "bios21", "Set4 Dev BIOS" )
			//{ 3, "boot_rom_64b8.ic606", 0x000000, 0x080000 },
			//ROM_SYSTEM_BIOS( 22, "bios22", "Dev BIOS v1.10" )
			//{ 3, "develop110.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 23, "bios23", "Dev BIOS (Nov 1998)" )
			//{ 3, "develop.ic27", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 24, "bios24", "Development ROM Board" )
			//{ 3, "zukinver0930.ic25", 0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 25, "bios25", "epr-21576h (multi-region hack)" )
			//{ 3, "epr-21576h_multi.ic27", 0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		"naomigd",
		{
			//ROM_SYSTEM_BIOS( 0, "bios0", "epr-21576e (Japan)" )
			//{ 0, "epr-21576e.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 1, "bios1", "epr-21576g (Japan)" )
			//{ 0, "epr-21576g.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 2, "bios2", "epr-21576h (Japan)" )
			{ 0, "epr-21576h.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 3, "bios3", "epr-21578h (Export)" )
			{ 2, "epr-21578h.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 4, "bios4", "epr-21578g (Export)" )
			//{ 0, "epr-21578g.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 5, "bios5", "epr-21578e (Export)" )
			//{ 0, "epr-21578e.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 6, "bios6", "epr-21577h (USA)" )
			{ 1, "epr-21577h.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 7, "bios7", "epr-21577g (USA)" )
			//{ 0, "epr-21577g.ic27",  0x000000, 0x200000 },
			//ROM_SYSTEM_BIOS( 8, "bios8", "epr-21577e (USA)" )
			//{ 0, "epr-21577e.ic27",  0x000000, 0x200000 },
			{ 0, NULL, 0, 0 },
		}
	},
	{
		NULL,
	}
};

Game Games[] =
{
    // Naomi M1 Roms
    // Giant Gram 2000 (JPN, USA, EXP, KOR, AUS)
    {
        "gram2000",
        NULL,
        "Giant Gram 2000",
        0x0b000000,
        0x7f805c3f,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23377.ic11",  0x0000000, 0x0400000 },
            { "mpr-23357.ic17s", 0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23358.ic18",  0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23359.ic19s", 0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23360.ic20",  0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23361.ic21s", 0x3000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23362.ic22",  0x3000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23363.ic23s", 0x4000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23364.ic24",  0x4000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23365.ic25s", 0x5000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23366.ic26",  0x5000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23367.ic27s", 0x6000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23368.ic28",  0x6000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23369.ic29",  0x7000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23370.ic30s", 0x7000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23371.ic31",  0x8000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23372.ic32s", 0x8000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23373.ic33",  0x9000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23374.ic34s", 0x9000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23375.ic35",  0xa000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23376.ic36s", 0xa000002, 0x0800000,  0x0000000, InterleavedWord },
            { NULL, 0, 0 },
        },
		nullptr,
        // ATACK, HOLD, THROW, MOVE
        // same as ggram2
    },
    // Kick '4' Cash (Export)
    {
        "kick4csh",
        NULL,
        "Kick '4' Cash (Export)",
        0x9000000,
        0x820857c9,
        "naomi",    // Needs Export BIOS
        M1,
        REGION_EXPORT_ONLY,
        ROT0,
        {
            { "epr-24212.ic11",   0x0000000, 0x400000 },
            { "opr-24213a.ic17s", 0x1000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24214a.ic18",  0x1000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24215a.ic19s", 0x2000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24216a.ic20",  0x2000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24224a.ic21s", 0x3000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24225a.ic22",  0x3000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24226a.ic23s", 0x4000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24227a.ic24",  0x4000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24228a.ic25s", 0x5000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24229a.ic26",  0x5000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24230a.ic27s", 0x6000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24231a.ic28",  0x6000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24232a.ic29",  0x7000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24233a.ic30s", 0x7000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24234a.ic31",  0x8000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24235a.ic32s", 0x8000002, 0x800000,  0x0000000, InterleavedWord },
            { "copy",             0x400000, 0xc00000,  0x0000000, Copy, 0x1000000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //ROM_LOAD( "25lc040.ic13s", 0, 0x200, CRC(1576366a) SHA1(3e8bf3dbc8a248a6863242b78d5c6e53a869e951) )

            // TODO Need emulation of 837-14438 board on serial port
            //ROM_REGION(0x220000, "hopper_board", 0)
            //ROM_LOAD( "fpr-24150.ic6",   0x0000000, 0x200000, CRC(3845c34c) SHA1(027b17bac64482ee152773d5fab30fcbc6e2bcb7) ) // SH4 code
            //ROM_LOAD( "6372a.ic3",       0x0200000, 0x020000, CRC(f30839ad) SHA1(ea1a32c4da1ed9745300bcdd7964a7c0964e3221) ) // FPGA config

            { NULL, 0, 0 },
        },
        NULL,
        NULL,
        kick4csh_eeprom_dump
    },
    // Marvel Vs. Capcom 2 New Age of Heroes (Export, Korea, Rev A)
    {
        "mvsc2",
        NULL,
        "Marvel Vs. Capcom 2 New Age of Heroes (Export, Korea, Rev A)",
        0x08800000,
        0xc18b6e7c,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23085a.ic11", 0x0000000, 0x0400000 },
            { "mpr-23048.ic17s", 0x0800000, 0x0800000 },
            { "mpr-23049.ic18",  0x1000000, 0x0800000 },
            { "mpr-23050.ic19s", 0x1800000, 0x0800000 },
            { "mpr-23051.ic20",  0x2000000, 0x0800000 },
            { "mpr-23052.ic21s", 0x2800000, 0x0800000 },
            { "mpr-23053.ic22",  0x3000000, 0x0800000 },
            { "mpr-23054.ic23s", 0x3800000, 0x0800000 },
            { "mpr-23055.ic24",  0x4000000, 0x0800000 },
            { "mpr-23056.ic25s", 0x4800000, 0x0800000 },
            { "mpr-23057.ic26",  0x5000000, 0x0800000 },
            { "mpr-23058.ic27s", 0x5800000, 0x0800000 },
            { "mpr-23059.ic28",  0x6000000, 0x0800000 },
            { "mpr-23060.ic29",  0x6800000, 0x0800000 },
            { "mpr-23061.ic30s", 0x7000000, 0x0800000 },
            { "mpr-23083.ic31",  0x7800000, 0x0400000 },

            // 32 bit area starts here
            { "mpr-23083.ic31",  0x8000000, 0x0400000,  0x0000000, InterleavedWord },
            { "mpr-23084.ic32s", 0x8000002, 0x0400000,  0x0000000, InterleavedWord },
            { "copy",            0x0400000, 0x0400000,  0x0000000, Copy, 0x1200000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //ROM_LOAD( "25lc040.ic13s", 0x000000, 0x200, CRC(dc449637) SHA1(6cab09f61be1498271a36bff6a114a4eeeb00e1a) )

            { NULL, 0, 0 },
        },
        NULL,
        &mvsc2_inputs
    },
    // Mushiking The King Of Beetle (2K3 2ND, World)
    {
        "mushike",
        NULL,
        "Mushiking The King Of Beetle (2K3 2ND Ver. 1.003-, World)",
        0x4000000,
        0x3892fb3a,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24217.ic11",  0x0000000, 0x0400000 },
            { "mpr-24218.ic17s", 0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24219.ic18",  0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24220.ic19s", 0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24221.ic20",  0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24222.ic21s", 0x3000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24223.ic22",  0x3000002, 0x0800000,  0x0000000, InterleavedWord },
            { "copy",            0x400000,  0xc00000,  0x0000000,  Copy, 0x1000000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //{ "25lc040.ic13s", 0, 0x200, CRC(9adb86c2) SHA1(682d06b2004809c3c7ff2f4f9bc0bde0e51885c0) )

            // MUSHIKING
            // The King of Beetle
            // TYPE-1
            // 800
            // note: this dump from "empty/dead" Management Chip with no game run count left
            //ROM_REGION( 0x80, "rf_tag", 0 )
            //{ "mushi_type1.bin", 0, 0x80, CRC(8f36572b) SHA1(87e00e56d07a961e9180c7da02e35f7fd216dbae) )

            { NULL, 0, 0 },
        }
    },
    // Quiz Ah Megamisama (JPN, USA, EXP, KOR, AUS)
    {
        "qmegamis",
        NULL,
        "Quiz Ah Megamisama",
        0x9000200,
        0xcd9b4896,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23227.ic11",  0x0000000, 0x0400000 },
            { "mpr-23211.ic17s", 0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23212.ic18",  0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23213.ic19s", 0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23214.ic20",  0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23215.ic21s", 0x3000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23216.ic22",  0x3000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23217.ic23s", 0x4000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23218.ic24",  0x4000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23219.ic25s", 0x5000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23220.ic26",  0x5000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23221.ic27s", 0x6000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23222.ic28",  0x6000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23223.ic29",  0x7000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23224.ic30s", 0x7000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23225.ic31",  0x8000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23226.ic32s", 0x8000002, 0x0800000,  0x0000000, InterleavedWord },
            { NULL, 0, 0 },
        }
    },
    // Shootout Pool
    {
        "shootopl",
        NULL,
        "Shootout Pool",
        0x3000000,
        0xa0f37ca7,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23844.ic11",  0x0000000, 0x400000 },
            { "mtp-23840.ic17s", 0x1000000, 0x800000,  0x0000000, InterleavedWord },
            { "mtp-23841.ic18",  0x1000002, 0x800000,  0x0000000, InterleavedWord },
            { "mtp-23842.ic19s", 0x2000000, 0x800000,  0x0000000, InterleavedWord },
            { "mtp-23843.ic20",  0x2000002, 0x800000,  0x0000000, InterleavedWord },
            { "copy",            0x400000, 0xc00000,  0x0000000, Copy, 0x1000000 },
            { NULL, 0, 0 },
        }
        // btn0: TOP VIEW, btn2; START/MODE, up: ZOOM IN, down: ZOOM OUT
        // mouse: TRACK BALL X/Y
        // TODO CUE ROLLER (x8000)
        //      CUE TIP UD (x80h)
        //      CUE TIP LR (x80h)
    },
    // Shootout Pool The Medal / Shootout Pool Prize (Rev A)
    {
        "shootpl",
        NULL,
        "Shootout Pool Prize (Export) / Shootout Pool The Medal (Japan, Rev A)",
        0x3000000,
        0x9dbde9cd,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24065a.ic11", 0x0000000, 0x0400000 },
            { "opr-24060.ic17s", 0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "opr-24061.ic18",  0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "opr-24062.ic19s", 0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "opr-24063.ic20",  0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "copy",            0x400000, 0xc00000,  0x0000000, Copy, 0x1000000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //ROM_LOAD( "25lc040.ic13s", 0, 0x200, CRC(d11312d3) SHA1(c444012954f58a9af283ab8439f31cb89de9c14d) )

            { NULL, 0, 0 },
        }
    },
    // Shootout Pool The Medal Ver. B / Shootout Pool Prize Ver. B
    {
        "shootplm",
        NULL,
        "Shootout Pool Prize (Export) / Shootout Pool The Medal (Japan) Version B",
        0x3000000,
        0x9dbde9cd,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24148.ic11",  0x0000000, 0x400000 },
            { "opr-24174.ic17s", 0x1000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24175.ic18",  0x1000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24176.ic19s", 0x2000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-24177.ic20",  0x2000002, 0x800000,  0x0000000, InterleavedWord },
            { "copy",            0x400000, 0xc00000,  0x0000000, Copy, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Shootout Pool Prize (Export) / Shootout Pool The Medal (Japan) Version B (prototype)
    {
        "shootplmp",
        "shootplm",
        "Shootout Pool Prize (Export) / Shootout Pool The Medal (Japan) Version B (prototype)",
        0x3000000,
        0x9dbde9cd,
        NULL,
        M1,
        REGION_JAPAN,
        ROT0,
        {
            { "rom0.ic22", 0x0000000, 0x400000 },
            { "rom1.ic1s", 0x0800000, 0x800000 },
            { "rom2.ic2s", 0x1000000, 0x800000 },
            { "rom3.ic3s", 0x1800000, 0x800000 },
            { "rom4.ic4s", 0x2000000, 0x800000 },
            // IC5 - IC21 populated, empty.
            { NULL, 0, 0 },
        }
    },

    // Touch de Uno! 2 (Japan)
    {
        "tduno2",
        NULL,
        "Touch de Uno! 2 (Japan)",
        0x4000000,
        0x2f6f0f8d,
        NULL,
        M1,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-23071.ic11",  0x0000000, 0x0200000 },
            { "epr-23071.ic11",  0x0200000, 0x0200000 }, // reload
            { "mpr-23063.ic17s", 0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23064.ic18",  0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23065.ic19s", 0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23066.ic20",  0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23067.ic21s", 0x3000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-23068.ic22",  0x3000002, 0x0800000,  0x0000000, InterleavedWord },
            { "copy",            0x400000 , 0xc00000,  0x0000000,  Copy, 0x1000000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //ROM_LOAD( "25lc040.ic13s", 0, 0x200, CRC(6291605c) SHA1(44f757da4814b08108d1a4f431c9a39c38acecb2) )

            { NULL, 0, 0 },
        }
    },
    // Virtua Tennis 2 / Power Smash 2 (Rev A)
    {
        "vtenis2c",
        NULL,
        "Virtua Tennis 2 / Power Smash 2 (Rev A)",
        0x0a000000,
        0x2d2d4743,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22327a.ic11", 0x0000000, 0x400000 },
            { "mpr-22307.ic17s", 0x1000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22308.ic18",  0x1000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22309.ic19s", 0x2000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22310.ic20",  0x2000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22311.ic21s", 0x3000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22312.ic22",  0x3000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22313.ic23s", 0x4000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22314.ic24",  0x4000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22315.ic25s", 0x5000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22316.ic26",  0x5000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22317.ic27s", 0x6000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22318.ic28",  0x6000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22319.ic29",  0x7000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22320.ic30s", 0x7000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22321.ic31",  0x8000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22322.ic32s", 0x8000002, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22323.ic33",  0x9000000, 0x800000,  0x0000000, InterleavedWord },
            { "mpr-22324.ic34s", 0x9000002, 0x800000,  0x0000000, InterleavedWord },
            { "copy",             0x0400000, 0xc00000,  0x0000000, Copy, 0x1000000 }, // changed
            { NULL, 0, 0 },
        },
        nullptr,
        &shot12_inputs
    },
    // Star Horse 2002
    {
        "shors2k2",
        NULL,
        "Star Horse 2002 (sound, Export/Taiwan)",
        0x04000000,
        0x403431d2,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23964.ic11",  0x0000000, 0x400000 },
            { "opr-23965.ic17s", 0x1000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-23966.ic18",  0x1000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-23967.ic19s", 0x2000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-23968.ic20",  0x2000002, 0x800000,  0x0000000, InterleavedWord },
            { "opr-23969.ic21s", 0x3000000, 0x800000,  0x0000000, InterleavedWord },
            { "opr-23970.ic22",  0x3000002, 0x800000,  0x0000000, InterleavedWord },
            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetle (2K3 2ND Ver. 1.002-, World)
    {
        "mushikeo",
        "mushike",
        "Mushiking The King Of Beetle (2K3 2ND Ver. 1.002-, World)",
        0x04000000,
        0x3892fb3a,
        NULL,
        M1,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24217-1002.ic11", 0x0000000, 0x0400000 },
            { "mpr-24218.ic17s",     0x1000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24219.ic18",      0x1000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24220.ic19s",     0x2000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24221.ic20",      0x2000002, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24222.ic21s",     0x3000000, 0x0800000,  0x0000000, InterleavedWord },
            { "mpr-24223.ic22",      0x3000002, 0x0800000,  0x0000000, InterleavedWord },
            { "copy",                0x400000,  0xc00000,  0x0000000,  Copy, 0x1000000 },

            //ROM_REGION(0x200, "some_eeprom", 0)
            //{ "25lc040.ic13s", 0, 0x200, CRC(9adb86c2) SHA1(682d06b2004809c3c7ff2f4f9bc0bde0e51885c0) )

            // MUSHIKING
            // The King of Beetle
            // TYPE-1
            // 800
            // note: this dump from "empty/dead" Management Chip with no game run count left
            //ROM_REGION( 0x80, "rf_tag", 0 )
            //{ "mushi_type1.bin", 0, 0x80, CRC(8f36572b) SHA1(87e00e56d07a961e9180c7da02e35f7fd216dbae) )

            { NULL, 0, 0 },
        }
    },
    // Naomi M2/M3 Roms
    // 18 Wheeler (deluxe) (Rev A)
    {
        "18wheelr",
        NULL,
        "18 Wheeler (deluxe, Rev A)",
        0x0a800000,
        0x2807cf54,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22185a.ic22", 0x0000000, 0x400000 },
            { "mpr-22164.ic1",   0x0800000, 0x800000 },
            { "mpr-22165.ic2",   0x1000000, 0x800000 },
            { "mpr-22166.ic3",   0x1800000, 0x800000 },
            { "mpr-22167.ic4",   0x2000000, 0x800000 },
            { "mpr-22168.ic5",   0x2800000, 0x800000 },
            { "mpr-22169.ic6",   0x3000000, 0x800000 },
            { "mpr-22170.ic7",   0x3800000, 0x800000 },
            { "mpr-22171.ic8",   0x4000000, 0x800000 },
            { "mpr-22172.ic9",   0x4800000, 0x800000 },
            { "mpr-22173.ic10",  0x5000000, 0x800000 },
            { "mpr-22174.ic11",  0x5800000, 0x800000 },
            { "mpr-22175.ic12s", 0x6000000, 0x800000 },
            { "mpr-22176.ic13s", 0x6800000, 0x800000 },
            { "mpr-22177.ic14s", 0x7000000, 0x800000 },
            { "mpr-22178.ic15s", 0x7800000, 0x800000 },
            { "mpr-22179.ic16s", 0x8000000, 0x800000 },
            { "mpr-22180.ic17s", 0x8800000, 0x800000 },
            { "mpr-22181.ic18s", 0x9000000, 0x800000 },
            { "mpr-22182.ic19s", 0x9800000, 0x800000 },
            { "mpr-22183.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &_18wheelr_inputs
    },
    // 18 Wheeler (deluxe)
    {
        "18wheelro",
        "18wheelr",
        "18 Wheeler (deluxe)",
        0x0a800000,
        0x2807cf54,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22185.ic22",  0x0000000, 0x400000 },
            { "mpr-22164.ic1",   0x0800000, 0x800000 },
            { "mpr-22165.ic2",   0x1000000, 0x800000 },
            { "mpr-22166.ic3",   0x1800000, 0x800000 },
            { "mpr-22167.ic4",   0x2000000, 0x800000 },
            { "mpr-22168.ic5",   0x2800000, 0x800000 },
            { "mpr-22169.ic6",   0x3000000, 0x800000 },
            { "mpr-22170.ic7",   0x3800000, 0x800000 },
            { "mpr-22171.ic8",   0x4000000, 0x800000 },
            { "mpr-22172.ic9",   0x4800000, 0x800000 },
            { "mpr-22173.ic10",  0x5000000, 0x800000 },
            { "mpr-22174.ic11",  0x5800000, 0x800000 },
            { "mpr-22175.ic12s", 0x6000000, 0x800000 },
            { "mpr-22176.ic13s", 0x6800000, 0x800000 },
            { "mpr-22177.ic14s", 0x7000000, 0x800000 },
            { "mpr-22178.ic15s", 0x7800000, 0x800000 },
            { "mpr-22179.ic16s", 0x8000000, 0x800000 },
            { "mpr-22180.ic17s", 0x8800000, 0x800000 },
            { "mpr-22181.ic18s", 0x9000000, 0x800000 },
            { "mpr-22182.ic19s", 0x9800000, 0x800000 },
            { "mpr-22183.ic20s", 0xa000000, 0x800000 },

            // JVS I/O board 837-13844, external Z80 code for Sega 315-6146 "MIE" MCU
            //ROM_REGION( 0x20000, "jvsio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-21868.ic7", 0x000000, 0x010000, CRC(c306a51f) SHA1(7833b73dc34c4c62401a30637968f46b949ceac0) )

            // later version of the same I/O board (temporary, we'll handle this properly later)
            //ROM_LOAD( "epr-22082.ic7", 0x010000, 0x010000, CRC(de26fc6c) SHA1(cf8ef7969770fff8697299c3e3152413b898a967) )

            // 837-14645 JVS I/O, uses same PCB as 837-13844
            //ROM_LOAD( "epr-24354.ic7", 0x000000, 0x010000, CRC(0ce43505) SHA1(7700e3acfb756dfbf95f3ff14786d1bcb57e2f7d) )

            // 18 Wheeler motor controller 838-13992, code is for a TMPZ84C015 which is Z80 compatible
            //ROM_REGION( 0x10000, "motorio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-23000.ic8", 0x000000, 0x010000, CRC(e3b162f7) SHA1(52c7ad759c3c4a3148764e14d77ba5006bc8af48) )

            { NULL, 0, 0 },
        },
        NULL,
        &_18wheelr_inputs
    },
    // 18 Wheeler (deluxe) (Rev T)
    {
        "18wheelrt",
        "18wheelr",
        "18 Wheeler (deluxe, Rev T)",
        0x0a800000,
        0x2807cf54,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22185t.ic22", 0x0000000, 0x400000 },
            { "mpr-22164.ic1",   0x0800000, 0x800000 },
            { "mpr-22165.ic2",   0x1000000, 0x800000 },
            { "mpr-22166.ic3",   0x1800000, 0x800000 },
            { "mpr-22167.ic4",   0x2000000, 0x800000 },
            { "mpr-22168.ic5",   0x2800000, 0x800000 },
            { "mpr-22169.ic6",   0x3000000, 0x800000 },
            { "mpr-22170.ic7",   0x3800000, 0x800000 },
            { "mpr-22171.ic8",   0x4000000, 0x800000 },
            { "mpr-22172.ic9",   0x4800000, 0x800000 },
            { "mpr-22173.ic10",  0x5000000, 0x800000 },
            { "mpr-22174.ic11",  0x5800000, 0x800000 },
            { "mpr-22175.ic12s", 0x6000000, 0x800000 },
            { "mpr-22176.ic13s", 0x6800000, 0x800000 },
            { "mpr-22177.ic14s", 0x7000000, 0x800000 },
            { "mpr-22178.ic15s", 0x7800000, 0x800000 },
            { "mpr-22179.ic16s", 0x8000000, 0x800000 },
            { "mpr-22180.ic17s", 0x8800000, 0x800000 },
            { "mpr-22181.ic18s", 0x9000000, 0x800000 },
            { "mpr-22182.ic19s", 0x9800000, 0x800000 },
            { "mpr-22183.ic20s", 0xa000000, 0x800000 },

            // JVS I/O board 837-13844, external Z80 code for Sega 315-6146 "MIE" MCU
            //ROM_REGION( 0x20000, "jvsio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-21868.ic7", 0x000000, 0x010000, CRC(c306a51f) SHA1(7833b73dc34c4c62401a30637968f46b949ceac0) )

            // later version of the same I/O board (temporary, we'll handle this properly later)
            //ROM_LOAD( "epr-22082.ic7", 0x010000, 0x010000, CRC(de26fc6c) SHA1(cf8ef7969770fff8697299c3e3152413b898a967) )

            // 837-14645 JVS I/O, uses same PCB as 837-13844
            //ROM_LOAD( "epr-24354.ic7", 0x000000, 0x010000, CRC(0ce43505) SHA1(7700e3acfb756dfbf95f3ff14786d1bcb57e2f7d) )

            // 18 Wheeler motor controller 838-13992, code is for a TMPZ84C015 which is Z80 compatible
            //ROM_REGION( 0x10000, "motorio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-23000.ic8", 0x000000, 0x010000, CRC(e3b162f7) SHA1(52c7ad759c3c4a3148764e14d77ba5006bc8af48) )

            { NULL, 0, 0 },
        },
        NULL,
        &_18wheelr_inputs
    },
    // 18 Wheeler (standard)
    {
        "18wheels",
        "18wheelr",
        "18 Wheeler (standard)",
        0x0a800000,
        0x2807cf54,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23298.ic22",  0x0000000, 0x400000 },
            { "mpr-22164.ic1",   0x0800000, 0x800000 },
            { "mpr-22165.ic2",   0x1000000, 0x800000 },
            { "mpr-22166.ic3",   0x1800000, 0x800000 },
            { "mpr-22167.ic4",   0x2000000, 0x800000 },
            { "mpr-22168.ic5",   0x2800000, 0x800000 },
            { "mpr-22169.ic6",   0x3000000, 0x800000 },
            { "mpr-22170.ic7",   0x3800000, 0x800000 },
            { "mpr-22171.ic8",   0x4000000, 0x800000 },
            { "mpr-22172.ic9",   0x4800000, 0x800000 },
            { "mpr-22173.ic10",  0x5000000, 0x800000 },
            { "mpr-22174.ic11",  0x5800000, 0x800000 },
            { "mpr-22175.ic12s", 0x6000000, 0x800000 },
            { "mpr-22176.ic13s", 0x6800000, 0x800000 },
            { "mpr-22177.ic14s", 0x7000000, 0x800000 },
            { "mpr-22178.ic15s", 0x7800000, 0x800000 },
            { "mpr-22179.ic16s", 0x8000000, 0x800000 },
            { "mpr-22180.ic17s", 0x8800000, 0x800000 },
            { "mpr-22181.ic18s", 0x9000000, 0x800000 },
            { "mpr-22182.ic19s", 0x9800000, 0x800000 },
            { "mpr-22183.ic20s", 0xa000000, 0x800000 },

            // JVS I/O board 837-13844, code is for a Z80 of unknown type (it's inside the big Sega ASIC)
            //ROM_REGION( 0x20000, "jvsio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-21868.ic7", 0x000000, 0x010000, CRC(c306a51f) SHA1(7833b73dc34c4c62401a30637968f46b949ceac0) )

            // later version of the same I/O board (temporary, we'll handle this properly later)
            //ROM_LOAD( "epr-22082.ic7", 0x010000, 0x010000, CRC(de26fc6c) SHA1(cf8ef7969770fff8697299c3e3152413b898a967) )

            // 18 Wheeler motor controller 838-13992, code is for a TMPZ84C015 which is Z80 compatible
            //ROM_REGION( 0x10000, "motorio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-23000.ic8", 0x000000, 0x010000, CRC(e3b162f7) SHA1(52c7ad759c3c4a3148764e14d77ba5006bc8af48) )

            { NULL, 0, 0 },
        },
        NULL,
        &_18wheelr_inputs
    },
    // 18 Wheeler (upright)
    {
        "18wheelu",
        "18wheelr",
        "18 Wheeler (upright)",
        0x0a800000,
        0x2807cf54,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23299.ic22",  0x0000000, 0x400000 },
            { "mpr-22164.ic1",   0x0800000, 0x800000 },
            { "mpr-22165.ic2",   0x1000000, 0x800000 },
            { "mpr-22166.ic3",   0x1800000, 0x800000 },
            { "mpr-22167.ic4",   0x2000000, 0x800000 },
            { "mpr-22168.ic5",   0x2800000, 0x800000 },
            { "mpr-22169.ic6",   0x3000000, 0x800000 },
            { "mpr-22170.ic7",   0x3800000, 0x800000 },
            { "mpr-22171.ic8",   0x4000000, 0x800000 },
            { "mpr-22172.ic9",   0x4800000, 0x800000 },
            { "mpr-22173.ic10",  0x5000000, 0x800000 },
            { "mpr-22174.ic11",  0x5800000, 0x800000 },
            { "mpr-22175.ic12s", 0x6000000, 0x800000 },
            { "mpr-22176.ic13s", 0x6800000, 0x800000 },
            { "mpr-22177.ic14s", 0x7000000, 0x800000 },
            { "mpr-22178.ic15s", 0x7800000, 0x800000 },
            { "mpr-22179.ic16s", 0x8000000, 0x800000 },
            { "mpr-22180.ic17s", 0x8800000, 0x800000 },
            { "mpr-22181.ic18s", 0x9000000, 0x800000 },
            { "mpr-22182.ic19s", 0x9800000, 0x800000 },
            { "mpr-22183.ic20s", 0xa000000, 0x800000 },

            // JVS I/O board 837-13844, code is for a Z80 of unknown type (it's inside the big Sega ASIC)
            //ROM_REGION( 0x20000, "jvsio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-21868.ic7", 0x000000, 0x010000, CRC(c306a51f) SHA1(7833b73dc34c4c62401a30637968f46b949ceac0) )

            // later version of the same I/O board (temporary, we'll handle this properly later)
            //ROM_LOAD( "epr-22082.ic7", 0x010000, 0x010000, CRC(de26fc6c) SHA1(cf8ef7969770fff8697299c3e3152413b898a967) )

            // 840-0023    2000     317-0273-COM   Naomi
            //ROM_PARAMETER( ":rom_board:segam2crypt:key", "2807cf54" )

            { NULL, 0, 0 },
        },
        NULL,
        &_18wheelr_inputs
    },
    // Airline Pilots (Rev B)
    {
        "alpilot",
        NULL,
        "Airline Pilots (World, Rev B)",
        0x0b000000,
        0x28070e41,
        "naomi",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21787b.ic22", 0x0000000, 0x400000 },
            { "mpr-21728.ic1",   0x0800000, 0x800000 },
            { "mpr-21729.ic2",   0x1000000, 0x800000 },
            { "mpr-21730.ic3",   0x1800000, 0x800000 },
            { "mpr-21731.ic4",   0x2000000, 0x800000 },
            { "mpr-21732.ic5",   0x2800000, 0x800000 },
            { "mpr-21733.ic6",   0x3000000, 0x800000 },
            { "mpr-21734.ic7",   0x3800000, 0x800000 },
            { "mpr-21735.ic8",   0x4000000, 0x800000 },
            { "mpr-21736.ic9",   0x4800000, 0x800000 },
            { "mpr-21737.ic10",  0x5000000, 0x800000 },
            { "mpr-21738.ic11",  0x5800000, 0x800000 },

            // on-cart X76F100 eeprom contents
            //ROM_REGION( 0x84, "naomibd_eeprom", 0 )
            //ROM_LOAD( "airlinepdx.sf",  0x000000, 0x000084, CRC(404b2add) SHA1(540c8474806775646ace111a2993397b1419fee3) )

            { NULL, 0, 0 },
        },
        NULL,
        &alpilot_inputs,
        alpilot_eeprom_dump
    },
    // Airline Pilots (Japan, Rev A)
    {
        "alpilotj",
        NULL,
        "Airline Pilots (Japan, Rev A)",
        0x0b000000,
        0x28070e41,
        "naomi",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21739a.ic22", 0x000000,  0x400000 },
            { "mpr-21728.ic1",   0x0800000, 0x800000 },
            { "mpr-21729.ic2",   0x1000000, 0x800000 },
            { "mpr-21730.ic3",   0x1800000, 0x800000 },
            { "mpr-21731.ic4",   0x2000000, 0x800000 },
            { "mpr-21732.ic5",   0x2800000, 0x800000 },
            { "mpr-21733.ic6",   0x3000000, 0x800000 },
            { "mpr-21734.ic7",   0x3800000, 0x800000 },
            { "mpr-21735.ic8",   0x4000000, 0x800000 },
            { "mpr-21736.ic9",   0x4800000, 0x800000 },
            { "mpr-21737.ic10",  0x5000000, 0x800000 },
            { "mpr-21738.ic11",  0x5800000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &alpilot_inputs,
        alpilot_eeprom_dump
    },
    // Alien Front (Rev T)
    {
        "alienfnt",
        NULL,
        "Alien Front (Rev T)",
        0x05800000,
        0x28174343,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23586t.ic22", 0x0000000, 0x0400000 },
            { "mpr-23581.ic1",   0x0800000, 0x1000000 },
            { "mpr-23582.ic2",   0x1800000, 0x1000000 },
            { "mpr-23583.ic3",   0x2800000, 0x1000000 },
            { "mpr-23584.ic4",   0x3800000, 0x1000000 },
            { "mpr-23585.ic5",   0x4800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &alienfnt_inputs,
        alienfnt_eeprom_dump
    },
    // Alien Front (Rev A)
    {
        "alienfnta",
        "alienfnt",
        "Alien Front (Rev A)",
        0x05800000,
        0x28174343,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23586a.ic22", 0x0000000, 0x0400000 },
            { "mpr-23581.ic1",   0x0800000, 0x1000000 },
            { "mpr-23582.ic2",   0x1800000, 0x1000000 },
            { "mpr-23583.ic3",   0x2800000, 0x1000000 },
            { "mpr-23584.ic4",   0x3800000, 0x1000000 },
            { "mpr-23585.ic5",   0x4800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &alienfnt_inputs,
        alienfnt_eeprom_dump
    },
    // Capcom Vs. SNK Millennium Fight 2000 (JPN, USA, EXP, KOR, AUS) (Rev C)
    {
        "capsnk",
        NULL,
        "Capcom Vs. SNK Millennium Fight 2000 (Rev C)",
        0x07800000,
        0x00000000,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23511c.ic22", 0x0000000, 0x0400000 },
            { "mpr-23504.ic1",   0x0800000, 0x1000000 },
            { "mpr-23505.ic2",   0x1800000, 0x1000000 },
            { "mpr-23506.ic3",   0x2800000, 0x1000000 },
            { "mpr-23507.ic4",   0x3800000, 0x1000000 },
            { "mpr-23508.ic5",   0x4800000, 0x1000000 },
            { "mpr-23509.ic6",   0x5800000, 0x1000000 },
            { "mpr-23510.ic7",   0x6800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &capsnk_inputs
    },
    // Capcom Vs. SNK Millennium Fight 2000 (Rev A)
    {
        "capsnka",
        "capsnk",
        "Capcom Vs. SNK Millennium Fight 2000 (Rev A)",
        0x07800000,
        0x00000000,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23511a.ic22", 0x000000,  0x400000  },
            { "mpr-23504.ic1",   0x0800000, 0x1000000 },
            { "mpr-23505.ic2",   0x1800000, 0x1000000 },
            { "mpr-23506.ic3",   0x2800000, 0x1000000 },
            { "mpr-23507.ic4",   0x3800000, 0x1000000 },
            { "mpr-23508.ic5",   0x4800000, 0x1000000 },
            { "mpr-23509.ic6",   0x5800000, 0x1000000 },
            { "mpr-23510.ic7",   0x6800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &capsnk_inputs
    },
    // Capcom Vs. SNK Millennium Fight 2000
    {
        "capsnkb",
        "capsnk",
        "Capcom Vs. SNK Millennium Fight 2000",
        0x07800000,
        0x00000000,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23511.ic22", 0x000000,  0x400000  },
            { "mpr-23504.ic1",  0x0800000, 0x1000000 },
            { "mpr-23505.ic2",  0x1800000, 0x1000000 },
            { "mpr-23506.ic3",  0x2800000, 0x1000000 },
            { "mpr-23507.ic4",  0x3800000, 0x1000000 },
            { "mpr-23508.ic5",  0x4800000, 0x1000000 },
            { "mpr-23509.ic6",  0x5800000, 0x1000000 },
            { "mpr-23510.ic7",  0x6800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &capsnk_inputs
    },
    // Crackin' DJ
    {
        "crackndj",
        NULL,
        "Crackin' DJ",
        0x0a800000,
        0x281c2347,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23450.ic22", 0x0000000, 0x0400000 },
            { "mpr-23525.ic1",  0x0800000, 0x1000000 },
            { "mpr-23526.ic2",  0x1800000, 0x1000000 },
            { "mpr-23527.ic3",  0x2800000, 0x1000000 },
            { "mpr-23528.ic4",  0x3800000, 0x1000000 },
            { "mpr-23529.ic5",  0x4800000, 0x1000000 },
            { "mpr-23530.ic6",  0x5800000, 0x1000000 },
            { "mpr-23531.ic7",  0x6800000, 0x1000000 },
            { "mpr-23532.ic8",  0x7800000, 0x1000000 },
            { "mpr-23533.ic9",  0x8800000, 0x1000000 },
            { "mpr-23534.ic10", 0x9800000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Crackin' DJ Part 2 (Japan)
    {
        "crakndj2",
        NULL,
        "Crackin' DJ Part 2 (Japan)",
        0x0a800000,
        0x28428247,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-23674.ic22", 0x0000000, 0x400000 },
            { "rom1.ic1s",      0x0800000, 0x800000 },
            { "rom2.ic2s",      0x1000000, 0x800000 },
            { "rom3.ic3s",      0x1800000, 0x800000 },
            { "rom4.ic4s",      0x2000000, 0x800000 },
            { "rom5.ic5s",      0x2800000, 0x800000 },
            { "rom6.ic6s",      0x3000000, 0x800000 },
            { "rom7.ic7s",      0x3800000, 0x800000 },
            { "rom8.ic8s",      0x4000000, 0x800000 },
            { "rom9.ic9s",      0x4800000, 0x800000 },
            { "rom10.ic10s",    0x5000000, 0x800000 },
            { "rom11.ic11s",    0x5800000, 0x800000 },
            { "rom12.ic12s",    0x6000000, 0x800000 },
            { "rom13.ic13s",    0x6800000, 0x800000 },
            { "rom14.ic14s",    0x7000000, 0x800000 },
            { "rom15.ic15s",    0x7800000, 0x800000 },
            { "rom16.ic16s",    0x8000000, 0x800000 },
            { "rom17.ic17s",    0x8800000, 0x800000 },
            { "rom18.ic18s",    0x9000000, 0x800000 },
            { "rom19.ic19s",    0x9800000, 0x800000 },
            { "rom20.ic20s",    0xa000000, 0x800000 },

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD("sflash.ic37", 0x000000, 0x000084, CRC(08f27149) SHA1(3b8d53dcf2c09035b318022906c444cf8504d7fa) )

            { NULL, 0, 0 },
        }
    },
    // Crazy Taxi
    {
        "crzytaxi",
        NULL,
        "Crazy Taxi",
        0x08800000,
        0x280d2f45,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21684.ic22",  0x0000000, 0x400000 },
            { "mpr-21671.ic1",   0x0800000, 0x800000 },
            { "mpr-21672.ic2",   0x1000000, 0x800000 },
            { "mpr-21673.ic3",   0x1800000, 0x800000 },
            { "mpr-21674.ic4",   0x2000000, 0x800000 },
            { "mpr-21675.ic5",   0x2800000, 0x800000 },
            { "mpr-21676.ic6",   0x3000000, 0x800000 },
            { "mpr-21677.ic7",   0x3800000, 0x800000 },
            { "mpr-21678.ic10",  0x5000000, 0x800000 },
            { "mpr-21679.ic11",  0x5800000, 0x800000 },
            { "mpr-21680.ic12s", 0x6000000, 0x800000 },
            { "mpr-21681.ic13s", 0x6800000, 0x800000 },
            { "mpr-21682.ic14s", 0x7000000, 0x800000 },
            { "mpr-21683.ic15s", 0x7800000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &crzytaxi_inputs
    },
    // Cosmic Smash (Rev A)
    {
        "csmash",
        NULL,
        "Cosmic Smash (Rev A)",
        0x04800000,
        0x28103347,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23428a.ic22", 0x0000000, 0x0400000 },
            { "mpr-23420.ic1",   0x0800000, 0x0800000 },
            { "mpr-23421.ic2",   0x1000000, 0x0800000 },
            { "mpr-23422.ic3",   0x1800000, 0x0800000 },
            { "mpr-23423.ic4",   0x2000000, 0x0800000 },
            { "mpr-23424.ic5",   0x2800000, 0x0800000 },
            { "mpr-23425.ic6",   0x3000000, 0x0800000 },
            { "mpr-23426.ic7",   0x3800000, 0x0800000 },
            { "mpr-23427.ic8",   0x4000000, 0x0800000 },
            { NULL, 0, 0 },
        }
        // SMASH, JUMP, udlr
    },
    // Cosmic Smash
    {
        "csmasho",
        "csmash",
        "Cosmic Smash",
        0x04800000,
        0x28103347,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23428.ic22", 0x0000000, 0x400000  },
            { "mpr-23420.ic1",  0x0800000, 0x0800000 },
            { "mpr-23421.ic2",  0x1000000, 0x0800000 },
            { "mpr-23422.ic3",  0x1800000, 0x0800000 },
            { "mpr-23423.ic4",  0x2000000, 0x0800000 },
            { "mpr-23424.ic5",  0x2800000, 0x0800000 },
            { "mpr-23425.ic6",  0x3000000, 0x0800000 },
            { "mpr-23426.ic7",  0x3800000, 0x0800000 },
            { "mpr-23427.ic8",  0x4000000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Cannon Spike / Gun Spike
    {
        "cspike",
        NULL,
        "Cannon Spike / Gun Spike",
        0x06800000,
        0x000e2010,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23210.ic22",  0x0000000, 0x0400000 },
            { "mpr-23198.ic1",   0x0800000, 0x0800000 },
            { "mpr-23199.ic2",   0x1000000, 0x0800000 },
            { "mpr-23200.ic3",   0x1800000, 0x0800000 },
            { "mpr-23201.ic4",   0x2000000, 0x0800000 },
            { "mpr-23202.ic5",   0x2800000, 0x0800000 },
            { "mpr-23203.ic6",   0x3000000, 0x0800000 },
            { "mpr-23204.ic7",   0x3800000, 0x0800000 },
            { "mpr-23205.ic8",   0x4000000, 0x0800000 },
            { "mpr-23206.ic9",   0x4800000, 0x0800000 },
            { "mpr-23207.ic10",  0x5000000, 0x0800000 },
            { "mpr-23208.ic11",  0x5800000, 0x0800000 },
            { "mpr-23209.ic12s", 0x6000000, 0x0800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &cspike_inputs
    },
    // Death Crimson OX (JPN, USA, EXP, KOR, AUS)
    {
        "deathcox",
        NULL,
        "Death Crimson OX (Rev A)",
        0x05800000,
        0x000b64d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23524a.ic22", 0x0000000, 0x0400000 },
            { "mpr-23514.ic1",   0x0800000, 0x0800000 },
            { "mpr-23515.ic2",   0x1000000, 0x0800000 },
            { "mpr-23516.ic3",   0x1800000, 0x0800000 },
            { "mpr-23517.ic4",   0x2000000, 0x0800000 },
            { "mpr-23518.ic5",   0x2800000, 0x0800000 },
            { "mpr-23519.ic6",   0x3000000, 0x0800000 },
            { "mpr-23520.ic7",   0x3800000, 0x0800000 },
            { "mpr-23521.ic8",   0x4000000, 0x0800000 },
            { "mpr-23522.ic9",   0x4800000, 0x0800000 },
            { "mpr-23523.ic10",  0x5000000, 0x0800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &trigger_inputs
    },
    // Death Crimson OX
    {
        "deathcoxo",
        "deathcox",
        "Death Crimson OX",
        0x05800000,
        0x000b64d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23524.ic22", 0x0000000, 0x0400000 },
            { "mpr-23514.ic1",  0x0800000, 0x0800000 },
            { "mpr-23515.ic2",  0x1000000, 0x0800000 },
            { "mpr-23516.ic3",  0x1800000, 0x0800000 },
            { "mpr-23517.ic4",  0x2000000, 0x0800000 },
            { "mpr-23518.ic5",  0x2800000, 0x0800000 },
            { "mpr-23519.ic6",  0x3000000, 0x0800000 },
            { "mpr-23520.ic7",  0x3800000, 0x0800000 },
            { "mpr-23521.ic8",  0x4000000, 0x0800000 },
            { "mpr-23522.ic9",  0x4800000, 0x0800000 },
            { "mpr-23523.ic10", 0x5000000, 0x0800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &trigger_inputs
    },
    // Derby Owners Club 2000 (Rev A)
    {
        "derbyo2k",
        NULL,
        "Derby Owners Club 2000 Ver.2 (Japan, Rev A)",
        0x8800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22284a.ic22", 0x0000000, 0x400000 },
            { "mpr-22223.ic1",   0x0800000, 0x800000 },
            { "mpr-22224.ic2",   0x1000000, 0x800000 },
            { "mpr-22225.ic3",   0x1800000, 0x800000 },
            { "mpr-22226.ic4",   0x2000000, 0x800000 },
            { "mpr-22227.ic5",   0x2800000, 0x800000 },
            { "mpr-22228.ic6",   0x3000000, 0x800000 },
            { "mpr-22229.ic7",   0x3800000, 0x800000 },
            { "mpr-22230.ic8",   0x4000000, 0x800000 },
            { "mpr-22231.ic9",   0x4800000, 0x800000 },
            { "mpr-22232.ic10",  0x5000000, 0x800000 },
            { "mpr-22233.ic11",  0x5800000, 0x800000 },
            { "mpr-22234.ic12s", 0x6000000, 0x800000 },
            { "mpr-22235.ic13s", 0x6800000, 0x800000 },
            { "mpr-22236.ic14s", 0x7000000, 0x800000 },
            { "mpr-22237.ic15s", 0x7800000, 0x800000 },
            { "mpr-22238.ic16s", 0x8000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Derby Owners Club (JPN, USA, EXP, KOR, AUS) (Rev B)
    {
        "derbyoc",
        NULL,
        "Derby Owners Club (Japan, Rev B)",
        0x07800000,
        0x280fee35,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22099b.ic22", 0x0000000, 0x0400000 },
            { "mpr-22085.ic1",   0x0800000, 0x0800000 },
            { "mpr-22086.ic2",   0x1000000, 0x0800000 },
            { "mpr-22087.ic3",   0x1800000, 0x0800000 },
            { "mpr-22088.ic4",   0x2000000, 0x0800000 },
            { "mpr-22089.ic5",   0x2800000, 0x0800000 },
            { "mpr-22090.ic6",   0x3000000, 0x0800000 },
            { "mpr-22091.ic7",   0x3800000, 0x0800000 },
            { "mpr-22092.ic8",   0x4000000, 0x0800000 },
            { "mpr-22093.ic9",   0x4800000, 0x0800000 },
            { "mpr-22094.ic10",  0x5000000, 0x0800000 },
            { "mpr-22095.ic11",  0x5800000, 0x0800000 },
            { "mpr-22096.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22097.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22098.ic14s", 0x7000000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Derby Owners Club II (JPN, USA, EXP, KOR, AUS) (Rev B)
    {
        "derbyoc2",
        NULL,
        "Derby Owners Club II Ver.2.1 (Japan, Rev B)",
        0x0b800000,
        0x2a436bb7,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22306b.ic22", 0x0000000, 0x0400000 },
            { "mpr-22295.ic1",   0x0800000, 0x1000000 },
            { "mpr-22296.ic2",   0x1800000, 0x1000000 },
            { "mpr-22297.ic3",   0x2800000, 0x1000000 },
            { "mpr-22298.ic4",   0x3800000, 0x1000000 },
            { "mpr-22299.ic5",   0x4800000, 0x1000000 },
            { "mpr-22300.ic6",   0x5800000, 0x1000000 },
            { "mpr-22301.ic7",   0x6800000, 0x1000000 },
            { "mpr-22302.ic8",   0x7800000, 0x1000000 },
            { "mpr-22303.ic9",   0x8800000, 0x1000000 },
            { "mpr-22304.ic10",  0x9800000, 0x1000000 },
            { "mpr-22305.ic11",  0xa800000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Derby Owners Club World Edition (JPN, USA, EXP, KOR, AUS) (Rev D)
    {
        "derbyocw",
        NULL,
        "Derby Owners Club World Edition EX (Rev D)",
        0x07800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22336d.ic22", 0x0000000, 0x0400000, 0xe6c0cb0c },
            { "mpr-22328.ic1",   0x0800000, 0x1000000, 0x179cec02 },
            { "mpr-22329.ic2",   0x1800000, 0x1000000, 0xe0d5b98c },
            { "mpr-22330.ic3",   0x2800000, 0x1000000, 0x6737cd62 },
            { "mpr-22331.ic4",   0x3800000, 0x1000000, 0x8fb5cbcf },
            { "mpr-22332.ic5",   0x4800000, 0x1000000, 0xc5e365a8 },
            { "mpr-22333.ic6",   0x5800000, 0x1000000, 0x96f324aa },
            { "mpr-22334.ic7",   0x6800000, 0x1000000, 0x5389b05a },
            { NULL, 0, 0, 0x00000000 },
        }
    },
    // Derby Owners Club World Edition (Rev A)
    {
        "drbyocwa",
        "derbyocw",
        "Derby Owners Club World Edition (Rev A)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22336a.ic22", 0x0000000, 0x0400000, 0x56dee69a },
            { "mpr-22328.ic1",   0x0800000, 0x1000000, 0x179cec02 },
            { "mpr-22329.ic2",   0x1800000, 0x1000000, 0xe0d5b98c },
            { "mpr-22330.ic3",   0x2800000, 0x1000000, 0x6737cd62 },
            { "mpr-22331.ic4",   0x3800000, 0x1000000, 0x8fb5cbcf },
            { "mpr-22332.ic5",   0x4800000, 0x1000000, 0xc5e365a8 },
            { "mpr-22333.ic6",   0x5800000, 0x1000000, 0x96f324aa },
            { "mpr-22334.ic7",   0x6800000, 0x1000000, 0x5389b05a },
            { NULL, 0, 0, 0x00000000 },
        }
    },
    // Derby Owners Club World Edition (Rev B)
    {
        "drbyocwb",
        "derbyocw",
        "Derby Owners Club World Edition (Rev B)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22336b.ic22", 0x0000000, 0x0400000, 0x8df5434b },
            { "mpr-22328.ic1",   0x0800000, 0x1000000, 0x179cec02 },
            { "mpr-22329.ic2",   0x1800000, 0x1000000, 0xe0d5b98c },
            { "mpr-22330.ic3",   0x2800000, 0x1000000, 0x6737cd62 },
            { "mpr-22331.ic4",   0x3800000, 0x1000000, 0x8fb5cbcf },
            { "mpr-22332.ic5",   0x4800000, 0x1000000, 0xc5e365a8 },
            { "mpr-22333.ic6",   0x5800000, 0x1000000, 0x96f324aa },
            { "mpr-22334.ic7",   0x6800000, 0x1000000, 0x5389b05a },
            { NULL, 0, 0, 0x00000000 },
        }
    },
    // Derby Owners Club World Edition (Rev C)
    {
        "drbyocwc",
        "derbyocw",
        "Derby Owners Club World Edition (Rev C)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22336c.ic22", 0x0000000, 0x0400000, 0x50053f82 },
            { "mpr-22328.ic1",   0x0800000, 0x1000000, 0x179cec02 },
            { "mpr-22329.ic2",   0x1800000, 0x1000000, 0xe0d5b98c },
            { "mpr-22330.ic3",   0x2800000, 0x1000000, 0x6737cd62 },
            { "mpr-22331.ic4",   0x3800000, 0x1000000, 0x8fb5cbcf },
            { "mpr-22332.ic5",   0x4800000, 0x1000000, 0xc5e365a8 },
            { "mpr-22333.ic6",   0x5800000, 0x1000000, 0x96f324aa },
            { "mpr-22334.ic7",   0x6800000, 0x1000000, 0x5389b05a },
            { NULL, 0, 0, 0x00000000 },
        }
    },
    // Dead or Alive 2 (JPN, USA, EXP, KOR, AUS)
    {
        "doa2",
        "doa2m",
        "Dead or Alive 2",
        0xb000000,
        0x0008ad01,
        NULL,
        M2,
        REGION_EXPORT,
        ROT0,
        {
            { "epr-22207.ic22", 0x0000000, 0x0400000 },
            { "mpr-22100.ic1",   0x0800000, 0x0800000 },
            { "mpr-22101.ic2",   0x1000000, 0x0800000 },
            { "mpr-22102.ic3",   0x1800000, 0x0800000 },
            { "mpr-22103.ic4",   0x2000000, 0x0800000 },
            { "mpr-22104.ic5",   0x2800000, 0x0800000 },
            { "mpr-22105.ic6",   0x3000000, 0x0800000 },
            { "mpr-22106.ic7",   0x3800000, 0x0800000 },
            { "mpr-22107.ic8",   0x4000000, 0x0800000 },
            { "mpr-22108.ic9",   0x4800000, 0x0800000 },
            { "mpr-22109.ic10",  0x5000000, 0x0800000 },
            { "mpr-22110.ic11",  0x5800000, 0x0800000 },
            { "mpr-22111.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22112.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22113.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22114.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22115.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22116.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22117.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22118.ic19s", 0x9800000, 0x0800000 },
            { "mpr-22119.ic20s", 0xa000000, 0x0800000 },
            { "mpr-22120.ic21s", 0xa800000, 0x0800000 },

            // on-cart X76F100 eeprom contents
            //ROM_REGION( 0x84, "naomibd_eeprom", 0 )
            //ROM_LOAD( "841-0003.sf",  0x000000, 0x000084, CRC(3a119a17) SHA1(d37a092cca7c9cfc5f2637b355af90a65d04013e) )

            { NULL, 0, 0 },
        }
    },
    // Dead or Alive 2 (Rev A)
    {
        "doa2a",
        "doa2m",
        "Dead or Alive 2 (Rev A)",
        0xb000000,
        0x0008ad01,
        NULL,
        M2,
        REGION_EXPORT,
        ROT0,
        {
            { "epr-22121a.ic22", 0x0000000, 0x0400000 },
            { "mpr-22100.ic1",   0x0800000, 0x0800000 },
            { "mpr-22101.ic2",   0x1000000, 0x0800000 },
            { "mpr-22102.ic3",   0x1800000, 0x0800000 },
            { "mpr-22103.ic4",   0x2000000, 0x0800000 },
            { "mpr-22104.ic5",   0x2800000, 0x0800000 },
            { "mpr-22105.ic6",   0x3000000, 0x0800000 },
            { "mpr-22106.ic7",   0x3800000, 0x0800000 },
            { "mpr-22107.ic8",   0x4000000, 0x0800000 },
            { "mpr-22108.ic9",   0x4800000, 0x0800000 },
            { "mpr-22109.ic10",  0x5000000, 0x0800000 },
            { "mpr-22110.ic11",  0x5800000, 0x0800000 },
            { "mpr-22111.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22112.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22113.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22114.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22115.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22116.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22117.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22118.ic19s", 0x9800000, 0x0800000 },
            { "mpr-22119.ic20s", 0xa000000, 0x0800000 },
            { "mpr-22120.ic21s", 0xa800000, 0x0800000 },

            // on-cart X76F100 eeprom contents
            //ROM_REGION( 0x84, "naomibd_eeprom", 0 )
            //ROM_LOAD( "841-0003.sf",  0x000000, 0x000084, CRC(3a119a17) SHA1(d37a092cca7c9cfc5f2637b355af90a65d04013e) )

            { NULL, 0, 0 },
        }
    },
    // Dead or Alive 2 Millennium (JPN, USA, EXP, KOR, AUS)
    {
        "doa2m",
        NULL,
        "Dead or Alive 2 Millennium",
        0xb000000,
        0x0008ad01,
        NULL,
        M2,
        REGION_EXPORT,
        ROT0,
        {
            { "doa2verm.ic22",   0x0000000, 0x0400000 },
            { "mpr-22100.ic1",  0x0800000, 0x0800000 },
            { "mpr-22101.ic2",  0x1000000, 0x0800000 },
            { "mpr-22102.ic3",  0x1800000, 0x0800000 },
            { "mpr-22103.ic4",  0x2000000, 0x0800000 },
            { "mpr-22104.ic5",  0x2800000, 0x0800000 },
            { "mpr-22105.ic6",  0x3000000, 0x0800000 },
            { "mpr-22106.ic7",  0x3800000, 0x0800000 },
            { "mpr-22107.ic8",  0x4000000, 0x0800000 },
            { "mpr-22108.ic9",  0x4800000, 0x0800000 },
            { "mpr-22109.ic10", 0x5000000, 0x0800000 },
            { "mpr-22110.ic11", 0x5800000, 0x0800000 },
            { "mpr-22111.ic12s",0x6000000, 0x0800000 },
            { "mpr-22112.ic13s",0x6800000, 0x0800000 },
            { "mpr-22113.ic14s",0x7000000, 0x0800000 },
            { "mpr-22114.ic15s",0x7800000, 0x0800000 },
            { "mpr-22115.ic16s",0x8000000, 0x0800000 },
            { "mpr-22116.ic17s",0x8800000, 0x0800000 },
            { "mpr-22117.ic18s",0x9000000, 0x0800000 },
            { "mpr-22118.ic19s",0x9800000, 0x0800000 },
            { "mpr-22119.ic20s",0xa000000, 0x0800000 },
            { "mpr-22120.ic21s",0xa800000, 0x0800000 },

            // on-cart X76F100 eeprom contents
            //ROM_REGION( 0x84, "naomibd_eeprom", 0 )
            //ROM_LOAD( "841-0003.sf",  0x000000, 0x000084, CRC(3a119a17) SHA1(d37a092cca7c9cfc5f2637b355af90a65d04013e) )
            { NULL, 0, 0 },
        }
    },
    // Dynamite Baseball '99 (JPN) / World Series '99 (USA, EXP, KOR, AUS) (Rev B) ***
    {
        "dybb99",
        NULL,
        "Dynamite Baseball '99 (Japan, Rev B)",
        0x0a000000,
        0x2804ae71,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-22141b.ic22", 0x0000000, 0x0200000 },
            { "epr-22141b.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-22122.ic1",   0x0800000, 0x0800000 },
            { "mpr-22123.ic2",   0x1000000, 0x0800000 },
            { "mpr-22124.ic3",   0x1800000, 0x0800000 },
            { "mpr-22125.ic4",   0x2000000, 0x0800000 },
            { "mpr-22126.ic5",   0x2800000, 0x0800000 },
            { "mpr-22127.ic6",   0x3000000, 0x0800000 },
            { "mpr-22128.ic7",   0x3800000, 0x0800000 },
            { "mpr-22129.ic8",   0x4000000, 0x0800000 },
            { "mpr-22130.ic9",   0x4800000, 0x0800000 },
            { "mpr-22131.ic10",  0x5000000, 0x0800000 },
            { "mpr-22132.ic11",  0x5800000, 0x0800000 },
            { "mpr-22133.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22134.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22135.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22136.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22137.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22138.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22139.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22140.ic19s", 0x9800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&wsbb_inputs,
    },
    // Dynamite Baseball NAOMI (Japan)
    {
        "dybbnao",
        NULL,
        "Dynamite Baseball NAOMI (Japan)",
        0x0b000000,
        0x280e6ae1,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-21575.ic22",  0x0000000, 0x0200000 },
            { "epr-21575.ic22",  0x0200000, 0x0200000 }, // reload
            { "mpr-21554.ic1",   0x0800000, 0x0800000 },
            { "mpr-21555.ic2",   0x1000000, 0x0800000 },
            { "mpr-21556.ic3",   0x1800000, 0x0800000 },
            { "mpr-21557.ic4",   0x2000000, 0x0800000 },
            { "mpr-21558.ic5",   0x2800000, 0x0800000 },
            { "mpr-21559.ic6",   0x3000000, 0x0800000 },
            { "mpr-21560.ic7",   0x3800000, 0x0800000 },
            { "mpr-21561.ic8",   0x4000000, 0x0800000 },
            { "mpr-21562.ic9",   0x4800000, 0x0800000 },
            { "mpr-21563.ic10",  0x5000000, 0x0800000 },
            { "mpr-21564.ic11",  0x5800000, 0x0800000 },
            { "mpr-21565.ic12s", 0x6000000, 0x0800000 },
            { "mpr-21566.ic13s", 0x6800000, 0x0800000 },
            { "mpr-21567.ic14s", 0x7000000, 0x0800000 },
            { "mpr-21568.ic15s", 0x7800000, 0x0800000 },
            { "mpr-21569.ic16s", 0x8000000, 0x0800000 },
            { "mpr-21570.ic17s", 0x8800000, 0x0800000 },
            { "mpr-21571.ic18s", 0x9000000, 0x0800000 },
            { "mpr-21572.ic19s", 0x9800000, 0x0800000 },
            { "mpr-21573.ic20s", 0xa000000, 0x0800000 },
            { "mpr-21574.ic21s", 0xa800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&wsbb_inputs,
    },
    // Ferrari F355 Challenge (deluxe)
    {
        "f355",
        NULL,
        "Ferrari F355 Challenge (deluxe, no link)",
        0x0b000000,
        0x280e8f84,
        "f355dlx",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21902.ic22",  0x0000000, 0x0400000 },

            { "mpr-21881.ic1",   0x0800000, 0x0800000 },
            { "mpr-21882.ic2",   0x1000000, 0x0800000 },
            { "mpr-21883.ic3",   0x1800000, 0x0800000 },
            { "mpr-21884.ic4",   0x2000000, 0x0800000 },
            { "mpr-21885.ic5",   0x2800000, 0x0800000 },
            { "mpr-21886.ic6",   0x3000000, 0x0800000 },
            { "mpr-21887.ic7",   0x3800000, 0x0800000 },
            { "mpr-21888.ic8",   0x4000000, 0x0800000 },
            { "mpr-21889.ic9",   0x4800000, 0x0800000 },
            { "mpr-21890.ic10",  0x5000000, 0x0800000 },
            { "mpr-21891.ic11",  0x5800000, 0x0800000 },
            { "mpr-21892.ic12s", 0x6000000, 0x0800000 },
            { "mpr-21893.ic13s", 0x6800000, 0x0800000 },
            { "mpr-21894.ic14s", 0x7000000, 0x0800000 },
            { "mpr-21895.ic15s", 0x7800000, 0x0800000 },
            { "mpr-21896.ic16s", 0x8000000, 0x0800000 },
            { "mpr-21897.ic17s", 0x8800000, 0x0800000 },
            { "mpr-21898.ic18s", 0x9000000, 0x0800000 },
            { "mpr-21899.ic19s", 0x9800000, 0x0800000 },
            { "mpr-21900.ic20s", 0xa000000, 0x0800000 },
            { "mpr-21901.ic21s", 0xa800000, 0x0800000 },

            //ROM_REGION( 0x10000, "drivebd", 0 ) // drive board ROM
            //ROM_LOAD( "epr-21867p.bin", 0x000000, 0x010000, CRC(6143b911) SHA1(360ebc53696da7a29e6404376c82947563274835) ) // prototype preview
            //ROM_LOAD( "epr-21867.bin", 0x000000, 0x010000, CRC(4f93a2a0) SHA1(875907e7fcfc44850e2c60c12268ac61c742f217) )

            { NULL, 0, 0 },
        },
		NULL,
		&f355_inputs
    },
    // Ferrari F355 Challenge (twin)
    {
        "f355twin",
        NULL,
        "Ferrari F355 Challenge (twin/deluxe)",
        0x0b000000,
        0x2806efd4,
        "f355bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22848.ic22",  0x0000000, 0x400000, 0xa29edec2 },
            { "mpr-22827.ic1",   0x0800000, 0x800000, 0xeeb1b975 },
            { "mpr-22828.ic2",   0x1000000, 0x800000, 0x691d246a },
            { "mpr-22829.ic3",   0x1800000, 0x800000, 0x00719c9c },
            { "mpr-22830.ic4",   0x2000000, 0x800000, 0xbfeb0e95 },
            { "mpr-22831.ic5",   0x2800000, 0x800000, 0x697e60a8 },
            { "mpr-22832.ic6",   0x3000000, 0x800000, 0x78e146a0 },
            { "mpr-22833.ic7",   0x3800000, 0x800000, 0xcbd847ea },
            { "mpr-22834.ic8",   0x4000000, 0x800000, 0x3bfc6571 },
            { "mpr-22835.ic9",   0x4800000, 0x800000, 0xc0a14f8e },
            { "mpr-22836.ic10",  0x5000000, 0x800000, 0xee68d756 },
            { "mpr-22837.ic11",  0x5800000, 0x800000, 0x3b53f0c9 },
            { "mpr-22838.ic12s", 0x6000000, 0x800000, 0xc17a2228 },
            { "mpr-22839.ic13s", 0x6800000, 0x800000, 0x31ab7352 },
            { "mpr-22840.ic14s", 0x7000000, 0x800000, 0xaf4c757b },
            { "mpr-22841.ic15s", 0x7800000, 0x800000, 0x7adceb6b },
            { "mpr-22842.ic16s", 0x8000000, 0x800000, 0x1ce2ec11 },
            { "mpr-22843.ic17s", 0x8800000, 0x800000, 0x1c659384 },
            { "mpr-22844.ic18s", 0x9000000, 0x800000, 0x361ea725 },
            { "mpr-22845.ic19s", 0x9800000, 0x800000, 0x3327aed1 },
            { "mpr-22846.ic20s", 0xa000000, 0x800000, 0xd4148f39 },
            { "mpr-22847.ic21s", 0xa800000, 0x800000, 0x955ad42e },
            { NULL, 0, 0 },
        }
    },
    // Ferrari F355 Challenge (twin/deluxe, preview)
    {
        "f355twinp",
        "f355twin",
        "Ferrari F355 Challenge (twin/deluxe, preview)",
        0x0b000000,
        0x2806efd4,
        "f355bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22848p.ic22", 0x0000000, 0x400000, 0x2c43b053 },
            { "rom1.ic1s",       0x0800000, 0x800000, 0xeeb1b975 },
            { "rom2.ic2s",       0x1000000, 0x800000, 0x691d246a },
            { "rom3.ic3s",       0x1800000, 0x800000, 0x00719c9c },
            { "rom4.ic4s",       0x2000000, 0x800000, 0xbfeb0e95 },
            { "rom5.ic5s",       0x2800000, 0x800000, 0x697e60a8 },
            { "rom6.ic6s",       0x3000000, 0x800000, 0x78e146a0 },
            { "rom7.ic7s",       0x3800000, 0x800000, 0xcbd847ea },
            { "rom8.ic8s",       0x4000000, 0x800000, 0x3bfc6571 },
            { "rom9.ic9s",       0x4800000, 0x800000, 0xc0a14f8e },
            { "rom10.ic10s",     0x5000000, 0x800000, 0xee68d756 },
            { "rom11.ic11s",     0x5800000, 0x800000, 0x3b53f0c9 },
            { "rom12.ic12s",     0x6000000, 0x800000, 0xc17a2228 },
            { "rom13.ic13s",     0x6800000, 0x800000, 0x31ab7352 },
            { "rom14.ic14s",     0x7000000, 0x800000, 0xaf4c757b },
            { "rom15.ic15s",     0x7800000, 0x800000, 0x7adceb6b },
            { "rom16.ic16s",     0x8000000, 0x800000, 0x1ce2ec11 },
            { "rom17.ic17s",     0x8800000, 0x800000, 0x1c659384 },
            { "rom18.ic18s",     0x9000000, 0x800000, 0x361ea725 },
            { "rom19.ic19s",     0x9800000, 0x800000, 0x3327aed1 },
            { "rom20.ic20s",     0xa000000, 0x800000, 0xd4148f39 },
            { "rom21.ic21s",     0xa800000, 0x800000, 0x955ad42e },
            { NULL, 0, 0 },
        }
    },
    // Ferrari F355 Challenge 2 (twin)
    {
        "f355twn2",
        NULL,
        "Ferrari F355 Challenge 2 - International Course Edition (twin/deluxe)",
        0xb000000,
        0x281666c6,
        "f355bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23399.ic22",  0x0000000, 0x400000 },
            //{ "epr-23399_alt.ic22", 0x0000000, 0x400000 },
            { "mpr-23378.ic1",   0x0800000, 0x800000 },
            { "mpr-23379.ic2",   0x1000000, 0x800000 },
            { "mpr-23380.ic3",   0x1800000, 0x800000 },
            { "mpr-23381.ic4",   0x2000000, 0x800000 },
            { "mpr-23382.ic5",   0x2800000, 0x800000 },
            { "mpr-23383.ic6",   0x3000000, 0x800000 },
            { "mpr-23384.ic7",   0x3800000, 0x800000 },
            { "mpr-23385.ic8",   0x4000000, 0x800000 },
            { "mpr-23386.ic9",   0x4800000, 0x800000 },
            { "mpr-23387.ic10",  0x5000000, 0x800000 },
            { "mpr-23388.ic11",  0x5800000, 0x800000 },
            { "mpr-23389.ic12s", 0x6000000, 0x800000 },
            { "mpr-23390.ic13s", 0x6800000, 0x800000 },
            { "mpr-23391.ic14s", 0x7000000, 0x800000 },
            { "mpr-23392.ic15s", 0x7800000, 0x800000 },
            { "mpr-23393.ic16s", 0x8000000, 0x800000 },
            { "mpr-23394.ic17s", 0x8800000, 0x800000 },
            { "mpr-23395.ic18s", 0x9000000, 0x800000 },
            { "mpr-23396.ic19s", 0x9800000, 0x800000 },
            { "mpr-23397.ic20s", 0xa000000, 0x800000 },
            { "mpr-23398.ic21s", 0xa800000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Giant Gram: All Japan Pro Wrestling 2 (JPN, USA, EXP, KOR, AUS)
    {
        "ggram2",
        NULL,
        "Giant Gram: All Japan Pro Wrestling 2 (Japan)",
        0x06000000,
        0x28074a61,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-21820.ic22", 0x0000000, 0x0200000 },
            { "epr-21820.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-21821.ic1",  0x0800000, 0x0800000 },
            // IC2 empty
            { "mpr-21823.ic3",  0x1800000, 0x0800000 },
            { "mpr-21824.ic4",  0x2000000, 0x0800000 },
            { "mpr-21825.ic5",  0x2800000, 0x0800000 },
            { "mpr-21826.ic6",  0x3000000, 0x0800000 },
            { "mpr-21827.ic7",  0x3800000, 0x0800000 },
            // IC8 empty
            { "mpr-21829.ic9",  0x4800000, 0x0800000 },
            { "mpr-21830.ic10", 0x5000000, 0x0800000 },
            { "mpr-21831.ic11", 0x5800000, 0x0800000 },
            { NULL, 0, 0 },
        }
        // same as gram2000
    },
    // Guilty Gear X (JPN)
    {
        "ggx",
        NULL,
        "Guilty Gear X",
        0x07800000,
        0x00076110,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23356.ic22",  0x0000000, 0x0400000 },
            { "mpr-23342.ic1",   0x0800000, 0x0800000 },
            { "mpr-23343.ic2",   0x1000000, 0x0800000 },
            { "mpr-23344.ic3",   0x1800000, 0x0800000 },
            { "mpr-23345.ic4",   0x2000000, 0x0800000 },
            { "mpr-23346.ic5",   0x2800000, 0x0800000 },
            { "mpr-23347.ic6",   0x3000000, 0x0800000 },
            { "mpr-23348.ic7",   0x3800000, 0x0800000 },
            { "mpr-23349.ic8",   0x4000000, 0x0800000 },
            { "mpr-23350.ic9",   0x4800000, 0x0800000 },
            { "mpr-23351.ic10",  0x5000000, 0x0800000 },
            { "mpr-23352.ic11",  0x5800000, 0x0800000 },
            { "mpr-23353.ic12s", 0x6000000, 0x0800000 },
            { "mpr-23354.ic13s", 0x6800000, 0x0800000 },
            { "mpr-23355.ic14s", 0x7000000, 0x0800000 },
            { NULL, 0, 0 },
        }
        // PUNCH, KICK, SLASH, HIGH SLASH
    },
    // Mobile Suit Gundam: Federation Vs. Zeon
    {
        "gundmct",
        NULL,
        "Mobile Suit Gundam: Federation Vs. Zeon",
        0x0a800000,
        0x000e8010,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23638.ic22", 0x0000000, 0x0400000 },
            { "mpr-23628.ic1",  0x0800000, 0x1000000 },
            { "mpr-23629.ic2",  0x1800000, 0x1000000 },
            { "mpr-23630.ic3",  0x2800000, 0x1000000 },
            { "mpr-23631.ic4",  0x3800000, 0x1000000 },
            { "mpr-23632.ic5",  0x4800000, 0x1000000 },
            { "mpr-23633.ic6",  0x5800000, 0x1000000 },
            { "mpr-23634.ic7",  0x6800000, 0x1000000 },
            { "mpr-23635.ic8",  0x7800000, 0x1000000 },
            { "mpr-23636.ic9",  0x8800000, 0x1000000 },
            { "mpr-23637.ic10", 0x9800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &shot1234_inputs,
        gundmct_eeprom_dump
    },
    // Gun Survivor 2 Biohazard Code: Veronica (BHF2 Ver. E)
    {
        "gunsur2",
        NULL,
        "Gun Survivor 2 Biohazard Code: Veronica (World, BHF2 Ver.E)",
        0x10000000,
        0x000680d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "bhf2vere.2f", 0x0000000, 0x0800000 },
            { "bhf1ma2.4m",   0x2000000, 0x1000000 },
            { "bhf1ma3.4l",   0x3000000, 0x1000000 },
            { "bhf1ma4.4k",   0x4000000, 0x1000000 },
            { "bhf1ma5.4j",   0x5000000, 0x1000000 },
            { "bhf1ma6.4h",   0x6000000, 0x1000000 },
            { "bhf1ma7.4f",   0x7000000, 0x1000000 },
            { "bhf1ma8.4d",   0x8000000, 0x1000000 },
            { "bhf1ma9.4e",   0x9000000, 0x1000000 },
            { "bhf1ma10.4c",  0xa000000, 0x1000000 },
            { "bhf1ma11.4b",  0xb000000, 0x1000000 },
            { "bhf1ma12.6p",  0xc000000, 0x1000000 },
            { "bhf1ma13.6n",  0xd000000, 0x1000000 },
            { "bhf1ma14.6m",  0xe000000, 0x1000000 },
            { "bhf1ma15.6l",  0xf000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &gunsur2_inputs
    },
    // Gun Survivor 2 Biohazard Code: Veronica (Japan, BHF1 Ver.E)
    {
        "gunsur2j",
        "gunsur2",
        "Gun Survivor 2 Biohazard Code: Veronica (Japan, BHF1 Ver.E)",
        0x10000000,
        0x000680d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "bhf1vere.2f",  0x0000000, 0x0800000 },
            { "bhf1ma2.4m",   0x2000000, 0x1000000 },
            { "bhf1ma3.4l",   0x3000000, 0x1000000 },
            { "bhf1ma4.4k",   0x4000000, 0x1000000 },
            { "bhf1ma5.4j",   0x5000000, 0x1000000 },
            { "bhf1ma6.4h",   0x6000000, 0x1000000 },
            { "bhf1ma7.4f",   0x7000000, 0x1000000 },
            { "bhf1ma8.4d",   0x8000000, 0x1000000 },
            { "bhf1ma9.4e",   0x9000000, 0x1000000 },
            { "bhf1ma10.4c",  0xa000000, 0x1000000 },
            { "bhf1ma11.4b",  0xb000000, 0x1000000 },
            { "bhf1ma12.6p",  0xc000000, 0x1000000 },
            { "bhf1ma13.6n",  0xd000000, 0x1000000 },
            { "bhf1ma14.6m",  0xe000000, 0x1000000 },
            { "bhf1ma15.6l",  0xf000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &gunsur2_inputs
    },
    // Giga Wing 2
    {
        "gwing2",
        NULL,
        "Giga Wing 2",
        0x05800000,
        0x000b25d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22270.ic22", 0x0000000, 0x0200000 },
            { "epr-22270.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-22271.ic1", 0x0800000, 0x1000000 },
            { "mpr-22272.ic2", 0x1800000, 0x1000000 },
            { "mpr-22273.ic3", 0x2800000, 0x1000000 },
            { "mpr-22274.ic4", 0x3800000, 0x1000000 },
            { "mpr-22275.ic5", 0x4800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        nullptr,
        &shot12_inputs,
    },
    // Heavy Metal Geomatrix (JPN, USA, EUR, ASI, AUS) (Rev B)
    {
        "hmgeo",
        NULL,
        "Heavy Metal Geomatrix (Rev B)",
        0x06000000,
        0x00038510,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23716a.ic22", 0x0000000, 0x0400000 },
            { "mpr-23705.ic1",   0x0800000, 0x0800000 },
            { "mpr-23706.ic2",   0x1000000, 0x0800000 },
            { "mpr-23707.ic3",   0x1800000, 0x0800000 },
            { "mpr-23708.ic4",   0x2000000, 0x0800000 },
            { "mpr-23709.ic5",   0x2800000, 0x0800000 },
            { "mpr-23710.ic6",   0x3000000, 0x0800000 },
            { "mpr-23711.ic7",   0x3800000, 0x0800000 },
            { "mpr-23712.ic8",   0x4000000, 0x0800000 },
            { "mpr-23713.ic9",   0x4800000, 0x0800000 },
            { "mpr-23714.ic10",  0x5000000, 0x0800000 },
            { "mpr-23715.ic11",  0x5800000, 0x0800000 },
            { NULL, 0, 0 },
        },
        NULL,
		&shot1234_inputs,
        hmgeo_eeprom_dump
    },
    // House of the Dead 2
    {
        "hotd2",
        NULL,
        "The House of the Dead 2 (USA)",
        0xa800000,
        0xfffffff, // not populated
        "hod2bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21585.ic22",  0x0000000, 0x200000 },
            { "epr-21585.ic22",  0x0200000, 0x200000 }, // reload
            { "mpr-21386.ic1",   0x0800000, 0x800000 },
            { "mpr-21387.ic2",   0x1000000, 0x800000 },
            { "mpr-21388.ic3",   0x1800000, 0x800000 },
            { "mpr-21389.ic4",   0x2000000, 0x800000 },
            { "mpr-21390.ic5",   0x2800000, 0x800000 },
            { "mpr-21391.ic6",   0x3000000, 0x800000 },
            { "mpr-21392.ic7",   0x3800000, 0x800000 },
            { "mpr-21393.ic8",   0x4000000, 0x800000 },
            { "mpr-21394.ic9",   0x4800000, 0x800000 },
            { "mpr-21395.ic10",  0x5000000, 0x800000 },
            { "mpr-21396.ic11",  0x5800000, 0x800000 },
            { "mpr-21397.ic12s", 0x6000000, 0x800000 },
            { "mpr-21398.ic13s", 0x6800000, 0x800000 },
            { "mpr-21399.ic14s", 0x7000000, 0x800000 },
            { "mpr-21400.ic15s", 0x7800000, 0x800000 },
            { "mpr-21401.ic16s", 0x8000000, 0x800000 },
            { "mpr-21402.ic17s", 0x8800000, 0x800000 },
            { "mpr-21403.ic18s", 0x9000000, 0x800000 },
            { "mpr-21404.ic19s", 0x9800000, 0x800000 },
            { "mpr-21405.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // The House of the Dead 2
    {
        "hotd2o",
        "hotd2",
        "The House of the Dead 2",
        0xa800000,
        0xfffffff, // not populated
        "hod2bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21385.ic22",  0x0000000, 0x200000 },
            { "epr-21385.ic22",  0x0200000, 0x200000 }, //reload
            { "mpr-21386.ic1",   0x0800000, 0x800000 },
            { "mpr-21387.ic2",   0x1000000, 0x800000 },
            { "mpr-21388.ic3",   0x1800000, 0x800000 },
            { "mpr-21389.ic4",   0x2000000, 0x800000 },
            { "mpr-21390.ic5",   0x2800000, 0x800000 },
            { "mpr-21391.ic6",   0x3000000, 0x800000 },
            { "mpr-21392.ic7",   0x3800000, 0x800000 },
            { "mpr-21393.ic8",   0x4000000, 0x800000 },
            { "mpr-21394.ic9",   0x4800000, 0x800000 },
            { "mpr-21395.ic10",  0x5000000, 0x800000 },
            { "mpr-21396.ic11",  0x5800000, 0x800000 },
            { "mpr-21397.ic12s", 0x6000000, 0x800000 },
            { "mpr-21398.ic13s", 0x6800000, 0x800000 },
            { "mpr-21399.ic14s", 0x7000000, 0x800000 },
            { "mpr-21400.ic15s", 0x7800000, 0x800000 },
            { "mpr-21401.ic16s", 0x8000000, 0x800000 },
            { "mpr-21402.ic17s", 0x8800000, 0x800000 },
            { "mpr-21403.ic18s", 0x9000000, 0x800000 },
            { "mpr-21404.ic19s", 0x9800000, 0x800000 },
            { "mpr-21405.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // The House of the Dead 2 (Export)
    {
        "hotd2e",
        "hotd2",
        "The House of the Dead 2 (Export)",
        0xa800000,
        0xfffffff, // not populated
        "hod2bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21805.ic22",  0x0000000, 0x200000 },
            { "epr-21805.ic22",  0x0200000, 0x200000 }, //reload
            { "mpr-21386.ic1",   0x0800000, 0x800000 },
            { "mpr-21387.ic2",   0x1000000, 0x800000 },
            { "mpr-21388.ic3",   0x1800000, 0x800000 },
            { "mpr-21389.ic4",   0x2000000, 0x800000 },
            { "mpr-21390.ic5",   0x2800000, 0x800000 },
            { "mpr-21391.ic6",   0x3000000, 0x800000 },
            { "mpr-21392.ic7",   0x3800000, 0x800000 },
            { "mpr-21393.ic8",   0x4000000, 0x800000 },
            { "mpr-21394.ic9",   0x4800000, 0x800000 },
            { "mpr-21395.ic10",  0x5000000, 0x800000 },
            { "mpr-21396.ic11",  0x5800000, 0x800000 },
            { "mpr-21397.ic12s", 0x6000000, 0x800000 },
            { "mpr-21398.ic13s", 0x6800000, 0x800000 },
            { "mpr-21399.ic14s", 0x7000000, 0x800000 },
            { "mpr-21400.ic15s", 0x7800000, 0x800000 },
            { "mpr-21401.ic16s", 0x8000000, 0x800000 },
            { "mpr-21402.ic17s", 0x8800000, 0x800000 },
            { "mpr-21403.ic18s", 0x9000000, 0x800000 },
            { "mpr-21404.ic19s", 0x9800000, 0x800000 },
            { "mpr-21405.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // The House of the Dead 2 (prototype)
    {
        "hotd2p",
        "hotd2",
        "The House of the Dead 2 (prototype)",
        0xa800000,
        0xfffffff, // not populated
        "hod2bios",
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "hotd2proto.ic22", 0x000000,  0x200000 },
            { "hotd2proto.ic22", 0x200000,  0x200000 },
            { "mpr-21386.ic1",   0x0800000, 0x800000 },
            { "mpr-21387.ic2",   0x1000000, 0x800000 },
            { "mpr-21388.ic3",   0x1800000, 0x800000 },
            { "mpr-21389.ic4",   0x2000000, 0x800000 },
            { "mpr-21390.ic5",   0x2800000, 0x800000 },
            { "mpr-21391.ic6",   0x3000000, 0x800000 },
            { "mpr-21392.ic7",   0x3800000, 0x800000 },
            { "mpr-21393.ic8",   0x4000000, 0x800000 },
            { "mpr-21394.ic9",   0x4800000, 0x800000 },
            { "mpr-21395.ic10",  0x5000000, 0x800000 },
            { "mpr-21396.ic11",  0x5800000, 0x800000 },
            { "mpr-21397.ic12s", 0x6000000, 0x800000 },
            { "mpr-21398.ic13s", 0x6800000, 0x800000 },
            { "mpr-21399.ic14s", 0x7000000, 0x800000 },
            { "mpr-21400.ic15s", 0x7800000, 0x800000 },
            { "mpr-21401.ic16s", 0x8000000, 0x800000 },
            { "mpr-21402.ic17s", 0x8800000, 0x800000 },
            { "mpr-21403.ic18s", 0x9000000, 0x800000 },
            { "mpr-21404.ic19s", 0x9800000, 0x800000 },
            { "mpr-21405.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Inu No Osanpo / Dog Walking (Rev A)
    {
        "inunoos",
        NULL,
        "Inu no Osanpo / Dog Walking (Japan, Export, Rev A)",
        0x08800000,
        0x294bc3e3,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-22294a.ic22", 0x0000000, 0x400000 },
            { "rom1.ic1s",       0x0800000, 0x800000 },
            { "rom2.ic2s",       0x1000000, 0x800000 },
            { "rom3.ic3s",       0x1800000, 0x800000 },
            { "rom4.ic4s",       0x2000000, 0x800000 },
            { "rom5.ic5s",       0x2800000, 0x800000 },
            { "rom6.ic6s",       0x3000000, 0x800000 },
            { "rom7.ic7s",       0x3800000, 0x800000 },
            { "rom8.ic8s",       0x4000000, 0x800000 },
            { "rom9.ic9s",       0x4800000, 0x800000 },
            { "rom10.ic10s",     0x5000000, 0x800000 },
            { "rom11.ic11s",     0x5800000, 0x800000 },
            { "rom12.ic12s",     0x6000000, 0x800000 },
            { "rom13.ic13s",     0x6800000, 0x800000 },
            { "rom14.ic14s",     0x7000000, 0x800000 },
            { "rom15.ic15s",     0x7800000, 0x800000 },
            { "rom16.ic16s",     0x8000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Jambo! Safari (Rev A)
    {
        "jambo",
        NULL,
        "Jambo! Safari (Rev A)",
        0x08800000,
        0x280fab95,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22826a.ic22", 0x0000000, 0x400000 },
            { "mpr-22818.ic1",  0x0800000, 0x800000 },
            { "mpr-22819.ic2",  0x1000000, 0x800000 },
            { "mpr-22820.ic3",  0x1800000, 0x800000 },
            { "mpr-22821.ic4",  0x2000000, 0x800000 },
            { "mpr-22822.ic5",  0x2800000, 0x800000 },
            { "mpr-22823.ic6",  0x3000000, 0x800000 },
            { "mpr-22824.ic7",  0x3800000, 0x800000 },
            { "mpr-22825.ic8",  0x4000000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &jambo_inputs
    },
    // Mars TV (JPN)
    {
        "marstv",
        NULL,
        "Mars TV (Japan)",
        0x08000000,
        0x280b8ef5,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-22993.ic22",  0x0000000, 0x200000 },
            { "epr-22993.ic22",  0x0200000, 0x200000 }, // reload
            { "mpr-22978.ic1",   0x0800000, 0x800000 },
            { "mpr-22979.ic2",   0x1000000, 0x800000 },
            { "mpr-22980.ic3",   0x1800000, 0x800000 },
            { "mpr-22981.ic4",   0x2000000, 0x800000 },
            { "mpr-22982.ic5",   0x2800000, 0x800000 },
            { "mpr-22983.ic6",   0x3000000, 0x800000 },
            { "mpr-22984.ic7",   0x3800000, 0x800000 },
            { "mpr-22985.ic8",   0x4000000, 0x800000 },
            { "mpr-22986.ic9",   0x4800000, 0x800000 },
            { "mpr-22987.ic10",  0x5000000, 0x800000 },
            { "mpr-22988.ic11",  0x5800000, 0x800000 },
            { "mpr-22989.ic12s", 0x6000000, 0x800000 },
            { "mpr-22990.ic13s", 0x6800000, 0x800000 },
            { "mpr-22991.ic14s", 0x7000000, 0x800000 },
            { "mpr-22992.ic15s", 0x7800000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Mazan: Flash of the Blade (MAZ2 Ver. A)
    {
        "mazan",
        NULL,
        "Mazan: Flash of the Blade (World, MAZ2 Ver.A)",
        0x10000000,
        0x280fea94,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "maz2vera.2d", 0x0800000, 0x0800000 },
            { "maz1ma1.4m",  0x1000000, 0x1000000 },
            { "maz1ma2.4l",  0x2000000, 0x1000000 },
            { "maz1ma3.4k",  0x3000000, 0x1000000 },
            { "maz1ma4.4j",  0x4000000, 0x1000000 },
            { "maz1ma5.4h",  0x5000000, 0x1000000 },
            { "maz1ma6.4f",  0x6000000, 0x1000000 },
            { "maz1ma7.4e",  0x7000000, 0x1000000 },
            { "maz1ma8.4d",  0x8000000, 0x1000000 },
            { NULL, 0, 0 },
        }
        // ENTER, START BUTTON
    },
    // Mazan: Flash of the Blade (US, MAZ3 Ver.A)
    {
        "mazanu",
        "mazan",
        "Mazan: Flash of the Blade (US, MAZ3 Ver.A)",
        0x10000000,
        0x280fea94,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "maz3vera.2d", 0x0800000, 0x0800000 },
            { "maz1ma1.4m",  0x1000000, 0x1000000 },
            { "maz1ma2.4l",  0x2000000, 0x1000000 },
            { "maz1ma3.4k",  0x3000000, 0x1000000 },
            { "maz1ma4.4j",  0x4000000, 0x1000000 },
            { "maz1ma5.4h",  0x5000000, 0x1000000 },
            { "maz1ma6.4f",  0x6000000, 0x1000000 },
            { "maz1ma7.4e",  0x7000000, 0x1000000 },
            { "maz1ma8.4d",  0x8000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetles - Mushiking IV / V / VI (World)
    {
        "mushi2k4",
        NULL,
        "Mushiking The King Of Beetles 2004 Second (Japan)",
        0x5800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-24241.ic22", 0x00000000, 0x00400000 },
            { "mpr-24242.ic1",  0x00800000, 0x01000000 },
            { "mpr-24243.ic2",  0x01800000, 0x01000000 },
            { "mpr-24244.ic3",  0x02800000, 0x01000000 },
            { "mpr-24245.ic4",  0x03800000, 0x01000000 },
            { "mpr-24246.ic5",  0x04800000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetles 2005 First (Japan)
    {
        "mushi2k5",
        NULL,
        "Mushiking The King Of Beetles 2005 First (Japan)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-24286.ic22", 0x0000000, 0x0400000, 0x00000000 },
            { "mpr-24276.ic1",  0x0800000, 0x1000000, 0x00000000 },
            { "mpr-24277.ic2",  0x1800000, 0x1000000, 0x00000000 },
            { "mpr-24278.ic3",  0x2800000, 0x1000000, 0x00000000 },
            { "mpr-24279.ic4",  0x3800000, 0x1000000, 0x00000000 },
            { "mpr-24280.ic5",  0x4800000, 0x1000000, 0x00000000 },
            { "mpr-24281.ic6",  0x5800000, 0x1000000, 0x00000000 },
            { "mpr-24282.ic7",  0x6800000, 0x1000000, 0x00000000 },
            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetle (MUSHIUSA '04 1ST, Prototype)
    {
        "mushikep",
        "mushike",
        "Mushiking The King Of Beetle (MUSHIUSA '04 1ST, Prototype)",
        0x07800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "rom1.ic1s", 0x0800000, 0x800000, 0x9cdc8dcb },
            { "rom2.ic2s", 0x1000000, 0x800000, 0x7b637bb6 },
            { "rom3.ic3s", 0x1800000, 0x800000, 0x6c6ddfbf },
            { "rom4.ic4s", 0x2000000, 0x800000, 0xa427002d },
            { "rom5.ic5s", 0x2800000, 0x800000, 0x7076a50e },
            { "rom6.ic6s", 0x3000000, 0x800000, 0xd7143066 },
            { "rom7.ic7s", 0x3800000, 0x800000, 0x98839bab },
            { NULL, 0, 0 },
        }
    },
    // Marvel Vs. Capcom 2 New Age of Heroes (USA, Rev A)
    {
        "mvsc2u",
        "mvsc2",
        "Marvel Vs. Capcom 2 New Age of Heroes (USA, Rev A)",
        0x07800000,
        0x0002c840,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23062a.ic22", 0x0000000, 0x0400000, 0x96038276 },
            { "mpr-23048.ic1",   0x0800000, 0x0800000, 0x93d7a63a },
            { "mpr-23049.ic2",   0x1000000, 0x0800000, 0x003dcce0 },
            { "mpr-23050.ic3",   0x1800000, 0x0800000, 0x1d6b88a7 },
            { "mpr-23051.ic4",   0x2000000, 0x0800000, 0x01226aaa },
            { "mpr-23052.ic5",   0x2800000, 0x0800000, 0x74bee120 },
            { "mpr-23053.ic6",   0x3000000, 0x0800000, 0xd92d4401 },
            { "mpr-23054.ic7",   0x3800000, 0x0800000, 0x78ba02e8 },
            { "mpr-23055.ic8",   0x4000000, 0x0800000, 0x84319604 },
            { "mpr-23056.ic9",   0x4800000, 0x0800000, 0xd7386034 },
            { "mpr-23057.ic10",  0x5000000, 0x0800000, 0xa3f087db },
            { "mpr-23058.ic11",  0x5800000, 0x0800000, 0x61a6cc5d },
            { "mpr-23059.ic12s", 0x6000000, 0x0800000, 0x64808024 },
            { "mpr-23060.ic13s", 0x6800000, 0x0800000, 0x67519942 },
            { "mpr-23061.ic14s", 0x7000000, 0x0800000, 0xfb1844c4 },

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD("sflash.ic37", 0x000000, 0x000084, CRC(37a66f3c) SHA1(df6cd2cdc2813caa5da4dc9f171998485bcbdc44))
            { NULL, 0, 0 },
        },
        NULL,
        &mvsc2_inputs
    },
    // Ninja Assault (NJA3 Ver. A)
    {
        "ninjaslt",
        NULL,
        "Ninja Assault (World, NJA2 Ver.A)",
        0xb000000,
        0x000ca510,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "nja2vera.2d", 0x0800000, 0x0800000 },
            { "nja1vera.2c", 0x1000000, 0x0800000 },
            { "nja1vera.2b", 0x1800000, 0x0800000 },
            { "nja1ma2.4l",      0x2000000, 0x1000000 },
            { "nja1ma3.4k",      0x3000000, 0x1000000 },
            { "nja1ma4.4j",      0x4000000, 0x1000000 },
            { "nja1ma5.4h",      0x5000000, 0x1000000 },
            { "nja1ma6.4f",      0x6000000, 0x1000000 },
            { "nja1ma7.4e",      0x7000000, 0x1000000 },
            { "nja1ma8.4d",      0x8000000, 0x1000000 },
            { "nja1ma9.4c",      0x9000000, 0x1000000 },
            { "nja1ma10.4b",     0xa000000, 0x1000000 },
            //ROM_REGION( 0x20000, "jyu_io", 0 )  // H8/3334-based I/O board ROM, eventually should be separated out
            //ROM_LOAD( "jyu1_prg0a.ic3", 0x000000, 0x020000, CRC(aec4dbc1) SHA1(bddd4f345baf7f594998a39c09da18b3834f0ac2) )
            { NULL, 0, 0 },
        },
        NULL,
        &ninjaslt_inputs
    },
    // Ninja Assault (Asia, NJA4 Ver.A)
    {
        "ninjaslta",
        "ninjaslt",
        "Ninja Assault (Asia, NJA4 Ver.A)",
        0xb000000,
        0x000ca510,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "nja4vera.2d",     0x0800000, 0x0800000 },
            { "nja1vera.2c",     0x1000000, 0x0800000 },
            { "nja1vera.2b",     0x1800000, 0x0800000 },
            { "nja1ma2.4l",      0x2000000, 0x1000000 },
            { "nja1ma3.4k",      0x3000000, 0x1000000 },
            { "nja1ma4.4j",      0x4000000, 0x1000000 },
            { "nja1ma5.4h",      0x5000000, 0x1000000 },
            { "nja1ma6.4f",      0x6000000, 0x1000000 },
            { "nja1ma7.4e",      0x7000000, 0x1000000 },
            { "nja1ma8.4d",      0x8000000, 0x1000000 },
            { "nja1ma9.4c",      0x9000000, 0x1000000 },
            { "nja1ma10.4b",     0xa000000, 0x1000000 },

            //ROM_REGION( 0x20000, "jyu_io", 0 )  // H8/3334-based I/O board ROM, eventually should be separated out
            //ROM_LOAD( "jyu1_prg0a.ic3", 0x000000, 0x020000, CRC(aec4dbc1) SHA1(bddd4f345baf7f594998a39c09da18b3834f0ac2) )
            { NULL, 0, 0 },
        },
        NULL,
        &ninjaslt_inputs
    },
    // Ninja Assault (Japan, NJA1 Ver.A)
    {
        "ninjasltj",
        "ninjaslt",
        "Ninja Assault (Japan, NJA1 Ver.A)",
        0xb000000,
        0x000ca510,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "nja1vera.2d",     0x0800000, 0x0800000 },
            { "nja1vera.2c",     0x1000000, 0x0800000 },
            { "nja1vera.2b",     0x1800000, 0x0800000 },
            { "nja1ma2.4l",      0x2000000, 0x1000000 },
            { "nja1ma3.4k",      0x3000000, 0x1000000 },
            { "nja1ma4.4j",      0x4000000, 0x1000000 },
            { "nja1ma5.4h",      0x5000000, 0x1000000 },
            { "nja1ma6.4f",      0x6000000, 0x1000000 },
            { "nja1ma7.4e",      0x7000000, 0x1000000 },
            { "nja1ma8.4d",      0x8000000, 0x1000000 },
            { "nja1ma9.4c",      0x9000000, 0x1000000 },
            { "nja1ma10.4b",     0xa000000, 0x1000000 },

            //ROM_REGION( 0x20000, "jyu_io", 0 )  // H8/3334-based I/O board ROM, eventually should be separated out
            //ROM_LOAD( "jyu1_prg0a.ic3", 0x000000, 0x020000, CRC(aec4dbc1) SHA1(bddd4f345baf7f594998a39c09da18b3834f0ac2) )

            { NULL, 0, 0 },
        },
        NULL,
        &ninjaslt_inputs
    },
    // Ninja Assault (US, NJA3 Ver.A)
    {
        "ninjasltu",
        "ninjaslt",
        "Ninja Assault (US, NJA3 Ver.A)",
        0xb000000,
        0x000ca510,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "nja3vera.2d", 0x0800000, 0x0800000 },
            { "nja1vera.2c", 0x1000000, 0x0800000 },
            { "nja1vera.2b", 0x1800000, 0x0800000 },
            { "nja1ma2.4l",  0x2000000, 0x1000000 },
            { "nja1ma3.4k",  0x3000000, 0x1000000 },
            { "nja1ma4.4j",  0x4000000, 0x1000000 },
            { "nja1ma5.4h",  0x5000000, 0x1000000 },
            { "nja1ma6.4f",  0x6000000, 0x1000000 },
            { "nja1ma7.4e",  0x7000000, 0x1000000 },
            { "nja1ma8.4d",  0x8000000, 0x1000000 },
            { "nja1ma9.4c",  0x9000000, 0x1000000 },
            { "nja1ma10.4b", 0xa000000, 0x1000000 },

            //ROM_REGION( 0x20000, "jyu_io", 0 )  // H8/3334-based I/O board ROM, eventually should be separated out
            //ROM_LOAD( "jyu1_prg0a.ic3", 0x000000, 0x020000, CRC(aec4dbc1) SHA1(bddd4f345baf7f594998a39c09da18b3834f0ac2) )

            { NULL, 0, 0 },
        },
        NULL,
        &ninjaslt_inputs
    },
    // Oinori-daimyoujin Matsuri
    {
        "oinori",
        NULL,
        "Oinori-daimyoujin Matsuri",
        0x05800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24053.ic22", 0x0000000, 0x0400000 },
            { "mpr-24054.ic1",  0x0800000, 0x1000000 },
            { "mpr-24055.ic2",  0x1800000, 0x1000000 },
            { "mpr-24056.ic3",  0x2800000, 0x1000000 },
            { "mpr-24057.ic4",  0x3800000, 0x1000000 },
            { "mpr-24058.ic5",  0x4800000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // OutTrigger (JPN, USA, EXP, KOR, AUS)
    {
        "otrigger",
        NULL,
        "OutTrigger",
        0xa000000,
        0x280fea94,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22163.ic22", 0x0000000, 0x0400000 },
            { "mpr-22142.ic1",  0x0800000, 0x0800000 },
            { "mpr-22143.ic2",  0x1000000, 0x0800000 },
            { "mpr-22144.ic3",  0x1800000, 0x0800000 },
            { "mpr-22145.ic4",  0x2000000, 0x0800000 },
            { "mpr-22146.ic5",  0x2800000, 0x0800000 },
            { "mpr-22147.ic6",  0x3000000, 0x0800000 },
            { "mpr-22148.ic7",  0x3800000, 0x0800000 },
            { "mpr-22149.ic8",  0x4000000, 0x0800000 },
            { "mpr-22150.ic9",  0x4800000, 0x0800000 },
            { "mpr-22151.ic10", 0x5000000, 0x0800000 },
            { "mpr-22152.ic11", 0x5800000, 0x0800000 },
            { "mpr-22153.ic12s",0x6000000, 0x0800000 },
            { "mpr-22154.ic13s",0x6800000, 0x0800000 },
            { "mpr-22155.ic14s",0x7000000, 0x0800000 },
            { "mpr-22156.ic15s",0x7800000, 0x0800000 },
            { "mpr-22157.ic16s",0x8000000, 0x0800000 },
            { "mpr-22158.ic17s",0x8800000, 0x0800000 },
            { "mpr-22159.ic18s",0x9000000, 0x0800000 },
            { "mpr-22160.ic19s",0x9800000, 0x0800000 },
            //ROM_REGION( 0x10000, "io_board", 0)
            //ROM_LOAD("epr-22084.ic3", 0x0000, 0x10000, CRC(18cf58bb) SHA1(1494f8215231929e41bbe2a133658d01882fbb0f) )

            { NULL, 0, 0 },
        }
        // TRIGGER, CHANGE, JUMP
        // STICK U/D/L/R
    },
    // Moero! Justice Gakuen (JPN) / Project Justice (USA, EXP, KOR, AUS) (Rev A)
    {
        "pjustic",
        NULL,
        "Project Justice / Moero! Justice Gakuen (Rev A)",
        0x0b800000,
        0x000725d0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23548a.ic22", 0x0000000, 0x0400000 },
            { "mpr-23537.ic1",   0x0800000, 0x1000000 },
            { "mpr-23538.ic2",   0x1800000, 0x1000000 },
            { "mpr-23539.ic3",   0x2800000, 0x1000000 },
            { "mpr-23540.ic4",   0x3800000, 0x1000000 },
            { "mpr-23541.ic5",   0x4800000, 0x1000000 },
            { "mpr-23542.ic6",   0x5800000, 0x1000000 },
            { "mpr-23543.ic7",   0x6800000, 0x1000000 },
            { "mpr-23544.ic8",   0x7800000, 0x1000000 },
            { "mpr-23545.ic9",   0x8800000, 0x1000000 },
            { "mpr-23546.ic10",  0x9800000, 0x1000000 },
            { "mpr-23547.ic11",  0xa800000, 0x1000000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&pjustic_inputs,
    },
    // Power Stone
    {
        "pstone",
        NULL,
        "Power Stone",
        0x04800000,
        0x000e69c1,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21597.ic22",0x0000000, 0x0200000 },
            { "epr-21597.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-21589.ic1", 0x0800000, 0x0800000 },
            { "mpr-21590.ic2", 0x1000000, 0x0800000 },
            { "mpr-21591.ic3", 0x1800000, 0x0800000 },
            { "mpr-21592.ic4", 0x2000000, 0x0800000 },
            { "mpr-21593.ic5", 0x2800000, 0x0800000 },
            { "mpr-21594.ic6", 0x3000000, 0x0800000 },
            { "mpr-21595.ic7", 0x3800000, 0x0800000 },
            { "mpr-21596.ic8", 0x4000000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&shot123_inputs,
    },
    // Power Stone 2
    {
        "pstone2",
        NULL,
        "Power Stone 2",
        0x05000000,
        0x000b8dc0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23127.ic22", 0x0000000, 0x0400000 },
            { "mpr-23118.ic1", 0x0800000, 0x0800000 },
            { "mpr-23119.ic2", 0x1000000, 0x0800000 },
            { "mpr-23120.ic3", 0x1800000, 0x0800000 },
            { "mpr-23121.ic4", 0x2000000, 0x0800000 },
            { "mpr-23122.ic5", 0x2800000, 0x0800000 },
            { "mpr-23123.ic6", 0x3000000, 0x0800000 },
            { "mpr-23124.ic7", 0x3800000, 0x0800000 },
            { "mpr-23125.ic8", 0x4000000, 0x0800000 },
            { "mpr-23126.ic9", 0x4800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&shot123_inputs,
        pstone2_eeprom_dump
    },
    // Power Stone 2 (bootleg)
    {
        "pstone2b",
        "pstone2",
        "Power Stone 2 (bootleg)",
        0x05000000,
        0x000b8dc0,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "00.ic1",  0x0000000, 0x0800000 },
            { "01.ic2",  0x0800000, 0x0800000 },
            { "02.ic3",  0x1000000, 0x0800000 },
            { "03.ic4",  0x1800000, 0x0800000 },
            { "04.ic5",  0x2000000, 0x0800000 },
            { "05.ic6",  0x2800000, 0x0800000 },
            { "06.ic7",  0x3000000, 0x0800000 },
            { "07.ic8",  0x3800000, 0x0800000 },
            { "08.ic9",  0x4000000, 0x0800000 },
            { "09.ic10", 0x4800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&shot123_inputs,
        pstone2_eeprom_dump
    },
    // Puyo Puyo Da! (Japan)
    {
        "puyoda",
        NULL,
        "Puyo Puyo Da! (Japan)",
        0x0a800000,
        0x000acd40,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-22206.ic22", 0x0000000, 0x400000 },
            { "mpr-22186.ic1",   0x0800000, 0x800000 },
            { "mpr-22187.ic2",   0x1000000, 0x800000 },
            { "mpr-22188.ic3",   0x1800000, 0x800000 },
            { "mpr-22189.ic4",   0x2000000, 0x800000 },
            { "mpr-22190.ic5",   0x2800000, 0x800000 },
            { "mpr-22191.ic6",   0x3000000, 0x800000 },
            { "mpr-22192.ic7",   0x3800000, 0x800000 },
            { "mpr-22193.ic8",   0x4000000, 0x800000 },
            { "mpr-22194.ic9",   0x4800000, 0x800000 },
            { "mpr-22195.ic10",  0x5000000, 0x800000 },
            { "mpr-22196.ic11",  0x5800000, 0x800000 },
            { "mpr-22197.ic12s", 0x6000000, 0x800000 },
            { "mpr-22198.ic13s", 0x6800000, 0x800000 },
            { "mpr-22199.ic14s", 0x7000000, 0x800000 },
            { "mpr-22200.ic15s", 0x7800000, 0x800000 },
            { "mpr-22201.ic16s", 0x8000000, 0x800000 },
            { "mpr-22202.ic17s", 0x8800000, 0x800000 },
            { "mpr-22203.ic18s", 0x9000000, 0x800000 },
            { "mpr-22204.ic19s", 0x9800000, 0x800000 },
            { "mpr-22205.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Ring Out 4x4 (Rev A)
    {
        "ringout",
        NULL,
        "Ring Out 4x4 (Rev A)",
        0x05800000,
        0x280b1e40,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21779a.ic22", 0x0000000, 0x400000 },
            { "mpr-21761.ic1",  0x0800000, 0x800000 },
            { "mpr-21762.ic2",  0x1000000, 0x800000 },
            { "mpr-21763.ic3",  0x1800000, 0x800000 },
            { "mpr-21764.ic4",  0x2000000, 0x800000 },
            { "mpr-21765.ic5",  0x2800000, 0x800000 },
            { "mpr-21766.ic6",  0x3000000, 0x800000 },
            { "mpr-21767.ic7",  0x3800000, 0x800000 },
            { "mpr-21768.ic8",  0x4000000, 0x800000 },
            { "mpr-21769.ic9",  0x4800000, 0x800000 },
            { "mpr-21770.ic10", 0x5000000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
		&ringout_inputs,
        ringout_eeprom_dump
    },
    // Ring Out 4x4
    {
        "ringouto",
        "ringout",
        "Ring Out 4x4",
        0x05800000,
        0x280b1e40,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21779.ic22", 0x0000000, 0x400000 },
            { "mpr-21761.ic1",  0x0800000, 0x800000 },
            { "mpr-21762.ic2",  0x1000000, 0x800000 },
            { "mpr-21763.ic3",  0x1800000, 0x800000 },
            { "mpr-21764.ic4",  0x2000000, 0x800000 },
            { "mpr-21765.ic5",  0x2800000, 0x800000 },
            { "mpr-21766.ic6",  0x3000000, 0x800000 },
            { "mpr-21767.ic7",  0x3800000, 0x800000 },
            { "mpr-21768.ic8",  0x4000000, 0x800000 },
            { "mpr-21769.ic9",  0x4800000, 0x800000 },
            { "mpr-21770.ic10", 0x5000000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
		&ringout_inputs,
        ringout_eeprom_dump
    },
    // Samba De Amigo (Rev B)
    {
        "samba",
        NULL,
        "Samba De Amigo (Rev B)",
        0x08800000,
        0x280a8b5d,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22966b.ic22",0x0000000, 0x0400000 }, // was also found in cartridge with Rev.A case label
            { "mpr-22950.ic1",  0x0800000, 0x0800000 },
            { "mpr-22951.ic2",  0x1000000, 0x0800000 },
            { "mpr-22952.ic3",  0x1800000, 0x0800000 },
            { "mpr-22953.ic4",  0x2000000, 0x0800000 },
            { "mpr-22954.ic5",  0x2800000, 0x0800000 },
            { "mpr-22955.ic6",  0x3000000, 0x0800000 },
            { "mpr-22956.ic7",  0x3800000, 0x0800000 },
            { "mpr-22957.ic8",  0x4000000, 0x0800000 },
            { "mpr-22958.ic9",  0x4800000, 0x0800000 },
            { "mpr-22959.ic10", 0x5000000, 0x0800000 },
            { "mpr-22960.ic11", 0x5800000, 0x0800000 },
            { "mpr-22961.ic12s",0x6000000, 0x0800000 },
            { "mpr-22962.ic13s",0x6800000, 0x0800000 },
            { "mpr-22963.ic14s",0x7000000, 0x0800000 },
            { "mpr-22964.ic15s",0x7800000, 0x0800000 },
            { "mpr-22965.ic16s",0x8000000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Samba De Amigo (Rev A)
    {
        "sambaa",
        "samba",
        "Samba De Amigo (Rev A)",
        0x08800000,
        0x280a8b5d,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22966a.ic22", 0x0000000, 0x0400000 },
            { "mpr-22950.ic1",   0x0800000, 0x0800000 },
            { "mpr-22951.ic2",   0x1000000, 0x0800000 },
            { "mpr-22952.ic3",   0x1800000, 0x0800000 },
            { "mpr-22953.ic4",   0x2000000, 0x0800000 },
            { "mpr-22954.ic5",   0x2800000, 0x0800000 },
            { "mpr-22955.ic6",   0x3000000, 0x0800000 },
            { "mpr-22956.ic7",   0x3800000, 0x0800000 },
            { "mpr-22957.ic8",   0x4000000, 0x0800000 },
            { "mpr-22958.ic9",   0x4800000, 0x0800000 },
            { "mpr-22959.ic10",  0x5000000, 0x0800000 },
            { "mpr-22960.ic11",  0x5800000, 0x0800000 },
            { "mpr-22961.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22962.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22963.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22964.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22965.ic16s", 0x8000000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Samba De Amigo (USA, prototype)
    {
        "sambap",
        "samba",
        "Samba De Amigo (USA, prototype)",
        0x08800000,
        0x280a8b5d,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "sambaproto.ic22", 0x000000,   0x0400000  },
            { "rom1.ic1s",       0x00800000, 0x00800000 },
            { "rom2.ic2s",       0x01000000, 0x00800000 },
            { "rom3.ic3s",       0x01800000, 0x00800000 },
            { "rom4.ic4s",       0x02000000, 0x00800000 },
            { "rom5.ic5s",       0x02800000, 0x00800000 },
            { "rom6.ic6s",       0x03000000, 0x00800000 },
            { "rom7.ic7s",       0x03800000, 0x00800000 },
            { "rom8.ic8s",       0x04000000, 0x00800000 },
            { "rom9.ic9s",       0x04800000, 0x00800000 },
            { "rom10.ic10s",     0x05000000, 0x00800000 },
            { "rom11.ic11s",     0x05800000, 0x00800000 },
            { "rom12.ic12s",     0x06000000, 0x00800000 },
            { "rom13.ic13s",     0x06800000, 0x00800000 },
            { "rom14.ic14s",     0x07000000, 0x00800000 },
            { NULL, 0, 0 },
        }
    },
    //Samba de Amigo ver. 2000 (Japan)
    {
        "samba2k",
        NULL,
        "Samba de Amigo ver. 2000 (Japan)",
        0x0b800000,
        0x281702cf,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-23600.ic22", 0x00000000, 0x0400000 },
            { "mpr-23589.ic1",  0x00800000, 0x1000000 },
            { "mpr-23590.ic2",  0x01800000, 0x1000000 },
            { "mpr-23591.ic3",  0x02800000, 0x1000000 },
            { "mpr-23592.ic4",  0x03800000, 0x1000000 },
            { "mpr-23593.ic5",  0x04800000, 0x1000000 },
            { "mpr-23594.ic6",  0x05800000, 0x1000000 },
            { "mpr-23595.ic7",  0x06800000, 0x1000000 },
            { "mpr-23596.ic8",  0x07800000, 0x1000000 },
            { "mpr-23597.ic9",  0x08800000, 0x1000000 },
            { "mpr-23598.ic10", 0x09800000, 0x1000000 },
            { "mpr-23599.ic11", 0x0a800000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Sega Tetris
    {
        "sgtetris",
        NULL,
        "Sega Tetris",
        0x03800000,
        0x2808ae51,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            {  "epr-22909.ic22", 0x0000000, 0x200000 },
            {  "epr-22909.ic22", 0x0200000, 0x200000 }, // reload
            {  "mpr-22910.ic1", 0x0800000, 0x800000 },
            {  "mpr-22911.ic2", 0x1000000, 0x800000 },
            {  "mpr-22912.ic3", 0x1800000, 0x800000 },
            {  "mpr-22913.ic4", 0x2000000, 0x800000 },
            {  "mpr-22914.ic5", 0x2800000, 0x800000 },
            {  "mpr-22915.ic6", 0x3000000, 0x800000 },
            { NULL, 0, 0 },
        }
        // SW1/2
    },
    // Dengen Tenshi Taisen Janshi Shangri-la (JPN, USA, EXP, KOR, AUS)
    {
        "shangril",
        NULL,
        "Dengen Tenshi Taisen Janshi Shangri-la",
        0x06800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22060.ic22",  0x0000000, 0x0400000 },
            { "mpr-22061.ic1",   0x0800000, 0x0800000 },
            { "mpr-22062.ic2",   0x1000000, 0x0800000 },
            { "mpr-22063.ic3",   0x1800000, 0x0800000 },
            { "mpr-22064.ic4",   0x2000000, 0x0800000 },
            { "mpr-22065.ic5",   0x2800000, 0x0800000 },
            { "mpr-22066.ic6",   0x3000000, 0x0800000 },
            { "mpr-22067.ic7",   0x3800000, 0x0800000 },
            { "mpr-22068.ic8",   0x4000000, 0x0800000 },
            { "mpr-22069.ic9",   0x4800000, 0x0800000 },
            { "mpr-22070.ic10",  0x5000000, 0x0800000 },
            { "mpr-22071.ic11",  0x5800000, 0x0800000 },
            { "mpr-22072.ic12s", 0x6000000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Star Horse (satellite)
    {
        "shorse",
        NULL,
        "Star Horse (satellite)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "epr-23627.ic22", 0x0000000, 0x0400000 },
            { "mpr-23275.ic1",  0x0800000, 0x1000000 },
            { "mpr-23276.ic2",  0x1800000, 0x1000000 },
            { "mpr-23277.ic3",  0x2800000, 0x1000000 },
            { "mpr-23278.ic4",  0x3800000, 0x1000000 },
            { "mpr-23279.ic5",  0x4800000, 0x1000000 },
            { "mpr-23280.ic6",  0x5800000, 0x1000000 },
            { "mpr-23281.ic7",  0x6800000, 0x0800000 },

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD( "sflash.ic46",   0x000000, 0x000084, CRC(4929e940) SHA1(f8c4277ca0ae5e36b2eed033cc731b8fc4fccafc) )

            { NULL, 0, 0 },
        }
    },
    // Star Horse (live and backup)
    {
        "shorsel",
        "shorse",
        "Star Horse (live and backup)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23626.ic22", 0x0000000, 0x200000 },
            { "epr-23626.ic22", 0x0200000, 0x200000 }, //reload
            { "rom1.ic1s",      0x0800000, 0x800000 },
            { "rom2.ic2s",      0x1000000, 0x800000 },
            { "rom3.ic3s",      0x1800000, 0x800000 },
            { "rom4.ic4s",      0x2000000, 0x800000 },
            { "rom5.ic5s",      0x2800000, 0x800000 },
            { "rom6.ic6s",      0x3000000, 0x800000 },
            { "rom7.ic7s",      0x3800000, 0x800000 },
            { "rom8.ic8s",      0x4000000, 0x800000 },
            { "rom9.ic9s",      0x4800000, 0x800000 },
            { "rom10.ic10s",    0x5000000, 0x800000 },
            { "rom11.ic11s",    0x5800000, 0x800000 },
            { "rom12.ic12s",    0x6000000, 0x800000 },
            { "rom13.ic13s",    0x6800000, 0x800000 },
            { "rom14.ic14s",    0x7000000, 0x800000 },
            { "rom15.ic15s",    0x7800000, 0x800000 },
            { "rom16.ic16s",    0x8000000, 0x800000 },
            { "rom17.ic17s",    0x8800000, 0x800000 },
            // .18s chip is not present but is tested for an FF fill (pull-up resistors on the PCB's data bus presumably accomplish this)

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD( "sflash.ic37",   0x000000, 0x000084, CRC(1557297e) SHA1(41e8a7a8eaf5076b124d378afdf97e328d100e72) )

            { NULL, 0, 0 },
        }
    },
    // Star Horse (main screens)
    {
        "shorsem",
        "shorse",
        "Star Horse (main screens)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23625.ic22", 0x0000000, 0x0400000 },
            { "mpr-23231.ic1",  0x0800000, 0x1000000 },
            { "mpr-23232.ic2",  0x1800000, 0x1000000 },
            { "mpr-23233.ic3",  0x2800000, 0x1000000 },
            { "mpr-23234.ic4",  0x3800000, 0x1000000 },

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD( "sflash.ic46",   0x000000, 0x000084, CRC(951684e4) SHA1(0beaf5827064252293223b946c04b8698e7207bb) )

            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress (satellite, Rev A)
    {
        "shorsep",
        NULL,
        "Star Horse Progress (satellite, Rev A)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "epr-24122a.ic22", 0x0000000, 0x0400000 },
            { "mpr-24123.ic1",   0x0800000, 0x1000000 },
            { "mpr-24124.ic2",   0x1800000, 0x1000000 },
            { "mpr-24125.ic3",   0x2800000, 0x1000000 },
            { "mpr-24126.ic4",   0x3800000, 0x1000000 },
            { "mpr-24127.ic5",   0x4800000, 0x1000000 },
            { "mpr-24128.ic6",   0x5800000, 0x1000000 },
            { "mpr-24129.ic7",   0x6800000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress (backup data)
    {
        "shorsepb",
        "shorsep",
        "Star Horse Progress (backup data)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "rom1.ic1s",   0x00800000, 0x00800000 },
            { "rom2.ic2s",   0x01000000, 0x00800000 },

            //ROM_REGION(0x84, "some_eeprom", 0)
            //ROM_LOAD( "sflash.ic37",   0x000000, 0x000084, CRC(fe8f8f5c) SHA1(839461ab736e0228dec7e2512e1692d6ecc4e664) )

            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress (live, Rev A)
    {
        "shorsepl",
        "shorsep",
        "Star Horse Progress (live, Rev A)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24107a.ic22", 0x00000000, 0x00400000 },
            { "mpr-24108.ic1",   0x00800000, 0x01000000 },
            { "mpr-24109.ic2",   0x01800000, 0x01000000 },
            { "mpr-24110.ic3",   0x02800000, 0x01000000 },
            { "mpr-24111.ic4",   0x03800000, 0x01000000 },
            { "mpr-24112.ic5",   0x04800000, 0x01000000 },
            { "mpr-24113.ic6",   0x05800000, 0x01000000 },
            { "mpr-24114.ic7",   0x06800000, 0x01000000 },
            { "mpr-24115.ic8",   0x07800000, 0x01000000 },
            { "mpr-24116.ic9",   0x08800000, 0x01000000 },
            { "mpr-24117.ic10",  0x09800000, 0x01000000 },
            { "mpr-24118.ic11",  0x0a800000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress (main screens)
    {
        "shorsepm",
        "shorsep",
        "Star Horse Progress (main screens, Rev B)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24087b.ic22", 0x00000000, 0x00400000 },
            { "mpr-24088.ic1",   0x00800000, 0x01000000 },
            { "mpr-24089.ic2",   0x01800000, 0x01000000 },
            { "mpr-24090.ic3",   0x02800000, 0x01000000 },
            { "mpr-24091.ic4",   0x03800000, 0x01000000 },
            { "mpr-24092.ic5",   0x04800000, 0x01000000 },
            { "mpr-24093.ic6",   0x05800000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress (sound & backup)
    {
        "shorseps",
        "shorsep",
        "Star Horse Progress (sound & backup, Rev A)",
        0x7000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24097a.ic22", 0x00000000, 0x00400000 },
            { "mpr-24098.ic1",   0x00800000, 0x01000000 },
            { "mpr-24099.ic2",   0x01800000, 0x01000000 },
            { "mpr-24100.ic3",   0x02800000, 0x01000000 },
            { "mpr-24101.ic4",   0x03800000, 0x01000000 },
            { "mpr-24102.ic5",   0x04800000, 0x01000000 },
            { "mpr-24103.ic6",   0x05800000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Star Horse 2001 (satellite, Rev B)
    {
        "shors2k1",
        NULL,
        "Star Horse 2001 (satellite, Rev B)",
        0x7800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "epr-23739b.ic22", 0x00000000, 0x00400000 },
            { "mpr-23740.ic1",   0x00800000, 0x01000000 },
            { "mpr-23741.ic2",   0x01800000, 0x01000000 },
            { "mpr-23742.ic3",   0x02800000, 0x01000000 },
            { "mpr-23743.ic4",   0x03800000, 0x01000000 },
            { "mpr-23744.ic5",   0x04800000, 0x01000000 },
            { "mpr-23745.ic6",   0x05800000, 0x01000000 },
            { "mpr-23746.ic7",   0x06800000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Super Major League '99
    {
        "smlg99",
        NULL,
        "World Series 99 / Super Major League 99",
        0x0b000000,
        0x28048a01,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22059.ic22",  0x0000000, 0x200000 },
            { "epr-22059.ic22",  0x0200000, 0x200000 }, // reload
            { "mpr-22038.ic1",   0x0800000, 0x800000 },
            { "mpr-22039.ic2",   0x1000000, 0x800000 },
            { "mpr-22040.ic3",   0x1800000, 0x800000 },
            { "mpr-22041.ic4",   0x2000000, 0x800000 },
            { "mpr-22042.ic5",   0x2800000, 0x800000 },
            { "mpr-22043.ic6",   0x3000000, 0x800000 },
            { "mpr-22044.ic7",   0x3800000, 0x800000 },
            { "mpr-22045.ic8",   0x4000000, 0x800000 },
            { "mpr-22046.ic9",   0x4800000, 0x800000 },
            { "mpr-22047.ic10",  0x5000000, 0x800000 },
            { "mpr-22048.ic11",  0x5800000, 0x800000 },
            { "mpr-22049.ic12s", 0x6000000, 0x800000 },
            { "mpr-22050.ic13s", 0x6800000, 0x800000 },
            { "mpr-22051.ic14s", 0x7000000, 0x800000 },
            { "mpr-22052.ic15s", 0x7800000, 0x800000 },
            { "mpr-22053.ic16s", 0x8000000, 0x800000 },
            { "mpr-22054.ic17s", 0x8800000, 0x800000 },
            { "mpr-22055.ic18s", 0x9000000, 0x800000 },
            { "mpr-22056.ic19s", 0x9800000, 0x800000 },
            { "mpr-22057.ic20s", 0xa000000, 0x800000 },
            { "mpr-22058.ic21s", 0xa800000, 0x800000 },
            { NULL, 0, 0 },
        },
		NULL,
		&wsbb_inputs,
    },
    // Slashout
    {
        "slasho",
        NULL,
        "Slashout",
        0x09000000,
        0x281a66ca,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23341.ic22", 0x0000000, 0x0400000 },
            { "mpr-23324.ic1",  0x0800000, 0x0800000 },
            { "mpr-23325.ic2",  0x1000000, 0x0800000 },
            { "mpr-23326.ic3",  0x1800000, 0x0800000 },
            { "mpr-23327.ic4",  0x2000000, 0x0800000 },
            { "mpr-23328.ic5",  0x2800000, 0x0800000 },
            { "mpr-23329.ic6",  0x3000000, 0x0800000 },
            { "mpr-23330.ic7",  0x3800000, 0x0800000 },
            { "mpr-23331.ic8",  0x4000000, 0x0800000 },
            { "mpr-23332.ic9",  0x4800000, 0x0800000 },
            { "mpr-23333.ic10", 0x5000000, 0x0800000 },
            { "mpr-23334.ic11", 0x5800000, 0x0800000 },
            { "mpr-23335.ic12s",0x6000000, 0x0800000 },
            { "mpr-23336.ic13s",0x6800000, 0x0800000 },
            { "mpr-23337.ic14s",0x7000000, 0x0800000 },
            { "mpr-23338.ic15s",0x7800000, 0x0800000 },
            { "mpr-23339.ic16s",0x8000000, 0x0800000 },
            { "mpr-23340.ic17s",0x8800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		NULL,
		&slashout_inputs,
		slashout_eeprom_dump
    },
    // Sega Marine Fishing
    {
        "smarinef",
        NULL,
        "Sega Marine Fishing",
        0x06800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22221.ic22",  0x0000000, 0x0400000 },
            { "mpr-22208.ic1",   0x0800000, 0x0800000 },
            { "mpr-22209.ic2",   0x1000000, 0x0800000 },
            // IC3 empty
            // IC4 empty
            { "mpr-22212.ic5",   0x2800000, 0x0800000 },
            { "mpr-22213.ic6",   0x3000000, 0x0800000 },
            { "mpr-22214.ic7",   0x3800000, 0x0800000 },
            { "mpr-22215.ic8",   0x4000000, 0x0800000 },
            { "mpr-22216.ic9",   0x4800000, 0x0800000 },
            { "mpr-22217.ic10",  0x5000000, 0x0800000 },
            { "mpr-22218.ic11",  0x5800000, 0x0800000 },
            { "mpr-22219.ic12s", 0x6000000, 0x0800000 },
            { NULL, 0, 0 },
        },
		NULL,
		&marine_fishing_inputs,
    },
    // Spawn In the Demon's Hand (JPN, USA, EUR, ASI, AUS) (Rev B)
    {
        "spawn",
        NULL,
        "Spawn In the Demon's Hand (Rev B)",
        0x05800000,
        0x00078d01,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22977b.ic22", 0x0000000, 0x0400000 },
            { "mpr-22967.ic1",   0x0800000, 0x0800000 },
            { "mpr-22968.ic2",   0x1000000, 0x0800000 },
            { "mpr-22969.ic3",   0x1800000, 0x0800000 },
            { "mpr-22970.ic4",   0x2000000, 0x0800000 },
            { "mpr-22971.ic5",   0x2800000, 0x0800000 },
            { "mpr-22972.ic6",   0x3000000, 0x0800000 },
            { "mpr-22973.ic7",   0x3800000, 0x0800000 },
            { "mpr-22974.ic8",   0x4000000, 0x0800000 },
            { "mpr-22975.ic9",   0x4800000, 0x0800000 },
            { "mpr-22976.ic10",  0x5000000, 0x0800000 },
            { NULL, 0, 0 },
        },
        NULL,
		&shot1234_inputs,
        spawn_eeprom_dump
    },
    // Sega Strike Fighter (Rev A)
    {
        "sstrkfgt",
        NULL,
        "Sega Strike Fighter (Rev A)",
        0x0b000000,
        0x28132303,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23323a.ic22", 0x0000000, 0x400000 },
            { "mpr-23302.ic1",   0x0800000, 0x800000 },
            { "mpr-23303.ic2",   0x1000000, 0x800000 },
            { "mpr-23304.ic3",   0x1800000, 0x800000 },
            { "mpr-23305.ic4",   0x2000000, 0x800000 },
            { "mpr-23306.ic5",   0x2800000, 0x800000 },
            { "mpr-23307.ic6",   0x3000000, 0x800000 },
            { "mpr-23308.ic7",   0x3800000, 0x800000 },
            { "mpr-23309.ic8",   0x4000000, 0x800000 },
            { "mpr-23310.ic9",   0x4800000, 0x800000 },
            { "mpr-23311.ic10",  0x5000000, 0x800000 },
            { "mpr-23312.ic11",  0x5800000, 0x800000 },
            { "mpr-23313.ic12s", 0x6000000, 0x800000 },
            { "mpr-23314.ic13s", 0x6800000, 0x800000 },
            { "mpr-23315.ic14s", 0x7000000, 0x800000 },
            { "mpr-23316.ic15s", 0x7800000, 0x800000 },
            { "mpr-23317.ic16s", 0x8000000, 0x800000 },
            { "mpr-23318.ic17s", 0x8800000, 0x800000 },
            { "mpr-23319.ic18s", 0x9000000, 0x800000 },
            { "mpr-23320.ic19s", 0x9800000, 0x800000 },
            { "mpr-23321.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&sstrkfgt_inputs,
    },
    // Sega Strike Fighter (Rev A, no training mode)
    {
        "sstrkfgta",
        "sstrkfgt",
        "Sega Strike Fighter (Rev A, no training mode)",
        0x0b000000,
        0x28132303,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23786a.ic22", 0x0000000, 0x400000 },
            { "mpr-23302.ic1",   0x0800000, 0x800000 },
            { "mpr-23303.ic2",   0x1000000, 0x800000 },
            { "mpr-23304.ic3",   0x1800000, 0x800000 },
            { "mpr-23305.ic4",   0x2000000, 0x800000 },
            { "mpr-23306.ic5",   0x2800000, 0x800000 },
            { "mpr-23307.ic6",   0x3000000, 0x800000 },
            { "mpr-23308.ic7",   0x3800000, 0x800000 },
            { "mpr-23309.ic8",   0x4000000, 0x800000 },
            { "mpr-23310.ic9",   0x4800000, 0x800000 },
            { "mpr-23311.ic10",  0x5000000, 0x800000 },
            { "mpr-23312.ic11",  0x5800000, 0x800000 },
            { "mpr-23313.ic12s", 0x6000000, 0x800000 },
            { "mpr-23314.ic13s", 0x6800000, 0x800000 },
            { "mpr-23315.ic14s", 0x7000000, 0x800000 },
            { "mpr-23316.ic15s", 0x7800000, 0x800000 },
            { "mpr-23317.ic16s", 0x8000000, 0x800000 },
            { "mpr-23318.ic17s", 0x8800000, 0x800000 },
            { "mpr-23319.ic18s", 0x9000000, 0x800000 },
            { "mpr-23320.ic19s", 0x9800000, 0x800000 },
            { "mpr-23321.ic20s", 0xa000000, 0x800000 },
            { NULL, 0, 0 },
        },
		nullptr,
		&sstrkfgt_inputs,
    },
    // Idol Janshi Suchie-Pai 3 (JPN)
    {
        "suchie3",
        NULL,
        "Idol Janshi Suchie-Pai 3 (Japan)",
        0x07800000,
        0x000368e1,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-21979.ic22", 0x0000000, 0x0200000 },
            { "epr-21979.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-21980.ic1",  0x0800000, 0x0800000 },
            { "mpr-21981.ic2",  0x1000000, 0x0800000 },
            { "mpr-21982.ic3",  0x1800000, 0x0800000 },
            { "mpr-21983.ic4",  0x2000000, 0x0800000 },
            { "mpr-21984.ic5",  0x2800000, 0x0800000 },
            { "mpr-21985.ic6",  0x3000000, 0x0800000 },
            { "mpr-21986.ic7",  0x3800000, 0x0800000 },
            { "mpr-21987.ic8",  0x4000000, 0x0800000 },
            { "mpr-21988.ic9",  0x4800000, 0x0800000 },
            { "mpr-21989.ic10", 0x5000000, 0x0800000 },
            { "mpr-21990.ic11", 0x5800000, 0x0800000 },
            { "mpr-21991.ic12s",0x6000000, 0x0800000 },
            { "mpr-21992.ic13s",0x6800000, 0x0800000 },
            { "mpr-21993.ic14s",0x7000000, 0x0400000 },
            { NULL, 0, 0 },
        }
    },
    // Touch de Uno! / Unou Nouryoku Check Machine
    {
        "tduno",
        NULL,
        "Touch de Uno! / Unou Nouryoku Check Machine (Japan)",
        0x04000000,
        0x28028ea5,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            //ROM_REGION16_BE( 0x80, "main_eeprom", 0 )
            //ROM_LOAD16_WORD("main_eeprom.bin", 0x0000, 0x0080, CRC(fea29cbb) SHA1(4099f1747aafa07db34f6e072cd9bfaa83bae10e) )

            { "epr-22073.ic22", 0x0000000, 0x200000 },
            { "epr-22073.ic22", 0x0200000, 0x200000 }, // reload
            { "mpr-22074.ic1",  0x0800000, 0x800000 },
            { "mpr-22075.ic2",  0x1000000, 0x800000 },
            { "mpr-22076.ic3",  0x1800000, 0x800000 },
            { "mpr-22077.ic4",  0x2000000, 0x400000 },

            // on-cart X76F100 eeprom contents
            //ROM_REGION( 0x84, "naomibd_eeprom", 0 )
            //ROM_LOAD( "x76f100.ic37", 0x000000, 0x000084, CRC(c79251d5) SHA1(3e70bbbb6d28bade7eec7e27d716463045656f98) )

            { NULL, 0, 0 },
        }
    },
	// Tokyo Bus
	{
		"tokyobus",
		NULL,
		"Tokyo Bus Guide (Rev A)",
		0x09800000,
		0x281e1242,
		NULL,
		M2,
		REGION_JAPAN,
		ROT0,
		{
			{ "epr-23468a.ic22", 0x0000000, 0x0400000 },
			{ "rom1.ic1s",       0x0800000, 0x0800000 },
			{ "rom2.ic2s",       0x1000000, 0x0800000 },
			{ "rom3.ic3s",       0x1800000, 0x0800000 },
			{ "rom4.ic4s",       0x2000000, 0x0800000 },
			{ "rom5.ic5s",       0x2800000, 0x0800000 },
			{ "rom6.ic6s",       0x3000000, 0x0800000 },
			{ "rom7.ic7s",       0x3800000, 0x0800000 },
			{ "rom8.ic8s",       0x4000000, 0x0800000 },
			{ "rom9.ic9s",       0x4800000, 0x0800000 },
			{ "rom10.ic10s",     0x5000000, 0x0800000 },
			{ "rom11.ic11s",     0x5800000, 0x0800000 },
			{ "rom12.ic12s",     0x6000000, 0x0800000 },
			{ "rom13.ic13s",     0x6800000, 0x0800000 },
			{ "rom14.ic14s",     0x7000000, 0x0800000 },
			{ "rom15.ic15s",     0x7800000, 0x0800000 },
			{ "rom16.ic16s",     0x8000000, 0x0800000 },
			{ "rom17.ic17s",     0x8800000, 0x0800000 },
			{ "rom18.ic18s",     0x9000000, 0x0800000 },
            { NULL, 0, 0 },
		},
		NULL,
		&tokyobus_inputs,
	},
    // The Typing of the Dead (Rev A)
    {
        "totd",
        NULL,
        "The Typing of the Dead (Rev A)",
        0x0b000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23021a.ic22", 0x0000000, 0x0400000 },

            { "mpr-23001.ic1",   0x0800000, 0x0800000 },
            { "mpr-23002.ic2",   0x1000000, 0x0800000 },
            { "mpr-23003.ic3",   0x1800000, 0x0800000 },
            { "mpr-23004.ic4",   0x2000000, 0x0800000 },
            { "mpr-23005.ic5",   0x2800000, 0x0800000 },
            // IC6 not populated
            { "mpr-23007.ic7",   0x3800000, 0x0800000 },
            { "mpr-23008.ic8",   0x4000000, 0x0800000 },
            { "mpr-23009.ic9",   0x4800000, 0x0800000 },
            { "mpr-23010.ic10",  0x5000000, 0x0800000 },
            { "mpr-23011.ic11",  0x5800000, 0x0800000 },
            { "mpr-23012.ic12s", 0x6000000, 0x0800000 },
            // IC13S not populated
            { "mpr-23014.ic14s", 0x7000000, 0x0800000 },
            { "mpr-23015.ic15s", 0x7800000, 0x0800000 },
            { "mpr-23016.ic16s", 0x8000000, 0x0800000 },
            { "mpr-23017.ic17s", 0x8800000, 0x0800000 },
            { "mpr-23018.ic18s", 0x9000000, 0x0800000 },
            { "mpr-23019.ic19s", 0x9800000, 0x0800000 },
            { "mpr-23020.ic20s", 0xa000000, 0x0800000 },
            // IC21s not populated
            { NULL, 0, 0 },
        }
    },
    // The Typing of the Dead
    {
        "totdo",
        "totd",
        "The Typing of the Dead",
        0x0b000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23021.ic22",  0x0000000, 0x0400000 },
            { "mpr-23001.ic1",   0x0800000, 0x0800000 },
            { "mpr-23002.ic2",   0x1000000, 0x0800000 },
            { "mpr-23003.ic3",   0x1800000, 0x0800000 },
            { "mpr-23004.ic4",   0x2000000, 0x0800000 },
            { "mpr-23005.ic5",   0x2800000, 0x0800000 },
            // IC6 not populated
            { "mpr-23007.ic7",   0x3800000, 0x0800000 },
            { "mpr-23008.ic8",   0x4000000, 0x0800000 },
            { "mpr-23009.ic9",   0x4800000, 0x0800000 },
            { "mpr-23010.ic10",  0x5000000, 0x0800000 },
            { "mpr-23011.ic11",  0x5800000, 0x0800000 },
            { "mpr-23012.ic12s", 0x6000000, 0x0800000 },
            // IC13S not populated
            { "mpr-23014.ic14s", 0x7000000, 0x0800000 },
            { "mpr-23015.ic15s", 0x7800000, 0x0800000 },
            { "mpr-23016.ic16s", 0x8000000, 0x0800000 },
            { "mpr-23017.ic17s", 0x8800000, 0x0800000 },
            { "mpr-23018.ic18s", 0x9000000, 0x0800000 },
            { "mpr-23019.ic19s", 0x9800000, 0x0800000 },
            { "mpr-23020.ic20s", 0xa000000, 0x0800000 },
            // IC21S not populated
            { NULL, 0, 0 },
        }
    },
    // Shin Nihon Pro Wrestling Toukon Retsuden 4 Arcade Edition (TRF1 Ver. A)
    {
        "toukon4",
        NULL,
        "Shin Nihon Pro Wrestling Toukon Retsuden 4 Arcade Edition (Japan, TRF1 Ver.A)",
        0x10000000,
        0x052e2901,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "trf1vera.2f", 0x0000000, 0x0800000 },
            { "trf1vera.2d", 0x0800000, 0x0800000 },
            { "trf1ma1.4n",  0x1000000, 0x1000000 },
            { "trf1ma2.4m",  0x2000000, 0x1000000 },
            { "trf1ma3.4l",  0x3000000, 0x1000000 },
            { "trf1ma4.4k",  0x4000000, 0x1000000 },
            { "trf1ma5.4j",  0x5000000, 0x1000000 },
            { "trf1ma6.4h",  0x6000000, 0x1000000 },
            { "trf1ma7.4f",  0x7000000, 0x1000000 },
            { "trf1ma8.4e",  0x8000000, 0x1000000 },
            { "trf1ma9.4d",  0x9000000, 0x1000000 },
            { "trf1ma10.4c", 0xa000000, 0x1000000 },
            { "trf1ma11.4b", 0xb000000, 0x1000000 },
            { "trf1ma12.6p", 0xc000000, 0x1000000 },
            { "trf1ma13.6n", 0xd000000, 0x1000000 },
            { "trf1ma14.6m", 0xe000000, 0x1000000 },
            { "trf1ma15.6l", 0xf000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Toy Fighter
    {
        "toyfight",
        NULL,
        "Toy Fighter",
        0x08000000,
        0x2802ca85,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22035.ic22",0x0000000, 0x0400000 },
            { "mpr-22025.ic1", 0x0800000, 0x0800000 },
            { "mpr-22026.ic2", 0x1000000, 0x0800000 },
            { "mpr-22027.ic3", 0x1800000, 0x0800000 },
            { "mpr-22028.ic4", 0x2000000, 0x0800000 },
            { "mpr-22029.ic5", 0x2800000, 0x0800000 },
            { "mpr-22030.ic6", 0x3000000, 0x0800000 },
            { "mpr-22031.ic7", 0x3800000, 0x0800000 },
            { "mpr-22032.ic8", 0x4000000, 0x0800000 },
            { "mpr-22033.ic9", 0x4800000, 0x0800000 },
            { "mpr-22034.ic10",0x5000000, 0x0800000 },
            { NULL, 0, 0 },
        }
        // PUNCH, KICK, DODGE, N/A,
        // JUMP, CROUCH, LEFT/RIGHT MOVE
    },
    // Virtua NBA (USA)
    {
        "virnba",
        NULL,
        "Virtua NBA (USA)",
        0x0b000000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23073.ic22",  0x0000000, 0x0400000 },
            { "mpr-22928.ic1",   0x0800000, 0x0800000 },
            { "mpr-22929.ic2",   0x1000000, 0x0800000 },
            { "mpr-22930.ic3",   0x1800000, 0x0800000 },
            { "mpr-22931.ic4",   0x2000000, 0x0800000 },
            { "mpr-22932.ic5",   0x2800000, 0x0800000 },
            { "mpr-22933.ic6",   0x3000000, 0x0800000 },
            { "mpr-22934.ic7",   0x3800000, 0x0800000 },
            { "mpr-22935.ic8",   0x4000000, 0x0800000 },
            { "mpr-22936.ic9",   0x4800000, 0x0800000 },
            { "mpr-22937.ic10",  0x5000000, 0x0800000 },
            { "mpr-22938.ic11",  0x5800000, 0x0800000 },
            { "mpr-22939.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22940.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22941.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22942.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22943.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22944.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22945.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22946.ic19s", 0x9800000, 0x0800000 },
            { "mpr-22947.ic20s", 0xa000000, 0x0800000 },
            { "mpr-22948.ic21s", 0xa800000, 0x0800000 },
            { NULL, 0, 0 },
        }
        // PASS, SHOOT
    },
    // Virtua NBA
    {
        "virnbao",
        "virnba",
        "Virtua NBA",
        0x0b000000,
        0x28068b58,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22949.ic22",  0x0000000, 0x0400000 },
            { "mpr-22928.ic1",   0x0800000, 0x0800000 },
            { "mpr-22929.ic2",   0x1000000, 0x0800000 },
            { "mpr-22930.ic3",   0x1800000, 0x0800000 },
            { "mpr-22931.ic4",   0x2000000, 0x0800000 },
            { "mpr-22932.ic5",   0x2800000, 0x0800000 },
            { "mpr-22933.ic6",   0x3000000, 0x0800000 },
            { "mpr-22934.ic7",   0x3800000, 0x0800000 },
            { "mpr-22935.ic8",   0x4000000, 0x0800000 },
            { "mpr-22936.ic9",   0x4800000, 0x0800000 },
            { "mpr-22937.ic10",  0x5000000, 0x0800000 },
            { "mpr-22938.ic11",  0x5800000, 0x0800000 },
            { "mpr-22939.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22940.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22941.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22942.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22943.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22944.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22945.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22946.ic19s", 0x9800000, 0x0800000 },
            { "mpr-22947.ic20s", 0xa000000, 0x0800000 },
            { "mpr-22948.ic21s", 0xa800000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Virtua NBA (prototype)
    {
        "virnbap",
        "virnba",
        "Virtua NBA (prototype)",
        0x0b000000,
        0x28068b58,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "vnbaearly.ic22",  0x0000000, 0x0400000 },
            { "mpr-22928.ic1",   0x0800000, 0x0800000 },
            { "mpr-22929.ic2",   0x1000000, 0x0800000 },
            { "mpr-22930.ic3",   0x1800000, 0x0800000 },
            { "mpr-22931.ic4",   0x2000000, 0x0800000 },
            { "mpr-22932.ic5",   0x2800000, 0x0800000 },
            { "mpr-22933.ic6",   0x3000000, 0x0800000 },
            { "mpr-22934.ic7",   0x3800000, 0x0800000 },
            { "mpr-22935.ic8",   0x4000000, 0x0800000 },
            { "mpr-22936.ic9",   0x4800000, 0x0800000 },
            { "mpr-22937.ic10",  0x5000000, 0x0800000 },
            { "mpr-22938.ic11",  0x5800000, 0x0800000 },
            { "mpr-22939.ic12s", 0x6000000, 0x0800000 },
            { "mpr-22940.ic13s", 0x6800000, 0x0800000 },
            { "mpr-22941.ic14s", 0x7000000, 0x0800000 },
            { "mpr-22942.ic15s", 0x7800000, 0x0800000 },
            { "mpr-22943.ic16s", 0x8000000, 0x0800000 },
            { "mpr-22944.ic17s", 0x8800000, 0x0800000 },
            { "mpr-22945.ic18s", 0x9000000, 0x0800000 },
            { "mpr-22946.ic19s", 0x9800000, 0x0800000 },
            { "mpr-22947.ic20s", 0xa000000, 0x0800000 },
            { "mpr-22948.ic21s", 0xa800000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Virtua NBA (prototype, 15.11)
    {
        "virnbapa",
        "virnba",
        "Virtua NBA (prototype, 15.11)",
        0x0b000000,
        0x28068b58,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "11-15.ic22",      0x0000000, 0x0400000 },
            { "rom1.ic1s",       0x0800000, 0x0800000 },
            { "rom2.ic2s",       0x1000000, 0x0800000 },
            { "rom3.ic3s",       0x1800000, 0x0800000 },
            { "rom4.ic4s",       0x2000000, 0x0800000 },
            { "rom5.ic5s",       0x2800000, 0x0800000 },
            { "rom6.ic6s",       0x3000000, 0x0800000 },
            { "rom7.ic7s",       0x3800000, 0x0800000 },
            { "rom8.ic8s",       0x4000000, 0x0800000 },
            { "rom9.ic9s",       0x4800000, 0x0800000 },
            { "rom10.ic10s",     0x5000000, 0x0800000 },
            { "rom11.ic11s",     0x5800000, 0x0800000 },
            { "rom12.ic12s",     0x6000000, 0x0800000 },
            { "rom13.ic13s",     0x6800000, 0x0800000 },
            { "rom14.ic14s",     0x7000000, 0x0800000 },
            { "rom15.ic15s",     0x7800000, 0x0800000 },
            { "rom16.ic16s",     0x8000000, 0x0800000 },
            { "rom17.ic17s",     0x8800000, 0x0800000 },
            { "rom18.ic18s",     0x9000000, 0x0800000 },
            { "rom19.ic19s",     0x9800000, 0x0800000 },
            { "rom20.ic20s",     0xa000000, 0x0800000 },
            { "rom21.ic21s",     0xa800000, 0x0800000 },
            { NULL, 0, 0 },
        }
    },
    // Virtual On Oratorio Tangram M.S.B.S. ver5.66 2000 Edition
    {
        "vonot",
        NULL,
        "Virtual On Oratorio Tangram M.S.B.S. ver5.66 2000 Edition",
        0x07000000,
        0x28010715,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23198.ic22",  0x0000000, 0x400000 },
            { "mpr-23182.ic1",   0x0800000, 0x800000 },
            { "mpr-23183.ic2",   0x1000000, 0x800000 },
            { "mpr-23184.ic3",   0x1800000, 0x800000 },
            { "mpr-23185.ic4",   0x2000000, 0x800000 },
            { "mpr-23186.ic5",   0x2800000, 0x800000 },
            { "mpr-23187.ic6",   0x3000000, 0x800000 },
            { "mpr-23188.ic7",   0x3800000, 0x800000 },
            { "mpr-23189.ic8",   0x4000000, 0x800000 },
            { "mpr-23190.ic9",   0x4800000, 0x800000 },
            { "mpr-23191.ic10",  0x5000000, 0x800000 },
            { "mpr-23192.ic11",  0x5800000, 0x800000 },
            { "mpr-23193.ic12s", 0x6000000, 0x800000 },
            { "mpr-23194.ic13s", 0x6800000, 0x800000 },
            { NULL, 0, 0 },
        },
        NULL,
        &vonot_inputs,
		vonot_eeprom_dump
    },
    // Virtua Striker 2 Ver. 2000 (JPN, USA, EXP, KOR, AUS) (Rev C)
    {
        "vs2_2k",
        NULL,
        "Virtua Striker 2 Ver. 2000 (Rev C)",
        0x8000000,
        0x28088b08,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21929c.ic22",0x0000000, 0x0400000 },
            { "mpr-21924.ic1",  0x0800000, 0x0800000 },
            { "mpr-21925.ic2",  0x1000000, 0x0800000 },
            { "mpr-21911.ic3",  0x1800000, 0x0800000 },
            { "mpr-21926.ic4",  0x2000000, 0x0800000 },
            { "mpr-21913.ic5",  0x2800000, 0x0800000 },
            { "mpr-21914.ic6",  0x3000000, 0x0800000 },
            { "mpr-21915.ic7",  0x3800000, 0x0800000 },
            { "mpr-21916.ic8",  0x4000000, 0x0800000 },
            { "mpr-21917.ic9",  0x4800000, 0x0800000 },
            { "mpr-21918.ic10", 0x5000000, 0x0800000 },
            { "mpr-21919.ic11", 0x5800000, 0x0800000 },
            { "mpr-21920.ic12s",0x6000000, 0x0800000 },
            { "mpr-21921.ic13s",0x6800000, 0x0800000 },
            { "mpr-21922.ic14s",0x7000000, 0x0800000 },
            { "mpr-21923.ic15s",0x7800000, 0x0400000 },
            { NULL, 0, 0 },
        }
        // LONG PASS, SHOOT, SHORT PASS
    },
    // Virtua Striker 2 Ver. 2000
    {
        "vs2_2ko",
        "vs2_2k",
        "Virtua Striker 2 Ver. 2000",
        0x8000000,
        0x28088b08,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            {"epr-21929.ic22",   0x0000000, 0x0400000 },
            { "mpr-21924.ic1",   0x0800000, 0x0800000 },
            { "mpr-21925.ic2",   0x1000000, 0x0800000 },
            { "mpr-21911.ic3",   0x1800000, 0x0800000 },
            { "mpr-21926.ic4",   0x2000000, 0x0800000 },
            { "mpr-21913.ic5",   0x2800000, 0x0800000 },
            { "mpr-21914.ic6",   0x3000000, 0x0800000 },
            { "mpr-21915.ic7",   0x3800000, 0x0800000 },
            { "mpr-21916.ic8",   0x4000000, 0x0800000 },
            { "mpr-21917.ic9",   0x4800000, 0x0800000 },
            { "mpr-21918.ic10",  0x5000000, 0x0800000 },
            { "mpr-21919.ic11",  0x5800000, 0x0800000 },
            { "mpr-21920.ic12s", 0x6000000, 0x0800000 },
            { "mpr-21921.ic13s", 0x6800000, 0x0800000 },
            { "mpr-21922.ic14s", 0x7000000, 0x0800000 },
            { "mpr-21923.ic15s", 0x7800000, 0x0400000 },
            { NULL, 0, 0 },
        }
    },
    // Virtua Tennis (USA, EXP, KOR, AUS) / Power Smash (JPN)
    {
        "vtennis",
        NULL,
        "Virtua Tennis / Power Smash",
        0x06000000,
        0x2803eb15,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22927.ic22", 0x0000000, 0x0400000 },
            { "mpr-22916.ic1", 0x0800000, 0x0800000 },
            { "mpr-22917.ic2", 0x1000000, 0x0800000 },
            { "mpr-22918.ic3", 0x1800000, 0x0800000 },
            { "mpr-22919.ic4", 0x2000000, 0x0800000 },
            { "mpr-22920.ic5", 0x2800000, 0x0800000 },
            { "mpr-22921.ic6", 0x3000000, 0x0800000 },
            { "mpr-22922.ic7", 0x3800000, 0x0800000 },
            { "mpr-22923.ic8", 0x4000000, 0x0800000 },
            { "mpr-22924.ic9", 0x4800000, 0x0800000 },
            { "mpr-22925.ic10",0x5000000, 0x0800000 },
            { "mpr-22926.ic11",0x5800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		nullptr,
        &shot12_inputs,
    },
    // Wave Runner GP
    {
        "wrungp",
        NULL,
        "Wave Runner GP",
        0x06800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-24059.ic22", 0x0000000, 0x0400000 },
            { "mpr-23719.ic1",  0x0800000, 0x1000000 },
            { "mpr-23720.ic2",  0x1800000, 0x1000000 },
            { "mpr-23721.ic3",  0x2800000, 0x1000000 },
            { "mpr-23722.ic4",  0x3800000, 0x1000000 },
            { "mpr-23723.ic5",  0x4800000, 0x1000000 },
            { "mpr-23724.ic6",  0x5800000, 0x1000000 },
            { NULL, 0, 0 },
        },
		NULL,
		&wrungp_inputs,
		wrungp_eeprom_dump
    },
    // Wave Runner GP (USA, Rev A)
    {
        "wrungpo",
        "wrungp",
        "Wave Runner GP (USA, Rev A)",
        0x06800000,
        0xffffffff, // not populated
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-23725a.ic22", 0x0000000, 0x400000  },
            { "mpr-23719.ic1",   0x0800000, 0x1000000 },
            { "mpr-23720.ic2",   0x1800000, 0x1000000 },
            { "mpr-23721.ic3",   0x2800000, 0x1000000 },
            { "mpr-23722.ic4",   0x3800000, 0x1000000 },
            { "mpr-23723.ic5",   0x4800000, 0x1000000 },
            { "mpr-23724.ic6",   0x5800000, 0x1000000 },
            // note: origin ROM board have 12x8MB FlashROMs with same contents as above

            // 838-12801 DRIVE BD WAVERUNNER
            //ROM_REGION( 0x10000, "motorio", ROMREGION_ERASEFF)
            //ROM_LOAD( "epr-19250.ic8", 0x000000, 0x010000, CRC(542d3836) SHA1(128cb0bfaf05791d219437653002f6bb948a4ad5) )

            { NULL, 0, 0 },
        },
		NULL,
		&wrungp_inputs,
		wrungp_eeprom_dump
    },
    // World Kicks (WK2 Ver. A)
    {
        "wldkicks",
        NULL,
        "World Kicks (World, WK2 Ver.A)",
        0xb000000,
        0x052e2901,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "wk2vera.2d",  0x0800000, 0x0800000 },
            { "wk2vera.2c",  0x1000000, 0x0800000 },
            { "wk1ma2.4m",   0x2000000, 0x1000000 },
            { "wk1ma3.4l",   0x3000000, 0x1000000 },
            { "wk1ma4.4k",   0x4000000, 0x1000000 },
            { "wk1ma5.4j",   0x5000000, 0x1000000 },
            { "wk1ma6.4h",   0x6000000, 0x1000000 },
            { "wk1ma7.4f",   0x7000000, 0x1000000 },
            { "wk1ma8.4e",   0x8000000, 0x1000000 },
            { "wk1ma9.4d",   0x9000000, 0x1000000 },
            { "wk1ma10.4c",  0xa000000, 0x1000000 },
            { NULL, 0, 0 },
        }
        // BUTTON, (n/a, n/a, ENTER)
    },
    // World Kicks (Japan, WK1 Ver.A)
    {
        "wldkicksj",
        "wldkicks",
        "World Kicks (Japan, WK1 Ver.A)",
        0xb000000,
        0x052e2901,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "wk1vera.2d",  0x0800000, 0x0800000 },
            { "wk2vera.2c",  0x1000000, 0x0800000 },
            { "wk1ma2.4m",   0x2000000, 0x1000000 },
            { "wk1ma3.4l",   0x3000000, 0x1000000 },
            { "wk1ma4.4k",   0x4000000, 0x1000000 },
            { "wk1ma5.4j",   0x5000000, 0x1000000 },
            { "wk1ma6.4h",   0x6000000, 0x1000000 },
            { "wk1ma7.4f",   0x7000000, 0x1000000 },
            { "wk1ma8.4e",   0x8000000, 0x1000000 },
            { "wk1ma9.4d",   0x9000000, 0x1000000 },
            { "wk1ma10.4c",  0xa000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // World Kicks (US, WK3 Ver.A)
    {
        "wldkicksu",
        "wldkicks",
        "World Kicks (US, WK3 Ver.A)",
        0xb000000,
        0x052e2901,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "wk3vera.2d", 0x0800000, 0x0800000 },
            { "wk2vera.2c", 0x1000000, 0x0800000 },
            { "wk1ma2.4m",  0x2000000, 0x1000000 },
            { "wk1ma3.4l",  0x3000000, 0x1000000 },
            { "wk1ma4.4k",  0x4000000, 0x1000000 },
            { "wk1ma5.4j",  0x5000000, 0x1000000 },
            { "wk1ma6.4h",  0x6000000, 0x1000000 },
            { "wk1ma7.4f",  0x7000000, 0x1000000 },
            { "wk1ma8.4e",  0x8000000, 0x1000000 },
            { "wk1ma9.4d",  0x9000000, 0x1000000 },
            { "wk1ma10.4c", 0xa000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // World Kicks PCB (Japan, WKC1 Ver.A)
    {
        "wldkickspj",
        "wldkicks",
        "World Kicks PCB (Japan, WKC1 Ver.A)",
        0xb000000,
        0x052e2901,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "wkc1vera.2d", 0x0800000, 0x0800000 },
            { "wkc1vera.2c", 0x1000000, 0x0800000 },
            { "wk1ma2.4m",   0x2000000, 0x1000000 },
            { "wk1ma3.4l",   0x3000000, 0x1000000 },
            { "wk1ma4.4k",   0x4000000, 0x1000000 },
            { "wk1ma5.4j",   0x5000000, 0x1000000 },
            { "wk1ma6.4h",   0x6000000, 0x1000000 },
            { "wk1ma7.4f",   0x7000000, 0x1000000 },
            { "wk1ma8.4e",   0x8000000, 0x1000000 },
            { "wk1ma9.4d",   0x9000000, 0x1000000 },
            { "wk1ma10.4c",  0xa000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // World Kicks PCB (World, WKC2 Ver.A)
    {
        "wldkickspw",
        "wldkicks",
        "World Kicks PCB (World, WKC2 Ver.A)",
        0xb000000,
        0x052e2901,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "wkc2vera.2d", 0x0800000, 0x0800000 },
            { "wkc1vera.2c", 0x1000000, 0x0800000 },
            { "wk1ma2.4m",   0x2000000, 0x1000000 },
            { "wk1ma3.4l",   0x3000000, 0x1000000 },
            { "wk1ma4.4k",   0x4000000, 0x1000000 },
            { "wk1ma5.4j",   0x5000000, 0x1000000 },
            { "wk1ma6.4h",   0x6000000, 0x1000000 },
            { "wk1ma7.4f",   0x7000000, 0x1000000 },
            { "wk1ma8.4e",   0x8000000, 0x1000000 },
            { "wk1ma9.4d",   0x9000000, 0x1000000 },
            { "wk1ma10.4c",  0xa000000, 0x1000000 },
            { NULL, 0, 0 },
        }
        // C BUTTON
    },
    // WWF Royal Rumble (JPN, USA, EXP, KOR, AUS)
    {
        "wwfroyal",
        NULL,
        "WWF Royal Rumble",
        0x08800000,
        0x281627c3,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-22261.ic22", 0x0000000, 0x0400000 },
            { "mpr-22262.ic1",  0x0800000, 0x1000000 },
            { "mpr-22263.ic2",  0x1800000, 0x1000000 },
            { "mpr-22264.ic3",  0x2800000, 0x1000000 },
            { "mpr-22265.ic4",  0x3800000, 0x1000000 },
            { "mpr-22266.ic5",  0x4800000, 0x1000000 },
            { "mpr-22267.ic6",  0x5800000, 0x1000000 },
            { "mpr-22268.ic7",  0x6800000, 0x1000000 },
            { "mpr-22269.ic8",  0x7800000, 0x1000000 },
            { NULL, 0, 0 },
        }
        // ATTACK, GRAPPLE, SUPPORT
    },
    // Zero Gunner 2
    {
        "zerogu2",
        NULL,
        "Zero Gunner 2",
        0x05800000,
        0x0007c010,
        NULL,
        M2,
        REGION_JAPAN,
        ROT0,
        {
            { "epr-23689.ic22", 0x0000000, 0x0400000 },
            { "mpr-23684.ic1",  0x0800000, 0x1000000 },
            { "mpr-23685.ic2",  0x1800000, 0x1000000 },
            { "mpr-23686.ic3",  0x2800000, 0x1000000 },
            { "mpr-23687.ic4",  0x3800000, 0x1000000 },
            { "mpr-23688.ic5",  0x4800000, 0x1000000 },
            { NULL, 0, 0 },
        },
        nullptr,
		&shot12_inputs,
    },
    // Zombie Revenge
    {
        "zombrvn",
        NULL,
        "Zombie Revenge (Rev A)",
        0xa000000,
        0x28012b41,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21707a.ic22", 0x0000000, 0x0200000 },
            { "epr-21707a.ic22", 0x0200000, 0x0200000 }, // reload
            { "mpr-21708.ic1",   0x0800000, 0x0800000 },
            { "mpr-21709.ic2",   0x1000000, 0x0800000 },
            { "mpr-21710.ic3",   0x1800000, 0x0800000 },
            { "mpr-21711.ic4",   0x2000000, 0x0800000 },
            { "mpr-21712.ic5",   0x2800000, 0x0800000 },
            { "mpr-21713.ic6",   0x3000000, 0x0800000 },
            { "mpr-21714.ic7",   0x3800000, 0x0800000 },
            { "mpr-21715.ic8",   0x4000000, 0x0800000 },
            { "mpr-21716.ic9",   0x4800000, 0x0800000 },
            { "mpr-21717.ic10",  0x5000000, 0x0800000 },
            { "mpr-21718.ic11",  0x5800000, 0x0800000 },
            { "mpr-21719.ic12s", 0x6000000, 0x0800000 },
            { "mpr-21720.ic13s", 0x6800000, 0x0800000 },
            { "mpr-21721.ic14s", 0x7000000, 0x0800000 },
            { "mpr-21722.ic15s", 0x7800000, 0x0800000 },
            { "mpr-21723.ic16s", 0x8000000, 0x0800000 },
            { "mpr-21724.ic17s", 0x8800000, 0x0800000 },
            { "mpr-21725.ic18s", 0x9000000, 0x0800000 },
            { "mpr-21726.ic19s", 0x9800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		NULL,
		&zombie_inputs
    },
    // Zombie Revenge
    {
        "zombrvno",
        "zombrvn",
        "Zombie Revenge",
        0x0a000000,
        0x28012b41,
        NULL,
        M2,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "epr-21707.ic22",0x0000000, 0x0200000 },
            { "epr-21707.ic22",0x0200000, 0x0200000 },    // Reload
            { "mpr-21708.ic1",  0x0800000, 0x0800000 },
            { "mpr-21709.ic2",  0x1000000, 0x0800000 },
            { "mpr-21710.ic3",  0x1800000, 0x0800000 },
            { "mpr-21711.ic4",  0x2000000, 0x0800000 },
            { "mpr-21712.ic5",  0x2800000, 0x0800000 },
            { "mpr-21713.ic6",  0x3000000, 0x0800000 },
            { "mpr-21714.ic7",  0x3800000, 0x0800000 },
            { "mpr-21715.ic8",  0x4000000, 0x0800000 },
            { "mpr-21716.ic9",  0x4800000, 0x0800000 },
            { "mpr-21717.ic10", 0x5000000, 0x0800000 },
            { "mpr-21718.ic11", 0x5800000, 0x0800000 },
            { "mpr-21719.ic12s",0x6000000, 0x0800000 },
            { "mpr-21720.ic13s",0x6800000, 0x0800000 },
            { "mpr-21721.ic14s",0x7000000, 0x0800000 },
            { "mpr-21722.ic15s",0x7800000, 0x0800000 },
            { "mpr-21723.ic16s",0x8000000, 0x0800000 },
            { "mpr-21724.ic17s",0x8800000, 0x0800000 },
            { "mpr-21725.ic18s",0x9000000, 0x0800000 },
            { "mpr-21726.ic19s",0x9800000, 0x0800000 },
            { NULL, 0, 0 },
        },
		NULL,
		&zombie_inputs
    },
    // Naomi M4 Roms
    // Akatsuki Blitzkampf Ausf. Achse (Japan)
    {
        "ausfache",
        NULL,
        "Akatsuki Blitzkampf Ausf. Achse (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "ic8.bin", 0x0000000, 0x4000000 },
            { "ic9.bin", 0x4000000, 0x4000000 },
            // IC10 and IC11 Populated, Empty
            { "317-05130-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
        // ATTACK1/2/3
    },
    // Asian Dynamite
    {
        "asndynmt",
        NULL,
        "Asian Dynamite / Dynamite Deka EX",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24382.ic8",  0x0000000, 0x4000000 },
            { "fpr-24383.ic9",  0x4000000, 0x4000000 },
            { "fpr-24384.ic10", 0x8000000, 0x4000000 },
            { "fpr-24385.ic11", 0xc000000, 0x4000000 },
            { "317-0495-com.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
        // PUNCH, KICK, JUMP
    },
    // Asian Dynamite / Dynamite Deka EX (older)
    {
        "asndynmto",
        "asndynmt",
        "Asian Dynamite / Dynamite Deka EX (older)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24382.ic8",  0x0000000, 0x4000000 },
            { "fpr-24383.ic9",  0x4000000, 0x4000000 },
            { "fpr-24384.ic10", 0x8000000, 0x4000000 },
            { "fpr-24385.ic11", 0xc000000, 0x4000000 },
            { "317-0495-com.ic3", 0, 0x800,  0x0000000, Key },

            { NULL, 0, 0 },
        }
        // PUNCH, KICK, JUMP
    },
    // Illvelo (Illmatic Envelope) (Japan)
    {
        "illvelo",
        NULL,
        "Illvelo (Illmatic Envelope) (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT270,
        {
            { "fpr-24437.ic8",  0x0000000, 0x4000000 },
            { "fpr-24438.ic9",  0x4000000, 0x4000000 },
            { "fpr-24439.ic10", 0x8000000, 0x4000000 },
            { "317-5131-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        },
        NULL,
        NULL, // SHOT/DOLL/SPECIAL
        illvelo_eeprom_dump
    },
    // Manic Panic Ghosts! *** BAD DUMP ***
    {
        "manicpnc",
        NULL,
        "Manic Panic Ghosts! (USA, Export)",
        0x14000000,
        0x5505,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24408.ic8",  0x00000000, 0x4000000 },
            { "fpr-24372.ic9",  0x04000000, 0x4000000 },
            { "fpr-24373.ic10", 0x08000000, 0x4000000 },
            { "fpr-24374.ic11", 0x0c000000, 0x4000000 },
            { "fpr-24375.ic12", 0x10000000, 0x4000000 },

            //ROM_REGION( 0x200000, "ioboard", 0) // touch screen I/O board, program disassembles as little-endian SH-4
            //ROM_LOAD( "fpr24351.ic14", 0x000000, 0x200000, CRC(4d1b7b89) SHA1(965b8c6b5a2e7b3f1b1e2eac19c86000c3b66754) )

            //ROM_REGION( 0x800, "pic_readout", 0 )
            //ROM_LOAD( "317-0461-com.ic3", 0, 0x800, BAD_DUMP CRC(c9282cdd) SHA1(23933e489d763515428e2714cc6e7676df1d5323) )
            { "317-0461-com.ic3", 0, 0x800,  0x0000000, Key },

            { NULL, 0, 0 },
        }
    },
    // Mamoru-kun wa Norowarete Shimatta! (Japan)
    {
        "mamonoro",
        NULL,
        "Mamoru-kun wa Norowarete Shimatta! (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT270,
        {
            { "ic8.bin",  0x0000000, 0x4000000 },
            { "ic9.bin",  0x4000000, 0x4000000 },
            { "ic10.bin", 0x8000000, 0x4000000 },
            { "317-5132-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        },
        NULL,
        NULL, // SHOT(A)/(B)
        mamonoro_eeprom_dump
    },
    // Melty Blood Actress Again Version A (Japan, Rev A)
    {
        "mbaa",
        NULL,
        "Melty Blood Actress Again Version A (Japan, Rev A)",
        0x18000000,
        0x5586,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "ic8.bin",       0x00000000, 0x4000000 },
            { "epr-24455.ic7", 0x00000000, 0x0400000 }, // EPR mode, overwrite FPR data
            { "ic9.bin",       0x04000000, 0x4000000 },
            { "ic10.bin",      0x08000000, 0x4000000 },
            { "ic11.bin",      0x0c000000, 0x4000000 },
            { "ic12.bin",      0x10000000, 0x4000000 },
            { "ic13.bin",      0x14000000, 0x4000000 },
            { "317-5133-jpn.ic3", 0, 0x800,  0x0000000, Key }, // pic_readout
            { NULL, 0, 0 },
        }
        // BUTTON A/B/C/D/E
    },
    // Melty Blood Actress Again (Japan) (Clone)
    {
        "mbaao",
        "mbaa",
        "Melty Blood Actress Again (Japan)",
        0x18000000,
        0x5506,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "ic8.bin",       0x00000000, 0x4000000 },
            { "ic9.bin",       0x04000000, 0x4000000 },
            { "ic10.bin",      0x08000000, 0x4000000 },
            { "ic11.bin",      0x0c000000, 0x4000000 },
            { "ic12.bin",      0x10000000, 0x4000000 },
            { "ic13.bin",      0x14000000, 0x4000000 },
            { "317-5133-jpn.ic3", 0, 0x800,  0x0000000, Key }, // pic_readout
            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetles - Mushiking II / III / III+ (Ver. 1.001) (World)
    {
        "mushi2eo",
        "mushik2e",
        "Mushiking The King Of Beetles - Mushiking II / III / III+ (Ver. 1.001) (World)",
        0x8000000,
        0x5502,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24333.ic8", 0x0000000, 0x4000000 },
            { "fpr-24334.ic9", 0x4000000, 0x4000000 },
            { "317-0437-com.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
    },
    // MushiKing II - The King Of Beetle II ENG (Ver. 1.001)
    {
        "mushik2e",
        NULL,
        "Mushiking The King Of Beetles - Mushiking II / III / III+ (Ver. 2.001) (World)",
        0x8000000,
        0x5582,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24333.ic8", 0x0000000, 0x4000000 },
            { "epr-24357.ic7", 0x0000000, 0x0400000 },
            { "fpr-24334.ic9", 0x4000000, 0x4000000 },

            //ROM_REGION( 0x800, "pic_readout", 0 )
            //ROM_LOAD( "317-0437-com.ic3", 0, 0x800, CRC(3b6fcee8) SHA1(65fbdd3b8c61a4b5ccb6389b25483a7ecdc0794d) )
            { "317-0437-com.ic3", 0, 0x800,  0x0000000, Key },

            { NULL, 0, 0 },
        }
    },
    // Mushiking The King Of Beetles - Mushiking IV / V / VI (World)
    // change game version (4/5/6): in BACKUP DATA CLEAR menu hold P1 and P2 buttons 1 for 3 seconds, then change version number in appeared menu and select YES(CLEAR)
    {
        "mushik4e",
        NULL,
        "Mushiking The King Of Beetles - Mushiking IV / V / VI (World)",
        0x8000000,
        0x5502,
        "naomi",
        M4,
        REGION_EXPORT,
        ROT0,
        {
            { "fpr-24417.ic8", 0x0000000, 0x4000000 },
            { "fpr-24418.ic9", 0x4000000, 0x4000000 },

            //ROM_REGION( 0x800, "pic_readout", 0 )
            //ROM_LOAD( "317-0437-com.ic3", 0, 0x800, CRC(3b6fcee8) SHA1(65fbdd3b8c61a4b5ccb6389b25483a7ecdc0794d) )
            { "317-0437-com.ic3", 0, 0x800,  0x0000000, Key },

            { NULL, 0, 0 },
        }
    },
    // Pokasuka Ghost *** BAD DUMP ***
    {
        "pokasuka",
		"manicpnc",
        "Pokasuka Ghost! (Japan)",
        0x14000000,
        0x5505,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "fpr-24365.ic8",  0x00000000, 0x4000000, 0x11489cda },
            { "fpr-24366.ic9",  0x04000000, 0x4000000, 0x7429714a },
            { "fpr-24367.ic10", 0x08000000, 0x4000000, 0xdee87bab },
            { "fpr-24368.ic11", 0x0c000000, 0x4000000, 0x124f55e2 },
            { "fpr-24369.ic12", 0x10000000, 0x4000000, 0x35b544ab },

            //ROM_REGION( 0x200000, "ioboard", 0) // touch screen I/O board, program disassembles as little-endian SH-4
            //ROM_LOAD( "fpr24351.ic14", 0x000000, 0x200000, CRC(4d1b7b89) SHA1(965b8c6b5a2e7b3f1b1e2eac19c86000c3b66754) )

            //ROM_REGION( 0x800, "pic_readout", 0 )
            //ROM_LOAD( "317-0461-com.ic3", 0, 0x800, BAD_DUMP CRC(c9282cdd) SHA1(23933e489d763515428e2714cc6e7676df1d5323) )
            { "317-0461-com.ic3", 0, 0x800,  0xc9282cdd, Key },

            { NULL, 0, 0 },
        }
    },
    // Radirgy Noa
    {
        "radirgyn",
        NULL,
        "Radirgy Noa (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "ic8.bin", 0x0000000, 0x4000000 },
            { "ic9.bin", 0x4000000, 0x4000000 },
            { "317-5138-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
        // SHOT (A)/(B)/(C)
    },
    // Rhythm Tengoku
    {
        "rhytngk",
        NULL,
        "Rhythm Tengoku (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "fpr-24423.ic8",  0x00000000, 0x4000000 },
            { "fpr-24424.ic9",  0x04000000, 0x4000000 },
            { "fpr-24425.ic10", 0x08000000, 0x4000000 },
            { "fpr-24426.ic11", 0x0c000000, 0x4000000 },
            { "317-0503-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
        // SHOT A/B
    },
    // Shooting Love 2007 (Japan)
    {
        "sl2007",
        NULL,
        "Shooting Love 2007 (Japan)",
        0x10000000,
        0x5504,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT270,
        {
            { "fpr-24413.ic8",  0x0000000, 0x4000000 },
            { "fpr-24414.ic9",  0x4000000, 0x4000000 },
            { "fpr-24415.ic10", 0x8000000, 0x4000000 },
            { "fpr-24416.ic11", 0xc000000, 0x4000000 },
            { "317-5129-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        },
        NULL,
        NULL, // PUSH1/2/3
        sl2007_eeprom_dump
    },
    // Touch De Zunou (Rev A) *** BAD DUMP ***
    {
        "zunou",
        NULL,
        "Touch De Zunou (Japan, Rev A)",
        0x8000000,
        0x5502,
        "naomi",
        M4,
        REGION_JAPAN,
        ROT0,
        {
            { "fpr-24338.ic8", 0x0000000, 0x4000000 },
            { "fpr-24339.ic9", 0x4000000, 0x4000000 },

            //ROM_REGION( 0x800, "pic_readout", 0 )
            //ROM_LOAD( "317-0435-jpn.ic3", 0, 0x800, BAD_DUMP CRC(b553d900) SHA1(ed1c3c2053f2c0e98cb5c4d99f93143a66c29e5c) )
            { "317-0435-jpn.ic3", 0, 0x800,  0x0000000, Key },
            { NULL, 0, 0 },
        }
    },
    // Star Horse Progress Returns (satellite)
    {
        "shorsepr",
        NULL,
        "Star Horse Progress Returns (satellite)",
        0x8000000,
        0x5502,
        "naomi",
        M4,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "fpr-24489.ic8",  0x00000000, 0x4000000 },
            { "fpr-24490.ic9",  0x04000000, 0x4000000 },
            { NULL, 0, 0 },
        }
    },
    // Naomi GD Roms

    // Azumanga Daioh Puzzle Bobble (GDL-0018)
    {
        "azumanga",
        NULL,
        "Azumanga Daioh Puzzle Bobble (GDL-0018)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5091-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0018",
    },
    // Border Down (Rev A) (GDL-0023A)
    {
        "bdrdown",
        NULL,
        "Border Down (Rev A) (GDL-0023A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5097-jpn.pic", 0, 0x4000 },
            { "bdrdown-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0023a",
		// SHOT, LASER, SPEED
    },
    // Chaos Field (Japan) (GDL-0025)
    {
        "cfield",
        NULL,
        "Chaos Field (Japan) (GDL-0025)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5102-com.pic", 0, 0x4000 },
            { "cfield-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0025",
		// TRG1/2/3
    },
    // Musapey's Choco Marker (Rev A) (GDL-0014A)
    {
        "chocomk",
        NULL,
        "Musapey's Choco Marker (Rev A) (GDL-0014A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5085-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0014a",
		// BUTTON A/B
    },
    // Cleopatra Fortune Plus (GDL-0012)
    {
        "cleoftp",
        NULL,
        "Cleopatra Fortune Plus (GDL-0012)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5083-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0012",
		// BUTTON 1/2
    },
    // Confidential Mission (GDS-0001)
    {
        "confmiss",
        NULL,
        "Confidential Mission (GDS-0001)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0298-com.pic",  0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0001",
    },
    // Capcom Vs. SNK Millennium Fight 2000 Pro (Japan) (GDL-0004)
    {
        "cvsgd",
        NULL,
        "Capcom Vs. SNK Millennium Fight 2000 Pro (Japan) (GDL-0004)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5076-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0004",
		// SHOT1/2/na/4/5
    },
    // Capcom Vs. SNK 2 Mark Of The Millennium 2001 (GDL-0008)
    // ver 010804
    // with Japan BIOS will be shown 010705, likely forgot / was not cared to update it
    {
        "cvs2",
        NULL,
        "Capcom Vs. SNK 2 Mark Of The Millennium 2001 (USA) (GDL-0008)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5078-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0008",
        &cvs2_inputs,
    },
    // Capcom Vs. SNK 2 Millionaire Fighting 2001 (Rev A) (GDL-0007A)
    // ver 010705
    {
        "cvs2mf",
        "cvs2",
        "Capcom Vs. SNK 2 Millionaire Fighting 2001 (Japan, Rev A) (GDL-0007A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5078-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0007a",
        &cvs2_inputs,
    },
    // Dragon Treasure (Rev B) (GDS-0030B)
    {
        "dragntr",
        NULL,
        "Dragon Treasure (Rev B) (GDS-0030B)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0363-com.pic", 0, 0x4000 },
            //{ "317-0364-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0030b",
    },
    // Dragon Treasure (Rev A) (GDS-0030A)
    {
        "dragntra",
        "dragntr",
        "Dragon Treasure (Rev A) (GDS-0030A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0363-com.pic", 0, 0x4000 },
            //{ "317-0364-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0030a",
    },
    // Dragon Treasure 2 (Rev A) (GDS-0037A)
    {
        "dragntr2",
        NULL,
        "Dragon Treasure 2 (Rev A) (GDS-0037A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0389-com.pic", 0, 0x4000 },
            //{ "317-0390-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0037a",
    },
    // Dragon Treasure 3 (Rev A) (GDS-0041A)
    {
        "dragntr3",
        NULL,
        "Dragon Treasure 3 (Rev A) (GDS-0041A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0426-jpn.pic", 0, 0x4000 },
            //{ "317-0390-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0041a",
    },
    // Virtua Golf / Dynamic Golf (Rev A) (GDS-0009A)
    {
        "dygolf",
        NULL,
        "Virtua Golf / Dynamic Golf (Rev A) (GDS-0009A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0308-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0009a",
    },
    // Guilty Gear XX (GDL-0011)
    {
        "ggxx",
        NULL,
        "Guilty Gear XX (GDL-0011)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5082-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0011",
		// KICK, SLASH, HIGH SLASH, PUNCH, DUST ATTACK
    },
    // Guilty Gear XX Accent Core (Japan) (GDL-0041)
    {
        "ggxxac",
        NULL,
        "Guilty Gear XX Accent Core (Japan) (GDL-0041)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5126-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0041",
		// same KICK, SLASH, HIGH SLASH, PUNCH, DUST ATTACK
    },
    // Guilty Gear XX #Reload (Japan, Rev A) (GDL-0019A)
    {
        "ggxxrl",
        NULL,
        "Guilty Gear XX #Reload (Japan, Rev A) (GDL-0019A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5092-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0019a",
		// same KICK, SLASH, HIGH SLASH, PUNCH, DUST ATTACK
    },
    // Guilty Gear XX #Reload (Japan) (GDL-0019)
    {
        "ggxxrlo",
        "ggxxrl",
        "Guilty Gear XX #Reload (Japan) (GDL-0019)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5092-jpn.pic" , 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0019",
    },
    // Guilty Gear XX Slash (Japan, Rev A) (GDL-0033A)
    {
        "ggxxsla",
        NULL,
        "Guilty Gear XX Slash (Japan, Rev A) (GDL-0033A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5111-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0033a",
		// same KICK, SLASH, HIGH SLASH, PUNCH, DUST ATTACK
    },
    // Mobile Suit Gundam: Federation Vs. Zeon (GDL-0001)
    {
        "gundmgd",
        NULL,
        "Mobile Suit Gundam: Federation Vs. Zeon (GDL-0001)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5069-com.pic", 0, 0x4000 },
            //{ "gundmgd-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0001",
		&shot1234_inputs,
		gundmct_eeprom_dump
    },
    // Mobile Suit Gundam: Federation Vs. Zeon DX (USA, Japan) (GDL-0006)
    {
        "gundmxgd",
        NULL,
        "Mobile Suit Gundam: Federation Vs. Zeon DX (USA, Japan) (GDL-0006)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_USA,
        ROT0,
        {
            { "317-5079-com.pic", 0, 0x4000 },
            //{ "gundmxgd-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0006",
		&shot1234_inputs,
		gundmxgd_eeprom_dump
    },
    // Ikaruga (GDL-0010)
    {
        "ikaruga",
        NULL,
        "Ikaruga (GDL-0010)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "317-5081-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0010",
		// SHOT, CHANGE
    },
    // Jingi Storm - The Arcade (Japan) (GDL-0037)
    {
        "jingystm",
        NULL,
        "Jingi Storm - The Arcade (Japan) (GDL-0037)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5122-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0037",
		// GUARD, PUNCH, KICK
    },
    // Karous (Japan) (GDL-0040)
    {
        "karous",
        NULL,
        "Karous (Japan) (GDL-0040)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5125-com.pic", 0, 0x4000 },
            { "karous-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0040",
		// SHOT, SWORD, SPECIAL same as radirgy
    },
    // La Keyboard (GDS-0017)
    {
        "keyboard",
        NULL,
        "La Keyboard (GDS-0017)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0323-com.pic", 0, 0x4000 },
            { "keyboard-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gds-0017",
    },
    // Kurukuru Chameleon (Japan) (GDL-0034)
    {
        "kurucham",
        NULL,
        "Kurukuru Chameleon (Japan) (GDL-0034)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5115-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0034",
    },
    // Lupin The Third - The Shooting (Rev A) (GDS-0018A)
    {
        "lupinsho",
        NULL,
        "Lupin The Third - The Shooting (Rev A) (GDS-0018A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0325-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0018a",
    },
    // Lupin The Third - The Shooting (GDS-0018)
    {
        "lupinshoo",
        "lupinsho",
        "Lupin The Third - The Shooting (GDS-0018)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0325-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0018",
    },
    // Lupin The Third - The Typing (Rev A) (GDS-0021A)
    {
        "luptype",
        NULL,
        "Lupin The Third - The Typing (Rev A) (GDS-0021A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0332-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0021a",
    },
    // Melty Blood Act Cadenza Version B2 (Japan) (GDL-0039A)
    {
        "meltyb",
        NULL,
        "Melty Blood Act Cadenza Version B2 (Japan) (GDL-0039A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5124-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0039a",
		// BUTTON A/B/C/D/E
    },
    // Melty Blood Act Cadenza Ver. A (Japan) (GDL-0028C)
    {
        "meltybld",
        NULL,
        "Melty Blood Act Cadenza Ver. A (Japan) (GDL-0028C)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5104-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0028c",
    },
    // Melty Blood Act Cadenza (Japan) (GDL-0028)
    {
        "meltyblo",
        "meltybld",
        "Melty Blood Act Cadenza (Japan) (GDL-0028)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5104-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0028",
    },
    // Melty Blood Act Cadenza Version B (Japan) (GDL-0039)
    {
        "meltybo",
        "meltyb",
        "Melty Blood Act Cadenza Version B (Japan) (GDL-0039)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5124-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0039",
    },
    // Moeru Casinyo (Japan) (GDL-0013)
    {
        "moeru",
        NULL,
        "Moeru Casinyo (Japan) (GDL-0013)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5084-jpn.pic", 0, 0x4000 },
            { "moeru-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0013",
    },
    // The Maze of the Kings (GDS-0022)
    {
        "mok",
        NULL,
        "The Maze of the Kings (GDS-0022)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0333-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0022",
    },
    // Monkey Ball (GDS-0008)
    {
        "monkeyba",
        NULL,
        "Monkey Ball (GDS-0008)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0307-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0008",
        &monkeyba_inputs,
    },
    // Psyvariar 2 - The Will To Fabricate (Japan) (GDL-0024)
    {
        "psyvar2",
        NULL,
        "Psyvariar 2 - The Will To Fabricate (Japan) (GDL-0024)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5100-jpn.pic", 0, 0x4000 },
            { "psyvar2-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0024",
		// SHOT, BOMB
    },
    // Puyo Pop Fever (World) (GDS-0034)
    {
        "puyofev",
        NULL,
        "Puyo Pop Fever (World) (GDS-0034)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0375-com.pic", 0, 0x4000 },
            { "puyofev-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gds-0034",
    },
    // Puyo Puyo Fever (Japan) (GDS-0031)
    {
        "puyofevj",
        "puyofev",
        "Puyo Puyo Fever (Japan) (GDS-0031)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-0375-com.pic", 0, 0x4000 },
            { "puyofev-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gds-0031",
    },
	// Puyo Puyo Fever (Prototype)
	{
		"puyofevp",
		"puyofev",
		"Puyo Puyo Fever (Prototype)",
		0x0c000000,
		0xff9d4d3c,
		"naomi",
		M1,
		REGION_JAPAN,
		ROT0,
		{
				{ "ic17s.bin", 0x01000000, 0x800000, 0xf51ce63b, InterleavedWord },
				{ "ic18s.bin", 0x01000002, 0x800000, 0x7109decc, InterleavedWord },
				{ "ic19s.bin", 0x02000000, 0x800000, 0xa58efa9c, InterleavedWord },
				{ "ic20s.bin", 0x02000002, 0x800000, 0x6dee24b2, InterleavedWord },
				{ "ic21s.bin", 0x03000000, 0x800000, 0x9a0564c2, InterleavedWord },
				{ "ic22s.bin", 0x03000002, 0x800000, 0xdf692133, InterleavedWord },
				{ "ic23s.bin", 0x04000000, 0x800000, 0x61c98256, InterleavedWord },
				{ "ic24s.bin", 0x04000002, 0x800000, 0xc7e8ec24, InterleavedWord },
				{ "ic25s.bin", 0x05000000, 0x800000, 0x2cb47ef5, InterleavedWord },
				{ "ic26s.bin", 0x05000002, 0x800000, 0xf5b477d5, InterleavedWord },
				{ "ic27s.bin", 0x06000000, 0x800000, 0x22c07470, InterleavedWord },
				{ "ic28s.bin", 0x06000002, 0x800000, 0x018233e0, InterleavedWord },
				{ "ic29s.bin", 0x07000000, 0x800000, 0x96101b95, InterleavedWord },
				{ "ic30s.bin", 0x07000002, 0x800000, 0x16dff39b, InterleavedWord },
				{ "ic31s.bin", 0x08000000, 0x800000, 0x510c03dd, InterleavedWord },
				{ "ic32s.bin", 0x08000002, 0x800000, 0xb184e263, InterleavedWord },
				{ "ic33s.bin", 0x09000000, 0x800000, 0xbe2a164b, InterleavedWord },
				{ "ic34s.bin", 0x09000002, 0x800000, 0x01e0a163, InterleavedWord },
				{ "ic35s.bin", 0x0a000000, 0x800000, 0xae0c1caa, InterleavedWord },
				{ "ic36s.bin", 0x0a000002, 0x800000, 0x6de8d5c7, InterleavedWord },
				{ "ic37s.bin", 0x0b000000, 0x800000, 0xfc89454c, InterleavedWord },
				{ "ic38s.bin", 0x0b000002, 0x800000, 0x86954476, InterleavedWord },
	            { "copy",      0x00400000, 0xc00000, 0x0000000, Copy, 0x1000000 },

				{ NULL, 0, 0, 0x00000000 },
		},
	},
    // Quiz Keitai Q mode (GDL-0017)
    {
        "quizqgd",
        NULL,
        "Quiz Keitai Q mode (GDL-0017)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "317-5090-jpn.pic", 0, 0x4000 },
            { "quizqgd-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0017",
    },
    // Radirgy (Japan, Rev A) (GDL-0032A)
    {
        "radirgy",
        NULL,
        "Radirgy (Japan, Rev A) (GDL-0032A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5110-jpn.pic", 0, 0x4000 },
            { "radirgy-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0032a",
		// SHOT, SWORD, SPECIAL same as karous
    },
    // Radirgy (Japan) (GDL-0032)
    {
        "radirgyo",
        "radirgy",
        "Radirgy (Japan) (GDL-0032)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5110-jpn.pic", 0, 0x4000 },
            { "radirgy-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0032",
    },
    // Senko No Ronde (Japan, Rev A) (GDL-0030A)
    {
        "senko",
        NULL,
        "Senko no Ronde (Japan, Rev A) (GDL-0030A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5107-jpn.pic", 0, 0x4000 },
            { "senko-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0030a",
    },
    // Senko No Ronde (Japan) (GDL-0030)
    {
        "senkoo",
        "senko",
        "Senko no Ronde (Japan) (GDL-0030)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5107-jpn.pic", 0, 0x4000 },
            { "senkoo-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0030",
    },
    // Senko No Ronde Special (Export, Japan) (GDL-0038)
    {
        "senkosp",
        NULL,
        "Senko no Ronde Special (Export, Japan) (GDL-0038)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN, // one of the few exceptions that doesn't work with USA bios while they work with Export bios, so it's safer to restrict it to Japan bios
        ROT0,
        {
            { "317-5123-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0038",
    },
    // Street Fighter Zero 3 Upper (Japan) (GDL-0002)
    {
        "sfz3ugd",
        NULL,
        "Street Fighter Zero 3 Upper (Japan) (GDL-0002)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5072-com.pic", 0, 0x4000 },
            { "sfz3ugd-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0002",
        &sfz3ugd_inputs
    },
    // Shakatto Tambourine (Rev B) (GDS-0002B)
    {
        "shaktam",
        NULL,
        "Shakatto Tambourine (Rev B) (GDS-0002B)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0299-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0002b",
    },
    // Shakatto Tambourine Cho Powerup Chu (2K1 AUT) (GDS-0016)
    {
        "shaktamb",
        NULL,
        "Shakatto Tambourine Cho Powerup Chu (2K1 AUT) (GDS-0016)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0321-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0016",
    },
    // Shakatto Tambourine Motto Norinori Shinkyoku Tsuika (2K1 SPR) (GDS-0013)
    {
        "shaktmsp",
        NULL,
        "Shakatto Tambourine Motto Norinori Shinkyoku Tsuika (2K1 SPR) (GDS-0013)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0315-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0013",
    },
    // Shikigami No Shiro II / The Castle of Shikigami II (GDL-0021)
    {
        "shikgam2",
        NULL,
        "Shikigami no Shiro II / The Castle of Shikigami II (GDL-0021)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "317-5095-jpn.pic", 0, 0x4000 },
            { "shikgam2-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0021",
    },
    // Slashout (GDS-0004)
    {
        "slashout",
        NULL,
        "Slashout (GDS-0004)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0302-com.pic",  0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0004",
		&slashout_inputs,
		slashout_eeprom_dump
    },
    // Spikers Battle (GDS-0005)
    {
        "spkrbtl",
        NULL,
        "Spikers Battle (GDS-0005)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0303-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0005",
		NULL, // BEAT, CHARGE ,JUMP, SHIFT
		spkrbtl_eeprom_dump
    },
    // Sports Jam (GDS-0003)
    {
        "sprtjam",
        NULL,
        "Sports Jam (GDS-0003)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0300-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0003",
		&shot12_inputs,
    },
    // Super Shanghai 2005 (Japan, Rev A) (GDL-0031A)
    {
        "ss2005",
        NULL,
        "Super Shanghai 2005 (Japan, Rev A) (GDL-0031A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5108-jpn.pic", 0, 0x4000 },
            { "ss2005-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0031a",
    },
    // Super Shanghai 2005 (Japan) (GDL-0031)
    {
        "ss2005o",
        "ss2005",
        "Super Shanghai 2005 (Japan) (GDL-0031)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5108-jpn.pic", 0, 0x4000 },
            { "ss2005-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0031",
    },
    // Doki Doki Idol Star Seeker (GDL-0005)
    {
        "starseek",
        NULL,
        "Doki Doki Idol Star Seeker (GDL-0005)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-5077-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0005",
    },
    // Noukone Puzzle Takoron (Japan) (GDL-0042)
    {
        "takoron",
        NULL,
        "Noukone Puzzle Takoron (Japan) (GDL-0042)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5127-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gdl-0042",
    },
    // Tetris Kiwamemichi (Japan) (GDL-0020)
    {
        "tetkiwam",
        NULL,
        "Tetris Kiwamemichi (Japan) (GDL-0020)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5093-jpn.pic", 0, 0x4000 },
            { "tetkiwam-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0020",
    },
    // Trigger Heart Exelica Ver.A (Japan) (GDL-0036A)
    {
        "trgheart",
        NULL,
        "Trigger Heart Exelica Ver.A (Japan) (GDL-0036A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5121-jpn.pic", 0, 0x4000 },
            { "trgheart-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0036a",
		// SHOT, ANCHOR, BOMB
    },
    // Trigger Heart Exelica (Japan) (GDL-0036)
    {
        "trghearto",
        "trgheart",
        "Trigger Heart Exelica (Japan) (GDL-0036)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5121-jpn.pic", 0, 0x4000 },
            { "trgheart-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0036",
    },
    // Trizeal (Japan) (GDL-0026)
    {
        "trizeal",
        NULL,
        "Trizeal (Japan) (GDL-0026)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5103-jpn.pic", 0, 0x4000 },
            { "trizeal-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0026",
		// PUSH1/2/3
    },
    // Under Defeat (Japan) (GDL-0035)
    {
        "undefeat",
        NULL,
        "Under Defeat (Japan) (GDL-0035)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT270,
        {
            { "317-5117-jpn.pic", 0, 0x4000 },
            { "undefeat-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0035",
		// SHOT, BOMB
    },
    // Usagi - Yamashiro Mahjong Hen (Japan) (GDL-0022)
    {
        "usagiym",
        NULL,
        "Usagi - Yamashiro Mahjong Hen (Japan) (GDL-0022)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_JAPAN,
        ROT0,
        {
            { "317-5096-jpn.pic", 0, 0x4000 },
            { "usagiym-default-eeprom.bin", 0, 0x80,  0x0000000, Eeprom },
            { NULL, 0, 0 },
        },
        "gdl-0022",
    },
    // Virtua Athletics / Virtua Athlete (GDS-0019)
    {
        "vathlete",
        NULL,
        "Virtua Athletics / Virtua Athlete (GDS-0019)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0330-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0019",
		// RUN1, ACTION, RUN2
    },
    // Virtua Tennis 2 / Power Smash 2 (Rev A) (GDS-0015A)
    {
        "vtennis2",
        NULL,
        "Virtua Tennis 2 / Power Smash 2 (Rev A) (GDS-0015A)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0318-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0015a",
    },
    // Virtua Tennis / Power Smash (GDS-0011)
    {
        "vtennisg",
        NULL,
        "Virtua Tennis / Power Smash (GDS-0011)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0312-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0011",
    },
    // World Series Baseball / Super Major League (GDS-0010)
    {
        "wsbbgd",
        NULL,
        "World Series Baseball / Super Major League (GDS-0010)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0309-com.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "gds-0010",
		&wsbb_inputs,
    },
    // Sega Yonin Uchi Mahjong MJ (セガ四人打ち麻雀MJ), "Sega The 4Players Mah-Jong"
    // uses CRP-1231 card RW connected via 838-13661 RS422/RS232C converter BD, and 2x JVS I/O boards (or one special I/O ?).
    {
        "mj1",
        NULL,
        "Sega Yonin Uchi Mahjong MJ (Update Disc Ver.1.008, Japan) (CDP-10002B)",
        0x4000,
        0,
        "naomi",
        GD,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "317-0352-jpn.pic", 0, 0x4000 },
            { NULL, 0, 0 },
        },
        "cdp-10002b",
    },

    // AtomisWave Roms

    // Animal Basket (24 Jan 2005)
    {
        "anmlbskt",
        NULL,
        "Animal Basket (24 Jan 2005)",
        0x4000000,
        0x45,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "vm2001f01.u3",  0x0000000, 0x800000 },
            { "vm2001f01.u4",  0x1000000, 0x800000 },
            { "vm2001f01.u2",  0x1800000, 0x800000 },
            { "vm2001f01.u15", 0x2000000, 0x800000 },
            { NULL, 0, 0 },
        }
    },
    // Animal Basket (19 Jan 2005)
    {
        "anmlbskta",
        "anmlbskt",
        "Animal Basket (19 Jan 2005)",
        0x4000000,
        0x45,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "u3",  0x0000000, 0x1000000 },
            { "u1",  0x1000000, 0x1000000 },
            { "u4",  0x2000000, 0x1000000 },
            { "u2",  0x3000000, 0x1000000 },
            // U14-U17 not populated
            { NULL, 0, 0 },
        }
    },
    // Sega Bass Fishing Challenge Version A
    {
        "basschal",
        NULL,
        "Sega Bass Fishing Challenge Version A",
        0x8000000,
        0x2a,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "vera.u3",      0x00000000, 0x01000000 },
            { "vera.u1",      0x01000000, 0x01000000 },
            { "vera.u4",      0x02000000, 0x01000000 },
            { "vera.u2",      0x03000000, 0x01000000 },
            { "vera.u15",     0x04000000, 0x01000000 },
            { "vera.u17",     0x05000000, 0x01000000 },
            { "vera.u14",     0x06000000, 0x01000000 },
            { "vera.u16",     0x07000000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Sega Bass Fishing Challenge
    {
        "basschalo",
        "basschal",
        "Sega Bass Fishing Challenge",
        0x8000000,
        0x2a,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "610-0811.u3",  0x00000000, 0x01000000 },
            { "610-0811.u1",  0x01000000, 0x01000000 },
            { "vera.u4",      0x02000000, 0x01000000 },
            { "610-0811.u2",  0x03000000, 0x01000000 },
            { "610-0811.u15", 0x04000000, 0x01000000 },
            { "610-0811.u17", 0x05000000, 0x01000000 },
            { "610-0811.u14", 0x06000000, 0x01000000 },
            { "vera.u16",     0x07000000, 0x01000000 },
            { NULL, 0, 0 },
        }
    },
    // Block Pong-Pong
    {
        "blokpong",
        NULL,
        "Block Pong-Pong",
        0x4000000,
        0x45,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "u3", 0x0000000, 0x1000000 },
            { "u1", 0x1000000, 0x1000000 },
            { "u4", 0x2000000, 0x1000000 },
            //ROM_LOAD( "u2",  0x3000000, 0x1000000, CRC(b9162d97) SHA1(7f561617fa0538da554ad6f6c4d6a20e739491dc) ) // garbage data not used by this game, match anmlbskta U2
            // U14-U17 not populated

            { NULL, 0, 0 },
        },
        NULL,
        &blockpong_inputs,
    },
    // Sega Clay Challenge
    {
        "claychal",
        NULL,
        "Sega Clay Challenge",
        0x8000100,
        0x2a,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "608-2161.u3",  0x0000000, 0x1000100 },
            { "608-2161.u1",  0x1000000, 0x1000100 },
            { "608-2161.u4",  0x2000000, 0x1000100 },
            { "608-2161.u2",  0x3000000, 0x1000100 },
            { "608-2161.u15", 0x4000000, 0x1000100 },
            { "608-2161.u17", 0x5000000, 0x1000100 },
            { "608-2161.u14", 0x6000000, 0x1000100 },
            { "608-2161.u16", 0x7000000, 0x1000100 },
            { NULL, 0, 0 },
        }
    },
    // Demolish Fist
    {
        "demofist",
        NULL,
        "Demolish Fist",
        0x8000000,
        0x90,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax0601p01.ic18", 0x0000000, 0x0800000 },
            { "ax0601m01.ic11", 0x1000000, 0x1000000 },
            { "ax0602m01.ic12", 0x2000000, 0x1000000 },
            { "ax0603m01.ic13", 0x3000000, 0x1000000 },
            { "ax0604m01.ic14", 0x4000000, 0x1000000 },
            { "ax0605m01.ic15", 0x5000000, 0x1000000 },
            { "ax0606m01.ic16", 0x6000000, 0x1000000 },
            { "ax0607m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Dirty Pigskin Football
    {
        "dirtypig",
        NULL,
        "Dirty Pigskin Football",
        0x8000000,
        0x2a,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "695-0014.u3",  0x0000000, 0x1000000 },
            { "695-0014.u1",  0x1000000, 0x1000000 },
            { "695-0014.u4",  0x2000000, 0x1000000 },
            { "695-0014.u2",  0x3000000, 0x1000000 },
            { "695-0014.u15", 0x4000000, 0x1000000 },
            { "695-0014.u17", 0x5000000, 0x1000000 },
            { "695-0014.u14", 0x6000000, 0x1000000 },
            { "695-0014.u16", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Dolphin Blue
    {
        "dolphin",
        NULL,
        "Dolphin Blue",
        0x8000000,
        0x40,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax0401p01.ic18", 0x0000000, 0x0800000 },
            { "ax0401m01.ic11", 0x1000000, 0x1000000 },
            { "ax0402m01.ic12", 0x2000000, 0x1000000 },
            { "ax0403m01.ic13", 0x3000000, 0x1000000 },
            { "ax0404m01.ic14", 0x4000000, 0x1000000 },
            { "ax0405m01.ic15", 0x5000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Fist Of The North Star
    {
        "fotns",
        NULL,
        "Fist Of The North Star",
        0x8000000,
        0xc2,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1901p01.ic18", 0x0000000, 0x0800000 },
            { "ax1901m01.ic11", 0x1000000, 0x1000000 },
            { "ax1902m01.ic12", 0x2000000, 0x1000000 },
            { "ax1903m01.ic13", 0x3000000, 0x1000000 },
            { "ax1904m01.ic14", 0x4000000, 0x1000000 },
            { "ax1905m01.ic15", 0x5000000, 0x1000000 },
            { "ax1906m01.ic16", 0x6000000, 0x1000000 },
            { "ax1907m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Faster Than Speed
    {
        "ftspeed",
        NULL,
        "Faster Than Speed",
        0x9000000,
        0x6b,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1701p01.ic18", 0x0000000, 0x0800000 },
            { "ax1701m01.ic11", 0x1000000, 0x1000000 },
            { "ax1702m01.ic12", 0x2000000, 0x1000000 },
            { "ax1703m01.ic13", 0x3000000, 0x1000000 },
            { "ax1704m01.ic14", 0x4000000, 0x1000000 },
            { "ax1705m01.ic15", 0x5000000, 0x1000000 },
            { "ax1706m01.ic16", 0x6000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &ftspeed_inputs,
    },
    // Guilty Gear Isuka
    {
        "ggisuka",
        NULL,
        "Guilty Gear Isuka",
        0x9000000,
        0xed,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1201p01.ic18", 0x0000000, 0x0800000 },
            { "ax1201m01.ic10", 0x0800000, 0x1000000 },
            { "ax1202m01.ic11", 0x1000000, 0x1000000 },
            { "ax1203m01.ic12", 0x2000000, 0x1000000 },
            { "ax1204m01.ic13", 0x3000000, 0x1000000 },
            { "ax1205m01.ic14", 0x4000000, 0x1000000 },
            { "ax1206m01.ic15", 0x5000000, 0x1000000 },
            { "ax1207m01.ic16", 0x6000000, 0x1000000 },
            { "ax1208m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Guilty Gear X ver. 1.5
    {
        "ggx15",
        NULL,
        "Guilty Gear X ver. 1.5",
        0x8000000,
        0xc9,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax0801p01.ic18", 0x0000000, 0x0800000 },
            { "ax0801m01.ic11", 0x1000000, 0x1000000 },
            { "ax0802m01.ic12", 0x2000000, 0x1000000 },
            { "ax0803m01.ic13", 0x3000000, 0x1000000 },
            { "ax0804m01.ic14", 0x4000000, 0x1000000 },
            { "ax0805m01.ic15", 0x5000000, 0x1000000 },
            { "ax0806m01.ic16", 0x6000000, 0x1000000 },
            { "ax0807m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // The King of Fighters Neowave
    {
        "kofnw",
        NULL,
        "The King of Fighters Neowave",
        0x8000000,
        0x99,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax2201en_p01.ic18", 0x0000000, 0x0800000 },
            { "ax2201m01.ic11",    0x1000000, 0x1000000 },
            { "ax2202m01.ic12",    0x2000000, 0x1000000 },
            { "ax2203m01.ic13",    0x3000000, 0x1000000 },
            { "ax2204m01.ic14",    0x4000000, 0x1000000 },
            { "ax2205m01.ic15",    0x5000000, 0x1000000 },
            { "ax2206m01.ic16",    0x6000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &kofnw_inputs
    },
    // The King of Fighters Neowave (Japan)
    {
        "kofnwj",
        "kofnw",
        "The King of Fighters Neowave (Japan)",
        0x8000000,
        0x99,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax2201jp_p01.ic18", 0x0000000, 0x0800000 },
            // these are taken from the above set, game *seems* to work fine with these
            { "ax2201m01.ic11", 0x1000000, 0x1000000 },
            { "ax2202m01.ic12", 0x2000000, 0x1000000 },
            { "ax2203m01.ic13", 0x3000000, 0x1000000 },
            { "ax2204m01.ic14", 0x4000000, 0x1000000 },
            { "ax2205m01.ic15", 0x5000000, 0x1000000 },
            { "ax2206m01.ic16", 0x6000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &kofnw_inputs
    },
    // The King of Fighters XI
    {
        "kofxi",
        NULL,
        "The King of Fighters XI",
        0x14000000,
        0xd3,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax3201p01.fmem1", 0x00000000, 0x0800000 },
            { "ax3201m01.mrom1", 0x02000000, 0x2000000 },
            { "ax3202m01.mrom2", 0x04000000, 0x2000000 },
            { "ax3203m01.mrom3", 0x06000000, 0x2000000 },
            { "ax3204m01.mrom4", 0x0a000000, 0x2000000 },
            { "ax3205m01.mrom5", 0x0c000000, 0x2000000 },
            { "ax3206m01.mrom6", 0x0e000000, 0x2000000 },
            { "ax3207m01.mrom7", 0x12000000, 0x2000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &kofxi_inputs
    },
    // Knights of Valour - The Seven Spirits
    {
        "kov7sprt",
        NULL,
        "Knights of Valour - The Seven Spirits",
        0x8000000,
        0x35,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1301p01.ic18", 0x0000000, 0x0800000 },
            { "ax1301m01.ic11", 0x1000000, 0x1000000 },
            { "ax1301m02.ic12", 0x2000000, 0x1000000 },
            { "ax1301m03.ic13", 0x3000000, 0x1000000 },
            { "ax1301m04.ic14", 0x4000000, 0x1000000 },
            { "ax1301m05.ic15", 0x5000000, 0x1000000 },
            { "ax1301m06.ic16", 0x6000000, 0x1000000 },
            { "ax1301m07.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Maximum Speed
    {
        "maxspeed",
        NULL,
        "Maximum Speed",
        0x9000000,
        0x55,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax0501p01.ic18", 0x0000000, 0x0800000 },
            { "ax0501m01.ic11", 0x1000000, 0x1000000 },
            { "ax0502m01.ic12", 0x2000000, 0x1000000 },
            { "ax0503m01.ic13", 0x3000000, 0x1000000 },
            { "ax0504m01.ic14", 0x4000000, 0x1000000 },
            { "ax0505m01.ic15", 0x5000000, 0x1000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &maxspeed_inputs
    },
    // Metal Slug 6
    {
        "mslug6",
        NULL,
        "Metal Slug 6",
        0xc000000,
        0x82,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax3001p01.fmem1", 0x0000000, 0x0800000 },
            { "ax3001m01.mrom1", 0x2000000, 0x2000000 },
            { "ax3002m01.mrom2", 0x4000000, 0x2000000 },
            { "ax3003m01.mrom3", 0x6000000, 0x2000000 },
            { "ax3004m01.mrom4", 0xa000000, 0x2000000 },
            { NULL, 0, 0 },
        }
    },
    // NeoGeo Battle Coliseum
    {
        "ngbc",
        NULL,
        "NeoGeo Battle Coliseum",
        0x14000000,
        0xa0,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax3301en_p01.fmem1", 0x00000000, 0x0800000 },
            { "ax3301m01.mrom1",    0x02000000, 0x2000000 },
            { "ax3302m01.mrom2",    0x04000000, 0x2000000 },
            { "ax3303m01.mrom3",    0x06000000, 0x2000000 },
            { "ax3304m01.mrom4",    0x0a000000, 0x2000000 },
            { "ax3305m01.mrom5",    0x0c000000, 0x2000000 },
            { "ax3306m01.mrom6",    0x0e000000, 0x2000000 },
            { "ax3307m01.mrom7",    0x12000000, 0x2000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &ngbc_inputs
    },
    // NeoGeo Battle Coliseum (Japan)
    {
        "ngbcj",
        "ngbc",
        "NeoGeo Battle Coliseum (Japan)",
        0x14000000,
        0xa0,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax3301p01.fmem1", 0x00000000, 0x0800000 },
            { "ax3301m01.mrom1", 0x02000000, 0x2000000 },
            { "ax3302m01.mrom2", 0x04000000, 0x2000000 },
            { "ax3303m01.mrom3", 0x06000000, 0x2000000 },
            { "ax3304m01.mrom4", 0x0a000000, 0x2000000 },
            { "ax3305m01.mrom5", 0x0c000000, 0x2000000 },
            { "ax3306m01.mrom6", 0x0e000000, 0x2000000 },
            { "ax3307m01.mrom7", 0x12000000, 0x2000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &ngbc_inputs
    },
    // Ranger Mission
    {
        "rangrmsn",
        NULL,
        "Ranger Mission",
        0x8000000,
        0x88,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1601p01.ic18", 0x0000000, 0x0800000 },
            { "ax1601m01.ic11", 0x1000000, 0x1000000 },
            { "ax1602m01.ic12", 0x2000000, 0x1000000 },
            { "ax1603m01.ic13", 0x3000000, 0x1000000 },
            { "ax1604m01.ic14", 0x4000000, 0x1000000 },
            { "ax1605m01.ic15", 0x5000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // The Rumble Fish
    {
        "rumblef",
        NULL,
        "The Rumble Fish",
        0x8000000,
        0xaa,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1801p01.ic18", 0x0000000, 0x0800000 },
            { "ax1801m01.ic11", 0x1000000, 0x1000000 },
            { "ax1802m01.ic12", 0x2000000, 0x1000000 },
            { "ax1803m01.ic13", 0x3000000, 0x1000000 },
            { "ax1804m01.ic14", 0x4000000, 0x1000000 },
            { "ax1805m01.ic15", 0x5000000, 0x1000000 },
            { "ax1806m01.ic16", 0x6000000, 0x1000000 },
            { "ax1807m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // The Rumble Fish (prototype)
    {
        "rumblefp",
        "rumblef",
        "The Rumble Fish (prototype)",
        0x8000000,
        0x25,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ic12", 0x00000000, 0x00800000 },
            { "ic13", 0x00800000, 0x00800000 },
            { "ic14", 0x01000000, 0x00800000 },
            { "ic15", 0x01800000, 0x00800000 },
            { "ic16", 0x02000000, 0x00800000 },
            { "ic17", 0x02800000, 0x00800000 },
            { "ic18", 0x03000000, 0x00800000 },
            { "ic19", 0x03800000, 0x00800000 },
            { "ic20", 0x04000000, 0x00800000 },
            { "ic21", 0x04800000, 0x00800000 },
            { "ic22", 0x05000000, 0x00800000 },
            { "ic23", 0x05800000, 0x00800000 },
            { "ic24", 0x06000000, 0x00800000 },
            { "ic25", 0x06800000, 0x00800000 },
            { "ic26", 0x07000000, 0x00800000 },
            // IC27 populated, empty
            { NULL, 0, 0 },
        }
    },
    // The Rumble Fish 2
    {
        "rumblef2",
        NULL,
        "The Rumble Fish 2",
        0xe000000,
        0x07,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax3401p01.fmem1", 0x0000000, 0x0800000 },
            { "ax3401m01.mrom1", 0x2000000, 0x2000000 },
            { "ax3402m01.mrom2", 0x4000000, 0x2000000 },
            { "ax3403m01.mrom3", 0x6000000, 0x2000000 },
            { "ax3404m01.mrom4", 0xa000000, 0x2000000 },
            { "ax3405m01.mrom5", 0xc000000, 0x2000000 },
            { NULL, 0, 0 },
        }
    },
    // The Rumble Fish 2 (prototype)
    {
        "rumblf2p",
        "rumblef2",
        "The Rumble Fish 2 (prototype)",
        0xe000000,
        0x25,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ic12", 0x00000000, 0x00800000 },
            { "ic13", 0x00800000, 0x00800000 },
            { "ic14", 0x01000000, 0x00800000 },
            { "ic15", 0x01800000, 0x00800000 },
            { "ic16", 0x02000000, 0x00800000 },
            { "ic17", 0x02800000, 0x00800000 },
            { "ic18", 0x03000000, 0x00800000 },
            { "ic19", 0x03800000, 0x00800000 },
            { "ic20", 0x04000000, 0x00800000 },
            { "ic21", 0x04800000, 0x00800000 },
            { "ic22", 0x05000000, 0x00800000 },
            { "ic23", 0x05800000, 0x00800000 },
            { "ic24", 0x06000000, 0x00800000 },
            { "ic25", 0x06800000, 0x00800000 },
            { "ic26", 0x07000000, 0x00800000 },
            // IC27 populated, empty
            { NULL, 0, 0 },
        }
    },
    // Net Select: Salaryman Kintaro
    {
        "salmankt",
        NULL,
        "Net Select: Salaryman Kintaro",
        0x9000000,
        0x77,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax1401p01.ic18", 0x0000000, 0x0800000 },
            { "ax1401m01.ic11", 0x1000000, 0x1000000 },
            { "ax1402m01.ic12", 0x2000000, 0x1000000 },
            { "ax1403m01.ic13", 0x3000000, 0x1000000 },
            { "ax1404m01.ic14", 0x4000000, 0x1000000 },
            { "ax1405m01.ic15", 0x5000000, 0x1000000 },
            { "ax1406m01.ic16", 0x6000000, 0x1000000 },
            { "ax1407m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Samurai Spirits Tenkaichi Kenkakuden
    {
        "samsptk",
        NULL,
        "Samurai Spirits Tenkaichi Kenkakuden",
        0x14000000,
        0x1d,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax2901p01.fmem1", 0x00000000, 0x0800000 },
            { "ax2901m01.mrom1", 0x02000000, 0x2000000 },
            { "ax2902m01.mrom2", 0x04000000, 0x2000000 },
            { "ax2903m01.mrom3", 0x06000000, 0x2000000 },
            { "ax2904m01.mrom4", 0x0a000000, 0x2000000 },
            { "ax2905m01.mrom5", 0x0c000000, 0x2000000 },
            { "ax2906m01.mrom6", 0x0e000000, 0x2000000 },
            { "ax2907m01.mrom7", 0x12000000, 0x2000000 },
            { NULL, 0, 0 },
        },
        NULL,
        &samsptk_inputs
    },
    // Sports Shooting USA
    {
        "sprtshot",
        NULL,
        "Sports Shooting USA",
        0x8000000,
        0x64,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax0101p01.ic18", 0x0000000, 0x0800000 },
            { "ax0101m01.ic11", 0x1000000, 0x1000000 },
            { "ax0102m01.ic12", 0x2000000, 0x1000000 },
            { "ax0103m01.ic13", 0x3000000, 0x1000000 },
            { "ax0104m01.ic14", 0x4000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Sushi Bar
    {
        "sushibar",
        NULL,
        "Sushi Bar",
        0x8000000,
        0x25,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ic12", 0x00000000, 0x00800000 },
            { "ic14", 0x01000000, 0x00800000 },
            { "ic15", 0x01800000, 0x00800000 },
            { "ic16", 0x02000000, 0x00800000 },
            { "ic17", 0x02800000, 0x00800000 },
            { "ic18", 0x03000000, 0x00800000 },
            { NULL, 0, 0 },
        }
    },
    // Net Select Horse Racing: Victory Furlong"
    {
        "vfurlong",
        NULL,
        "Net Select Horse Racing: Victory Furlong",
        0x9000000,
        0xdb,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax2001p01.ic18", 0x0000000, 0x0800000 },
            { "ax2001m01.ic11", 0x1000000, 0x1000000 },
            { "ax2002m01.ic12", 0x2000000, 0x1000000 },
            { "ax2003m01.ic13", 0x3000000, 0x1000000 },
            { "ax2004m01.ic14", 0x4000000, 0x1000000 },
            { "ax2005m01.ic15", 0x5000000, 0x1000000 },
            { "ax2006m01.ic16", 0x6000000, 0x1000000 },
            { "ax2007m01.ic17", 0x7000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // WaiWai Drive
    {
        "waidrive",
        NULL,
        "WaiWai Drive",
        0x4000000,
        0x45,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT270,
        {
            { "u3", 0x0000000, 0x1000000 },
            { "u1", 0x1000000, 0x1000000 },
            { NULL, 0, 0 },
        }
    },
    // Extreme Hunting
    {
        "xtrmhunt",
        NULL,
        "Extreme Hunting",
        0x8000000,
        0xe4,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "ax2401p01.ic18", 0x0000000, 0x0800000 },
            { "ax2401m01.ic11", 0x1000000, 0x1000000 },
            { "ax2402m01.ic12", 0x2000000, 0x1000000 },
            { "ax2403m01.ic13", 0x3000000, 0x1000000 },
            { "ax2404m01.ic14", 0x4000000, 0x1000000 },
            { "ax2405m01.ic15", 0x5000000, 0x1000000 },
            { "ax2406m01.ic16", 0x6000000, 0x1000000 },
        }
    },
    // Extreme Hunting 2
    {
        "xtrmhnt2",
        NULL,
        "Extreme Hunting 2",
        0x8000000,
        0x2a,
        "awbios",
        AW,
        REGION_AUSTRALIA,
        ROT0,
        {
            { "610-0752.u3",    0x0000000, 0x1000000 },
            { "610-0752.u1",    0x1000000, 0x1000000 },
            { "610-0752.u4",    0x2000000, 0x1000000 },
            { "610-0752.u2",    0x3000000, 0x1000000 },
            { "610-0752.u15",   0x4000000, 0x1000000 },
            { "610-0752.u17",   0x5000000, 0x1000000 },
            { "610-0752.u14",   0x6000000, 0x1000000 },
            { "610-0752.u16",   0x7000000, 0x1000000 },

            //ROM_REGION( 0x1400000, "network", 0)    // network board
            //ROM_LOAD( "fpr-24330a.ic2", 0x000000, 0x400000, CRC(8d89877e) SHA1(6caafc49114eb0358e217bc2d1a3ab58a93c8d19) )
            //ROM_LOAD( "flash128.ic4s", 0x400000, 0x1000000, CRC(866ed675) SHA1(2c4c06935b7ab1876e640cede51713b841833567) )

            { NULL, 0, 0 },
        }
    },
    {
        NULL
    }
};
