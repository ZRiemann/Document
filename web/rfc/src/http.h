/*
 * All rights reserved Z.Riemann.
 */
#ifndef _Z_HTTP_H_
#define _Z_HTTP_H_

#include <zit/base/error.h>
/**
 * HTTP/1.1 parser see RFC-2616
 */
/*
 * 2.2 Basic Rule
 * OCTET          = <any 8-bit sequence of data>
 *  CHAR           = <any US-ASCII character (octets 0 - 127)>
 *  UPALPHA        = <any US-ASCII uppercase letter "A".."Z">
 *  LOALPHA        = <any US-ASCII lowercase letter "a".."z">
 *  ALPHA          = UPALPHA | LOALPHA
 *  DIGIT          = <any US-ASCII digit "0".."9">
 *  CTL            = <any US-ASCII control character
 *  (octets 0 - 31) and DEL (127)>
 *  CR             = <US-ASCII CR, carriage return (13)>
 *  LF             = <US-ASCII LF, linefeed (10)>
 *  SP             = <US-ASCII SP, space (32)>
 *  HT             = <US-ASCII HT, horizontal-tab (9)>
 *  <">            = <US-ASCII double-quote mark (34)>
 *
 *  CRLF           = CR LF
 *  LWS            = [CRLF] 1*( SP | HT )
 *  TEXT           = <any OCTET except CTLs, but including LWS>
 *  HEX            = "A" | "B" | "C" | "D" | "E" | "F" |
 *                   "a"   | "b" | "c" | "d" | "e" | "f" | DIGIT
 *
 *  token          = 1*<any CHAR except CTLs or separators>
 *  separators     = "(" | ")" | "<" | ">" | "@" |
 *                   ","   | ";" | ":" | "\" | <"> |
 *                   "/"  | "[" | "]" | "?" | "=" |
 *                   "{"  | "}" | SP | HT
 *  comment        = "(" *( ctext | quoted-pair | comment ) ")"
 *  ctext          = <any TEXT excluding "(" and ")">
 *
 *  quoted-string  = ( <"> *(qdtext | quoted-pair ) <"> )
 *  qdtext         = <any TEXT except <">>
 *  quoted-pair    = "\" CHAR
 */
#define ZHTTP_CR 13 /* 0xD carriage return */
#define ZHTTP_LF 10 /* 0xA linefeed */
#define ZHTTP_SP 32 /* 0x10 space*/
#define ZHTTP_HT 9  /* 0x9 horizontal-tab */
#define ZHTTP_CRLF 0xDA /* end-of-line marker */

/*
 * c = char
 * pc = char*
 */
#define ZHTTP_IS_UPALAHA(c) (c >= 'A' && c <= 'Z')
#define ZHTTP_IS_LOALPHA(c) (c >= 'a' && c <= 'z')
#define ZHTTP_IS_ALPHA(c) (IS_UPALAHA(c) || IS_LOALPHA(c))
#define ZHTTP_IS_DIGIT(c) (c >= '0' && c <= '9')
#define ZHTTP_IS_CRLF(pc) (*pc == ZHTTP_CR && *(pc + 1) == ZHTTP_LF))
#define ZHTTP_IS_HEX(c) (ZHTTP_IS_DIGIT(c) || \
                         (c >= 'a' && c <= 'f') || \
                         (c >= 'A' && c <= 'F'))

#define ZHTTP_IS_LWS(pc) ()/* LWS = [CRLF] 1*(SP | HT) */
#define ZHTTP_IS_TOKEN(pc) ()
#define ZHTTP_IS_URI(pc)

/*
 * 3 Protocol Parameters
 */
#define ZHTTP_VERSION "HTTP/1.1" /* <major>.<minor> numbering scheme */

/* 6.1.1 State Code and Preson Phrase
 * The first digit of the Status-Code defines the class of response.
 * - 1xx: Informational - Request received, continuing process
 * - 2xx: Success - The action was successfully received, understood, and accepted
 * - 3xx: Redirection - Further action must be taken in order to complete the request
 * - 4xx: Client Error - The request contains bad syntax or cannot be fulfilled
 * - 5xx: Server Error - The server failed to fulfill an apparently valid request
 *
 * Status-Code:
 *  "100"  ; Section 10.1.1: Continue
 *  "101"  ; Section 10.1.2: Switching Protocols
 *  "200"  ; Section 10.2.1: OK
 *  "201"  ; Section 10.2.2: Created
 *  "202"  ; Section 10.2.3: Accepted
 *  "203"  ; Section 10.2.4: Non-Authoritative Information
 *  "204"  ; Section 10.2.5: No Content
 *  "205"  ; Section 10.2.6: Reset Content
 *  "206"  ; Section 10.2.7: Partial Content
 *  "300"  ; Section 10.3.1: Multiple Choices
 *  "301"  ; Section 10.3.2: Moved Permanently
 *  "302"  ; Section 10.3.3: Found
 *  "303"  ; Section 10.3.4: See Other
 *  "304"  ; Section 10.3.5: Not Modified
 *  "305"  ; Section 10.3.6: Use Proxy
 *  "307"  ; Section 10.3.8: Temporary Redirect
 *  "400"  ; Section 10.4.1: Bad Request
 *  "401"  ; Section 10.4.2: Unauthorized
 *  "402"  ; Section 10.4.3: Payment Required
 *  "403"  ; Section 10.4.4: Forbidden
 *  "404"  ; Section 10.4.5: Not Found
 *  "405"  ; Section 10.4.6: Method Not Allowed
 *  "406"  ; Section 10.4.7: Not Acceptable
 *  extension-code
 *  extension-code = 3DIGIT
 *  Reason-Phrase  = *<TEXT, excluding CR, LF>
 */
#define ZHTTP_SC_CONTINUE "100"
#define ZHTTP_RF_CONTINUE "Continue"
#define ZHTTP_SC_SWITCHING_PROTOCOLS "101"
#define ZHTTP_RF_SWITCHING_PROTOCOLS "Switching Protocols"

#define ZHTTP_SC_OK "200"
#define ZHTTP_RF_OK "OK"
#define ZHTTP_SC_CREATED "201"
#define ZHTTP_RF_CREATED "Created"
#define ZHTTP_SC_ACCEPTED "202"
#define ZHTTP_RF_ACCEPTED "Accepted"
#define ZHTTP_SC_NON_AUTH_INFO "203"
#define ZHTTP_SC_NO_CONTENT "204"
#define ZHTTP_SC_RESET_CONTENT "205"
#define ZHTTP_SC_PARTIAL_CONTENT "206"

#define ZHTTP_SC_MULTIPLE_CHOICES "300"
#define ZHTTP_SC_MOVED_PERMANENTLY "301"
#define ZHTTP_SC_FOUND "302"
#define ZHTTP_SC_SEE_OTHER "303"
#define ZHTTP_SC_NOT_MODIFIED "304"
#define ZHTTP_SC_USE_PROXY "305"
#define ZHTTP_SC_TEMPORARY_REDIRECT "307"

#define ZHTTP_SC_BED_REQUEST "400"
#define ZHTTP_SC_UNAUTHORIZED "401"
#define ZHTTP_SC_PAYMENT_REQUIRED "402"
#define ZHTTP_SC_FORBIDDEN "403"
#define ZHTTP_SC_NOT_FOUND "404"
#define ZHTTP_SC_METHOD_NOT_ALLOWED "405"
#define ZHTTP_SC_NOT_ACCEPTABLE "406"

#define ZHTTP_SC_REQUEST_URL_TOO_LONG 414  /* 255 bytes, older client/proxy may not support*/
#define ZHTTP_RF_REQUEST_URL_TOO_LONG "request-URI too long"

#define ZHTTP_SC_NON_AUTH_INFO "Non-Authoritative Information"
#define ZHTTP_SC_NO_CONTENT "No Content"
#define ZHTTP_SC_RESET_CONTENT "Reset Content"
#define ZHTTP_SC_PARTIAL_CONTENT "Partial Content"

#define ZHTTP_SC_MULTIPLE_CHOICES "Multiple Choices"
/**
 * PUT server desires request be applied to a different URI
 */
#define ZHTTP_SC_MOVED_PERMANENTLY "Moved Permanently"
#define ZHTTP_SC_FOUND "Found"
#define ZHTTP_SC_SEE_OTHER "See Other"
#define ZHTTP_SC_NOT_MODIFIED "Not Modified"
#define ZHTTP_SC_USE_PROXY "Use Proxy"
#define ZHTTP_SC_TEMPORARY_REDIRECT "Temporary Redirect"

#define ZHTTP_SC_BED_REQUEST "Bad Request"
#define ZHTTP_SC_UNAUTHORIZED "Unauthorized"
#define ZHTTP_SC_PAYMENT_REQUIRED "Payment Required"
#define ZHTTP_SC_FORBIDDEN "Forbidden"
#define ZHTTP_SC_NOT_FOUND "Not Found"
#define ZHTTP_SC_METHOD_NOT_ALLOWED "Method Not Allowed"
#define ZHTTP_SC_NOT_ACCEPTABLE "Not Acceptable"

/**
 * parse http URL
 * http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]
 * @param url [in] http URL
 * @return error code
 */
zerr_t zhttp_parse_rul(const char *url);

/**
 * 3.2.3 URI Comparison
 * use a case-sensitive octet-by-octet comparison
 * exceptions:
 * - A port that is empty or not given is equivalent to the default
 *   port for that URI-reference;
 * - Comparisons of host names MUST be case-insensitive;
 * - Comparisons of scheme names MUST be case-insensitive;
 * - An empty abs_path is equivalent to an abs_path of "/".
 *
 * Characters other than those in the "reserved" and "unsafe" sets (see
 * RFC 2396 [42]) are equivalent to their ""%" HEX HEX" encoding.
 *
 * For example, the following three URIs are equivalent:
 * http://abc.com:80/~smith/home.html
 * http://ABC.com/%7Esmith/home.html
 * http://ABC.com:/%7esmith/home.html
 */
zerr_t zhttp_compare_rul(const char *base, const char *compare);

/**
 * convert time to string
 */
zerr_t zhttp_datetime_string(time_t time, char *datetime);

/**
 * check message body
 * 4.3 Message Body
 *   - All responses to the HEAD request method MUST NOT include a message-body.
 *   - All 1xx(informational), 204 (no content), and 304 (not modified) responses
 *     MUST NOT include a message-body.
 *   - All other responses do include a message-body, although it MAY be of zero length.
 * 4.4 Message Length
 *   - Any response message which "MUST NOT" include a message-body
 *     is always terminated by the first empty line after the header fields
 *   - If a Transfer-Encoding header field is present then the transfer-length is
 *     defined by use of the "chunked" transfer-coding
 *   - If a Content-Length header field is present,
 *     its decimal value in OCTETs represents both the entity-length and the transfer-length.
 *   - If the message uses the media type "multipart/byteranges", and the
 *   - By the server closing the connection.
 *   - If a request contains a message-body and a Content-Length is not given,
 *     the server SHOULD respond with 400
 *   - if it cannot determine the length of the message, or with 411 (length required) if
 *     it wishes to insist on receiving a valid Content-Length.
 *   - Messages MUST NOT include both a Content-Length header field and a
 *     non-identity transfer-coding. If the message does include a non-
 *     identity transfer-coding, the Content-Length MUST be ignored.
 * @return error code
 */
zerr_t zhttp_parse_message_body(const char *message_body);
#endif