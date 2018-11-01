/*
 * All rights reserved Z.Riemann.
 */
#ifndef _Z_HTTP_H_
#define _Z_HTTP_H_

/**
 * HTTP/1.1 parser see RFC-2616
 */
/*
 * 2.2 Basic Rule
 */
#define ZHTTP_CR 13 /* 0xD */
#define ZHTTP_LF 10 /* 0xA */
#define ZHTTP_SP 32 /* 0x10*/
#define ZHTTP_CRLF 0xDA /* end-of-line marker */

#define IS_UPALAHA(x) (x >= 'A' && x <= 'Z')
#define IS_LOALPHA(x) (x >= 'a' && x <= 'z')
#define IS_ALPHA(x) (IS_UPALAHA(x) || IS_LOALPHA(x))
#define IS_DIGIT(x) (x >= '0' && x <= '9')
#endif