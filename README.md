![Cosmopolitan Honeybadger](usr/share/img/honeybadger.png)

[![build](https://github.com/jart/cosmopolitan/actions/workflows/build.yml/badge.svg)](https://github.com/jart/cosmopolitan/actions/workflows/build.yml)
# Cosmopolitan

[Cosmopolitan Libc](https://justine.lol/cosmopolitan/index.html) makes C
a build-once run-anywhere language, like Java, except it doesn't need an
interpreter or virtual machine. Instead, it reconfigures stock GCC and
Clang to output a POSIX-approved polyglot format that runs natively on
Linux + Mac + Windows + FreeBSD + OpenBSD + NetBSD + BIOS with the best
possible performance and the tiniest footprint imaginable.

## Background

For an introduction to this project, please read the [αcτµαlly pδrταblε
εxεcµταblε](https://justine.lol/ape.html) blog post and [cosmopolitan
libc](https://justine.lol/cosmopolitan/index.html) website. We also have
[API documentation](https://justine.lol/cosmopolitan/documentation.html).

## Getting Started

If you're doing your development work on Linux or BSD then you need just
five files to get started. Here's what you do on Linux:

```sh
wget https://justine.lol/cosmopolitan/cosmopolitan.zip
unzip cosmopolitan.zip
printf 'main() { printf("hello world\\n"); }\n' >hello.c
gcc -g -Os -static -nostdlib -nostdinc -fno-pie -no-pie -mno-red-zone \
  -fno-omit-frame-pointer -pg -mnop-mcount \
  -o hello.com.dbg hello.c -fuse-ld=bfd -Wl,-T,ape.lds \
  -include cosmopolitan.h crt.o ape-no-modify-self.o cosmopolitan.a
objcopy -S -O binary hello.com.dbg hello.com
```

You now have a portable program.

```sh
./hello.com
bash -c './hello.com'  # zsh/fish workaround (we patched them in 2021)
```

Since we used the `ape-no-modify-self.o` bootloader (rather than
`ape.o`) your executable will not modify itself when it's run. What
it'll instead do, is extract a 4kb program to `${TMPDIR:-${HOME:-.}}`
that maps your program into memory without needing to copy it. It's
possible to install the APE loader systemwide as follows.

```sh
# (1) linux systems that want binfmt_misc
ape/apeinstall.sh

# (2) for linux/freebsd/netbsd/openbsd systems
cp build/bootstrap/ape.elf /usr/bin/ape

# (3) for mac os x systems
cp build/bootstrap/ape.macho /usr/bin/ape
```

If you followed steps (2) and (3) then there's going to be a slight
constant-time startup latency each time you run an APE binary. Your
system might also prevent your APE program from being installed to a
system directory as a setuid binary or a script interpreter. To solve
that, you can use the following flag to turn your binary into the
platform local format (ELF or Mach-O):

```sh
$ file hello.com
hello.com: DOS/MBR boot sector
./hello.com --assimilate
$ file hello.com
hello.com: ELF 64-bit LSB executable
```

There's also some other useful flags that get baked into your binary by
default:

```sh
./hello.com --strace   # log system calls to stderr
./hello.com --ftrace   # log function calls to stderr
```

If you want your `hello.com` program to be much tinier, more on the
order of 16kb rather than 60kb, then all you have to do is use
<https://justine.lol/cosmopolitan/cosmopolitan-tiny.zip> instead. See
<https://justine.lol/cosmopolitan/download.html>.

### MacOS

If you're developing on MacOS you can install the GNU compiler
collection for x86_64-elf via homebrew:

```sh
brew install x86_64-elf-gcc
```

Then in the above scripts just replace `gcc` and `objcopy` with
`x86_64-elf-gcc` and `x86_64-elf-objcopy` to compile your APE binary.

### Windows

If you're developing on Windows then you need to download an
x86_64-pc-linux-gnu toolchain beforehand. See the [Compiling on
Windows](https://justine.lol/cosmopolitan/windows-compiling.html)
tutorial. It's needed because the ELF object format is what makes
universal binaries possible.

Cosmopolitan officially only builds on Linux. However, one highly
experimental (and currently broken) thing you could try, is building the
entire cosmo repository from source using the cross9 toolchain.

```
mkdir -p o/third_party
rm -rf o/third_party/gcc
wget https://justine.lol/linux-compiler-on-windows/cross9.zip
unzip cross9.zip
mv cross9 o/third_party/gcc
build/bootstrap/make.com
```

## Source Builds

Cosmopolitan can be compiled from source on any Linux distro. First, you
need to download or clone the repository.

```sh
wget https://justine.lol/cosmopolitan/cosmopolitan.tar.gz
tar xf cosmopolitan.tar.gz  # see releases page
cd cosmopolitan
```

This will build the entire repository and run all the tests:

```sh
build/bootstrap/make.com -j16
o//examples/hello.com
find o -name \*.com | xargs ls -rShal | less
```

If you get an error running make.com then it's probably because you have
WINE installed to `binfmt_misc`. You can fix that by installing the the
APE loader as an interpreter. It'll improve build performance too!

```sh
ape/apeinstall.sh
```

Since the Cosmopolitan repository is very large, you might only want to
build a particular thing. Cosmopolitan's build config does a good job at
having minimal deterministic builds. For example, if you wanted to build
only hello.com then you could do that as follows:

```sh
build/bootstrap/make.com -j16 o//examples/hello.com
```

Sometimes it's desirable to build a subset of targets, without having to
list out each individual one. You can do that by asking make to build a
directory name. For example, if you wanted to build only the targets and
subtargets of the chibicc package including its tests, you would say:

```sh
build/bootstrap/make.com -j16 o//third_party/chibicc
o//third_party/chibicc/chibicc.com --help
```

Cosmopolitan provides a variety of build modes. For example, if you want
really tiny binaries (as small as 12kb in size) then you'd say:

```sh
build/bootstrap/make.com -j16 MODE=tiny
```

Here's some other build modes you can try:

```sh
build/bootstrap/make.com -j16 MODE=dbg       # asan + ubsan + debug
build/bootstrap/make.com -j16 MODE=asan      # production memory safety
build/bootstrap/make.com -j16 MODE=opt       # -march=native optimizations
build/bootstrap/make.com -j16 MODE=rel       # traditional release binaries
build/bootstrap/make.com -j16 MODE=optlinux  # optimal linux-only performance
build/bootstrap/make.com -j16 MODE=tinylinux # tiniest linux-only 4kb binaries
```

For further details, see [//build/config.mk](build/config.mk).

## GDB

Here's the recommended `~/.gdbinit` config:

```
set host-charset UTF-8
set target-charset UTF-8
set target-wide-charset UTF-8
set osabi none
set complaints 0
set confirm off
set history save on
set history filename ~/.gdb_history
define asm
  layout asm
  layout reg
end
define src
  layout src
  layout reg
end
src
```

You normally run the `.com.dbg` file under gdb. If you need to debug the
`.com` file itself, then you can load the debug symbols independently as

```
gdb foo.com -ex 'add-symbol-file foo.com.dbg 0x401000'
```

## Support Vector

| Platform        | Min Version | Circa |
| :---            | ---:        | ---:  |
| AMD             | K8 Venus    | 2005  |
| Intel           | Core        | 2006  |
| New Technology  | Vista       | 2006  |
| GNU/Systemd     | 2.6.18      | 2007  |
| XNU's Not UNIX! | 15.6        | 2018  |
| FreeBSD         | 13          | 2020  |
| OpenBSD         | 6.4         | 2018  |
| NetBSD          | 9.2         | 2021  |

## Special Thanks

Funding for this project is crowdsourced using
[GitHub Sponsors](https://github.com/sponsors/jart) and
[Patreon](https://www.patreon.com/jart). Your support is what makes this
project possible. Thank you! We'd also like to give special thanks to
the following individuals:

- [Joe Drumgoole](https://github.com/jdrumgoole)

For publicly sponsoring our work at the highest tier.
