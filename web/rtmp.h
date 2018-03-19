#ifndef _ZPTL_RTMP_H_
#define _ZPTL_RTMP_H_

#include <zsi/base/error.h>
#include <zsi/base/type.h>

typedef zinline static inline

/**
 * chunk format
 * +-------------+----------------+-------------------+--------------+
 * | Basic header|Chunk Msg Header|Extended Time Stamp|   Chunk Data | Name
 * +-------------+----------------+-------------------+--------------+
 * | 1~3         | 0/3/7/11       | 0/4               | < chunk size | Bytes
 * +-------------+----------------+-------------------+--------------+
 *
 * Basic header
 *  0 1 2 3 4 5 6 7
 * +-+-+-+-+-+-+-+-+
 * |fmt|   cs id   |  csid(3~63)
 * +-+-+-+-+-+-+-+-+
 *
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |fmt| 0         |  cs id - 64   | csid(64~319)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |fmt| 1         |           cs id - 64          | csid(64~63399)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

#define ZRTMP_CSID_MASK 0x3f /** chunk stream id masker */
#define ZRTMP_CSID_MAX 65599 /** Max chunk stream id */
#define ZRTMP_CSID_MIN 3 /** min user chunk stream id */
#define ZRTMP_CSID_2B 0 /** reserved csid 0, indicates ID 46~319 */
#define ZRTMP_CSID_3B 1 /** indicates ID 64~65599 */
#define ZRTMP_CSID_MSG 2 /** indicates its low-level protocol message */

typedef uint8_t zbyte_t; /** byte type */
typedef uint8_t zrtmp_bh_t; /** rtmp base header type */
typedef uint32_t zrtmp_csid_t; /** rtmp chunk stream id type */
typedef uint32_t zrtmp_msid_t; /** rtmp message stream id type */

/**
 * @brief get the CSID from RTMP base header
 */
zinline zrtmp_csid_t zrtmp_get_csid(zrtmp_bh_t* bh, zbyte_t **next){
    zrtmp_csid_t csid = *bh & ZRTMP_CSID_MASK;
    if(0 == csid){
        csid = *(bh+1) + 64;
        if(next){
            *next = bh + 2;
        }
    }else if(1 == csid){
        csid = *(uint16_t*)(bh+1) + 64;
        if(next){
            *next = bh + 3;
        }
    }else if(next){
        *next = bh + 1;
    }
    return csid;
}
/**
 * @brief set the CSID to RTMP base header
 */
zinline zerr_t zrtmp_set_csid(zrtmp_bh_t* bh, zrtmp_csid_t csid, zbyte_t **next){
    if(!bh || csid < ZRTMP_CSID_MIN ||
       csid > ZRTMP_CSID_MAX){
        return ZEPARAM_INVALID;
    }
    if(csid < 64){
        /* 1 Bytes */
        *bh |= (zbyte_t)csid;
        if(next){
            *next = bh + 1;
        }
    }else if(csid < 320){
        /* 2 Bytes */
        *bh |= 0xc0;
        *(bh+1) = (zbyte_t)csid + 64;
        if(next){
            *next = bh + 2;
        }
    }else{
        /* 3 Bytes */
        *bh |= 0xc1;
        *(uint16_t*)(bh+1) = (uint16_t)csid;
        if(next){
            *next = bh + 3;
        }
    }
    return ZEOK;
}

/**
 * Chunk Message Header
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | timestamp(delta)                              |message length |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | message length (cont)         |message type id| msg stream id |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             message stream id (cont)          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * fmt:0 11 Bytes
 * fmt:1 7 Bytes no message stream id.
 * fmt:2 3 Bytes just have timestamp.
 * fmt:3 0 Bytes message header same to preview message header.
 */
#define ZRTMP_CMH_TSMAX 0xffffff /**
                                  * max timestamp value,
                                  * if greater use extended timestamp
                                  */
typedef zrtmp_chunk_msg_header_s{
    zbyte_t timestamp[3];
    zbyte_t msg_len[3];
    zbyte_t msg_type;
    zrtmp_msid_t msid;
}zrtmp_cmh_t;

/**
 * Protocol Control Messages
 *
 * msid = 0 && csid = 2 && highest priority
 * has a fixed-size payload
 * always sent in a single chunk
 *
 * MTID CMD              Payload Value
 * 1    set-chunk-size   4       new chunk size
 * 2    abort-message    4       csid
 * 3    acknowledegement 4       total bytes received
 * 4    ---
 * 5    ack-win-size     4       window size
 * 6    bandwidth        5       window size + limit type
 *                               0-hard 1-soft 2-dynamic
 */

typedef zbyte_t zrtmp_mtid_t; /** message type id type */
#define ZRTMP_MTID_CSIZE 0x01 /** Set Chunk Size, default 128Bytes */
#define ZRTMP_MTID_ABORTMSG 0x02 /** Abort Message */
#define ZRTMP_MTID_ACK 0x03 /** Acknowledgement while receive window size bytes */
#define ZRTMP_MTID_5 0x05
#define ZRTMP_MTID_6 0x06

#define ZRTMP_MAX_CSIZE 0xffff /** or 0xffffff, max chunk size */

/**
 * RTMP Message Format
 *
 * Message Header
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Message Type  |              Payload length                   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Timestamp                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     Stream ID                 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * MTID  CMD              Payload Value
 * 4     user-ctl-msg     2+      event-type-2B + event-data
 * 20,17 
 */

/**
 * AMF0
 *
 * 
 * number double 
 */
#endif
