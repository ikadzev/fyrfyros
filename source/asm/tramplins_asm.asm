%macro deadcode 0
    push 0x0DEADC0DE
%endmacro

[BITS 32]

global tramplin_00
global tramplin_01
global tramplin_02
global tramplin_03
global tramplin_04
global tramplin_05
global tramplin_06
global tramplin_07
global tramplin_08
global tramplin_09
global tramplin_0A
global tramplin_0B
global tramplin_0C
global tramplin_0D
global tramplin_0E
global tramplin_0F
global tramplin_10
global tramplin_11
global tramplin_12
global tramplin_13
global tramplin_14
global tramplin_15
global tramplin_16
global tramplin_17
global tramplin_18
global tramplin_19
global tramplin_1A
global tramplin_1B
global tramplin_1C
global tramplin_1D
global tramplin_1E
global tramplin_1F
global tramplin_20
global tramplin_21
global tramplin_22
global tramplin_23
global tramplin_24
global tramplin_25
global tramplin_26
global tramplin_27
global tramplin_28
global tramplin_29
global tramplin_2A
global tramplin_2B
global tramplin_2C
global tramplin_2D
global tramplin_2E
global tramplin_2F
global tramplin_30
global tramplin_31
global tramplin_32
global tramplin_33
global tramplin_34
global tramplin_35
global tramplin_36
global tramplin_37
global tramplin_38
global tramplin_39
global tramplin_3A
global tramplin_3B
global tramplin_3C
global tramplin_3D
global tramplin_3E
global tramplin_3F
global tramplin_40
global tramplin_41
global tramplin_42
global tramplin_43
global tramplin_44
global tramplin_45
global tramplin_46
global tramplin_47
global tramplin_48
global tramplin_49
global tramplin_4A
global tramplin_4B
global tramplin_4C
global tramplin_4D
global tramplin_4E
global tramplin_4F
global tramplin_50
global tramplin_51
global tramplin_52
global tramplin_53
global tramplin_54
global tramplin_55
global tramplin_56
global tramplin_57
global tramplin_58
global tramplin_59
global tramplin_5A
global tramplin_5B
global tramplin_5C
global tramplin_5D
global tramplin_5E
global tramplin_5F
global tramplin_60
global tramplin_61
global tramplin_62
global tramplin_63
global tramplin_64
global tramplin_65
global tramplin_66
global tramplin_67
global tramplin_68
global tramplin_69
global tramplin_6A
global tramplin_6B
global tramplin_6C
global tramplin_6D
global tramplin_6E
global tramplin_6F
global tramplin_70
global tramplin_71
global tramplin_72
global tramplin_73
global tramplin_74
global tramplin_75
global tramplin_76
global tramplin_77
global tramplin_78
global tramplin_79
global tramplin_7A
global tramplin_7B
global tramplin_7C
global tramplin_7D
global tramplin_7E
global tramplin_7F
global tramplin_80
global tramplin_81
global tramplin_82
global tramplin_83
global tramplin_84
global tramplin_85
global tramplin_86
global tramplin_87
global tramplin_88
global tramplin_89
global tramplin_8A
global tramplin_8B
global tramplin_8C
global tramplin_8D
global tramplin_8E
global tramplin_8F
global tramplin_90
global tramplin_91
global tramplin_92
global tramplin_93
global tramplin_94
global tramplin_95
global tramplin_96
global tramplin_97
global tramplin_98
global tramplin_99
global tramplin_9A
global tramplin_9B
global tramplin_9C
global tramplin_9D
global tramplin_9E
global tramplin_9F
global tramplin_A0
global tramplin_A1
global tramplin_A2
global tramplin_A3
global tramplin_A4
global tramplin_A5
global tramplin_A6
global tramplin_A7
global tramplin_A8
global tramplin_A9
global tramplin_AA
global tramplin_AB
global tramplin_AC
global tramplin_AD
global tramplin_AE
global tramplin_AF
global tramplin_B0
global tramplin_B1
global tramplin_B2
global tramplin_B3
global tramplin_B4
global tramplin_B5
global tramplin_B6
global tramplin_B7
global tramplin_B8
global tramplin_B9
global tramplin_BA
global tramplin_BB
global tramplin_BC
global tramplin_BD
global tramplin_BE
global tramplin_BF
global tramplin_C0
global tramplin_C1
global tramplin_C2
global tramplin_C3
global tramplin_C4
global tramplin_C5
global tramplin_C6
global tramplin_C7
global tramplin_C8
global tramplin_C9
global tramplin_CA
global tramplin_CB
global tramplin_CC
global tramplin_CD
global tramplin_CE
global tramplin_CF
global tramplin_D0
global tramplin_D1
global tramplin_D2
global tramplin_D3
global tramplin_D4
global tramplin_D5
global tramplin_D6
global tramplin_D7
global tramplin_D8
global tramplin_D9
global tramplin_DA
global tramplin_DB
global tramplin_DC
global tramplin_DD
global tramplin_DE
global tramplin_DF
global tramplin_E0
global tramplin_E1
global tramplin_E2
global tramplin_E3
global tramplin_E4
global tramplin_E5
global tramplin_E6
global tramplin_E7
global tramplin_E8
global tramplin_E9
global tramplin_EA
global tramplin_EB
global tramplin_EC
global tramplin_ED
global tramplin_EE
global tramplin_EF
global tramplin_F0
global tramplin_F1
global tramplin_F2
global tramplin_F3
global tramplin_F4
global tramplin_F5
global tramplin_F6
global tramplin_F7
global tramplin_F8
global tramplin_F9
global tramplin_FA
global tramplin_FB
global tramplin_FC
global tramplin_FD
global tramplin_FE
global tramplin_FF

extern interrupt_handler
extern tet

collect_context:
    push ds
    push es
    push fs
    push gs
    pusha
    push esp
    mov eax, 0x10
    mov ds, ax
    mov es, ax
    call interrupt_handler
    add esp, 4
    popa
    pop gs
    pop fs
    pop es
    pop ds
    add esp, 8
    iretd


tramplin_00:
 deadcode
 push 0x00
 jmp collect_context

tramplin_01:
 deadcode
 push 0x01
 jmp collect_context

tramplin_02:
 deadcode
 push 0x02
 jmp collect_context

tramplin_03:
 deadcode
 push 0x03
 jmp collect_context

tramplin_04:
 deadcode
 push 0x04
 jmp collect_context

tramplin_05:
 deadcode
 push 0x05
 jmp collect_context

 tramplin_06:
 deadcode
 push 0x06
 jmp collect_context

tramplin_07:
 deadcode
 push 0x07
 jmp collect_context

tramplin_08:
 push 0x08
 jmp collect_context

tramplin_09:
 deadcode
 push 0x09
 jmp collect_context

tramplin_0A:
 push 0x0A
 jmp collect_context

tramplin_0B:
 push 0x0B
 jmp collect_context

tramplin_0C:
 push 0x0C
 jmp collect_context

tramplin_0D:
 push 0x0D
 jmp collect_context

tramplin_0E:
 push 0x0E
 jmp collect_context

tramplin_0F:
 deadcode
 push 0x0F
 jmp collect_context

tramplin_10:
 deadcode
 push 0x10
 jmp collect_context

tramplin_11:
 push 0x11
 jmp collect_context

tramplin_12:
 deadcode
 push 0x12
 jmp collect_context

tramplin_13:
 deadcode
 push 0x13
 jmp collect_context

tramplin_14:
 deadcode
 push 0x14
 jmp collect_context

tramplin_15:
 push 0x15
 jmp collect_context

tramplin_16:
 deadcode
 push 0x16
 jmp collect_context

tramplin_17:
 deadcode
 push 0x17
 jmp collect_context

tramplin_18:
 deadcode
 push 0x18
 jmp collect_context

tramplin_19:
 deadcode
 push 0x19
 jmp collect_context

tramplin_1A:
 deadcode
 push 0x1A
 jmp collect_context

tramplin_1B:
 deadcode
 push 0x1B
 jmp collect_context

tramplin_1C:
 deadcode
 push 0x1C
 jmp collect_context

tramplin_1D:
 push 0x1D
 jmp collect_context

tramplin_1E:
 push 0x1E
 jmp collect_context

tramplin_1F:
 deadcode
 push 0x1F
 jmp collect_context

tramplin_20:
deadcode
push 0x20
jmp collect_context

tramplin_21:
deadcode
push 0x21
jmp collect_context

tramplin_22:
deadcode
push 0x22
jmp collect_context

tramplin_23:
deadcode
push 0x23
jmp collect_context

tramplin_24:
deadcode
push 0x24
jmp collect_context

tramplin_25:
deadcode
push 0x25
jmp collect_context

tramplin_26:
deadcode
push 0x26
jmp collect_context

tramplin_27:
deadcode
push 0x27
jmp collect_context

tramplin_28:
deadcode
push 0x28
jmp collect_context

tramplin_29:
deadcode
push 0x29
jmp collect_context

tramplin_2A:
deadcode
push 0x2A
jmp collect_context

tramplin_2B:
deadcode
push 0x2B
jmp collect_context

tramplin_2C:
deadcode
push 0x2C
jmp collect_context

tramplin_2D:
deadcode
push 0x2D
jmp collect_context

tramplin_2E:
deadcode
push 0x2E
jmp collect_context

tramplin_2F:
deadcode
push 0x2F
jmp collect_context

tramplin_30:
deadcode
push 0x30
jmp collect_context

tramplin_31:
deadcode
push 0x31
jmp collect_context

tramplin_32:
deadcode
push 0x32
jmp collect_context

tramplin_33:
deadcode
push 0x33
jmp collect_context

tramplin_34:
deadcode
push 0x34
jmp collect_context

tramplin_35:
deadcode
push 0x35
jmp collect_context

tramplin_36:
deadcode
push 0x36
jmp collect_context

tramplin_37:
deadcode
push 0x37
jmp collect_context

tramplin_38:
deadcode
push 0x38
jmp collect_context

tramplin_39:
deadcode
push 0x39
jmp collect_context

tramplin_3A:
deadcode
push 0x3A
jmp collect_context

tramplin_3B:
deadcode
push 0x3B
jmp collect_context

tramplin_3C:
deadcode
push 0x3C
jmp collect_context

tramplin_3D:
deadcode
push 0x3D
jmp collect_context

tramplin_3E:
deadcode
push 0x3E
jmp collect_context

tramplin_3F:
deadcode
push 0x3F
jmp collect_context

tramplin_40:
deadcode
push 0x40
jmp collect_context

tramplin_41:
deadcode
push 0x41
jmp collect_context

tramplin_42:
deadcode
push 0x42
jmp collect_context

tramplin_43:
deadcode
push 0x43
jmp collect_context

tramplin_44:
deadcode
push 0x44
jmp collect_context

tramplin_45:
deadcode
push 0x45
jmp collect_context

tramplin_46:
deadcode
push 0x46
jmp collect_context

tramplin_47:
deadcode
push 0x47
jmp collect_context

tramplin_48:
deadcode
push 0x48
jmp collect_context

tramplin_49:
deadcode
push 0x49
jmp collect_context

tramplin_4A:
deadcode
push 0x4A
jmp collect_context

tramplin_4B:
deadcode
push 0x4B
jmp collect_context

tramplin_4C:
deadcode
push 0x4C
jmp collect_context

tramplin_4D:
deadcode
push 0x4D
jmp collect_context

tramplin_4E:
deadcode
push 0x4E
jmp collect_context

tramplin_4F:
deadcode
push 0x4F
jmp collect_context

tramplin_50:
deadcode
push 0x50
jmp collect_context

tramplin_51:
deadcode
push 0x51
jmp collect_context

tramplin_52:
deadcode
push 0x52
jmp collect_context

tramplin_53:
deadcode
push 0x53
jmp collect_context

tramplin_54:
deadcode
push 0x54
jmp collect_context

tramplin_55:
deadcode
push 0x55
jmp collect_context

tramplin_56:
deadcode
push 0x56
jmp collect_context

tramplin_57:
deadcode
push 0x57
jmp collect_context

tramplin_58:
deadcode
push 0x58
jmp collect_context

tramplin_59:
deadcode
push 0x59
jmp collect_context

tramplin_5A:
deadcode
push 0x5A
jmp collect_context

tramplin_5B:
deadcode
push 0x5B
jmp collect_context

tramplin_5C:
deadcode
push 0x5C
jmp collect_context

tramplin_5D:
deadcode
push 0x5D
jmp collect_context

tramplin_5E:
deadcode
push 0x5E
jmp collect_context

tramplin_5F:
deadcode
push 0x5F
jmp collect_context

tramplin_60:
deadcode
push 0x60
jmp collect_context

tramplin_61:
deadcode
push 0x61
jmp collect_context

tramplin_62:
deadcode
push 0x62
jmp collect_context

tramplin_63:
deadcode
push 0x63
jmp collect_context

tramplin_64:
deadcode
push 0x64
jmp collect_context

tramplin_65:
deadcode
push 0x65
jmp collect_context

tramplin_66:
deadcode
push 0x66
jmp collect_context

tramplin_67:
deadcode
push 0x67
jmp collect_context

tramplin_68:
deadcode
push 0x68
jmp collect_context

tramplin_69:
deadcode
push 0x69
jmp collect_context

tramplin_6A:
deadcode
push 0x6A
jmp collect_context

tramplin_6B:
deadcode
push 0x6B
jmp collect_context

tramplin_6C:
deadcode
push 0x6C
jmp collect_context

tramplin_6D:
deadcode
push 0x6D
jmp collect_context

tramplin_6E:
deadcode
push 0x6E
jmp collect_context

tramplin_6F:
deadcode
push 0x6F
jmp collect_context

tramplin_70:
deadcode
push 0x70
jmp collect_context

tramplin_71:
deadcode
push 0x71
jmp collect_context

tramplin_72:
deadcode
push 0x72
jmp collect_context

tramplin_73:
deadcode
push 0x73
jmp collect_context

tramplin_74:
deadcode
push 0x74
jmp collect_context

tramplin_75:
deadcode
push 0x75
jmp collect_context

tramplin_76:
deadcode
push 0x76
jmp collect_context

tramplin_77:
deadcode
push 0x77
jmp collect_context

tramplin_78:
deadcode
push 0x78
jmp collect_context

tramplin_79:
deadcode
push 0x79
jmp collect_context

tramplin_7A:
deadcode
push 0x7A
jmp collect_context

tramplin_7B:
deadcode
push 0x7B
jmp collect_context

tramplin_7C:
deadcode
push 0x7C
jmp collect_context

tramplin_7D:
deadcode
push 0x7D
jmp collect_context

tramplin_7E:
deadcode
push 0x7E
jmp collect_context

tramplin_7F:
deadcode
push 0x7F
jmp collect_context

tramplin_80:
deadcode
push 0x80
jmp collect_context

tramplin_81:
deadcode
push 0x81
jmp collect_context

tramplin_82:
deadcode
push 0x82
jmp collect_context

tramplin_83:
deadcode
push 0x83
jmp collect_context

tramplin_84:
deadcode
push 0x84
jmp collect_context

tramplin_85:
deadcode
push 0x85
jmp collect_context

tramplin_86:
deadcode
push 0x86
jmp collect_context

tramplin_87:
deadcode
push 0x87
jmp collect_context

tramplin_88:
deadcode
push 0x88
jmp collect_context

tramplin_89:
deadcode
push 0x89
jmp collect_context

tramplin_8A:
deadcode
push 0x8A
jmp collect_context

tramplin_8B:
deadcode
push 0x8B
jmp collect_context

tramplin_8C:
deadcode
push 0x8C
jmp collect_context

tramplin_8D:
deadcode
push 0x8D
jmp collect_context

tramplin_8E:
deadcode
push 0x8E
jmp collect_context

tramplin_8F:
deadcode
push 0x8F
jmp collect_context

tramplin_90:
deadcode
push 0x90
jmp collect_context

tramplin_91:
deadcode
push 0x91
jmp collect_context

tramplin_92:
deadcode
push 0x92
jmp collect_context

tramplin_93:
deadcode
push 0x93
jmp collect_context

tramplin_94:
deadcode
push 0x94
jmp collect_context

tramplin_95:
deadcode
push 0x95
jmp collect_context

tramplin_96:
deadcode
push 0x96
jmp collect_context

tramplin_97:
deadcode
push 0x97
jmp collect_context

tramplin_98:
deadcode
push 0x98
jmp collect_context

tramplin_99:
deadcode
push 0x99
jmp collect_context

tramplin_9A:
deadcode
push 0x9A
jmp collect_context

tramplin_9B:
deadcode
push 0x9B
jmp collect_context

tramplin_9C:
deadcode
push 0x9C
jmp collect_context

tramplin_9D:
deadcode
push 0x9D
jmp collect_context

tramplin_9E:
deadcode
push 0x9E
jmp collect_context

tramplin_9F:
deadcode
push 0x9F
jmp collect_context

tramplin_A0:
deadcode
push 0xA0
jmp collect_context

tramplin_A1:
deadcode
push 0xA1
jmp collect_context

tramplin_A2:
deadcode
push 0xA2
jmp collect_context

tramplin_A3:
deadcode
push 0xA3
jmp collect_context

tramplin_A4:
deadcode
push 0xA4
jmp collect_context

tramplin_A5:
deadcode
push 0xA5
jmp collect_context

tramplin_A6:
deadcode
push 0xA6
jmp collect_context

tramplin_A7:
deadcode
push 0xA7
jmp collect_context

tramplin_A8:
deadcode
push 0xA8
jmp collect_context

tramplin_A9:
deadcode
push 0xA9
jmp collect_context

tramplin_AA:
deadcode
push 0xAA
jmp collect_context

tramplin_AB:
deadcode
push 0xAB
jmp collect_context

tramplin_AC:
deadcode
push 0xAC
jmp collect_context

tramplin_AD:
deadcode
push 0xAD
jmp collect_context

tramplin_AE:
deadcode
push 0xAE
jmp collect_context

tramplin_AF:
deadcode
push 0xAF
jmp collect_context

tramplin_B0:
deadcode
push 0xB0
jmp collect_context

tramplin_B1:
deadcode
push 0xB1
jmp collect_context

tramplin_B2:
deadcode
push 0xB2
jmp collect_context

tramplin_B3:
deadcode
push 0xB3
jmp collect_context

tramplin_B4:
deadcode
push 0xB4
jmp collect_context

tramplin_B5:
deadcode
push 0xB5
jmp collect_context

tramplin_B6:
deadcode
push 0xB6
jmp collect_context

tramplin_B7:
deadcode
push 0xB7
jmp collect_context

tramplin_B8:
deadcode
push 0xB8
jmp collect_context

tramplin_B9:
deadcode
push 0xB9
jmp collect_context

tramplin_BA:
deadcode
push 0xBA
jmp collect_context

tramplin_BB:
deadcode
push 0xBB
jmp collect_context

tramplin_BC:
deadcode
push 0xBC
jmp collect_context

tramplin_BD:
deadcode
push 0xBD
jmp collect_context

tramplin_BE:
deadcode
push 0xBE
jmp collect_context

tramplin_BF:
deadcode
push 0xBF
jmp collect_context

tramplin_C0:
deadcode
push 0xC0
jmp collect_context

tramplin_C1:
deadcode
push 0xC1
jmp collect_context

tramplin_C2:
deadcode
push 0xC2
jmp collect_context

tramplin_C3:
deadcode
push 0xC3
jmp collect_context

tramplin_C4:
deadcode
push 0xC4
jmp collect_context

tramplin_C5:
deadcode
push 0xC5
jmp collect_context

tramplin_C6:
deadcode
push 0xC6
jmp collect_context

tramplin_C7:
deadcode
push 0xC7
jmp collect_context

tramplin_C8:
deadcode
push 0xC8
jmp collect_context

tramplin_C9:
deadcode
push 0xC9
jmp collect_context

tramplin_CA:
deadcode
push 0xCA
jmp collect_context

tramplin_CB:
deadcode
push 0xCB
jmp collect_context

tramplin_CC:
deadcode
push 0xCC
jmp collect_context

tramplin_CD:
deadcode
push 0xCD
jmp collect_context

tramplin_CE:
deadcode
push 0xCE
jmp collect_context

tramplin_CF:
deadcode
push 0xCF
jmp collect_context

tramplin_D0:
deadcode
push 0xD0
jmp collect_context

tramplin_D1:
deadcode
push 0xD1
jmp collect_context

tramplin_D2:
deadcode
push 0xD2
jmp collect_context

tramplin_D3:
deadcode
push 0xD3
jmp collect_context

tramplin_D4:
deadcode
push 0xD4
jmp collect_context

tramplin_D5:
deadcode
push 0xD5
jmp collect_context

tramplin_D6:
deadcode
push 0xD6
jmp collect_context

tramplin_D7:
deadcode
push 0xD7
jmp collect_context

tramplin_D8:
deadcode
push 0xD8
jmp collect_context

tramplin_D9:
deadcode
push 0xD9
jmp collect_context

tramplin_DA:
deadcode
push 0xDA
jmp collect_context

tramplin_DB:
deadcode
push 0xDB
jmp collect_context

tramplin_DC:
deadcode
push 0xDC
jmp collect_context

tramplin_DD:
deadcode
push 0xDD
jmp collect_context

tramplin_DE:
deadcode
push 0xDE
jmp collect_context

tramplin_DF:
deadcode
push 0xDF
jmp collect_context

tramplin_E0:
deadcode
push 0xE0
jmp collect_context

tramplin_E1:
deadcode
push 0xE1
jmp collect_context

tramplin_E2:
deadcode
push 0xE2
jmp collect_context

tramplin_E3:
deadcode
push 0xE3
jmp collect_context

tramplin_E4:
deadcode
push 0xE4
jmp collect_context

tramplin_E5:
deadcode
push 0xE5
jmp collect_context

tramplin_E6:
deadcode
push 0xE6
jmp collect_context

tramplin_E7:
deadcode
push 0xE7
jmp collect_context

tramplin_E8:
deadcode
push 0xE8
jmp collect_context

tramplin_E9:
deadcode
push 0xE9
jmp collect_context

tramplin_EA:
deadcode
push 0xEA
jmp collect_context

tramplin_EB:
deadcode
push 0xEB
jmp collect_context

tramplin_EC:
deadcode
push 0xEC
jmp collect_context

tramplin_ED:
deadcode
push 0xED
jmp collect_context

tramplin_EE:
deadcode
push 0xEE
jmp collect_context

tramplin_EF:
deadcode
push 0xEF
jmp collect_context

tramplin_F0:
deadcode
push 0xF0
jmp collect_context

tramplin_F1:
deadcode
push 0xF1
jmp collect_context

tramplin_F2:
deadcode
push 0xF2
jmp collect_context

tramplin_F3:
deadcode
push 0xF3
jmp collect_context

tramplin_F4:
deadcode
push 0xF4
jmp collect_context

tramplin_F5:
deadcode
push 0xF5
jmp collect_context

tramplin_F6:
deadcode
push 0xF6
jmp collect_context

tramplin_F7:
deadcode
push 0xF7
jmp collect_context

tramplin_F8:
deadcode
push 0xF8
jmp collect_context

tramplin_F9:
deadcode
push 0xF9
jmp collect_context

tramplin_FA:
deadcode
push 0xFA
jmp collect_context

tramplin_FB:
deadcode
push 0xFB
jmp collect_context

tramplin_FC:
deadcode
push 0xFC
jmp collect_context

tramplin_FD:
deadcode
push 0xFD
jmp collect_context

tramplin_FE:
deadcode
push 0xFE
jmp collect_context

tramplin_FF:
deadcode
push 0xFF
jmp collect_context