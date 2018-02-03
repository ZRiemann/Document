#include <stdio.h>
#include <st.h>

typedef int err_t;
const char *err_prefix = "ST_EORR: ";
#define zst_error() perror(err_prefix)

err_t zst_init(int eventsys);
err_t zst_set_switch_cb(st_switch_cb_t in, st_switch_cb_t out);

int main(int argc, char **argv){
    /* Library Initialization */
    zst_init(ST_EVENTSYS_ALT);
    zst_set_switch_cb(NULL, NULL);

    /* Thread Control and Indentification */
}

err_t zst_init(int eventsys){
    err_t ret = 0;
    do{
        /* 1. Set event notification mechanism */
        if(-1 == (ret = st_set_eventsys(eventsys))){
            break;
        }
        /* 2. Initializes the runtime. */
        if(-1 == (ret = st_init())){
            break;
        }
        /* 3. List state threads configs */
        printf("st.fd_limit<%d>\n", st_getfdlimit());
        printf("st.eventsys<%d %s>", st_get_eventsys(), st_get_eventsys_name());
    }while(0);

    if(ret){
        zst_error();
    }
    return ret;
}

err_t zst_set_switch_cb(st_switch_cb_t in, st_switch_cb_t out){
    st_set_switch_in_cb(in);
    st_set_switch_out_cb(out);
}
