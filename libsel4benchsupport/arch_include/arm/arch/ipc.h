/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */
#pragma once

#include <sel4bench/armv/sel4bench.h>

#define READ_COUNTER_BEFORE SEL4BENCH_READ_CCNT
#define READ_COUNTER_AFTER  SEL4BENCH_READ_CCNT

#define DO_CALL(ep, tag, swi) do { \
    register seL4_Word dest asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1") = tag; \
    register seL4_Word scno asm("r7") = seL4_SysCall; \
    asm volatile(NOPS swi NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_CALL_10(ep, tag, swi) do { \
    register seL4_Word dest asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1") = tag; \
    register seL4_Word scno asm("r7") = seL4_SysCall; \
    asm volatile(NOPS swi NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
        : "r2", "r3", "r4", "r5" \
    ); \
} while(0)

#define DO_SEND(ep, tag, swi) do { \
    register seL4_Word dest asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1") = tag; \
    register seL4_Word scno asm("r7") = seL4_SysSend; \
    asm volatile(NOPS swi NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_REPLY_RECV_10(ep, tag, swi) do { \
    register seL4_Word src asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1") = tag; \
    register seL4_Word scno asm("r7") = seL4_SysReplyRecv; \
    asm volatile(NOPS swi NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno) \
        : "r2", "r3", "r4", "r5" \
    ); \
} while(0)

#define DO_REPLY_RECV(ep, tag, swi) do { \
    register seL4_Word src asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1") = tag; \
    register seL4_Word scno asm("r7") = seL4_SysReplyRecv; \
    asm volatile(NOPS swi NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_RECV(ep, swi) do { \
    register seL4_Word src asm("r0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("r1"); \
    register seL4_Word scno asm("r7") = seL4_SysRecv; \
    asm volatile(NOPS swi NOPS \
        : "+r"(src), "=r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_REAL_CALL(ep, tag) DO_CALL(ep, tag, "swi $0")
#define DO_NOP_CALL(ep, tag) DO_CALL(ep, tag, "nop")
#define DO_REAL_REPLY_RECV(ep, tag) DO_REPLY_RECV(ep, tag, "swi $0")
#define DO_NOP_REPLY_RECV(ep, tag) DO_REPLY_RECV(ep, tag, "nop")
#define DO_REAL_CALL_10(ep, tag) DO_CALL_10(ep, tag, "swi $0")
#define DO_NOP_CALL_10(ep, tag) DO_CALL_10(ep, tag, "nop")
#define DO_REAL_REPLY_RECV_10(ep, tag) DO_REPLY_RECV_10(ep, tag, "swi $0")
#define DO_NOP_REPLY_RECV_10(ep, tag) DO_REPLY_RECV_10(ep, tag, "nop")
#define DO_REAL_SEND(ep, tag) DO_SEND(ep, tag, "swi $0")
#define DO_NOP_SEND(ep, tag) DO_SEND(ep, tag, "nop")
#define DO_REAL_RECV(ep) DO_RECV(ep, "swi $0")
#define DO_NOP_RECV(ep) DO_RECV(ep, "nop")

