/* Taint-route fixtures: each fN_entry is an entry point; its parameters are the sources. Each sink is a memcpy into a
 * local 64-byte buffer, so a length bound of 64 satisfies it and anything larger does not. A line marked clamp
 * bounds the length to 64 or less; a line marked breaking bounds it to more than 64.
 *
 * Expected verdict of each memcpy, by construction:
 *   F1 VIOLATED   two call routes to the sink; one caller clamps, the other does not
 *   F2 SATISFIED  two call routes, both clamp
 *   F3 VIOLATED   one function; the clamp is in one arm only and does not dominate the sink
 *   F4 SATISFIED  a satisfying clamp, then a breaking clamp nearer the sink (it can no longer raise the length)
 *   F5 SATISFIED  a breaking clamp, then a satisfying clamp nearer the sink
 *   F6 VIOLATED   two callees return the length; one clamps, the other does not
 *   F7 SATISFIED  two callees return the length; both clamp
 *   F8 SATISFIED  the length passed by value to 50 guarded calls of a defined function, then clamped
 *   F9 VIOLATED   the same, not clamped
 */
typedef unsigned long size_t;
void *memcpy(void *dst, const void *src, size_t n);
int cond(void);

static void copy_in(const char *src, size_t n) {
    char buf[64];
    memcpy(buf, src, n);
}
static void via_clamp(const char *src, size_t n) {
    if (n > 64) n = 64; /* clamp */
    copy_in(src, n);
}
static void via_raw(const char *src, size_t n) {
    copy_in(src, n);
}
void f1_entry(const char *src, size_t n) {
    if (cond())
        via_clamp(src, n);
    else
        via_raw(src, n);
}

static void copy_in2(const char *src, size_t n) {
    char buf[64];
    memcpy(buf, src, n);
}
static void via_clamp2a(const char *src, size_t n) {
    if (n > 64) n = 64; /* clamp */
    copy_in2(src, n);
}
static void via_clamp2b(const char *src, size_t n) {
    if (n > 32) n = 32; /* clamp */
    copy_in2(src, n);
}
void f2_entry(const char *src, size_t n) {
    if (cond())
        via_clamp2a(src, n);
    else
        via_clamp2b(src, n);
}

void f3_entry(const char *src, size_t n) {
    char buf[64];
    size_t m;
    if (cond()) {
        size_t t = n;
        if (t > 64) t = 64; /* clamp */
        m = t;
    } else {
        m = n;
    }
    memcpy(buf, src, m);
}

void f4_entry(const char *src, size_t n) {
    char buf[64];
    if (n > 64) n = 64; /* clamp */
    if (n > 128) n = 128; /* breaking */
    memcpy(buf, src, n);
}

void f5_entry(const char *src, size_t n) {
    char buf[64];
    if (n > 128) n = 128; /* breaking */
    if (n > 64) n = 64; /* clamp */
    memcpy(buf, src, n);
}

static size_t clamp_len(size_t n) {
    if (n > 64) n = 64; /* clamp */
    return n;
}
static size_t keep_len(size_t n) {
    return n;
}
void f6_entry(const char *src, size_t n) {
    char buf[64];
    size_t m;
    if (cond())
        m = clamp_len(n);
    else
        m = keep_len(n);
    memcpy(buf, src, m);
}

static size_t clamp_len7a(size_t n) {
    if (n > 64) n = 64; /* clamp */
    return n;
}
static size_t clamp_len7b(size_t n) {
    if (n > 16) n = 16; /* clamp */
    return n;
}
void f7_entry(const char *src, size_t n) {
    char buf[64];
    size_t m;
    if (cond())
        m = clamp_len7a(n);
    else
        m = clamp_len7b(n);
    memcpy(buf, src, m);
}

int use(const char *src, size_t n) { return src[0] + (int)n; }
void f8_entry(const char *src, size_t n) {
    char buf[64];
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (n > 64) n = 64; /* clamp */
    memcpy(buf, src, n);
}

void f9_entry(const char *src, size_t n) {
    char buf[64];
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    if (cond())
        use(src, n);
    memcpy(buf, src, n);
}

