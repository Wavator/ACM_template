void solve(InputReader in, PrintWriter out) throws Exception {
            BigInteger integer = new BigInteger(in.next());
            out.println("2-base length = " + integer.bitLength());
            out.println("2-base amount of 1: " + integer.bitCount());
            out.println(integer.abs());
            out.println(integer.add(new BigInteger("2")));
            out.println(integer.andNot(new BigInteger("2")));
            out.println(integer.compareTo(BigInteger.ZERO)); // > 0 is 1
            out.println(integer.divide(new BigInteger("1")));
            out.println(integer.max(new BigInteger("2")));
            out.println(integer.min(new BigInteger("2")));
            out.println(integer.multiply(new BigInteger("2")));
            out.println(integer.negate()); // "return -x"
            out.println(integer.mod(new BigInteger("3")));
            out.println(integer.pow(2));
            out.println(integer.toString());
            out.println(integer.byteValueExact());
            out.println(integer.byteValue());
            out.println(integer.clearBit(1));
            out.println(integer.flipBit(1));
            out.println(integer.gcd(new BigInteger("6")));
            out.println(integer.not());
            out.println(integer.setBit(1));
            out.println(integer.getLowestSetBit());
            out.println(integer.xor(new BigInteger("3")));
            out.println(integer.and(new BigInteger("1")));
            out.println(integer.subtract(new BigInteger("2")));
            out.println(integer.longValue());
            out.println(integer.shiftLeft(2)); // shiftRight
            BigDecimal decimal = new BigDecimal("0.1");
            out.println(decimal.scale()); // decimal's length after '.'
            out.println(decimal.divide(new BigDecimal("2.33333"), 100, 5));
            /*
             * round 100 length after floating point. mode = 1(round_up) ***** if mode == 2 : round = round_down, if mode == 3: round = round_ceiling
             * mode == 4 round_floor ; mode == 5: 4 miss 5 plus. mode == 6: 5 miss 6 pass
             * */
            out.println(decimal.unscaledValue()); // it is a big integer, cut the floating part
            out.println(decimal.scaleByPowerOfTen(1));
        }
