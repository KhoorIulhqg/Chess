#include "zobrist.h"

// Auto-generated Zobrist hashing constants
const uint32_t ZOBRIST_PIECES[2][7][64] = {
    { // White pieces
        { // Empty squares (index 0)
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000
        },
        { // Pawns (index 1)
            0x89463E85, 0x1FF49B78, 0xF91E1D4C, 0xEC1B8CA1,
            0x60E7A113, 0x142C3FE8, 0x8D5288F1, 0x4B0DBB41,
            0xD453DD32, 0xA0EE89AE, 0x9E574F7A, 0xE2ACF72F,
            0xDC98D2C1, 0x5C941CF0, 0x93CD59BF, 0x3139D32C,
            0xB45ED1F0, 0x11CE5DD2, 0x0BBB2599, 0xA9488D99,
            0x3A578A8E, 0xC5E7CE8A, 0x4A15544D, 0xFC377A4C,
            0x146D3F31, 0xDAF61A26, 0x3B982EF8, 0xDDD1DFB2,
            0x19DB3AD0, 0x614FF3D7, 0x47294739, 0x7412B293,
            0xA2BC372F, 0xD58842DE, 0x5D65A441, 0x29A3B2E9,
            0x5EC42E08, 0x5AF30553, 0x35A240AE, 0xAB9099A4,
            0x4458A885, 0xB3AA7EFE, 0xEFC89849, 0xAEFCFAD8,
            0xA5E5A5AB, 0x12476F57, 0x9BF00273, 0xA28DEFE3,
            0x2BCFBE01, 0x88BD6407, 0xBAA80DD4, 0x3EABEDCB,
            0x29D4BEEF, 0x7656AF72, 0x6123FDF7, 0x451B4CF3,
            0xFD5166E6, 0xECE66FA2, 0xA3D70628, 0xB02B61C4,
            0x8E944239, 0x3838B326, 0xAF42E12F, 0x5304317F
        },
        { // Knights (index 2)
            0xD7C524A5, 0xC4B032CC, 0xC6A7EE39, 0x0E51F30D,
            0x3AA2E4F9, 0xD261A7AB, 0x0837B8A3, 0xCE177B4E,
            0x50C187FC, 0x66B2BC5B, 0x448AAA9E, 0x10F1BC81,
            0x3602F8AC, 0xE9C349E0, 0xF16287E4, 0x9132B63E,
            0xE059A0EE, 0xB7C93ACF, 0x508EBAD7, 0x366EB16F,
            0xA7CAD415, 0x7FCD9EB1, 0x654821D0, 0xE27A984D,
            0xEA1FCA65, 0xA491F0B2, 0x757750A9, 0x24933B83,
            0x43CF2FDE, 0x23BED01D, 0x3F22FAF8, 0xBEB79919,
            0x8FB5D27B, 0x89FA6A68, 0x434308BC, 0xBF3C4C06,
            0x95A76D79, 0x6DADD6C7, 0xE5D7B875, 0x956269F0,
            0x663F1C97, 0x5CABCC97, 0x382567B8, 0xFF50BDE4,
            0xFF5E9FF0, 0x2369B584, 0x827050A8, 0x7E570DDF,
            0x1745D6D8, 0xC17AF08A, 0x0C0FD195, 0xDC713D96,
            0x1C11F735, 0x27209BDF, 0xA0A04DC4, 0x28F49481,
            0xCAC5B68C, 0xAE340454, 0x6C12ACE8, 0x98AE4334,
            0x10435A10, 0x62801C45, 0x61B1CD22, 0x988C24C9
        },
        { // Bishops (index 3)
            0xFF01CF99, 0x77D21E02, 0x877409A9, 0x405CACEC,
            0xF89897B9, 0x8DA0365B, 0xDC5C0EED, 0xF143262F,
            0x02F06B90, 0xAE270DA7, 0xB88139B9, 0x1D53434B,
            0xAE849217, 0xE2817EFD, 0x8976E334, 0xC0398710,
            0x444EA7C8, 0xC4C2E2E3, 0xA4161293, 0x5715BD6F,
            0x1C8EAEE9, 0x4B22D308, 0x6F4CC69A, 0x287D06CA,
            0x74273CA3, 0x00D4AF59, 0xF42D47CC, 0xB8DB0672,
            0xE037E5ED, 0xB83CFE0B, 0x436D76E2, 0xF8CDA88B,
            0x8026695F, 0xC30FF46E, 0x2DBC2134, 0x81F76D1C,
            0xE9A1FA6F, 0x1B3DBD5C, 0xDEDA4E16, 0xA013AC6E,
            0x4C66E0A8, 0xD777A477, 0xA39231A7, 0x81F631D4,
            0x9BE578C7, 0x32EBD689, 0x2720797D, 0x5FB8D16C,
            0xC333E861, 0x295B4715, 0x8A14BE62, 0xF4188F3F,
            0xC754108F, 0xEC24A3C5, 0x87C5421E, 0xEB2263DD,
            0x00257AD1, 0x99546EB4, 0x52FBE43B, 0x7D154385,
            0x04FC6D82, 0x1CA35CFB, 0xEDD96831, 0x5CEC4EB5
        },
        { // Rooks (index 4)
            0xE0F3EAB0, 0xFC3E058B, 0xD4E80839, 0xCE88CB2D,
            0x4EB93EFF, 0x3D4CBF37, 0x0ED42F1A, 0x3DA9C2A9,
            0xE0C53CB8, 0x913E4DE2, 0xF26B4776, 0x14296C07,
            0x15ED6269, 0xBB5E4BCF, 0x7C69DEE1, 0xD0E6E660,
            0x11B7E948, 0xFA5D3100, 0xC2B6D2C5, 0x885F6E66,
            0xC40DB9B4, 0x2031D750, 0x20DE435D, 0xA8E56E0C,
            0x79AC1B1E, 0xF264ACCC, 0x8CBFEDB0, 0x2A45C2AB,
            0x43DAC043, 0x8715A103, 0xDF57C59A, 0x9B49BD26,
            0x6C52C49F, 0xF6E07CC0, 0x36386821, 0xEDCD465E,
            0x8A0F4EFB, 0xC1590F53, 0xBADCC32A, 0xB09B2A5C,
            0x337EA2DF, 0xB683D2E6, 0x4FCCA39A, 0x66245BFA,
            0xFEC21BBE, 0xABF3AD39, 0xA65E688E, 0x5F987C71,
            0x702753A1, 0xE64D1BCB, 0x847FD9B4, 0x7394988F,
            0x1EFA2197, 0x3F76BE1D, 0x3985C3CF, 0x1064005C,
            0x568CC69B, 0x05628059, 0x969B6662, 0x8DCDCD03,
            0x3AE8CC93, 0x96A402F2, 0x38602AB6, 0x01D74256
        },
        { // Queens (index 5)
            0x122C9A56, 0xB535106E, 0xA18FF6B6, 0x0F1259E0,
            0x3A9BEDD4, 0x114125C6, 0xE7C99B26, 0x080AADFB,
            0xDC1110C1, 0x5496F63C, 0x1223B513, 0x839FBC50,
            0x3CEDDF2D, 0x474A493B, 0xAB4220A7, 0x7C441FE7,
            0x36D8393A, 0x8A0B3C33, 0x21DF306F, 0xB92DA22B,
            0xEF7DDC76, 0xE1E3DB63, 0x922FE15A, 0x93829B43,
            0x7900F7F9, 0x3E351128, 0xC8DCD19F, 0x7914C120,
            0xCEB81F9D, 0x683514F2, 0x30BEB45F, 0x1825BC54,
            0x18D0752B, 0xA8B317FA, 0x6E595ED3, 0x5AB33EDF,
            0x6C6FA611, 0x693DFFBC, 0x778EEDB3, 0xDD2467AC,
            0xBAA4B71A, 0x0DDE29A6, 0xAC619E63, 0xA748DBCF,
            0xFBF24050, 0xA56C0941, 0x1931E9EE, 0x0F844FEF,
            0x6712303A, 0xBA6C34AB, 0x56DC8907, 0xCCF3A171,
            0xDC96925E, 0x1BF90E27, 0x3FA7F104, 0x310C0C00,
            0x30B187EF, 0x894A05E4, 0x72D8567D, 0x23E2FCB4,
            0x6C006F61, 0x2EF91276, 0x474EBC19, 0x766ECB15
        },
        { // Kings (index 6)
            0x3FF350BF, 0xDFDE4FBF, 0xEC5B227C, 0x134C6C92,
            0x71710434, 0xCEDA8BBB, 0xDC815FE7, 0xDB20A56E,
            0x8CE21EA3, 0x19108BE5, 0x0CF35B58, 0xA6F2F7B8,
            0xFFD0F9D5, 0x8A63F881, 0xD605E770, 0x03C72BA8,
            0xF8102383, 0x17E011B7, 0xED2662E9, 0xC0E9AB30,
            0xD9441FA5, 0x3C835DC0, 0x2A935D62, 0x680AC07A,
            0x7C52FA17, 0x7B3A4E3E, 0x36B82481, 0xDD59BA71,
            0x66AA9385, 0xE7067EF4, 0x0F02BAD0, 0x2A25A888,
            0x610461E3, 0x008D4127, 0xFC3D3348, 0x63F2AE24,
            0x43E458FC, 0xED3049CF, 0xC8B8D9C6, 0xC8FE3CCD,
            0x747B6DBA, 0x490617F2, 0x6C4A37EA, 0xB253D218,
            0xF512C4C3, 0xBB026576, 0xFED4057D, 0xC88A618E,
            0x8E46D534, 0xA97065E1, 0xB7E99ACA, 0x7C967F79,
            0x27A0C3D7, 0x309D258C, 0x4BF50B52, 0x37BB3EEC,
            0xF7FD5646, 0x0EF8C2D6, 0x944528C0, 0xBC594585,
            0x8ACD4E10, 0x0F9AEA4B, 0xBF7B539B, 0x504867BA
        }
    },
    { // Black pieces
        { // Empty squares (index 0)
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000
        },
        { // Pawns (index 1)
            0x12C136E0, 0x89A2688B, 0x369147EB, 0x8181A8CC,
            0x43E42CAF, 0x21E8AC68, 0xEEEA163E, 0x5958A499,
            0xE1805081, 0x119C4EA3, 0xE117DAC3, 0x3E896C64,
            0x5E9953D2, 0x48F4EF12, 0x286218B8, 0x702CDD20,
            0xD5704F32, 0x8B10550C, 0xB41B3143, 0x4D71C366,
            0x9C96E9EC, 0xFBDDCF7C, 0xFCBB4E59, 0xCE9E1A11,
            0xA76AFDE6, 0x8768A84F, 0x0200B1F0, 0xAAF91531,
            0xD12DBC9A, 0x8DFA6A56, 0x4CA415EA, 0xEE87905E,
            0xA9D3D7C7, 0x1A84A51A, 0xF05DB76E, 0xE0CCEDC5,
            0x2260E70F, 0x43B409EF, 0x1D8CBBAC, 0xE3C43657,
            0x1B66B5A9, 0xBE0F051B, 0x8DA01097, 0x27CB6F2A,
            0x45B89CD9, 0x48212DDB, 0x9AD620AB, 0x35EBD32D,
            0xB7B56EA7, 0x57C700AA, 0x341EF40B, 0xAFFFCFD2,
            0xA25D6B29, 0xDA587E8A, 0x439472E6, 0x81627CF1,
            0x7D106C60, 0x40497B71, 0xE7C421C7, 0xE87D1C78,
            0xD89A40C0, 0x0D01280F, 0x17A0DF49, 0xA2607723
        },
        { // Knights (index 2)
            0x6C6F7633, 0xD450281C, 0x46D483F3, 0x0B49452D,
            0x00E85ECE, 0x5563F616, 0xC56811CD, 0x217D65A0,
            0xA319DCB4, 0xFAD409E2, 0x430F801D, 0x295D6FBF,
            0xBDC14F1F, 0x711C21C9, 0x8D3AED99, 0xB4A69F3C,
            0x6D7CE3C9, 0x8F9797B0, 0x0279B6A6, 0x1CA3C448,
            0x13432E61, 0xF1EEDBA3, 0xE21342B0, 0xB0E6A969,
            0xE767DCEA, 0x26286BFB, 0x8BABCE3B, 0x093923DE,
            0xD5A804EB, 0x5E84F058, 0x951F58D0, 0x8D7248E2,
            0x25E97977, 0x6E068097, 0x20A04502, 0x0AB54BDE,
            0x4EEA04E7, 0x5D59CD2A, 0xE623A689, 0xEEDEDB07,
            0xCBCEABDE, 0xF8E1DAA7, 0xDC570131, 0x0A368CE7,
            0xE61FECC0, 0x5B9962C6, 0x35C7936C, 0xAE9BEC36,
            0x3FE12E47, 0xAABC25FA, 0x1A50AEC3, 0x5A8AAECA,
            0xC7B5B2BC, 0x8F5486B7, 0xE256A6DC, 0xDFED2C43,
            0x6808593F, 0xF94D6204, 0x9EE3AC2A, 0xBFDDC3D9,
            0x2790CEBD, 0xECFEDB99, 0xEE0CAEB5, 0x3C9AD14C
        },
        { // Bishops (index 3)
            0xDD56CC94, 0x2999B735, 0xF9E8A369, 0xCCC56569,
            0xCF8EBC5A, 0x2D534DD0, 0xE1A47E10, 0x698C206F,
            0x0658663A, 0x2DEA9493, 0xBC8F7D29, 0xECAB3301,
            0x550A1B46, 0xC84A7B28, 0xEE49F329, 0x696608AA,
            0xCD5F4822, 0xAB7F089A, 0xDD334CC7, 0xBC2CBB0D,
            0xCF8D446A, 0x3F87E362, 0x444D610B, 0x28C13091,
            0xC991603F, 0xB386F7A4, 0x1BAC27A7, 0x61EE411A,
            0xDF465290, 0x09E9DB0A, 0xDBCCC477, 0x787F2425,
            0x38F16A81, 0x33173470, 0xD10BD1D0, 0xEB1FA9F2,
            0x75D66ED4, 0x598336E3, 0x4E20FD1A, 0xD20EAC17,
            0xCB9BC326, 0xDF0F06CB, 0x3A43B2BA, 0x39118497,
            0x060EDF5B, 0xA8F7EF5A, 0x3170F437, 0x6601DDD0,
            0x5408F9AC, 0x475287AA, 0xDD463C09, 0x11C58EF0,
            0xF7860B50, 0xC5F8BC16, 0x4774BC58, 0x59E4B671,
            0xA43825B5, 0x8268690B, 0x6651529E, 0xADF4E62D,
            0xFB2CA025, 0xD7FA2D8D, 0x89456F27, 0x54C63CD8
        },
        { // Rooks (index 4)
            0xF071D879, 0x0710D430, 0x1D870966, 0xE08596DB,
            0xF86C2CA2, 0x42DEFFCC, 0x2DB69EDB, 0x94A1875D,
            0xF668A617, 0xFBC9F87A, 0x43F59A85, 0x09CB3942,
            0x1BC044FC, 0x98B8E4CC, 0x6F3F920C, 0x587EF344,
            0xBA81EDD9, 0xC9535B63, 0x504D281F, 0x6FB78271,
            0x9B3080D5, 0xFBF6E16F, 0x82EC9F2D, 0x1D9AF659,
            0x629C2AE3, 0xE645F129, 0x939B462D, 0x30A900AD,
            0x41357E8C, 0x0B5CEA6A, 0xB572F3D0, 0x6FA17735,
            0x006ED6E3, 0x85197FF4, 0xECF27E76, 0xCE777F00,
            0x89D7FD6C, 0xAFD5DEA5, 0xB82C9074, 0xF0B5156B,
            0xBDF070AA, 0xBCAE8081, 0xABAE4F43, 0x3270E4FA,
            0x5D3D9E56, 0x6E6981A3, 0x11E9CDAA, 0xF2E9702D,
            0xAA0B7B14, 0xEBB7A385, 0x5487FD4F, 0x9F871CE7,
            0x505CC686, 0xA9D3C2E6, 0xD9178793, 0x1FE771D6,
            0xB841D0A0, 0xE6697833, 0x4CE1EB90, 0x81D2C7DE,
            0x4F2D4796, 0xAAB97E49, 0x688C7015, 0x5380B904
        },
        { // Queens (index 5)
            0x6703B636, 0xB27C4026, 0x4BB00F20, 0x8DEDF9FB,
            0x2095EEF6, 0x311C6EB6, 0x6BA25EFE, 0xAA38D0A1,
            0xF0BBAC67, 0x610FAA3F, 0xAD64B56C, 0xBF85BF0E,
            0xE71E43A6, 0x2C8D0E44, 0x9D9262AF, 0x91B0E1D9,
            0x4D0B0D1A, 0x67F48AD5, 0x8C459CE2, 0xD56F0350,
            0x001A9A8B, 0x4DCABFB7, 0x49732D6C, 0x35CE8841,
            0x6E0D2648, 0xC9277D9B, 0x9479E1E6, 0x9B4E2C24,
            0xA79AC9AA, 0x527EECFA, 0x77097749, 0x7118E364,
            0x71316269, 0xACF5E81E, 0x36B5229A, 0x82DC4C8E,
            0x7922BAC2, 0xCB323E35, 0xE6B3C944, 0xF5B78CC7,
            0xCBC84759, 0xBC67F831, 0x2B70E525, 0xA8AA7158,
            0x15B52908, 0x48A639D0, 0x83F4A9A9, 0xA9F25336,
            0xA2086977, 0x9E87E04C, 0x55CEE5DB, 0x17E8392A,
            0xD1843324, 0xF3B63FE1, 0xC04A96C4, 0x3C20592F,
            0xAC3C5640, 0x4F77A665, 0x39820CFF, 0xCE7AE7F6,
            0x32FA2DE8, 0x25B8FD4B, 0x0640BE0F, 0x0BD4A990
        },
        { // Kings (index 6)
            0x3EAE0032, 0xFBE33B24, 0x79A28903, 0x9C7C7377,
            0xD98868DD, 0xC4BBB7A9, 0x12A4DEF0, 0x74962764,
            0x6A18CE4C, 0xE2D9DE5D, 0xA1384DDC, 0x935F2B0A,
            0x31C681EC, 0xB7E58481, 0xB24445A7, 0x624C69B6,
            0x7E8F8095, 0x664FA663, 0x3E75C3B4, 0x25C73C44,
            0xA7F36AE9, 0xB00805CC, 0x016B6287, 0xE4855AA1,
            0xC03F3538, 0xDC45D539, 0xC521BF2D, 0xE2ADD909,
            0x1B494E15, 0xC7468F59, 0x6CD66193, 0x3805F907,
            0x2D06E8CF, 0xCDDA24BA, 0xF53D4330, 0xB227462C,
            0x8498E113, 0x76ECBDD6, 0x0CDB1CA4, 0x8EB22579,
            0x3FCB7546, 0xEADF5085, 0xD92C9227, 0x1F115B76,
            0x74DAAEBF, 0x222282E1, 0xCD29A36F, 0x76F2DBFE,
            0xAAE65FC1, 0x87F8424D, 0xFCE68504, 0x8F15BA58,
            0x986F9025, 0x513A7052, 0xF335CBA3, 0xC1581092,
            0xE4347D51, 0x714C7DF4, 0x9CD6C852, 0xD0A44432,
            0xB8225688, 0xE45B712E, 0x81392443, 0x6D3EE1DC
        }
    }
};

const uint32_t ZOBRIST_CASTLING[16] = {
    0xD4A02E53, 0xE827A1B9, 0x8C41561B, 0x722764E6,
            0xE5AF6E39, 0x28BE9288, 0xBE6033F7, 0xDC8AEE30,
            0x79844388, 0x7337C599, 0x425A609F, 0xC074718E,
            0x3F4B1A70, 0xD701410D, 0xA33DC7AF, 0x46FDE062
};

const uint32_t ZOBRIST_EN_PASSANT[8] = {
    0xC40C5D91, 0xC715B2B9, 0x8573E793, 0x7C0E8CD8,
            0xA07295E9, 0x3D3F3799, 0x464C04AF, 0x709B7D97
};

const uint32_t ZOBRIST_SIDE_TO_MOVE = 0x13D5F2F7;