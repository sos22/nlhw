#define __NR_exit 60
#define __NR_write 1

typedef long ssize_t;
typedef unsigned long size_t;

int errno;

static unsigned long
errno_munge(unsigned long r)
{
	if ((long)r < 0 && (long)r > -4096) {
		errno = -r;
		return (unsigned long)-1;
	} else {
		return r;
	}
}

unsigned long
_syscall1(int sysnr, unsigned long arg)
{
	unsigned long res;
	asm ("syscall\n"
	     : "=a" (res)
	     : "0" (sysnr), "D" (arg)
	     : "memory");
	return errno_munge(res);
}

unsigned long
_syscall3(int sysnr, unsigned long arg1, unsigned long arg2, unsigned long arg3)
{
	unsigned long res;
	asm ("syscall\n"
	     : "=a" (res)
	     : "0" (sysnr), "D" (arg1), "S" (arg2), "d" (arg3)
	     : "memory");
	return errno_munge(res);
}

void
exit(int code)
{
	_syscall1(__NR_exit, code);
}

ssize_t
write(int fd, const void *buf, size_t sz)
{
	return _syscall3(__NR_write, fd, (unsigned long)buf, sz);
}

int
main(int argc, char *argv[])
{
	write(1, "HELLO WORLD\n", sizeof("HELLO WORLD\n"));
	return argc;
}
