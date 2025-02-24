#ifndef COSMOPOLITAN_LIBC_STR_STR_H_
#define COSMOPOLITAN_LIBC_STR_STR_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_
/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § characters » usas x3.4-1967                               ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│─╝
  fourth age telecommunications */

extern const int8_t kHexToInt[256];
extern const uint8_t gperf_downcase[256];
extern const uint8_t kToLower[256];
extern const uint8_t kToUpper[256];
extern const uint8_t kBase36[256];
extern const char16_t kCp437[256];

int isascii(int);
int isspace(int);
int isalpha(int);
int isdigit(int);
int isalnum(int);
int isxdigit(int);
int isprint(int);
int islower(int);
int isupper(int);
int isblank(int);
int iscntrl(int);
int isgraph(int);
int tolower(int);
int ispunct(int);
int toupper(int);
int hextoint(int);
int cescapec(int);

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § characters » thompson-pike encoding                       ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│─╝
  fifth age telecommunications

      0123456789abcdef
    ┌0─ ☺☻♥♦♣♠•◘○◙♂♀♪♫☼┬───Control
    └1─►◄↕‼¶§▬↨↑↓→←∟↔▲▼┘
    ┌2─ !"#$%&'()*+,-./┐
    │3 0123456789:;<=>?│
    │4 @ABCDEFGHIJKLMNO├───ASA x3.4-1967
    │5 PQRSTUVWXYZ[\]^_│
    │6 `abcdefghijklmno│
    └7─pqrstuvwxyz{|}~⌂┘
    ┌8─ÇüéâäàåçêëèïîìÄÅ┐
    │9 ÉæÆôöòûùÿÖÜ¢£¥€ƒ├───Thompson-Pike Continuation
    │a á¡óúñÑªº¿⌐¬½¼¡«»│    (not really characters)
    └b─░▒▓│┤╡╢╖╕╣║╗╝╜╛┐┘
    ┌c─└┴┬├─┼╞╟╚╔╩╦╠═╬╧┬───1 Continuation will follow
    └d─╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀┘
    ─e─αßΓπΣσμτΦΘΩδ∞φε∩────2 Continuations will follow
     f─≡±≥≤⌠⌡÷≈°∙·√ⁿ²■λ
       │      ││  │││└┤
       │      ││  │└┤ └───5 Continuations follow (and is negative)
       │      │└─┬┘ └─────5 Continuations follow (note: -1=λ┐┐┐┐┐)
       └───┬──┘  └────────4 Continuations follow
           └──────────────3 Continuations follow */

#define INVALID_CODEPOINT 0xfffd

int iswalnum(wint_t);
int iswalpha(wint_t);
int iswblank(wint_t);
int iswcntrl(wint_t);
int iswdigit(wint_t);
int iswgraph(wint_t);
int iswlower(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);
int iswpunct(wint_t);
int iswprint(wint_t);
int iswseparator(wint_t);
wint_t towlower(wint_t);
wint_t towupper(wint_t);

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings                                                   ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

void bzero(void *, size_t) memcpyesque;
void *memset(void *, int, size_t) memcpyesque;
void *memmove(void *, const void *, size_t) memcpyesque;
void *memcpy(void *restrict, const void *restrict, size_t) memcpyesque;
void *mempcpy(void *restrict, const void *restrict, size_t) memcpyesque;
void *memccpy(void *restrict, const void *restrict, int, size_t) memcpyesque;
void bcopy(const void *, void *, size_t) memcpyesque;
void explicit_bzero(void *, size_t);

int bcmp(const void *, const void *, size_t) strlenesque;
int memcmp(const void *, const void *, size_t) strlenesque;
int timingsafe_bcmp(const void *, const void *, size_t);
int timingsafe_memcmp(const void *, const void *, size_t);

size_t strlen(const char *) strlenesque;
size_t strnlen(const char *, size_t) strlenesque;
size_t strnlen_s(const char *, size_t);
char *strchr(const char *, int) strlenesque;
char *index(const char *, int) strlenesque;
void *memchr(const void *, int, size_t) strlenesque;
char *strchrnul(const char *, int) strlenesque returnsnonnull;
void *rawmemchr(const void *, int) strlenesque returnsnonnull;
size_t strlen16(const char16_t *) strlenesque;
size_t strnlen16(const char16_t *, size_t) strlenesque;
size_t strnlen16_s(const char16_t *, size_t);
char16_t *strchr16(const char16_t *, int) strlenesque;
void *memchr16(const void *, int, size_t) strlenesque;
char16_t *strchrnul16(const char16_t *, int) strlenesque returnsnonnull;
void *rawmemchr16(const void *, int) strlenesque returnsnonnull;
size_t wcslen(const wchar_t *) strlenesque;
size_t wcsnlen(const wchar_t *, size_t) strlenesque;
size_t wcsnlen_s(const wchar_t *, size_t);
wchar_t *wcschr(const wchar_t *, wchar_t) strlenesque;
wchar_t *wmemchr(const wchar_t *, wchar_t, size_t) strlenesque;
wchar_t *wcschrnul(const wchar_t *, wchar_t) strlenesque returnsnonnull;
char *strstr(const char *, const char *) strlenesque;
char16_t *strstr16(const char16_t *, const char16_t *) strlenesque;
wchar_t *wcsstr(const wchar_t *, const wchar_t *) strlenesque;
void *rawwmemchr(const void *, wchar_t) strlenesque returnsnonnull;
int strcmp(const char *, const char *) strlenesque;
int strncmp(const char *, const char *, size_t) strlenesque;
int strcmp16(const char16_t *, const char16_t *) strlenesque;
int strncmp16(const char16_t *, const char16_t *, size_t) strlenesque;
int wcscmp(const wchar_t *, const wchar_t *) strlenesque;
int wcsncmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
int wmemcmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
int strcasecmp(const char *, const char *) strlenesque;
int memcasecmp(const void *, const void *, size_t) strlenesque;
int strcasecmp16(const char16_t *, const char16_t *) strlenesque;
int wcscasecmp(const wchar_t *, const wchar_t *) strlenesque;
int strncasecmp(const char *, const char *, size_t) strlenesque;
int strncasecmp16(const char16_t *, const char16_t *, size_t) strlenesque;
int wcsncasecmp(const wchar_t *, const wchar_t *, size_t) strlenesque;
char *strrchr(const char *, int) strlenesque;
void *memrchr(const void *, int, size_t) strlenesque;
char16_t *strrchr16(const char16_t *, int) strlenesque;
void *memrchr16(const void *, int, size_t) strlenesque;
wchar_t *wcsrchr(const wchar_t *, int) strlenesque;
void *wmemrchr(const void *, wchar_t, size_t) strlenesque;
char *strpbrk(const char *, const char *) strlenesque;
char16_t *strpbrk16(const char16_t *, const char16_t *) strlenesque;
wchar_t *wcspbrk(const wchar_t *, const wchar_t *) strlenesque;
size_t strspn(const char *, const char *) strlenesque;
size_t strspn16(const char16_t *, const char16_t *) strlenesque;
size_t wcsspn(const wchar_t *, const wchar_t *) strlenesque;
size_t strcspn(const char *, const char *) strlenesque;
size_t strcspn16(const char16_t *, const char16_t *) strlenesque;
size_t wcscspn(const wchar_t *, const wchar_t *) strlenesque;
void *memfrob(void *, size_t) memcpyesque;
int strcoll(const char *, const char *) strlenesque;
char *strsep(char **, const char *) paramsnonnull();
int strcmpzbw(const uint16_t *, const char *) strlenesque;
int strcasecmpzbw(const uint16_t *, const char *) strlenesque;
char *stpcpy(char *, const char *) memcpyesque;
char *stpncpy(char *, const char *, size_t) memcpyesque;
char *strcat(char *, const char *) memcpyesque;
char16_t *strcat16(char16_t *, const char16_t *) memcpyesque;
wchar_t *wcscat(wchar_t *, const wchar_t *) memcpyesque;
size_t strlcpy(char *, const char *, size_t);
size_t strlcat(char *, const char *, size_t);
size_t strxfrm(char *, const char *, size_t);
char *strcpy(char *, const char *) memcpyesque;
char16_t *strcpy16(char16_t *, const char16_t *) memcpyesque;
wchar_t *wcscpy(wchar_t *, const wchar_t *) memcpyesque;
char *strncat(char *, const char *, size_t) memcpyesque;
char16_t *strncat16(char16_t *, const char16_t *, size_t) memcpyesque;
wchar_t *wcsncat(wchar_t *, const wchar_t *, size_t) memcpyesque;
char *strncpy(char *, const char *, size_t) memcpyesque;
char *strtok(char *, const char *) paramsnonnull((2)) libcesque;
char *strtok_r(char *, const char *, char **) paramsnonnull((2, 3));
wchar_t *wcstok(wchar_t *, const wchar_t *, wchar_t **) paramsnonnull((2, 3));
char *wstrtrunc(uint16_t *) memcpyesque;
char *wstrntrunc(uint16_t *, size_t) memcpyesque;
bool startswith(const char *, const char *) strlenesque;
bool startswithi(const char *, const char *) strlenesque;
bool startswith16(const char16_t *, const char16_t *) strlenesque;
bool wcsstartswith(const wchar_t *, const wchar_t *) strlenesque;
bool endswith(const char *, const char *) strlenesque;
bool endswith16(const char16_t *, const char16_t *) strlenesque;
bool wcsendswith(const wchar_t *, const wchar_t *) strlenesque;
const char *IndexDoubleNulString(const char *, unsigned) strlenesque;
int strverscmp(const char *, const char *);
wchar_t *wmemset(wchar_t *, wchar_t, size_t) memcpyesque;
char16_t *memset16(char16_t *, char16_t, size_t) memcpyesque;
wchar_t *wmemcpy(wchar_t *, const wchar_t *, size_t) memcpyesque;
wchar_t *wmempcpy(wchar_t *, const wchar_t *, size_t) memcpyesque;
wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t) memcpyesque;
void *tinymemccpy(void *, const void *, int, size_t) memcpyesque;
void *memmem(const void *, size_t, const void *, size_t) libcesque nosideeffect;
long a64l(const char *);
char *l64a(long);

char *strntolower(char *, size_t) libcesque;
char *strtolower(char *) libcesque paramsnonnull();
char *strntoupper(char *, size_t) libcesque;
char *strtoupper(char *) libcesque paramsnonnull();
char *_chomp(char *) libcesque;
char16_t *_chomp16(char16_t *) libcesque;
wchar_t *_wchomp(wchar_t *) libcesque;
bool _istext(const void *, size_t) libcesque;
bool _isutf8(const void *, size_t) libcesque;
bool _escapedos(char16_t *, unsigned, const char16_t *, unsigned) libcesque;

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » multibyte                                       ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

typedef unsigned mbstate_t;

axdx_t tprecode8to16(char16_t *, size_t, const char *);
axdx_t tprecode16to8(char *, size_t, const char16_t *);
int strcmp8to16(const char *, const char16_t *) strlenesque;
int strncmp8to16(const char *, const char16_t *, size_t) strlenesque;
int strcasecmp8to16(const char *, const char16_t *) strlenesque;
int strncasecmp8to16(const char *, const char16_t *, size_t) strlenesque;
int strcmp16to8(const char16_t *, const char *) strlenesque;
int strncmp16to8(const char16_t *, const char *, size_t) strlenesque;
int strcasecmp16to8(const char16_t *, const char *) strlenesque;
int strncasecmp16to8(const char16_t *, const char *, size_t) strlenesque;
wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);
int mbtowc(wchar_t *, const char *, size_t);
size_t mbrtowc(wchar_t *, const char *, size_t, mbstate_t *);
size_t mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
size_t mbstowcs(wchar_t *, const char *, size_t);
size_t wcrtomb(char *, wchar_t, mbstate_t *);
size_t c32rtomb(char *, char32_t, mbstate_t *);
size_t mbrtoc32(char32_t *, const char *, size_t, mbstate_t *);
size_t c16rtomb(char *, char16_t, mbstate_t *);
size_t mbrtoc16(char16_t *, const char *, size_t, mbstate_t *);
size_t mbrlen(const char *, size_t, mbstate_t *);
size_t mbsnrtowcs(wchar_t *, const char **, size_t, size_t, mbstate_t *);
size_t wcsnrtombs(char *, const wchar_t **, size_t, size_t, mbstate_t *);
size_t wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
size_t wcstombs(char *, const wchar_t *, size_t);
int mbsinit(const mbstate_t *);
int mblen(const char *, size_t);
int wctomb(char *, wchar_t);
int wctob(wint_t);
wint_t btowc(int);

size_t strclen(const char *) nosideeffect;
size_t strnclen(const char *, size_t) nosideeffect;
size_t strclen16(const char16_t *) nosideeffect;
size_t strnclen16(const char16_t *, size_t) nosideeffect;

typedef unsigned wctype_t;
wctype_t wctype(const char *) strlenesque;
int iswctype(wint_t, wctype_t) pureconst;

typedef const int *wctrans_t;
wctrans_t wctrans(const char *);
wint_t towctrans(wint_t, wctrans_t);

/*───────────────────────────────────────────────────────────────────────────│─╗
│ cosmopolitan § strings » system                                          ─╬─│┼
╚────────────────────────────────────────────────────────────────────────────│*/

char *strsignal(int) returnsnonnull libcesque;
char *strerror(int) returnsnonnull dontthrow nocallback;
char *strerrno(int) nosideeffect libcesque;
char *strerdoc(int) nosideeffect libcesque;
int strerror_r(int, char *, size_t) dontthrow nocallback;
int strerror_wr(int, uint32_t, char *, size_t) dontthrow nocallback;
int __xpg_strerror_r(int, char *, size_t) dontthrow nocallback;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_STR_STR_H_ */
