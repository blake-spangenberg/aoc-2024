- The contents of `util.h`
    - Ideally you'd re-write all the macro-style utilities to use `typeof()` like so:

```c
#define max(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a > _b ? _a : _b; \
})
```

- Making everything a struct is good because it lets you avoid memcpy
- Have to define `_POSIX_C_SOURCE` before defining any system headers
- Makefiles
