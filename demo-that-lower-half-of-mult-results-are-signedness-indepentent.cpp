#include <bitset>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct I32 {
    I32(int32_t x) { val.s = x; }

    I32(uint32_t x) { val.u = x; }

    union {
        uint32_t u;
        int32_t s;
    } val;
};

struct I64 {
    I64(int64_t x) { val.s = x; }

    I64(uint64_t x) { val.u = x; }

    union {
        uint64_t u;
        int64_t s;
    } val;
};

ostream& operator<<(ostream& os, const I32& i) {
    os << "u:";
    os << setfill('0') << setw(10);
    os << i.val.u;

    os << " s:";
    os << setfill('0') << internal;
    os << setw(10 + 1);
    os << showpos;
    os << i.val.s;

    os << " h:0x";
    os << setfill('0') << internal;
    os << setw(sizeof(i.val.u) * 2);
    os << hex;
    os << i.val.u;
    os << dec;

    os << " b:" << bitset<sizeof(i.val.u) * 8>{i.val.u};
    return os;
}

ostream& operator<<(ostream& os, const I64& i) {
    os << "u:";
    os << setfill('0') << setw(20);
    os << i.val.u;

    os << " s:";
    os << setfill('0') << internal;
    os << setw(20 + 1);
    os << showpos;
    os << i.val.s;

    os << " h:0x";
    os << setfill('0') << internal;
    os << setw(sizeof(i.val.u) * 2);
    os << hex;
    os << i.val.u;
    os << dec;

    os << " b:" << bitset<sizeof(i.val.u) * 8>{i.val.u};
    return os;
}

int32_t main() {
    I32 a(-3);
    I32 b(3000000000u);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    I64 a64(-3l);
    I64 b64(3000000000ul);
    cout << "a64 = " << a64 << endl;
    cout << "b64 = " << b64 << endl;

    cout << endl;
    cout << endl;

    // These output of this section demonstrates that, at least for these
    // numbers, the least-significant 32-bits have the same value for both
    // multiplications, but the most-significant 32-bits differ depending on
    // the whether the multiplication assumed signed or unsigned operands.
    const auto ab_u = a.val.u * b.val.u;
    const auto ab_s = a.val.s * b.val.s;
    cout << "a.val.u * b.val.u = " << I32(ab_u) << endl;
    cout << "a.val.s * b.val.s = " << I32(ab_s) << endl;

    cout << endl;
    cout << endl;

    const uint64_t ab_cast_to_64_u = uint64_t(a.val.u) * uint64_t(b.val.u);
    const int64_t ab_cast_to_64_s = int64_t(a.val.s) * int64_t(b.val.s);
    cout << "uint64_t(a.val.u) * uint64_t(b.val.u) = " << I64(ab_cast_to_64_u)
         << endl;
    cout << "int64_t(a.val.s)  * int64_t(b.val.s)  = " << I64(ab_cast_to_64_s)
         << endl;

    cout << endl;
    cout << endl;

    const uint64_t ab64_u = a64.val.u * b64.val.u;
    const int64_t ab64_s = a64.val.s * b64.val.s;
    cout << "a64.val.u * b64.val.u = " << I64(ab64_u) << endl;
    cout << "a64.val.s * b64.val.s = " << I64(ab64_s) << endl;
}

