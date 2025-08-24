// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MOUDLARISATION OF BASIC DEFINES TO DO WITH THE
// MEMORY MANAGEMENT UNIT SPECIFICALLY - FOCUSSING MORE SO ON THE DEFINTIONS FOR
// OPERATION MASKS

#ifndef MMU_DEF_HH
#define MMU_DEF_HH

// NESTED INCLUDES

#include <common.hh>

namespace aquinas
{
    namespace mmu_def
    {
        #define     MMU_ATC_ENTRIES         64
        #define     MMU_ATC_MAX_TLB         7
        #define     MMU_ATC_BUS_ERR         0x08000000
        #define     MMU_ATC_CACHE           0x04000000
        #define     MMU_ATC_WRITE_PR        0x02000000
        #define     MMU_ATC_MOD             0x01000000
        #define     MMU_ATC_MASK            0x00FFFFFF
        #define     MMU_ATC_SHIFT           8

        #define     MMU_SR_BUS_ERR          0x8000
        #define     MMU_SR_SVR              0x2000
        #define     MMU_SR_WRITE_PROTECT    0x0800
        #define     MMU_SR_INVALID          0x0400
        #define     MMU_SR_MOD              0x0200
        #define     MMU_SR_TRANS            0x0040

        #define     MMU_DF_DT_MASK          0x00000003
        #define     MMU_DF_DT_INVALID       0x00000000
        #define     MMU_DF_DT_PAGE          0x00000001
        #define     MMU_DF_DT_TLB_4         0x00000002
        #define     MMU_DF_DT_TLB_8         0x00000003
        #define     MMU_DF_WP               0x00000004
        #define     MMU_DF_USED             0x00000008
        #define     MMU_DF_MODIFIED         0x00000010
        #define     MMU_DF_CI               0x00000040
        #define     MMU_DF_SVR              0x00000100
        #define     MMU_DF_ADDR_MASK        0xFFFFFFF0
        #define     MMU_DF_IND_ADDR_MASK    0xFFFFFFFC
    }
}

#endif
