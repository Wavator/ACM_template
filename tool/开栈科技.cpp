void Main() {

}

int main() {
#define OPENSTACK
#ifdef OPENSTACK
    size_t size = 70 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
#if (defined _WIN64) or (defined __unix)
    __asm__("movq %0, %%rsp\n" :: "r"(p));
#else
    __asm__("movl %0, %%esp\n" :: "r"(p));
#endif
#endif
    Main();
#ifdef OPENSTACK
    exit(0);
#else
    return 0;
#endif
}
