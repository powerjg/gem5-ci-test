/*
 * Copyright (c) 2008 The Hewlett-Packard Development Company
 * All rights reserved.
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Gabe Black
 */

#include "arch/x86/bios/acpi.hh"

#include "mem/port.hh"
#include "params/X86ACPIRSDP.hh"
#include "params/X86ACPIRSDT.hh"
#include "params/X86ACPISysDescTable.hh"
#include "params/X86ACPIXSDT.hh"
#include "sim/byteswap.hh"
#include "sim/sim_object.hh"

using namespace std;

const char X86ISA::ACPI::RSDP::signature[] = "RSD PTR ";

X86ISA::ACPI::RSDP::RSDP(Params *p) : SimObject(p), oemID(p->oem_id),
    revision(p->revision), rsdt(p->rsdt), xsdt(p->xsdt)
{}

X86ISA::ACPI::SysDescTable::SysDescTable(Params *p,
        const char * _signature, uint8_t _revision) : SimObject(p),
    signature(_signature), revision(_revision),
    oemID(p->oem_id), oemTableID(p->oem_table_id),
    oemRevision(p->oem_revision),
    creatorID(p->creator_id), creatorRevision(p->creator_revision)
{}

X86ISA::ACPI::RSDT::RSDT(Params *p) :
    SysDescTable(p, "RSDT", 1), entries(p->entries)
{}

X86ISA::ACPI::XSDT::XSDT(Params *p) :
    SysDescTable(p, "XSDT", 1), entries(p->entries)
{}

X86ISA::ACPI::RSDP *
X86ACPIRSDPParams::create()
{
    return new X86ISA::ACPI::RSDP(this);
}

X86ISA::ACPI::RSDT *
X86ACPIRSDTParams::create()
{
    return new X86ISA::ACPI::RSDT(this);
}

X86ISA::ACPI::XSDT *
X86ACPIXSDTParams::create()
{
    return new X86ISA::ACPI::XSDT(this);
}
