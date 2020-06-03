#include <jni.h>

JNIEXPORT void JNICALL
Java_com_secret_fridawars_MainActivity_init(JNIEnv *env, jobject thiz) {
    // do your shits, remove this if not needed or add stuff
}

// dt_init function
__attribute__((constructor))
static inline void init() {
    // do your shits, remove this if not needed or add more constructor functions
}
