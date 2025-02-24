-- Copyright 2022 Justine Alexandra Roberts Tunney
--
-- Permission to use, copy, modify, and/or distribute this software for
-- any purpose with or without fee is hereby granted, provided that the
-- above copyright notice and this permission notice appear in all copies.
--
-- THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
-- WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
-- WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
-- AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
-- DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
-- PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
-- TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
-- PERFORMANCE OF THIS SOFTWARE.

m,a,b,c,d = assert(re.search([[^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$]], "127.0.0.1"))
assert(m == "127.0.0.1")
assert(a == "127")
assert(b == "0")
assert(c == "0")
assert(d == "1")

p = assert(re.compile[[^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$]])
m,a,b,c,d = assert(p:search("127.0.0.1"))
assert(m == "127.0.0.1")
assert(a == "127")
assert(b == "0")
assert(c == "0")
assert(d == "1")

m,a,b,c,d = assert(re.search([[\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)\.\([0-9]*\)]], "127.0.0.1", re.BASIC))
assert(m == "127.0.0.1")
assert(a == "127")
assert(b == "0")
assert(c == "0")
assert(d == "1")

p,e = re.compile("[{")
assert(e:errno() == re.EBRACK)
assert(e:doc() == "Missing ']'")
