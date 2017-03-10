#ifndef LEMONKITTY_LEXER_H
#define LEMONKITTY_LEXER_H

#define Tok_EOF -1 // eof must be -1....... it is defined in other file

//key word
#define Tok_auto -2 // auto
#define Tok_break -3 // break
#define Tok_case -4 // case
#define Tok_char -5 // char
#define Tok_const -6 // const
#define Tok_continue -7 // continue
#define Tok_default -8 // default
#define Tok_do -9 // do
#define Tok_double -10 // double
#define Tok_else -11 // else
#define Tok_enum -12 // enum
#define Tok_extern -13 // extern
#define Tok_float -14 // float
#define Tok_for -15 // for
#define Tok_goto -16 // goto
#define Tok_if -17 // if
#define Tok_int -18 // int
#define Tok_long -19 // long
#define Tok_register -20 // register
#define Tok_return -21 // return
#define Tok_short -22 // short
#define Tok_signed -23 // signed
#define Tok_sizeof -24 // sizeof
#define Tok_static -25 // static
#define Tok_struct -26 // struct
#define Tok_switch -27 // switch
#define Tok_typedef -28 // typedef
#define Tok_union -29 // union
#define Tok_unsigned -30 // unsigned
#define Tok_void -31 // void
#define Tok_volatile -32 // volatile
#define Tok_while -33 // while

//operator
#define Tok_member -34 // -> 
#define Tok_O_parenthese -35 // (
#define Tok_C_parenthese -36 // )
#define Tok_O_bracket -37 // [
#define Tok_C_bracket -38 // ]
#define Tok_O_braces -39 // {
#define Tok_C_braces -40 // }
#define Tok_not -41 // !
#define Tok_not_by_bit -42 // ~
#define Tok_self_plus -43 // ++
#define Tok_self_minus -44 // --
#define Tok_positive -45 // + positive
#define Tok_negetive -46 // - negetive
#define Tok_pointer -47 // * in pointer
#define Tok_locate_address -48 // & locate address
#define Tok_mul -49 // *
#define Tok_div -50 // /
#define Tok_mod -51 // %
#define Tok_plus -52 // +
#define Tok_minus -53 // -
#define Tok_left_shift -54 // <<
#define Tok_right_shift -55 // >>
#define Tok_less -56 // <
#define Tok_not_larger -57 // <=
#define Tok_not_less -58 // >=
#define Tok_larger -59 // >
#define Tok_equal -60 // ==
#define Tok_not_equal -61 // !=
#define Tok_bit_and -62 // & bit_and
#define Tok_bit_xor -63 // ^ bit_xor
#define Tok_bit_or -64 // | bit_or
#define Tok_and -65 // &&
#define Tok_or -66 // ||
#define Tok_tmop_if -67 // ? 
#define Tok_tmop_or -68 // :
#define Tok_assign -69 // =
#define Tok_plus_assign -70 // +=
#define Tok_minus_assign -71 // -=
#define Tok_mul_assign -72 // *=
#define Tok_div_assign -73 // /=
#define Tok_and_assign -74 // &=
#define Tok_xor_assign -75 // ^=
#define Tok_or_assign -76 // |=
#define Tok_left_shift_assign -77 // <<=
#define Tok_right_shift_assign -78 // >>=
#define Tok_comma -79 // ,
#define Tok_double_quot -80 // "
#define Tok_quot -81 // '
#define Tok_note_line -82 // //
#define Tok_O_note -83 // /*
#define Tok_C_note -84 // */
#define Tok_sharp -85 // #
#define Tok_file -86 // filename

#endif
