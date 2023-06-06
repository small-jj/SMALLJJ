#include "MoFtInd.h"  


#if COMPRESS_MONO_FONT

// Compressed mono font:
code BYTE tOSDFont1[] =
{
    // Code 000 [0x00]:
    0x00, 0x0F, 0x00, 0x11, 
    // Code 001 [0x01]:
    0x00, 0x0B, 0x03, 0xF0, 0x0F, 0xF0, 0x3F, 0xF0, 0x7F, 0xF0, 0xFF, 0xF1, 
    // Code 002 [0x02]:
    0x00, 0x0B, 0xFF, 0xF5, 
    // Code 003 [0x03]:
    0x00, 0x0B, 0xE0, 0x00, 0xFC, 0x00, 0xFF, 0x00, 0xFF, 0x80, 0xFF, 0xC0, 0xFF, 0xE0, 
    // Code 004 [0x04]:
    0x00, 0x0F, 0x00, 0x01, 
    // Code 005 [0x05]:
    0x00, 0x30, 0x00, 0x72, 0x00, 0xFD, 
    // Code 006 [0x06]:
    0xFC, 0x01, 0xF0, 0x00, 0xC0, 0x01, 0x80, 0x0C, 
    // Code 007 [0x07]:
    0x1F, 0xE0, 0x07, 0xF1, 0x01, 0xF0, 0x00, 0xF3, 0x00, 0x79, 
    // Code 008 [0x08]:
    0x00, 0x01, 0x80, 0x03, 0xC0, 0x0B, 
    // Code 009 [0x09]:
    0x00, 0xFF, 0x00, 0xF1, 
    // Code 010 [0x0a]:
    0x80, 0x01, 0x80, 0x1F, 
    // Code 011 [0x0b]:
    0x00, 0x01, 0xFF, 0xF9, 0xFF, 0x05, 
    // Code 012 [0x0c]:
    0x00, 0x01, 0xFF, 0xF9, 0x00, 0x05, 
    // Code 013 [0x0d]:
    0x00, 0x01, 0x80, 0x00, 0xC0, 0x07, 0x80, 0x00, 0x00, 0x05, 
    // Code 014 [0x0e]:
    0x00, 0x01, 0x07, 0xF0, 0x03, 0xF0, 0x01, 0xF0, 0x00, 0xF0, 0x00, 0x70, 0x00, 0x30, 0x00, 0x10, 0x00, 0x04, 0x00, 0x10, 0x00, 0x30, 0x00, 0x70, 0x00, 0xF0, 
    // Code 015 [0x0f]:
    0x00, 0x01, 0xFF, 0xF7, 0x7F, 0xF0, 0xFF, 0xF0, 0x7F, 0xF0, 0xFF, 0xF4, 
    // Code 016 [0x10]:
    0x00, 0x01, 0xFF, 0xCF, 
    // Code 017 [0x11]:
    0x00, 0x7F, 0x00, 0x71, 
    // Code 018 [0x12]:
    0xC0, 0x0F, 0xC0, 0x01, 
    // Code 019 [0x13]:
    0x80, 0x1F, 0x80, 0x11, 
    // Code 020 [0x14]:
    0xFF, 0x0F, 0xFF, 0x01, 
    // Code 021 [0x15]:
    0x00, 0x07, 0x00, 0x10, 0x00, 0x30, 0x00, 0x70, 0x00, 0xF0, 0x01, 0xF0, 0x03, 0xF0, 0x07, 0xF0, 0x0F, 0xF0, 0x07, 0xF0, 0x03, 0xF0, 
    // Code 022 [0x16]:
    0x01, 0xF0, 0x03, 0xF0, 0x07, 0xF0, 0x0F, 0xF0, 0x1F, 0xF0, 0x3F, 0xF0, 0x7F, 0xF0, 0xFF, 0xF9, 0xFF, 0xE0, 
    // Code 023 [0x17]:
    0xFF, 0xF4, 0xFF, 0xE0, 0xFF, 0xC0, 0xFF, 0x80, 0xFF, 0x00, 0xFE, 0x00, 0xFC, 0x00, 0xF8, 0x00, 0xF0, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0x80, 0x00, 0x00, 0x01, 
    // Code 024 [0x18]:
    0xFF, 0xC4, 0xBF, 0xC0, 0x1F, 0xC0, 0x0F, 0xC0, 0x07, 0xC0, 0x03, 0xC0, 0x01, 0xC0, 0x00, 0xC0, 0x00, 0x40, 0x00, 0x04, 
    // Code 025 [0x19]:
    0x01, 0xF0, 0x00, 0xF0, 0x00, 0x70, 0x00, 0x30, 0x00, 0x10, 0x00, 0x0C, 
    // Code 026 [0x1a]:
    0xFF, 0xC0, 0xFF, 0x80, 0xFF, 0x00, 0xFE, 0x00, 0xFC, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x20, 0x00, 0x00, 0x09, 
    // Code 027 [0x1b]:
    0x00, 0x0B, 0x3F, 0x80, 0x7F, 0xC4, 
    // Code 028 [0x1c]:
    0xFF, 0x0A, 0xFF, 0xF6, 
    // Code 029 [0x1d]:
    0x00, 0x0A, 0xFF, 0xF6, 
    // Code 030 [0x1e]:
    0x7F, 0xCA, 0xFF, 0xC6, 
    // Code 031 [0x1f]:
    0x80, 0x12, 0x80, 0x0E, 
    // Code 032 [0x20]:
    0xFF, 0xF2, 0x00, 0x0E, 
    // Code 033 [0x21]:
    0xFF, 0xC2, 0x00, 0x0E, 
    // Code 034 [0x22]:
    0x00, 0x7E, 0x00, 0xF2, 
    // Code 035 [0x23]:
    0x00, 0xF0, 0x00, 0x72, 0x00, 0x30, 0x00, 0x10, 0x00, 0x0B, 
    // Code 036 [0x24]:
    0xC0, 0x00, 0xE0, 0x00, 0xF0, 0x00, 0xF8, 0x00, 0xFC, 0x00, 0xFF, 0xF1, 0x7F, 0xF0, 0x3F, 0xF0, 0x0F, 0xF0, 0x03, 0xF0, 0x00, 0x06, 
    // Code 037 [0x25]:
    0x00, 0x04, 0xFF, 0xF5, 0x00, 0x06, 
    // Code 038 [0x26]:
    0x01, 0xF1, 0x03, 0xF0, 0x07, 0xF0, 0x1F, 0xE0, 0xFF, 0xC1, 0xFF, 0x80, 0xFE, 0x00, 0xF8, 0x00, 0xE0, 0x00, 0x00, 0x06, 
    // Code 039 [0x27]:
    0xC0, 0x00, 0x80, 0x01, 0x00, 0x0E, 
    // After compressed, size = 370
};
code WORD tMonoFontDataAddr[40] = {
    0x0000, 0x0004, 0x0010, 0x0014, 0x0022, 0x0026, 0x002C, 0x0034, 0x003E, 0x0044, 0x0048, 0x004C, 0x0052, 0x0058, 0x0062, 0x007C, 
    0x0088, 0x008C, 0x0090, 0x0094, 0x0098, 0x009C, 0x00B2, 0x00C4, 0x00DE, 0x00F2, 0x00FE, 0x0110, 0x0116, 0x011A, 0x011E, 0x0122, 
    0x0126, 0x012A, 0x012E, 0x0132, 0x013C, 0x0152, 0x0158, 0x016C, };


#else // No compress

#if 0 
// Mono font: Format 2: 1 word ==> 1 line
code WORD tOSDFont1[720] =
{
    // Code   0 [0x00] (INPUT_WHITE_0_0):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0010, 0x0010, 
    // Code   1 [0x01] (INPUT_WHITE_0_1):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03F0, 0x0FF0, 0x3FF0, 0x7FF0, 0xFFF0, 0xFFF0, 
    // Code   2 [0x02] (INPUT_WHITE_0_2):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 
    // Code   3 [0x03] (INPUT_WHITE_0_10):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE000, 0xFC00, 0xFF00, 0xFF80, 0xFFC0, 0xFFE0, 
    // Code   4 [0x04] (INPUT_WHITE_0_11):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code   5 [0x05] (INPUT_WHITE_1_0):
    0x0030, 0x0070, 0x0070, 0x0070, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 
    // Code   6 [0x06] (INPUT_WHITE_1_1):
    0xFC00, 0xFC00, 0xF000, 0xC000, 0xC000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
    // Code   7 [0x07] (INPUT_WHITE_1_10):
    0x1FE0, 0x07F0, 0x07F0, 0x01F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 
    // Code   8 [0x08] (INPUT_WHITE_1_11):
    0x0000, 0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 
    // Code   9 [0x09] (INPUT_WHITE_2_0):
    0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 0x00F0, 
    // Code  10 [0x0a] (INPUT_WHITE_2_1):
    0x8000, 0x8000, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 
    // Code  11 [0x0b] (INPUT_WHITE_2_2):
    0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 
    // Code  12 [0x0c] (INPUT_WHITE_2_3):
    0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  13 [0x0d] (INPUT_WHITE_2_6):
    0x0000, 0x0000, 0x8000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  14 [0x0e] (INPUT_WHITE_2_7):
    0x0000, 0x0000, 0x07F0, 0x03F0, 0x01F0, 0x00F0, 0x0070, 0x0030, 0x0010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0010, 0x0030, 0x0070, 0x00F0, 
    // Code  15 [0x0f] (INPUT_WHITE_2_8):
    0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0x7FF0, 0xFFF0, 0x7FF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 
    // Code  16 [0x10] (INPUT_WHITE_2_9):
    0x0000, 0x0000, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 
    // Code  17 [0x11] (INPUT_WHITE_2_10):
    0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 
    // Code  18 [0x12] (INPUT_WHITE_2_11):
    0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 
    // Code  19 [0x13] (INPUT_WHITE_3_1):
    0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 0x8010, 
    // Code  20 [0x14] (INPUT_WHITE_3_2):
    0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 
    // Code  21 [0x15] (INPUT_WHITE_3_6):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0010, 0x0030, 0x0070, 0x00F0, 0x01F0, 0x03F0, 0x07F0, 0x0FF0, 0x07F0, 0x03F0, 
    // Code  22 [0x16] (INPUT_WHITE_3_7):
    0x01F0, 0x03F0, 0x07F0, 0x0FF0, 0x1FF0, 0x3FF0, 0x7FF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFE0, 
    // Code  23 [0x17] (INPUT_WHITE_3_8):
    0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFE0, 0xFFC0, 0xFF80, 0xFF00, 0xFE00, 0xFC00, 0xF800, 0xF000, 0xE000, 0xC000, 0x8000, 0x0000, 0x0000, 
    // Code  24 [0x18] (INPUT_WHITE_3_9):
    0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xBFC0, 0x1FC0, 0x0FC0, 0x07C0, 0x03C0, 0x01C0, 0x00C0, 0x0040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  25 [0x19] (INPUT_WHITE_4_6):
    0x01F0, 0x00F0, 0x0070, 0x0030, 0x0010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  26 [0x1a] (INPUT_WHITE_4_7):
    0xFFC0, 0xFF80, 0xFF00, 0xFE00, 0xFC00, 0xF800, 0x7000, 0x2000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  27 [0x1b] (INPUT_WHITE_4_9):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3F80, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 
    // Code  28 [0x1c] (INPUT_WHITE_5_2):
    0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 
    // Code  29 [0x1d] (INPUT_WHITE_5_3):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 
    // Code  30 [0x1e] (INPUT_WHITE_5_9):
    0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0x7FC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 0xFFC0, 
    // Code  31 [0x1f] (INPUT_WHITE_6_1):
    0x8010, 0x8010, 0x8010, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 
    // Code  32 [0x20] (INPUT_WHITE_6_2):
    0xFFF0, 0xFFF0, 0xFFF0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  33 [0x21] (INPUT_WHITE_6_9):
    0xFFC0, 0xFFC0, 0xFFC0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  34 [0x22] (INPUT_WHITE_6_10):
    0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x00F0, 0x00F0, 0x00F0, 
    // Code  35 [0x23] (INPUT_WHITE_7_0):
    0x00F0, 0x0070, 0x0070, 0x0070, 0x0030, 0x0010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  36 [0x24] (INPUT_WHITE_7_1):
    0xC000, 0xE000, 0xF000, 0xF800, 0xFC00, 0xFFF0, 0xFFF0, 0x7FF0, 0x3FF0, 0x0FF0, 0x03F0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  37 [0x25] (INPUT_WHITE_7_2):
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0xFFF0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  38 [0x26] (INPUT_WHITE_7_10):
    0x01F0, 0x01F0, 0x03F0, 0x07F0, 0x1FE0, 0xFFC0, 0xFFC0, 0xFF80, 0xFE00, 0xF800, 0xE000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    // Code  39 [0x27] (INPUT_WHITE_7_11):
    0xC000, 0x8000, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
};

#else
// Mono font: Format 2: 1 byte ==> 1 line
code BYTE tINPMonoFont[1080] =
{ 
  // Code   0 [0x00] (INPUT_WHITE_0_0):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,  
  // Code   1 [0x01] (INPUT_WHITE_0_1):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x73, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
  // Code   2 [0x02] (INPUT_WHITE_0_2):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
  // Code   3 [0x03] (INPUT_WHITE_0_10):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xC0, 0xFF, 0xF0, 0xF8, 0xFF, 0xFC, 0xFE,  
  // Code   4 [0x04] (INPUT_WHITE_0_11):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code   5 [0x05] (INPUT_WHITE_1_0):
  0x00, 0x03, 0x07, 0x00, 0x07, 0x07, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F,  
  // Code   6 [0x06] (INPUT_WHITE_1_1):
  0xFF, 0xC0, 0xC0, 0xCF, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00,  
  // Code   7 [0x07] (INPUT_WHITE_1_10):
  0x01, 0xFE, 0x7F, 0x00, 0x7F, 0x1F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07,  
  // Code   8 [0x08] (INPUT_WHITE_1_11):
  0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00,  
  // Code   9 [0x09] (INPUT_WHITE_2_0):
  0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x0F,  
  // Code  10 [0x0a] (INPUT_WHITE_2_1):
  0x88, 0x00, 0x00, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01,  
  // Code  11 [0x0b] (INPUT_WHITE_2_2):
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,  
  // Code  12 [0x0c] (INPUT_WHITE_2_3):
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  13 [0x0d] (INPUT_WHITE_2_6):
  0x00, 0x00, 0x00, 0xC8, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  14 [0x0e] (INPUT_WHITE_2_7):
  0x00, 0x00, 0x00, 0x00, 0x7F, 0x3F, 0x00, 0x1F, 0x0F, 0x00, 0x07, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x07, 0x0F,  
  // Code  15 [0x0f] (INPUT_WHITE_2_8):
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
  // Code  16 [0x10] (INPUT_WHITE_2_9):
  0x00, 0x00, 0x00, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC,  
  // Code  17 [0x11] (INPUT_WHITE_2_10):
  0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07,  
  // Code  18 [0x12] (INPUT_WHITE_2_11):
  0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0x00, 0x00,  
  // Code  19 [0x13] (INPUT_WHITE_3_1):
  0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01, 0x88, 0x01, 0x01,  
  // Code  20 [0x14] (INPUT_WHITE_3_2):
  0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0,  
  // Code  21 [0x15] (INPUT_WHITE_3_6):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x07, 0x0F, 0x00, 0x1F, 0x3F, 0x00, 0x7F, 0xFF, 0x00, 0x7F, 0x3F,  
  // Code  22 [0x16] (INPUT_WHITE_3_7):
  0x00, 0x1F, 0x3F, 0x00, 0x7F, 0xFF, 0x31, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,  
  // Code  23 [0x17] (INPUT_WHITE_3_8):
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFC, 0xF8, 0xFF, 0xF0, 0xE0, 0xFF, 0xC0, 0x80, 0xEF, 0x00, 0x00, 0x8C, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  24 [0x18] (INPUT_WHITE_3_9):
  0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xBF, 0xFC, 0xFC, 0x01, 0xFC, 0xFC, 0x00, 0x7C, 0x3C, 0x00, 0x1C, 0x0C, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  25 [0x19] (INPUT_WHITE_4_6):
  0x00, 0x1F, 0x0F, 0x00, 0x07, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  26 [0x1a] (INPUT_WHITE_4_7):
  0xFF, 0xFC, 0xF8, 0xFF, 0xF0, 0xE0, 0xFF, 0xC0, 0x80, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  27 [0x1b] (INPUT_WHITE_4_9):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0xF8, 0xFC, 0x77, 0xFC, 0xFC, 0x77, 0xFC, 0xFC,  
  // Code  28 [0x1c] (INPUT_WHITE_5_2):
  0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xF0, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
  // Code  29 [0x1d] (INPUT_WHITE_5_3):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  
  // Code  30 [0x1e] (INPUT_WHITE_5_9):
  0x77, 0xFC, 0xFC, 0x77, 0xFC, 0xFC, 0x77, 0xFC, 0xFC, 0x77, 0xFC, 0xFC, 0x77, 0xFC, 0xFC, 0xF7, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC, 0xFF, 0xFC, 0xFC,  
  // Code  31 [0x1f] (INPUT_WHITE_6_1):
  0x88, 0x01, 0x01, 0x88, 0x01, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00, 0x88, 0x00, 0x00,  
  // Code  32 [0x20] (INPUT_WHITE_6_2):
  0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  33 [0x21] (INPUT_WHITE_6_9):
  0xFF, 0xFC, 0xFC, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  34 [0x22] (INPUT_WHITE_6_10):
  0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x0F, 0x00, 0x0F, 0x0F,  
  // Code  35 [0x23] (INPUT_WHITE_7_0):
  0x00, 0x0F, 0x07, 0x00, 0x07, 0x07, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  36 [0x24] (INPUT_WHITE_7_1):
  0xEC, 0x00, 0x00, 0xFF, 0x00, 0x80, 0xFF, 0xC0, 0xFF, 0x7F, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  37 [0x25] (INPUT_WHITE_7_2):
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  38 [0x26] (INPUT_WHITE_7_10):
  0x00, 0x1F, 0x1F, 0x00, 0x3F, 0x7F, 0xF1, 0xFE, 0xFC, 0xFF, 0xFC, 0xF8, 0xFF, 0xE0, 0x80, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
  // Code  39 [0x27] (INPUT_WHITE_7_11):
  0x8C, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

#endif 

#endif

code BYTE tINP4ColorFont[] =
{
};
code BYTE tINP8ColorFont[] =
{
};



 BYTE code  tINPPalette[] =
{
		 // 2 color [0x00]  INPUT_WHITE_0_0
		 CP256_RGB_C(   0,   0,   0), 
		 CP256_RGB_C( 255, 255, 255), 
};



 BYTE code strINPWindow[8][13]=
{
	{	 INM(0x00), INM(0x01), INM(0x02), INM(0x02), INM(0x02), INM(0x02), INM(0x02), INM(0x02), 
		 INM(0x02), INM(0x02), INM(0x03), INM(0x04), 
	 0},
	{	 INM(0x05), INM(0x06), INM(0x04), INM(0x04), INM(0x04), INM(0x04), INM(0x04), INM(0x04), 
		 INM(0x04), INM(0x04), INM(0x07), INM(0x08), 
	 0},
	{	 INM(0x09), INM(0x0A), INM(0x0B), INM(0x0C), INM(0x0C), INM(0x0C), INM(0x0D), INM(0x0E), 
		 INM(0x0F), INM(0x10), INM(0x11), INM(0x12), 
	 0},
	{	 INM(0x09), INM(0x13), INM(0x14), INM(0x04), INM(0x04), INM(0x04), INM(0x15), INM(0x16), 
		 INM(0x17), INM(0x18), INM(0x11), INM(0x12), 
	 0},
	{	 INM(0x09), INM(0x13), INM(0x14), INM(0x04), INM(0x04), INM(0x04), INM(0x19), INM(0x1A), 
		 INM(0x04), INM(0x1B), INM(0x11), INM(0x12), 
	 0},
	{	 INM(0x09), INM(0x13), INM(0x1C), INM(0x1D), INM(0x1D), INM(0x1D), INM(0x1D), INM(0x1D), 
		 INM(0x1D), INM(0x1E), INM(0x11), INM(0x12), 
	 0},
	{	 INM(0x09), INM(0x1F), INM(0x20), INM(0x20), INM(0x20), INM(0x20), INM(0x20), INM(0x20), 
		 INM(0x20), INM(0x21), INM(0x22), INM(0x12), 
	 0},
	{	 INM(0x23), INM(0x24), INM(0x25), INM(0x25), INM(0x25), INM(0x25), INM(0x25), INM(0x25), 
		 INM(0x25), INM(0x25), INM(0x26), INM(0x27), 
	 0}
};
